#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Функция обмена двух строк матрицы
void swap_rows(double *row1, double *row2, int size) 
{
    for (int i = 0; i < size; i++) 
    {
        double temp = row1[i];
        row1[i] = row2[i];
        row2[i] = temp;
    }
}

//Функция обмена двух значений типа double
void swap_floats(double *a, double *b) 
{
    double temp = *a;
    *a = *b;
    *b = temp;
}

//Функция решения СЛАУ методом Жордана-Гаусса
int Joga(double** A, double* b, double* x, int m, int n)
{
    double d;       //Множитель для обнуления
    int flag = 0;   //Флаг для отслеживания перестановок строк
    float maximal;  //Максимальный элемент в строке
    int i0;         //Индекс строки с максимальным элементом

    //Прямой ход метода Гаусса - приведение к верхнетреугольному виду
    for (int i = 0; i < (m < n ? m : n); i++)
    {
        //Поиск максимального элемента в текущем столбце (выбор главного элемента)
        maximal = A[i][i];
        for (int j = i; j < m; j++)
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
            swap_rows(A[i], A[i0], n);
            swap_floats(&b[i], &b[i0]);
            flag = 0;
        }
        
        //Обнуление элементов под текущим диагональным элементом
        for (int j = i; j < m-1; j++)
        {
            d = A[j+1][i]/A[i][i];
            A[j+1][i] = A[j+1][i] - A[i][i] * d;//Обнуление элемента
            b[j+1] = b[j+1] - b[i] * d;        //Корректировка вектора b
            
            //Корректировка остальных элементов строки
            for (int u = i+1; u < n; u++)
            {
                A[j+1][u] = A[j+1][u] - A[i][u] * d;
            }
        }
    }
    
    //Обратный ход и приведение к диагональному виду
    for (int i = (m < n ? m : n) - 1; i > 0; i--)
    {
        for (int j = i - 1; j >= 0; j--)
        {
            d = A[j][i]/A[i][i];
            A[j][i] = A[j][i] - A[i][i] * d;
            b[j] = b[j] - b[i] * d;
        }
    }
    
    // Анализ системы на совместность и нахождение решения
    if (m < n && b[m-1] == 0)
    {
        return 2;  //Бесконечно много решений
    }
    else if (m < n && b[m-1] != 0)
    {
        return 0;  //Нет решений
    }
    else
    {
        for (int i = 0; i < (m < n ? m : n); i++)
        {
            x[i] = b[i] / A[i][i];  //Решение диагональной системы
        }
        return 1;  //Единственное решение
    }
}
