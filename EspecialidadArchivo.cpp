#include "EspecialidadArchivo.h"
#include <cstdio>

EspecialidadArchivo::EspecialidadArchivo(std::string nombre)
    : _nombreArchivo(nombre) {}

bool EspecialidadArchivo::guardar(Especialidad reg)
{
    return ArchivoManagerUtil::guardar(_nombreArchivo, &reg, sizeof(Especialidad));
}

bool EspecialidadArchivo::guardar(int pos, Especialidad reg)
{
    return ArchivoManagerUtil::guardar(_nombreArchivo, pos, &reg, sizeof(Especialidad));
}


Especialidad EspecialidadArchivo::leer(int pos)
{
    Especialidad reg;
    ArchivoManagerUtil::leer(_nombreArchivo, pos, &reg, sizeof(Especialidad));
    return reg;
}

int EspecialidadArchivo::leerTodos(Especialidad *vec, int cantidad)
{
    return ArchivoManagerUtil::leerTodos(_nombreArchivo, vec, sizeof(Especialidad), cantidad);
}

int EspecialidadArchivo::cantidadRegistros()
{
    return ArchivoManagerUtil::cantidadRegistros(_nombreArchivo, sizeof(Especialidad));
}

int EspecialidadArchivo::buscarPorDescripcion(std::string desc)
{
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (!p) return -1;

    Especialidad reg;
    int pos = 0;
    while (fread(&reg, sizeof(Especialidad), 1, p))
    {
        if (reg.getEstado() && reg.getDescripcion() == desc)
        {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -1;
}

int EspecialidadArchivo::generarNuevoId()
{
    int cant = cantidadRegistros();
    if (cant == 0) return 1;

    Especialidad reg;
    int maxId = 0;

    for (int i = 0; i < cant; i++)
    {

        reg = leer(i);
        if (!reg.getEstado()) continue;

        if (reg.getIdEspecialidad() > maxId)
        {
            maxId = reg.getIdEspecialidad();
        }
    }


    return maxId + 1;
}

bool EspecialidadArchivo::eliminar(int pos)
{
    Especialidad reg = leer(pos);
    reg.setEstado(false);
    return ArchivoManagerUtil::guardar(_nombreArchivo, pos, &reg, sizeof(Especialidad));
}
int EspecialidadArchivo::buscarPorId(int id)
{
    int cant = cantidadRegistros();
    Especialidad obj;

    for (int i = 0; i < cant; i++)
    {
        obj = leer(i);
        if (obj.getIdEspecialidad() == id)
            return i;
    }
    return -1;
}
