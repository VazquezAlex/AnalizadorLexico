//  lexico.cpp
//  AnalizadorSintáctico.
//
//  Created by Alejandro Vazquez on 10/4/19.
//  Copyright © 2019 Alejandro Vazquez. All rights reserved.
//

// TODO: Que acepte strings
// TODO: Que pueda realizar asignaciones sin el tipo de dato.


#include "lexico.hpp"
#include <iostream>
#include <ctype.h>
#include <map>
#include <string>
#include <stdlib.h>
#include <string.h>

#include<fstream>

using namespace std;

// Declaració de funciones.
bool declaracion(int num_token, string tokens[50][2]);
bool si(string tokens[50][2], int num_token);
bool mientras(string tokens[50][2], int num_token);
bool asignacion(string tokens[50][2], int num_token);

string variables[100][2] = {};
int num_variables = 0;

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

	string tokens[50][2] = {}; // [condicion, ==] [identificador, hola]
	string tokens_verificar[50][2] = {};


	int num_token = 0;
	int num_tokens_verificar = 0;

	
	// // Ingreso de cadena.
	// cout << "Ingresa la cadena a analizar: ";
	// cin >> cadena;
	
	ifstream myReadFile;
	myReadFile.open("codigo.txt");
	char output[100];

	// Leer el archivo de codigo.
	if (myReadFile.is_open()) {
		string s;
		while (!myReadFile.eof()) {
			while(getline(myReadFile, s)) {
				cadena += s + "\n";
			}
			// cout << cadena;
		}
	}

	// Convertir la cadena para trabajarla en cada caracter.
	// char *cadena = strdup(cadena.c_str());
	
	// Ciclo para analizar cada caracter de cadena.
	for (int i = 0; i < cadena.length(); i++) {
		
		switch (estado) {
			case 0:
				
				// Estado inicial.
				if (cadena[i] == '+') {
					estado = 1;
					if(cadena[i+1] == '+') {
						// Mandar a estado de aceptación de incremento (Estado 2).
						estado = 2;
					} else {
						// Mandar a estado de suma, y regresar la cadena una posición.
						estado = 3;
						i--;
					}
				} else if(cadena[i] == '-') {
					estado = 4;
					if(cadena[i+1] == '-') {
						estado = 5;
					} else {
						estado = 6;
						i--;
					}
				} else if (cadena[i] == '*') {
					estado = 7;
					i--;
				} else if (cadena[i] == '/') {                  
					estado = 8;
					i--;                
				} else if (cadena[i] == '=') { 
					estado = 9;
					i--;  
				} else if (cadena[i] == '<') {
					estado = 11;
					i--;
				} else if (cadena[i] == '>') {
					estado = 15;
					i--;					
				} else if (cadena[i] == ':') {
					estado = 18;
				} else if (cadena[i] == ';') {
					estado = 20;
					i--;
				} else if (cadena[i] == '(') {
					estado = 21;
					i--;
				} else if (cadena[i] == ')') {
					estado = 22;
					i--;
				} else if (cadena[i] == '"') {
					estado = 23;
					i--;
				} else if(cadena[i] == '{') {
					// cout << "Token: Llave Abre" << endl;
					tokens[num_token][0] = "llave_abre";
					tokens[num_token][1] = "{";
					num_token++;
				}  else if(cadena[i] == '}') {
					// cout << "Token: Llave Cierra" << endl;
					tokens[num_token][0] = "llave_cierra";
					tokens[num_token][1] = "}";
					num_token++;
				}  else if(isalpha(cadena[i])) {
					estado = 24;
					posicionPalabra = i;
					i--;
				} else if(isdigit(cadena[i])) {
					estado = 26;
					posicionDigito = i;
					i--;
				} else if(cadena[i] == ' ' | cadena[i] == '\n' | cadena[i] == '	' ) {
					//cout << "Se encontró espacio" << endl;
				} else {
					cout << "Error lexico" << endl;                    
				}
				
				break;
				
			case 1:
				
				break;
			
			case 2:
				// Estado de aceptación de incremento.
				// cout << "Token: Incremento" << endl;
				tokens[num_token][0] = "incremento";
				tokens[num_token][1] = "++";
				num_token++; 
				estado = 0;
			case 3:
				// Estado de aceptación de suma.
				// cout << "Token: Suma" << endl;
				tokens[num_token][0] = "suma";
				tokens[num_token][1] = "+";
				num_token++;
				estado = 0;
				break;
			case 4:
				// Estado de recibió un '-' en estado 0.
				if(cadena[i+1] == '-') {
					// cout << "Token: Decremento" << endl;
					tokens[num_token][0] = "decremento";
					tokens[num_token][1] = "--";
					num_token++; 
					estado = 5;
				} else {
					// cout << "Token: Resta" << endl;
					tokens[num_token][0] = "resta";
					tokens[num_token][1] = "-";
					num_token++; 
					estado = 6;
				} 
				break;
				
			case 5:
				// Estado de aceptación de decremento.
				// cout << "Token: Decremento" << endl;
				tokens[num_token][0] = "decremento";
				tokens[num_token][1] = "--";
				num_token++; 
				estado = 0;
				break;
				
			case 6:
				// Estado de aceptación de resta.
				// cout << "Token: Resta" << endl;
				tokens[num_token][0] = "resta";
				tokens[num_token][1] = "-";
				num_token++; 
				estado = 0;
				break;
			
			case 7:
				// Estado de aceptacion multiplicación.
				// cout << "Token: Multiplicacion" << endl;
				tokens[num_token][0] = "multiplicacion";
				tokens[num_token][1] = "*";
				num_token++; 
				estado = 0;
				break;
				
			case 8:
				// Estado de aceptación de división.
				// cout << "Token: Division" << endl;
				tokens[num_token][0] = "division";
				tokens[num_token][1] = "/";
				num_token++; 
				estado = 0;
				break;
				
			case 9:
				// Si cuenta con un '='.
				if(cadena[i+1] == '=') {
					estado = 10;
				}
				
				break;
			
			case 10:
				// Estado de acpetación de la igualación;
				// cout << "Token: Comparacion" << endl;
				tokens[num_token][0] = "condicion";
				tokens[num_token][1] = "==";
				num_token++; 
				estado = 0;
				break;
				
			case 11:
				// Si tiene "=" o "<".
				if(cadena[i+1] == '=') {
					estado = 13;
				} else if(cadena[i+1] == '>') {
					estado = 12;
				} else  {
					estado = 14;
					i--;
				}
				
				break;
			
			case 12:
				// cout << "Token: Diferente" << endl;
				tokens[num_token][0] = "diferente";
				tokens[num_token][1] = "<>";
				num_token++; 
				estado = 0;
				break;
				
			case 13:
				// cout << "Token: Menor o Igual" << endl;
				tokens[num_token][0] = "condicion";
				tokens[num_token][1] = "<=";
				num_token++; 
				estado = 0;
				break;
				
			case 14:
				// cout << "Token: Menor que" << endl;
				tokens[num_token][0] = "condicion";
				tokens[num_token][1] = "<";
				num_token++; 
				estado = 0;
				break;
				
			case 15:
				if (cadena[i+1] == '=') {
					estado = 17;
					i--;
				} else  {
					estado = 16;
					i--;
				}
				
				break;
				
			case 16:
				// cout << "Token: Mayor que" << endl;
				tokens[num_token][0] = "condicion";
				tokens[num_token][1] = ">";
				num_token++; 
				estado = 0;
				break;
			
			case 17:
				// cout << "Token: Mayor o Igual" << endl;
				tokens[num_token][0] = "condicion";
				tokens[num_token][1] = ">=";
				num_token++; 
				estado = 0;
				break;
				
			case 18:
				if (cadena[i+1] == '=') {
					estado = 19;
				}
				
			case 19:
				// cout << "Token: Asignacion" << endl;
				tokens[num_token][0] = "asignacion";
				tokens[num_token][1] = ":=";
				num_token++;
				estado = 0;
				break;
				
			case 20:
				// cout << "Token: Cierre" << endl;
				tokens[num_token][0] = "cierre";
				tokens[num_token][1] = ";";
				num_token++; 
				estado = 0;
				break;
				
			case 21:
				// cout << "Token: Parentesis Abre" << endl;
				tokens[num_token][0] = "parentesis_abre";
				tokens[num_token][1] = "(";
				num_token++; 
				estado = 0;
				break;
			
			case 22:
				// cout << "Token: Parentesis Cierra" << endl;
				tokens[num_token][0] = "parentesis_cierra";
				tokens[num_token][1] = ")";
				num_token++; 
				estado = 0;
				break;
			
			case 23:
				// cout << "Token: Comilla" << endl;
				tokens[num_token][0] = "comilla";
				tokens[num_token][1] = '"';
				num_token++; 
				estado = 0;
				break;
			
			case 24:
				if(cadena.length()==1){
					// cout << "Token: Identificador" << endl;
					tokens[num_token][0] = "identificador";
					tokens[num_token][1] = palabra;
					num_token++;
					palabra = ""; 
					estado = 0;
		   		} else if((isalpha(cadena[i+2]) or isdigit(cadena[i+2])) && (isalpha(cadena[i+1]) or isdigit(cadena[i+1]))) {
					estado = 24;
				} else {
					estado = 25;
				} 
				
				break;
			
			case 25:
				for (int j = posicionPalabra; j < i+1; j++) {
					
					
					if(isalpha(cadena[j])) {
						palabra = palabra + cadena[j];						
					} else {
						palabra = palabra;
						i--;
						estado = 0;
					}
					
					
				
					if(palabra == "si") {
						// cout << "Token: Palabra Reservada si" << endl;
						tokens[num_token][0] = "si";
						tokens[num_token][1] = palabra;	
						num_token++; 
						palabra = "";
						palabraNormal = false;
						i++;

					} else if(palabra == "cuandono") {
						// cout << "Token: Palabra Reservada cuandono" << endl;
						tokens[num_token][0] = "cuandono";
						tokens[num_token][1] = palabra;	
						num_token++; 
						palabra = "";
						palabraNormal = false;
						i++; // 7;
						// cout << tokens[num_token][0] << endl;
					} else if(palabra == "mientras") {
						// cout << "Token: Palabra Reservada mientras" << endl;
						
						tokens[num_token][0] = "mientras";
						tokens[num_token][1] = palabra;	
						num_token++; 
						palabra = "";
						palabraNormal = false;
						// i+= 5;
						i++;
						
					} else if(palabra == "escribir") {
						// cout << "Token: Palabra Reservada escribir" << endl;
						tokens[num_token][0] = "escribir";
						tokens[num_token][1] = palabra;	
						num_token++; 
						palabra = "";
						palabraNormal = false;
						i+= 7;
						
					} else if(palabra == "leer") {
						// cout << "Token: Palabra Reservada leer" << endl;
						tokens[num_token][0] = "leer";
						tokens[num_token][1] = palabra;	
						num_token++; 
						palabra = "";
						palabraNormal = false;
						i+= 3;

					} else if(palabra == "comienzo") {
						// cout << "Token: Palabra Reservada comienzo" << endl;
						tokens[num_token][0] = "comienzo";
						tokens[num_token][1] = palabra;	
						num_token++; 
						palabra = "";
						palabraNormal = false;
						i+= 7;
					} else if(palabra == "fin") {
						// cout << "Token: Palabra Reservada fin" << endl;
						tokens[num_token][0] = "fin";
						tokens[num_token][1] = palabra;	
						num_token++; 
						palabra = "";
						palabraNormal = false;
						i+= 2;
					} else if(palabra == "int") {
						// cout << "Token: Palabra Reservada fin" << endl;
						tokens[num_token][0] = "tipo_dato";
						tokens[num_token][1] = palabra;	
						num_token++; 
						palabra = "";
						palabraNormal = false;
						i+= 2;
					} else if(palabra == "string") {
						// cout << "Token: Palabra Reservada fin" << endl;
						tokens[num_token][0] = "tipo_dato";
						tokens[num_token][1] = palabra;	
						num_token++; 
						palabra = "";
						palabraNormal = false;
						i+= 2;
					} else if(palabra == "float") {
						// cout << "Token: Palabra Reservada fin" << endl;
						tokens[num_token][0] = "tipo_dato";
						tokens[num_token][1] = palabra;	
						num_token++; 
						palabra = "";
						palabraNormal = false;
						i+= 2;
					}  else if(palabra == "(" | palabra == ")" | palabra == ":") {
						palabraNormal = false;
						palabra = "";
						i--;
						estado = 0;
					} else {
						palabraNormal = true;
					}
					
				}
			
				if(palabraNormal) {
						
					if(palabra[0] != '_' && palabra.length() > 0) {
						// cout << "Token: Identificador: " << palabra << endl;
						tokens[num_token][0] = "identificador";
						tokens[num_token][1] = palabra;	
						num_token++; 
						palabra = "";
						estado = 0;
					} 
				}
	
				break;
	
			case 26:
				
				if(isdigit(cadena[i+1])) {
					estado = 26;
					digito = digito + cadena[i];
					//cout << "Estado 26" << endl;
				} else if(isdigit(cadena[i])) {
					digito = digito + cadena[i];
					estado = 27;
					i--;
					//cout << "Estado 26.1" << endl;
				}
				
				break;
				
			case 27:
				
				largo = digito.length();
				// cout << "Token: Digito " << digito << endl;
				tokens[num_token][0] = "digito";
				tokens[num_token][1] = digito;	
				num_token++; 
				digito = "";
				estado = 0;
				
				break;
		
			default:
				break;
		}
	}

	if(tokens[0][0] == "si") {
		bool ver_si = si(tokens, num_token);
	} else if(tokens[0][0] == "mientras") {
		bool ver_mientras = mientras(tokens, num_token);
	} else if(tokens[0][0] == "tipo_dato") {
		bool ver_declaracion = declaracion(num_token, tokens);
	} else {
		cout << "Error 106: Expresion no valida" << endl;
	}

	for(int i = 0; i < num_variables; i++) {
		cout << variables[i][0] << " | "  << variables[i][1] << endl;
	}
		
	return 1;
}

