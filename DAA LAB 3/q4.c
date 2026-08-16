#include <stdio.h>

void printMatrix(const char *label, int n, int mat[n][n])
{
    printf("%s:\n", label);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d\n", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// ADDITION

void addMatrix(int n, int A[n][n], int B[n][n], int C[n][n])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

// SUBTRACTION

void subMatrix(int n, int A[n][n], int B[n][n], int C[n][n])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

// STRASSEN'S ALGO

void strassen(int n, int A[n][n], int B[n][n], int C[n][n])
{
    // base case
    if (n == 1)
    {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n / 2;

    // SUBMATRICES ALLOCATED DIRECTLY ON THE STACK
    int A11[k][k], A12[k][k], A21[k][k], A22[k][k];
    int B11[k][k], B12[k][k], B21[k][k], B22[k][k];
    int C11[k][k], C12[k][k], C21[k][k], C22[k][k];

    int M1[k][k], M2[k][k], M3[k][k], M4[k][k], M5[k][k], M6[k][k], M7[k][k];
    int tempA[k][k], tempB[k][k];

    // STEP 1:PARTITION A AND B INTO 4 SUBMATRICES EACH

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }

    // Step 2: Compute Strassen's 7 products (M1 to M7)

    // M1 = (A11 + A22) * (B11 + B22)
    addMatrix(k, A11, A22, tempA);
    addMatrix(k, B11, B22, tempB);
    strassen(k, tempA, tempB, M1);

    // M2 = (A21 + A22) * B11
    addMatrix(k, A21, A22, tempA);
    strassen(k, tempA, B11, M2);

    // M3 = A11 * (B12 - B22)
    subMatrix(k, B12, B22, tempB);
    strassen(k, A11, tempB, M3);

    // M4 = A22 * (B21 - B11)
    subMatrix(k, B21, B11, tempB);
    strassen(k, A22, tempB, M4);

    // M5 = (A11 + A12) * B22
    addMatrix(k, A11, A12, tempA);
    strassen(k, tempA, B22, M5);

    // M6 = (A21 - A11) * (B11 + B12)
    subMatrix(k, A21, A11, tempA);
    addMatrix(k, B11, B12, tempB);
    strassen(k, tempA, tempB, M6);

    // M7 = (A12 - A22) * (B21 + B22)
    subMatrix(k, A12, A22, tempA);
    addMatrix(k, B21, B22, tempB);
    strassen(k, tempA, tempB, M7);

    // Step 3: Compute output submatrices C11, C12, C21, C22

    // C11 = M1 + M4 - M5 + M7
    addMatrix(k, M1, M4, tempA);
    subMatrix(k, tempA, M5, tempB);
    addMatrix(k, tempB, M7, C11);

    // C12 = M3 + M5
    addMatrix(k, M3, M5, C12);

    // C21 = M2 + M4
    addMatrix(k, M2, M4, C21);

    // C22 = M1 - M2 + M3 + M6
    subMatrix(k, M1, M2, tempA);
    addMatrix(k, tempA, M3, tempB);
    addMatrix(k, tempB, M6, C22);

    // Step 4: Merge C11, C12, C21, C22 into final matrix C
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            C[i][j] = C11[i][j];
            C[i][j + k] = C12[i][j];
            C[i + k][j] = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }
    }
}

int main()
{
    int n = 4;

    int A[4][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}};

    int B[4][4] = {
        {1, 0, 4, 5},
        {4, 5, 9, 5},
        {1, 0, 4, 9},
        {4, 5, 3, 3}};

    int C[4][4];

    printMatrix("Matrix A", n, A);
    printMatrix("Matrix B", n, B);

    // RUN STRASSENS ALGO
    strassen(n, A, B, C);

    printMatrix("Result Matrix C(A*B)", n, C);

    return 0;
}