#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

//pap lo declaramos para hacer un fgets() que evita un error de salto.
char pap[10];
//players es un contador de los jugadores ya anotados.
int players = 0;
//pozo es la cantidad total de dinero apostado todo sumado.
int pozo = 0;

struct datos{
	char nom_apel[100];
	char palo[10];
	int apuesta;
} jugador[100];

void ingresar_jugadores(struct datos *jugador){
	//Pide al usuario que ingrese a los jugadores y guarda la informacion en la estructura
	fgets(pap, 100, stdin);
	printf("Ingrese el nombre del jugador: ");
	fgets(jugador[players].nom_apel, 100, stdin);
	printf("Ingrese el palo al que apostara el jugador: ");
	fgets(jugador[players].palo, 10, stdin);
	printf("Ingrese la apuesta del jugador: ");
	scanf("%d", &jugador[players].apuesta);
	pozo += jugador[players].apuesta;
	players += 1;
	
}

void generar_carta_linea(int *ce,int *co,int *cb,int *cc){
	tiro:
	//Genera un numero aleatorio entre 0 y 3
	//Cada numero del 0 a 3 representa una carta, y la que salga retrocede un espacio
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

void generar_carta(int *ce,int *co,int *cb,int *cc, int *c_count){
	//Comodin verifica si ya salio y no salio otra carta aun.
	int comodin = 0;
	//Count sirve como contador de los comodines. Si ya salieron 2 no puede salir otro.
	int count = *c_count;
	tiro:
	//Genera un numero aleatorio entre 0 y 4
	//Cada numero del 0 a 4 representa una carta, y la que salga avanza un espacio o dos, si es comodin.
	int r = (rand() %5);
	switch(r){
		case 0:
			//Color B pone la consola en azul.
			{system("color B");printf("Salio... Espada!\t\tPozo: %d\n", pozo);}
			//Se fija si el comodin salio anteriormente
			//En caso de que si, el caballo avanza dos espacios
			//Si no avanza solo uno.
			if(comodin == 1) *ce += 2;
			else *ce +=1;	
			comodin = 0;
			break;
		case 1:
			//Color 6 pone la consola en amarillo.
			{system("color 6");printf("Salio... Oro!\t\t\tPozo: %d\n", pozo);}
			if(comodin == 1) *co += 2;
			else *co += 1;
			comodin = 0;
			break;
		case 2:
			//Color 2 pone la consola en verde.
			{system("color 2");printf("Salio... Basto!\t\t\tPozo: %d\n", pozo);}
			if(comodin == 1) *cb += 2;
			else *cb += 1;
			comodin = 0;
			break;
		case 3:
			//Color 4 pone la consola en rojo.
			{system("color 4");printf("Salio... Copa!\t\t\tPozo: %d\n", pozo);}
			if(comodin == 1) *cc += 2;
			else *cc += 1;
			comodin = 0;
			break;
		case 4:
			//Verifica si ya hay un comodin o si ya salio dos veces.
			if(comodin == 1 || count == 2) goto tiro;
			printf("Comodin!\n");
			comodin = 1;
			*c_count += 1;
			goto tiro;
			break;
	}
}

void llenar_matriz(char carrera[5][21]){
	//Llena la matriz con caracteres de '=' y '|'
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 21; j++){
			if(i == 2) carrera[i][j] = '-';
			else if((j+1) % 5 == 0) carrera[i][j] = '|';
			else carrera[i][j] = '=';
		}
	}
}

