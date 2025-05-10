#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define BLOCK_SIZE 2 // Размер блока для блочной матричной умножения

//Функция для вычисления блока матричного произведения
void matit (double** A, double** B, double** C, int m1, int m2, int n1, int n2, int ind1, int ind2) 
{
    //Проходим по строкам блока A
    for (int i = ind1; i < m1 + ind1; i++) 
    {
        //Проходим по столбцам блока B
        for (int j = ind2; j < n2 + ind2; j++) 
        {
            //Умножаем строки A на столбцы B и суммируем результат в C
            for (int k = 0; k < m2; k++) 
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

//Функция для выбора блоков и вызова функции матричного умножения
int SelBlock(double*** A, double*** B, double*** C, int N) 
{
	int N1, k = 0;
	//Нахождение нового размера матриц - ближайшей степени двойки
    if (N == 1) N1 = 2;
    else 
    {
        while (pow(2, k) < N) k++; //Находим степень двойки больше или равную N
        N1 = pow(2, k);
    }
	
    //Перераспределение памяти для матриц до нового размера
    if (N != N1)
    {
        *A = (double**)realloc(*A, N1 * sizeof(double*));
        for (int i = 0; i < N1; i++) 
            (*A)[i] = (double*)realloc((*A)[i], N1 * sizeof(double));

        *B = (double**)realloc(*B, N1 * sizeof(double*));
        for (int i = 0; i < N1; i++) 
            (*B)[i] = (double*)realloc((*B)[i], N1 * sizeof(double));

        *C = (double**)realloc(*C, N1 * sizeof(double*));
        for (int i = 0; i < N1; i++) 
            (*C)[i] = (double*)realloc((*C)[i], N1 * sizeof(double));
    }
    
    //Проходим по всем блокам матриц
    for (int i = 0; i < N1; i += BLOCK_SIZE) 
    {
        for (int j = 0; j < N1; j += BLOCK_SIZE) 
        {
            //Вызываем функцию для вычисления текущего блока
            matit(*A, *B, *C, BLOCK_SIZE, N1, N1, BLOCK_SIZE, i, j);
        }
    }
    return N1;
}
