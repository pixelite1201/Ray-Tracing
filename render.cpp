#include "render.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
sphere *sp;
cylinder *cyl;
cone *con;
vector light_src;
void render::initImg()
{
	img = new vector[w*h];
}
void render::readInput(char *fname, camera &cam)
{
	ifstream infile(fname);
	if(!infile.is_open())
	{
		std::cout<<"File"<<fname<<"cannot be opened"<<"\n";
		return ;
	}
	infile>>w>>h;
	infile>>pw>>ph;
	//cout<<pw<<" "<<ph<<endl;
	infile>>cam.near>>cam.far;
	infile>>cam.fov;
	infile>>cam.lat[0]>>cam.lat[1]>>cam.lat[2];
	infile>>cam.vup[0]>>cam.vup[1]>>cam.vup[2];
	infile>>cam.cop.x>>cam.cop.y>>cam.cop.z;
	//cout<<cam.fov<<endl;
	infile>>objCnt;
	int objType;
	for(int temp=0; temp<objCnt; temp++)
	{
		infile>>objType;
		switch(objType)
		{
			case 0:
				if(sphCnt == 0)
					sp = new sphere[10];
				infile>>sp[sphCnt].color.x>>sp[sphCnt].color.y>>sp[sphCnt].color.z;
				//infile>>sp[sphCnt].emitColor.x>>sp[sphCnt].emitColor.y>>sp[sphCnt].emitColor.z;
				infile>>sp[sphCnt].transp>>sp[sphCnt].reflect;
				infile>>sp[sphCnt].rad;
				infile>>sp[sphCnt].center.x>>sp[sphCnt].center.y>>sp[sphCnt].center.z;
				sp[sphCnt].emitColor=0;
				sphCnt++;
				break;
			case 1:
				if(cylCnt == 0)
					cyl = new cylinder[10];
				infile>>cyl[cylCnt].color.x>>cyl[cylCnt].color.y>>cyl[cylCnt].color.z;
				//infile>>cyl[cylCnt].emitColor.x>>cyl[cylCnt].emitColor.y>>cyl[cylCnt].emitColor.z;
				infile>>cyl[cylCnt].transp>>cyl[cylCnt].reflect;
				infile>>cyl[cylCnt].rad;
				infile>>cyl[cylCnt].height;
				infile>>cyl[cylCnt].center.x>>cyl[cylCnt].center.y>>cyl[cylCnt].center.z;
				cyl[cylCnt].emitColor=0;
				cylCnt++;
				break;
			case 2:
				if(coneCnt == 0)
					con = new cone[10];
				infile>>con[coneCnt].color.x>>con[coneCnt].color.y>>con[coneCnt].color.z;
				//infile>>con[coneCnt].emitColor.x>>con[coneCnt].emitColor.y>>con[coneCnt].emitColor.z;
				infile>>con[coneCnt].transp>>con[coneCnt].reflect;
				infile>>con[coneCnt].rad;
				infile>>con[coneCnt].height;
				infile>>con[coneCnt].center.x>>con[coneCnt].center.y>>con[coneCnt].center.z;
				con[coneCnt].emitColor=0;
				coneCnt++;
				break;
		}
	}
	infile>>lightSrcCnt;
	lightSrc = new int*[lightSrcCnt];
	for(int tmp=0; tmp<lightSrcCnt; tmp++)
	{
		lightSrc[tmp] = new int[3];
		infile>>lightSrc[tmp][0]>>lightSrc[tmp][1]>>lightSrc[tmp][2];
	}
	infile>>antiAlias;
	infile>>ambComp;
	infile>>depth;
}
double mix(const double a, const double b, const double mix)
{
	return b * mix + a * (1.0 - mix);
}
double max(double a, double b)
{
	return a>b?a:b;
}
vector render::rayTrace(vector rOrigin, vector rDir,camera cam,int argDepth)
{
	double int_point=1e8;
	sphere sphere_intersecting;
	cylinder cylinder_intersecting;
	cone cone_intersecting;
	int flag=0;
	vector norHit;
	vector sp_int_point;
	vector cyl_int_point;
	vector con_int_point;
	vector sp_normal;
	vector cyl_normal;
	vector con_normal;
	vector final_int_point;
	vector light_dir;
	vector temp_con_normal;
	vector temp_con_int_point;
	vector temp_cyl_int_point;
	vector temp_cyl_normal;
	for(int i=0;i<sphCnt;i++)// spherical objects
	{
		double int_point1=1e8,int_point2=1e8;
		bool p=sp[i].intersect(rOrigin,rDir,&int_point1,&int_point2);
		if (p)
		{
			if(int_point1<0)
				int_point1=int_point2;
			if(int_point1<int_point)
			{
				flag=1;
				int_point=int_point1;
				sphere_intersecting=sp[i];
				//cout<<int_point<<endl;
			}
		}
	}
	vector temp;
	temp.x=rDir.x*int_point;
	temp.y=rDir.y*int_point;
	temp.z=rDir.z*int_point;
	sp_int_point=rOrigin+temp;
	sp_normal=sp_int_point-sphere_intersecting.center;
	for(int i=0;i<cylCnt;i++)// cylindrical objects
	{
		double int_point1=1e8;
		bool p=cyl[i].intersect(rOrigin,rDir,&int_point1,&cyl_int_point,&cyl_normal);
		if (p)
		{
			if(int_point1<int_point)
			{
				flag=2;
				int_point=int_point1;
				cylinder_intersecting=cyl[i];
				temp_cyl_int_point=cyl_int_point;
				temp_cyl_normal=cyl_normal;
			}
		}
	}
	cyl_int_point=temp_cyl_int_point;
	cyl_normal=temp_cyl_normal;
	for(int i=0;i<coneCnt;i++)//Conical objects
	{
		double int_point1=1e8;
		bool p=con[i].intersect(rOrigin,rDir,&int_point1,&con_int_point,&con_normal);
		if (p)
		{
			if(int_point1<int_point)
			{
				flag=3;
				int_point=int_point1;
				cone_intersecting=con[i];
				temp_con_int_point=con_int_point;
				temp_con_normal=con_normal;
			}
		}
	}
	con_int_point=temp_con_int_point;
	con_normal=temp_con_normal;
	if(flag==0)
		return vector(1.0,1.0,1.0);
	if(flag==3)
	{
		norHit=con_normal;
		final_int_point=con_int_point;
	}
	else if(flag==2)
	{
		norHit=cyl_normal;
		final_int_point=cyl_int_point;
	}
	else if(flag==1 )
	{
		final_int_point=sp_int_point;
		norHit=sp_normal;
	}
	vector surfaceColor;
	vector ptHit = final_int_point;
	norHit.normalize();
	double bias = 1e-4; 
	bool ptIn = false;
	if (rDir.dot(norHit) > 0)
	{
		norHit = -norHit;
		ptIn = true;
	}
	switch(flag)
	{
		case 1:
			if ((sphere_intersecting.transp > 0 || sphere_intersecting.reflect > 0) && argDepth < depth)
			{
				double fRatio = -rDir.dot(norHit);
				double fresnel = mix(pow(1 - fRatio, 3), 1, 0.1);
				temp = norHit.mul(2);
				vector temp1= temp.mul(rDir.dot(norHit));
				vector reflDir = rDir - temp1;
				reflDir.normalize();
				temp= norHit.mul(bias);
				vector refl = rayTrace(ptHit + temp, reflDir, cam, argDepth + 1);
				vector refr;
				if (sphere_intersecting.transp)
				{
					double ior = 1.1, eta = (ptIn) ? ior : 1 / ior; 
					double cos = -norHit.dot(rDir);
					double k = 1 - eta * eta * (1 - cos * cos);
					temp = norHit .mul(eta *  cos - sqrt(k));
					vector refrDir = rDir.mul(eta) + temp;
					refrDir.normalize();
					temp  = norHit.mul(bias);
					refr = rayTrace(ptHit - temp, refrDir, cam, argDepth + 1);
				}
				temp = refr.mul( (1 - fresnel) *sphere_intersecting.transp);
				if(!(sphere_intersecting.transp))
					surfaceColor = (refl.mul(fRatio) + temp) * sphere_intersecting.color;
				else
					surfaceColor = (refl.mul(fresnel) + temp) * sphere_intersecting.color;
			}
			else
			{
				for(int i=0;i<lightSrcCnt;i++){
					light_src=vector(lightSrc[i][0],lightSrc[i][1],lightSrc[i][2]);
					vector lightDir = light_src - ptHit;
					lightDir.normalize();
					double trans=diffuse(lightDir,ptHit);
					vector temp1 = sphere_intersecting.color.mul(trans * max(0, norHit.dot(lightDir)));//* sp[i].emitColor; 
					surfaceColor = surfaceColor + temp1;
				}
			}			
			return surfaceColor+ sphere_intersecting.emitColor;
			break;
		case 2:
			if ((cylinder_intersecting.transp > 0 || cylinder_intersecting.reflect > 0) && argDepth < depth)
			{
				double fRatio = -rDir.dot(norHit);
				double fresnel = mix(pow(1 - fRatio, 3), 1, 0.1);
				temp = norHit.mul(2);
				vector temp1= temp.mul(rDir.dot(norHit));
				vector reflDir = rDir - temp1;
				reflDir.normalize();
				temp= norHit.mul(bias);
				vector refl = rayTrace(ptHit + temp, reflDir, cam, argDepth + 1);
				vector refr;
				if (cylinder_intersecting.transp)
				{
					double ior = 1.1, eta = (ptIn) ? ior : 1 / ior; // are we inside or outside the surface?
					double cos = -norHit.dot(rDir);
					double k = 1 - eta * eta * (1 - cos * cos);
					temp = norHit .mul(eta *  cos - sqrt(k));
					vector refrDir = rDir.mul(eta) + temp;
					refrDir.normalize();
					temp  = norHit.mul(bias);
					refr = rayTrace(ptHit - temp, refrDir, cam, argDepth + 1);
				}
				temp = refr.mul( (1 - fresnel) *cylinder_intersecting.transp);
				//cout<<refl<<endl;
				if(cylinder_intersecting.transp)
					surfaceColor = (refl.mul(fresnel) + temp) * cylinder_intersecting.color;
				else
					surfaceColor = (refl.mul(fRatio) + temp) * cylinder_intersecting.color;
			}
			else
			{
				for(int i=0;i<lightSrcCnt;i++){
					light_src=vector(lightSrc[i][0],lightSrc[i][1],lightSrc[i][2]);
					vector lightDir = light_src - ptHit;
					lightDir.normalize();
					double trans=diffuse(lightDir,ptHit);
					vector temp1 = cylinder_intersecting.color.mul(trans * max(0, norHit.dot(lightDir)));//* cyl[i].emitColor;
					surfaceColor = surfaceColor + temp1;
				}
			}
			return surfaceColor+ cylinder_intersecting.emitColor;
			break;
		case 3:
			if ((cone_intersecting.transp > 0 || cone_intersecting.reflect > 0) && argDepth < depth)
			{
				double fRatio = -rDir.dot(norHit);
				double fresnel = mix(pow(1 - fRatio, 3), 1, 0.1);
				temp = norHit.mul(2);
				vector temp1= temp.mul(rDir.dot(norHit));
				vector reflDir = rDir - temp1;
				reflDir.normalize();
				temp= norHit.mul(bias);
				vector refl = rayTrace(ptHit + temp, reflDir, cam, argDepth + 1);
				vector refr;
				if (cone_intersecting.transp)
				{
					double ior = 1.1, eta = (ptIn) ? ior : 1 / ior;
					double cos = -norHit.dot(rDir);
					double k = 1 - eta * eta * (1 - cos * cos);
					temp = norHit .mul(eta *  cos - sqrt(k));
					vector refrDir = rDir.mul(eta) + temp;
					refrDir.normalize();
					refr = rayTrace(ptHit - temp, refrDir, cam, argDepth + 1);
				}
				temp = refr.mul( (1 - fresnel) *cone_intersecting.transp);
				if (cone_intersecting.transp)
					surfaceColor = (refl.mul(fresnel) + temp) * cone_intersecting.color;
				else
					surfaceColor = (refl.mul(fRatio) + temp) * cone_intersecting.color;
			}
			else
			{
				for(int i=0;i<lightSrcCnt;i++){
					light_src=vector(lightSrc[i][0],lightSrc[i][1],lightSrc[i][2]);
					vector lightDir = light_src - ptHit;
					lightDir.normalize();
					double trans=diffuse(lightDir,ptHit);
					vector temp1 = cone_intersecting.color.mul(trans * max(0, norHit.dot(lightDir)));//* conel[i].emitColor;
					surfaceColor = surfaceColor + temp1;
				}
			}
			return surfaceColor+ cone_intersecting.emitColor;
			break;
		default:
			break;
	}
	return vector(0,0,0);
}
const unsigned long RAND_MAX_PLUS_1 = RAND_MAX + 1;
unsigned long bigRand()
{
	return rand() * (RAND_MAX_PLUS_1) + rand();
}
const unsigned long BIG_RAND_MAX = RAND_MAX_PLUS_1 * RAND_MAX_PLUS_1 - 1;
float rand0to1()
{
	return static_cast<float>(bigRand() ) / BIG_RAND_MAX;
}
void render::renderImage(camera cam)
{
	double angle = tan(3.14 * 0.5 * cam.fov / 180.0);
	vector *pixel=img;
	double aspectRatio=pw/ph;
	vector rOrigin(0,0,0);
	for(int i=0;i<ph;i++)
	{
		double y = (1-2*((i+0.5)/ph))*angle;
		for(int j=0;j<pw;j++)
		{
			double x=(2*((j+0.5)/pw)-1)*angle*aspectRatio;
			if(antiAlias) //4x supersampling
			{
				vector sum(0.0,0.0,0.0);
				for(int p=0;p<4;p++) 
				{
					for(int q=0;q<4;q++)
					{
						double xi = x + (p+0.5)/2000.0;
						double yi = y + (q+0.5)/2000.0;
						vector rDir(xi,yi,-1);
						rDir.normalize();
						vector tempray = rayTrace(rOrigin,rDir,cam,0);
						sum =sum+tempray;
					}
				}
				*img=sum/16.0;
			}
			else
			{
				vector rDir(x,y,-1);
				rDir.normalize();
				*img =rayTrace(rOrigin,rDir,cam,0);
			}
			img++;
		}
	}
	//cout<<"here"<<endl;
	/*for(int i=0;i<w*h;i++)
	  {
	  if(i==4436)
	  continue;
	  cout<<"pixel "<<i<<" x:"<<pixel[i].x<<" y:"<<pixel[i].y<<" z:"<<pixel[i].z<<endl;
	  }*/
	std::ofstream ofs("./untitled.ppm", std::ios::out | std::ios::binary);
	ofs << "P6\n" << w << " " << h << "\n255\n";
	for (int i = 0; i < w * h; ++i)
		ofs << (unsigned char)( pixel[i].x * 255) << (unsigned char)( pixel[i].y * 255) <<(unsigned char)( pixel[i].z * 255);
	ofs.close();
}
double render:: diffuse(vector lightDir,vector ptHit){
	double trans= 1.0;
	for (int j = 0; j < sphCnt; ++j)
	{
		if (sp[j].intersect(ptHit /*+ norHit * bias*/, lightDir))
		{
			trans = 0;
			return trans;
		}
	}
	if(trans)
	{
		for (int j = 0; j < cylCnt; ++j)
		{
			if (cyl[j].intersect(ptHit /*+ norHit * bias*/, lightDir))
			{
				trans = 0;
				return trans;
			}
		}
	}
	if(trans)
	{
		for (int j = 0; j < coneCnt; ++j)
		{
			if (con[j].intersect(ptHit /*+ norHit * bias*/, lightDir))
			{
				trans = 0;
				return trans;
			}
		}
	}
	return trans;
}
