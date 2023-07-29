#include "Registro.h"
#include <sstream>

// Inicializa un objeto Registro sin ningún valor. Complejidad: O(1)
Registro::Registro() {
    mes = "";
    dia = "";
    horas = "";
    minutos = "";
    segundos = "";
    ip = "";
    puerto = "";
    falla = "";
    fechaHora = 0;
}

//Inicializa un objeto Registro con valores especificados y  convierte la estructura de fecha y hora a un valor de tiempo(timestamp). Complejidad: O(1)
Registro::Registro(std::string _mes, std::string _dia, std::string _horas, std::string _minutos, std::string _segundos, std::string _ip, std::string _puerto, std::string _falla) {
    mes = _mes;
    dia = _dia;
    horas = _horas;
    minutos = _minutos;
    segundos = _segundos;
    ip = _ip;
    puerto = _puerto;
    falla = _falla;

    dateStruct.tm_hour = 0;
    dateStruct.tm_min = 0;
    dateStruct.tm_sec = 0;
    dateStruct.tm_mday = 0;
    dateStruct.tm_mon = 0;
    dateStruct.tm_year = 0;
    dateStruct.tm_isdst = 0;

    std::istringstream hoursStream(_horas);
    hoursStream >> dateStruct.tm_hour;

    std::istringstream minutesStream(_minutos);
    minutesStream >> dateStruct.tm_min;

    std::istringstream secondsStream(_segundos);
    secondsStream >> dateStruct.tm_sec;

    std::istringstream dayStream(_dia);
    dayStream >> dateStruct.tm_mday;

    for (int i = 0; i < (int)meses.size(); i++) {
        if (meses[i] == mes)
            dateStruct.tm_mon = i;
    }

    dateStruct.tm_year = 2023 - 1900;
    fechaHora = mktime(&dateStruct);
}

//Devuelve una cadena de texto que representa todos los datos del objeto Registro. Complejidad: O(1)
std::string Registro::getAll() const {
    return mes + " " + dia + " " + horas + ":" + minutos + ":" + segundos + " " + ip + ":" + puerto + " " + falla;
}

//Devuelve el valor de tiempo (time_t) que representa la fecha y hora del registro. Complejidad: O(1)
time_t Registro::getFechaHora() {
    return fechaHora;
}

//Sobrecarga de operadores, realizan una comparación entre dos valores de tiempo. Complejidad: O(1)
bool Registro::operator==(const Registro& other) const {
    return this->fechaHora == other.fechaHora;
}

bool Registro::operator!=(const Registro& other) const {
    return this->fechaHora != other.fechaHora;
}

bool Registro::operator>(const Registro& other) const {
    return this->fechaHora > other.fechaHora;
}

bool Registro::operator<(const Registro& other) const {
    return this->fechaHora < other.fechaHora;
}

bool Registro::operator>=(const Registro& other) const {
    return this->fechaHora >= other.fechaHora;
}

bool Registro::operator<=(const Registro& other) const {
    return this->fechaHora <= other.fechaHora;
}