void imprimir_matriz(char carrera[5][21], int ce, int co, int cb, int cc){
	//Estas lineas imprimen un borde en ASCII.
	printf("%c%c%c%c%c%c%c%c%c%c", 205, 205, 205, 205, 205, 205, 205, 205, 205, 205);
	printf("%c%c%c%c%c%c%c%c%c%c", 205, 205, 205, 205, 205, 205, 205, 205, 205, 205);
	printf("%c%c%c%c%c%c%c%c%c%c", 205, 205, 205, 205, 205, 205, 205, 205, 205, 205);
	printf("%c%c%c%c%c%c%c%c%c%c", 205, 205, 205, 205, 205, 205, 205, 205, 205, 205);
	printf("%c%c%c%c%c\n\n", 205, 205, 205, 205, 205);
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 21; j++){
			//Imprime Los Caballos
			if (ce == j && i == 0)printf("%c ", 006); // Caballo de Espada.
			if (co == j && i == 1)printf("%c ", 003); // Caballo de Oro.
			if (cb == j && i == 3)printf("%c ", 004); // Caballo de Basto.
			if (cc == j && i == 4)printf("%c ", 005); // Caballo de Copa.
			else if (carrera[i][j] == '|') printf("%c ", 186);
			else if (carrera[i][j] == '-') printf("%c ", 178);
			else printf("%c ", carrera[i][j]);
		}
		//Imprime el palo correspondiente a cada linea.
		if(i == 0) printf("\tEspada");
		if(i == 1) printf("\tOro");
		if(i == 3) printf("\tBasto");
		if(i == 4) printf("\tCopa");
		printf("\n\n");
	}
	//Estas lineas imprimen un borde en ASCII.
	printf("%c%c%c%c%c%c%c%c%c%c", 205, 205, 205, 205, 205, 205, 205, 205, 205, 205);
	printf("%c%c%c%c%c%c%c%c%c%c", 205, 205, 205, 205, 205, 205, 205, 205, 205, 205);
	printf("%c%c%c%c%c%c%c%c%c%c", 205, 205, 205, 205, 205, 205, 205, 205, 205, 205);
	printf("%c%c%c%c%c%c%c%c%c%c", 205, 205, 205, 205, 205, 205, 205, 205, 205, 205);
	printf("%c%c%c%c%c\n", 205, 205, 205, 205, 205);	
}

void verificar_puntos(int *ce, int *co, int *cb, int *cc, int *ver, int ce1, int ce2, int ce3, int ce4, int co1, int co2, int co3, int co4, int cb1, int cb2, int cb3, int cb4, int cc1, int cc2, int cc3, int cc4){
	//Verificacion chequea si ya ocurre el evento de dar vuelta una carta para evitar repeticiones.
	int verificacion = *ver;
	//Si todos los caballos ya pasaron la quinta linea y verificacion es menor a uno ocurre el evento y asi con el resto.
	if(ce1 >= 1 && co1 >= 1 && cb1 >= 1 && cc1 >= 1 && verificacion < 1){
		printf("Ya todos los caballos pasaron la marca de la 5ta linea\nSe dara vuelta una carta, y el palo que salga retrocede un lugar\n");
		printf("Presione enter para seguir\n");
		while( getchar() != '\n' );
		while( getchar() != '\n' );
		//Llama a la funcion que genera una carta y hace retroceder a un caballo.
		generar_carta_linea(ce, co, cb, cc);
		//Suma uno a verificacion y entonces este if ya no vuelve a ocurrir.
		*ver += 1;
	}
	if(ce2 >= 1 && co2 >= 1 && cb2 >= 1 && cc2 >= 1 && verificacion < 2){
		printf("Ya todos los caballos pasaron la marca de la 10ma linea\nSe dara vuelta una carta, y el palo que salga retrocede un lugar\n");
		printf("Presione enter para seguir\n");
		while( getchar() != '\n' );
		generar_carta_linea(ce, co, cb, cc);
		*ver += 1;
	}
	if(ce3 >= 1 && co3 >= 1 && cb3 >= 1 && cc3 >= 1 && verificacion < 3){
		printf("Ya todos los caballos pasaron la marca de la 15va linea\nSe dara vuelta una carta, y el palo que salga retrocede un lugar\n");
		printf("Presione enter para seguir\n");
		while( getchar() != '\n' );
		generar_carta_linea(ce, co, cb, cc);
		*ver += 1;
	}
	if(ce4 >= 1 && co4 >= 1 && cb4 >= 1 && cc4 >= 1 && verificacion < 4){
		printf("Ya todos los caballos pasaron la marca de la 20va linea\nSe dara vuelta una carta, y el palo que salga retrocede un lugar\n");
		printf("Presione enter para seguir\n");
		while( getchar() != '\n' );
		generar_carta_linea(ce, co, cb, cc);
		*ver += 1;
	}
}

