#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

struct datos{
	char nom_apel[100];
	char palo[10];
	int apuesta;
} jugador;

void ingresar_jugadores(struct datos *jugador){
printf("Ingrese el nombre del jugador: ");
fgets(jugador->nom_apel, 100, stdin);
printf("Ingrese el palo al que apostara el jugador: ");
fgets(jugador->palo, 10, stdin);
printf("Ingrese la apuesta del jugador: ");
scanf("%d", &jugador->apuesta);
	
	FILE *apuestas;
	apuestas = fopen("apuestas.txt", "w+");  

	if(apuestas==NULL){
	fprintf(stderr, "\nERROR OPENED FILE\n");
	exit(1);
	}
	
	int flag=0;
	
	flag = fwrite(&apuestas, sizeof(struct datos), 1, apuestas);
	
	if(flag){
		printf("Se Copio con Exito!\n");
	} else printf("Error al guardar :( \n");
	
	fclose(apuestas);
}

void generar_carta_linea(int *ce,int *co,int *cb,int *cc){
	tiro:
	int r = (rand() %4);
	switch(r){
		case 0:
			printf("Espada!\n");
			*ce -= 1;	
			break;
		case 1:
			printf("Oro!\n");
			*co -= 1;
			break;
		case 2:
			printf("Basto!\n");
			*cb -= 1;
			break;
		case 3:
			printf("Copa!\n");
			*cc -= 1;
			break;
		default:
			goto tiro;
	}
}

void generar_carta(int *ce,int *co,int *cb,int *cc){
	int comodin = 0;
	tiro:
	int r = (rand() %5);
	switch(r){
		case 0:
			printf("Salio... Espada!\n");
			if(comodin == 1) *ce += 2;
			else *ce +=1;	
			comodin = 0;
			break;
		case 1:
			printf("Salio... Oro!\n");
			if(comodin == 1) *co += 2;
			else *co += 1;
			comodin = 0;
			break;
		case 2:
			printf("Salio... Basto!\n");
			if(comodin == 1) *cb += 2;
			else *cb += 1;
			comodin = 0;
			break;
		case 3:
			printf("Salio... Copa!\n");
			if(comodin == 1) *cc += 2;
			else *cc += 1;
			comodin = 0;
			break;
		case 4:
			if(comodin == 1) goto tiro;
			printf("Comodin!\n");
			comodin = 1;
			goto tiro;
			break;
	}
}

void llenar_matriz(char carrera[5][21]){
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 21; j++){
			if(i == 2 && (j+1) % 5 == 0) carrera[i][j] = '|';
			else carrera[i][j] = '=';
		}
	}
}

void imprimir_matriz(char carrera[5][21], int ce, int co, int cb, int cc){
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 21; j++){
			//Imprime Los Caballos
			if (ce == j && i == 0)printf("%c ", 006); // Caballo de Espada
			if (co == j && i == 1)printf("%c ", 003); // Caballo de Oro
			if (cb == j && i == 3)printf("%c ", 004); // Caballo de Basto
			if (cc == j && i == 4)printf("%c ", 005); // Caballo de Copa
			else printf("%c ", carrera[i][j]);
		}
		printf("\n");
	}
	
}

void juego(char carrera[5][21]){
	//Cada variable representa la posicion de cada caballo, y comodin sirve como verificacion si ya salio un comodin.
	int ce = 0, co = 0, cb = 0, cc = 0;
	//Estas variables chequean si cada caballo pasÃƒÂ³ alguno de las cuatro lÃƒÂ­neas.
	int ce1, ce2, ce3, ce4, co1, co2, co3, co4, cb1, cb2, cb3, cb4, cc1, cc2, cc3, cc4;
	//Esta variable evita que se repita el evento de pasar un punto determinado
	int ver = 0;
	//El juego ocurre dentro de este while infinito.
	while(1){
		generar_carta(&ce, &co, &cb, &cc);
		//Verifica si el caballo ya paso tal punto.
		if(ce >= 4 && ce < 9 && ce1 != 1) ce1 = 1;
		else if(ce >= 9 && ce < 14 && ce2 != 1) ce2 = 1;
		else if(ce >= 14 && ce < 19 && ce3 != 1) ce3 = 1;
		else if(ce >= 19 && ce4 != 1) ce4 = 1;
		//Verifica si el caballo ya paso tal punto.
		if(co >= 4 && co < 9 && co1 != 1) co1 = 1;
		else if(co >= 9 && co < 14 && co2 != 1) co2 = 1;
		else if(co >= 14 && co < 19 && co3 != 1) co3 = 1;
		else if(co >= 19 && co4 != 1) co4 = 1;
		//Verifica si el caballo ya paso tal punto.
		if(cb >= 4 && cb < 9 && cb1 != 1) cb1 = 1;
		else if(cb >= 9 && cb < 14 && cb2 != 1) cb2 = 1;
		else if(cb >= 14 && cb < 19 && cb3 != 1) cb3 = 1;
		else if(cb >= 19 && cb4 != 1) cb4 = 1;
		//Verifica si el caballo ya paso tal punto.
		if(cc >= 4 && cc < 9 && cc1 != 1) cc1 = 1;
		else if(cc >= 9 && cc < 14 && cc2 != 1) cc2 = 1;
		else if(cc >= 14 && cc < 19 && cc3 != 1) cc3 = 1;
		else if(cc >= 19 && cc4 != 1) cc4 = 1;
		//Llama a la funciÃƒÂ³n encargada de imprimir la matriz (valga la rebundancia).
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
		if(ce1 == 1 && co1 == 1 && cb1 == 1 && cc1 == 1 && ver < 1){
			printf("Ya todos los caballos pasaron la marca de la 5ta linea\nSe dara vuelta una carta, y el palo que salga retrocede un lugar\n");
			printf("Presione enter para seguir\n");
			while( getchar() != '\n' );
			generar_carta_linea(&ce, &co, &cb, &cc);
			ver += 1;
			//imprimir_matriz(carrera, ce, co, cb, cc);
		}
		//Espera tres segundos antes de empezar denuevo el loop
		Sleep(1500);
		system("cls");
		}
	}}

	//Menu del juego

	void menu(struct datos *jugador, char carrera[5][21]){
	 int menu;
	 while(1){
	printf("Bienvenido Al juego de Carreras de Caballos\n 1- Ingresar Jugadores\n 2- Ver Reglas\n 3- Eliminar Apuesta\n");
	scanf("%d", &menu);
	switch(menu){
		case 1:
			ingresar_jugadores(jugador);
			break;
		case 2:
			printf("------REGLAS-------\n");
			printf("1) Siempre hay cuatro caballos en juego, 1 de cada palo.\n 2) Para que un caballo avance, tiene que salir el palo de ese caballo(por ejemplo, si al voltear la carta sale basto, avanza el caballo de basto)\n 3) Gana el caballo que logre avanzar 21 lugares.\n 4)Cada 5 pasos, cuando todos los caballos hayan pasado ese punto se voltea una carta. El caballo que sea del palo que salio retrocede un lugar.\n 5) Si sale un comodin, la proxima carta a la que le toque avanzar subira dos casillas en vez de una.\n");
			printf("\n");
		case 3:
			
	}
	
	}
}

int main(void){
	//Pone una semilla con raÃƒÆ’Ã‚Â­z time, asegurando que el numero generado siempre sea aleatorio.
	srand(time(NULL));
	/*FILE *apuestas;
	fopen("apuestas.txt", "w+");*/	
	char carrera[5][21];
	//datos *jugadores = &jugador;
	llenar_matriz(carrera);
	//juego(carrera);
	menu(&jugador, carrera);

}
