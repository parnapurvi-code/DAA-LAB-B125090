#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Print matrix */
void printMatrix(double A[][20], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%8.2f ", A[i][j]);

        printf("\n");
    }
}

/* (i) Matrix Addition */
void matrixAddition(double A[][20], double B[][20],
                    double C[][20], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
    }
}

/* (ii) Matrix Multiplication */
void matrixMultiplication(double A[][20], double B[][20],
                          double C[][20], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = 0;

            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
    }
}

/* (iii) Check zero matrix */
int isZeroMatrix(double A[][20], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (A[i][j] != 0)
                return 0;
        }
    }

    return 1;
}

/* (iv) Check symmetric matrix */
int isSymmetric(double A[][20], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (A[i][j] != A[j][i])
                return 0;
        }
    }

    return 1;
}

/* Helper function for determinant */
void getCofactor(double A[][20], double temp[][20],
                 int p, int q, int n)
{
    int i = 0, j = 0;

    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (row != p && col != q)
            {
                temp[i][j++] = A[row][col];

                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

/* (v) Recursive determinant */
double determinant(double A[][20], int n)
{
    if (n == 1)
        return A[0][0];

    if (n == 2)
        return A[0][0] * A[1][1]
             - A[0][1] * A[1][0];

    double temp[20][20];
    double det = 0;
    int sign = 1;

    for (int f = 0; f < n; f++)
    {
        getCofactor(A, temp, 0, f, n);

        det += sign * A[0][f]
             * determinant(temp, n - 1);

        sign = -sign;
    }

    return det;
}

/* (vi) In-place transpose */
void transposeInPlace(double A[][20], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            double temp = A[i][j];
            A[i][j] = A[j][i];
            A[j][i] = temp;
        }
    }
}

/*
   (vii) Eigenvalue demonstration

   Power iteration finds the dominant eigenvalue
   and corresponding eigenvector.

   This is a simplified demonstration.
*/
void dominantEigen(double A[][20], int n)
{
    double x[20], y[20];
    double eigenvalue = 0;

    for (int i = 0; i < n; i++)
        x[i] = 1.0;

    for (int iteration = 0; iteration < 1000; iteration++)
    {
        double norm = 0;

        /* y = A*x */
        for (int i = 0; i < n; i++)
        {
            y[i] = 0;

            for (int j = 0; j < n; j++)
                y[i] += A[i][j] * x[j];
        }

        /* Find maximum absolute value */
        for (int i = 0; i < n; i++)
        {
            if (fabs(y[i]) > norm)
                norm = fabs(y[i]);
        }

        /* Normalize */
        for (int i = 0; i < n; i++)
            x[i] = y[i] / norm;

        eigenvalue = norm;
    }

    printf("\nDominant eigenvalue ≈ %.4f\n", eigenvalue);

    printf("Corresponding eigenvector:\n");

    for (int i = 0; i < n; i++)
        printf("%.4f\n", x[i]);
}

int main()
{
    int n;

    double A[20][20];
    double B[20][20];
    double C[20][20];

    printf("Enter order of square matrix: ");
    scanf("%d", &n);

    printf("\nEnter elements of Matrix A:\n");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            scanf("%lf", &A[i][j]);
    }

    printf("\nEnter elements of Matrix B:\n");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            scanf("%lf", &B[i][j]);
    }

    /* (i) Addition */
    matrixAddition(A, B, C, n);

    printf("\n(i) Matrix Addition:\n");
    printMatrix(C, n);

    /* (ii) Multiplication */
    matrixMultiplication(A, B, C, n);

    printf("\n(ii) Matrix Multiplication:\n");
    printMatrix(C, n);

    /* (iii) Zero matrix */
    if (isZeroMatrix(A, n))
        printf("\n(iii) Matrix A is a zero matrix.\n");
    else
        printf("\n(iii) Matrix A is not a zero matrix.\n");

    /* (iv) Symmetric matrix */
    if (isSymmetric(A, n))
        printf("\n(iv) Matrix A is symmetric.\n");
    else
        printf("\n(iv) Matrix A is not symmetric.\n");

    /* (v) Determinant */
    printf("\n(v) Determinant of A = %.2f\n",
           determinant(A, n));

    /* (vi) Transpose */
    transposeInPlace(A, n);

    printf("\n(vi) Transpose of A (in-place):\n");
    printMatrix(A, n);

    /* (vii) Eigenvalue and eigenvector */
    printf("\n(vii) Eigenvalue and eigenvector:\n");

    dominantEigen(A, n);

    return 0;
}