bool declaracion(int num_token, string tokens[50][2]) {

	if(tokens[0][0] == "si" or tokens[0][0] == "mientras" or tokens[0][0] == "identificador") {
		return false;
	}

	int inicio_expresion = 0;
	int termino_expresion = 0;
	string tokens_verificar[50][2] = {};
	int num_tokens_verificar = 0;

	int var_aum = 0;
	int cierres = 0;

	string tipo = "";
	int dato = 0;

	// cout << "Dentro de declaracion" << endl;
	// for(int i = 0; i < num_token; i++) {
	// 	cout << "Dentro de declaracion: " << tokens[i][1] << endl;
	// }


	for( int i = 0; i < num_token; i++ ) {

		if(tokens[var_aum][0] == "tipo_dato") {
			tipo = tokens[var_aum][1];
			var_aum++;
			if(tokens[var_aum][0] == "identificador"){
				var_aum++;
				if(tokens[var_aum][0] == "asignacion") {
					var_aum++;
					if(tokens[var_aum][0] == "identificador" or tokens[var_aum][0] == "digito") {
						var_aum++;
						if(tokens[var_aum][0] == "cierre") {
							var_aum++;
							cout << "declaracion valida" << endl;
						} else {
							while(
								(tokens[var_aum][0] == "suma" or tokens[var_aum][0] == "resta" or tokens[var_aum][0] == "multiplicacion") && 
								(tokens[var_aum+1][0] == "identificador" or tokens[var_aum+1][0] == "digito")) {
								var_aum += 2;
							}
							if(tokens[var_aum][0] == "cierre") {
								var_aum++;
								cout << "declaracion valida" << endl;
							} else {
								cout << "Error 107: Se esperaba un ;" << endl;
							}
						}
					} else if(tokens[var_aum][0] == "comilla" && tipo == "string") {
						var_aum++;
						if(tokens[var_aum][0] == "identificador" or tokens[var_aum][0] == "digito") {
							dato = var_aum;
							var_aum++;
							if(tokens[var_aum][0] == "comilla") {
								var_aum++;
								if(tokens[var_aum][0] == "cierre") {
									cout << "Se encontró una declaracion de string" << endl;
									variables[num_variables][0] = "string";
									variables[num_variables][1] = tokens[dato][1];
									num_variables++;
								}
							}
						}
							

					} else {
						// Error cuando no haya un id o parametro despues del numero.
						cout << "Error 100: Parámetro no valido en la posicion: " << var_aum  << ", se esperaba un id o un digito" << endl;
					}
				} else {
					// Error cuando no haya una asignacion después de el id.
					cout << "Error 100: Parámetro no valido en la posicion: " << var_aum  << ", se esperaba una asignacion" << endl;
				}
			} else {
				// Error falta identificador
				cout << "Error 100: Parámetro no valido en la posicion: " << var_aum  << ", se esperaba un id" << endl;
			}
		}

	}

	// num_tokens_verificar = 0;

	int a = 0;
	for(int m = var_aum; m < num_token; m++) {
		tokens_verificar[a][0] = tokens[m][0];
		tokens_verificar[a][1] = tokens[m][1];
		num_tokens_verificar += 1;
		// cout << tokens_verificar[a][0] << " " << tokens_verificar[a][1] << endl;
		a++;
	}

	if(tokens[var_aum][0] == "si"){
		bool ver_si = si(tokens_verificar, num_tokens_verificar);
	} else if(tokens[var_aum][0] == "mientras"){
		bool ver_mientras = mientras(tokens_verificar, num_tokens_verificar);
	} else if(tokens[var_aum][0] == "identificador"){
		bool ver_asignacion = asignacion(tokens_verificar, num_tokens_verificar);
	} else if(tokens[var_aum][0] == "tipo_dato"){
		cout << "Encontro otra declaracion" << endl;
		bool ver_declaracion = declaracion(num_tokens_verificar, tokens_verificar);
	} 

	return false;

}

