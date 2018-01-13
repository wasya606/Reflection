#ifndef TYPETOOLS_IMPL_CPP
#define TYPETOOLS_IMPL_CPP

#include "typetools.h"
#include "../../Logger/Interface/logger.h"

template<typename T>
static void clean(T arg)
{
    Extractor<T>::clean(arg);
}

void cleanAll()
{
    TempStorage::clearAll();
}

template<typename T, typename... Args>
static void clean(T arg, Args... args)
{
    Extractor<T>::clean(arg);
    clean(args...);
}

template<typename Type>
static void getTypeFullName(char *result)
{
    char buffer[50] = {0};
    strcat(buffer, std::is_const<Type>::value ? "const " : "");
    strcat(buffer, std::is_volatile<Type>::value ? "volatile " : "");
    strcat(buffer, typeid(Type) != typeid(bool) && std::is_unsigned<Type>::value ? "unsigned " : "");

    using TypeCleaner = typename TypeCleaner<Type>::PureType;

    if (typeid(TypeCleaner) == typeid(bool))
    {
        strcat(buffer, "bool");
    }
    else if (typeid(TypeCleaner) == typeid(char) ||
             typeid(TypeCleaner) == typeid(unsigned char))
    {
        strcat(buffer, "char");
    }
    else if (typeid(TypeCleaner) == typeid(short int) ||
             typeid(TypeCleaner) == typeid(unsigned short int))
    {
        strcat(buffer, "short int");
    }
    else if (typeid(TypeCleaner) == typeid(int) ||
             typeid(TypeCleaner) == typeid(unsigned int))
    {
        strcat(buffer, "int");
    }
    else if (typeid(TypeCleaner) == typeid(long int) ||
             typeid(TypeCleaner) == typeid(unsigned long int))
    {
        strcat(buffer, "long int");
    }
    else if (typeid(TypeCleaner) == typeid(long long int) ||
             typeid(TypeCleaner) == typeid(unsigned long long int))
    {
        strcat(buffer, "long long int");
    }
    else if (typeid(TypeCleaner) == typeid(float))
    {
        strcat(buffer, "float");
    }
    else if (typeid(TypeCleaner) == typeid(double))
    {
        strcat(buffer, "double");
    }
    else if (typeid(TypeCleaner) == typeid(long double))
    {
        strcat(buffer, "long double");
    }
    else if (std::is_void<TypeCleaner>::value)
    {
        strcat(buffer, "void");
    }
    else
    {
        strcat(buffer, "Object ");
        strcat(buffer, typeid(Type).name());
    }

    strcat(buffer, std::is_pointer<Type>::value ? "*" : "");
    strcat(buffer, std::is_lvalue_reference<Type>::value ? "&" : "");
    strcat(buffer, std::is_rvalue_reference<Type>::value ? "&&" : "");


    strcpy(result, buffer);
}

