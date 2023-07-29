#ifndef _MAXHEAP_H_
#define _MAXHEAP_H_

#include <iostream>
#include <stdexcept>
#include <vector>

template <class T> class MaxHeap {
private:
  std::vector<T> data;
  int currentSize;
  int parent(int k);
  int left(int k);
  int right(int k);
  void MaxHeapify(int i);

public:
  MaxHeap();
  bool isEmpty();
  int getCurrentSize();
  void print();
  void push(const T &key);
  T getTop();
  void pop();
  void swap(T *x, T *y);
};

// O(n)
template <class T>
MaxHeap<T>::MaxHeap() {
  data = std::vector<T>();
  currentSize = 0;
}

// O(1)
template <class T> bool MaxHeap<T>::isEmpty() { return (currentSize <= 0); }

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
template <class T>
void MaxHeap<T>::push(const T &key) {
  data.push_back(key);
  currentSize++;
  int k = currentSize - 1;
  while (k != 0 && data[parent(k)] < data[k]) {
    std::swap(data[k], data[parent(k)]);
    k = parent(k);
  }
}

// O(1)
template <class T> T MaxHeap<T>::getTop() {
  if (isEmpty()) 
     throw std::out_of_range("El heap está vacío");   
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

template <class T> void MaxHeap<T>::MaxHeapify(int i){
    int l = left(i);
    int r = right(i);
    int biggest = i;
    if (l < currentSize && data[l] > data[biggest])
        biggest = l;
    if (r < currentSize && data[r] > data[biggest])
        biggest = r;
    if (biggest != i)
    {
        swap(&data[i], &data[biggest]);
        MaxHeapify(biggest);
    }

}


template <class T>
void MaxHeap<T>::swap(T *x, T *y) {
    T temp = *x;
    *x = *y;
    *y = temp;
}

#endif // _MAXHEAP_H_