/*
* Autores: 
*  - Héctor Calderón Reyes: A01350637
*  - Noreth Sofia Villalpando Saldaña: A01368579
*
* Fecha de creación: 23 de Julio de 2023
*
* Act 3.3 - Actividad Integral de BST (Evidencia Competencia)
*
* Ejemplo que implementa objetos de la clase Registro
* que contienen una fecha-hora convertida a Linux timestamp
* para realizar comparaciones (sobrecarga de operadores)
*
* Instrucciones de compilación y ejecución:
*
* Compilacion para debug:  
*    g++ -std=c++17 -g -o main *.cpp 
* Ejecucion con valgrind:
*    nix-env -iA nixpkgs.valgrind
*    valgrind --leak-check=full ./main
*
* Compilacion para ejecucion:  
*    g++ -std=c++17 -O3 -o main *.cpp 
* Ejecucion:
*    ./main
**/

#include <iostream>
#include "Bitacora.h"

int main() {
  Bitacora miBitacora;   // Crear una instancia de la clase Bitacora
  miBitacora.leerArchivo("bitacoraHeap.txt"); 
    // Guardar la bitácora ordenada en un nuevo archivo
  miBitacora.ordenarBitacora();
  std::string nuevoArchivo = "bitacora_ordenada.txt";
  miBitacora.guardarArchivo(nuevoArchivo);
  // Mostrar los 10 IPs con más accesos en la bitácora
  std::cout<< "Los 10 IPs con más accesos:" << std::endl << std::endl;
  miBitacora.ordenarTopIps();

  return 0;
}
