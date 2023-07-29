#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

#include <vector>
#include <iostream>
#include <stdexcept>
#include "HashNode.h"
#include "ipHashTable.h"

template <class K, class T>
class HashTable {
private:
    std::vector<HashNode<K, T>> table;
    int numElements;
    int maxSize;

public:
    HashTable();
    ~HashTable();
    void setMaxSize(int selectedMaxSize);
    // Función hash
    int getHashIndex(K keyValue);
    int getNumElements();
    void print();
    void add(K keyValue, T dataValue);  // Complejidad promedio: O(1), Complejidad peor caso: O(n)
    int find(K keyValue);  // Complejidad promedio: O(1), Complejidad peor caso: O(n)
    T getDataAt(int index);
    void remove(K keyValue);  // Complejidad promedio: O(1), Complejidad peor caso: O(n)
    void collisions();  // Complejidad: O(m), donde "m" es el tamaño actual de la tabla con elementos no nulos.
};

template<class K, class T>
HashTable<K,T>::HashTable() {
  maxSize = 0;
  numElements = 0;
  table = std::vector<HashNode<K, T>>(maxSize);
}

template<class K, class T>
HashTable<K,T>::~HashTable() {
  maxSize = 0;
  numElements = 0;
  table = std::vector<HashNode<K, T>>(maxSize);
}

template<class K, class T>
void HashTable<K,T>::setMaxSize(int selectedMaxSize) {
  maxSize = selectedMaxSize;
  numElements = 0;
  table = std::vector<HashNode<K, T>>(maxSize);
}



template<class K, class T>
int HashTable<K,T>::getHashIndex(K keyValue) {
  // metodo de residuales (key mod maxSize)
  return keyValue % maxSize;
}

template<class K, class T>
int HashTable<K,T>::getNumElements() {
  return numElements;
}

template<class K, class T>
void HashTable<K,T>::print() {
  std::cout << "Contenido de la tabla hash" << std::endl;
  for (int i = 0; i < maxSize; i++) {
    // 0 empty,  1 used,  2 deleted
    if (table[i].getStatus() == 1) {
      std::cout << "Celda: " << i << " Key: " << table[i].getKey() << ", Value: " << table[i].getData() << ", Overflow.size: " << table[i].getOverflowSize() << std::endl;
    }
  }
}

template<class K, class T>
void HashTable<K,T>::add(K keyValue, T dataValue) {
  if (numElements == maxSize) {
    throw std::out_of_range("La hash table esta llena");
  }
  if (find(keyValue) != -1) {
    throw std::out_of_range("El elemento ya existe en la tabla hash");
  }
  // Calcular el index en la tabla hash
  int hashIndex = getHashIndex(keyValue);
  HashNode<K, T> node = table[hashIndex];
  // 0 empty,  1 used,  2 deleted
  if (node.getStatus() != 1) { // la celda esta libre
    node.setKey(keyValue);
    node.setData(dataValue);
    table[hashIndex] = node;
  }
  else { // la celda NO esta libre
    int i = 1;
    int currentHashIndex = getHashIndex(hashIndex + i * i);
    HashNode<K, T> currentNode = table[currentHashIndex];
    while (currentNode.getStatus() == 1) { // la celda esta ocupada
      i++;
      currentHashIndex = getHashIndex(hashIndex + i * i);
      currentNode = table[currentHashIndex];
    }
    // Se ha encontrado una celda libre
    currentNode.setKey(keyValue);
    currentNode.setData(dataValue);
    node.addToOverflow(currentHashIndex);
    table[currentHashIndex] = currentNode;
    table[hashIndex] = node;
  }
  numElements++;
}

template<class K, class T>
int HashTable<K,T>::find(K keyValue) {
  // Calcular el index en la tabla hash
  int hashIndex = getHashIndex(keyValue);
  HashNode<K, T> node = table[hashIndex];
  // 0 empty,  1 used,  2 deleted
  if (node.getStatus() == 1) {
    if (node.getKey() == keyValue)
      return hashIndex;
    for (int i = 0; i < (int)node.getOverflowSize(); i++) {
      int overflowIndex = node.getOverflowAt(i);
      if (table[overflowIndex].getKey() == keyValue)
        return overflowIndex;
    }
    return -1;
  }
  return -1;
}

template<class K, class T>
T HashTable<K,T>::getDataAt(int index) {
  return table[index].getData();
}

template<class K, class T>
void HashTable<K,T>::remove(K keyValue) {
  int pos, hashIndex;
  pos = find(keyValue);
  if (pos == -1) {
    throw std::out_of_range("El elemento no existe en la tabla hash");
  }
  hashIndex = getHashIndex(keyValue);
  if (pos != hashIndex) {
    HashNode<K, T> node = table[hashIndex];
    node.removeFromOverflow(pos);
    table[hashIndex] = node;
  }
  table[pos].clearData();
  numElements--;
}

template<class K, class T>
void HashTable<K,T>::collisions(){
  int total = 0; 
  for(int i = 0; i < maxSize; i++){
   if(table[i].getStatus() == 1){
     if (table[i].getOverflowSize() > 0){
       total++;
     }
   } 
  }
  std::cout<< "Colisiones totales: " << total << std::endl;
}

#endif  // _HASH_TABLE_H_