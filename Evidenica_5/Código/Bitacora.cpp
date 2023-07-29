#include "Bitacora.h"

//Constructor
Bitacora::Bitacora() {}

//Aqui se realiza todo el procesamiento del grafo
Bitacora::Bitacora(std::string fileName) {
  graph.readGraph(fileName, 1, 1);
  //graph.print();
  graph.crearHash();
  graph.getIPSummary();
}

//Destructor
Bitacora::~Bitacora() {}

