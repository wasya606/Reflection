#ifndef REFLECTIONFACTORY_H
#define REFLECTIONFACTORY_H

#include "src/Reflection/Impl/commandmanager.h"

struct ReflectionFactory
{
    static Reflection* getReflection()
    {
        return new CommandManager();
    }
};

#endif // REFLECTIONFACTORY_H
