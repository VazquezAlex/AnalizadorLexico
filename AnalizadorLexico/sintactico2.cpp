#include<iostream>
#include<fstream>

using namespace std;

int main() {

	ifstream myReadFile;
	myReadFile.open("codigo.txt");
	char output[100];
	string cadena;

	if (myReadFile.is_open()) {
		string s;
		while (!myReadFile.eof()) {
			while(getline(myReadFile, s)) {
				cadena += s + "\n";
			}
			cout << cadena;
		}
	}
	
	// char *cadenaconver = strdup(output.c_str());

	// Convertir la cadena para trabajarla en cada caracter.
	// char *cadenaconver = strdup(output.c_str());

	cout << "Posicion 2 del arreglo: " << cadena[1];

	myReadFile.close();
	cout << endl;
	return 0;
}
