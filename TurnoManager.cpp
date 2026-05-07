#include "TurnoManager.h"

#include <algorithm> // find
#include <vector>
#include <iostream>

#include "MedicoArchivo.h"
#include "AgendaMedArchivo.h"
#include "TurnoArchivo.h"
#include "EspecialidadArchivo.h"
#include "Turno.h"
#include "Medico.h"
#include "AgendaMed.h"
using namespace std;

static int toMinutes( Hora h)
{
    return h.getHora() * 60 + h.getMinuto();
}

void TurnoManager::mostrarTurno( Turno t)
{
    cout << t.toString() << endl;
}

bool TurnoManager::existeAgenda(int idAgenda)
{
    return _archAgenda.buscarPorId(idAgenda) != -1;
}

// =====================================================
//  1. Generación automática (Llamado desde AgendaMedManager)
// =====================================================
void TurnoManager::generarTurnosParaAgenda(int idAgenda)
{
    AgendaMedArchivo archAg("agendas_medicos.dat");
    int pos = archAg.buscarPorId(idAgenda);
    if (pos == -1)
    {
        cout << "No se encontró la agenda.\n";
        return;
    }

    AgendaMed ag = archAg.leer(pos);



    int inicio = ag.getHoraInicio().getHora() * 60 + ag.getHoraInicio().getMinuto();
    int fin    = ag.getHoraFin().getHora() * 60 + ag.getHoraFin().getMinuto();


    for (int m = inicio; m < fin; m += 30)
    {
        int h = m / 60;
        int min = m % 60;

        Turno t;
        t.setIdTurno(_archTurno.generarNuevoId());
        t.setIdAgenda(idAgenda);
        t.setEstadoTurno('L');
        t.setEstadoLogico(true);
        t.setDniPaciente("");
        t.setMotivo("");

        Hora horaTurno;
        horaTurno.setHora(h);
        horaTurno.setMinuto(min);
        t.setHoraTurno(horaTurno);

        _archTurno.guardar(t);
    }

    cout << "Turnos generados correctamente.\n";


}

void TurnoManager::reservarTurno()
{
    MedicoArchivo archM;
    AgendaMedArchivo archA;
    TurnoArchivo archT;
    EspecialidadArchivo archE;

    // 1) listar medicos
    int cantM = archM.cantidadRegistros();
    if (cantM == 0)
    {
        cout << "No hay médicos cargados.\n";
        return;
    }

    cout << "\n=== LISTA DE MÉDICOS ===\n";
    vector<int> posMedicos;
    for (int i = 0; i < cantM; ++i)
    {
        Medico m = archM.leer(i);
        if (!m.getEstado()) continue;

        string descEsp;
        int idEsp = m.getIdEspecialidad();
        int posE = archE.buscarPorId(idEsp);
        if (posE != -1)
        {
            Especialidad e = archE.leer(posE);
            descEsp = e.getDescripcion();
        }

        cout << posMedicos.size() + 1 << ") "
             << m.getApellido() << ", " << m.getNombre()
             << " | Esp(ID " << idEsp << "): " << descEsp << endl;

        posMedicos.push_back(i);
    }

    if (posMedicos.empty())
    {
        cout << "No hay medicos activos.\n";
        return;
    }

    // 2) seleccionar medico
    int selMed;
    cout << "\nSeleccione un medico (numero): ";
    cin >> selMed;
    if (selMed < 1 || selMed > (int)posMedicos.size())
    {
        cout << "Opcion invalida.\n";
        return;
    }
    int posMed = posMedicos[selMed - 1];
    Medico medicoSeleccionado = archM.leer(posMed);

    // 3) buscar agendas del medico
    int cantA = archA.cantidadRegistros();
    vector<int> agendasDelMedico;
    for (int i = 0; i < cantA; ++i)
    {
        AgendaMed a = archA.leer(i);
        if (!a.getEstado()) continue;
        if (a.getDniMedico() == medicoSeleccionado.getDni())
            agendasDelMedico.push_back(i);
    }
    if (agendasDelMedico.empty())
    {
        cout << "El medico no tiene agendas cargadas.\n";
        return;
    }

    // 4) listar turnos libres de esas agendas (obteniendo fecha/hora desde Agenda)
    int cantT = archT.cantidadRegistros();
    vector<int> turnosLibres;
    cout << "\n=== TURNOS DISPONIBLES PARA " << medicoSeleccionado.getApellido()
         << " " << medicoSeleccionado.getNombre() << " ===\n";

    for (int i = 0; i < cantT; ++i)
    {
        Turno t;
        if (!archT.leer(i, t)) continue;         // TurnoArchivo tiene leer(pos, Turno&)
        if (!t.getEstadoLogico() || t.getEstadoTurno() != 'L') continue;

        int posAg = archA.buscarPorId(t.getIdAgenda());
        if (posAg == -1) continue;


        if (find(agendasDelMedico.begin(), agendasDelMedico.end(), posAg) != agendasDelMedico.end())
        {
            AgendaMed ag = archA.leer(posAg);
            cout << turnosLibres.size() + 1 << ") Agenda ID: " << ag.getIdAgenda()
     << " | Fecha: " << ag.getFecha().toString()
     << " | Hora: " << t.getHoraTurno().toString() << "\n";
            turnosLibres.push_back(i);
        }
    }

    if (turnosLibres.empty())
    {
        cout << "No hay turnos libres para ese medico.\n";
        return;
    }

    // 5) seleccionar turno
    int selTurno;
    cout << "\nSeleccione un turno (numero): ";
    cin >> selTurno;
    if (selTurno < 1 || selTurno > (int)turnosLibres.size())
    {
        cout << "Opcion invalida.\n";
        return;
    }
    int posTurno = turnosLibres[selTurno - 1];

string dniPac;
PacienteArchivo pacArch("pacientes.dat");
int posPac;
do {
    cout << "DNI del paciente: ";
    cin >> dniPac;
    posPac = pacArch.buscarPorDNI(dniPac);
    if (posPac == -1)
        cout << "El paciente no existe. Intente nuevamente.\n";
} while (posPac == -1);

cin.ignore();
cout << "Motivo de consulta: ";
string motivo;
getline(cin, motivo);

// 7) reservar
Turno tFinal;
if (!archT.leer(posTurno, tFinal)) {
    cout << "Error leyendo turno.\n";
    return;
}
tFinal.cargarReserva(dniPac, motivo);
archT.guardar(posTurno, tFinal);
cout << "Turno reservado correctamente.\n";
}




