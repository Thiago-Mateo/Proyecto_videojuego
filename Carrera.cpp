#include<stdio.h>
#include<stdlib.h>

struct mazo{
	int numero_carta;
	char palo[10];
};

struct datos{
	char nom_apel[100];
	char palo[10];
	int apuesta;
} jugador;

void crear_mazo(struct mazo *cartas){
	return;
}

void ingresar_jugadores(datos *jugador, FILE *apuestas){
	
}

void llenar_matriz(char carrera[5][21]){
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 21; j++){
			if(i == 2 && (j+1) % 5 == 0) carrera[i][j] = '+';
			else carrera[i][j] = '0';
		}
	}
}

void imprimir_carrera(char carrera[5][21]){
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 21; j++){
			printf("%c", carrera[i][j]);
		}
		printf("\n");
	}
}
int main(void){
	FILE *apuestas;
	fopen("apuestas.txt", "w+");
	mazo *cartas = new mazo[48];
	char carrera[5][21];
	llenar_matriz(carrera);
	imprimir_carrera(carrera);
}
