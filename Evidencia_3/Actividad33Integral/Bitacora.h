#ifndef _BITACORA_H_
#define _BITACORA_H_

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Registro.h"

class Bitacora {
private:
    std::vector<Registro> listaRegistros;

    // Funciones de ordenamiento (Heap Sort)
    void heapify(int n, int k);
    void heapSort(int n);

public:
    Bitacora();
    void leerArchivo(std::string filePath);
    std::vector<Registro> getListaRegistros() const;
    void ordenarBitacora();
    void guardarArchivo(const std::string &filePath);
    void ordenarTopIps();
};


#endif  // _BITACORA_H_