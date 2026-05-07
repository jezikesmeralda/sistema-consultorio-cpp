#include "MedicoArchivo.h"
#include <iostream>
using namespace std;

MedicoArchivo::MedicoArchivo(std::string nombreArchivo)
    : _nombreArchivo(nombreArchivo) {}

bool MedicoArchivo::guardar(Medico reg) {
    return ArchivoManagerUtil::guardar(_nombreArchivo, &reg, sizeof(Medico));
}

bool MedicoArchivo::guardar(int pos, Medico reg) {
    return ArchivoManagerUtil::guardar(_nombreArchivo, pos, &reg, sizeof(Medico));
}

Medico MedicoArchivo::leer(int pos) {
    Medico reg;
    ArchivoManagerUtil::leer(_nombreArchivo, pos, &reg, sizeof(Medico));
    return reg;
}

int MedicoArchivo::leerTodos(Medico *vec, int cantidad) {
    return ArchivoManagerUtil::leerTodos(_nombreArchivo, vec, sizeof(Medico), cantidad);
}

int MedicoArchivo::cantidadRegistros() {
    return ArchivoManagerUtil::cantidadRegistros(_nombreArchivo, sizeof(Medico));
}

int MedicoArchivo::buscarPorDNI(std::string dni) {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == nullptr) return -1;
    Medico reg;
    int pos = 0;
    while (fread(&reg, sizeof(Medico), 1, p)) {
        if (reg.getDni() == dni && reg.getEstado()) {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -1;
}

bool MedicoArchivo::eliminar(int pos) {
    Medico reg = leer(pos);
    reg.setEstado(false);
    return guardar(pos, reg);
}
