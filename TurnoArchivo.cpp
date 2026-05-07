#include "TurnoArchivo.h"

TurnoArchivo::TurnoArchivo(std::string nombre)
    : _nombreArchivo(nombre), _tamanioRegistro(sizeof(Turno)) {}

bool TurnoArchivo::guardar(Turno reg) {
    return ArchivoManagerUtil::guardar(_nombreArchivo, &reg, _tamanioRegistro);
}

bool TurnoArchivo::guardar(int pos, Turno reg) {
    return ArchivoManagerUtil::guardar(_nombreArchivo, pos, &reg, _tamanioRegistro);
}

bool TurnoArchivo::leer(int pos, Turno &reg) {
    return ArchivoManagerUtil::leer(_nombreArchivo, pos, &reg, _tamanioRegistro);
}

int TurnoArchivo::leerTodos(Turno *vec, int cantidad) {
    return ArchivoManagerUtil::leerTodos(_nombreArchivo, vec, _tamanioRegistro, cantidad);
}

int TurnoArchivo::cantidadRegistros() {
    return ArchivoManagerUtil::cantidadRegistros(_nombreArchivo, _tamanioRegistro);
}

int TurnoArchivo::generarNuevoId() {
 int cant = cantidadRegistros();
    if (cant == 0) return 1;

    Turno reg;
    int maxId = 0;

    for (int i = 0; i < cant; i++) {
        leer(i, reg);

        if (reg.getIdTurno() > maxId) {
            maxId = reg.getIdTurno();
        }
    }

    return maxId + 1;
}


int TurnoArchivo::buscarPorId(int idTurno) {
    int cant = cantidadRegistros();
    Turno reg;

    for (int i = 0; i < cant; i++) {
        if (leer(i, reg)) {
            if (reg.getIdTurno() == idTurno && reg.getEstadoLogico())
                return i;
        }
    }

    return -1;
}
