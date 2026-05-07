#include "PacienteArchivo.h"
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

PacienteArchivo::PacienteArchivo(string nombreArchivo)
    : _nombreArchivo(nombreArchivo) {}

bool PacienteArchivo::guardar(Paciente reg) {
    return ArchivoManagerUtil::guardar(_nombreArchivo, &reg, sizeof(Paciente));
}

bool PacienteArchivo::guardar(int pos, Paciente reg) {
    return ArchivoManagerUtil::guardar(_nombreArchivo, pos, &reg, sizeof(Paciente));
}

Paciente PacienteArchivo::leer(int pos) {
    Paciente reg;
    ArchivoManagerUtil::leer(_nombreArchivo, pos, &reg, sizeof(Paciente));
    return reg;
}

int PacienteArchivo::leerTodos(Paciente* vec, int cantidad) {
    return ArchivoManagerUtil::leerTodos(_nombreArchivo, vec, sizeof(Paciente), cantidad);
}

int PacienteArchivo::cantidadRegistros() {
    return ArchivoManagerUtil::cantidadRegistros(_nombreArchivo, sizeof(Paciente));
}


int PacienteArchivo::buscarPorDNI(string dni) {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == nullptr) return -1;

    Paciente reg;
    int pos = 0;
    while (fread(&reg, sizeof(Paciente), 1, p)) {
        string dniArchivo = reg.getDni();
        dniArchivo.erase(remove(dniArchivo.begin(), dniArchivo.end(), ' '), dniArchivo.end());
        string dniBuscado = dni;
        dniBuscado.erase(remove(dniBuscado.begin(), dniBuscado.end(), ' '), dniBuscado.end());

        if (dniArchivo == dniBuscado && reg.getEstado()) {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -1;
}


bool PacienteArchivo::eliminarLogico(int pos) {
    Paciente reg = leer(pos);
    reg.setEstado(false);
    return guardar(pos, reg);
}
