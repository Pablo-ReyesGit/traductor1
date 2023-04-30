#include<iostream>
using namespace std;
const char* nombre_archivo = "traducciones";
struct Traductor {
	char english[50];
	char espanish[50];
	char descripcion[200];
};
void crear();
void leer();
void actualizar();
void borrar();

int main() {
	crear();
	actualizar();

	system("pause");
}

void crear() {
	FILE* archivo = fopen(nombre_archivo, "a+b");
	char res;
	Traductor traductor;
	do {
		fflush(stdin);

		cout << "ingrese la palabra inglesa" << endl;
		cin.getline(traductor.english, 50);

		cout << "ingrese la palabra española" << endl;
		cin.getline(traductor.espanish, 50);

		cout << "ingrese una descripcion a del funcionamiento de la palabra" << endl;
		cin.getline(traductor.descripcion, 200);

		fwrite(&traductor, sizeof(traductor), 1, archivo);
		cout << "desea ingresar un nuevo estudainte(s/n)" << endl;
		cin >> res;
	} while (res == 's' || res == 'S');
	fclose(archivo);
	leer();
}
void leer() {
	system("cls");
	FILE* archivo = fopen(nombre_archivo, "rb");
	if (!archivo) {
		archivo = fopen(nombre_archivo, "w+b");
	}
	Traductor traductor;
	int id = 0;
	fread(&traductor, sizeof(traductor), 1, archivo);
	cout << "____________________________________________" << endl;
	cout << "ID || ingles || español " << endl;
	do {
		cout << "ID" << "|" << traductor.english << " || " << traductor.espanish << endl;
		cout << " descripcion" << traductor.descripcion;
		fread(&traductor, sizeof(traductor), 1, archivo);
		id += 1;
	} while (feof(archivo) == 0);
	fclose(archivo);
}
void actualizar() {
	FILE* archivo = fopen(nombre_archivo, "r+b");
	Traductor traductor; 
	int id = 0;
	cout << "ingrese el ID de la palabra que quiere modificar" << endl;
	cin >> id;
	fseek(archivo, id * sizeof(traductor), SEEK_SET);

	cout << "ingrese la palabra inglesa" << endl;
	cin.getline(traductor.english, 50);

	cout << "ingrese la palabra española" << endl;
	cin.getline(traductor.espanish, 50);

	cout << "ingrese una descripcion a del funcionamiento de la palabra" << endl;
	cin.getline(traductor.descripcion, 200);

	fwrite(&traductor, sizeof(traductor), 1, archivo);

	fclose(archivo);
	leer();
}
void borrar() {
	const char* nombre_archivoAux = "archivoAux.dat";
	FILE* archivo = fopen(nombre_archivo, "rb");
	FILE* archivoAux = fopen(nombre_archivoAux, "w+b");
	Traductor traductor; 
	int id, id_n = 0;

	cout << "que elemento desea elimminar" << endl;
	cin >> id;

	while (fread(&traductor, sizeof(traductor), 1, archivo)) {
		if (id_n != id) {
			fread(&traductor, sizeof(traductor), 1, archivoAux);
		}
		id_n++;
	}

	fclose(archivo);
	fclose(archivoAux);

	archivo = fopen(nombre_archivo, "rb");
	archivoAux = fopen(nombre_archivoAux, "wb");

	while (fread(&traductor, sizeof(traductor), 1, archivoAux)) {
		if (id_n != id) {
			fread(&traductor, sizeof(traductor), 1, archivo);
		}
		id_n++;
	}
	fclose(archivo);
	fclose(archivoAux);
	leer();
}
