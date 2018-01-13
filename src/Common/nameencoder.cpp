#include "nameencoder.h"

NameId NameEncoder::encode(const char *name)
{
    NameId result = 0;
    size_t nameLen = strlen(name);

    for (size_t i = 0; i < nameLen; i++)
    {
        NameId encodedSymbol = encodeSymbol(name[i]);
        result |= encodedSymbol << (6 * (nameLen - i - 1));
    }

    return result;
}

void NameEncoder::decode(NameId nameId, char *nameBuffer)
{
    size_t nameLen = calculateLen(nameId);

    NameId tmp = nameId;

    for (size_t i = 0; i < nameLen; i++)
    {
        size_t shift = 6 * (nameLen - i - 1);
        NameId codedSymbol = tmp >> shift;
        char decodedSymbol = decodeSymbol(codedSymbol);
        nameBuffer[i] = decodedSymbol;
        tmp ^= (codedSymbol << shift);
    }
    nameBuffer[nameLen] = '\0';
}

char NameEncoder::encodeSymbol(const char symbol)
{
    char result = 0;

    if(symbol >= '0' && symbol <= '9')
    {
        result = symbol - '0' + 1;
    }
    else if(symbol >= 'A' && symbol <= 'Z')
    {
        result = symbol - 'A' + 11;
    }
    else if (symbol >= 'a' && symbol <= 'z')
    {
        result = symbol - 'a' + 36;
    }
    else if (symbol == '-')
    {
        result = 62;
    }
    else if (symbol == '_')
    {
        result = 63;
    }

    return result;
}

char NameEncoder::decodeSymbol(const char symbol)
{
    char result = 0;

    if (symbol < 11)
    {
        result = symbol + '0' - 1;
    }
    else if(symbol < 36)
    {
        result = symbol + 'A' - 11;
    }
    else if (symbol < 62)
    {
        result = symbol + 'a' - 36;
    }
    else if (symbol == 62)
    {
        result = '-';
    }
    else if (symbol == 63)
    {
        result = '_';
    }

    return result;
}

int NameEncoder::compareAsString(const NameId value1, const NameId value2)
{
    size_t len1 = calculateLen(value1);
    size_t len2 = calculateLen(value2);

    NameId tmp1 = value1;
    NameId tmp2 = value2;

    for (size_t i = 0; i < len1 && i < len2; i++)
    {
        size_t shift1 = 6 * (len1 - i - 1);
        size_t shift2 = 6 * (len2 - i - 1);

        NameId codedSymbol1 = tmp1 >> shift1;
        NameId codedSymbol2 = tmp2 >> shift2;

        char sym1 = decodeSymbol(codedSymbol1);
        char sym2 = decodeSymbol(codedSymbol2);

        if (sym1 != sym2)
        {
            return (sym1 - sym2) * 64;
        }

        tmp1 ^= (codedSymbol1 << shift1);
        tmp1 ^= (codedSymbol2 << shift2);
    }

    return 0;
}

size_t NameEncoder::calculateLen(const NameId &nameId)
{
    size_t result = 0;

    NameId tmp = nameId;

    while (tmp > 0)
    {
        tmp = tmp >> 6;
        result ++;
    }

    return result;

}

