#include "EspecialidadManager.h"
#include <iostream>
#include <algorithm>
#include <cctype>
using namespace std;

EspecialidadManager::EspecialidadManager()
    : _archivo("especialidades.dat") {}

void EspecialidadManager::agregar()
{
    cout << "\n=== NUEVA ESPECIALIDAD ===\n";

    int nuevoId = _archivo.generarNuevoId();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string desc;
    cout << "Descripcion: ";
    getline(cin, desc);

    while (desc.length() < 3)
    {
        cout << "Descripcion muy corta. Intente de nuevo: ";
        getline(cin, desc);
    }


    if (_archivo.buscarPorDescripcion(desc) != -1)
    {
        cout << "Esa especialidad ya existe.\n";
        return;
    }


    Especialidad reg(nuevoId, desc, true);

    if (_archivo.guardar(reg))
        cout << "Especialidad guardada correctamente.\n";
    else
        cout << "Error al guardar.\n";
}

void EspecialidadManager::listarAlfabeticamente()
{
    int cant = _archivo.cantidadRegistros();
    if (cant == 0)
    {
        cout << "No hay especialidades cargadas.\n";
        return;
    }

    vector<Especialidad> lista(cant);
    _archivo.leerTodos(lista.data(), cant);

    sort(lista.begin(), lista.end(), [](Especialidad a, Especialidad b)
    {
        string sa = a.getDescripcion(), sb = b.getDescripcion();
        transform(sa.begin(), sa.end(), sa.begin(), ::tolower);
        transform(sb.begin(), sb.end(), sb.begin(), ::tolower);
        return sa < sb;
    });

    cout << "\n=== LISTADO DE ESPECIALIDADES ===\n";
    for (auto &e : lista)
        if (e.getEstado())
            cout << e.toString() << endl;
}

void EspecialidadManager::modificarDescripcion(int id)
{
    int pos = id - 1;
    Especialidad reg = _archivo.leer(pos);

    if (reg.getIdEspecialidad() == 0)
    {
        cout << "No se encontro la especialidad.\n";
        return;
    }

    cout << "Descripcion actual: " << reg.getDescripcion() << endl;
    cout << "Nueva descripcion: ";
    string nueva;
    cin.ignore();
    getline(cin, nueva);

    reg.setDescripcion(nueva);

    if (_archivo.guardar(pos, reg))
        cout << "Descripcion actualizada correctamente.\n";
    else
        cout << "Error al modificar.\n";
}

void EspecialidadManager::eliminarEspecialidad(int id)
{
    int pos = id - 1;
    if (_archivo.eliminar(pos))
        cout << "Especialidad dada de baja.\n";
    else
        cout << "No se pudo eliminar.\n";
}

void EspecialidadManager::mostrarMedicosPorEspecialidad()
{
    MedicoArchivo medArch("medicos.dat");
    int idEsp;
    cout << "Ingrese ID de especialidad: ";
    cin >> idEsp;

    int cantMed = medArch.cantidadRegistros();
    if (cantMed == 0)
    {
        cout << "No hay medicos registrados.\n";
        return;
    }

    vector<Medico> medicos(cantMed);
    medArch.leerTodos(medicos.data(), cantMed);

    cout << "\n=== MEDICOS CON ESTA ESPECIALIDAD ===\n";
    bool encontrado = false;
    for (auto &m : medicos)
    {
        if (m.getIdEspecialidad() == idEsp && m.getEstado())
        {
            cout << m.toString() << endl;
            encontrado = true;
        }
    }

    if (!encontrado)
        cout << "No se encontraron medicos con esa especialidad.\n";
}
void EspecialidadManager::buscarPorNombre()
{
    int cant = _archivo.cantidadRegistros();
    if (cant == 0)
    {
        cout << "No hay especialidades cargadas.\n";
        return;
    }

    vector<Especialidad> lista(cant);
    _archivo.leerTodos(lista.data(), cant);

    string buscar;
    cout << "Ingrese texto a buscar (parte del nombre): ";
    cin.ignore();
    getline(cin, buscar);

    transform(buscar.begin(), buscar.end(), buscar.begin(), ::tolower);

    cout << "\n=== RESULTADOS DE BUSQUEDA ===\n";
    bool encontrado = false;
    for (auto &e : lista)
    {
        string desc = e.getDescripcion();
        transform(desc.begin(), desc.end(), desc.begin(), ::tolower);

        if (desc.find(buscar) != string::npos && e.getEstado())
        {
            cout << e.toString() << endl;
            encontrado = true;
        }
    }

    if (!encontrado)
        cout << "No se encontraron coincidencias.\n";
}
