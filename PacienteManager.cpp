#include "PacienteManager.h"
#include "ObraSocialArchivo.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void PacienteManager::cargarNuevo() {
    Paciente p;
    string dni;

    cout << "Ingrese DNI: ";
    cin >> dni;


    int pos = _archivo.buscarPorDNI(dni);
    if (pos != -1) {
        cout << "Ya existe un paciente con ese DNI.\n";
        return;
    }

    cin.ignore();
    p.setDni(dni);

    p.cargar();


    int idObra;
    cout << "Ingrese ID de la Obra Social: ";
    cin >> idObra;

    ObraSocialArchivo archivoOS("obrasocial.dat");
    int posOS = archivoOS.buscarPorId(idObra);

    while (posOS == -1) {
        cout << "La Obra Social con ese ID NO existe. Ingrese nuevamente: ";
        cin >> idObra;
        posOS = archivoOS.buscarPorId(idObra);
    }

    p.setIdObraSocial(idObra);
    p.setEstado(true);

    if (_archivo.guardar(p))
        cout << "Paciente guardado correctamente.\n";
    else
        cout << "Error al guardar el paciente.\n";
}

void PacienteManager::listarPorApellido()
{
    int cant = _archivo.cantidadRegistros();
    if (cant == 0)
    {
        cout << "No hay pacientes registrados.\n";
        return;
    }

    vector<Paciente> lista(cant);
    _archivo.leerTodos(lista.data(), cant);

    // Ordena por apellido
    sort(lista.begin(), lista.end(),
         []( Paciente &a,  Paciente &b)
    {
        return a.getApellido() < b.getApellido();
    });

    for (auto &p : lista)
        if (p.getEstado())
            cout << p.toString() << endl;
}

void PacienteManager::listarPorObraSocial(int idObra)
{
    int cant = _archivo.cantidadRegistros();
    if (cant == 0)
    {
        cout << "No hay pacientes registrados.\n";
        return;
    }
    bool encontrado = false;

    for (int i = 0; i < cant; i++)
    {
        Paciente p = _archivo.leer(i);
        if (p.getEstado() && p.getIdObraSocial() == idObra)
            cout << p.toString() << endl;
    }

  if (!encontrado)
        cout << "No se encontraron pacientes para esa obra social.\n";
}

void PacienteManager::listarPorFechaNacimiento(Fecha fecha)
{
    int cant = _archivo.cantidadRegistros();
    if (cant == 0)
    {
        cout << "No hay pacientes registrados.\n";
        return;
    }
    bool encontrado = false;

    for (int i = 0; i < cant; i++)
    {
        Paciente p = _archivo.leer(i);
        Fecha fn = p.getFechaNacimiento();
        if (p.getEstado() &&
                fn.getDia() == fecha.getDia() &&
                fn.getMes() == fecha.getMes() &&
                fn.getAnio() == fecha.getAnio())
        {
            cout << p.toString() << endl;
        }
    }
     if (!encontrado)
        cout << "No se encontraron pacientes con esa fecha de nacimiento.\n";

}
void PacienteManager::eliminarPaciente() {
    string dni;
    cout << " DNI del paciente a eliminar: ";
    cin >> dni;


    int pos = _archivo.buscarPorDNI(dni);
    if (pos == -1) {
        cout << "No existe un paciente con ese DNI.\n";
        return;
    }


    Paciente p = _archivo.leer(pos);

    cout << "\nSe encontro el siguiente paciente:\n";
    cout << p.toString() << endl;

    if (_archivo.eliminarLogico(pos)) {
        cout << "Paciente eliminado .\n";
    } else {
        cout << "Error al eliminar el paciente.\n";
    }
}
