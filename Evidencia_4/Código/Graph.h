#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <utility> 
#include <map>
#include <queue>
#include <bits/stdc++.h>
#include <algorithm>
#include "LinkedList.h"
#include "ipAddress.h"

// https://stackoverflow.com/questions/18429021/why-is-infinity-0x3f3f3f3f
#define INF 0x3f3f3f3f

template <class T>
class Graph {
  private: 
    // Número de nodos
    int numNodes;
    // Número de aristas
    int numEdges;
    // Dirección del grafo: 1 dirigido; 0 no-dirigido
    int directedGraph; 
    // Peso del grafo: 1 ponderado; 0 no-ponderado
    int weightedGraph;
    // Cada nodo tiene un id y un objeto de datos tipo T
    std::string botMaster;
    int indexBot;
    std::map<int, T> nodesInfo;

    // Vector de objetos ipAddress para contar los grados (in y out)
    std::vector<ipAddress> ips;
    // Cola de prioridad para el grado de cada IP
    std::priority_queue<std::pair<int, std::string>, std::vector<std::pair<int, std::string>>, std::less<std::pair<int, std::string>>> myMaxHeap;
    std::priority_queue<std::pair<int, std::string>, std::vector<std::pair<int, std::string>>, std::less<std::pair<int, std::string>>> ipDistance;

    // Lista de adyacencia (vector de listas de pares <nodo,peso>)
    std::vector<LinkedList<std::pair<int, int>>> adjList;

    // Método para dividir la línea en múltiples valores enteros
    void split(std::string line, std::vector<int> &res);  // Complejidad: O(n)

    // Método para realizar la búsqueda binaria
    int binarySearch(ipAddress key);  // Complejidad: O(log n)

  public:
    // Constructor del grafo
    Graph();  
    // Destructor del grafo
    ~Graph();  
    // Método para leer el grafo desde un archivo de entrada
    void readGraph(std::string inputFile, int _directed, int _weighted);  // Complejidad: O(n^2 log n)
    // Método para imprimir la información del grafo
    void print(int flagInfo = 0);  // Complejidad: O(n^2)
    // Método para implementar el algoritmo de Dijkstra
    void dijkstraAlgorithm(int v);  // Complejidad: O((n+m) log n)
    // Método para calcular los grados de las IPs
    void gradosIps(std::string fileName);  // Complejidad: O(n)
    // Método para obtener las IPs con mayor grado
    void ipMayores(std::string fileName);  // Complejidad: O(n log n)
    // Método para calcular la distancia al botMaster
    void distBotMaster();  // Complejidad: O((n+m) log n)
};

template <class T>
Graph<T>::Graph() {
  numNodes = 0;
  numEdges = 0;
  directedGraph = 1;
  weightedGraph = 1;
}

template <class T>
Graph<T>::~Graph() {
  adjList.clear();
  numNodes = 0;
  numEdges = 0;
  directedGraph = 1;
  weightedGraph = 1;
}

template <class T>
void Graph<T>::split(std::string line, std::vector<int> &res) {
    size_t strPos = line.find(" ");
    size_t lastPos = 0;
    while (strPos != std::string::npos) {
      res.push_back(stoi(line.substr(lastPos, strPos - lastPos)));
      lastPos = strPos + 1;
      strPos = line.find(" ", lastPos);
    }
    res.push_back(stoi(line.substr(lastPos, line.size() - lastPos)));
}


//Complejidad: O(log n)
template <class T>
int Graph<T>::binarySearch(ipAddress key) {
  int low = 0;
  int high = ips.size() - 1;
  int mid = 0;
  while (low <= high) {
    mid = low + (high - low) / 2;
    if (key == ips[mid])
      return mid;
    else if (key < ips[mid])
      high = mid - 1;
    else
      low = mid + 1;
  }
  return -1;
}

template <class T>
void Graph<T>::readGraph(std::string inputFile, int _directed, int _weighted) {
  directedGraph = _directed;
  weightedGraph = _weighted;
  std::string line, ip1, ip2, peso;
  int i = 0;
  
  std::ifstream file(inputFile);
  if (!file.good()) {
    file.close();
    throw std::invalid_argument("File not found");
  } else {
    while (std::getline(file, line)) {
      if (i == 0) { // Leemos numNodes y numEdges
        std::vector<int> res;
        split(line, res);
        numNodes = res[0];
        numEdges = res[1];
        // Reservar memoria para los renglones de la 
        // lista de adyacencia (cero basada)
        adjList.resize(numNodes);
        i++;
        continue;
      } else if (i > 0 && i <= numNodes) {
        T data = line; // ATENCION: convertir al tipo de dato adecuado
        // map <key, data> con los nodos indexados cero basados 
        nodesInfo.insert(std::make_pair(i - 1, data));  
        // Vector de objetos ipAddress para hacer búsqueda binaria de ips
        ipAddress tmpIP(line, i - 1);
        ips.push_back(tmpIP);
        if (i == numNodes) { // al leer la ultima ip se ordena el vector
          std::sort(ips.begin(), ips.end());
        }
        i++;
        continue;
      }
      // Tomamos de la linea solo las 2 ips y su peso
      std::size_t found = line.find(":", 15);
      ip1 = line.substr(15, found - 15);
      std::size_t found2 = line.find(" ", found + 1);
      std::size_t found3 = line.find(":", found2 + 1);
      ip2 = line.substr(found2, found3 - found2);
      std::size_t found4 = line.find(" ", found3 + 1);
      std::size_t found5 = line.find(" ", found4 + 1);
      peso = line.substr(found4, found5 - found4);
      // Buscamos a que numero de nodo corresponde cada ip
      int pos1 = binarySearch(ipAddress(ip1, 0));
      int nodoU = ips[pos1].getIpIndex();
      int pos2 = binarySearch(ipAddress(ip2, 0));
      int nodoV = ips[pos2].getIpIndex();
      int weight = std::stoi(peso);
      // el grafo es dirigido y ponderado
      adjList[nodoU].addLast(std::make_pair(nodoV, weight));
      ips[pos1].addToDegreeOut(); // sumas una arista saliente a la ip de origen
      ips[pos2].addToDegreeIn();  // sumas una arista entrante a la ip de destino
      i++;
    }
    file.close();
  }
}


