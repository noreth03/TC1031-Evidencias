#ifndef _DLLNODE_H_
#define _DLLNODE_H_

template <class T>
class DLLNode {
public:
    T data;
    DLLNode<T> *next;
    DLLNode<T> *prev;

    DLLNode();
    DLLNode(T value);
};

//Inicializa un nodo de la lista doblemente enlazada sin ningún valor. Complejidad: O(1)
template <class T>
DLLNode<T>::DLLNode() : data{}, next(nullptr), prev(nullptr) {}

//Inicializa un nodo de la lista doblemente enlazada con un valor especificado. Complejidad: O(1)
template <class T>
DLLNode<T>::DLLNode(T value) : data(value), next(nullptr), prev(nullptr) {}

#endif // _DLLNODE_H_
