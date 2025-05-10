#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Алгоритм Штрассена для умножения матриц
void Strassen(double** A, double** B, double** C, int N1, int ind1, int ind2) {
    //Проходим по блокам матриц
    for (int k = 0; k < N1; k += 2) {
        //Вычисляем промежуточные значения для матричного умножения
        double D = (A[ind1][k] + A[1 + ind1][k + 1]) * (B[k][ind2] + B[k + 1][1 + ind2]);
        double D1 = (A[ind1][1 + k] - A[1 + ind1][1 + k]) * (B[1 + k][ind2] + B[1 + k][1 + ind2]);
        double D2 = (A[1 + ind1][k] - A[ind1][k]) * (B[k][ind2] + B[k][1 + ind2]);
        double H1 = (A[ind1][k] + A[ind1][1 + k]) * B[1 + k][1 + ind2];
        double H2 = (A[1 + ind1][k] + A[1 + ind1][1 + k]) * B[k][ind2];
        double V1 = A[1 + ind1][1 + k] * (B[1 + k][ind2] - B[k][ind2]);
        double V2 = A[ind1][k] * (B[k][1 + ind2] - B[1 + k][1 + ind2]);

        //Обновляем значения в результирующей матрице C
        C[ind1][ind2] += D + D1 + V1 - H1;
		C[ind1][1+ind2] += V2 + H1;
		C[1+ind1][ind2] += V1 + H2;
		C[1+ind1][1+ind2] += D + D2 + V2 - H2;
    }
}

//Функция для выбора блоков и вызова алгоритма Штрассена
int SelStrassen(double*** A, double*** B, double*** C, int N) 
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
    for (int i = 0; i < N; i += 2) 
    {
        for (int j = 0; j < N; j += 2) 
        {
            Strassen(*A, *B, *C, N, i, j);
        }
    }
    return N1;
}
