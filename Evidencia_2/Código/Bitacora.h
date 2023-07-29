#ifndef _BITACORA_H_
#define _BITACORA_H_

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "Registro.h"
#include "DLinkedList.h"

class Bitacora {
private:
    DLinkedList<Registro> listaRegistros;

public:
    Bitacora();
    void leerArchivo(const std::string& filePath);
    void print() const;
    const DLinkedList<Registro>& getListaRegistros() const;
    void ordenarBitacora();
    void buscarRegistrosPorFecha();
    void guardarArchivo(const std::string& filePath);
};

#endif  // _BITACORA_H_
