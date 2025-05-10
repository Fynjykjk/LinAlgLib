#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Функция для вычисления скалярного произведения
double scal(double* x, double* y, int N)
{
    double n = 0;
    for (int i = 0; i < N; i++)
    {
        n += x[i] * y[i];
    }
    return n;
}

//Метод сопряженных градиентов
int Gradient(int N, double** A, double* b, double* x, double eps) 
{
    //Альфа и бетта
    double alpha = 0., betta = 0.;
    
    double* x0 = (double*)calloc(N, sizeof(double)); //Предыдущее приближение решения
    double* r0 = (double*)malloc(N * sizeof(double)); //Невязка на предыдущем шаге
    double* z0 = (double*)malloc(N * sizeof(double)); //Направление поиска на предыдущем шаге
    double* r = (double*)calloc(N, sizeof(double)); //Текущая невязка
    double* z = (double*)calloc(N, sizeof(double)); //Текущее направление поиска
    double* temp = (double*)calloc(N, sizeof(double)); //Временный вектор для вычислений

    // Инициализация начальных значений
    for (int i = 0; i < N; i++) 
    {
        r0[i] = b[i];
        z0[i] = r0[i];
    }

    int k = 0; // Счетчик итераций

    // Основной итерационный процесс
    do
    {
        //Вычисление alpha:
        //temp = A * z0 (матрично-векторное произведение)
        for (int i = 0; i < N; i++)
        {
            temp[i] = 0;
            for (int j = 0; j < N; j++)
            {
                temp[i] += A[i][j] * z0[j];
            }
        }
        //alpha = (r0, r0) / (A*z0, z0)
        alpha = scal(r0, r0, N) / scal(temp, z0, N);

        //Обновление решения и невязки:
        for (int i = 0; i < N; i++)
        {
            x[i] = x0[i] + alpha * z0[i];
            r[i] = r0[i] - alpha * temp[i];
        }

        //Вычисление betta:
        //betta = (r, r) / (r0, r0)
        betta = scal(r, r, N) / scal(r0, r0, N);

        //Обновление направления поиска:
        for (int i = 0; i < N; i++)
        {
            z[i] = r[i] + betta * z0[i];
        }

        //||r|| / ||b|| < eps (относительная невязка)
        if ((sqrt(scal(r, r, N))) / (sqrt(scal(b, b, N))) < eps) break;

        //Подготовка к следующей итерации:
        for (int i = 0; i < N; i++)
        {
            x0[i] = x[i];
            z0[i] = z[i];
            r0[i] = r[i];
        }

        k++;
    } while (k <= 300);

    //Освобождение памяти
    free(r);
    free(z);
    free(r0);
    free(z0);
    free(x0);
    free(temp);

    return k; //Возвращаем количество итераций
}
