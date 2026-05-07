#pragma once
#include "MedicoArchivo.h"
#include <vector>

class MedicoManager {
private:
    MedicoArchivo _archivo;

public:
    MedicoManager();

    void agregarMedico();
    void listarPorEspecialidad(int idEspecialidad);
    void listarTodos();
    void eliminarMedico(std::string dni);
    void listarPorApellido();
    void listarPorFechaIngreso(Fecha fechaDesde, Fecha fechaHasta);
    void eliminarMedico();
};
