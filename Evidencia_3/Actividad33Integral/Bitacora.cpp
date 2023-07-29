#include "Bitacora.h"
#include "MaxHeap.h"
#include "IpAddress.h"

Bitacora::Bitacora() {}// Constructor por defecto de la clase Bitacora : o(n)

// Función para leer los registros desde un archivo y almacenarlos en el vector listaRegistros. O(n)
void Bitacora::leerArchivo(std::string filePath) {
    std::string month, day, hours, minutes, seconds, ipAdd, port, error;
    std::ifstream file(filePath);
    if (!file.good()) {
        file.close();
        throw std::invalid_argument("File not found");
    } else {
        while (!file.eof()) {
            std::getline(file, month, ' ');
            std::getline(file, day, ' ');
            std::getline(file, hours, ':');
            std::getline(file, minutes, ':');
            std::getline(file, seconds, ' ');
            std::getline(file, ipAdd, ':');
            std::getline(file, port, ' ');
            std::getline(file, error);

            // Crear un objeto de la clase Registro
            Registro tmpRec(month, day, hours, minutes, seconds, ipAdd, port, error);
            listaRegistros.push_back(tmpRec);
        }
        file.close();
    }
}

// Obtener el vector listaRegistros. O(1)
std::vector<Registro> Bitacora::getListaRegistros() const {
    return listaRegistros;
}

// Función para reorganizar el Heap: O(log n)
void Bitacora::heapify(int n, int k) {
    int largest = k;
    int left = 2 * k + 1;
    int right = 2 * k + 2;

    // Si el hijo izquierdo es más grande que la raíz
    if (left < n && listaRegistros[left] > listaRegistros[largest])
        largest = left;

    // Si el hijo derecho es más grande que la raíz
    if (right < n && listaRegistros[right] > listaRegistros[largest])
        largest = right;

    // Si el más grande no es la raíz
    if (largest != k) {
        std::swap(listaRegistros[k], listaRegistros[largest]);
        heapify(n, largest);
    }
}

// Función para aplicar el Heap Sort: O(log n)
void Bitacora::heapSort(int n) {
    // 1. Construir el Heap a partir de la lista
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(n, i);
    }

    // 2. Extraer elemento por elemento del Heap
    for (int i = n - 1; i > 0; i--) {
        // Intercambiar raíz con la última hoja
        std::swap(listaRegistros[0], listaRegistros[i]);
        heapify(i, 0);
    }
}

// Función para ordenar la bitácora utilizando Heap Sort: O(log n)
void Bitacora::ordenarBitacora() {
    heapSort(listaRegistros.size());
}

// Función para guardar los registros ordenados en un nuevo archivo:  O(n)
void Bitacora::guardarArchivo(const std::string& filePath) {
    std::ofstream file(filePath);
    for (const auto& registro : listaRegistros) {
        file << registro.getAll() << "\n";
    }
    file.close();
}

// Función para ordenar y contar la frecuencia de las direcciones IP presentes en la bitácora
void Bitacora::ordenarTopIps() {
    IpAddress ip("", 0, 0);
    ip.countFreq(listaRegistros);
}