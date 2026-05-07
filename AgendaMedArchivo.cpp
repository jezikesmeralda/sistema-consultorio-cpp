#include "AgendaMedArchivo.h"


AgendaMedArchivo::AgendaMedArchivo(std::string nombre)
{
    _nombreArchivo = nombre;
    _tamanioRegistro = sizeof(AgendaMed);
    }


bool AgendaMedArchivo::guardar(AgendaMed registro)
{
    return ArchivoManagerUtil::guardar(_nombreArchivo, &registro, _tamanioRegistro);
}

bool AgendaMedArchivo::guardar(int pos, AgendaMed registro)
{
    return ArchivoManagerUtil::guardar(_nombreArchivo, pos, &registro, _tamanioRegistro);
}

AgendaMed AgendaMedArchivo::leer(int pos)
{
    AgendaMed reg;
    if (!ArchivoManagerUtil::leer(_nombreArchivo, pos, &reg, _tamanioRegistro))
    {
        reg.setEstado(false);
        reg.setIdAgenda(-1);
    }
    return reg;
}

int AgendaMedArchivo::leerTodos(AgendaMed *vec, int cantidad)
{

    return ArchivoManagerUtil::leerTodos(_nombreArchivo, vec, _tamanioRegistro, cantidad);
}


int AgendaMedArchivo::cantidadRegistros()
{
    return ArchivoManagerUtil::cantidadRegistros(_nombreArchivo, _tamanioRegistro);
}

int AgendaMedArchivo::buscarPorDniYFechaHora(std::string dni, Fecha fecha, Hora horaInicio, Hora horaFin )
{
    int cant = cantidadRegistros();
    AgendaMed reg;
    for (int i = 0; i < cant; i++)
    {
        ArchivoManagerUtil::leer(_nombreArchivo, i, &reg, _tamanioRegistro);
        if (reg.getEstado() &&
                reg.getDniMedico() == dni
                && reg.getFecha().toString() == fecha.toString()
                && reg.getHoraInicio().toString() == horaInicio.toString()
                && reg.getHoraFin().toString() == horaFin.toString())
        {
            return i;
        }
    }
    return -1;
}


int AgendaMedArchivo::buscarPorId(int idAgenda)
{
    int cant = cantidadRegistros();
    AgendaMed reg;
    for (int i = 0; i < cant; i++)
    {
        ArchivoManagerUtil::leer(_nombreArchivo, i, &reg, _tamanioRegistro);
        if (reg.getIdAgenda() == idAgenda) return i;
    }
    return -1;
}


bool AgendaMedArchivo::eliminar(int pos)
{
    AgendaMed reg = leer(pos);
    if (reg.getIdAgenda() == -1) return false;

    reg.setEstado(false);
    return guardar(pos, reg);
}

int AgendaMedArchivo::getNuevoId()
{
    int cant = cantidadRegistros();
    if (cant == 0) return 1;

    AgendaMed reg;
    int maxId = 0;

    for (int i = 0; i < cant; i++)
    {
        reg = leer(i);


        if (!reg.getEstado()) continue;

        if (reg.getIdAgenda() > maxId)
        {
            maxId = reg.getIdAgenda();
        }
    }

    return maxId + 1;
}

std::vector<int> AgendaMedArchivo::buscarTodasPorDniMedico(std::string dni)
{
    std::vector<int> posiciones;
    int cant = cantidadRegistros();
    AgendaMed reg;

    for (int i = 0; i < cant; i++)
    {
        reg = leer(i);
        if (std::string(reg.getDniMedico()) == dni && reg.getEstado())
        {
            posiciones.push_back(i);
        }
    }

    return posiciones;
}
