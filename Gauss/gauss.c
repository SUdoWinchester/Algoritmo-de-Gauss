#include <stdio.h>
#include <stdlib.h>

void print(int m, int n, double mat[m][n]) {
	printf("\n\n");
	for(int i = 0; i < m; i++) {
		for(int j = 0; j < n; j++) {
			printf("%lf\t", mat[i][j]);
		}
		printf("\n");
	}
}

void pivotiamento(int m, int n, double mat[m][n], int pivo) {
	double aux[n];

	for(int i = 0; i < n; i++)
		aux[i] = mat[pivo][i];

	for(int i = pivo+1; i < m; i++) {
		if(mat[i][pivo] != 0) {
			for(int j = 0; j < n; j++) {
				mat[pivo][j] = mat[i][j];
			}
			for(int j = 0; j < n; j++) {
				mat[i][j] = aux[j];
			}

			return ;
		}
	}

	printf("ERRO DE PIVOTIAMENTO!!!\n");

}

void reducao(int m, int n, double mat[m][n], int px, int py) {
	if(mat[py][py] == 0) 
		pivotiamento(m, n, mat, py);

	if(mat[px][py] == 0)
		return ;

	double k = mat[px][py]/mat[py][py];

	for(int i = py; i < n; i++){
		mat[px][i] = mat[px][i] - (mat[py][i]*k);
	}
}

void calculo(int m, int n, double mat[m][n], double x[m]) {
	double soma;

	for(int i = m-1; i >= 0; i--) {
		soma = 0;

		for(int j = 0; j < n-1; j++) {
			if(j != i) {
				soma += mat[i][j] * x[j];
			}
		}		
		x[i] = (mat[i][n-1] - soma)/mat[i][i];
	}	
}

void main() {
	int m, n, eq;

	printf("Entre com o numero de equacoes lineares: ");
	scanf("%d", &eq);
	m = eq;
	n = eq+1;
	double mat[m][n], x[m];		

	printf("\n\nEntre com os valores da matriz:\n");
	for(int i = 0; i < m; i++) {
		for(int j = 0; j < n; j++) {
			printf("A[%d][%d] = ", i+1, j+1);
			scanf("%lf", &mat[i][j]);
		}
		x[i] = 0;
	}
	printf("\n\nMatriz:");
	print(m, n, mat);

	for(int j = 0; j < n-2; j++) {
		for(int i = 1; i+j < m; i++) {
			reducao(m, n, mat, i+j, j);
		}
	}
	printf("\n\nMatriz reduzida:");
	print(m, n, mat);

	calculo(m, n, mat, x);	
	
	printf("\n\nResultado Final:\n");
	for(int i = 0; i < m; i++)
		printf("X%d = %lf\n", i+1, x[i]);
}