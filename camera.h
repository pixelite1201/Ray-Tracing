/*Contains camera specifications and light source details*/

#include <cmath>
#include <ostream>

class matrix_t;

using namespace std;

class vector{
	public:
		double x,y,z;
		vector(){
			x=0;
			y=0;
			z=0;
		}
			vector(double x,double y,double z){
				this->x=x;
				this->y=y;
				this->z=z;
			}
			vector& normalize()
			{
				if(sqrt_length()>0){
				x=x/sqrt_length();
				y=y/sqrt_length();
				z=z/sqrt_length();
				}
				return *this;
			}
			double length(){
				return x*x + y*y + z*z;
			}
			double sqrt_length(){
				return sqrt(length());
			}
			vector operator + (vector &other){
				double temp_x=x+other.x;
				double temp_y=y+other.y;
				double temp_z=z+other.z;
				return vector(temp_x,temp_y,temp_z);
			}
			
			vector operator - (vector &other){
				double temp_x=x-other.x;
				double temp_y=y-other.y;
				double temp_z=z-other.z;
				return vector(temp_x,temp_y,temp_z);
			}
			vector operator - (double other){
				double temp_x=x-other;
				double temp_y=y-other;
				double temp_z=z-other;
				return vector(temp_x,temp_y,temp_z);
			}
			vector operator * (vector &other){
				double temp_x=x*other.x;
				double temp_y=y*other.y;
				double temp_z=z*other.z;
				return vector(temp_x,temp_y,temp_z);
			}
			
			vector operator / (double other){
				double temp_x, temp_y, temp_z;
				if(other > 0.0)
				{
					 temp_x=x/other;
					 temp_y=y/other;
					 temp_z=z/other;
				}
				return vector(temp_x,temp_y,temp_z);
			}
			
			bool operator == (vector &other){
					return (x==other.x && y==other.y && z==other.z);
			}
			
			vector  mul(double other){
				double temp_x=x*other;
				double temp_y=y*other;
				double temp_z=z*other;
				return vector(temp_x,temp_y,temp_z);
			}
			
			vector operator -(){
				x=-x;
				y=-y;
				z=-z;
				return *this;
			}
			double dot ( vector &other){
				return (x*other.x+y*other.y+z*other.z);
			}
			vector operator =(double a){
				x=a;
				y=a;
				z=a;
				
				return *this;
			}
			friend ostream & operator << (ostream & os, vector &other){
				os<<"["<<other.x<<" "<<other.y<<" "<<other.z<<"]"<<endl;
				return os;
			}
			

};

class ray{
	public:
		vector origin;
		vector end_point;
};


class camera
{
	public:
		int near, far;
		float fov;
		int lat[3],vup[3];
		vector cop;
		//matrix_t w2c(4,4), c2w(4,4);
};	
		

