#ifndef _IPADDRESS_H_
#define _IPADDRESS_H_

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <random>
#include "MaxHeap.h"

class Registro;

class IpAddress {
private:
    int accesos;
    std::string ipString;
    unsigned int ipDecimal;
    MaxHeap<IpAddress> listaTop;

public:
    IpAddress(std::string _ipString, unsigned int _ipDecimal, int _accesos);
    ~IpAddress();
    void countFreq(std::vector<Registro> &A);
    bool operator==(const IpAddress &other) const;
    bool operator!=(const IpAddress &other) const;
    bool operator>(const IpAddress &other) const;
    bool operator<(const IpAddress &other) const;
    bool operator>=(const IpAddress &other) const;
    bool operator<=(const IpAddress &other) const;
    std::string getIpString() const;
    int getAccesos() const;
};

// Constructor. O(1)
IpAddress::IpAddress(std::string _ipString, unsigned int _ipDecimal, int _accesos) {
    ipString = _ipString;
    ipDecimal = _ipDecimal;
    accesos = _accesos;
}

IpAddress::~IpAddress() {}

// Función para contar la frecuencia de acceso de cada dirección IP en el vector de registros "A" O(n^2).
//GeeksforGeeks. (2023d). Counting frequencies of array elements. GeeksforGeeks. https://www.geeksforgeeks.org/counting-frequencies-of-array-elements/
void IpAddress::countFreq(std::vector<Registro> &A) {
  std::ofstream outputFile("ips_con_mayor_acceso.txt");

  if (!outputFile.is_open()) {
    std::cout << "Error al abrir el archivo de salida." << std::endl;
  }
  
  unsigned int n = A.size();
  std::vector<IpAddress> tmp;
  std::vector<bool> visited(n, false);

  for (int i = 0; i < n; i++) {
    if (visited[i] == true)
      continue;
    int count = 1;
    for (int j = i + 1; j < n; j++) {
      if (A[i] == A[j]) {
        visited[j] = true;
         count++;
     }
   }
  std::string ipInfo = A[i].getIp();
  int cantidad = count;
  unsigned int ipDec = A[i].getIpDecimal();
  IpAddress tmpTop(ipInfo, ipDec, cantidad);
  tmp.push_back(tmpTop);
  }

    // Construye el Max Heap 
  for (int i = 0; i < tmp.size(); i++) {
    listaTop.push(tmp[i]); 
  }

for (int i = 0; i < 10; i++) {
        try {
          outputFile << listaTop.getTop().getIpString() << " - " << listaTop.getTop().getAccesos() << std::endl;
          std::cout << listaTop.getTop().getIpString() << " - " << listaTop.getTop().getAccesos() << std::endl;
            listaTop.pop();
        } catch (const std::out_of_range& e) {
            break;
        }
    }
      outputFile.close();
}
// Función para obtener la representación en formato de cadena de la dirección IP  O(1)
std::string IpAddress::getIpString() const {
    return ipString;
}
// Función para obtener la frecuencia de acceso de la dirección IP  O(1)
int IpAddress::getAccesos() const {
    return accesos;
}

// Sobrecarga de operadores de comparación
bool IpAddress::operator==(const IpAddress &other) const {
    return this->accesos == other.accesos;
}

bool IpAddress::operator!=(const IpAddress &other) const {
    return this->accesos != other.accesos;
}

bool IpAddress::operator>(const IpAddress &other) const {
    return this->accesos > other.accesos;
}

bool IpAddress::operator<(const IpAddress &other) const {
    return this->accesos < other.accesos;
}

bool IpAddress::operator>=(const IpAddress &other) const {
    return this->accesos >= other.accesos;
}

bool IpAddress::operator<=(const IpAddress &other) const {
    return this->accesos <= other.accesos;
}

#endif // _IPADDRESS_H_
