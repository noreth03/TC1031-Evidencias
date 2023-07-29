#ifndef _IPADDRESS_H_
#define _IPADDRESS_H_

#include <cmath>
#include <iostream>
#include <vector>

class ipAddress {
    private:
      std::string ipString;
      int ipIndex;
      int value;
      unsigned int ipValue;
      int degreeIn; // Total de direcciones que acceden al vértice de esta ip
      int degreeOut; // Total de direcciones que el vértice de esta ip accede

    public:
      ipAddress();
      ipAddress(std::string _ip, int idx);
      std::string getIp();
      unsigned int getIpValue();
      int getIpIndex();
      
      void setDegreeIn(int g); // Establecer el grado de entrada
      void addToDegreeIn(); // Incrementar el grado de entrada
      int getDegreeIn(); // Obtener el grado de entrada
      void setDegreeOut(int g); // Establecer el grado de salida
      void addToDegreeOut(); // Incrementar el grado de salida
      int getDegreeOut(); // Obtener el grado de salida
      std::string toString();


      bool operator ==(const ipAddress&) const;
      bool operator !=(const ipAddress&) const;
      bool operator >(const ipAddress&) const;
      bool operator >=(const ipAddress&) const;
      bool operator <(const ipAddress&) const;
      bool operator <=(const ipAddress&) const;
};


#endif
