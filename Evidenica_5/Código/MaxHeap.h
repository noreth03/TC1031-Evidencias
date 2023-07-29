#ifndef _MAXHEAP_H_
#define _MAXHEAP_H_

#include <iostream>
#include <stdexcept>
#include <vector>

template <class T> class MaxHeap {
private:
  // contiene los elementos del maxheap
  std::vector<ipAddress> data;
  // capacidad maxima del maxheap
  int maxCapacity;
  // tamaño actual del maxheap
  int currentSize;

  int parent(int k);
  int left(int k);
  int right(int k);

public:
  MaxHeap();
  MaxHeap(int _maxCapacity);
  ~MaxHeap();
  bool isEmpty();
  int getMaxCapacity();
  int getCurrentSize();
  void print();
  void push(T key);
  T getTop();
  void pop();
};

// O(n)
template <class T> MaxHeap<T>::MaxHeap() {
  data.clear();
  maxCapacity = 0;
  currentSize = 0;
}

// O(n)
template <class T> MaxHeap<T>::MaxHeap(int _maxCapacity) {
  maxCapacity = _maxCapacity;
  data.resize(maxCapacity);
  currentSize = 0;
}

// O(n)
template <class T> MaxHeap<T>::~MaxHeap() {
  maxCapacity = 0;
  currentSize = 0;
  data.clear();
}

// O(1)
template <class T> bool MaxHeap<T>::isEmpty() { return (currentSize <= 0); }

// O(1)
template <class T> int MaxHeap<T>::getMaxCapacity() { return maxCapacity; }

// O(1)
template <class T> int MaxHeap<T>::getCurrentSize() { return currentSize; }

// O(n)
template <class T> void MaxHeap<T>::print() {
  std::cout << "Contenido del maxheap:" << std::endl;
  for (int i = 0; i < currentSize; i++) {
    std::cout << data[i] << " ";
  }
  std::cout << std::endl;
}

// O(1)
template <class T> int MaxHeap<T>::parent(int k) { return (k - 1) / 2; }

// O(1)
template <class T> int MaxHeap<T>::left(int k) { return (2 * k + 1); }

// O(1)
template <class T> int MaxHeap<T>::right(int k) { return (2 * k + 2); }

// O(log n)
template <class T> void MaxHeap<T>::push(T key) {
  if (currentSize == maxCapacity) {
    throw std::out_of_range("Overflow: no se puede insertar la llave");
  }
  int k = currentSize;
  data[k] = key;
  currentSize++;

  while (k != 0 && data[parent(k)] < data[k]) {
    std::swap(data[k], data[parent(k)]);
    k = parent(k);
  }
}

// O(1)
template <class T> T MaxHeap<T>::getTop() {
  if (isEmpty()) {
    throw std::out_of_range("El heap esta vacio");
    return {};
  }
  return data[0];
}

template <class T> void MaxHeap<T>::pop()
{
    if (isEmpty()) {
    throw std::out_of_range("El heap esta vacio");
    }
    if (currentSize == 1)
    {
        currentSize--;
    }
 
    data[0] = data[currentSize-1];
    currentSize--;
    MaxHeapify(0);
}