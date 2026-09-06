#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

#define PI acos(-1.0)

/* Recursive FFT */
void fft(complex double a[], int n, int invert)
{
    if (n == 1)
        return;

    /* Divide into even and odd elements */
    complex double *even = malloc((n / 2) * sizeof(complex double));
    complex double *odd  = malloc((n / 2) * sizeof(complex double));

    for (int i = 0; i < n / 2; i++)
    {
        even[i] = a[2 * i];
        odd[i]  = a[2 * i + 1];
    }

    /* Recursive calls */
    fft(even, n / 2, invert);
    fft(odd, n / 2, invert);

    /* Combine */
    double angle = 2 * PI / n * (invert ? -1 : 1);

    complex double w = 1;
    complex double wn = cos(angle) + I * sin(angle);

    for (int k = 0; k < n / 2; k++)
    {
        complex double t = w * odd[k];

        a[k] = even[k] + t;
        a[k + n / 2] = even[k] - t;

        w *= wn;
    }

    free(even);
    free(odd);

    /* Scaling for inverse FFT */
    if (invert)
    {
        for (int i = 0; i < n; i++)
            a[i] /= 2;
    }
}

/* Convolution using FFT */
void convolution(double A[], int m,
                 double B[], int n,
                 double C[])
{
    int required = m + n - 1;

    /* Find next power of 2 */
    int N = 1;

    while (N < required)
        N *= 2;

    /* Allocate complex arrays */
    complex double *FA =
        calloc(N, sizeof(complex double));

    complex double *FB =
        calloc(N, sizeof(complex double));

    /* Copy input vectors */
    for (int i = 0; i < m; i++)
        FA[i] = A[i];

    for (int i = 0; i < n; i++)
        FB[i] = B[i];

    /* FFT */
    fft(FA, N, 0);
    fft(FB, N, 0);

    /* Pointwise multiplication */
    for (int i = 0; i < N; i++)
        FA[i] *= FB[i];

    /* Inverse FFT */
    fft(FA, N, 1);

    /* Extract result */
    for (int i = 0; i < required; i++)
        C[i] = creal(FA[i]);

    free(FA);
    free(FB);
}

/* Print vector */
void printVector(double A[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%.2f ", A[i]);

    printf("\n");
}

int main()
{
    int m, n;

    printf("Enter size of vector A: ");
    scanf("%d", &m);

    printf("Enter size of vector B: ");
    scanf("%d", &n);

    if (n < m)
    {
        printf("Please ensure n >= m.\n");
        return 1;
    }

    double *A = malloc(m * sizeof(double));
    double *B = malloc(n * sizeof(double));
    double *C = malloc((m + n - 1) * sizeof(double));

    printf("\nEnter elements of A:\n");

    for (int i = 0; i < m; i++)
        scanf("%lf", &A[i]);

    printf("\nEnter elements of B:\n");

    for (int i = 0; i < n; i++)
        scanf("%lf", &B[i]);

    /* Perform convolution */
    convolution(A, m, B, n, C);

    printf("\nVector A: ");
    printVector(A, m);

    printf("Vector B: ");
    printVector(B, n);

    printf("\nConvolution C: ");
    printVector(C, m + n - 1);

    free(A);
    free(B);
    free(C);

    return 0;
}