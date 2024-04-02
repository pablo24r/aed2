#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// Función para imprimir la subcadena C
void imprimirSubcadena(const string& cadena, int inicio, int longitud) {
    cout << "Subcadena C: " << cadena.substr(inicio, longitud) << endl;
}

int main(int argc, char *argv[]) {
    int inicioMAX = 0;
    int longitudMAX = 0;
    int inicioActual = 0;
    int longitudActual = 1;

    string cadena = argv[1];
    int longitud = cadena.length();
    int m=longitud/1000;

    // Imprime la cadena generada
    // cout << "Cadena de longitud " << longitud << ": " << cadena << endl;

    // Busca la subcadena más larga con caracteres consecutivos o consecutivos en ASCII
    for (int i = 0; i < longitud - 1; ++i) {
        if (cadena[i] == cadena[i + 1] || cadena[i] + 1 == cadena[i + 1]) {
            longitudActual++;
                // Si la longitud de la cadena actual es igual a m, puedo acabar (mejor caso)
                if(longitudActual>m){
                    cout << "Posición inicial " << inicioMAX+1 << ": Longitud de la cadena: " << m << endl;
                    imprimirSubcadena(cadena, inicioMAX, m);
                    return EXIT_SUCCESS;
            }
        } 
        else {
            if (longitudActual > longitudMAX) {
                longitudMAX = longitudActual;
                inicioMAX = inicioActual;
            }
            longitudActual = 1;
            inicioActual = i + 1;
        }
    }

    // Verifica la última secuencia
    if (longitudActual > longitudMAX) {
        longitudMAX = longitudActual;
        inicioMAX = inicioActual;
    }

    cout << "Posición inicial " << inicioMAX+1 << ": Longitud de la cadena: " << longitudMAX << endl;
    imprimirSubcadena(cadena, inicioMAX, longitudMAX);

    return EXIT_SUCCESS;
}

