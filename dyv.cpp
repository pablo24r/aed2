#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <array>
using namespace std;

int inicioMAX = 0;
int longitudMAX = 0;

// Función para generar la cadena aleatoria
string generarCadenaAleatoria(int longitud) {
    srand(time(NULL));
    // Alfabeto
    string alfabeto = "abcdefghijklmnopqrstuvwxyz";
    int tamAlfabeto = alfabeto.length();

    // Genera la cadena aleatoria
    string cadena;
    cadena.reserve(longitud);
    for (int i = 0; i < longitud; ++i) {
        cadena.push_back(alfabeto[rand() % tamAlfabeto]);
    }

    return cadena;
}

// Función para imprimir la subcadena C
void imprimirSubcadena(const string& cadena, int inicio, int longitud) {
    cout << "Subcadena C: " << cadena.substr(inicio, longitud) << endl;
}


// Resolucion
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
            inicioActual = i + 1;
        }
    }

    // Verifica la última secuencia
    if (longitudActual > longitudMAXSubcadena) {
        longitudMAXSubcadena = longitudActual;
        inicioMAXSubcadena = inicioActual;
    }
    array<int, 2> solucion = {inicioMAXSubcadena, longitudMAXSubcadena};

    cout << "Cadena: " << cadena << endl;
    cout << "\tSolución: " << inicioMAXSubcadena+1 << "-" << longitudMAXSubcadena << endl;
    imprimirSubcadena(cadena,inicioMAXSubcadena, longitudMAXSubcadena);
    return solucion;
}


// Dyv
void dyv(string cadena, int p, int m){
	int n = cadena.length();
    
    if( n/2 >= m){
        string primeraMitad = cadena.substr(0, n/2);
        string segundaMitad = cadena.substr(n/2);
        
        // Imprimir las dos mitades
        cout << "Primera mitad: " << primeraMitad << endl;
        cout << "Segunda mitad: " << segundaMitad << endl;
        dyv(primeraMitad, p, m);
        dyv(segundaMitad, n/2, m);
    }
    else{
        resolver(cadena, p, m);
    }


}

int main(int argc, char *argv[]) {


    // Verifica que se haya pasado un argumento para la longitud de la cadena
    if (argc != 2) {
        cerr << "Uso: " << argv[0] << " <longitud>" << endl;
        return EXIT_FAILURE;
    }

    // Obtiene la longitud de la cadena desde el argumento de línea de comandos
    int longitud = atoi(argv[1]);

    // Verifica que la longitud sea válida
    if (longitud <= 0) {
        cerr << "La longitud debe ser un número entero positivo." << endl;
        return EXIT_FAILURE;
    }

    // Genera la cadena aleatoria
    string cadena = generarCadenaAleatoria(longitud);
    int m = 50;//longitud/1000;
    
    // Imprime la cadena generada
    cout << "Cadena de longitud " << longitud << ": " << cadena << endl;

    // Dyv
    dyv(cadena, 0, m);

    // Mostrar resultados
    cout << "Posición inicial " << inicioMAX+1 << ": Longitud de la cadena: " << longitudMAX << endl;
    imprimirSubcadena(cadena, inicioMAX, longitudMAX);

    return EXIT_SUCCESS;
}

