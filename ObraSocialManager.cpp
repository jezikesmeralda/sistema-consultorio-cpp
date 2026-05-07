#include "ObraSocialManager.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;

ObraSocialManager::ObraSocialManager()
    : _archivo("obrasocial.dat") {}

void ObraSocialManager::agregar()
{
    ObraSocial reg;
    int nuevoId = _archivo.generarNuevoId();
    reg.cargar(nuevoId);

    // Validar duplicado por nombre
    int cantidad = ArchivoManagerUtil::cantidadRegistros("obrasocial.dat", sizeof(ObraSocial));
    if (cantidad > 0)
    {
        vector<ObraSocial> existentes(cantidad);
        ArchivoManagerUtil::leerTodos("obrasocial.dat", existentes.data(), sizeof(ObraSocial), cantidad);

        for (auto &o : existentes)
        {
            if (o.getEstado() && o.getNombre() == reg.getNombre())
            {
                cout << "Ya existe una obra social con ese nombre.\n";
                return;
            }
        }
    }

    if (ArchivoManagerUtil::agregar("obrasocial.dat", &reg, sizeof(ObraSocial)))
        cout << "Obra social guardada correctamente.\n";
    else
        cout << "Error al guardar la obra social.\n";
}

void ObraSocialManager::eliminar()
{
    int id;
    cout << "Ingrese ID de la obra social a eliminar: ";
    cin >> id;

    int pos = _archivo.buscarPorId(id);
    if (pos == -1)
    {
        cout << "No se encontro la obra social.\n";
        return;
    }

    ObraSocial reg = _archivo.leer(pos);
    reg.setEstado(false);

    if (ArchivoManagerUtil::guardar("obrasocial.dat", pos, &reg, sizeof(ObraSocial)))
        cout << "Obra social eliminada (baja logica).\n";
    else
        cout << "Error al eliminar la obra social.\n";
}

void ObraSocialManager::modificar()
{
    int id;
    cout << "Ingrese ID de la obra social a modificar: ";
    cin >> id;

    int pos = _archivo.buscarPorId(id);
    if (pos == -1)
    {
        cout << "No se encontro la obra social.\n";
        return;
    }

    ObraSocial reg = _archivo.leer(pos);
    cout << "Registro actual:\n" << reg.toString() << endl;

    cout << "\n 1. Modificar nombre\n 2. Modificar tipo de cobertura\n Opción: ";
    int opcion;
    cin >> opcion;
    cin.ignore();

    if (opcion == 1)
    {
        string nuevoNombre;
        cout << "Nuevo nombre: ";
        getline(cin, nuevoNombre);
        reg.setNombre(nuevoNombre);
    }
    else if (opcion == 2)
    {
        int nuevoTipo;
        cout << "Nuevo tipo de cobertura: ";
        cin >> nuevoTipo;
        reg.setTipoCobertura(nuevoTipo);
    }
    else
    {
        cout << "Opcion invalida.\n";
        return;
    }

    if (ArchivoManagerUtil::guardar("obrasocial.dat", pos, &reg, sizeof(ObraSocial)))
        cout << "Registro actualizado correctamente.\n";
    else
        cout << "Error al actualizar la obra social.\n";
}

void ObraSocialManager::listarTodos()
{
    int cantidad = ArchivoManagerUtil::cantidadRegistros("obrasocial.dat", sizeof(ObraSocial));
    if (cantidad == 0)
    {
        cout << "No hay obras sociales cargadas.\n";
        return;
    }

    vector<ObraSocial> vec(cantidad);
    ArchivoManagerUtil::leerTodos("obrasocial.dat", vec.data(), sizeof(ObraSocial), cantidad);

    cout << "\n=== LISTADO DE OBRAS SOCIALES ===\n";
    for (auto &o : vec)
        if (o.getEstado())
            cout << o.toString() << endl;
}

void ObraSocialManager::listarPorNombre()
{
    int cantidad = ArchivoManagerUtil::cantidadRegistros("obrasocial.dat", sizeof(ObraSocial));
    if (cantidad == 0)
    {
        cout << "No hay obras sociales registradas.\n";
        return;
    }

    vector<ObraSocial> vec(cantidad);
    ArchivoManagerUtil::leerTodos("obrasocial.dat", vec.data(), sizeof(ObraSocial), cantidad);

    sort(vec.begin(), vec.end(), []( ObraSocial &a,  ObraSocial &b)
    {
        return a.getNombre() < b.getNombre();
    });

    cout << "\n=== LISTADO ORDENADO POR NOMBRE ===\n";
    for (auto &o : vec)
        if (o.getEstado())
            cout << o.toString() << endl;
}

void ObraSocialManager::listarPorTipoCobertura()
{
    int cantidad = ArchivoManagerUtil::cantidadRegistros("obrasocial.dat", sizeof(ObraSocial));
    if (cantidad == 0)
    {
        cout << "No hay obras sociales registradas.\n";
        return;
    }

    vector<ObraSocial> vec(cantidad);
    ArchivoManagerUtil::leerTodos("obrasocial.dat", vec.data(), sizeof(ObraSocial), cantidad);

    sort(vec.begin(), vec.end(), []( ObraSocial &a,  ObraSocial &b)
    {
        return a.getTipoCobertura() < b.getTipoCobertura();
    });

    cout << "\n=== LISTADO POR TIPO DE COBERTURA ===\n";
    for (auto &o : vec)
        if (o.getEstado())
            cout << o.toString() << endl;
}
