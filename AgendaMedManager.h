#pragma once
#include "AgendaMedArchivo.h"
#include "MedicoArchivo.h"
#include "ArchivoManagerUtil.h"
#include <string>
#include <vector>

class AgendaMedManager {
private:
    AgendaMedArchivo _archivo;

public:
    AgendaMedManager();

    void agregarAgenda();
    void listarPorDniMedico(std::string dni);
    void listarPorFecha(Fecha fecha);
    void mostrarTodas();
    void modificarAgenda();
    void eliminarAgenda(int idAgenda);
};