// Funcion de asignacion. Ejemplo de sintaxis correcta: x := 1;
bool asignacion(string tokens[50][2], int num_token) {

	if(tokens[0][0] == "si" or tokens[0][0] == "mientras") {
		return false;
	}

	int inicio_expresion;
	int termino_expresion;
	int num_tokens_verificar;

	int var_aum = 0;
	int cierres = 0;

	// cout << "Dentro de asignacion" << endl;
	// for(int i = 0; i < num_token; i++) {
	// 	cout << "Dentro de asignacion: " << tokens[i][0] << endl;
	// }


	for( int i = 0; i < num_token; i++ ) {
		if(tokens[var_aum][0] == "identificador"){
			var_aum++;
			if(tokens[var_aum][0] == "asignacion") {
				var_aum++;
				if(tokens[var_aum][0] == "identificador" or tokens[var_aum][0] == "digito") {
					var_aum++;
					if(tokens[var_aum][0] == "cierre") {
						var_aum++;
						cout << "asignacion valida" << endl;
						i = num_token;
					} else {
						while(
							(tokens[var_aum][0] == "suma" or tokens[var_aum][0] == "resta" or tokens[var_aum][0] == "division" or tokens[var_aum][0] == "multiplicacion") && 
							(tokens[var_aum+1][0] == "identificador" or tokens[var_aum+1][0] == "digito")) {
							var_aum += 2;
						}
						if(tokens[var_aum][0] == "cierre") {
							var_aum++;
							cout << "asignacion valida" << endl;
							i = num_token;
						} else {
							cout << "Error 107: Se esperaba un ;" << endl;
							return false;
						}
					}
				} else {
					// Error cuando no haya un id o parametro despues del numero.
					cout << "Error 100: Parámetro no valido en la posicion: " << var_aum  << ", se esperaba un id o un digito" << endl;
					return false;
				}
			} else {
				// Error cuando no haya una asignacion después de el id.
				cout << "Error 100: Parámetro no valido en la posicion: " << var_aum  << ", se esperaba una asignacion" << endl;
				return false;
			}
		} else {
			// Error falta identificador
			cout << "Error 100: Parámetro no valido en la posicion: " << var_aum  << ", se esperaba un id" << endl;
			return false;
		}
	}

	num_tokens_verificar = 0;
	// cout << "Primer token a verificar: " << tokens[var_aum][0] << endl;
	// cout << "Cantidad de tokens: " << num_token  << endl;

	// cout << "Segunda validacion" << endl;
	int a = 0;
	string tokens_verificar[50][2] = {};
	for(int m = var_aum; m < num_token; m++) {
		tokens_verificar[a][0] = tokens[m][0];
		tokens_verificar[a][1] = tokens[m][1];
		num_tokens_verificar += 1;
		// cout << tokens_verificar[a][0] << " " << tokens_verificar[a][1] << endl;
		a++;
	}

	// cout << "Posicion final: " << tokens[var_aum][0] << endl;

	if(tokens[var_aum][0] == "si"){
		bool ver_si = si(tokens_verificar, num_tokens_verificar);
	} else if(tokens[var_aum][0] == "mientras"){
		bool ver_mientras = mientras(tokens_verificar, num_tokens_verificar);
	} else if(tokens[var_aum][0] == "identificador"){
		bool ver_asig = asignacion(tokens_verificar, num_tokens_verificar);
	}

	return true;

}


