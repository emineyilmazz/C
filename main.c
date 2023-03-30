   /*
    * Main
    * Yazýlan fonksiyon kodlarýnýn test edildiði, çaðrýldýðý kodlarý içinde barýndýrmaktadýr.
    *  Birinci Proje
    * 10.12.2022
    * emine yilmaz  emine.yilmaz@stu.fsm.edu.tr
    */

#include <stdio.h>
#include <stdlib.h>
#include "matrixLib.h"


int main(void)
{
	float* vector = returnVector(5);
	float* vector2= returnVector(5);
	float** matrix = returnMatrix(5, 5);
	float** matrix2 = returnMatrix(6, 5);

	printf("\n-----------ilk vector---------\n");
	printVector(vector, 5);
	printf("\n-----------ilk matrix---------\n");
	printMatrix(matrix, 5, 5);
	
	
	printf("\nVector mean = %f\n", mean(vector, 5));
	printf("\nCorrelation = %f\n", correlation(vector, vector2, 5));
	printf("\nCovariance = %f\n", covariance(vector, vector2, 5));
	
	float** carpimMatrix = matrixMultiplication(matrix, matrix, 5, 5, 5, 5);
	float** carpimMatrix2 = matrixMultiplication(matrix, matrix2, 5, 5, 6, 5);
	
	printf("\n-----------carpim sonucu matrix---------\n");
	printMatrix(carpimMatrix, 5, 5);

	float** tranpose = matrixTranspose(matrix, 5, 5);
	
	printf("\n-----------transpose matrix---------\n");
	printMatrix(tranpose, 5, 5);
	
	printf("\n-----------row mean ---------\n");
	float* rowMeanResult = rowMeans(matrix, 5, 5);
	printVector(rowMeanResult, 5);
	
	printf("\n-----------column mean ---------\n");
	float* columnMeanResult = columnMeans(matrix, 5, 5);
	printVector(columnMeanResult, 5);
	
	freeMatrix(matrix, 5);
	freeMatrix(carpimMatrix, 5);
	freeMatrix(matrix2, 6);
	freeMatrix(tranpose, 5);

	int ex;
	printf("press for exit");
	scanf("%d", &ex);
	return 0;
}
