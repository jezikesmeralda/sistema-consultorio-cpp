#pragma once
#include "AgendaMed.h"
#include "ArchivoManagerUtil.h"
#include <string>

class AgendaMedArchivo {


private:
    std::string _nombreArchivo;
    int _tamanioRegistro;

public:
    AgendaMedArchivo(std::string nombreArchivo = "agendas_medicos.dat");

    bool guardar(AgendaMed registro);
    bool guardar(int pos, AgendaMed registro);
    AgendaMed leer(int pos);
    int leerTodos(AgendaMed *vec, int cantidad);
    int cantidadRegistros();
    bool eliminar(int pos);
    int getNuevoId();


    int buscarPorDniYFechaHora( std::string dni,  Fecha fecha,  Hora horaInicio, Hora horaFin);
    int buscarPorId(int idAgenda);

    std::vector<int> buscarTodasPorDniMedico(std::string dni);

};
