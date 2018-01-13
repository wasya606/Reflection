#ifndef NAMEENCODER_H
#define NAMEENCODER_H


#include <iostream>
#include <cstring>
using namespace std;

using NameId = long long unsigned int;

class NameEncoder
{
public:
    static NameId encode(const char* name);
    static void decode(NameId nameId, char* nameBuffer);

    NameEncoder() = delete;
private:
    static char encodeSymbol(const char symbol);
    static char decodeSymbol(const char symbol);
    static int compareAsString(const NameId value1, const NameId value2);
    static size_t calculateLen(const NameId& nameId);
};

#endif // NAMEENCODER_H
