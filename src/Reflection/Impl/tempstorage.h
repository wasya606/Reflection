#ifndef TEMPSTORAGE_H
#define TEMPSTORAGE_H
#include <list>
#include <cstddef>
#include "src/Logger/Interface/logger.h"

class TempStorage
{
public:
    template<typename T>
    static T* createPtr();

    template<typename T>
    static T* createPtr(const T&& initValue);

    template<typename T>
    static T* createArrPtr(const size_t length);

    static void clearAll();
    static void clearPtrs();
    static void clearArrPtrs();

public:
    TempStorage();
    ~TempStorage();

private:
    static TempStorage* getInstance();

    static TempStorage* instance;
    //TempStorage();

    bool clearPtr(void* ptr);
    bool clearArrPtr(void* ptr);
private:
    std::list<void*>* ptrsList;
    std::list<void*>* arrPtrsList;
};


template<typename T>
T* TempStorage::createPtr()
{
    Logger::debug("TempStorage:  ") << "Create ptr of " << typeid(T).name();
    T* objPtr = new T;
    getInstance()->ptrsList->push_back(static_cast<void*>(objPtr));
    return objPtr;
}

template<typename T>
T* TempStorage::createPtr(const T&& initValue)
{
    Logger::debug("TempStorage:  ") << "Create ptr of " << typeid(T).name() << " init with: " << initValue;
    T* objPtr = new T;
    *objPtr = initValue;
    getInstance()->ptrsList->push_back(static_cast<void*>(objPtr));
    return objPtr;
}

template<typename T>
T* TempStorage::createArrPtr(const size_t length)
{
    Logger::debug("TempStorage:  ") << "Create array of " << typeid(T).name() << " length: " << length;
    T* objPtr = new T[length];
    getInstance()->arrPtrsList->push_back(static_cast<void*>(objPtr));
    return objPtr;
}

#endif // TEMPSTORAGE_H
