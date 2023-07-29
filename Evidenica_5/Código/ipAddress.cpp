#include "ipAddress.h"

ipAddress::ipAddress(){
  ipString = "0.0.0.0";
  ipIndex = 0;
  degreeIn = 0;
  degreeOut = 0;
  ipValue = 0;
}

ipAddress::ipAddress(std::string _ip, int idx){
  ipString=_ip;
  ipIndex = idx;
  degreeIn = 0;
  degreeOut = 0;
  // Convertir IP
  int posInit = 0;
  int posFound = 0;
  std::string splitted;
  std::vector<std::string> results;   
  while(posFound >= 0) {
    posFound = ipString.find(".", posInit);
    splitted = ipString.substr(posInit, posFound - posInit);
    posInit = posFound + 1;
    results.push_back(splitted);
  }
  int partA = std::stoi(results[0]);
  int partB = std::stoi(results[1]);
  int partC = std::stoi(results[2]);
  int partD = std::stoi(results[3]);
  ipValue = partA*(pow(256,3)) + partB*(pow(256,2)) + partC*(pow(256,1)) + partD;
  

}

std::string ipAddress::getIp(){
  return ipString;
}

unsigned int ipAddress::getIpValue(){
  return ipValue;
}

int ipAddress::getIpIndex(){
  return ipIndex;
}

bool ipAddress::operator==(const ipAddress &other) const {
  return this->ipValue == other.ipValue;
}

bool ipAddress::operator!=(const ipAddress &other) const {
  return this->ipValue != other.ipValue;
}

bool ipAddress::operator>(const ipAddress &other) const {
  return this->ipValue > other.ipValue;
}

bool ipAddress::operator>=(const ipAddress &other) const {
  return this->ipValue >= other.ipValue;
}

bool ipAddress::operator<(const ipAddress &other) const {
  return this->ipValue < other.ipValue;
}

bool ipAddress::operator<=(const ipAddress &other) const {
  return this->ipValue <= other.ipValue;
}

//Complejidad O(1)
void ipAddress::setDegreeIn(int g){
  degreeIn = g;
}

//Complejidad O(1)
void ipAddress::addToDegreeIn(){
  degreeIn++;
}

//Complejidad O(1)
int ipAddress::getDegreeIn(){
  return degreeIn;
}

//Complejidad O(1)
void ipAddress::setDegreeOut(int g){
  degreeOut = g;
}

//Complejidad O(1)
void ipAddress::addToDegreeOut(){
  degreeOut++;
}

//Complejidad O(1)
int ipAddress::getDegreeOut(){
  return degreeOut;
}

std::string toString() {
    int value = 0;
    return std::to_string(value);
};
