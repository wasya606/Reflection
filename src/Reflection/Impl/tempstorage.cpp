#include "tempstorage.h"

TempStorage* TempStorage::instance = nullptr;

void TempStorage::clearAll()
{
    clearPtrs();
    clearArrPtrs();
}

void TempStorage::clearPtrs()
{
    Logger::debug("TempStorage:  ") << "----- Clearing ptrs start... " << getInstance()->ptrsList->size();
    for (auto iter = getInstance()->ptrsList->begin(); iter != getInstance()->ptrsList->end(); iter++)
    {
        getInstance()->clearPtr(*iter);
    }
    Logger::debug("TempStorage:  ") << "===== Cleared: " << getInstance()->ptrsList->size() << " ptrs.";
    getInstance()->ptrsList->clear();
}

void TempStorage::clearArrPtrs()
{
    Logger::debug("TempStorage:  ") << "----- Clearing arrays start...";
    for (auto iter = getInstance()->arrPtrsList->begin(); iter != getInstance()->arrPtrsList->end(); iter++)
    {
        getInstance()->clearArrPtr(*iter);
    }
    Logger::debug("TempStorage:  ") << "===== Cleared: " << getInstance()->arrPtrsList->size() << " ptrs.";
    getInstance()->arrPtrsList->clear();
}

TempStorage::TempStorage() : ptrsList(new std::list<void*>), arrPtrsList(new std::list<void*>)
{

}

TempStorage::~TempStorage()
{
    clearAll();
    clearPtr(ptrsList);
    clearArrPtr(arrPtrsList);
}

TempStorage *TempStorage::getInstance()
{
    if (instance == nullptr)
        instance = new TempStorage();
    return instance;
}

bool TempStorage::clearPtr(void *ptr)
{
    if (ptr != nullptr)
    {
        try
        {
            delete ptr;
            ptr = nullptr;
            return true;
        }
        catch(std::bad_alloc e)
        {
            Logger::error() << "Clear array ptr failed!!! " << e.what();
            ptr = nullptr;
            return false;
        }
    }
}

bool TempStorage::clearArrPtr(void *ptr)
{
    if (ptr != nullptr)
    {
        try
        {
            delete[] ptr;
            ptr = nullptr;
            return true;
        }
        catch(std::bad_alloc e)
        {
            Logger::error() << "Clear array ptr failed!!! " << e.what();
            ptr = nullptr;
            return false;
        }
    }
}
