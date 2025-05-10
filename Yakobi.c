#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Метод Якоби
int Yakobi(int N, double** A, double* b, double* x, double eps) 
{
    double err[N], x0[N], maxx; //err - массив ошибок, x0 - предыдущее приближение, maxx - максимальная ошибка на текущей итерации
    int k = 0; //Счетчик итераций
    
    //Инициализация начального приближения нулями
    for (int i = 0; i < N; i++) {
        x0[i] = 0.0;
    }

    //Нормирование уравнений
    for (int i = 0; i < N; i++)
    {
        b[i] /= A[i][i]; //деление правой части
        for (int j = 0; j < N; j++)
        {
            if (i != j)
            {
                A[i][j] /= A[i][i]; //деление недиагональных элементов
            }
        }
        A[i][i] /= A[i][i];
    }
    
    //Основной итерационный процесс
    do
    {
        maxx = 0;
        
        //Вычисление нового приближения по методу Якоби
        for (int i = 0; i < N; i++)
        {
            x[i] = b[i];
            
            for (int j = 0; j < i; j++)
            {
                if (i != j)
                {
                    x[i] -= A[i][j] * x[j];
                }
            }
            
            for (int j = i; j < N; j++)
            {
                if (i != j)
                {
                    x[i] -= A[i][j] * x0[j];
                }
            }
        }
        
        //Вычисление ошибки
        for (int i = 0; i < N; i++)
        {
            err[i] = fabs(x[i] - x0[i]);
            if (maxx < err[i])
            {
                maxx = err[i];
            }
        }
        
        //Проверка условия выхода
        if (maxx < eps) break;
        
        //Сохраняем текущее приближение для следующей итерации
        for (int i = 0; i < N; i++)
        {
            x0[i] = x[i];
        }
        
        k++; //Увеличиваем счетчик итераций
        
    } while (k <= 300);
    
    return k;
}
