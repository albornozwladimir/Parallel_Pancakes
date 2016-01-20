// Ejecutar gcc code.c -o nombre_a_elegir

//Librerias
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#define MAX_N 20
//Variables globales
int n,k,k1,a[MAX_N],b[MAX_N],c[MAX_N],d[MAX_N],quema1[MAX_N],quema2[MAX_N],total1,total2,total3,total4,tipo,SIGNED=0,SIGNED1=0;
//Modulos

void input(){
	printf("---------------------------------\n");
	printf("-- Generacion de permutaciones --\n");
	printf("---------------------------------\n");
	printf("------Maximos giro---------------\n");
	printf("------Minimos giro---------------\n");
	printf("------Maximos giros(quemados)----\n");
	printf("------Minimos giros(quemados)----\n");
	printf("---------------------------------\n");
	printf("\n");
}
//Funcion imprimir para minimos no quemados
void print1(){
	int i;
	for (i = 1; i <= n; i++)
	{
		printf(" %d ", a[i]);
	}
	printf("\n");
	total1++;
}
//Funcion imprimir para maximos no quemados
void print2(){
	int i;
	for (i = 1; i <= n; i++)
	{
		printf(" %d ", b[i]);
	}
	printf("\n");
	total2++;
}
//Funcion imprimir para minimos QUEMADOS
void print3(){
	int i;
	for (i = 1; i <= n; i++)
	{
		if (quema1[i]==0 || !SIGNED)
			printf(" %d ", c[i]);
		else
			printf("-%d ", c[i]);
	}
	printf("\n");
	total3++;
}
//Funcion imprimir para maximos QUEMADOS
void print4(){
	int i;
	for (i = 1; i <= n; i++)
	{
		if (quema2[i]==0 || !SIGNED1)
			printf(" %d ", d[i]);
		else
			printf("-%d ", d[i]);
	}
	printf("\n");
	total4++;
}
//Funcion giro minimos no quemados
void magia1(int t){
	int i,aux[MAX_N];
	for (i = 1; i <= t; i++)
		aux[i]=a[t-i+1];
	for (i = 1; i <= t; i++)
		a[i]=aux[i];
}
//Funcion giro maximos no quemados
void magia2(int t){
	int i,aux[MAX_N];
	for (i = 1; i <= t; i++)
		aux[i]=b[t-i+1];
	for (i = 1; i <= t; i++)
		b[i]=aux[i];
}
//Funcion giro minimos QUEMADOS
void magia3(int t){
	int i,aux[MAX_N];
	for (i = 1; i <= t; i++)
		aux[i]=c[t-i+1];
	for (i = 1; i <= t; i++)
		c[i]=aux[i];
	//Giro caso quemados
	if (k>1)
	{
		for (i = 1; i <= t; i++)
			aux[i] = quema1[t-i+1];
		for (i = 1; i <= t; i++)
			quema1[i] = ((aux[i]+1)%k);
	}
}
//Funcion giro minimos QUEMADOS
void magia4(int t){
	int i,aux[MAX_N];
	for (i = 1; i <= t; i++)
		aux[i]=d[t-i+1];
	for (i = 1; i <= t; i++)
		d[i]=aux[i];
	//Giro caso quemados
	if (k1>1)
	{
		for (i = 1; i <= t; i++)
			aux[i] = quema2[t-i+1];
		for (i = 1; i <= t; i++)
			quema2[i] = ((aux[i]+1)%k1);
	}
}
//Funcion giro minimo panqueques normales
void min_giro_no(){
	//printf("Funcion giro minimo panqueques NORMALES\n");
	int incremento=0,j=0;
	do{
		//print1();
		incremento=0;
		j=1;
		while(j<n){
			if (a[j] < a[j+1])
				incremento++;
			if (incremento == 2 || incremento == 1 && a[j+1] < a[1])
				break;
			j++;	
		}
		magia1(j);
	}while(!(j == n && a[1] == 1));
}
//Funcion giro maximo panqueques normales
void max_giro_no(){
	//printf("Funcion giro maximo panqueques NORMALES\n");
	int j;
	do{
		//print2();
		magia2(n);
		//print2();
		j = n;
		while(b[j] == j)
			j--;
		magia2(j-1);
	}while(j > 2);
}
//Funcion giro minimo panqueques QUEMADOS
void min_giro_si(){
	//printf("Funcion giro minimo panqueques QUEMADOS\n");
	int incremento,j;
	do{
		//print3();
		incremento=0;
		j=1;
		while(j < n){
			if (c[j] < c[j+1])
				incremento++;
			if (incremento == 2 || (incremento == 1 && c[j+1] < c[1]))
				break;
			if (c[j] < c[j+1] && quema1[j] == quema1[j+1])
				break;
			if (c[j] > c[j+1] && quema1[j] != quema1[j+1])
				break;
			j++;	
		}
		magia3(j);
	}while(!(j == n && c[1] == 1 && quema1[1] == 0));
}
//Funcion giro maximo panqueques QUEMADOS
void max_giro_si(){
	//printf("Funcion giro maximo panqueques QUEMADOS\n");
	int j;
	do{
		//print4();
		magia4(n);
		//print4();
		j = n;
		while(d[j] == j && quema2[j] == 0)
			j--;
		magia4(j-1);
	}while(j>1);
}
int main(int argc, char const *argv[])
{
	n = atoi(argv[1]);
	printf("Usted selecciono una cadena de largo: %d",n);
	printf("\n");
	clock_t t_ini, t_fin;
	double secs;
	tipo = 1;
	SIGNED = 1;
	SIGNED1 = 1;
	k = 2;
	k1 = 2;
	int j;
	//	input();
	//Permutaciones iniciales
	for (j = 1; j <= n; j++){
		a[j] = j;
		b[j] = j;
		c[j] = j;
		d[j] = j;
	}
	for (j = 1; j <= n; j++){
		quema1[j] = 0;
		quema2[j] = 0;
	}
	if (tipo == 1){
		t_ini = clock();
		min_giro_no();
		//printf("Total = %d\n\n", total1);
		max_giro_no();
		//printf("Total = %d\n\n", total2);
		min_giro_si();
		//printf("Total = %d\n\n", total3);
		max_giro_si();
		//printf("Total = %d\n\n", total4);
	}
	t_fin = clock();
	secs = (double)(t_fin - t_ini) / CLOCKS_PER_SEC;		
	//printf("%.16g milisegundos\n", secs * 1000.0);
	return 0;
}