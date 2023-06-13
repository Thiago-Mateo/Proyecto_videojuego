#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct datos{
	char nom_apel[100];
	char palo[10];
	int apuesta;
} jugador;

void ingresar_jugadores(struct datos *jugador, FILE *apuestas){
printf("Ingrese el nombre del juagador: ");
fgets(jugador->nom, 100, stdin);
printf("Ingrese el palo al que apostara el jugador: ");
fgets(jugador->palo, 10, stdin);
printf("Ingrese la apuesta del jugador: ");
scanf("%d", &jugador->apuesta);
}

void llenar_matriz(char carrera[5][21]){
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 21; j++){
			if(i == 2 && (j+1) % 5 == 0) carrera[i][j] = '+';
			else carrera[i][j] = '0';
		}
	}
}

void juego(char carrera[5][21]){
	srand(time(NULL));
	int ce = 0, co = 0, cb = 0, cc = 0;
	char palo;
	while(1){
		int r = (rand() %50);
		if(r <= 12 && r > 0) palo = 'e';
		else if (r <= 24 && r > 12) palo = 'o';
		else if (r <= 36 && r > 24) palo = 'b';
		else if (r <= 48 && r > 36) palo = 'c';
		else if(r > 48) palo = 'C'; 
	}
}

void imprimir_matriz(char carrera[5][21], int ce, int co, int cb, int cc){
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
	char carrera[5][21];
	llenar_matriz(carrera);
	juego(carrera);
}
