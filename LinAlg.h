#ifndef LINALG_H
#define LINALG_H

int Gaus(double** A, double* b, double* x, int m, int n);
int Joga(double** A, double* b, double* x, int m, int n);
void Back(double** A, double** b, int N);
void DetDef(double** A, double* det, int N);
int approximate(int N, double** A, double* b, double* x, double eps);
int Yakobi(int N, double** A, double* b, double* x, double eps);
int Gradient(int N, double** A, double* b, double* x, double eps);
int SelBlock(double*** A, double*** B, double*** C, int N);
int SelStrassen(double*** A, double*** B, double*** C, int N);

#endif  // Конец GAUS_H
