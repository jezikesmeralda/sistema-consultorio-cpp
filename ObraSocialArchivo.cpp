#pragma once
#include "ObraSocialArchivo.h"

ObraSocialArchivo::ObraSocialArchivo(std::string nombre)
    :_nombreArchivo (nombre)
{
}

bool ObraSocialArchivo::guardar(ObraSocial registro) {
    return ArchivoManagerUtil::guardar(_nombreArchivo, &registro, sizeof(ObraSocial));
}

bool ObraSocialArchivo::guardar(int pos, ObraSocial registro) {
    return ArchivoManagerUtil::guardar(_nombreArchivo, pos, &registro, sizeof(ObraSocial));
}

int ObraSocialArchivo::leerTodos(ObraSocial* registros, int cantidad) {
    return ArchivoManagerUtil::leerTodos(_nombreArchivo, registros, sizeof(ObraSocial), cantidad);
}

ObraSocial ObraSocialArchivo::leer(int pos) {
    ObraSocial reg;
    if (!ArchivoManagerUtil::leer(_nombreArchivo, pos, &reg, sizeof(ObraSocial))) {
        reg.setIdObraSocial(-1);
    }
    return reg;
}

int ObraSocialArchivo::cantidadRegistros() {
    return ArchivoManagerUtil::cantidadRegistros(_nombreArchivo, sizeof(ObraSocial));
}


int ObraSocialArchivo::generarNuevoId()
{
   int cant = cantidadRegistros();
    if (cant == 0) return 1;

    ObraSocial reg;
    int maxId = 0;

    for (int i = 0; i < cant; i++) {
       reg = leer(i);


        if (!reg.getEstado()) continue;

        if (reg.getIdObraSocial() > maxId) {
            maxId = reg.getIdObraSocial();
        }
    }

    return maxId + 1;
}


int ObraSocialArchivo::buscarPorId(int id) {
    int cantidad = cantidadRegistros();
    ObraSocial reg;

    for (int i = 0; i < cantidad; i++) {
        ArchivoManagerUtil::leer(_nombreArchivo, i, &reg, sizeof(ObraSocial));
        if (reg.getIdObraSocial() == id && reg.getEstado())
            return i;
    }

    return -1;
}


bool ObraSocialArchivo::eliminar(int pos)
{
    ObraSocial reg = leer(pos);
    if (reg.getIdObraSocial() != -1)
    {
        reg.setEstado(false);
        return guardar(pos, reg);
    }
    return false;
}
