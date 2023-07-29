/*
 * Autores: 
 *  - Héctor Calderón Reyes: A01350637
 *  - Noreth Sofia Villalpando Saldaña: A01368579
 *
 * Fecha de creación: 7 de Julio de 2023
 *
 * Actividad: Act 1.3 - Actividad Integral de Conceptos Básicos y Algoritmos Fundamentales (Evidencia Competencia)
 *
 * Descripción: Este programa lee una bitácora de eventos de seguridad, la ordena y permite buscar eventos en un rango de fechas.
 *
 * Instrucciones de compilación y ejecución:
 * 
 * Para compilar en modo de depuración (Debug):
 * g++ -std=c++17 -Wall -g -o main *.cpp
 *
 * Para compilar en modo de ejecución (Release):
 * g++ -std=c++17 -O3 -o main *.cpp
 *
 * Para ejecutar el programa:
 * ./main
 * 3. Cuando se le solicite, introduzca la fecha de inicio y la fecha de fin en el formato 'MMM DD HH:MM:SS' (por ejemplo, 'Jun 01 00:22:36')
 * 4. El programa mostrará todos los eventos en el rango de fechas especificado y guardará la bitácora ordenada en el archivo 'bitacora_ordenada.txt'
 */

#include <iostream>
#include "Bitacora.h"

int main() {
  //Inicializa un objeto de la clase bitacora y lee un archivo que carga los datos en listaRegistros
  Bitacora bitacora;
  bitacora.leerArchivo("bitacora.txt");

  //Swap Sort
  unsigned int compara = 0, swap = 0;
  bitacora.swapSort(compara, swap);
  std::cout << "Swap sort: " << compara << " comparaciones, " << swap << " swaps\n";

  // Resetear los contadores
  compara = 0;
  swap = 0;
  
  //Merge Sort
  bitacora.mergeSort(0, bitacora.getListaRegistros().size() - 1, compara);
  std::cout << "Merge sort: " << compara << " comparaciones, " << " 0 swaps\n";

  //Captura las fechas de inicio y fin ingresadas por el usuario 
  std::string inicio, fin;
  std::cout << "Ingrese la fecha de inicio (formato: Jun 01 00:22:36): ";
  std::getline(std::cin, inicio);
  std::cout << "Ingrese la fecha de fin (formato: Jun 01 00:22:36): ";
  std::getline(std::cin, fin);

  // Verificar que las fechas ingresadas tienen la longitud correcta
  if (inicio.length() != 15 || fin.length() != 15) {
    std::cout << "Formato de fecha incorrecto. Por favor, ingrese la fecha en el formato correcto: Jun 01 00:22:36\n";
    return 1; // termina el programa con un código de error
  }

  // Crear objetos Registro con las fechas de inicio y fin ingresadas
  Registro regInicio(inicio.substr(0, 3), inicio.substr(4, 2), inicio.substr(7, 2), inicio.substr(10, 2), inicio.substr(13, 2), "", "", "");
  Registro regFin(fin.substr(0, 3), fin.substr(4, 2), fin.substr(7, 2), fin.substr(10, 2), fin.substr(13, 2), "", "", "");

  //Obtener una lista de registros de la bitácora y se realizan búsquedas binarias para encontrar los índices de inicio y fin ingresadas
  std::vector<Registro> registros = bitacora.getListaRegistros();
  int idxInicio = bitacora.busquedaBinaria(registros, regInicio, compara);
  int idxFin = bitacora.busquedaBinaria(registros, regFin, compara);

  //Realiza una verificación para determinar si los índices de busqueda son válidos, muestra su información y cuenta el número de registros mostrados. Complejidad = O(n)
  if (idxInicio == -1 || idxFin == -1) {
    std::cout << "Una o ambas fechas no se encontraron en la bitácora.\n";
  } else {
    int count = 0;
    for (int i = idxInicio; i <= idxFin; i++) {
      std::cout << registros[i].getAll() << "\n";
      count++;
    }
    std::cout << "Resultado: " << count << " registros\n";
  }

  //Guarda la bitacora ordenada en un archivo
  bitacora.guardarArchivo("bitacora_ordenada.txt");

  return 0;
}
