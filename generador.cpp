#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cerr << "Uso: " << argv[0] << " <caso (m, M, p)>" << " <longitud de la cadena> " << endl;
        return 1; // Devuelve un código de error
    }

    char letra = argv[1][0]; // Obtén el primer carácter del argumento
    int longitud = atoi(argv[2]);
    int m = longitud/1000;
    srand(time(NULL));
    string cadena = "";
    switch (letra) {
        case 'm':{ // Caso mejor
            for (int i = 0; i < longitud; ++i) {
                cadena.push_back('a');
            }
            cout << cadena << endl;
            break;  
        }   
        case 'M': // Caso peor
            cout << "La letra ingresada es una 'M'." << endl;
            break;
        
        case 'p':{ // Caso promedio (cadena aleatoria)
            string alfabeto = "abcdefghijklmnopqrstuvwxyz";
            int tamAlfabeto = alfabeto.length();
            cadena.reserve(longitud);
            for (int i = 0; i < longitud; ++i) {
                cadena.push_back(alfabeto[rand() % tamAlfabeto]);
            }
            cout << cadena << endl;
            break;
        } 
        default:
            cout << "La letra ingresada no es ni 'm', 'M' ni 'p'." << endl;
            break;
    }

    return 0; 
}
