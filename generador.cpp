#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    // Verifica si se proporcionan los argumentos correctos
    if (argc != 3) {
        cerr << "Uso: " << argv[0] << " <caso (m, M, p)>" << " <longitud de la cadena> " << endl;
        return 1; // Devuelve un código de error
    }

    // Obtiene el primer carácter del argumento para determinar el caso
    char letra = argv[1][0]; 

    // Convierte la longitud de la cadena de entrada a un entero
    int longitud = atoi(argv[2]);

    // Calcula el límite m para la longitud de la subcadena
    int m = longitud/1000;

    // Inicializa el generador de números aleatorios
    srand(time(NULL));

    // Cadena de caracteres donde se almacenará la cadena generada
    string cadena;

    // Selecciona el caso según la letra ingresada
    switch (letra) {
        case 'm':{ // Caso mejor
            // Genera una cadena de longitud 'longitud' con caracteres 'a'
            for (int i = 0; i < longitud; ++i) {
                cadena.push_back('a');
            }
            cout << cadena << endl; // Imprime la cadena generada
            break;  
        }   
        case 'M':{ // Caso peor
            // Genera una cadena aleatoria de longitud 'longitud' - (longitud/1000)
            // y luego completa la cadena con caracteres 'a' hasta alcanzar la longitud deseada
            string alfabeto = "abcdefghijklmnopqrstuvwxyz";
            int tamAlfabeto = alfabeto.length();
            cadena.reserve(longitud); // Reserva espacio en memoria para optimizar el rendimiento
            for (int i = 0; i < longitud-(longitud/1000); ++i) {
                cadena.push_back(alfabeto[rand() % tamAlfabeto]);
            }
            for (int i = longitud-(longitud/1000); i < longitud; ++i) {
                cadena.push_back('a');
            }
            cout << cadena << endl; // Imprime la cadena generada
            break;
        }             
        case 'p':{ // Caso promedio (cadena aleatoria)
            // Genera una cadena aleatoria de longitud 'longitud'
            string alfabeto = "abcdefghijklmnopqrstuvwxyz";
            int tamAlfabeto = alfabeto.length();
            cadena.reserve(longitud); // Reserva espacio en memoria para optimizar el rendimiento
            for (int i = 0; i < longitud; ++i) {
                cadena.push_back(alfabeto[rand() % tamAlfabeto]);
            }
            cout << cadena << endl; // Imprime la cadena generada
            break;
        } 
        default:
            cout << "La letra ingresada no es ni 'm', 'M' ni 'p'." << endl; // Mensaje de error si la letra no es válida
            break;
    }

    return 0; // Sale del programa con éxito
}
