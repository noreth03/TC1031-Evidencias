#ifndef _REGISTRO_H_
#define _REGISTRO_H_

#include <string>
#include <vector>
#include <ctime>
#include <iostream>

// Declaración de la clase Registro
class Registro {

  private:
    std::string mes, dia, horas, minutos, segundos, ip, puerto, falla; 
    std::vector<std::string> meses = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    
    // mktime. (n.d.). cplusplus.com. Retrieved July 7, 2023, from https://cplusplus.com/reference/ctime/tm/
    struct tm dateStruct; 
    time_t fechaHora; 

  public:
    Registro();
    Registro(std::string _mes, std::string _dia, std::string _horas, std::string _minutos, std::string _segundos, std::string _ip, std::string _puerto, std::string _falla);
    std::string getAll() const;
    time_t getFechaHora();

    bool operator ==(const Registro &other) const;
    bool operator !=(const Registro &other) const;
    bool operator  >(const Registro &other) const;
    bool operator  <(const Registro &other) const;
    bool operator >=(const Registro &other) const;
    bool operator <=(const Registro &other) const;
};

#endif  // _REGISTRO_H_