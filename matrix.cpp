#include "matrix.h"
#include <stdlib.h>


matrix_t::matrix_t(int nrow,int ncol)
 {
				row = nrow;
				col = ncol;
				matrix = new  float *[row];
				for(int i=0 ; i<row ; i++)
				matrix[i] = new float[col];
				
				for(int i=0;i<row;i++)
					for(int j=0;j<col;j++)
						if(i == j)
							matrix[i][j] = 1;
						else
							matrix[i][j] = 0;
}

void matrix_t::matcopy(matrix_t mat1,matrix_t& mat2)
{
	for(int i=0;i<mat1.row;i++)
		for(int j=0 ; j<mat1.col ; j++)
			mat2.matrix[i][j]=mat1.matrix[i][j];
}
float matrix_t::getDetAndCof(matrix_t mat1, matrix_t &cof)
{

	float det = 0.0;


	 if(mat1.row ==2)
	{
		det = mat1.matrix[0][0] * mat1.matrix[1][1] - mat1.matrix[1][0] * mat1.matrix[0][1];
		cof.matrix[0][0]= mat1.matrix[1][1];
		cof.matrix[0][1] = -1 * mat1.matrix[1][0];
		cof.matrix[1][0] = -1 * mat1.matrix[0][1];
		cof.matrix[1][1]= mat1.matrix[0][0];

		}
	else
	{

		for(int i = 0; i< mat1.row; i++)
			{ for(int j = 0; j< mat1.col; j++)
				{matrix_t temp(mat1.row -1 ,mat1.col-1 );
				int n,m=0;
				for(int k= 0; k < mat1.row ; k++)
				{
					if(i != k)

					{n=0;
						for(int l = 0; l<mat1.col ; l++)
						{

							if( j!=l)

							{
								temp.matrix[m][n]=mat1.matrix[k][l];
								n++;
								}
							}
							m++;
						}
				}
				matrix_t matr1(mat1.row-1, mat1.col-1),matr2(mat1.row-1, mat1.col-1);

				matcopy(temp, matr1);
				float sign;
				if((i+j)%2==0)
						sign = 1.0;
				else
					sign = -1.0;
				cof.matrix[i][j] = sign * getDetAndCof(matr1, matr2);
				if (i == 0)
					det = det + cof.matrix[i][j];
				}
	}

}
return det;
}

matrix_t matrix_t::matrix_tMul(matrix_t mat1,matrix_t mat2)
{
	float sum=0;
	matrix_t prod(mat1.row,mat2.col);


	for(int i=0 ; i<mat1.row ; i++)
		for(int j=0 ; j<mat1.col ; j++)
		{
			sum=0;
			for(int k=0 ; k<mat1.col ; k++)
				sum=sum+mat1.matrix[i][k] * mat2.matrix[k][j];
			prod.matrix[i][j] = sum;
	}

	return prod;
}


matrix_t matrix_t::identity(int dim)
{
	matrix_t id(dim,dim);

	for(int i=0 ; i<id.row ; i++)
		for(int j=0 ; j<id.col ; j++)
		{
			if(i == j)
				id.matrix[i][j] = 1;
			else
				id.matrix[i][j] = 0;
		}

	return id;
}

bool matrix_t::invert(matrix_t mat1,matrix_t& mat2)
{
    float det;
    matrix_t cofmat(mat1.row, mat1.col);
    det = getDetAndCof(mat1,cofmat);
    if (det == 0)
        return false;
    det = 1.0 / det;
    mat1 = transpose(cofmat);
    for(int i = 0 ; i < mat1.row ; i++)
    {
    	for(int j = 0 ; j < mat1.col ; j++)
    	{
    		mat2.matrix[i][j] = det * mat1.matrix[i][j];
    	}
	}
    return true;
}

void matrix_t::swap(float &x, float &y)    /*Swaps two variables */
{
  	int temp = x;
  	x = y;
	y = temp;
}

matrix_t matrix_t::transpose(matrix_t m)
{
	matrix_t temp(m.row,m.col);

	matcopy(m,temp);

	for(int i=0 ; i<m.row ; i++)
		for(int j=0 ; j<m.col ; j++)
				m.matrix[i][j] = temp.matrix[j][i];

	return m;

}


matrix_t::~matrix_t() {
	
}
