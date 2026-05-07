#include "MedicoManager.h"
#include "ArchivoManagerUtil.h"
#include "EspecialidadArchivo.h"
#include <iostream>
#include <algorithm>
#include <cctype>
using namespace std;

MedicoManager::MedicoManager() : _archivo("medicos.dat") {}

void MedicoManager::agregarMedico() {
    Medico reg;
    reg.cargar();


    int idEsp;
    EspecialidadArchivo espArch("especialidades.dat");

    cout << "ID de especialidad: ";
    cin >> idEsp;

    while (cin.fail() || idEsp <= 0 || espArch.buscarPorId(idEsp) == -1) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "⚠️ Especialidad NO encontrada. Ingrese un ID válido: ";
        cin >> idEsp;
    }

    reg.setIdEspecialidad(idEsp);

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (!_archivo.guardar(reg)) {
        cout << "Error al guardar medico.\n";
        return;
    }

    cout << "Medico guardado correctamente.\n";
}

void MedicoManager::listarPorEspecialidad(int idEspecialidad) {
    int cantidad = ArchivoManagerUtil::cantidadRegistros("medicos.dat", sizeof(Medico));
    if (cantidad == 0) {
        cout << "No hay medicos registrados.\n";
        return;
    }

    vector<Medico> medicos(cantidad);
    ArchivoManagerUtil::leerTodos("medicos.dat", medicos.data(), sizeof(Medico), cantidad);

    cout << "\n=== MEDICOS DE LA ESPECIALIDAD ID " << idEspecialidad << " ===\n";
    bool encontrado = false;

    for (auto &m : medicos) {
        if (m.getEstado() && m.getIdEspecialidad() == idEspecialidad) {
            cout << m.toString() << endl;
            encontrado = true;
        }
    }

    if (!encontrado)
        cout << "No se encontraron medicos con esa especialidad.\n";
}


void MedicoManager::listarTodos() {
    int cantidad = ArchivoManagerUtil::cantidadRegistros("medicos.dat", sizeof(Medico));
    if (cantidad == 0) {
        cout << "No hay medicos cargados.\n";
        return;
    }

    vector<Medico> medicos(cantidad);
    ArchivoManagerUtil::leerTodos("medicos.dat", medicos.data(), sizeof(Medico), cantidad);

    cout << "\n=== LISTADO DE MEDICOS ===\n";
    for (auto &m : medicos)
        if (m.getEstado())
            cout << m.toString() << endl;
}

void MedicoManager::eliminarMedico(string dni) {
    int pos = _archivo.buscarPorDNI(dni);
    if (pos == -1) {
        cout << "Medico no encontrado.\n";
        return;
    }
    _archivo.eliminar(pos);
    cout << "Medico eliminado (baja lógica).\n";
}

void MedicoManager::listarPorApellido() {
    int cantidad = ArchivoManagerUtil::cantidadRegistros("medicos.dat", sizeof(Medico));
    if (cantidad == 0) {
        cout << "No hay medicos registrados.\n";
        return;
    }

    vector<Medico> medicos(cantidad);
    ArchivoManagerUtil::leerTodos("medicos.dat", medicos.data(), sizeof(Medico), cantidad);

    auto toLower = [](string s) {
        transform(s.begin(), s.end(), s.begin(),
                  [](unsigned char c) { return tolower(c); });
        return s;
    };

    sort(medicos.begin(), medicos.end(),
         [&](Medico &a, Medico &b) {
             return toLower(a.getApellido()) < toLower(b.getApellido());
         });

    cout << "\n=== MEDICOS ORDENADOS POR APELLIDO ===\n";
    for (auto &m : medicos)
        if (m.getEstado())
            cout << m.toString() << endl;
}

void MedicoManager::listarPorFechaIngreso(Fecha fechaDesde, Fecha fechaHasta) {
    int cantidad = ArchivoManagerUtil::cantidadRegistros("medicos.dat", sizeof(Medico));
    if (cantidad == 0) {
        cout << "No hay medicos cargados.\n";
        return;
    }

    vector<Medico> medicos(cantidad);
    ArchivoManagerUtil::leerTodos("medicos.dat", medicos.data(), sizeof(Medico), cantidad);

    cout << "\n=== MEDICOS INGRESADOS ENTRE "
         << fechaDesde.toString() << " Y " << fechaHasta.toString() << " ===\n";

    bool encontrado = false;
    for (auto &m : medicos) {
        Fecha f = m.getFechaIngreso();
        if (m.getEstado() &&
            f.getAnio() >= fechaDesde.getAnio() &&
            f.getAnio() <= fechaHasta.getAnio()) {
            cout << m.toString() << endl;
            encontrado = true;
        }
    }

    if (!encontrado)
        cout << "No se encontraron medicos en ese rango de fechas.\n";
}

void MedicoManager::eliminarMedico() {
    string dni;
    cout << "DNI del medico a eliminar: ";
    cin >> dni;
    int pos = _archivo.buscarPorDNI(dni);
    if (pos == -1) {
        cout << "No existe un medico con ese DNI.\n";
        return;
    }

    Medico m = _archivo.leer(pos);

    cout << "\nSe encontro el siguiente medico:\n";
    cout << m.toString() << endl;

    if (_archivo.eliminar(pos)) {
        cout << "Meedico eliminado correctamente .\n";
    } else {
        cout << "Error al eliminar el medico.\n";
    }
}