// Función para identificar validaciones estilo if.
bool si(string tokens[50][2], int num_token) {

	int inicio_expresion = 0;
	int termino_expresion = 0;
	string tokens_verificar[50][2] = {};
	int num_tokens_verificar;

	int num_llaves = 0;
	int num_par = 0;
	bool valido = false;

	int cant_ifs = 0;

	// Variable aumento.
	int var_aum = 0;

	for(int j = 0; j < num_token ; j++) {
		if(tokens[j][0] == "si") {
			var_aum++;
			if(tokens[j+var_aum][0] == "parentesis_abre") {
				var_aum++;
				while(tokens[j+var_aum][0] == "parentesis_abre") {
					num_par++;
					var_aum++;
				}
				// Cicle parentesis.
				if(tokens[j+var_aum][0] == "identificador") {
					var_aum++;
					if(tokens[j+var_aum][0] == "condicion") {
						var_aum++;
						if(tokens[j+var_aum][0] == "digito" or tokens[j+var_aum][0] == "identificador") {
							var_aum++;
							if(tokens[j+var_aum][0] == "parentesis_cierra") {
								var_aum++;
								while(tokens[j+var_aum][0] == "parentesis_cierra") {
									num_par--;
									var_aum++;
								}
								if(num_par != 0) {
									cout << "Error 104: Cantidad de parentesis incorrecta. " << endl;
									if(num_par > 0) {
										cout << "Existe un ( de más" << endl;
									} else if(num_par < 0) {
										cout << "Existe un ) de más" << endl;
									}
									return false;
								}
								if(tokens[j+var_aum][0] == "llave_abre") {
									var_aum++;
									while(tokens[j+var_aum][0] == "llave_abre") {
										num_llaves++;
										var_aum++;
									}
									// Ciclo de llaves.
									inicio_expresion = j+var_aum;
									for(int k = j+var_aum; k < num_token; k++) {
										if(tokens[k][0] == "llave_cierra") {
											var_aum++;
											while(tokens[j+var_aum][0] == "llave_cierra") {
												num_llaves--;
												var_aum++;
											}
											if(num_llaves == 0) {
												termino_expresion = k;
												valido = true;
												cant_ifs++;
												j = num_token;
												cout << "if valido" << endl;
												break;
											} else {
												cout << "Error 103: Numero de llaves incorrecto. " ;
												if(num_llaves > 0) {
													cout << "Existe un numero mayor de {, en la posicion " << j+var_aum << endl;
												} else if(num_llaves < 0) {
													cout << "Existe un numero mayor de }, en la posicion " << j+var_aum << endl;
												}
												return false;
											}
										}
									}
								} 
							}
						} 
 					} else {
						// Error cuando la condición no sea válida.
						cout << "Error 101: Se espera una condición, y se obtuvo " << tokens[j+var_aum][1] 
							 << " en la posicion " << j+var_aum << endl;
						return false;
					}
				} else {
					// Error cuando el primer parámetro no sea válido.
					cout << "Error 100: Parametro no válido en la posicion " 
						 << j+var_aum << " se espera una variable y se obtuvo " << tokens[j+var_aum][1] << endl;
					return false;
				}
			} else {
				// Error, falta ( al comienzo.
				cout << "Error 102: Falta parentesis ( despues de si, en posicion: " << endl;
				return false;
			}
		}

	}

	// cout << "Numero de ifs recorridos: " << cant_ifs << endl;


	int x = 0;
	num_tokens_verificar = 0;
	for(int m = inicio_expresion; m < termino_expresion+1; m++) {
		tokens_verificar[x][0] = tokens[m][0];
		tokens_verificar[x][1] = tokens[m][1];
		num_tokens_verificar += 1;
		// cout << tokens_verificar[x][0] << " " << tokens_verificar[x][1] << endl;
		x++;
	}


	int inicio_declaracion = 0;
	string asig[50][2] =  {};
	
	for(int a = 0; a < num_tokens_verificar; a++) {
		if(tokens_verificar[inicio_declaracion][0] == "si") {
			int cierre_declaracion;
			bool si_valido = si(tokens_verificar, num_tokens_verificar);
			break;
		} else if(tokens_verificar[inicio_declaracion][0] == "tipo_dato") {
			int cierre_declaracion;
			for(int m = 0; m < num_tokens_verificar; m++) {
				if(tokens_verificar[m][0] == "cierre") {
					cierre_declaracion = m;
					bool declaracion_valida = declaracion(m+1, tokens_verificar);
					a = num_tokens_verificar;
					break;
				}
			}
		} else if(tokens_verificar[inicio_declaracion][0] == "identificador") {
			int cierre_declaracion;
			for(int m = 0; m < num_tokens_verificar; m++) {
				if(tokens_verificar[m][0] == "cierre") {
					cierre_declaracion = m;
					bool asignacion_valida = asignacion(tokens_verificar, num_tokens_verificar);
					a = num_tokens_verificar;
					break;
				}
			}
		} else if(tokens_verificar[inicio_declaracion][0] == "mientras") {
			bool mientras_valido = mientras(tokens_verificar, num_tokens_verificar);
		}
		inicio_declaracion++;
	}

	string tokens_ver_2[50][2] = {};

	int b = 0;
	for(int m = termino_expresion + 1; m <= num_token; m++) {
		tokens_ver_2[b][0] = tokens[m][0];
		tokens_ver_2[b][1] = tokens[m][1];
		num_tokens_verificar += 1;
		// cout << tokens_ver_2[b][0] << " " << tokens_ver_2[b][1] << endl;
		b++;
	}

	int aum = 1;
	int cierre_llave, abre_llave;
	int num_abre = 0, num_cierra = 0;



	if(tokens[termino_expresion+aum][0] == "tipo_dato"  ){
		int num = num_token - termino_expresion;
		bool ver_asig = declaracion(num, tokens_ver_2);
	}  else if(tokens[termino_expresion+aum][0] == "cuandono") {
		aum++;
		if(tokens[termino_expresion+aum][0] == "llave_abre") {
			num_abre++;
			abre_llave = termino_expresion+aum;
			while(tokens[termino_expresion+aum][0] != "llave_cierra") {
				aum++;
			}
			
			cierre_llave = termino_expresion + aum;
			cout << "Cuando no, valido" << endl;
			// cout << "la llave está en la posicion " << cierre_llave << "token: " << tokens[cierre_llave+1][0] << endl;

			int c = 0;
			num_tokens_verificar = 0;
			for(int m = abre_llave+1; m <= cierre_llave; m++) {
				tokens_verificar[c][0] = tokens[m][0];
				tokens_verificar[c][1] = tokens[m][1];
				num_tokens_verificar += 1;
				c++;
			}

			int size = cierre_llave - (abre_llave);

			if(tokens_verificar[0][0] == "tipo_dato") {
				bool ver_asig = declaracion(num_tokens_verificar, tokens_verificar);
			} else if(tokens_verificar[0][0] == "mientras") {
				bool ver_mientras = mientras(tokens_verificar, num_tokens_verificar);
			} else if(tokens_verificar[0][0] == "si") {
				bool ver_si = si(tokens_verificar, num_tokens_verificar);
			}

			string tokens_ver_despues[50][2] = {};

			int pos = 0;
			for(int i = cierre_llave+1; i <= num_token; i++) {
				tokens_ver_despues[pos][0] = tokens[i][0];
				tokens_ver_despues[pos][1] = tokens[i][1];
				pos++;
			}
			int tam = num_token - cierre_llave;

			if(tokens[cierre_llave+1][0] == "mientras"){
				bool ver_mientras = mientras(tokens_ver_despues, tam);
			} else if(tokens[cierre_llave+1][0] == "si"){
				bool ver_si = si(tokens_ver_despues, tam);
			}

		} else {
			cout << "Error Sintactico 105: Se esperaba { despues de cuandono" << endl;
		}
	} else if(tokens[termino_expresion+1][0] == "mientras"){
		int num = num_token - termino_expresion;
		bool ver_mientras = mientras(tokens_ver_2, num);
	}


	return valido;

}


