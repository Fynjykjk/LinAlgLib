#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Функция обмена двух строк матрицы
void swap_rows(double* row1, double* row2, int size) {
    for (int i = 0; i < size; i++) {
        double temp = row1[i];
        row1[i] = row2[i];
        row2[i] = temp;
    }
}

//Функция вычисления определителя
void DetDef(double** A, double* det, int N)
{
    float d;          //Множитель для обнуления
    float maximal;    //Максимальный элемент в строке
    int flag = 0;     //Флаг для отслеживания перестановок строк
    int i0;           //Индекс строки с максимальным элементом
    
    //Приведение матрицы к ступенчатому виду
    for (int i = 0; i < N; i++)
    {
        //Поиск максимального элемента в строке
        maximal = A[i][i];
        for (int j = i; j < N; j++)
        {
            if (fabs(maximal) < fabs(A[j][i]))
            {
                flag = 1;
                maximal = A[j][i];
                i0 = j;
            }
        }
        
        //Если найден больший элемент, меняем строки местами
        if (flag == 1)
        {
            swap_rows(A[i], A[i0], N);
            *det *= -1;                 //При перестановке строк определитель меняет знак
            flag = 0;
        }
        
        //Умножение определителя на диагональный элемент
        *det *= A[i][i];
        
        //Обнуление элементов под текущим диагональным элементом
        for (int j = i; j < N-1; j++)
        {
            d = A[j+1][i]/A[i][i];
            A[j+1][i] = A[j+1][i] - A[i][i] * d;
            
            //Корректировка остальных элементов строки
            for (int u = i+1; u < N; u++)
            {
                A[j+1][u] = A[j+1][u] - A[i][u] * d;
            }
        }
    }
}
