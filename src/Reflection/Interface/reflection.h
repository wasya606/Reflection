#ifndef REFLECTION_H
#define REFLECTION_H

#include "src/Common/common.h"

using namespace Common;

namespace Internal
{
    template<typename T>
    struct FunctionData
    {
        static const size_t argsCount;
        static void invoker(UniFunctionPtr functionPtr, CharPtrList* params);
    };
}

using namespace Internal;

enum ReflectionSettings
{
    VALIDATION_SET,
    LOGS_SET
};

class Reflection
{
public:
    //Reflection() {}
    virtual ~Reflection() {}

    template<typename FunctionType>
    size_t addFunctionToList(FunctionType* funct, const char* signatureInfo = nullptr);

    virtual size_t getFunctionsListSize() = 0;
    virtual char* getFunctionSignatureAt(const size_t index) const = 0;

    /**
     * @brief registerCommand
     * Allows registering command with any function
     * @param cmdName - name of command
     * @param funct - pointer to function
     */
    template<typename FunctionType>
    void registerCommand(const char* cmdName, FunctionType* funct, const char* signatureInfo = nullptr);

    /**
     * @brief registerCommand
     * Allows registering command with function from list which already
     * has been added earlier through addFunctionToList()
     * @param cmdName - name of command
     * @param index - function index in list
     */
    virtual void registerCommand(const char* cmdName, const size_t index) = 0;

    virtual void unRegisterCommand(char* cmdName) = 0;
    virtual void runCommand(const char* params) = 0;
    virtual void executeScenario(const char* scenarioFileUrl) = 0;


protected:
    virtual size_t addFunctionToList(UniFunctionPtr functionPtr, InvokerPtr invoker, size_t argsCount, const char* signatureInfo) = 0;
};

template<typename FunctionType>
void Reflection::registerCommand(const char* cmdName, FunctionType* funct, const char *signatureInfo)
{
    size_t index = addFunctionToList(funct, signatureInfo);
    registerCommand(cmdName, index);
}

template<typename FunctionType>
size_t Reflection::addFunctionToList(FunctionType* funct, const char *signatureInfo)
{
    UniFunctionPtr functionPtr = reinterpret_cast<UniFunctionPtr>(funct);
    InvokerPtr invoker = static_cast<InvokerPtr>(&FunctionData<FunctionType*>::invoker);
    size_t argsCount = FunctionData<FunctionType*>::argsCount;
    return addFunctionToList(functionPtr, invoker, argsCount, signatureInfo);
}

#endif // REFLECTION_H
