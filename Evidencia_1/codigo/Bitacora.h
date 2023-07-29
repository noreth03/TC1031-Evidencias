#ifndef _BITACORA_H_
#define _BITACORA_H_

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "Registro.h"

// Declaración de la clase Bitacora
class Bitacora {
  private:
    std::vector<Registro> listaRegistros; // Vector para almacenar los objetos de la clase Registro
    void merge(int low, int m, int high, unsigned int &compara); // Método privado para el algoritmo mergeSort

  public:
    Bitacora();
    ~Bitacora();
    void leerArchivo(std::string filePath);  // Método para leer un archivo y cargar los datos en listaRegistros
    void print();  //Funcion para imprimir la bitácora completa.
    std::vector<Registro> getListaRegistros() const; // Getter para obtener listaRegistros
    void swapSort(unsigned int &compara, unsigned int &swap); // Metodo del algoritmo de ordenamiento Swap Sort
    void mergeSort(int low, int high, unsigned int &compara);// Metodo del algoritmo de ordenamiento Merge Sort
    int busquedaBinaria(std::vector<Registro> &A, Registro key, unsigned int &compara);// Metodo del algoritmo de busqueda Binaria
    void guardarArchivo(std::string filePath); // Función para guardar la bitácora en un archivo
};


#endif  // _BITACORA_H_
