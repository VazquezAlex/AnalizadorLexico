//  lexico.cpp
//  AnalizadorSintáctico.
//
//  Created by Alejandro Vazquez on 10/4/19.
//  Copyright © 2019 Alejandro Vazquez. All rights reserved.
//

// TODO: Agregar error 106, cuando pongan un caracter al azar en la cadena.
// TODO: Agregar do-while, manejar con error 106, solo modificar el texto.


#include "lexico.hpp"
#include <iostream>
#include <ctype.h>
#include <map>
#include <string>
#include <stdlib.h>
#include <string.h>

using namespace std;

// Declaració de funciones.
bool asignacion(int num_token, string tokens[50][2]);
// string** crear_arreglo_asignacion(int inicial, int final, string tokens[50][2]);
bool si(string tokens[50][2], int num_token);
bool mientras(string tokens[50][2], int num_token);

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
	
	// Ingreso de cadena.
	cout << "Ingresa la cadena a analizar: ";
	cin >> cadena;
	
	// Convertir la cadena para trabajarla en cada caracter.
	char *cadenaconver = strdup(cadena.c_str());
	
	// Ciclo para analizar cada caracter de cadena.
	for (int i = 0; i < cadena.length(); i++) {
		
		switch (estado) {
			case 0:
				
				// Estado inicial.
				if (cadenaconver[i] == '+') {
					estado = 1;
					if(cadenaconver[i+1] == '+') {
						// Mandar a estado de aceptación de incremento (Estado 2).
						estado = 2;
					} else {
						// Mandar a estado de suma, y regresar la cadena una posición.
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
				} else if(cadenaconver[i] == '{') {
					// cout << "Token: Llave Abre" << endl;
					tokens[num_token][0] = "llave_abre";
					tokens[num_token][1] = "{";
					num_token++;
				}  else if(cadenaconver[i] == '}') {
					// cout << "Token: Llave Cierra" << endl;
					tokens[num_token][0] = "llave_cierra";
					tokens[num_token][1] = "}";
					num_token++;
				}  else if(isalpha(cadenaconver[i])) {
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
				if(cadenaconver[i+1] == '-') {
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
				if(cadenaconver[i+1] == '=') {
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
				if (cadenaconver[i+1] == '=') {
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
				if (cadenaconver[i+1] == '=') {
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
				tokens[num_token][1] = "'";
				num_token++; 
				estado = 0;
				break;
			
			case 24:
				if(cadena.length()==1){
					cout << "Token: Identificador" << endl;
					tokens[num_token][0] = "identificador";
					tokens[num_token][1] = palabra;
					num_token++;
					palabra = ""; 
					estado = 0;
		   		} else if((isalpha(cadenaconver[i+2]) or isdigit(cadenaconver[i+2])) && (isalpha(cadenaconver[i+1]) or isdigit(cadenaconver[i+1]))) {
					estado = 24;
				} else {
					estado = 25;
				} 
				
				break;
			
			case 25:
				for (int j = posicionPalabra; j < i+1; j++) {
					
					
					if(isalpha(cadenaconver[j])) {
						palabra = palabra + cadenaconver[j];						
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
						i+= 7;
						
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
					} else if(palabra == "(" | palabra == ")" | palabra == ":") {
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

	string lineacod[100] = {};

	if(tokens[0][0] == "si") {
		bool ver_si = si(tokens, num_token);
	} else if(tokens[0][0] == "mientras") {
		bool ver_mientras = mientras(tokens, num_token);
	} else {
		cout << "Error 106: Expresion no valida" << endl;
	}
		
	return 1;
}

bool asignacion(int num_token, string tokens[50][2]) {

	if(tokens[0][0] == "si" or tokens[0][0] == "mientras") {
		return false;
	}

	for( int l=0; l < num_token; l++ ){
		if(tokens[l][0] == "identificador"){
			if(tokens[l+1][0] == "asignacion"){
				if(tokens[l+2][0] == "digito" || tokens[l+2][0] == "identificador"){
					int cierrePos;
					for(int j = l; j < num_token; j++){
						if(tokens[j][0] == "cierre"){
							cierrePos = j;
						}
					}

					for(int m = l+2; m < cierrePos; m++) {
						if((cierrePos - m) == 1) {
							if (tokens[m][0] == "identificador" || tokens[m][0] == "digito") {
								return true;
								break;
							}
						} else if((cierrePos - m) >= 3) {
							if (tokens[m][0] == "identificador" || tokens[m][0] == "digito") {
								if(tokens[m+1][0] == "suma" || tokens[m+1][0] == "multiplicacion" || tokens[m+1][0] == "division" || tokens[m+1][0] == "resta") {
									if(tokens[m+2][0] == "identificador" || tokens[m+2][0] == "digito"){
										return true;
										m = m+2;
										break;
									} else {
										cout << "Error expresion no valida" << endl;
									} 
								} else {
									cout << "Error expresion no valida" << endl;
								} 
							}
						} else if((cierrePos - m) == 2 || ((cierrePos - m) % 2) == 0) {
							if (tokens[m][0] == "identificador") {
								if(tokens[m+1][0] == "decremento" || tokens[m+1][0] == "incremento") {
									return true;
									m = m+1;
								} else {
									cout << "Error expresion no valida" << endl;
								}
							} else if (tokens[m][0] == "suma" || tokens[m][0] == "multiplicacion" || tokens[m][0] == "division" || tokens[m][0] == "resta") {
								if (tokens[m+1][0] == "identificador" | tokens[m+1][0] == "digito"){
									return true;
									m = m+1;
								}
							} else {
								cout << "Error expresion no valida" << endl;
								return false;
							}
						}
					}	
				}
			}
			
		} 

	}

	return false;

}


bool si(string tokens[50][2], int num_token) {

	int inicio_expresion;
	int termino_expresion;
	string tokens_verificar[50][2];
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
									break;
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
											while(tokens[j+var_aum][0] == "llave_cierra") {
												num_llaves--;
												var_aum++;
											}
											// cout << "Cierre if: " << k << endl;
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

	int a = 0;
	for(int m = inicio_expresion; m < termino_expresion+1; m++) {
		tokens_verificar[a][0] = tokens[m][0];
		tokens_verificar[a][1] = tokens[m][1];
		num_tokens_verificar += 1;
		// cout << tokens_verificar[a][0] << " " << tokens_verificar[a][1] << endl;
		a++;
	}

	int inicio_asignacion = 0;
	string asig[50][2];

	for(int a = 0; a < num_tokens_verificar; a++) {
		if(tokens_verificar[inicio_asignacion][0] == "si") {
			
			int cierre_asignacion;
			bool si_valido = si(tokens_verificar, num_tokens_verificar);


		} else if(tokens_verificar[inicio_asignacion][0] == "identificador") {
			cout << tokens_verificar[inicio_asignacion][0] << endl;
			int cierre_asignacion;
			for(int m = 0; m < num_tokens_verificar; m++) {
				if(tokens_verificar[m][0] == "cierre") {
					cierre_asignacion = m;
					a = m;
					bool asignacion_valida = asignacion(m+1, tokens_verificar);
					if(asignacion_valida) {
						cout << "Asignación Válida" << endl;
					}
					break;
				}
			}
		} else if(tokens_verificar[inicio_asignacion][0] == "mientras") {
			bool mientras_valido = mientras(tokens_verificar, num_tokens_verificar);
		}
		inicio_asignacion++;
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
												cout << "Mientras valido" << endl;
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

	int a = 0;
	for(int m = inicio_expresion; m < termino_expresion+1; m++) {
		tokens_verificar[a][0] = tokens[m][0];
		tokens_verificar[a][1] = tokens[m][1];
		num_tokens_verificar += 1;
		// cout << tokens_verificar[a][0] << " " << tokens_verificar[a][1] << endl;
		a++;
	}

	// bool asig_valid = asignacion(num_tokens_verificar, tokens_verificar);

	// if(asignacion(num_tokens_verificar, tokens_verificar)) {
	// 	cout << "Asignacion correcta" << endl;
	// } else if(si(tokens_verificar, num_tokens_verificar))  {
	// 		// cout << "Si valido" << endl;
	// } else if(mientras(tokens_verificar, num_tokens_verificar)) {
	// 	// cout << "Mientras Valido" << endl;
	// }

	int inicio_asignacion = 0;
	string asig[50][2];

	for(int a = 0; a < num_tokens_verificar; a++) {
		if(tokens_verificar[inicio_asignacion][0] == "si") {
			
			int cierre_asignacion;
			bool si_valido = si(tokens_verificar, num_tokens_verificar);


		} else if(tokens_verificar[inicio_asignacion][0] == "identificador") {
			// cout << tokens_verificar[inicio_asignacion][0] << endl;
			int cierre_asignacion;
			for(int m = 0; m < num_tokens_verificar; m++) {
				if(tokens_verificar[m][0] == "cierre") {
					cierre_asignacion = m;
					a = m;
					bool asignacion_valida = asignacion(m+1, tokens_verificar);
					if(asignacion_valida) {
						cout << "Asignación Válida" << endl;
					}
					break;
				}
			}
		} else if(tokens_verificar[inicio_asignacion][0] == "mientras") {
			bool mientras_valido = mientras(tokens_verificar, num_tokens_verificar);
		}
		inicio_asignacion++;
	}
	
	return valido;

}