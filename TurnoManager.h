#pragma once
#pragma once
#include "TurnoArchivo.h"
#include "AgendaMedArchivo.h"
#include "PacienteArchivo.h"
#include <string>



class TurnoManager {
private:
    TurnoArchivo _archTurno;
    AgendaMedArchivo _archAgenda;

    void mostrarTurno( Turno t);
    bool existeAgenda(int idAgenda);

public:
    void generarTurnosParaAgenda(int idAgenda); // llamado desde AgendaMedManager

    void reservarTurno();
    void cancelarTurno();
    void finalizarTurno();

    void listarTodos();
    void listarPorFecha(Fecha fecha);
    void listarPorMedico(std::string dniMedico);
    void listarPorPaciente(std::string dniPaciente);
    void listarPorEstado(char estado);
};
