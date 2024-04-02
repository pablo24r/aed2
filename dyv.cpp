#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <array>
using namespace std;

int inicioMAX = 0;
int longitudMAX = 0;
bool fin = false;

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

// Combinar
void combinar(string cadenaA, string cadenaB, int p, int m){
    if (fin) return;
    if(cadenaA[cadenaA.size()-1]  == cadenaB[0] || cadenaA[cadenaA.size()-1] + 1  == cadenaB[0] ){
        //cout << "COMBINA: " << cadenaA << " + " << cadenaB << endl;
        int inicioActual = p-1;
        int longitudActual = 2;
        // ¿Cuantos caracteres de la cadena A nos quedamos?
        int i = cadenaA.size()-1;
        //cout << cadenaA[i-1] << " - " << cadenaA[i] << endl;
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
        if(longitudActual > longitudMAX){
            longitudMAX=longitudActual;
            inicioMAX=inicioActual;
        }
    }
    else return;
}


// Dyv
void dyv(string cadena, int p, int m){    
    if(longitudMAX>m){
        longitudMAX=m;
        fin=true;
    }
    
    if (fin) return;

    int n = cadena.length();
    if( n/2 >= m){
        string primeraMitad = cadena.substr(0, n/2);
        string segundaMitad = cadena.substr(n/2);
        
        dyv(primeraMitad, p, m);
        dyv(segundaMitad, p+n/2, m);
        combinar(primeraMitad,segundaMitad, p+n/2, m);
    }
    else{
        array<int,2> solucion = resolver(cadena, p, m);
        // Verifica si es la mejor
        if (solucion[1] > longitudMAX) {
            longitudMAX = solucion[1];
            inicioMAX = solucion[0];
        }
    }


}

int main(int argc, char *argv[]) {

    string cadena = argv[1];
    int longitud = cadena.length();
    int m = longitud/1000;
    
    // Imprime la cadena generada
    // cout << "Cadena de longitud " << longitud << ": " << cadena << endl;

    // Dyv
    dyv(cadena, 0, m);

    // Mostrar resultados
    cout << "Posición inicial " << inicioMAX+1 << ": Longitud de la cadena: " << longitudMAX << endl;
    imprimirSubcadena(cadena, inicioMAX, longitudMAX);

    return EXIT_SUCCESS;
}
