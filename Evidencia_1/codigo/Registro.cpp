#include "Registro.h"

//Constructor de la clase Registro. Complejidad = O(1)
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

//Cosntructor de la clase registro, con los parametros de todos los atributos mes, dia, horas, minutos, segundos, ip, puerto y el mesaje de falla . Complejidad = O(1)
Registro::Registro(std::string _mes, std::string _dia, std::string _horas, std::string _minutos, std::string _segundos, std::string _ip, std::string _puerto, std::string _falla) {
    mes = _mes;
    dia = _dia;
    horas = _horas;
    minutos = _minutos;
    segundos = _segundos;
    ip = _ip;
    puerto = _puerto;
    falla = _falla;
    // Convertir a Linux timestamp
    dateStruct.tm_hour = std::stoi(horas);
    dateStruct.tm_min = std::stoi(minutos);
    dateStruct.tm_sec = std::stoi(segundos);
    dateStruct.tm_mday = std::stoi(dia);
    // Resuelve problemas de compatibilidad con Windows
    dateStruct.tm_isdst = 0;
    for (int i = 0; i < (int)meses.size(); i++) {
      if (meses[i] == mes)
        dateStruct.tm_mon = i;
    }
    dateStruct.tm_year = 2023 - 1900; // asumimos el año 2023
    // Obtener el Linux timestamp
    // mktime. (s.f.). cplusplus.com. Retrieved July 7, 2023, from https://cplusplus.com/reference/ctime/mktime/
    fechaHora = mktime(&dateStruct);
}

//Metodo que devuelve una cadena que contiene todos los datos del objeto Registro. Complejidad = O(1)
std::string Registro::getAll() const {
  return mes + " " + dia + " " + horas + ":" + minutos + ":" + segundos + " " + ip + ":" + puerto + " " + falla;  
}

//Metodo que devuelve la Fecha en formato timestamp. Complejidad = O(1)
time_t Registro::getFechaHora() {
  return fechaHora;
}

// sobrecarga de operadores de comparacion. Complejidad = O(1)
bool Registro::operator ==(const Registro &other) const {
  return this->fechaHora == other.fechaHora;
}

bool Registro::operator !=(const Registro &other) const {
  return this->fechaHora != other.fechaHora;
}

bool Registro::operator  >(const Registro &other) const {
  return this->fechaHora > other.fechaHora;
}

bool Registro::operator  <(const Registro &other) const{
  return this->fechaHora < other.fechaHora;
}

bool Registro::operator >=(const Registro &other) const{
  return this->fechaHora >= other.fechaHora;
}

bool Registro::operator <=(const Registro &other) const{
  return this->fechaHora <= other.fechaHora;
}
