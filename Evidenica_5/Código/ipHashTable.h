#ifndef _IP_HASH_TABLE_H_
#define _IP_HASH_TABLE_H_

#include <iostream>


class ipHashTable{
  private:
    std::string ipString, degreeIn, degreeOut;

  public:
    ipHashTable();
    ipHashTable(std::string, int, int);
    std::string printIpHash();

};

#endif //_IP_HASH_TABLE_H_

