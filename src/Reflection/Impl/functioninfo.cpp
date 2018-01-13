#include "functioninfo.h"
#include "../../Logger/Interface/logger.h"

FunctionInfo::FunctionInfo(UniFunctionPtr functionPtr, InvokerPtr invoker, size_t argsCount, const char *signatureInfo) :
    functionPtr(functionPtr),
    invoker(invoker),
    argsCount(argsCount),
    signatureInfo(nullptr)
{
    if (signatureInfo != nullptr)
    {
        size_t infoLength = strlen(signatureInfo);
        if (infoLength > 0)
        {
            this->signatureInfo = new char[strlen(signatureInfo) + 1];
            strcpy(this->signatureInfo, signatureInfo);
        }
    }
}

FunctionInfo::~FunctionInfo()
{
    if (signatureInfo != nullptr)
        delete[] signatureInfo;
}

bool FunctionInfo::invoke(CharPtrList *parameters)
{
    if (invoker != nullptr && functionPtr != nullptr)
    {
        invoker(functionPtr, parameters);
        return true;
    }
    else
    {
        Logger::error() << "Cannot to invoke!!! Fatal error!!!";
        return false;
    }
}

char *FunctionInfo::getSignatureInfo() const
{
    return signatureInfo;
}

size_t FunctionInfo::getArgsCount() const
{
    return argsCount;
}