void cruzar_linea(int ce, int co, int cb, int cc, int *ce1, int *ce2, int *ce3, int *ce4, int *co1, int *co2, int *co3, int *co4, int *cb1, int *cb2, int *cb3, int *cb4, int *cc1, int *cc2, int *cc3, int *cc4){
	//La funcion busca la posicion de cada caballo, y se fija si ya todos pasaron alguna de las 4 lineas donde se debe dar vuelta una carta para retroceder.
	if(ce >= 4 && ce < 9) *ce1 += 1;
	else if(ce >= 9 && ce < 14) *ce2 += 1;
	else if(ce >= 14 && ce < 19) *ce3 += 1;
	else if(ce >= 19) *ce4 += 1;
	//Verifica si el caballo ya paso tal punto.
	if(co >= 4 && co < 9) *co1 += 1;
	else if(co >= 9 && co < 14) *co2 += 1;
	else if(co >= 14 && co < 19) *co3 += 1;
	else if(co >= 19) *co4 += 1;
	//Verifica si el caballo ya paso tal punto.
	if(cb >= 4 && cb < 9) *cb1 += 1;
	else if(cb >= 9 && cb < 14) *cb2 += 1;
	else if(cb >= 14 && cb < 19) *cb3 += 1;
	else if(cb >= 19) *cb4 += 1;
	//Verifica si el caballo ya paso tal punto.
	if(cc >= 4 && cc < 9) *cc1 += 1;
	else if(cc >= 9 && cc < 14) *cc2 += 1;
	else if(cc >= 14 && cc < 19) *cc3 += 1;
	else if(cc >= 19) *cc4 += 1;
}

