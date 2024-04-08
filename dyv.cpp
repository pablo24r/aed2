#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <array>
#include <stdio.h>
#include <sys/time.h>
using namespace std;

int inicioMAX = 0; // Inicio de la subcadena más larga encontrada
int longitudMAX = 0; // Longitud de la subcadena más larga encontrada
bool fin = false; // Bandera para detener la búsqueda

// Función para imprimir la subcadena C
void imprimirSubcadena(const string& cadena, int inicio, int longitud) {
    cout << "Subcadena C: " << cadena.substr(inicio, longitud) << endl;
}

// Resolución directa para encontrar la subcadena más larga
array<int,2> resolver(string cadena, int p, int m){
    int inicioActual = p;
    int longitudActual = 1;
    int inicioMAXSubcadena = 0;
    int longitudMAXSubcadena = 0;
    int longitud = cadena.length();

    // Busca la subcadena más larga con caracteres consecutivos o iguales
    for (int i = 0; i < longitud - 1; ++i) {
        if (cadena[i] == cadena[i + 1] || cadena[i] + 1 == cadena[i + 1]) {
            longitudActual++;
        } else {
            if (longitudActual > longitudMAXSubcadena) {
                longitudMAXSubcadena = longitudActual;
                inicioMAXSubcadena = inicioActual;
            }
            longitudActual = 1;
            inicioActual = p+i + 1;
        }
    }

    // Verifica la última secuencia
    if (longitudActual > longitudMAXSubcadena) {
        longitudMAXSubcadena = longitudActual;
        inicioMAXSubcadena = inicioActual;
    }
    array<int, 2> solucion = {inicioMAXSubcadena, longitudMAXSubcadena};

    return solucion;
}

// Función para combinar dos subcadenas
void combinar(string cadenaA, string cadenaB, int p, int m){
    if (fin) return; // Si ya se encontró la subcadena más larga, no se realizan más combinaciones
    if(cadenaA[cadenaA.size()-1]  == cadenaB[0] || cadenaA[cadenaA.size()-1] + 1  == cadenaB[0] ){
        int inicioActual = p-1;
        int longitudActual = 2;
        // ¿Cuántos caracteres de la cadena A nos quedamos?
        int i = cadenaA.size()-1;
        while(cadenaA[i-1] == cadenaA[i] || cadenaA[i-1] + 1 == cadenaA[i]){
            inicioActual--;
            longitudActual++;
            i--;
        }
        // ¿Y de la cadena B?
        i=0;
        while(cadenaB[i] == cadenaB[i+1] || cadenaB[i] + 1 == cadenaB[i+1]){
            longitudActual++;
            i++;
        }
        // Si la longitud de la cadena actual supera la longitud máxima encontrada hasta ahora, se actualizan los valores
        if(longitudActual > longitudMAX){
            longitudMAX=longitudActual;
            inicioMAX=inicioActual;
        }
    }
    else return;
}

// Algoritmo de Dividir y Vencer (DyV) para encontrar la subcadena más larga
void dyv(string cadena, int p, int m){    
    if(longitudMAX>m){
        longitudMAX=m; // Limita la longitud máxima a m si se supera
        fin=true; // Indica que ya se encontró la subcadena más larga
    }
    
    if (fin) return; // Si ya se encontró la subcadena más larga, no se realiza más división y conquista

    int n = cadena.length();
    if( n/2 >= m){
        string primeraMitad = cadena.substr(0, n/2);
        string segundaMitad = cadena.substr(n/2);
        
        dyv(primeraMitad, p, m); // Llamada recursiva a la primera mitad
        dyv(segundaMitad, p+n/2, m); // Llamada recursiva a la segunda mitad
        combinar(primeraMitad,segundaMitad, p+n/2, m); // Intenta combinar las subcadenas de las mitades
    }
    else{
        array<int,2> solucion = resolver(cadena, p, m); // Resuelve el problema directamente para cadenas pequeñas
        // Verifica si la solución encontrada es mejor que la actual y actualiza los valores si es necesario
        if (solucion[1] > longitudMAX) {
            longitudMAX = solucion[1];
            inicioMAX = solucion[0];
        }
    }
}

int main(int argc, char *argv[]) {
    string cadena = argv[1]; // Cadena de entrada
    int longitud = cadena.length(); // Longitud de la cadena de entrada
    int m = longitud/1000; // Límite m para la longitud de la subcadena

    // Medición del tiempo de la operación
    struct timeval ti, tf;
    double tiempo;
    gettimeofday(&ti, NULL); // Instante inicial

    // Llamada al algoritmo DyV para encontrar la subcadena más larga
    dyv(cadena, 0, m);

    gettimeofday(&tf, NULL); // Instante final
    tiempo = (tf.tv_sec - ti.tv_sec) * 1000 + (tf.tv_usec - ti.tv_usec) / 1000.0; // Calcula el tiempo transcurrido en milisegundos
    printf("DyV ha tardado: %g milisegundos\n", tiempo); // Imprime el tiempo transcurrido

    // Muestra los resultados
    cout << "Posición inicial " << inicioMAX+1 << ": Longitud de la cadena: " << longitudMAX << endl;
    imprimirSubcadena(cadena, inicioMAX, longitudMAX); // Imprime la subcadena más larga

    return EXIT_SUCCESS;
}