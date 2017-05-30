/* Contains object specifications */
#include <cmath>
//#include "vector.h"
//#include "matrix.h"
#include "camera.h"

#define PI 3.14

//class matrix_t;
//class vector;
//class camera;
 
class object
{
	public:
		vector color;
		vector emitColor;
		float trans[3];
		float scale[3];
		float rot[3];
		int loc[3];
		double transp,reflect;
		double intersectionPt1,intersectionPt2;
		
		/*matrix_t o2w(4,4);
		
		void setO2W()
		{
			scale[0]>0?o2w[0][0] = scale[0]:o2w[0][0] = 1; //scaling
			scale[1]>0?o2w[1][1] = scale[1]:o2w[1][1] = 1
			scale[2]>0?o2w[2][2] = scale[2]:o2w[2][2] = 1
			o2w[3][3] = 1;
			//o2w[0][1] = cos(rot[0]*PI/180.0

			o2w[0][3] = trans[0];
			o2w[1][3] = trans[1];
			o2w[2][3] = trarns[2];
		}*/
};
double caps_intersetion(vector n,vector point_plane,double rad,vector origin,vector ray_direction);
class sphere: public object
{
	public:
		float rad;
		vector center;
		
		bool intersect(vector &origin,vector &ray_direction,double *int_point1,double *int_point2);
		bool intersect(vector &rOrigin,vector &rDir);
};

class cone: public object
{
	public:
		double rad, height;
		vector center;
		bool intersect(vector &origin,vector &ray_direction,double *length_int,vector *int_point,vector *con_normal);
		bool intersect(vector &origin,vector &ray_direction);
};

class cylinder: public object
{
	public:
		float rad,height;
		vector center;
		bool intersect(vector &origin,vector &ray_direction,double *length_int,vector *int_point,vector *cyl_normal);
		bool intersect(vector &origin,vector &ray_direction);
};