void juego(char carrera[5][21], struct datos *jugador){
	//Abre el archivo de texto
	FILE *palos;
	palos = fopen("ganadores.txt", "w+");  
	//Si no logra abrir el archivo o este no existe tira error
	if(palos==NULL){
	fprintf(stderr, "\nERROR OPENED FILE\n");
	exit(1);
	}
	//Cada variable representa la posicion de cada caballo.
	int ce = 0, co = 0, cb = 0, cc = 0;
	//Estas variables chequean si cada caballo paso alguno de las cuatro lineas.
	int ce1 = 0, ce2 = 0, ce3 = 0, ce4 = 0, co1 = 0, co2 = 0, co3 = 0, co4 = 0, cb1 = 0, cb2 = 0, cb3 = 0, cb4 = 0, cc1 = 0, cc2 = 0, cc3 = 0, cc4 = 0;
	//Esta variable evita que se repita el evento de pasar un punto determinado
	int ver = 0;
	//c_count cuenta cuantos comodines salieron. Al salir 2, ya no pueden salir mas
	int c_count = 0;
	//El juego ocurre dentro de este while infinito.
	while(1){
		//Llama a la funcion que genera una carta aleatoria y hace avanzar a un caballo.
		generar_carta(&ce, &co, &cb, &cc, &c_count);
		//La funcion cruzar_linea se encarga de fijarse si algun caballo ya cruzo el punto de 5, 10, 15 o 20
		cruzar_linea(ce, co, cb, cc, &ce1, &ce2, &ce3, &ce4, &co1, &co2, &co3, &co4, &cb1, &cb2, &cb3, &cb4, &cc1, &cc2, &cc3, &cc4);
		//Llama a la funcion encargada de imprimir la matriz.
		imprimir_matriz(carrera, ce, co, cb, cc);
		//Si alguno de los caballos llega al final de la matriz(Matriz de 21 lugares) gana.
		if(ce == 20){
			//Pone la consola en color blanco
			{system("color 7");printf("Gana el caballo de espada!\n");}
			//Guarda en el archivo de texto el palo que gano la carrera.
			fputs("Espada\n", palos);
			return;
		}
		else if(co == 20){
			{system("color 7");printf("Gana el caballo de oro!\n");}
			fputs("Oro\n", palos);
			return;
		}
		else if(cb == 20){
			{system("color 7");printf("Gana el caballo de basto!\n");}
			fputs("Basto\n", palos);
			return;
		}
		else if(cc == 20){
			{system("color 7");printf("Gana el caballo de copa!\n");}
			fputs("Copa\n", palos);
			return;
		}
		//Esta funcion se fija si ya los caballos pasaron todos algun punto de los previamente nombrados.
		verificar_puntos(&ce, &co, &cb, &cc, &ver, ce1, ce2, ce3, ce4, co1, co2, co3, co4, cb1, cb2, cb3, cb4, cc1, cc2, cc3, cc4);
		//Espera tres segundos antes de empezar denuevo el loop
		Sleep(1500);
		//Limpia la consola de comando para que se vea mas limpio y sea mas comodo.
		system("cls");
		}
	}

	void imprimir_jugadores(struct datos *jugador){
		printf("Jugadores:\n----------\n");
		for(int i = 0; i < players; i++){
			//Imprime el nombre y apellido(si lo puso), el palo a que aposto y la apuesta de cada jugador.
			printf("%s%s%d\n\n", jugador[i].nom_apel, jugador[i].palo, jugador[i].apuesta);
		}
		//Imprime el pozo total acumulado.
		printf("Pozo: %d\n", pozo);
	}
	//Menu del juego
	void menu(struct datos *jugador, char carrera[5][21]){
	//menu sirve como una forma de elegir las opciones del menu.
	int menu;
	while(1){
		//Imprime en ASCII un cuadro que cubre al menu.
	 	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 201, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205);
	 	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205);
	 	printf("%c%c%c%c%c%c%c%c%c%c%c%c\n", 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 187);
	 	//Imprime las opciones del menu.
		printf("%cBienvenido Al juego de Carreras de Caballos\t   %c\n%c1- Ingresar Jugadores\t\t\t\t   %c\n%c2- Empezar Juego\t\t\t\t   %c\n%c3- Ver Reglas\t\t\t\t\t   %c\n%c4- Ver jugadores\t\t\t\t   %c\n%c5- Borrar jugadores\t\t\t\t   %c\n%c6- Salir del programa\t\t\t\t   %c\n", 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186);
		printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 200, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205);
	 	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205);
	 	printf("%c%c%c%c%c%c%c%c%c%c%c\n", 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 188);
	 	//Espera la entrada del usuario.
	 	scan:
		scanf("%d", &menu);
		printf("\n");
		switch(menu){
			//1 lleva al jugador a la funcion que ingresa los jugadores.
			case 1:
				system("cls");
				ingresar_jugadores(jugador);
				break;
			case 2:
				//2 lleva al jugador a la funcion principal donde ocurre el juego.
				system("cls");
				juego(carrera, jugador);
				break;
			case 3:
				//3 Imprime las reglas.
				system("cls");
				printf("------REGLAS-------\n");
				printf(" 1) Siempre hay cuatro caballos en juego, 1 de cada palo.\n 2) Para que un caballo avance, tiene que salir el palo de ese caballo(por ejemplo, si al voltear la carta sale basto, avanza el caballo de basto)\n 3) Gana el caballo que logre avanzar 21 lugares.\n 4)Cada 5 pasos, cuando todos los caballos hayan pasado ese punto se voltea una carta. El caballo que sea del palo que salio retrocede un lugar.\n 5) Si sale un comodin, la proxima carta a la que le toque avanzar subira dos casillas en vez de una.\n");
				printf("\n");
				break;
			case 4:
				//4 Imprime a todos los jugadores ingresados.
				system("cls");
				imprimir_jugadores(jugador);
				break;
			case 5:
				//5 Vacia la lista de jugadores.
				for(int i = 0; i < players; i++){
					//Vacia el nombre, palo y apuesta de cada estructura.
					memset(jugador[i].nom_apel, ' ', 100);
					memset(jugador[i].palo, ' ', 100);
					jugador[i].apuesta = 0;
				}
				//Vacia el pozo y pone valor 0 al contador de jugadores.
				pozo = 0;
				players = 0;
				system("cls");
				break;
			case 6:
				//6 Termina el programa.
				return;
				break;
			default:
				//Si el usuario ingresa cualquier otra cosa excepto lo indicado en pantalla no va a ocurrir nada.
				goto scan;
				break;
		}
	
	}
}

int main(void){
	//Pone una semilla con raiz time, asegurando que el numero generado siempre sea aleatorio.
	srand(time(NULL));
	//Crea la matriz que se va a imprimir con los caballos corriendo.	
	char carrera[5][21];
	//datos *jugadores = &jugador;
	llenar_matriz(carrera);
	//juego(carrera);
	menu(jugador, carrera);
}
