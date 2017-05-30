

class matrix_t
{
public:
	float** matrix;
	int row,col;
	matrix_t(int nrow,int ncol);
	void matcopy(matrix_t mat1, matrix_t& mat2);
	float getDetAndCof(matrix_t mat1, matrix_t &cof);
	matrix_t  matrix_tMul(matrix_t mat1,matrix_t mat2);
	matrix_t identity(int dim);
	bool invert(matrix_t mat1, matrix_t& mat2);
	matrix_t transpose(matrix_t mat);
	void swap(float &x, float &y);

	virtual ~matrix_t();
};


