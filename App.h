#pragma once
#include <string>

class App {
public:
    void run();

private:
    // ---- Menús por rol ----
    void mostrarMenuAdministrador();
    void mostrarMenuSecretario();
    void mostrarMenuMedico(const std::string &dniMedico);

    // ---- Submenús ----
    void menuPacientes();
    void menuMedicos();
    void menuEspecialidades();
    void menuObrasSociales();
    void menuMedicoObraSocial();
    void menuAgendas();
    void menuTurnos();
    void menuHistoriales();
    void menuFacturacion();
    void menuUsuarios();
    void menuInformes();

    // ---- Login ----
    bool login(std::string &dniMedicoLogueado, std::string &rol);

    // ---- Utilidades ----
    void clear();
    void pause();

    void inicializarAdmin();
};
