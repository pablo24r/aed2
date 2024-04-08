#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <sys/time.h>
using namespace std;

// Función para imprimir la subcadena C
void imprimirSubcadena(const string& cadena, int inicio, int longitud) {
    cout << "Subcadena C: " << cadena.substr(inicio, longitud) << endl;
}

int main(int argc, char *argv[]) {
    int inicioMAX = 0; // Inicio de la subcadena más larga
    int longitudMAX = 0; // Longitud de la subcadena más larga
    int inicioActual = 0; // Inicio de la subcadena actual
    int longitudActual = 1; // Longitud de la subcadena actual

    string cadena = argv[1]; // Cadena de entrada
    int longitud = cadena.length(); // Longitud de la cadena de entrada
    int m=longitud/1000; // Límite m para la longitud de la subcadena
    // Medición del tiempo de la operación
    struct timeval ti, tf;
    double tiempo;
    gettimeofday(&ti, NULL); // Instante inicial


    // Busca la subcadena más larga con caracteres consecutivos o consecutivos en ASCII
    for (int i = 0; i < longitud - 1; ++i) {
        if (cadena[i] == cadena[i + 1] || cadena[i] + 1 == cadena[i + 1]) { // Comprueba si el carácter actual y el siguiente son iguales o consecutivos
            longitudActual++; // Incrementa la longitud de la subcadena actual
            if(longitudActual>m){ // Verifica si la longitud actual supera el límite m
                cout << "Posición inicial " << inicioMAX+1 << ": Longitud de la cadena: " << m << endl; // Imprime la posición inicial y la longitud máxima limitada a m
                imprimirSubcadena(cadena, inicioMAX, m); // Imprime la subcadena más larga limitada a m

                gettimeofday(&tf, NULL); // Instante final
                tiempo = (tf.tv_sec - ti.tv_sec) * 1000 + (tf.tv_usec - ti.tv_usec) / 1000.0; // Calcula el tiempo transcurrido en milisegundos
                printf("Directo ha tardado: %g milisegundos\n", tiempo); // Imprime el tiempo transcurrido
                return EXIT_SUCCESS; // Sale del programa con éxito
            }
        } 
        else {
            if (longitudActual > longitudMAX) { // Comprueba si la longitud actual es mayor que la longitud máxima
                longitudMAX = longitudActual; // Actualiza la longitud máxima
                inicioMAX = inicioActual; // Actualiza el inicio de la subcadena más larga
            }
            longitudActual = 1; // Reinicia la longitud actual
            inicioActual = i + 1; // Actualiza el inicio de la subcadena actual
        }
    }

    // Verifica la última secuencia
    if (longitudActual > longitudMAX) { // Comprueba si la longitud actual es mayor que la longitud máxima
        longitudMAX = longitudActual; // Actualiza la longitud máxima
        inicioMAX = inicioActual; // Actualiza el inicio de la subcadena más larga
    }

    gettimeofday(&tf, NULL); // Instante final
    tiempo = (tf.tv_sec - ti.tv_sec) * 1000 + (tf.tv_usec - ti.tv_usec) / 1000.0; // Calcula el tiempo transcurrido en milisegundos
    printf("Directo ha tardado: %g milisegundos\n", tiempo); // Imprime el tiempo transcurrido  

    // Imprime la posición inicial y la longitud de la subcadena más larga encontrada
    cout << "Posición inicial " << inicioMAX+1 << ": Longitud de la cadena: " << longitudMAX << endl;
    // Imprime la subcadena más larga encontrada
    imprimirSubcadena(cadena, inicioMAX, longitudMAX);

    return EXIT_SUCCESS; // Sale del programa con éxito
}
