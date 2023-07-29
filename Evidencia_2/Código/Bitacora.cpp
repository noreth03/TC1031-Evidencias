#include "Bitacora.h"
#include <iostream>
#include <stdexcept>

//Constructor por defecto. 
Bitacora::Bitacora() {}

//Constructor que lee un archivo de registros y los almacenar en una lista de registros. Complejidad = O(n) 
void Bitacora::leerArchivo(const std::string& filePath) {
    std::string month, day, hours, minutes, seconds, ipAdd, port, error;
    std::ifstream file(filePath);
    if (!file.good()) {
        file.close();
        throw std::invalid_argument("File not found");
    }
    else {
        while (!file.eof()) {
            std::getline(file, month, ' ');
            std::getline(file, day, ' ');
            std::getline(file, hours, ':');
            std::getline(file, minutes, ':');
            std::getline(file, seconds, ' ');
            std::getline(file, ipAdd, ':');
            std::getline(file, port, ' ');
            std::getline(file, error);

            Registro tmpRecord(month, day, hours, minutes, seconds, ipAdd, port, error);
            listaRegistros.addLast(tmpRecord);
        }
        file.close();
    }
}

// Imprime los registros almacenados en la lista de registros. Complejidad: O(n)
void Bitacora::print() const {
    for (int i = 0; i < listaRegistros.getNumElements(); i++) {
        std::cout << listaRegistros.getData(i).getAll() << std::endl;
    }
}

//Devuelve la lista de registros almacenados de la bitácora. Complejidad: O(1)
const DLinkedList<Registro>& Bitacora::getListaRegistros() const {
    return listaRegistros;
}

//Ordena la lista de registros utilizando el algoritmo de ordenamiento merge sort. Complejidad: O(n log n)
void Bitacora::ordenarBitacora() {
    listaRegistros.mergeSort();
}

// Permite al usuario buscar registros de la bitácora por un rango de fechas y guardar los resultados en un archivo. Complejidad O(log n)
void Bitacora::buscarRegistrosPorFecha() {
    std::string start, end;
    std::cout << "Ingrese la fecha de inicio de búsqueda (formato: MMM dd hh:mm:ss): ";
    std::getline(std::cin, start);

    std::cout << "Ingrese la fecha de fin de búsqueda (formato: MMM dd hh:mm:ss): ";
    std::getline(std::cin, end);

    try {
        // Crear objetos Registro con las fechas de inicio y fin ingresadas
        Registro startRecord(start.substr(0, 3), start.substr(4, 2), start.substr(7, 2), start.substr(10, 2), start.substr(13, 2), "", "", "");
        Registro endRecord(end.substr(0, 3), end.substr(4, 2), end.substr(7, 2), end.substr(10, 2), end.substr(13, 2), "", "", "");

        int startIndex = listaRegistros.busquedaBinaria(startRecord);
        int endIndex = listaRegistros.busquedaBinaria(endRecord);

        if (startIndex == -1 || endIndex == -1 || startIndex > endIndex) {
            std::cout << "Una o ambas fechas de búsqueda no se encontraron en la bitácora." << std::endl;
        } else {
            std::ofstream outFile("resultado_busqueda.txt");
            outFile << "Fecha 1: " << startRecord.getAll().substr(0, startRecord.getAll().length() - 2) << std::endl;
outFile << "Fecha 2: " << endRecord.getAll().substr(0, endRecord.getAll().length() - 2) << std::endl;

            outFile << std::endl;
            outFile << "Resultado: " << (endIndex - startIndex + 1) << " Registros" << std::endl;

            for (int i = startIndex; i <= endIndex; i++) {
                outFile << listaRegistros.getData(i).getAll() << std::endl;
            }
            outFile.close();
            std::cout << "La búsqueda se ha completado. Los resultados se han guardado en 'resultado_busqueda.txt'." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "Error: Formato de fecha incorrecto. Asegúrese de ingresar las fechas en el formato especificado." << std::endl;
    }
}

//Guarda los registros de la bitácora en un archivo. Complejidad: O(n)
void Bitacora::guardarArchivo(const std::string& filePath) {
    std::ofstream file(filePath);
    for (int i = 0; i < listaRegistros.getNumElements(); i++) {
        file << listaRegistros.getData(i).getAll() << "\n";
    }
    file.close();
}
