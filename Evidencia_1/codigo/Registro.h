#ifndef _REGISTRO_H_
#define _REGISTRO_H_

#include <string>
#include <vector>
#include <ctime>
#include <iostream>

// Declaración de la clase Registro
class Registro {

  private:
    std::string mes, dia, horas, minutos, segundos, ip, puerto, falla; //las variables que compone cada registro
    std::vector<std::string> meses = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"}; //vector que almacena los 12 meses
    
    // mktime. (n.d.). cplusplus.com. Retrieved July 7, 2023, from https://cplusplus.com/reference/ctime/tm/
    struct tm dateStruct; //estructura que almacena información relacionada con fechas y horas, como año, mes, día, hora, minuto y segundo.
    // Linux timestamp (segundos transcurridos desde el 1 de enero de 1970)
    time_t fechaHora; //Fecha en forma timestamp

  public:
    Registro();//declaracion del constructor registro
    Registro(std::string _mes, std::string _dia, std::string _horas, std::string _minutos, std::string _segundos, std::string _ip, std::string _puerto, std::string _falla);//constructor que inicializa las variables miembro de la clase Registro con los valores proporcionados
    std::string getAll() const;//Devuelve una cadena que representa todos los datos del objeto Registro
    time_t getFechaHora();//Devuelve la fecha en formato timestamp
    // sobrecarga de operadores de comparacion
    bool operator ==(const Registro &other) const;
    bool operator !=(const Registro &other) const;
    bool operator  >(const Registro &other) const;
    bool operator  <(const Registro &other) const;
    bool operator >=(const Registro &other) const;
    bool operator <=(const Registro &other) const;
};

#endif  // _REGISTRO_H_
