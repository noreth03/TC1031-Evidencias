#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include <iostream>
#include <stdexcept>
#include "NodeLinkedList.h"

template <class T> 
class LinkedList {
  private:
    NodeLinkedList<T> *head;
    NodeLinkedList<T> *tail;
    int numElements;
  
  public:
    LinkedList();
    ~LinkedList();
    void addFirst(T value);
    void addLast(T value);
    int getNumElements();
    void printList();
    bool deleteData(T value);
    bool deleteAt(int position);
    T getData(int position);
    NodeLinkedList<T> *getHead();
};

// Complejidad O(1)
template <class T> 
LinkedList<T>::LinkedList() {
  head = nullptr;
  tail = nullptr;
  numElements = 0;
}

// Complejidad O(n)
template <class T> 
LinkedList<T>::~LinkedList() {
  NodeLinkedList<T> *p, *q;
  p = head;
  while (p != nullptr) {
    q = p->next;
    delete p;
    p = q;
  }
  head = nullptr;
  tail = nullptr;
  numElements = 0;  
}

// Complejidad O(1)
template <class T> 
void LinkedList<T>::addFirst(T value) {
  // 1. crear un nodo nuevo
  NodeLinkedList<T> *newNode = new NodeLinkedList<T>(value);
  // 2. apuntar newNode->next al nodo apuntado por head
  newNode->next = head;
  // 3. actualizar head para que apunte a newNode
  head = newNode;
  if (numElements == 0)
    tail = newNode;
  numElements++;
}

// Complejidad O(1)
template <class T>
void LinkedList<T>::addLast(T value) {
  // La lista esta vacia
  if (head == nullptr && tail == nullptr)
    addFirst(value);
  else {
    // 1. crear un newNode
    NodeLinkedList<T> *newNode = new NodeLinkedList<T>(value);
    // 2. apuntar tail->next a newNode
    tail->next = newNode;
    // 3. actualizar tail para apuntar al newNode
    tail = newNode;
    numElements++;
  }
}

// Complejidad O(1)
template <class T>
int LinkedList<T>::getNumElements() {
  return numElements;  
}

// Complejidad O(n)
template <class T>
void LinkedList<T>::printList() {
  if (head == nullptr && tail == nullptr)
    std::cout << "La lista esta vacia" << std::endl;
  else {
    std::cout << "El contenido de la lista es: " << std::endl;
    NodeLinkedList<T> *p = head;
    while(p != nullptr) {
      std::cout << p->data << " ";
      p = p->next;
    }
    std::cout << std::endl;
  }    
}
  
// Complejidad O(n)
template <class T>
bool LinkedList<T>::deleteData(T value) {
  // La lista esta vacia
  if (head == nullptr && tail == nullptr) {
    std::cout << "La lista esta vacia" << std::endl;
    return false;
  }
  else {
    NodeLinkedList<T> *p = head;
    NodeLinkedList<T> *prev = nullptr;
    while(p != nullptr && p->data != value) {
      prev = p;
      p = p->next;
    }
    // si no existe value en la lista
    if (p == nullptr) {
      std::cout << "El valor no existe en la lista" << std::endl;
      return false;
    }
    // si debo borrar el primer elemento en la lista
    if (p != nullptr && p == head) {
      head = p->next;
      if (head == nullptr) // habia un solo nodo en la lista
        tail = nullptr;
    } else if (p->next == nullptr) { // debo borrar el ultimo nodo
      prev->next = nullptr;
      tail = prev;
    } else {
      prev->next = p->next;
    }
    delete p;
    p = nullptr;
    numElements--;
    return true;
  }
}

// Complejidad O(n)
template <class T>
bool LinkedList<T>::deleteAt(int position) {
  if (position < 0 || position >= numElements) {
    throw std::out_of_range("Indice fuera de rango");
  } else if (position == 0) {
    NodeLinkedList<T> *p = head;
    // si la lista contiene un solo nodo
    if (p != nullptr && p->next == nullptr) {
      head = nullptr;
      tail = nullptr;
    } else {
      head = p->next;
    }
    delete p;
    p = nullptr;
    numElements--;
    return true;
  }
  else { // borrar cualquier otra posicion
    NodeLinkedList<T> *p = head;
    NodeLinkedList<T> *prev = nullptr;
    int index = 0;
    // buscar el indice del elemento a borrar
    while (index != position) {
      prev = p;
      p = p->next;
      index++;
    }
    // debo borrar el ultimo nodo
    if (p->next == nullptr) {
      prev->next = nullptr;
      tail = prev;
    } else { // borrar cualquier otro nodo
      prev->next = p->next;
    }
    delete p;
    p = nullptr;
    numElements--;
    return true;
  }
}

// Complejidad O(n)
template <class T>
T LinkedList<T>::getData(int position) {
  if (position < 0 || position >= numElements) {
    throw std::out_of_range("Indice fuera de rango");
  } else if (position == 0) { // si es el primero de la lista
    return head->data;
  } else { // si es cualquier otra posicion
    NodeLinkedList<T> *p = head;
    int index = 0;
    // buscar el indice del elemento
    while (p != nullptr) {
      if (index == position)
        return p->data;
      p = p->next;
      index++;
    }
    return {};
  }    
}

template <class T> 
NodeLinkedList<T> * LinkedList<T>::getHead() { 
  return head; 
}

#endif // _LINKEDLIST_H_

