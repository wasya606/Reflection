#include "commandmanager.h"

CommandManager::CommandManager() : cmdMap(nullptr), functionsList(nullptr)
{
    cmdMap = new CommandsMap;
    functionsList = new FunctionsList();
}

CommandManager::~CommandManager()
{
    if (cmdMap != nullptr) delete cmdMap;
    if (functionsList != nullptr) delete functionsList;
}

size_t CommandManager::getFunctionsListSize()
{
    return functionsList->size();
}

char *CommandManager::getFunctionSignatureAt(const size_t index) const
{
    char* result = nullptr;

    if (index < functionsList->size())
    {
        FunctionInfo* functionInfo = functionsList->at(index);
        result = functionInfo->getSignatureInfo();
    }
    return result;
}

void CommandManager::registerCommand(const char *cmdName, const size_t index)
{
    if (index > 0 && index < functionsList->size())
    {
        if (cmdMap->insert(cmdName, index))
        {
            Logger::info() << "Command \"" << cmdName << "\" registered successfully.";
        }
        else
        {
            Logger::error() << "The command \"" << cmdName << "\" is already registered! IGNORED";
        }
    }
    else
    {
        Logger::error() << "Command registration failed! Wrong function index!!!";
    }
}

size_t CommandManager::addFunctionToList(UniFunctionPtr functionPtr, InvokerPtr invoker, size_t argsCount, const char *signatureInfo)
{
    size_t index = functionsList->size();
    FunctionInfo* functionInfo = new FunctionInfo(functionPtr, invoker, argsCount, signatureInfo);
    functionsList->push_back(functionInfo);
    return index;
}

void CommandManager::unRegisterCommand(char *cmdName)
{
    if (cmdMap->remove(cmdName))
    {
        Logger::info() << "Command \"" << cmdName << "\" unregistered successfully.";
    }
    else
    {
        Logger::error() << "Command \"" << cmdName << "\" has not been registered! IGNORED";
    }
}

void CommandManager::runCommand(const char *params)
{
    char* str = new char[strlen(params) + 1];
    strcpy(str, params);

    char* cmdName = strtok(str, " ");

    size_t cmdIndex = cmdName != nullptr ? (cmdMap->getDataPtr(cmdName) != nullptr ? *(cmdMap->getDataPtr(cmdName)) : -1) : -1;

    FunctionInfo* cmd = (cmdIndex > 0 && cmdIndex < functionsList->size()) ? functionsList->at(cmdIndex) : nullptr;

    if (cmd != nullptr)
    {
        CharPtrList* paramsList = new CharPtrList;

        for (char* parameterStr = strtok(nullptr, " "); parameterStr != nullptr; parameterStr = strtok(nullptr, " "))
        {
            paramsList->push_back(parameterStr);
        }

        Logger::info() << "Executing command: \"" << cmdName << "\"";

        if (false)//Settings::getSettingsFlag(SettingsID::SETTINGS_LOGGING, ValidationFlags::ARGS_COUNT) > 0 && cmd->getArgsCount() > paramsList->size())
        {
            Logger::error() << "Arguments count error! Expected: " << cmd->getArgsCount() << ", got: "
                            << paramsList->size() << "\nCommand execute is impossible! SKIPPED!";
        }
        else
        {
            cmd->invoke(paramsList);
        }

        cout << "<----------------------------------------------------------------------->\n\n\n";
    }
    else if (cmdName != nullptr)
    {
        Logger::error() << "Any command with name \"" << cmdName << "\" has not been registered! Executing will SKIPPED!";
    }
    else
    {
        Logger::error() << "Bad command string!!! Executing will SKIPPED!!";
    }
    delete[] str;
}

void CommandManager::executeScenario(const char *scenarioFileUrl)
{
    FILE* file = fopen(scenarioFileUrl, "r");

    if (file != nullptr)
    {
        Logger::debug() << "Loading settings from: " << scenarioFileUrl;
    }
    else
    {
        Logger::error() << "Cannot open scenario file: " << scenarioFileUrl;
        return;
    }

    char cmdBuffer[128];

    while(fgets(cmdBuffer, 128, file))
    {
          if (isalpha(cmdBuffer[0]))
          {
              runCommand(cmdBuffer);
          }
    }
}
