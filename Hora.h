#pragma once

#include <string>
using namespace std;

class Hora {
private:
    int _hora;
    int _minuto;

public:
    Hora();
    Hora(int hora, int minuto);

    int getHora();
    int getMinuto();

    void setHora(int hora);
    void setMinuto(int minuto);

    void cargarHora();
    string toString();
};
