#include "MedicoObraSocialArchivo.h"
#include <cstdio>

MedicoObraSocialArchivo::MedicoObraSocialArchivo(std::string nombreArchivo)
    : _nombreArchivo(nombreArchivo) {}

bool MedicoObraSocialArchivo::guardar(MedicoObraSocial reg)
{
    return ArchivoManagerUtil::guardar(_nombreArchivo, &reg, sizeof(MedicoObraSocial));
}

bool MedicoObraSocialArchivo::guardar(int pos, MedicoObraSocial reg)
{
    return ArchivoManagerUtil::guardar(_nombreArchivo, pos, &reg, sizeof(MedicoObraSocial));
}

MedicoObraSocial MedicoObraSocialArchivo::leer(int pos)
{
    MedicoObraSocial reg;
    if (!ArchivoManagerUtil::leer(_nombreArchivo, pos, &reg, sizeof(MedicoObraSocial)))
    {
        reg.setIdRelacion(-1);
    }
    return reg;
}

int MedicoObraSocialArchivo::leerTodos(MedicoObraSocial* vec, int cantidad)
{
    return ArchivoManagerUtil::leerTodos(_nombreArchivo, vec, sizeof(MedicoObraSocial), cantidad);
}

int MedicoObraSocialArchivo::cantidadRegistros()
{
    return ArchivoManagerUtil::cantidadRegistros(_nombreArchivo, sizeof(MedicoObraSocial));
}


int MedicoObraSocialArchivo::getNuevoId()
{
    int cant = cantidadRegistros();
    if (cant == 0) return 1;

    MedicoObraSocial reg;
    int maxId = 0;

    for (int i = 0; i < cant; i++)
    {
        reg = leer(i);
        if (!reg.getEstado()) continue;

        if (reg.getIdRelacion() > maxId)
        {
            maxId = reg.getIdRelacion();
        }
    }
    return maxId + 1;
}

int MedicoObraSocialArchivo::buscarRelacion(std::string dniMedico, int idObraSocial)
{
    int cantidad = cantidadRegistros();
    MedicoObraSocial reg;

    for (int i = 0; i < cantidad; i++)
    {
        ArchivoManagerUtil::leer(_nombreArchivo, i, &reg, sizeof(MedicoObraSocial));
        if (reg.getDniMedico() == dniMedico &&
                reg.getIdObraSocial() == idObraSocial &&
                reg.getEstado())
        {
            return i;
        }
    }
    return -1;
}


bool MedicoObraSocialArchivo::eliminar(int pos)
{
    MedicoObraSocial reg = leer(pos);
    if (reg.getIdRelacion() == -1) return false;

    reg.setEstado(false);
    return guardar(pos, reg);
}
