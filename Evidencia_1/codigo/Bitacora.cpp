#include "Bitacora.h"


Bitacora::Bitacora(){ // Constructor por defecto. Complejidad = O(1)
   listaRegistros.clear(); // limpia la lista de registros
}

Bitacora::~Bitacora(){ // Destructor. Complejidad = O(1)

   listaRegistros.clear();
}
// Función para leer el archivo de la bitácora. Complejidad = O(n).
void Bitacora::leerArchivo(std::string filePath) {
  std::string month, day, hours, minutes, seconds, ipAdd, port, error;
  std::ifstream file(filePath);
  if (!file.good()) {
    file.close();
    throw std::invalid_argument("File not found");
  }
  else {
    while (!file.eof()) {
      // Extrae los campos de cada línea del archivo
        std::getline(file, month, ' ');
        std::getline(file, day, ' ');
        std::getline(file, hours, ':');
        std::getline(file, minutes, ':');
        std::getline(file, seconds, ' ');
        std::getline(file, ipAdd, ':');
        std::getline(file, port, ' ');
        std::getline(file, error);
        // crear un objeto de la clase Registro
        Registro tmpRecord(month, day, hours, minutes, seconds, ipAdd, port, error);
        listaRegistros.push_back(tmpRecord);       
    }
    file.close();
  }
}

//Metodo que devuelve una copia del vector listaRegistros. Complejidad = O(1)
std::vector<Registro> Bitacora::getListaRegistros() const {
  return listaRegistros;
}

// Función para imprimir la bitácora completa. Complejidad = O(n)
void Bitacora::print() {
  for (int i = 0; i < (int)listaRegistros.size(); i++) {
    std::cout << listaRegistros[i].getAll() << std::endl;
  }
   std::cout << std::endl;
}

// Implementación del algoritmo de ordenamiento Complejidad = O(n^2)
void Bitacora::swapSort(unsigned int &compara, unsigned int &swap) {
  compara = swap = 0;
  int n = listaRegistros.size();
  for (int i = 0; i < n - 1; i++) {
    int minIndex = i;
    for (int j = i + 1; j < n; j++) {
      compara++;
      if (listaRegistros[j] < listaRegistros[minIndex]) {
        minIndex = j;
      }
    }
    std::swap(listaRegistros[minIndex], listaRegistros[i]);
    swap++;
  }
}
// Implementación de la función de merge del algoritmo de ordenamiento Complejidad = O(nlogn)
void Bitacora::merge(int low, int m, int high, unsigned int &compara) {
  int i, j, k;
  int n1 = m - low + 1;
  int n2 = high - m;
  std::vector<Registro> L(n1);
  std::vector<Registro> R(n2);
  for (i = 0; i < n1; i++) L[i] = listaRegistros[low + i];
  for (j = 0; j < n2; j++) R[j] = listaRegistros[m + 1 + j];
  i = j = 0;
  k = low;
  while (i < n1 && j < n2) {
    compara++;
    if (L[i] <= R[j]) {
      listaRegistros[k] = L[i];
      i++;
    } else {
      listaRegistros[k] = R[j];
      j++;
    }
    k++;
  }
  while (i < n1) {
    listaRegistros[k] = L[i];
    i++;
    k++;
  }
  while (j < n2) {
    listaRegistros[k] = R[j];
    j++;
    k++;
  }
}
// Implementación del algoritmo de ordenamiento merge. Complejidad = O(nlogn)
void Bitacora::mergeSort(int low, int high, unsigned int &compara) {
  if (low < high) {
    int m = low + (high - low) / 2;
    mergeSort(low, m, compara);
    mergeSort(m + 1, high, compara);
    merge(low, m, high, compara);
  }
}
// Implementación de la búsqueda binaria. Complejidad = O(log2n)
int Bitacora::busquedaBinaria(std::vector<Registro> &A, Registro key, unsigned int &compara) {
  int low = 0;
  int high = (int)A.size() - 1;
  int mid = 0;
  compara = 0;
  while (low <= high) {
    mid = low + (high - low) / 2;
    compara++;
    if (key == A[mid]) {
      return mid;
    } else if (key < A[mid]) {
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }
  return -1;
}
// Función para guardar la bitácora en un archivo. Complejidad = O(n)
void Bitacora::guardarArchivo(std::string filePath) {
  std::ofstream file(filePath);
    // Recorre la lista de registros y escribe cada uno en el archivo
  for (const auto &registro : listaRegistros) {
    file << registro.getAll() << "\n";
  }
  file.close(); // Cierra el archivo
}
