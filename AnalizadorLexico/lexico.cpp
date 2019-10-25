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
#include <stdlib.h>
#include <string.h>

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

	string tokens[50] = {};
	
	int num_token = 0;
    
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
                    //i--;
                    
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
                    
                    cout << "Error lexico" << endl;
                    
                }
                
                break;
                
            case 1:
                
                break;
            
            case 2:
                
                // Estado de aceptación de incremento.
                cout << "Token: Incremento" << endl;
                tokens[num_token] = "incremento";
				num_token++; 
                estado = 0;
                break;
            
            case 3:
                
                // Estado de aceptación de suma.
                cout << "Token: Suma" << endl;
                
                tokens[num_token] = "suma";
				num_token++;
                estado = 0;
                break;
                
            case 4:
                // Estado de recibió un '-' en estado 0.
                
                if(cadenaconver[i+1] == '-') {
                	
                	cout << "Token: Decremento" << endl;
					tokens[num_token] = "decremento";
					num_token++; 
                    estado = 5;
                    
                } else {
                	
                	cout << "Token: Resta" << endl;
                    tokens[num_token] = "resta";
					num_token++; 
                    estado = 6;
                    
                }
                
                break;
                
            case 5:
                
                // Estado de aceptación de decremento.
                cout << "Token: Decremento" << endl;
                tokens[num_token] = "decremento";
				num_token++; 
                estado = 0;
                break;
                
            case 6:
                
                // Estado de aceptación de resta.
                cout << "Token: Resta" << endl;
                tokens[num_token] = "resta";
				num_token++; 
                estado = 0;
                break;
            
            case 7:
                
                // Estado de aceptacion multiplicación.
                cout << "Token: Multiplicacion" << endl;
                tokens[num_token] = "multiplicacion";
				num_token++; 
                estado = 0;
                break;
                
            case 8:
                
                // Estado de aceptación de división.
                cout << "Token: Division" << endl;
                tokens[num_token] = "division";
				num_token++; 
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
                tokens[num_token] = "igualacion";
				num_token++; 
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
                tokens[num_token] = "diferente";
				num_token++; 
                estado = 0;
                break;
                
            case 13:
                
                cout << "Token: Menor o Igual" << endl;
                tokens[num_token] = "menor o igual que";
				num_token++; 
                estado = 0;
                break;
                
            case 14:
                
                cout << "Token: Menor que" << endl;
                tokens[num_token] = "menor que";
				num_token++; 
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
                tokens[num_token] = "mayor que";
				num_token++; 
                estado = 0;
                break;
            
            case 17:
                
                cout << "Token: Mayor o Igual" << endl;
                tokens[num_token] = "mayor o igual que";
				num_token++; 
                estado = 0;
                break;
                
            case 18:
                
                if (cadenaconver[i+1] == '=') {
                    estado = 19;
                }
                
            case 19:
                
                cout << "Token: Asignacion" << endl;
                tokens[num_token] = "asignacion";
				num_token++;
                estado = 0;
                break;
                
            case 20:
                
                cout << "Token: Cierre" << endl;
                tokens[num_token] = "cierre";
				num_token++; 
                estado = 0;
                break;
                
            case 21:
                
                cout << "Token: Parentesis Abre" << endl;
                tokens[num_token] = "parentesis abre";
				num_token++; 
                estado = 0;
                break;
            
            case 22:
                
                cout << "Token: Parentesis Cierra" << endl;
                tokens[num_token] = "parentesis cierra";
				num_token++; 
                estado = 0;
                break;
            
            case 23:
                
                cout << "Token: Comilla" << endl;
                tokens[num_token] = "comilla";
				num_token++; 
                estado = 0;
                break;
            
            case 24:
                
                if(cadena.length()==1){
                	
                	cout << "Token: Identificador" << endl;
                    tokens[num_token] = "identificador";
					num_token++;
					palabra = ""; 
                    estado = 0;
                    
				} else if(isalpha(cadenaconver[i+2]) or isdigit(cadenaconver[i+2])) {
					
                    estado = 24;
                    
                } else {
                	
                    estado = 25;
                } 
                
                break;
            
            case 25:
                
                for (int j = posicionPalabra; j < i+1; j++) {
                    
                    palabra = palabra + cadenaconver[j];
                
                    if(palabra == "si") {
                        
						cout << "Token: Palabra Reservada si" << endl;
                        tokens[num_token] = "si";
						num_token++; 
                        palabra = "";
                        palabraNormal = false;

                    } else if(palabra == "cuandono") {
                    	
                        cout << "Token: Palabra Reservada cuandono" << endl;
                        tokens[num_token] = "cuandono";
						num_token++; 
                        palabra = "";
                        palabraNormal = false;
                        
                    } else if(palabra == "entonces") {
                    	
                        cout << "Token: Palabra Reservada entonces" << endl;
                        
                        tokens[num_token] = "entonces";
						num_token++; 
                        palabra = "";
                        palabraNormal = false;
                        
                    } else if(palabra == "escribir") {
                    	
                        cout << "Token: Palabra Reservada escribir" << endl;
                        tokens[num_token] = "escribir";
						num_token++; 
                        palabra = "";
                        palabraNormal = false;
                        
                    } else if(palabra == "leer") {
                        cout << "Token: Palabra Reservada leer" << endl;
                        tokens[num_token] = "leer";
						num_token++; 
                        palabra = "";
                        palabraNormal = false;
                    } else if(palabra == "comienzo") {
                        cout << "Token: Palabra Reservada comienzo" << endl;
                        tokens[num_token] = "comienzo";
						num_token++; 
                        palabra = "";
                        palabraNormal = false;
                    } else if(palabra == "fin") {
                        cout << "Token: Palabra Reservada fin" << endl;
                        tokens[num_token] = "fin";
						num_token++; 
                        palabra = "";
                        palabraNormal = false;
                    } else if(palabra == " ") {
                        palabraNormal = true;
                    } else{
                        palabraNormal = true;
                    }
                    
                }
            
                if(palabraNormal) {
                        
                    if(palabra[0] != '_' ) {        // and isdigit(palabra.at(0)
                        cout << "Token: Identificador: " << palabra << endl;
                        tokens[num_token] = "identificador";
						num_token++; 
						palabra = "";
                        estado = 0;
                    } else {
                        cout << "Token: Cadena (" << palabra << ")" << endl;
                        tokens[num_token] = "cadena";
                        palabra = "";
					num_token++; 
                        estado = 0;
                    }
                        
                    // var hola entonces
                }
    
                break;
    
            case 26:
                
                if(isdigit(cadenaconver[i+1])) {
                    estado = 26;
                    digito = digito + cadenaconver[i];
                    //cout << "Estado 26" << endl;
                } else if(isdigit(cadenaconver[i])) {
                    digito = digito + cadenaconver[i];
                    estado = 27;
                    i--;
                    //cout << "Estado 26.1" << endl;
                }
                
                break;
                
            case 27:
                
                largo = digito.length();
                
//                for(int j = 0; j <= largo; j++) {
//                    digito = digito + cadenaconver[j];
//                    cout << "Iteracion numero: " << j << endl;

//                }
                
                cout << "Token: Digito " << digito << endl;
                tokens[num_token] = "digito";
				num_token++; 
				digito = "";
				estado = 0;
				
                break;
        
            default:
                break;
        }
    }

    string lineacod[100] = {};


    
    //for (int k= 0; k< num_token; k++) cout<< tokens[k] << endl;
		
    //Declaración
    for( int l=0; l< num_token; l++ ){
    	if(tokens[l] == "identificador"){
    		if(tokens[l+1] == "asignacion"){
    			if(tokens[l+2] == "digito"){
    				if(tokens[l+3] == "cierre"){
    					cout << "Declaracion de variable" << endl;
                        lineacod[l] = "asignacion";
					}
				}
			}
    		
		} else if (tokens[l] == "digito" | tokens[l] == "identificador") {
            if(tokens[l+1] == "suma" | tokens[1+1] == "resta"){
                if(tokens[l+2] == "digito" | tokens[l] == "identificador"){
                    cout << "Expresion";
                    lineacod[l] = "expresion";
                }
            }
        }
	}

    return 1;
}
