#include <iostream>
#include <ctype.h>
#include <map>
#include <string>
#include <stdlib.h>
#include <string.h>

using namespace std;

int main() {
    
    // Variables.
    string cadena = "";
    string palabra = "";
    string digito = "";
    
    bool palabraNormal = true;
    
    int estado = 0;
    int posicionPalabra = 0;
    int posicionDigito = 0;
    int largo = 0;

	string tokens[50] = {};
	int num_token = 0;
    
    // Ingreso de cadena.
    cout << "Ingresa la cadena a analizar: ";
    cin >> cadena;
    
    char *cadenaconver = strdup(cadena.c_str())
	
	for (int i = 0; i < cadena.length(); i++) {
		switch(estado){
			case 0:
                
                // Estado inicial.
                if (cadenaconver[i] == '+') {
                    estado = 1;
                    if(cadenaconver[i+1] == '+') {
                        estado = 2;
                    } else {
                        estado = 3;
                        i--;
                    }
                    
                } else if(cadenaconver[i] == '-') {
                  
                    estado = 4;
                    
                    if(cadenaconver[i+1] == '-') {
                        estado = 5;
                    } else {
                        estado = 6;
                        i--;
                    }
                    
                } else if (cadenaconver[i] == '*') {
                
                    estado = 7;
                    i--;
                
                } else if (cadenaconver[i] == '/') {
                    
                    estado = 8;
                    i--;
                
                } else if (cadenaconver[i] == '=') {
                    
                    estado = 9;
                    i--;
                    
                } else if (cadenaconver[i] == '<') {
                    
                    estado = 11;
                    i--;
                    
                } else if (cadenaconver[i] == '>') {
                    
                    estado = 15;
                    i--;
                    
                } else if (cadenaconver[i] == ':') {
                    
                    estado = 18;
                    i--;
                    
                } else if (cadenaconver[i] == ';') {
                    
                    estado = 20;
                    i--;
                    
                } else if (cadenaconver[i] == '(') {
                    
                    estado = 21;
                    i--;
                    
                } else if (cadenaconver[i] == ')') {
                    
                    estado = 22;
                    i--;
                    
                } else if (cadenaconver[i] == '"') {
                    
                    estado = 23;
                    i--;
                    
                } else if(isalpha(cadenaconver[i])) {
                    estado = 24;
                    posicionPalabra = i;
                    i--;
                } else if(isdigit(cadenaconver[i])) {
                    
                    estado = 26;
                    posicionDigito = i;
                    i--;
                    
                } else {
                    
                    cout << "Error" << endl;
                    
                }
                
                break;
                
                case 1:
                
                break;
            
            case 2:
                
                // Estado de aceptacion de incremento.
                cout << "Token: Incremento" << endl;
                
                tokens[num_token] = "incremento";
				num_token++; 
				for (i= 0; i< num_token; i++)cout<< tokens[i] << endl;
				
                estado = 0;
                break;
            
            case 3:
                
                // Estado de aceptación de suma.
                cout << "Token: Suma" << endl;
                
                tokens[num_token] = "suma";
				num_token++; 
				for (i= 0; i< num_token; i++)cout<< tokens[i] << endl;
				
                estado = 0;
                break;
                
            case 4:
                // Estado de recibió un '-' en estado 0.
                
                if(cadenaconver[i+1] == '-') {
					
                    estado = 5;
                } else {
                    
                    estado = 6;
                }
                
                break;
			
		}
	}
    
    cout << endl;
    return 1;
}
