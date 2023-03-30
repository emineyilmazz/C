/*
    * MatrixLib.c  
    * Bu dosyanýn içerisinde fonksiyonlarýn kendisi bulunmaktadýr.
    *  Birinci Proje
    * 10.12.2022
    * emine yilmaz  emine.yilmaz@stu.fsm.edu.tr
*/
    
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrixLib.h"

#define MAXRAND 10


float *returnVector(int size){
	float *vector = (float*) malloc(size * sizeof(float));
	int seed;
	printf("proje 1 ");
    scanf("%d", &seed);
	srand(seed); // seed numarasýný veriyoruz.

	for(int i = 0; i < size; i++){
		*(vector + i) = rand() % MAXRAND; // 0 ile 10 arasýnda deðerler ile vectoru dolduruyoruz.
	}
	
	return vector;
}

float **returnMatrix(int row, int col){
	float **matrix = (float**) malloc(row * sizeof(float*));
	for (int i = 0; i < row; i++){
        matrix[i] = (float*)malloc(col * sizeof(float));
    }    
    
	int seed;
	printf("proje 1 ");
    scanf("%d", &seed);
	srand(seed);
	
    for (int i = 0; i < row; i++)
    { 
	    for (int j = 0; j < col; j++)
	    {
	        matrix[i][j] = rand() % MAXRAND;
	    }
	}
	
	return matrix;
}

void freeMatrix(float **mat, int row){
	for (int i = 0; i < row; i++)
		free(mat[i]);
 
	free(mat);
	
	printf("Hafizadan silindi.\n");
}

float mean(float *vec, int size){
	float sum = 0;
	
	for (int i = 0; i < size; i++){
		sum += vec[i];
	}
	
	return sum / size;
}

float correlation(float *vec, float *vec2, int size){ // vektörlerin arasýndaki cosinüsü alýcaz A.B / |A|.|B|
	float sum = 0;
	float lengthA = 0;
	float lengthB = 0;
	
	for(int i = 0; i < size; i++){
		sum += vec[i] * vec2[i]; // vektörlerin deðerlerini birbirleriyle çarpýp topluyoruz.
		lengthA += vec[i] * vec[i]; // ilk vektörün kareleri toplamýnýn karekökünü alýcaz.
		lengthB += vec2[i] * vec2[i]; // ikincisi içinde ayný.
	}
	
	lengthA = sqrt(lengthA);
	lengthB = sqrt(lengthB);
	
	return (float) sum / (lengthA * lengthB); // toplanan deðerleri vektörlerin uzunluklarý çarpýmýna bölüyoruz.
}

float covariance(float *vec1, float *vec2, int size){ // iki vektöründe kendi içinde her deðeri için kendi ortalamasýndan çýkarýp iki vektör ile çarpýpý toplayarak ilerleyip size'e bölerek bulabiliriz.
	float vec1Mean = mean(vec1, size); //yazdýmýz fonksiyonu kullanarak ortlamayý direk çaðýrýyoruz
	float vec2Mean = mean(vec2, size);
	float result = 0;
	
	for(int i = 0; i < size; i++){
		result += (vec1[i] - vec1Mean) * (vec2[i] - vec2Mean);
	}
	
	return result / size;
}

float **matrixMultiplication(float **mat1, float **mat2, int row1, int col1, int row2, int col2){
	if (col1 == row2) { // ilk matrisin kolon sayýsý ikinci matrisin satýr sayýsýna eþit olmalý.
        float **resultMatrix = returnMatrix(row1, col2); // sonucu yazacaðýmýz matris.
		
		for (int i = 0; i < row1; i++) {
			for (int j = 0; j < col2; j++) {
				for (int k = 0; k < col1; k++) { // birinci matris için sütun deðiþtiri ilincisi için satýr deðiþtirir 
					resultMatrix[i][j] += mat1[i][k] * mat2[k][j];  // matrisin bulunduðumuz satýr ve sütununa ilk matrisin sütunundaki sayýlar ikinci matrisin satýrýndaki sayýlarý dönerek çarpýp birbiri ile toplayarak gerçekleþtiriyoruz. 
				}
			}

		}
		return resultMatrix;
	} else {
		printf("Matrix carpim kuralina uymuyor.\n");
		return mat1;
	}
}

float **matrixTranspose(float **mat, int row, int col){
	float** transpose = returnMatrix(row, col); // transpoz matrisini oluþturmak için matrix oluþturuyoruz.
	
	for (int i = 0; i < row; i++){
		for (int j = 0; j < col; j++) {
			transpose[j][i] = mat[i][j]; 
		}
	}
	
	return transpose;
}

float *rowMeans(float **mat, int row, int col){
	float *rowMeans = returnVector(row); // her satýrýn ortalamasýný tutacaðý için size'ý row sayýsý kadar olan vectör oluþturuyoruz.
	
	for (int i = 0; i < row; i++){
		rowMeans[i] = mean(mat[i], col); // her satýr için mean fonksiyonumuzu çaðýrýp vektörümüzün ilgili indexine ekliyoruz.
	}
	
	return rowMeans;
}

float *columnMeans(float **mat, int row, int col){
	float *colMeans = returnVector(col); // her sütunun ortalamasýný tutacaðý için size'ý col sayýsý kadar olan vectör oluþturuyoruz.
	
	float** transpose = matrixTranspose(mat, row, col); // Sütunlarýn ortalamasýný alacaðýmýz için matrixin transpozunu alup bu matrisin satýrlarýnýn ortalamasýný alýrýz.
	
	for (int i = 0; i < row; i++){
		colMeans[i] = mean(transpose[i], col); // her satýr için mean fonksiyonumuzu çaðýrýp vektörümüzün ilgili indexine ekliyoruz.
	}
	
	return colMeans;
}



void printVector(float *vec, int N){

	for(int i = 0; i < N; i++){
		printf("%f ", *(vec+i));
	}
	
	printf("\n");        
}

void printMatrix(float **mat, int row, int col){
    for (int i = 0; i < row; i++)
    {
	    for (int j = 0; j < col; j++)
	    {
	        printf("%f ", mat[i][j]);
	    }
	    
	    printf("\n");
	}
}


