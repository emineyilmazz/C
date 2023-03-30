/*
    * MatrixLib.c  
    * Bu dosyan�n i�erisinde fonksiyonlar�n kendisi bulunmaktad�r.
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
	srand(seed); // seed numaras�n� veriyoruz.

	for(int i = 0; i < size; i++){
		*(vector + i) = rand() % MAXRAND; // 0 ile 10 aras�nda de�erler ile vectoru dolduruyoruz.
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

float correlation(float *vec, float *vec2, int size){ // vekt�rlerin aras�ndaki cosin�s� al�caz A.B / |A|.|B|
	float sum = 0;
	float lengthA = 0;
	float lengthB = 0;
	
	for(int i = 0; i < size; i++){
		sum += vec[i] * vec2[i]; // vekt�rlerin de�erlerini birbirleriyle �arp�p topluyoruz.
		lengthA += vec[i] * vec[i]; // ilk vekt�r�n kareleri toplam�n�n karek�k�n� al�caz.
		lengthB += vec2[i] * vec2[i]; // ikincisi i�inde ayn�.
	}
	
	lengthA = sqrt(lengthA);
	lengthB = sqrt(lengthB);
	
	return (float) sum / (lengthA * lengthB); // toplanan de�erleri vekt�rlerin uzunluklar� �arp�m�na b�l�yoruz.
}

float covariance(float *vec1, float *vec2, int size){ // iki vekt�r�nde kendi i�inde her de�eri i�in kendi ortalamas�ndan ��kar�p iki vekt�r ile �arp�p� toplayarak ilerleyip size'e b�lerek bulabiliriz.
	float vec1Mean = mean(vec1, size); //yazd�m�z fonksiyonu kullanarak ortlamay� direk �a��r�yoruz
	float vec2Mean = mean(vec2, size);
	float result = 0;
	
	for(int i = 0; i < size; i++){
		result += (vec1[i] - vec1Mean) * (vec2[i] - vec2Mean);
	}
	
	return result / size;
}

float **matrixMultiplication(float **mat1, float **mat2, int row1, int col1, int row2, int col2){
	if (col1 == row2) { // ilk matrisin kolon say�s� ikinci matrisin sat�r say�s�na e�it olmal�.
        float **resultMatrix = returnMatrix(row1, col2); // sonucu yazaca��m�z matris.
		
		for (int i = 0; i < row1; i++) {
			for (int j = 0; j < col2; j++) {
				for (int k = 0; k < col1; k++) { // birinci matris i�in s�tun de�i�tiri ilincisi i�in sat�r de�i�tirir 
					resultMatrix[i][j] += mat1[i][k] * mat2[k][j];  // matrisin bulundu�umuz sat�r ve s�tununa ilk matrisin s�tunundaki say�lar ikinci matrisin sat�r�ndaki say�lar� d�nerek �arp�p birbiri ile toplayarak ger�ekle�tiriyoruz. 
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
	float** transpose = returnMatrix(row, col); // transpoz matrisini olu�turmak i�in matrix olu�turuyoruz.
	
	for (int i = 0; i < row; i++){
		for (int j = 0; j < col; j++) {
			transpose[j][i] = mat[i][j]; 
		}
	}
	
	return transpose;
}

float *rowMeans(float **mat, int row, int col){
	float *rowMeans = returnVector(row); // her sat�r�n ortalamas�n� tutaca�� i�in size'� row say�s� kadar olan vect�r olu�turuyoruz.
	
	for (int i = 0; i < row; i++){
		rowMeans[i] = mean(mat[i], col); // her sat�r i�in mean fonksiyonumuzu �a��r�p vekt�r�m�z�n ilgili indexine ekliyoruz.
	}
	
	return rowMeans;
}

float *columnMeans(float **mat, int row, int col){
	float *colMeans = returnVector(col); // her s�tunun ortalamas�n� tutaca�� i�in size'� col say�s� kadar olan vect�r olu�turuyoruz.
	
	float** transpose = matrixTranspose(mat, row, col); // S�tunlar�n ortalamas�n� alaca��m�z i�in matrixin transpozunu alup bu matrisin sat�rlar�n�n ortalamas�n� al�r�z.
	
	for (int i = 0; i < row; i++){
		colMeans[i] = mean(transpose[i], col); // her sat�r i�in mean fonksiyonumuzu �a��r�p vekt�r�m�z�n ilgili indexine ekliyoruz.
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


