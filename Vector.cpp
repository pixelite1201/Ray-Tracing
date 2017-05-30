#include "vector.h"
#include<cmath>
#include<fstream>

vector::vector(){
			x=0;
			y=0;
			z=0;
		}
vector::vector(double x,double y,double z){
				this->x=x;
				this->y=y;
				this->z=z;
			}
vector& vector::normalize()
			{
				if(sqrt_length()>0){
				double temp=1/sqrt_length();  //using this give correct but if we directly divide by sqrt_length incorrect
				x=x*temp;
				
				y=y*temp;
				z=z*temp;
				}
				return *this;
			}
double vector::length(){
				return x*x + y*y + z*z;
			}
double vector::sqrt_length(){
				return sqrt(length());
			}
vector vector:: operator + (vector &other){
				double temp_x=x+other.x;
				double temp_y=y+other.y;
				double temp_z=z+other.z;
				return vector(temp_x,temp_y,temp_z);
			}

vector vector:: operator - (vector &other){
				double temp_x=x-other.x;
				double temp_y=y-other.y;
				double temp_z=z-other.z;
				return vector(temp_x,temp_y,temp_z);
			}

vector vector:: operator * (vector &other){
				double temp_x=x*other.x;
				double temp_y=y*other.y;
				double temp_z=z*other.z;
				return vector(temp_x,temp_y,temp_z);
			}
vector vector:: operator * (double other){
				double temp_x=x*other;
				double temp_y=y*other;
				double temp_z=z*other;
				return vector(temp_x,temp_y,temp_z);
			}
vector vector:: operator -(){
				x=-x;
				y=-y;
				z=-z;
				return *this;
			}
double vector::dot ( vector &other){
				return (x*other.x+y*other.y+z*other.z);
			}




