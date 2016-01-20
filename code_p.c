//Ejecutar gcc code.c -o nombre_a_elegir -lpthread
//Luego ./nombre_elegido Nro_de_panqueques 

//Librerias
#include <stdio.h>
#include <time.h> //Libreria que nos permite calcular el tiempo
#include <stdlib.h>
#include <pthread.h> //Libreria que nos permitirá ocupar threads
#define MAX_N 20 //Se define maximo estable para el largo de la cadena de panqueques
//Variables globales
int n,k,k1,a[MAX_N],b[MAX_N],c[MAX_N],d[MAX_N],quema1[MAX_N],quema2[MAX_N],total1,total2,total3,total4,tipo,SIGNED=0,SIGNED1=0;
clock_t t_ini, t_fin , t2_ini, t2_fin , t3_ini, t3_fin , t4_ini, t4_fin; //Variables para calcular el tiempo
double secs,secs2,secs3,secs4; //Variables para calcular el tiempo
//Modulos
void muestra();
void print1();
void print2();
void print3();
void print4();
void magia1(int t);
void magia2(int t);
void magia3(int t);
void magia4(int t);
void *min_giro_no(void *arg);
void *max_giro_no(void *arg);
void *min_giro_si(void *arg);
void *min_giro_si(void *arg);
FILE *QuemaMin, *QuemaMax, *NormalMin, *NormalMax, *TiempoNormalMin, *TiempoNormalMax, *TiempoQuemaMin, *TiempoQuemaMax;
void muestra(){
	printf("---------------------------------\n");
	printf("-- Generacion de permutaciones --\n");
	printf("---------------------------------\n");
	printf("------Maximos giro---------------\n");
	printf("------Minimos giro---------------\n");
	printf("------Maximos giros(quemados)----\n");
	printf("------Minimos giros(quemados)----\n");
	printf("---------------------------------\n\n");
}
//Funcion imprimir para minimos no quemados
void print1(){
	int i;
	for (i = 1; i <= n; i++)
	{
		fprintf(NormalMin, "%d", a[i]);
	}
	fprintf(NormalMin, "\n");
	total1++;
}
//Funcion imprimir para maximos no quemados
void print2(){
	int i;
	for (i = 1; i <= n; i++)
	{
		fprintf(NormalMax, "%d", b[i]);
	}
	fprintf(NormalMax, "\n");
	total2++;
}
//Funcion imprimir para minimos QUEMADOS
void print3(){
	int i;
	for (i = 1; i <= n; i++)
	{
		if (quema1[i]==0 || !SIGNED)
			fprintf(QuemaMin, "%d", c[i]);
		else
			fprintf(QuemaMin, "-%d", c[i]);
	}
	fprintf(QuemaMin, "\n");
	total3++;
}
//Funcion imprimir para maximos QUEMADOS
void print4(){
	int i;
	for (i = 1; i <= n; i++)
	{
		if (quema2[i]==0 || !SIGNED1)
			fprintf(QuemaMax, "%d", d[i]);
		else
			fprintf(QuemaMax, "-%d", d[i]);
	}
	fprintf(QuemaMax, "\n");
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
void *min_giro_no(void *arg){
	//printf("Funcion giro minimo panqueques NORMALES\n");
	t_ini = clock(); //Variable para calcular el tiempo
	int incremento1=0,j1=0;
	do{
		print1();
		incremento1=0;
		j1=1;
		while(j1<n){
			if (a[j1] < a[j1+1])
				incremento1++;
			if (incremento1 == 2 || incremento1 == 1 && a[j1+1] < a[1])
				break;
			j1++;	
		}
		magia1(j1);
	}while(!(j1 == n && a[1] == 1));
	t_fin = clock(); //Variable para calcular el tiempo
	secs = (double)(t_fin - t_ini) / CLOCKS_PER_SEC;
	//printf("La funcion de giro minimo para los panqueques normales se demora %.16g milisegundos\n", secs * 1000.0);
}
//Funcion giro maximo panqueques normales
void *max_giro_no(void *arg){
	//printf("Funcion giro maximo panqueques NORMALES\n");
	t2_ini = clock(); //Variable para calcular el tiempo
	int j2;
	do{
		print2();
		magia2(n);
		print2();
		j2 = n;
		while(b[j2] == j2)
			j2--;
		magia2(j2-1);
	}while(j2 > 2);
	t2_fin = clock(); //Variable para calcular el tiempo
	secs2 = (double)(t2_fin - t2_ini) / CLOCKS_PER_SEC;		
	//printf("La funcion de giro maximo para los panqueques normales se demora %.16g milisegundos\n", secs2 * 1000.0);
}
//Funcion giro minimo panqueques QUEMADOS
void *min_giro_si(void *arg){
	//printf("Funcion giro minimo panqueques QUEMADOS\n");
	t3_ini = clock(); //Variable para calcular el tiempo
	int incremento2,j3;
	do{
		print3();
		incremento2=0;
		j3=1;
		while(j3 < n){
			if (c[j3] < c[j3+1])
				incremento2++;
			if (incremento2 == 2 || (incremento2 == 1 && c[j3+1] < c[1]))
				break;
			if (c[j3] < c[j3+1] && quema1[j3] == quema1[j3+1])
				break;
			if (c[j3] > c[j3+1] && quema1[j3] != quema1[j3+1])
				break;
			j3++;	
		}
		magia3(j3);
	}while(!(j3 == n && c[1] == 1 && quema1[1] == 0));
	t3_fin = clock(); //Variable para calcular el tiempo
	secs3 = (double)(t3_fin - t3_ini) / CLOCKS_PER_SEC;
	//printf("La funcion de giro minimo para los panqueques QUEMADOS se demora %.16g milisegundos\n", secs3 * 1000.0);
}
//Funcion giro maximo panqueques QUEMADOS
void *max_giro_si(void *arg){
	//printf("Funcion giro maximo panqueques QUEMADOS\n");
	t4_ini = clock(); //Variable para calcular el tiempo
	int j4;
	do{
		print4(); 
		magia4(n);
		print4();
		j4 = n;
		while(d[j4] == j4 && quema2[j4] == 0)
			j4--;
		magia4(j4-1);
	}while(j4>1);
	t4_fin = clock(); //Variable para calcular el tiempo
	secs4 = (double)(t4_fin - t4_ini) / CLOCKS_PER_SEC;
	//printf("La funcion de giro maximo para los panqueques QUEMADOS se demora %.16g milisegundos\n", secs4 * 1000.0);
}
int main(int argc, char *argv[])
{
	n = atoi(argv[1]); //Asignamos el valor ingresado por la consola al ejecutar el programa
	printf("Usted selecciono una cadena de largo: %d",n);
	//Se crean los archivos para poder apreciar las combinaciones
	QuemaMin = fopen("Final_Min_Si.txt", "w+");
	QuemaMax = fopen("Final_Max_Si.txt", "w+");
	NormalMin = fopen("Final_Min_No.txt", "w+");
	NormalMax = fopen("Final_Max_No.txt", "w+");
	int j;
	//muestra(); //Variable que muestra los titulos
	tipo = 1;
	SIGNED = 1;
	SIGNED1 = 1;
	k = 2;
	k1 = 2;
	//Las permutaciones a continuacion es para llenar la primera "pila"
	//Permutaciones iniciales
	for (j = 1; j <= n; j++){
		a[j] = j;
		b[j] = j;
		c[j] = j;
		d[j] = j;
	}
	//Permutaciones iniciales para los quemados
	for (j = 1; j <= n; j++){
		quema1[j] = 0;
		quema2[j] = 0;
	}
	if (tipo == 1){
		//Se declaran los thread a ocupar
		pthread_t t1;
		pthread_t t2;
		pthread_t t3;
		pthread_t t4;
		pthread_create(&t1, NULL , min_giro_no , NULL); //Se le asigna la funcion al thread
		pthread_create(&t2, NULL , max_giro_no , NULL); //Se le asigna la funcion al thread
		pthread_create(&t3, NULL , min_giro_si , NULL); //Se le asigna la funcion al thread
		pthread_create(&t4, NULL , max_giro_si , NULL); //Se le asigna la funcion al thread
	}
	tipo++;
	pthread_exit(NULL); // Última función que debe ejecutar el main() siempre
	fclose(QuemaMin);
	fclose(QuemaMax);
	fclose(NormalMin);
	fclose(NormalMax);
	fclose(TiempoNormalMin);
	return 0;
}