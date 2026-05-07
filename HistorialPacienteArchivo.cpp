#include "HistorialPacienteArchivo.h"
#include "PacienteArchivo.h"
#include <iostream>
using namespace std;

HistorialPacienteArchivo::HistorialPacienteArchivo(string nombreArchivo)
    : _nombreArchivo(nombreArchivo) {}

bool HistorialPacienteArchivo::guardar(HistorialPaciente registro) {
    return ArchivoManagerUtil::guardar(_nombreArchivo, &registro, sizeof(HistorialPaciente));
}

bool HistorialPacienteArchivo::guardar(int pos, HistorialPaciente registro) {
    return ArchivoManagerUtil::guardar(_nombreArchivo, pos, &registro, sizeof(HistorialPaciente));
}

HistorialPaciente HistorialPacienteArchivo::leer(int pos) {
    HistorialPaciente reg;
    ArchivoManagerUtil::leer(_nombreArchivo, pos, &reg, sizeof(HistorialPaciente));
    return reg;
}

int HistorialPacienteArchivo::leerTodos(HistorialPaciente *vec, int cantidad) {
    return ArchivoManagerUtil::leerTodos(_nombreArchivo, vec, sizeof(HistorialPaciente), cantidad);
}

int HistorialPacienteArchivo::cantidadRegistros() {
    return ArchivoManagerUtil::cantidadRegistros(_nombreArchivo, sizeof(HistorialPaciente));
}

bool HistorialPacienteArchivo::eliminar(int pos) {
    HistorialPaciente reg = leer(pos);
    reg.setEstado(false);
    return ArchivoManagerUtil::guardar(_nombreArchivo, pos, &reg, sizeof(HistorialPaciente));
}


int HistorialPacienteArchivo::buscarPorDNI(std::string dniPaciente) {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (!p) return -1;

    HistorialPaciente reg;
    int pos = 0;
    while (fread(&reg, sizeof(HistorialPaciente), 1, p)) {
        if (reg.getEstado() && reg.getDniPaciente() == dniPaciente) {
            fclose(p);
            return pos;
        }
        pos++;
    }

    fclose(p);
    return -1;
}


void HistorialPacienteArchivo::listarPorPaciente(std::string dniPaciente)
{
    PacienteArchivo pacArch("pacientes.dat");
    int posPac = pacArch.buscarPorDNI(dniPaciente);

    std::string nombre = "DESCONOCIDO";
    std::string apellido = "";

    if (posPac != -1) {
        Paciente p = pacArch.leer(posPac);
        nombre = p.getNombre();
        apellido = p.getApellido();
    }

    std::cout << "\n===== HISTORIAL DEL PACIENTE =====\n";
    std::cout << "Paciente: " << nombre << " " << apellido
              << " (DNI " << dniPaciente << ")\n\n";

    int cant = cantidadRegistros();
    if (cant == 0) {
        std::cout << "No hay historiales cargados.\n";
        return;
    }

    std::vector<HistorialPaciente> historiales(cant);
    leerTodos(historiales.data(), cant);

    bool encontrado = false;
    for ( auto h : historiales) {
        if (h.getEstado() && h.getDniPaciente() == dniPaciente) {
            std::cout << h.toString() << std::endl;
            encontrado = true;
        }
    }

    if (!encontrado) {
        std::cout << "No hay historiales registrados para este paciente.\n";
    }
}



void HistorialPacienteArchivo::listarPorFecha(Fecha fecha) {
    int cantidad = cantidadRegistros();
    if (cantidad == 0) {
        cout << "No hay historiales cargados.\n";
        return;
    }

    vector<HistorialPaciente> lista(cantidad);
    leerTodos(lista.data(), cantidad);

    bool encontrado = false;
    for (auto &r : lista) {
        Fecha f = r.getFechaAtencion();
        if (r.getEstado() &&
            f.getDia() == fecha.getDia() &&
            f.getMes() == fecha.getMes() &&
            f.getAnio() == fecha.getAnio()) {
            cout << r.toString() << endl;
            encontrado = true;
        }
    }

    if (!encontrado)
        cout << "No hay historiales registrados en esa fecha.\n";
}
