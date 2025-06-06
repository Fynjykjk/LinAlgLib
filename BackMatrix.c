#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Алгоритм нахождения обратной матрицы
void Back(double** A, double** b, int N) {
    float d;         //Коэффициент для элементарных преобразований
    int flag = 0;    //Флаг перестановки строк
    float maximal;   //Максимальный элемент в столбце
    int i0;          //Индекс строки с максимальным элементом

    //Приведение матрицы к ступенчатому виду
    for (int i = 0; i < N; i++) {
        //Поиск максимального элемента в строке
        maximal = A[i][i];
        for (int j = i; j < N; j++) {
            if (fabs(maximal) < fabs(A[j][i])) {
                flag = 1;
                maximal = A[j][i];
                i0 = j;
            }
        }
        
        // Перестановка строк, если найден больший элемент
        if (flag == 1) {
            for (int k = 0; k < N; k++) {
                //Обмен строк в матрице A
                float temp = A[i][k];
                A[i][k] = A[i0][k];
                A[i0][k] = temp;

                //Обмен строк в матрице b
                temp = b[i][k];
                b[i][k] = b[i0][k];
                b[i0][k] = temp;
            }
            flag = 0;
        }
        
        //Обнуление элементов под главной диагональю
        for (int j = i; j < N - 1; j++) {
            d = A[j + 1][i] / A[i][i];
            
            //Преобразование строки матрицы A
            A[j + 1][i] = A[j + 1][i] - A[i][i] * d;
            for (int u = i + 1; u < N; u++) {
                A[j + 1][u] = A[j + 1][u] - A[i][u] * d;
            }
            
            //Преобразование строки матрицы b
            for (int u = 0; u < N; u++) {
                b[j + 1][u] = b[j + 1][u] - b[i][u] * d;
            }
        }
    }
    
    //Приведение к диагональному виду
    for (int i = N - 1; i > 0; i--) {
        for (int j = i - 1; j >= 0; j--) {
            d = A[j][i] / A[i][i];
            
            A[j][i] = A[j][i] - A[i][i] * d;
            
            for (int u = 0; u < N; u++) {
                b[j][u] = b[j][u] - b[i][u] * d;
            }
        }
    }
    
    //Нормирование диагональных элементов
    for (int i = 0; i < N; i++) {
        d = A[i][i];
        A[i][i] = A[i][i] / d;  //Деление диагонального элемента
        
        //Деленеие строки матрицы b на d
        for (int j = 0; j < N; j++) {
            b[i][j] = b[i][j] / d;
        }
    }
}
