#ifndef FUNCTIONINFO_H
#define FUNCTIONINFO_H
#include "src/Common/common.h"
using namespace Common;

class FunctionInfo
{
public:
    FunctionInfo(UniFunctionPtr functionPtr, InvokerPtr invoker, size_t argsCount, const char* signatureInfo = nullptr);
    ~FunctionInfo();

    bool invoke(CharPtrList* parameters);
    char* getSignatureInfo() const;
    size_t getArgsCount() const;

private:
    UniFunctionPtr functionPtr;
    InvokerPtr invoker;
    size_t argsCount;
    char* signatureInfo;
};

#endif // FUNCTIONINFO_H
