/*
 * Autores: 
 *  - Héctor Calderón Reyes: A01350637
 *  - Noreth Sofia Villalpando Saldaña: A01368579
 *
 * Fecha de creación: 7 de Julio de 2023
 *
 * Actividad: Act 1.3 - Actividad Integral de Conceptos Básicos y Algoritmos Fundamentales (Evidencia Competencia)
 *
 * Descripción: Este programa lee una bitácora de eventos de seguridad, la transforma en una Doubly Linked List, la ordena y permite buscar eventos en un rango de fechas.
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
    Bitacora bitacora;
    std::string filePath = "bitacora.txt";

    try {
        bitacora.leerArchivo(filePath);

        bitacora.ordenarBitacora();
        std::cout << "La bitácora ha sido ordenada." << std::endl;

        bitacora.buscarRegistrosPorFecha();

        std::string nuevoArchivo = "bitacora_ordenada.txt";
        bitacora.guardarArchivo(nuevoArchivo);
        std::cout << "La bitácora ordenada se ha guardado en el archivo '" << nuevoArchivo << "'" << std::endl;
    }
    catch (std::exception const& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
