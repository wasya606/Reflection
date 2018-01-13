#ifndef TYPETOOLS_H
#define TYPETOOLS_H

#include "src/Common/common.h"
#include "src/Reflection/Impl/tempstorage.h"

using namespace Common;

template<typename... Args>
/**
 * @brief clean - Performs release of dynamic memory, that has been allocated for storing the extracted parameters
 * @param args... - Extracted parameters pack
 */
static void clean(Args... args);

static void cleanAll();

template<typename Type>
/**
 * @brief getTypeFullName - presents name of Type as string char*
 * @tparam Type - type
 * @param result - char* buffer for store result
 */
static void getTypeFullName(char *result);

/**
 * @brief Struct for storing the interim parsing result
 */
struct ConvertResult
{
    union
    {
        unsigned long long int uintValue;
        long long int intValue;
        long double floatValue;
    } value;

    bool isNegative = false;
};

/**
 * @brief tryConvertToInteger - performs attempt to convert a char* string to an integer type
 * @param str - input char* string
 * @param result - store result of converting as ConvertResult struct
 * @return - true if attempt to convert is successfull and false if no
 */
static bool tryConvertToInteger(const char* str, ConvertResult& result);

/**
 * @brief tryConvertToFloat - performs attempt to convert a char* string to an floating type
 * @param str - input char* string
 * @param result - store result of converting as ConvertResult struct
 * @return - true if attempt to convert is successfull and false if no
 */
static bool tryConvertToFloat(const char* str, ConvertResult& result);

//-------------------------- Declarations of Parser  ----------------------------
template<typename Type, bool isPointer = std::is_pointer<Type>::value,
                        bool isInteger = std::is_integral<Type>::value || std::is_enum<Type>::value,
                        bool isFloating = std::is_floating_point<Type>::value>
struct Parser;

template<typename Type, bool isSigned = std::is_signed<Type>::value>
struct IntParser;

template<typename Type>
struct PointerParser;

//-------------------------- Declaration of Extractor  --------------------------
template<typename Type, bool isPointer = std::is_pointer<Type>::value,
                        bool isReference = std::is_reference<Type>::value,
                        bool isReferenceToPointer = std::is_pointer<typename std::remove_reference<Type>::type>::value>
struct Extractor;

#include "typetools.cpp"

#endif // TYPETOOLS_H
