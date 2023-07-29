#include "ipHashTable.h"

ipHashTable::ipHashTable(){
  
}

ipHashTable::ipHashTable(std::string _ipString, int out, int in){
  ipString = _ipString;
  degreeIn = std::to_string(in);
  degreeOut = std::to_string(out);
}


std::string ipHashTable::printIpHash(){ 
  return "Ip: " + ipString + "   Aristas de salida: " + degreeOut + "  Aristas de entrada: " + degreeIn;
}