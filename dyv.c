#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Función para generar la cadena aleatoria
char* generarCadenaAleatoria(int longitud) {
    // Alfabeto
    char alfabeto[] = "abcdefghijklmnopqrstuvwxyz";
    int tamAlfabeto = sizeof(alfabeto) - 1; // -1 para excluir el carácter nulo

    // Reserva memoria para la cadena
    char* cadena = (char*)malloc((longitud + 1) * sizeof(char)); // +1 para el carácter nulo al final
    if (cadena == NULL) {
        printf("Error: No se pudo asignar memoria.\n");
        exit(EXIT_FAILURE);
    }

    // Genera la cadena aleatoria
    srand(time(NULL)); // Inicializa la semilla del generador de números aleatorios
    for (int i = 0; i < longitud; i++) {
        cadena[i] = alfabeto[rand() % tamAlfabeto]; // Selecciona un carácter aleatorio del alfabeto
    }
    cadena[longitud] = '\0'; // Agrega el carácter nulo al final de la cadena

    return cadena;
}

// Función para imprimir la subcadena C
void imprimirSubcadena(char A[], int inicio, int longitud) {
    printf("Subcadena C: ");
    for (int i = inicio; i < inicio + longitud; i++) {
        printf("%c", A[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
	int inicioMAX=0;
	int longitudMAX=0;

	int inicioActual=0;
	int longitudActual=1;

    // Verifica que se haya pasado un argumento para la longitud de la cadena
    if (argc != 2) {
        printf("Uso: %s <longitud>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Obtiene la longitud de la cadena desde el argumento de línea de comandos
    int longitud = atoi(argv[1]);
	int m=longitud;
    
    // Verifica que la longitud sea válida
    if (longitud <= 0) {
        printf("La longitud debe ser un número entero positivo.\n");
        return EXIT_FAILURE;
    }

    // Genera la cadena aleatoria
    char* cadena = generarCadenaAleatoria(longitud);

    // Imprime la cadena generada
    printf("Cadena de longitud %d: %s\n", longitud, cadena);
    

    for (int i=0; i< longitud; i++){
    	/*if( longitudMAX > m || longitud - i < longitudMAX ){
    		break;
    	}*/
    	if( cadena[i] == cadena[i+1] || cadena[i] + 1 == cadena[i+1] ){
    		longitudActual++;
    		//printf("1:%c,2:%c\n",cadena[i],cadena[i+1]); Descomentar para ver que funciona bien
    	}
    	else{
    		if(longitudActual > longitudMAX){
    			longitudMAX = longitudActual;
    			inicioMAX = inicioActual;
    		}
    		longitudActual=1;
    	    	inicioActual=i+1;
    	}
    }
    printf("Posicion inicial %d: longitud de la cadena: %d\n", inicioMAX+1, longitudMAX);
    imprimirSubcadena(cadena, inicioMAX, longitudMAX);

    // Libera la memoria reservada para la cadena
    free(cadena);

    return EXIT_SUCCESS;
}

