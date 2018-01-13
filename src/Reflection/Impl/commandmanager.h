//---------------------------------------------------------------------------------------------
// Autor: Vasyl Dykyy
// class CommandManager implemented functional for registration and executing commands
//---------------------------------------------------------------------------------------------

#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H
#include <iostream>
#include <functional>
#include <cstring>

#include "functiondata.hpp"
#include "src/Common/common.h"
#include "internaltypes.h"
#include "../Interface/reflection.h"

using namespace std;

using namespace Internal;

/**
 * @brief The CommandManager class - implemented functional
 *  for registration and executing commands
 */
class CommandManager : public Reflection
{
public:
    friend class ReflectionFactory;

public:
    CommandManager();
    ~CommandManager();

    size_t getFunctionsListSize();
    char* getFunctionSignatureAt(const size_t index) const;
    void registerCommand(const char* cmdName, const size_t index);

    void unRegisterCommand(char* cmdName);

    void runCommand(const char* params);
    void executeScenario(const char* scenarioFileUrl);

private:
    size_t addFunctionToList(UniFunctionPtr functionPtr, InvokerPtr invoker, size_t argsCount, const char* signatureInfo);

private:
    CommandsMap* cmdMap;
    FunctionsList* functionsList;

};

#endif // COMMANDMANAGER_H