void TurnoManager::cancelarTurno()
{
    int idTurno;
    cout << "ID de turno a cancelar: ";
    cin >> idTurno;

    int cant = _archTurno.cantidadRegistros();
    Turno t;

    for (int i = 0; i < cant; i++)
    {
        if (!_archTurno.leer(i, t)) continue;
        if (t.getEstadoLogico() &&
                t.getIdTurno() == idTurno &&
                t.getEstadoTurno() == 'R')
        {
            t.setEstadoTurno('C');   // CANCELADO
            _archTurno.guardar(i, t);
            cout << "Turno cancelado.\n";
            return;
        }
    }

    cout << "No se encontro el turno o no estaba reservado.\n";
}

// =====================================================
//  Finalizar turno
// =====================================================
void TurnoManager::finalizarTurno()
{
    int idTurno;
    cout << "ID de turno a finalizar: ";
    cin >> idTurno;

    int cant = _archTurno.cantidadRegistros();
    Turno t;

    for (int i = 0; i < cant; i++)
    {
        if (!_archTurno.leer(i, t)) continue;
        if (t.getEstadoLogico() &&
                t.getIdTurno() == idTurno &&
                t.getEstadoTurno() == 'R')
        {
            t.setEstadoTurno('F');   // FINALIZADO
            _archTurno.guardar(i, t);
            cout << "Turno finalizado.\n";
            return;
        }
    }

    cout << "No se encontro turno reservado.\n";
}

// =====================================================
//  Listar todos
// =====================================================
void TurnoManager::listarTodos()
{
    int cant = _archTurno.cantidadRegistros();
    vector<Turno> vec(cant);
    _archTurno.leerTodos(vec.data(), cant);

    for (Turno &t : vec)
        if (t.getEstadoLogico())
            mostrarTurno(t);
}

// =====================================================
//  Listar por fecha
// =====================================================
void TurnoManager::listarPorFecha(Fecha fecha)
{
    int cantT = _archTurno.cantidadRegistros();
    int encontrados = 0;

    for (int i = 0; i < cantT; i++)
    {
        Turno t;
        if (!_archTurno.leer(i, t)) continue;
        if (!t.getEstadoLogico()) continue;

        int posAg = _archAgenda.buscarPorId(t.getIdAgenda());
        if (posAg == -1) continue;



        AgendaMed ag = _archAgenda.leer(posAg);
        if (ag.getFecha().toString() == fecha.toString())
            mostrarTurno(t);
        encontrados++;
    }

    if (encontrados == 0)
        cout << "No se encontraron turnos para la fecha " << fecha.toString() << ".\n";
}

// =====================================================
//  Listar por medico
// =====================================================
void TurnoManager::listarPorMedico(string dniMedico)
{
    int cantT = _archTurno.cantidadRegistros();
    int encontrados = 0;

    for (int i = 0; i < cantT; i++)
    {
        Turno t;
        if (!_archTurno.leer(i, t)) continue;
        if (!t.getEstadoLogico()) continue;

        int posAg = _archAgenda.buscarPorId(t.getIdAgenda());
        if (posAg == -1) continue;

        AgendaMed ag = _archAgenda.leer(posAg);

        if (ag.getDniMedico() == dniMedico)
            mostrarTurno(t);
        encontrados++;
    }
    if (encontrados == 0)
        cout << "No se encontraron turnos para el médico con DNI " << dniMedico << ".\n";
}

// =====================================================
//  Listar por paciente
// =====================================================
void TurnoManager::listarPorPaciente(string dniPaciente)
{
    int cant = _archTurno.cantidadRegistros();
    int encontrados = 0;
    Turno t;

    for (int i = 0; i < cant; i++)
    {
        if (!_archTurno.leer(i, t)) continue;
        if (t.getEstadoLogico() && t.getDniPaciente() == dniPaciente)
            mostrarTurno(t);
        encontrados++;
    }
    if (encontrados == 0)
        cout << "No se encontraron turnos para el paciente con DNI " << dniPaciente << ".\n";
}

// =====================================================
//  Listar por estado
// =====================================================
void TurnoManager::listarPorEstado(char estado)
{

    estado = static_cast<char>(toupper(static_cast<unsigned char>(estado)));

    int cant = _archTurno.cantidadRegistros();
    if (cant == 0)
    {
        cout << "No hay turnos registrados.\n";
        return;
    }

    Turno t;
    int encontrados = 0;

    for (int i = 0; i < cant; i++)
    {

        bool ok = _archTurno.leer(i, t);
        if (!ok)
        {

            continue;
        }


        if (!t.getEstadoLogico()) continue;


        char estadoTurno = t.getEstadoTurno();
        estadoTurno = static_cast<char>(toupper(static_cast<unsigned char>(estadoTurno)));

        if (estadoTurno == estado)
        {
            mostrarTurno(t);
            encontrados++;
        }
    }

    if (encontrados == 0)
        cout << "No se encontraron turnos con estado '" << estado << "'.\n";
}
