#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ppl.h>

#define mat_elem(a, y, x, n) (a + ((y) * (n) + (x)))

void swap_row(double *a, double *b, int r1, int r2, int n)
{
	double tmp2;
	int i;

	if (r1 == r2) return;
	parallel_for(i(0),n,[&](i i)
	 {
        double tmp, *p1, *p2;
		p1 = mat_elem(a, r1, i, n);
		p2 = mat_elem(a, r2, i, n);
		tmp = *p1, *p1 = *p2, *p2 = tmp;
	});
	
	tmp2 = b[r1], b[r1] = b[r2], b[r2] = tmp2;
}

void gauss_eliminate(double *a, double *b, double *x, int n)
{
#define A(y, x) (*mat_elem(a, y, x, n))
	int i, j, col, row, max_row,dia;
	double max;

	for (dia = 0; dia < n; dia++) {
		max_row = dia, max = A(dia, dia);

        //#pragma omp parallel for
		for (row = dia + 1; row < n; row++){
            double tmp;
			if ((tmp = fabs(A(row, dia))) > max)
				max_row = row, max = tmp;
		}
		swap_row(a, b, dia, max_row, n);


		for (row = dia + 1; row < n; row++) {
            double tmp;
			tmp = A(row, dia) / A(dia, dia);
			//#pragma omp parallel for
			for (col = dia+1; col < n; col++)
				A(row, col) -= tmp * A(dia, col);
			A(row, dia) = 0;
			b[row] -= tmp * b[dia];
		}
	}
	//#pragma omp parallel for
	for (row = n - 1; row >= 0; row--) {
        double tmp;
		tmp = b[row];
		//#pragma omp parallel for
		for (j = n - 1; j > row; j--)
			tmp -= x[j] * A(row, j);
		x[row] = tmp / A(row, row);
	}
#undef A
}

int main(void)
{
	double a[] = {
		1.00, 0.00, 0.00,  0.00,  0.00, 0.00,
		1.00, 0.63, 0.39,  0.25,  0.16, 0.10,
		1.00, 1.26, 1.58,  1.98,  2.49, 3.13,
		1.00, 1.88, 3.55,  6.70, 12.62, 23.80,
		1.00, 2.51, 6.32, 15.88, 39.90, 100.28,
		1.00, 3.14, 9.87, 31.01, 97.41, 306.02
	};
	double b[] = { -0.01, 0.61, 0.91, 0.99, 0.60, 0.02 };
	double x[6];
	int i;

	gauss_eliminate(a, b, x, 6);

	for (i = 0; i < 6; i++)
		printf("%g\n", x[i]);

	return 0;
}
