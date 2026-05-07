#include "App.h"
#include <iostream>
#include <limits>
#include <cstdlib>
using namespace std;


#include "UsuarioManager.h"
#include "PacienteManager.h"
#include "MedicoManager.h"
#include "EspecialidadManager.h"
#include "ObraSocialManager.h"
#include "MedicoObraSocialManager.h"
#include "AgendaMedManager.h"
#include "TurnoManager.h"
#include "HistorialPacienteManager.h"
#include "FacturaManager.h"
#include "InformeManager.h"
#include "PacienteArchivo.h"

// =====================================================
//  UTILIDADES
// =====================================================
void App::clear() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void App::pause() {
    cout << "\nPresione ENTER para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}
// ADMIN POR DEFECTO
// =====================================================
void App::inicializarAdmin() {
    UsuarioManager um;

    Usuario aux;
    if (um.login("admin", "1234", aux)) {
        return;
    }

    Usuario u;
    u.setUsuario("admin");
    u.setContrasenia("1234");
    u.setRol("ADMIN");
    u.setDniPersona("");
    u.setEstado(true);

    UsuarioArchivo arch("usuarios.dat");
    arch.guardar(u);

    cout << "\n Usuario administrador creado automaticamente (admin / 1234)\n";
    pause();
}


// =====================================================
//  LOGIN
// =====================================================
bool App::login(string &dniMedicoLogueado, string &rol) {
    UsuarioManager um;
    string usuario, pass;

    clear();
    cout << "===== LOGIN =====\n\n";
    cout << "Usuario: ";
    cin >> usuario;
    cout << "Contrasenia: ";
    cin >> pass;

    Usuario u;
    if (!um.login(usuario, pass, u)) {
        cout << "\n Usuario o contrasenia incorrectos.\n";
        pause();
        return false;
    }

    rol = u.getRol();
    dniMedicoLogueado = u.getDniPersona();
    return true;
}

// =====================================================
//  MENÚ ADMINISTRADOR
// =====================================================
void App::mostrarMenuAdministrador() {
    int opc;
    do {
        clear();
        cout << "===== MENU ADMINISTRADOR =====\n\n";
        cout << "1) Pacientes\n";
        cout << "2) Medicos\n";
        cout << "3) Especialidades\n";
        cout << "4) Obras Sociales\n";
        cout << "5) Medico por Obra Social\n";
        cout << "6) Agendas Medicas\n";
        cout << "7) Turnos\n";
        cout << "8) Historial de Pacientes\n";
        cout << "9) Facturacion\n";
        cout << "10) Usuarios\n";
        cout << "11) Informes\n";
        cout << "0) Salir\n\n";
        cout << "Opcion: ";
        cin >> opc;

        switch (opc) {
        case 1: menuPacientes(); break;
        case 2: menuMedicos(); break;
        case 3: menuEspecialidades(); break;
        case 4: menuObrasSociales(); break;
        case 5: menuMedicoObraSocial(); break;
        case 6: menuAgendas(); break;
        case 7: menuTurnos(); break;
        case 8: menuHistoriales(); break;
        case 9: menuFacturacion(); break;
        case 10: menuUsuarios(); break;
        case 11: menuInformes(); break;
        case 0: break;
        default: cout << "Opcion invalida.\n"; pause();
        }
    } while (opc != 0);
}

// =====================================================
//  MENÚ SECRETARIO
// =====================================================
void App::mostrarMenuSecretario() {
    int opc;
    do {
        clear();
        cout << "===== MENU SECRETARIO =====\n\n";
        cout << "1) Registrar paciente\n";
        cout << "2) Pacientes\n";
        cout << "3) Turnos\n";
        cout << "4) Facturacion\n";
        cout << "0) Salir\n\n";
        cout << "Opcion: ";
        cin >> opc;

        switch (opc) {
        case 1: {
            PacienteManager().cargarNuevo();
            pause();
            break;
        }
        case 2: menuPacientes(); break;
        case 3: menuTurnos(); break;
        case 4: menuFacturacion(); break;

        case 0: break;
        default: cout << "Opcion invalida\n"; pause();
        }
    } while (opc != 0);
}

// =====================================================
//  MENÚ MÉDICO
// =====================================================
void App::mostrarMenuMedico(const string &dni) {
    int opc;
    do {
        clear();
        cout << "===== MENU MEDICO =====\n\n";
        cout << "1) Ver mi agenda\n";
        cout << "2) Ver mis turnos\n";
        cout << "3) Ver historial de un paciente\n";
        cout << "0) Salir\n\n";
        cout << "Opcion: ";
        cin >> opc;

        switch (opc) {
        case 1: {
            AgendaMedManager ag;
            ag.listarPorDniMedico(dni);
            pause();
            break;
        }
        case 2: {
            TurnoManager tm;
            tm.listarPorMedico(dni);
            pause();
            break;
        }
        case 3: {
            string dniPac;
            cout << "DNI paciente: ";
            cin >> dniPac;
            HistorialPacienteManager().listarPorPaciente(dniPac);
            pause();
            break;
        }
        case 0: break;
        default: cout << "Opcion invalida"; pause();
        }
    } while (opc != 0);
}

// =====================================================
//  SUBMENÚS (LLAMAN A MANAGERS)
// =====================================================

// ---------- PACIENTES ----------
void App::menuPacientes() {
    int o;
    do {
        clear();
        cout << "==== PACIENTES ====\n";
        cout << "1) Alta\n";
        cout << "2) Listar por apellido\n";
        cout << "3) Listar por obra social\n";
        cout << "4) Listar por fecha nacimiento\n";
        cout << "5) Baja logica de Paciente por DNI\n";
        cout << "0) Volver\n";
        cin >> o;

        PacienteManager pm;

        switch (o) {
        case 1: pm.cargarNuevo(); break;
        case 2: pm.listarPorApellido(); break;
        case 3: {
            int id; cout << "ID obra social: "; cin >> id;
            pm.listarPorObraSocial(id);
            break;
        }
        case 4: {
            Fecha f; f.cargarFecha();
            pm.listarPorFechaNacimiento(f);
            break;
        }
        case 5:

            pm.eliminarPaciente();
        }
        pause();
    } while(o != 0);
}

// ---------- MÉDICOS ----------
void App::menuMedicos() {
    int o;
    do {
        clear();
        cout << "==== MEDICOS ====\n";
        cout << "1) Alta\n";
        cout << "2) Ordenados por apellido\n";
        cout << "3) Buscar por especialidad\n";
        cout << "4) Listar por rango de fechas de ingreso\n";
        cout << "5) Baja logica de Medico por dni\n";
        cout << "0) Volver\n";
        cin >> o;

        MedicoManager m;

        switch(o){
        case 1:
            m.agregarMedico();
            break;

        case 2:
            m.listarPorApellido();
            break;

        case 3: {
            int idEsp;
            cout << "Ingrese ID de especialidad: ";
            cin >> idEsp;
            m.listarPorEspecialidad(idEsp);
            break;
        }

        case 4: {
            Fecha desde, hasta;
            cout << "Fecha DESDE:\n";
            desde.cargarFecha();

            cout << "Fecha HASTA:\n";
            hasta.cargarFecha();

            m.listarPorFechaIngreso(desde, hasta);
            break;
        }
        case 5: {
                m.eliminarMedico();
        }
        }

        if(o != 0) pause();

    } while(o != 0);
}

// ---------- ESPECIALIDADES ----------
void App::menuEspecialidades() {
    int o;
    do {
        clear();
        cout << "==== ESPECIALIDADES ====\n";
        cout << "1) Alta\n";
        cout << "2) Listar por orden alfabetico\n";
        cout << "3) Buscar por nombre\n";
        cout << "0) Volver\n";
        cin >> o;

        EspecialidadManager em;

        switch(o){
        case 1:
            em.agregar();
            break;

        case 2:
            em.listarAlfabeticamente();
            break;
         case 3:
            em.buscarPorNombre();
            break;

        }
        if(o != 0) pause();

    } while(o != 0);
}
// ---------- OBRAS SOCIALES ----------
void App::menuObrasSociales() {
    int o;
    do {
        clear();
        cout << "==== OBRAS SOCIALES ====\n";
        cout << "1) Alta\n";
        cout << "2) Modificar\n";
        cout << "3) Eliminar\n";
        cout << "4) Listar todas\n";
        cout << "5) Listar ordenado por nombre\n";
        cout << "6) Listar por tipo cobertura\n";
        cout << "0) Volver\n";
        cin >> o;

        ObraSocialManager om;

        switch(o){
        case 1: om.agregar(); break;
        case 2: om.modificar(); break;
        case 3: om.eliminar(); break;
        case 4: om.listarTodos(); break;
        case 5: om.listarPorNombre(); break;
        case 6: om.listarPorTipoCobertura(); break;
        }
        pause();
    } while(o != 0);
}

// ---------- MEDICO ↔ OS ----------
void App::menuMedicoObraSocial() {
    int o;
    MedicoObraSocialManager m;

    do {
        clear();
        cout << "==== RELACION MEDICO   OBRA SOCIAL ====\n";
        cout << "1) Agregar relacion\n";
        cout << "2) Listar relaciones\n";
        cout << "3) Listar obras sociales de un medico\n";
        cout << "4) Eliminar relacion\n";
        cout << "0) Volver\n";
        cin >> o;

        clear();
        switch(o){
        case 1:
            m.agregarRelacion();
            break;

        case 2:
            m.listarRelaciones();
            break;

        case 3: {
            cout << "DNI del medico: ";
            string dni;
            cin >> dni;
            m.listarObrasSocialesPorMedico(dni);
        }
        break;

        case 4: {
            cout << "DNI del medico: ";
            string dni;
            cin >> dni;
            cout << "ID Obra Social: ";
            int id;
            cin >> id;
            m.eliminarRelacion(dni, id);
        }
        break;
        }

        if (o != 0) pause();

    } while(o != 0);
}

// ---------- AGENDAS ----------
void App::menuAgendas() {
    int o;
    AgendaMedManager ag;

    do {
        clear();
        cout << "==== AGENDAS MEDICAS ====\n";
        cout << "1) Crear agenda\n";
        cout << "2) Mostrar todas\n";
        cout << "3) Buscar por DNI medico\n";
        cout << "4) Buscar por fecha\n";
        cout << "5) Modificar agenda\n";
        cout << "6) Eliminar agenda\n";
        cout << "0) Volver\n";
        cin >> o;

        switch(o){
        case 1:
            ag.agregarAgenda();
            break;

        case 2:
            ag.mostrarTodas();
            break;

        case 3: {
            string dni;
            cout << "DNI medico: ";
            cin >> dni;
            ag.listarPorDniMedico(dni);
        }
        break;

        case 4: {
            Fecha f;
            cout << "Cargar fecha:\n";
            f.cargarFecha();
            ag.listarPorFecha(f);
        }
        break;

        case 5:

            ag.modificarAgenda();

        break;

        case 6: {
            int id;
            cout << "ID Agenda: ";
            cin >> id;
            ag.eliminarAgenda(id);
        }
        break;
        }

        if (o != 0) pause();

    } while(o != 0);
}

// ---------- TURNOS ----------
void App::menuTurnos() {
    TurnoManager tm;
    int o;

    do {
        clear();
        cout << "==== TURNOS ====\n";
        cout << "1) Reservar turno\n";
        cout << "2) Cancelar turno\n";
        cout << "3) Finalizar turno\n";
        cout << "4) Buscar por fecha\n";
        cout << "5) Buscar por dni medico\n";
        cout << "6) Buscar por dni paciente\n";
        cout << "7) Buscar por estado\n";
        cout << "0) Volver\n";
        cin >> o;

        switch(o){
        case 1:
            tm.reservarTurno();
            break;

        case 2:
            tm.cancelarTurno();
            break;

        case 3:
            tm.finalizarTurno();
            break;

        case 4: {
            Fecha f;
            cout << "Ingrese fecha:\n";
            f.cargarFecha();
            tm.listarPorFecha(f);
            break;
        }

        case 5: {
            string dni;
            cout << "DNI medico: ";
            cin >> dni;
            tm.listarPorMedico(dni);
            break;
        }

        case 6: {
            string dni;
            cout << "DNI paciente: ";
            cin >> dni;
            tm.listarPorPaciente(dni);
            break;
        }

        case 7: {
            char est;
            cout << "Estado (L (libre) /R (reservado) /C (cancelado) /F (finalizado): ";
            cin >> est;
            tm.listarPorEstado(est);
            break;
        }
        }

        pause();
    } while(o != 0);
}


// ---------- HISTORIALES ----------
void App::menuHistoriales() {
    HistorialPacienteManager hm;
    int o;
    do {
        clear();
        cout << "==== HISTORIAL PACIENTES ====\n";
        cout << "1) Agregar\n";
        cout << "2) Buscar por  dni paciente\n";
        cout << "3) Listar por fecha\n";
        cout << "4) Listar todos\n";
        cout << "0) Volver\n";
        cin >> o;

        switch(o){
        case 1: hm.agregarHistorial(); break;
        case 2: {
            string dni; cout << "DNI: "; cin >> dni;
            hm.listarPorPaciente(dni);
            break;
        }
        case 3: {
            Fecha f; f.cargarFecha();
            hm.listarPorFecha(f);
            break;
        }
        case 4: hm.mostrarTodos(); break;
        }
        pause();
    } while(o != 0);
}

// ---------- FACTURACIÓN ----------
void App::menuFacturacion() {
    FacturaManager fm;
    int o;

    do {
        clear();
        cout << "==== FACTURAS ====\n";
        cout << "1) Generar factura\n";
        cout << "2) Listar por fecha\n";
        cout << "3) Listar por medico\n";
        cout << "4) Listar por forma de pago\n";
        cout << "0) Volver\n";
        cin >> o;

        clear();
        switch(o){

        case 1:
            fm.generarFactura();
            break;

        case 2: {
            Fecha f;
            cout << "Ingrese fecha:\n";
            f.cargarFecha();
            fm.listarPorFecha(f);
            break;
        }

        case 3: {
            string dni;
            cout << "DNI del medico: ";
            cin >> dni;
            fm.listarPorMedico(dni);
            break;
        }

        case 4: {
            string pago;
            cout << "Forma de pago (EFECTIVO/TARJETA/OS): ";
            cin >> pago;
            fm.listarPorFormaPago(pago);
            break;
        }
        }

        pause();

    } while(o != 0);
}

// ---------- USUARIOS ----------
void App::menuUsuarios() {
    UsuarioManager um;
    int o;
    do {
        clear();
        cout << "==== USUARIOS ====\n";
        cout << "1) Crear usuario\n";
        cout << "2) Listar usuarios\n";
        cout << "3) Dar de baja\n";
        cout << "0) Volver\n";
        cin >> o;

        switch(o){
        case 1: um.crearUsuario(); break;
        case 2: um.listarUsuarios(); break;
        case 3: um.eliminarUsuario(); break;
        }
        pause();
    } while(o != 0);
}

// ---------- INFORMES ----------

void App::menuInformes() {
    InformeManager im;
    int o;
    do {
        clear();
        cout << "==== INFORMES ====\n";
        cout << "1) Turnos por medico\n";
        cout << "2) Turnos por especialidad\n";
        cout << "3) Pacientes atendidos por periodo\n";
        cout << "4) Ingresos por mes\n";
        cout << "5) Ingresos por obra social\n";
        cout << "6) Turnos cancelados\n";
        cout << "7) Listado \n";
        cout << "0) Volver\n";
        cin >> o;

        clear();

        switch(o){

        case 1:
            im.turnosPorMedico();
            break;

        case 2:
            im.turnosPorEspecialidad();
            break;

        case 3: {
            Fecha desde, hasta;
            cout << "Ingrese fecha DESDE:\n";
            desde.cargarFecha();
            cout << "Ingrese fecha HASTA:\n";
            hasta.cargarFecha();
            im.pacientesAtendidosPorPeriodo(desde, hasta);
            break;
        }

        case 4: {
            int mes, anio;
            cout << "Mes (1-12): ";
            cin >> mes;
            cout << "Anio: ";
            cin >> anio;
            im.ingresosPorMes(mes, anio);
            break;
        }

        case 5: {
            int codigo;
            cout << "Codigo de obra social: ";
            cin >> codigo;
            im.ingresosPorObraSocial(codigo);
            break;
        }

        case 6:
            im.turnosCancelados();
            break;
        case 7:
            im.listadoMedicos();

        }
        pause();
    } while(o != 0);
}

// =====================================================
//  RUN
// =====================================================
void App::run() {
    inicializarAdmin();

    string rol, dniMedico;

    while (true) {
        if (!login(dniMedico, rol)) continue;

        if (rol == "ADMIN")     mostrarMenuAdministrador();
        if (rol == "SECRETARIO") mostrarMenuSecretario();
        if (rol == "MEDICO")     mostrarMenuMedico(dniMedico);
    }
}


