#include "Bitacora.h"

//Constructor
Bitacora::Bitacora() {}

//Aqui se realiza todo el procesamiento del grafo
Bitacora::Bitacora(std::string fileName) {
  graph.readGraph(fileName, 1, 1);
  //graph.print();
  graph.gradosIps("grados_ips.txt");
  graph.ipMayores("mayores_grados_ips.txt");
  graph.distBotMaster();
}

//Destructor
Bitacora::~Bitacora() {}

