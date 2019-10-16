//
//  lexico.cpp
//  AnalizadorSintáctico.
//
//  Created by Alejandro Vazquez on 10/4/19.
//  Copyright © 2019 Alejandro Vazquez. All rights reserved.
//

#include "lexico.hpp"
#include <iostream>
#include <ctype.h>
#include <map>
#include <string>

using namespace std;

int main() {
    
    // Variables básicas.
    string cadena = "";
    string palabra = "";
    string digito = "";
    
    bool palabraNormal = true;
    
    int estado = 0;
    int posicionPalabra = 0;
    int posicionDigito = 0;
    int largo = 0;
    
    // Ingreso de cadena.
    cout << "Ingresa la cadena a analizar: ";
    cin >> cadena;
    
    char *cadenaconver = strdup(cadena.c_str());
    
    for (int i = 0; i < cadena.length(); i++) {
        
        switch (estado) {
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
                
                // Estado de aceptación de incremento.
                cout << "Token: Incremento" << endl;
                estado = 0;
                break;
            
            case 3:
                
                // Estado de aceptación de suma.
                cout << "Token: Suma" << endl;
                estado = 0;
                break;
                
            case 4:
                // Estado de recibió un '-' en estado 0.
                
                if(cadenaconver[i+1] == '-') {
                    cout << "Token: Decremento";
                    estado = 0;
                } else {
                    cout << "Token Resta";
                    estado = 0;
                }
                
                break;
                
            case 5:
                
                // Estado de aceptación de decremento.
                cout << "Token: Decremento" << endl;
                estado = 0;
                break;
                
            case 6:
                
                // Estado de aceptación de resta.
                cout << "Token: Resta" << endl;
                estado = 0;
                break;
            
            case 7:
                
                // Estado de aceptacion multiplicación.
                cout << "Token: Multiplicación" << endl;
                estado = 0;
                break;
                
            case 8:
                
                // Estado de aceptación de división.
                cout << "Token: División" << endl;
                estado = 0;
                break;
                
            case 9:
                
                // Si cuenta con un '='.
                if(cadenaconver[i+1] == '=') {
                    estado = 10;
                }
                
                break;
            
            case 10:
                
                // Estado de acpetación de la igualación;
                cout << "Token: Igualacion" << endl;
                estado = 0;
                break;
                
            case 11:
                
                // Si tiene "=" o "<".
                if(cadenaconver[i+1] == '=') {
                    estado = 13;
                } else if(cadenaconver[i+1] == '>') {
                    estado = 12;
                } else  {
                    estado = 14;
                    i--;
                }
                
                break;
            
            case 12:
                
                cout << "Token: Diferente" << endl;
                estado = 0;
                break;
                
            case 13:
                
                cout << "Token: Menor o Igual" << endl;
                estado = 0;
                break;
                
            case 14:
                
                cout << "Token: Menor que" << endl;
                estado = 0;
                break;
                
            case 15:
                
                if (cadenaconver[i+1] == '=') {
                    estado = 17;
                    i--;
                } else  {
                    estado = 16;
                    i--;
                }
                
                break;
                
            case 16:
                
                cout << "Token: Mayor que" << endl;
                estado = 0;
                break;
            
            case 17:
                
                cout << "Token: Mayor o Igual" << endl;
                estado = 0;
                break;
                
            case 18:
                
                if (cadenaconver[i+1] == '=') {
                    estado = 19;
                }
                
            case 19:
                
                cout << "Token: Asignacion" << endl;
                estado = 0;
                break;
                
            case 20:
                
                cout << "Token: Cierre" << endl;
                estado = 0;
                break;
                
            case 21:
                
                cout << "Token: Parentesis Abre" << endl;
                estado = 0;
                break;
            
            case 22:
                
                cout << "Token: Parentesis Cierra" << endl;
                estado = 0;
                break;
            
            case 23:
                
                cout << "Token: Comilla" << endl;
                estado = 0;
                break;
            
            case 24:
                
                if(isalpha(cadenaconver[i+1]) and isalpha(cadenaconver[i+2])) {
                    estado = 24;
                } else if(isalpha(cadenaconver[i+1]) or cadena.length() == 1) {
                    estado = 25;
                }
                
                break;
            
            case 25:
                
                for (int j = posicionPalabra; j < i+1; j++) {
                    
                    palabra = palabra + cadenaconver[j];
                
                    if(palabra == "si") {
                        cout << "Token: Palabra Reservada si" << endl;
                        palabra = "";
                        palabraNormal = false;
                    } else if(palabra == "cuandono") {
                        cout << "Token: Palabra Reservada cuandono" << endl;
                        palabra = "";
                        palabraNormal = false;
                    } else if(palabra == "entonces") {
                        cout << "Token: Palabra Reservada entonces" << endl;
                        palabra = "";
                        palabraNormal = false;
                    } else if(palabra == "escribir") {
                        cout << "Token: Palabra Reservada escribir" << endl;
                        palabra = "";
                        palabraNormal = false;
                    } else if(palabra == "leer") {
                        cout << "Token: Palabra Reservada leer" << endl;
                        palabra = "";
                        palabraNormal = false;
                    } else if(palabra == "comienzo") {
                        cout << "Token: Palabra Reservada comienzo" << endl;
                        palabra = "";
                        palabraNormal = false;
                    } else if(palabra == "fin") {
                        cout << "Token: Palabra Reservada fin" << endl;
                        palabra = "";
                        palabraNormal = false;
                    } else if(palabra == " ") {
                        palabraNormal = true;
                    } else if(isdigit(palabra[j])) {
                        estado = 0;
                        i--;
                    } else {
                        palabraNormal = true;
                    }
                    
                }
            
                if(palabraNormal) {
                    
                    if(palabra[0] == 'v' and palabra[1] == 'a' and palabra[2] == 'r' and palabra[3] == ' ') {
                        
                        cout << "Token: Identificador" << endl;
                        estado = 0;
                    
                    } else {
                        
                        if(palabra[0] != '_' ) {        // and isdigit(palabra.at(0)
                            cout << "Token: Identificador: " << palabra << endl;
                            estado = 0;
                        } else {
                            cout << "Token: Cadena (" << palabra << ")" << endl;
                            estado = 0;
                        }
                        
                        
                    }
                    // var hola entonces
                }
    
                break;
    
            case 26:
                
                if(isdigit(cadenaconver[i+1])) {
                    estado = 26;
                    digito = digito + cadenaconver[i];
                    cout << "Estado 26" << endl;
                } else if(isdigit(cadenaconver[i])) {
                    digito = digito + cadenaconver[i];
                    estado = 27;
                    i--;
                    cout << "Estado 26.1" << endl;
                }
                
                break;
                
            case 27:
                
                largo = digito.length();
                
//                for(int j = 0; j <= largo; j++) {
//                    digito = digito + cadenaconver[j];
//                    cout << "Iteracion numero: " << j << endl;
//                }
                
                cout << "Token: Dígito " << digito << endl;
                break;
        
            default:
                break;
        }
    }
    
    cout << endl;
    return 1;
}