template <class T>
void Graph<T>::print(int flagInfo) {
  std::cout << "numNodes: " << numNodes << std::endl;
  std::cout << "numEdges: " << numEdges << std::endl;
  std::cout << "Adjacency List" << std::endl;
  for (int nodeU = 0; nodeU < numNodes; nodeU++) {
    if (flagInfo) // Se imprime la info del nodo
      std::cout << "vertex " << nodesInfo[nodeU] << ": ";
    else // Se imprime el numero de nodo
	   std::cout << "vertex " << nodeU+1 << ": ";
    NodeLinkedList<std::pair<int, int>> *ptr = adjList[nodeU].getHead(); 
    while (ptr != nullptr) {
      std::pair<int, int> par = ptr->data;
      int nodeV = par.first;
      int weight = par.second;
      std::string nodeData = (flagInfo) ? nodesInfo[nodeV] + ", " : "";
      if (weightedGraph == 1) // grafo ponderado
          std::cout << "{" << nodeData << nodeV+1 << ", " << weight << "} ";
      else
        std::cout << "{" << nodeData << nodeV+1 << "} ";
      ptr = ptr->next;
    }
    std::cout << std::endl;
  }
}

template <class T>
void Graph<T>::dijkstraAlgorithm(int v) {
    std::ofstream outputFile("distancia_botmaster.txt");
    // nodos cero basados
    // v = v - 1;
    // vector de distancias con el resultado del algoritmo
    std::vector<int> dist(numNodes, INF);
    // vector con los nodos previos en el camino mas corto
    std::vector<int> prev(numNodes, -1);
    // Crear una priority queue del STL
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    // Insertar el nodo de origen v en la priority queue -- pares <dist, nodo>
    pq.push(std::make_pair(0, v)); // la distancia de v a v es cero
    dist[v] = 0;

    // Mientras la priority queue no este vacia
    while (!pq.empty()) {
        // Extrae un nodo de la priority queue
        int nodeU = pq.top().second; // pares <dist, nodo>
        pq.pop();
        // Obtener los vecinos de nodeU
        // Lista de de adyacencia
        NodeLinkedList<std::pair<int, int>> *ptr = adjList[nodeU].getHead();
        while (ptr != nullptr) {
            std::pair<int, int> par = ptr->data;
            int nodeV = par.first;
            int weight = par.second;
            if (dist[nodeV] > dist[nodeU] + weight) {
                // Actualizar la distancia mas corta de nodeV
                dist[nodeV] = dist[nodeU] + weight;
                prev[nodeV] = nodeU;
                pq.push(std::make_pair(dist[nodeV], nodeV));
            }
            ptr = ptr->next;
        }
    }

    // Resultados
    outputFile << "IPs \t\t Distancia desde " << botMaster << std::endl;
    for (int i = 0; i < numNodes; i++) {
        if (dist[i] != INF) {
            std::string ip = ips[i].getIp();
            int distancia = dist[i];
            ipDistance.push(std::make_pair(distancia, ip));
            outputFile << ip << "\t\t" << "\t\t" << dist[i] << std::endl;
        } else {
            std::string ip = ips[i].getIp(); 
            outputFile << ip << "\t\tINF" << std::endl;
        }
    }

    if (!ipDistance.empty()) {
        std::cout << "El ip que más trabajo le costaría al bot master es: " << ipDistance.top().second << std::endl;
    } else {
        std::cout << "No se encontraron IPs alcanzables desde el bot master." << std::endl;
    }
    
    outputFile.close();
}



template <class T>
void Graph<T>::distBotMaster(){
  indexBot = binarySearch(ipAddress(botMaster, 0));
  dijkstraAlgorithm(indexBot);
}

template <class T>
void Graph<T>::gradosIps(std::string fileName) {
  std::ofstream file(fileName);
  if (!file.good()) {
    file.close();
    throw std::invalid_argument("File not found");
  }
  else
    for(int i= 0; i<numNodes; i++){
      std::string ip = ips[i].getIp();
      int grado = ips[i].getDegreeOut();
      file << ip << "   out degrees: " << grado << std::endl;
    }
  file.close();
}

template <class T>
void Graph<T>::ipMayores(std::string fileName) {

  for (int i = 0; i < numNodes; i++) {
    std::string ip = ips[i].getIp();
    int grado = ips[i].getDegreeOut();
    myMaxHeap.push(std::make_pair(grado, ip));

  }
  std::ofstream file(fileName);
  if (!file.good()) {
    file.close();
    throw std::invalid_argument("File not found");
  }  
  else {
    botMaster = myMaxHeap.top().second;
    std::cout<< "El bot master esta en la ip: " << myMaxHeap.top().second << std::endl;
   // std::pair <int, std::string> bootMaster;
    
    for (int i=0; i<5; i++){
      int grado = myMaxHeap.top().first;
      std::string ip = myMaxHeap.top().second;
      file << "ip: " << ip << "   Grado: " << grado << std::endl;
      myMaxHeap.pop();
    }
  }
  file.close();
}



#endif  // _GRAPH_H_
