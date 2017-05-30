#include "object.h"
#include <iostream>
bool sphere::intersect(vector &rOrigin,vector &rDir,double *int_point1,double *int_point2)
{
	vector L=center-rOrigin;
	static int i=0;
	double t= L.dot(rDir);
	if (t<0)
		return false;
	else
	{
		double d;
		d=sqrt(L.dot(L)-t*t);
		if(d>rad)
			return false;
		else
		{
			i++;
			double t_dash=sqrt(rad*rad-d*d);
			intersectionPt1=t-t_dash;
			intersectionPt2=t+t_dash;
			*int_point1=intersectionPt1;
			*int_point2=intersectionPt2;
			return true;
		}
	}
}
bool sphere::intersect(vector &rOrigin,vector &rDir)
{
	vector L=center-rOrigin;
	double t= L.dot(rDir);
	if (t<0)
		return false;
	else
	{
		double d;
		d=sqrt(L.dot(L)-t*t);
		if(d>rad)
			return false;
		else
		{
			return true;
		}
	}
}
bool cone::intersect(vector &origin,vector &ray_direction,double *length_int=NULL,vector *int_point=NULL,vector *con_normal=NULL){
	vector L=center-origin;
	double tmp1=L.dot(ray_direction);
	if(tmp1<0)
		return false;
	double a,b,c;
	double k=rad/(height);
	double origin_x2=origin.x*origin.x;
	double origin_y2=origin.y*origin.y;
	double origin_z2=origin.z*origin.z;
	double ray_direction_x2=ray_direction.x*ray_direction.x;
	double ray_direction_y2=ray_direction.y*ray_direction.y;
	double ray_direction_z2=ray_direction.z*ray_direction.z;
	double k2=k*k;
	a=ray_direction_x2+ray_direction_z2-k2*ray_direction_y2;
	b=2*(ray_direction.x*origin.x+ray_direction.z*origin.z-center.x*ray_direction.x-center.z*ray_direction.z-k2*origin.y*ray_direction.y+k2*center.y*ray_direction.y);
	c=origin_x2+origin_z2+center.x*center.x+center.z*center.z-2*center.x*origin.x-2*center.z*origin.z-k2*origin_y2-k2*center.y*center.y+2*k2*center.y*origin.y;
	double discriminant = (pow(b,2) - 4*a*c);
	if(discriminant>0)
	{
		double positive_root = (((-b) + sqrt(discriminant))/(2*a));
		double negative_root = (((-b) - sqrt(discriminant))/(2*a));
		vector int_point1;
		vector int_point2;
		int_point1.y=origin.y+ray_direction.y*positive_root;
		int_point2.y=origin.y+ray_direction.y*negative_root;
		if(abs(int_point2.y-center.y)<=height){
			if(int_point2.y-center.y<0)//reversing sign will make cone inverted
			{
				int_point2.x=origin.x+ray_direction.x*negative_root;
				int_point2.z=origin.z+ray_direction.z*negative_root;
				*length_int=int_point2.sqrt_length();  //assuming that ray_origin is always 0,0,0
				int_point=&int_point2;
				double normal_y=sqrt((int_point->x-center.x)*(int_point->x-center.x)+(int_point->z-center.z)*(int_point->z-center.z))*k;
				*con_normal=vector((int_point->x-center.x),normal_y,(int_point->z-center.z));
				return true;
			}
			else
				return false;
		}
		else if(abs(int_point1.y-center.y)<=height&&int_point1.y-center.y<0){
			double t=caps_intersetion(vector(0.0,-1.0,0.0),vector(center.x,center.y-height,center.z),rad,origin,ray_direction);
			int_point1.x=origin.x+ray_direction.x*t;
			int_point1.y=origin.y+ray_direction.y*t;
			int_point1.z=origin.z+ray_direction.z*t-center.z;
			*length_int=int_point1.sqrt_length();  //assuming that ray_origin is always 0,0,0
			int_point=&int_point1;
			*con_normal=vector(0,-1,0);
			return true;
		}
		else
			return false;
	}
	else
		return false;
}
bool cone::intersect(vector &origin,vector &ray_direction){
	vector L=center-origin;
	double tmp1=L.dot(ray_direction);
	if(tmp1<0)
		return false;
	double a,b,c;
	double k=rad/(height);
	double origin_x2=origin.x*origin.x;
	double origin_y2=origin.y*origin.y;
	double origin_z2=origin.z*origin.z;
	double ray_direction_x2=ray_direction.x*ray_direction.x;
	double ray_direction_y2=ray_direction.y*ray_direction.y;
	double ray_direction_z2=ray_direction.z*ray_direction.z;
	double k2=k*k;
	a=ray_direction_x2+ray_direction_z2-k2*ray_direction_y2;
	b=2*(ray_direction.x*origin.x+ray_direction.z*origin.z-center.x*ray_direction.x-center.z*ray_direction.z-k2*origin.y*ray_direction.y+k2*center.y*ray_direction.y);
	c=origin_x2+origin_z2+center.x*center.x+center.z*center.z-2*center.x*origin.x-2*center.z*origin.z-k2*origin_y2-k2*center.y*center.y+2*k2*center.y*origin.y;
	double discriminant = (pow(b,2) - 4*a*c);
	if(discriminant>0)
	{
		double positive_root = (((-b) + sqrt(discriminant))/(2*a));
		double negative_root = (((-b) - sqrt(discriminant))/(2*a));
		vector int_point1;
		vector int_point2;
		int_point1.y=origin.y+ray_direction.y*positive_root;
		int_point2.y=origin.y+ray_direction.y*negative_root;
		if(abs(int_point2.y-center.y)<=height){
			if(int_point2.y-center.y<0)//reversing sign will make cone inverted
			{
				return true;
			}
			else
				return false;
		}
		else if(abs(int_point1.y-center.y)<=height&&int_point1.y-center.y<0){
			return true;
		}
		else
			return false;
	}
	else
		return false;
}		
bool cylinder::intersect(vector &origin,vector &ray_direction,double *length_int=NULL,vector *int_point=NULL,vector *cyl_normal=NULL)
{
	vector L=center-origin;
	double tmp1=L.dot(ray_direction);
	if(tmp1<0)
		return false;
	double a,b,c;
	a=ray_direction.x*ray_direction.x+ray_direction.z*ray_direction.z;
	b=2*origin.x*ray_direction.x+2*origin.z*ray_direction.z-2*ray_direction.x*center.x-2*ray_direction.z*center.z;
	c=origin.x*origin.x+origin.z*origin.z-rad*rad-2*origin.x*center.x-2*origin.z*center.z+center.z*center.z+center.x*center.x;
	double discriminant = (pow(b,2) - 4*a*c);
	if(discriminant>0)
	{
		double positive_root = (((-b) + sqrt(discriminant))/(2*a));
		double negative_root = (((-b) - sqrt(discriminant))/(2*a));
		vector int_point1;
		vector int_point2;
		int_point2.y=origin.y+ray_direction.y*negative_root;
		int_point1.y=origin.y+ray_direction.y*positive_root;
		if(abs(int_point2.y-center.y)<height/2)
		{
			int_point2.x=origin.x+ray_direction.x*negative_root;
			int_point2.z=origin.z+ray_direction.z*negative_root;
			*length_int=int_point2.sqrt_length();  //assuming that ray_origin is always 0,0,0
			int_point=&int_point2;
			vector temp(int_point->x-center.x,0,int_point->z-center.z);
			*cyl_normal=temp;
			return true;
		}
		else if(abs(int_point1.y-center.y)<height/2){
			double t;
			if(int_point1.y-center.y>0){
				t=caps_intersetion(vector(0.0,1.0,0.0),vector(center.x,height+center.y,center.z),rad,origin,ray_direction);
				int_point1.x=origin.x+ray_direction.x*t;
				int_point1.y=origin.y+ray_direction.y*t;
				int_point1.z=origin.z+ray_direction.z*t-center.z;
				*length_int=int_point1.sqrt_length();  //assuming that ray_origin is always 0,0,0
				int_point=&int_point1;
				*cyl_normal=vector(0,1,0);
				return true;
			}
			else{
				t=caps_intersetion(vector(0.0,-1.0,0.0),vector(center.x,center.y-height,center.z),rad,origin,ray_direction);
				int_point1.x=origin.x+ray_direction.x*t;
				int_point1.y=origin.y+ray_direction.y*t;
				int_point1.z=origin.z+ray_direction.z*t-center.z; //don't know why
				*length_int=int_point1.sqrt_length();  //assuming that ray_origin is always 0,0,0
				int_point=&int_point1;
				*cyl_normal=vector(0,-1,0);
				return true;
			}
		}
		else
			return false;
	}
	else
		return false;
}
bool cylinder::intersect(vector &origin,vector &ray_direction)
{
	vector L=center-origin;
	double tmp1=L.dot(ray_direction);
	if(tmp1<0)
		return false;
	double a,b,c;
	a=ray_direction.x*ray_direction.x+ray_direction.z*ray_direction.z;
	b=2*origin.x*ray_direction.x+2*origin.z*ray_direction.z-2*ray_direction.x*center.x-2*ray_direction.z*center.z;
	c=origin.x*origin.x+origin.z*origin.z-rad*rad-2*origin.x*center.x-2*origin.z*center.z+center.z*center.z+center.x*center.x;
	double discriminant = (pow(b,2) - 4*a*c);
	if(discriminant>0)
	{
		double positive_root = (((-b) + sqrt(discriminant))/(2*a));
		double negative_root = (((-b) - sqrt(discriminant))/(2*a));
		vector int_point1;
		vector int_point2;
		int_point2.y=origin.y+ray_direction.y*negative_root;
		int_point1.y=origin.y+ray_direction.y*positive_root;
		if(abs(int_point2.y-center.y)<height/2)
			return true;
		else if(abs(int_point1.y-center.y)<height/2)
			return true;
		else
			return false;
	}
	else
		return false;
}
double caps_intersetion(vector n,vector point_plane,double rad,vector origin,vector ray_direction)
{
	double denom=n.dot(ray_direction);
	double d=0;
	if(denom> 1e-6){
		vector point_plane_origin=point_plane-origin;
		d=point_plane_origin.dot(n)/denom;
		return d;
	}
	else
		return 0.0;
}
