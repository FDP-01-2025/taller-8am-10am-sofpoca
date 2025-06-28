#include <iostream>
#include <fstream>
using namespace std;

struct Estudiante {
    string nombre;
    string carnet;
    int edad;
};

// Función para agregar estudiante (CREATE)
void agregarEstudiante() {
    Estudiante e;
    cout << "Nombre (sin espacios): ";
    cin >> e.nombre;
    cout << "Carnet: ";
    cin >> e.carnet;
    cout << "Edad: ";
    cin >> e.edad;

    ofstream archivo("estudiantes.txt", ios::app);
    if (archivo.is_open()) {
        archivo << e.nombre << " " << e.carnet << " " << e.edad << endl;
        archivo.close();
        cout << "Estudiante agregado correctamente.\n";
    } else {
        cout << "Error al abrir el archivo.\n";
    }
}

// Función para mostrar estudiantes (READ)
void mostrarEstudiantes() {
    ifstream archivo("estudiantes.txt");
    Estudiante e;

    if (archivo.is_open()) {
        cout << "\n--- Lista de Estudiantes ---\n";
        while (archivo >> e.nombre >> e.carnet >> e.edad) {
            cout << "Nombre: " << e.nombre 
                 << ", Carnet: " << e.carnet
                 << ", Edad: " << e.edad << endl;
        }
        archivo.close();
    } else {
        cout << "Error al abrir el archivo.\n";
    }
}

// Función para modificar estudiante (UPDATE)
void modificarEstudiante() {
    ifstream archivo("estudiantes.txt");
    ofstream temp("temp.txt");
    Estudiante e;
    string buscado;
    bool modificado = false;

    cout << "Ingrese carnet a modificar: ";
    cin >> buscado;

    if (archivo.is_open() && temp.is_open()) {
        while (archivo >> e.nombre >> e.carnet >> e.edad) {
            if (e.carnet == buscado) {
                Estudiante nuevo;
                cout << "Nuevo nombre (sin espacios): ";
                cin >> nuevo.nombre;
                cout << "Nuevo carnet: ";
                cin >> nuevo.carnet;
                cout << "Nueva edad: ";
                cin >> nuevo.edad;

                temp << nuevo.nombre << " " << nuevo.carnet << " " << nuevo.edad << endl;
                modificado = true;
            } else {
                temp << e.nombre << " " << e.carnet << " " << e.edad << endl;
            }
        }
        archivo.close();
        temp.close();
        remove("estudiantes.txt");
        rename("temp.txt", "estudiantes.txt");

        if (modificado)
            cout << "Estudiante modificado correctamente.\n";
        else
            cout << "Carnet no encontrado.\n";
    } else {
        cout << "Error abriendo los archivos.\n";
    }
}

// -----------------------------
// 👇 TU TAREA: Completa esta función (DELETE)
// Escribe aquí la función que elimine un estudiante por su carnet.
// Puedes usar o no el manejo de archivos.
// Si lo haces con archivos, ganarás **2 puntos extra**.
void eliminarEstudiante() {
    string carnetBuscado;
    cout<<"Ingresa el carnet de el estudiante a eliminar: ";
    cin>>carnetBuscado;
    //Abrimos los achivos donde vamos a acceder a los estudiantes ya guardados y otro donde vamos a guardar temporalmente solo los que no vamos
    //a eliminar
    ifstream archivo("estudiantes.txt");
    ofstream auxiliar("aux.txt");
    if(!archivo.is_open() || !auxiliar.is_open()){
        cout<<"Error al abrir el archivo\n";
        //si el archivo no se abrio imprimimos error
    }
    else{
        bool encontrado=false;
        //Esta variable servira para saber si se encontro a algun estudiante con el carnet buscado
        Estudiante a;
        while(archivo>>a.nombre>>a.carnet>>a.edad){
            if(a.carnet==carnetBuscado){
                encontrado=true;
                continue;
                //si lo encontramos, no lo guardamos
            }
            else{
                auxiliar<<a.nombre<<" "<<a.carnet<<" "<<a.edad<<endl;
                //si no, si se guarda
            }
        }
        auxiliar.close();
        archivo.close();
        remove("estudiantes.txt");
        rename("aux.txt", "estudiantes.txt");
        // se cierran los archivos y se reemplaza, el archivo con las eliminaciones por el original
        if(!encontrado){
            cout<<"El estudiante de canet: "<<carnetBuscado<<" no se encontro\n";
        }
        else{
            cout<<"Estudiante eliminado con exito!\n";
        }
    }
}
// -----------------------------

// Menú principal
int main() {
    int opcion;
    do {
        cout << "\n=== CRUD de Estudiantes ===\n";
        cout << "1. Agregar estudiante\n";
        cout << "2. Mostrar todos\n";
        cout << "3. Modificar estudiante\n";
        cout << "4. Eliminar estudiante\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: agregarEstudiante(); break;
            case 2: mostrarEstudiantes(); break;
            case 3: modificarEstudiante(); break;
            case 4: eliminarEstudiante(); break;
            case 5: cout << "Saliendo...\n"; break;
            default: cout << "Opción inválida.\n";
        }

    } while (opcion != 5);

    return 0;
}