// Función para identificar ciclo mientras.
bool mientras(string tokens[50][2], int num_token) {

	int num_llaves = 0;
	bool valido = false;
	int inicio_expresion = 0, termino_expresion = 0;

	string tokens_verificar[50][2];
	int num_tokens_verificar = 0;

	int var_aum = 0;
	int num_par = 0;

	for(int i = 0; i < num_token; i++) {
		if(tokens[i][0] == "mientras") {
			var_aum++;
			if(tokens[i+var_aum][0] == "parentesis_abre") {
				var_aum++;
				while(tokens[i+var_aum][0] == "parentesis_abre") {
					num_par++;
					var_aum++;
				}
				if(tokens[i+var_aum][0] == "identificador") {
					var_aum++;
					if(tokens[i+var_aum][0] == "condicion") {
						var_aum++;
						if(tokens[i+var_aum][0] == "identificador" || tokens[i+var_aum][0] == "digito") {
							var_aum++;
							if(tokens[i+var_aum][0] == "parentesis_cierra") {
								var_aum++;
								while(tokens[i+var_aum][0] == "parentesis_cierra") {
									num_par--;
									var_aum++;
								}
								if(num_par != 0) {
									cout << "Error 104: Cantidad de parentesis incorrecta. " << endl;
									if(num_par > 0) {
										cout << "Existe un ( de más" << endl;
									} else if(num_par < 0) {
										cout << "Existe un ) de más" << endl;
									}
									return false;
								}
								if(tokens[i+var_aum][0] == "llave_abre") {
									var_aum++;
									num_llaves++;
									inicio_expresion = i+var_aum;
									// cout << "Inicio dce la expresion: " << tokens[inicio_expresion][1] << endl;
									for(int k = i+var_aum; k < num_token; k++) {
										if(tokens[k][0] == "llave_cierra") {
											num_llaves--;
											// cout << "Cierre if: " << k << endl;
											if(num_llaves == 0) {
												termino_expresion = k;
												valido = true;
												cout << "mientras valido" << endl;
												// cout << "Cierre de la expresion: " << tokens[termino_expresion][1] << endl;
												i = num_token;
												break;
											} else {
												cout << "Error 103: Numero de llaves incorrecto. " ;
												if(num_llaves > 0) {
													cout << "Existe un numero mayor de {, en la posicion " << i+var_aum << endl;
												} else if(num_llaves < 0) {
													cout << "Existe un numero mayor de }, en la posicion " << i+var_aum << endl;
												}
												return false;
											}
										}
									}
								}
							} else {
								// Error cuando no hay parentesis que cierra.
								cout << "Error 105: Uso de parentesis incorrecto, se esperaba ')' en " << i+var_aum 
									<< " y se recibio " << tokens[i+var_aum][1] << endl;
								return false;
							}
						}  else {
							cout << "Error 100: Parametro no válido en la posicion " 
							 << i+var_aum << " se espera una variable y se obtuvo " << tokens[i+var_aum][1] << endl;
							return false;
						}
					} else {
						// Error cuando la condición no sea válida.
						cout << "Error 101: Se espera una condición, y se obtuvo " << tokens[i+var_aum][1] 
							 << " en la posicion " << i+var_aum << endl;
						return false;
					}
				} else {
					cout << "Error 100: Parametro no válido en la posicion " 
						 << i+var_aum << " se espera una variable y se obtuvo " << tokens[i+var_aum][1] << endl;
					return false;
				}
			} else {
				// Error si no recibió un parentesís despues de mientras.
				cout << "Error 102: Se esperaba un ( despues de la funcion, en posicion " << i+var_aum << ", se recibio un " << tokens[i+var_aum][0] << endl;
				return false;
			}
		}
	}

	int x = 0;
	for(int m = inicio_expresion; m < termino_expresion; m++) {
		tokens_verificar[x][0] = tokens[m][0];
		tokens_verificar[x][1] = tokens[m][1];
		num_tokens_verificar += 1;
		// cout << tokens_verificar[x][0] << " " << tokens_verificar[x][1] << endl;
		x++;
	}

	int inicio_declaracion = 0;
	string asig[50][2] = {};

	// for(int a = 0; a < num_tokens_verificar; a++) {
		if(tokens_verificar[inicio_declaracion][0] == "si") {
			
			int cierre_declaracion;
			bool si_valido = si(tokens_verificar, num_tokens_verificar);


		} else if(tokens_verificar[inicio_declaracion][0] == "tipo_dato") {
			// cout << tokens_verificar[inicio_declaracion][0] << endl;
			int cierre_declaracion;
			for(int m = 0; m < num_tokens_verificar; m++) {
				if(tokens_verificar[m][0] == "cierre") {
					cierre_declaracion = m;
					// a = m;
					bool declaracion_valida = declaracion(num_tokens_verificar, tokens_verificar);
					break;
				}
			}
		} else if(tokens_verificar[inicio_declaracion][0] == "identificador") {
			// cout << tokens_verificar[inicio_declaracion][0] << endl;
			int cierre_declaracion;
			for(int m = 0; m < num_tokens_verificar; m++) {
				if(tokens_verificar[m][0] == "cierre") {
					cierre_declaracion = m;
					// a = m;
					bool asig_valida = asignacion(tokens_verificar, num_tokens_verificar);
					break;
				}
			}
		} else if(tokens_verificar[inicio_declaracion][0] == "mientras") {
		bool mientras_valido = mientras(tokens_verificar, num_tokens_verificar);
		}
		inicio_declaracion++;
	// }
	
	return valido;

}