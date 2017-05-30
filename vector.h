class vector{
	public:
		double x,y,z;
		vector();
		vector(double x,double y,double z);
		vector& normalize();
		double length();
		double sqrt_length();
		vector operator + (vector &other);
		vector operator - (vector &other);
		vector operator * (vector &other);
		vector operator * (double other);
		vector operator -();
		double dot ( vector &other);
		vector operator =(double a);
		

};

