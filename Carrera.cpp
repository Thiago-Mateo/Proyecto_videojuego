#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

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
	
FILE* jugadores;
	
	jugadores=fopen("datos.bin", "w+b");
	if(jugadores==NULL){
	fprintf(stderr, "\nERROR OPENED FILE\n");
	exit(1);
	}
	
	
	int flag=0;
	
	flag = fwrite(&jugadores, sizeof(struct datos), 1, jugadores);
	
	if(flag){
		printf("CONTENTS OF THE STRUCTURE WRITTEN SUCCESFULLY");
	} else printf("ERROR WRITING TO FILE");
	
	fclose(jugadores);
}
}

void llenar_matriz(char carrera[5][21]){
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 21; j++){
			if(i == 2 && (j+1) % 5 == 0) carrera[i][j] = '+';
			else carrera[i][j] = '0';
		}
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

void juego(char carrera[5][21]){
	//Pone una semilla con raíz time, asegurando que el numero generado siempre sea aleatorio.
	srand(time(NULL));
	//Cada variable representa la posicion de cada caballo, y comodin sirve como verificacion si ya salio un comodin.
	int ce = 0, co = 0, cb = 0, cc = 0, comodin = 0;
	//Estas variables chequean si cada caballo pasó alguno de las cuatro líneas.
	int ce1, ce2, ce3, ce4, co1, co2, co3, co4, cb1, cb2, cb3, cb4, cc1, cc2, cc3, cc4;
	//El juego ocurre dentro de este while infinito.
	while(1){
		tiro:
		//Genera un número aleatorio.
		int r = (rand() %50);
		//Según el valor generado, sale alguno de los cuatro palos o comodín.
		if(r <= 12 && r > 0){
			printf("Salio... Espada!\n");
			if(comodin == 1) ce += 2;
			else ce++;	
			comodin = 0;
			//Verifica si el caballo ya paso tal punto.
			if(ce >= 4 && ce < 9 && ce1 != 1) ce1 = 1;
			else if(ce >= 9 && ce < 14 && ce2 != 1) ce2 = 1;
			else if(ce >= 14 && ce < 19 && ce3 != 1) ce3 = 1;
			else if(ce >= 19 && ce4 != 1) ce4 = 1;
		}
		else if (r <= 24 && r > 12){
			printf("Salio... Oro!\n");
			if(comodin == 1) co += 2;
			else co++;
			comodin = 0;
			//Verifica si el caballo ya paso tal punto.
			if(co >= 4 && co < 9 && co1 != 1) co1 = 1;
			else if(co >= 9 && co < 14 && co2 != 1) co2 = 1;
			else if(co >= 14 && co < 19 && co3 != 1) co3 = 1;
			else if(co >= 19 && co4 != 1) co4 = 1;
		}
		else if (r <= 36 && r > 24){
			printf("Salio... Basto!\n");
			if(comodin == 1) cb += 2;
			else cb++;
			comodin = 0;
			//Verifica si el caballo ya paso tal punto.
			if(cb >= 4 && cb < 9 && cb1 != 1) cb1 = 1;
			else if(cb >= 9 && cb < 14 && cb2 != 1) cb2 = 1;
			else if(cb >= 14 && cb < 19 && cb3 != 1) cb3 = 1;
			else if(cb >= 19 && cb4 != 1) cb4 = 1;
		}
		else if (r <= 48 && r > 36){
			printf("Salio... Copa!\n");
			if(comodin == 1) cc += 2;
			else cc++;
			comodin = 0;
			//Verifica si el caballo ya paso tal punto.
			if(cc >= 4 && cc < 9 && cc1 != 1) cc1 = 1;
			else if(cc >= 9 && cc < 14 && cc2 != 1) cc2 = 1;
			else if(cc >= 14 && cc < 19 && cc3 != 1) cc3 = 1;
			else if(cc >= 19 && cc4 != 1) cc4 = 1;
		}
		else if(r > 48 && comodin == 0){
			printf("Comodin!\n");
			comodin++;
			goto tiro;
		}
		//Llama a la función encargada de imprimir la matriz (valga la rebundancia).
		imprimir_matriz(carrera, ce, co, cb, cc);
		//Si alguno de los caballos llega al final de la matriz(Matriz de 21 lugares) gana.
		if(ce == 20){
			printf("Gana el caballo de espada!");
			return;
		}
		else if(co == 20){
			printf("Gana el caballo de oro!");
			return;
		}
		else if(cb == 20){
			printf("Gana el caballo de basto!");
			return;
		}
		else if(cc == 20){
			printf("Gana el caballo de copa!");
			return;
		}
		//Espera tres segundos antes de empezar denuevo el loop
		Sleep(3000);
		}
	}

int main(void){
	FILE *apuestas;
	fopen("apuestas.txt", "w+");
	char carrera[5][21];
	llenar_matriz(carrera);
	juego(carrera);
	
}
