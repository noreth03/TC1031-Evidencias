#include "Registro.h"

Registro::Registro() {
  mes = "";
  dia = "";
  horas = "";
  minutos = "";
  segundos = "";
  ip = "";
  puerto = "";
  falla = "";
  ipDecimal = 0;
}

//Constructor que transforma la ip a un numero decimal. O(n)
Registro::Registro(std::string _mes, std::string _dia, std::string _horas, std::string _minutos, std::string _segundos, std::string _ip, std::string _puerto, std::string _falla) {
    mes = _mes;
    dia = _dia;
    horas = _horas;
    minutos = _minutos;
    segundos = _segundos;
    ip = _ip;
    puerto = _puerto;
    falla = _falla;
   
    // Conversion de la ip a numero decimal
    int posInit = 0;
    int posFound = 0;
    std::string splitted;
    std::vector<std::string> results;

    while (posFound >= 0) {
      posFound = ip.find(".", posInit);
      splitted = ip.substr(posInit, posFound-posInit);
      posInit = posFound + 1;
      results.push_back(splitted);
    } 

    int oct3 = std::stoi(results[0]);
    int oct2 = std::stoi(results[1]);
    int oct1 = std::stoi(results[2]);
    int oct0 = std::stoi(results[3]);
    ipDecimal = (oct3*std::pow(256,3)) + (oct2*std::pow(256,2)) + (oct1*256) + oct0;
}


 // Devuelve una cadena que contiene todos los detalles del registro en un formato legible. O(1)
std::string Registro::getAll() const{
  return mes + " " + dia + " " + horas + ":" + minutos + ":" + segundos + " " + ip + ":" + puerto + " " + falla;  
}

unsigned int Registro::getIpDecimal(){
  return ipDecimal;   // Devuelve el valor decimal de la dirección IP. O(1)

}

std::string Registro::getIp(){
  return ip;   // Devuelve la dirección IP como una cadena. O(1)

}

// sobrecarga de operadores de comparacion. O(1)
bool Registro::operator ==(const Registro &other) const {
  return this->ipDecimal == other.ipDecimal;
}

bool Registro::operator !=(const Registro &other) const {
  return this->ipDecimal != other.ipDecimal;
}

bool Registro::operator  >(const Registro &other) const {
  return this->ipDecimal > other.ipDecimal;
}

bool Registro::operator  <(const Registro &other) const{
  return this->ipDecimal < other.ipDecimal;
}

bool Registro::operator >=(const Registro &other) const{
  return this->ipDecimal >= other.ipDecimal;
}

bool Registro::operator <=(const Registro &other) const{
  return this->ipDecimal <= other.ipDecimal;
}