#ifndef _DLINKEDLIST_H_
#define _DLINKEDLIST_H_

#include <iostream>
#include <stdexcept>
#include "DLLNode.h"

template <class T>
class DLinkedList {
private:
    DLLNode<T> *head;
    DLLNode<T> *tail;
    int numElements;

    DLLNode<T>* merge(DLLNode<T>* first, DLLNode<T>* second);
    DLLNode<T>* mergeSort(DLLNode<T>* head);
    DLLNode<T>* split(DLLNode<T>* head);

public:
    DLinkedList();
    ~DLinkedList();

    void addFirst(T value);
    void addLast(T value);
    int getNumElements() const;
    void printList() const;
    bool deleteData(T value);
    bool deleteAt(int position);
    T getData(int position) const;
    void mergeSort();
    int busquedaBinaria(T key) const;
};

//Inicializa una lista doblemente enlazada vacía. Complejidad: O(1)
template <class T>
DLinkedList<T>::DLinkedList() : head(nullptr), tail(nullptr), numElements(0) {}

template <class T>
DLinkedList<T>::~DLinkedList() {
    DLLNode<T> *p = head;
    while (p != nullptr) {
        DLLNode<T> *nextNode = p->next;
        delete p;
        p = nextNode;
    }
    head = nullptr;
    tail = nullptr;
    numElements = 0;
}

//Agrega un nuevo elemento al principio de la lista. Complejidad: O(1)
template <class T>
void DLinkedList<T>::addFirst(T value) {
    DLLNode<T> *newNode = new DLLNode<T>(value);
    if (head == nullptr && tail == nullptr) {
        head = newNode;
        tail = newNode;
    }
    else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    numElements++;
}

//Agrega un nuevo elemento al final de la lista. Complejidad: O(1)
template <class T>
void DLinkedList<T>::addLast(T value) {
    if (head == nullptr && tail == nullptr)
        addFirst(value);
    else {
        DLLNode<T> *newNode = new DLLNode<T>(value);
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
        numElements++;
    }
}

//Devuelve el número de elementos en la lista. Complejidad: O(1)
template <class T>
int DLinkedList<T>::getNumElements() const {
    return numElements;
}

//Imprime los elementos de la lista. Complejidad: O(n)
template <class T>
void DLinkedList<T>::printList() const {
    if (head == nullptr && tail == nullptr)
        std::cout << "La lista está vacía" << std::endl;
    else {
        std::cout << "Contenido de la lista:" << std::endl;
        DLLNode<T> *p = head;
        while (p != nullptr) {
            std::cout << p->data << " ";
            p = p->next;
        }
        std::cout << std::endl;
    }
}

//Elimina el nodo que contiene el valor especificado de la lista. Complejidad: O(n)
template <class T>
bool DLinkedList<T>::deleteData(T value) {
    if (head == nullptr && tail == nullptr) {
        std::cout << "La lista está vacía" << std::endl;
        return false;
    }
    else {
        DLLNode<T> *p = head;
        while (p != nullptr && p->data != value) {
            p = p->next;
        }
        if (p == nullptr) {
            std::cout << "El valor no existe en la lista" << std::endl;
            return false;
        }
        if (p != nullptr && p == head) {
            head = p->next;
            if (head == nullptr)
                tail = nullptr;
        }
        else if (p->next == nullptr) {
            p->prev->next = nullptr;
            tail = p->prev;
        }
        else {
            p->prev->next = p->next;
            p->next->prev = p->prev;
        }
        delete p;
        p = nullptr;
        numElements--;
        return true;
    }
}

//Elimina el nodo en la posición especificada de la lista. Complejidad: O(n)
template <class T>
bool DLinkedList<T>::deleteAt(int position) {
    if (position < 0 || position >= numElements) {
        throw std::out_of_range("Índice fuera de rango");
    }
    else if (position == 0) {
        DLLNode<T> *p = head;
        if (p != nullptr && p->next == nullptr) {
            head = nullptr;
            tail = nullptr;
        }
        else {
            head = p->next;
            head->prev = nullptr;
        }
        delete p;
        p = nullptr;
        numElements--;
        return true;
    }
    else {
        DLLNode<T> *p = head;
        int index = 0;
        while (index != position) {
            p = p->next;
            index++;
        }
        if (p->next == nullptr) {
            p->prev->next = nullptr;
            tail = p->prev;
        }
        else {
            p->prev->next = p->next;
            p->next->prev = p->prev;
        }
        delete p;
        p = nullptr;
        numElements--;
        return true;
    }
}

//Devuelve el valor del elemento en la posición especificada de la lista. Complejidad: O(n)
template <class T>
T DLinkedList<T>::getData(int position) const {
    if (position < 0 || position >= numElements) {
        throw std::out_of_range("Índice fuera de rango");
    }
    else if (position == 0) {
        return head->data;
    }
    else {
        DLLNode<T> *p = head;
        int index = 0;
        while (p != nullptr) {
            if (index == position)
                return p->data;
            p = p->next;
            index++;
        }
        return {};
    }
}

//Ordena la lista utilizando el algoritmo de ordenamiento merge sort. Complejidad: O(n log n)
template <class T>
void DLinkedList<T>::mergeSort() {
    head = mergeSort(head);
    DLLNode<T> *p = head;
    while (p->next != nullptr) {
        p = p->next;
    }
    tail = p;
}

//Combina dos sublistas ordenadas en una sola lista ordenada. Complejidad: O(n)
template <class T>
DLLNode<T>* DLinkedList<T>::merge(DLLNode<T>* first, DLLNode<T>* second) {
    if (!first)
        return second;
    if (!second)
        return first;
    if (first->data <= second->data) {
        first->next = merge(first->next, second);
        first->next->prev = first;
        first->prev = nullptr;
        return first;
    }
    else {
        second->next = merge(first, second->next);
        second->next->prev = second;
        second->prev = nullptr;
        return second;
    }
}

//Ordena una sublista utilizando el algoritmo de ordenamiento merge sort de manera recursiva. Complejidad: O(n log n)
template <class T>
DLLNode<T>* DLinkedList<T>::mergeSort(DLLNode<T>* head) {
    if (!head || !head->next)
        return head;
    DLLNode<T>* second = split(head);
    head = mergeSort(head);
    second = mergeSort(second);
    return merge(head, second);
}

//Divide una sublista en dos sublistas aproximadamente de igual longitud. Complejidad: O(n)
template <class T>
DLLNode<T>* DLinkedList<T>::split(DLLNode<T>* head) {
    DLLNode<T>* fast = head;
    DLLNode<T>* slow = head;
    while (fast->next && fast->next->next) {
        fast = fast->next->next;
        slow = slow->next;
    }
    DLLNode<T>* temp = slow->next;
    slow->next = nullptr;
    return temp;
}

//Realiza una búsqueda binaria en la lista para encontrar la posición del elemento especificado. Complejidad: O(log n)
template <class T>
int DLinkedList<T>::busquedaBinaria(T key) const {
    int low = 0;
    int high = numElements - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (key == getData(mid))
            return mid;
        else if (key < getData(mid))
            high = mid - 1;
        else
            low = mid + 1;
    }
    return -1;
}

#endif // _DLINKEDLIST_H_