bool tryConvertToInteger(const char* str, ConvertResult &result)
{
    unsigned short int numericSystem = 0;
    bool success = true;

    size_t len = strlen(str);

    if (len > 2 && str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
    {
        numericSystem = 16;
        for (size_t i = 2; i < len; i ++)
        {
            if (!isxdigit(str[i]) && !isdigit(str[i]))
            {
                success = false;
                break;
            }
        }
    }
    else if ((len > 0 && isdigit(str[0])) || (len > 1 && (str[0] == '-' || str[0] == '+')))
    {
        numericSystem = 10;
        result.isNegative = str[0] == '-';
        for (size_t i = 1; i < len; i ++)
        {
            if (!isdigit(str[i]))
            {
                success = false;
                break;
            }
        }
    }
    else if (len == 3 && str[0] == '\'' && str[2] == '\'')
    {
        result.value.uintValue = str[1];
    }
    else if (strcmp(str, "true") == 0 || strcmp(str, "True") == 0 || strcmp(str, "TRUE") == 0)
    {
        result.value.uintValue = 1;
    }
    else if (strcmp(str, "false") == 0 || strcmp(str, "False") == 0 || strcmp(str, "FALSE") == 0)
    {
        result.value.uintValue = 0;
    }
    else
    {
        success = false;
    }

    if (success && numericSystem != 0)
    {
        if (result.isNegative)
        {
            result.value.intValue = strtoll(str, nullptr, numericSystem);
        }
        else
        {
            result.value.uintValue = strtoull(str, nullptr, numericSystem);
        }
    }

    return success;
}

bool tryConvertToFloat(const char* str, ConvertResult &result)
{
    bool success = true;
    size_t len = strlen(str);
    bool haveDot = false;

    if ((len > 0 && isdigit(str[0])) || (len > 1 && (str[0] == '-' || str[0] == '+')))
    {
        for (size_t i = 1; i < len; i ++)
        {
            if (!isdigit(str[i]))
            {
                if (str[i] == '.' && !haveDot)
                {
                    haveDot = true;
                }
                else
                {
                    success = false;
                    break;
                }
            }
        }
    }
    else
    {
        success = false;
    }

    if (success)
    {
        result.value.floatValue = strtold(str, nullptr);
    }
    return success;
}

//-------------------------- Implementations of Parser  --------------------------
template<typename Type>
struct Parser<Type, true, false, false>
{
    using PureType = typename TypeCleaner<Type>::PurePtrType;
    static const PureType* parse(const char* strValue)
    {
        return PointerParser<Type>::parse(strValue);
    }
};

template<typename Type>
struct Parser<Type, false, true, false>
{
    static const Type* parse(const char* strValue)
    {
        return IntParser<Type>::parse(strValue);
    }
};

template<typename Type>
struct Parser<Type, false, false, true>
{
    static const Type* parse(const char* strValue)
    {
        Type* result = TempStorage::createPtr<Type>(0.0);
        ConvertResult cResult;

        if (tryConvertToFloat(strValue, cResult))
        {
            *result = cResult.value.floatValue;
        }
        else if (tryConvertToInteger(strValue, cResult))
        {
            *result = cResult.value.intValue;
        }

        Logger::debug() << "Parser: is Float value. Type size: " << sizeof(Type) << ", result: " << *result;
        return result;
    }
};

template<typename Type>
struct Parser<Type, false, false, false>
{
    static const Type* parse(const char* strValue)
    {
        return TempStorage::createPtr<Type>();
    }
};

//-----------------------------------------

template<typename Type>
struct IntParser<Type, true>
{
    static const Type* parse(const char* str)
    {
        Type* result = TempStorage::createPtr<Type>(0);
        ConvertResult cResult;

        if (tryConvertToInteger(str, cResult))
        {
            *result = cResult.value.intValue;
        }

        Logger::debug() << "IntParser: signed. Type size: " << sizeof(Type) << ", result: " << *result;
        return result;
    }
};

template<typename Type>
struct IntParser<Type, false>
{
    static const Type* parse(const char* str)
    {
        ConvertResult cResult;

        Type* result = nullptr;

        if (tryConvertToInteger(str, cResult))
        {
            result = TempStorage::createPtr((Type)cResult.value.uintValue);
        }

        Logger::debug() << "IntParser: unsigned. Type size: " << sizeof(Type) << ", result: " << *result;
        return result;
    }
};

template<typename Type>
struct PointerParser
{
    static const Type parse(const char*)
    {
        Logger::debug() << "PointerParser:";
        return 0;
    }
};

template<>
struct PointerParser<void*>
{
    static const void* parse(const char* str)
    {
        void* result = reinterpret_cast<void*>(0);
        ConvertResult cResult;

        if (tryConvertToInteger(str, cResult))
        {
            result = reinterpret_cast<void*>(cResult.value.uintValue);
        }

        Logger::debug() << "PointerParser: void* Type size: " << sizeof(void*) << ", result: " << result;
        return result;
    }
};

template<>
struct PointerParser<char*>
{
    static const char* parse(const char* str)
    {
        char* result = TempStorage::createArrPtr<char>(strlen(str) + 1);
        strcpy(result, str);
        Logger::debug() << "PointerParser: char* Type size: " << sizeof(char*) << ", result: " << result;
        return result;
    }
};


//-------------------------- Implementations of Extractor  --------------------------
//POINTER
template<typename Type>
struct Extractor<Type, true, false, true>
{
    using PureType = typename TypeCleaner<Type>::PureCvPtrCvType;
    static const PureType* getValue(const char* strValue)
    {
        return Parser<PureType*>::parse(strValue);
    }

    static void clean(Type value)
    {
        Logger::debug() << "Is ARRAY: " << std::is_array<Type>::value;
        Extractor<decltype(*value)>::clean(*value);
        Logger::debug() << "DELETE pointer type: " << typeid(Type).name() << ", address: " << value << ", value:" << *value;
        delete value;
    }
};

template<>
struct Extractor<const void*, true, false, true>
{
    static const void* getValue(const char* strValue)
    {
        return Parser<void*>::parse(strValue);
    }
    static void clean(const void*) {Logger::debug() << "SKIP DELETING void*";}
};

template<>
struct Extractor<char*, true, false, true>
{
    static const char* getValue(const char* strValue)
    {
        return Parser<char*>::parse(strValue);
    }
    static void clean(const void*) {Logger::debug() << "SKIP DELETING char*";}
};

//REFERENCE
template<typename Type>
struct Extractor<Type, false, true, false>
{
    using PureType = typename TypeCleaner<Type>::PureCvRefCvType;
    static const PureType* getValue(const char* strValue)
    {
        return Parser<PureType>::parse(strValue);
    }

    static void clean(Type)
    {
        Logger::debug() << "SKIP DELETING reference, value: " << typeid(Type).name();
    }
};

//REFERENCE TO POINTER
template<typename Type>
struct Extractor<Type, false, true, true>
{
    using PureType = typename TypeCleaner<Type>::PureType;
    static const PureType** getValue(const char* strValue)
    {
        return TempStorage::createPtr<const PureType*>(Parser<PureType*>::parse(strValue));
    }

    static void clean(Type value)
    {
        Logger::debug() << "DELETE reference to pointer type: " << typeid(Type).name() << ", address: " << value << ", value:" << *value;
        Extractor<typename TypeCleaner<Type>::PureCvRefCvType>::clean(value);
    }
};

//PURE TYPE
template<typename Type>
struct Extractor<Type, false, false, false>
{
    using PureType = typename TypeCleaner<Type>::PureCvRefCvType;
    static const PureType getValue(const char* strValue)
    {
        const PureType* resultPtr = Parser<PureType>::parse(strValue);
        const PureType result = *resultPtr;

        return result;
    }

    static void clean(Type)
    {
        Logger::debug() << "SKIP DELETING Pure type, value: " << typeid(Type).name();
    }
};

#endif // TYPETOOLS_IMPL_CPP
