#include "common.h"

#ifndef COMMON_CPP
#define COMMON_CPP

//********************   Key Comparing  ********************
namespace Common {

template<typename Type>
bool Comparer<Type>::compare(const Type &key1, const Type &key2)
{
    return key1 == key2;
}

template<>
struct Comparer<const char*>
{
    static bool compare(const char* key1, const char* key2)
    {
        return strcmp(key1, key2) == 0;
    }
};

//****************    ContainerData    ********************

template<typename KeyType, typename DataType>
ContainerData<KeyType, DataType>::ContainerData(const KeyType& key, const DataType& data) : prevPtr(nullptr), nextPtr(nullptr)
{
    dataPtr = new DataType;
    *dataPtr = data;

    keyPtr = new KeyType;
    *keyPtr = key;
}

template<typename KeyType, typename DataType>
ContainerData<KeyType, DataType>::~ContainerData()
{
    if (dataPtr != nullptr) delete dataPtr;
    if (keyPtr != nullptr) delete keyPtr;
}

template<typename KeyType, typename DataType>
bool ContainerData<KeyType, DataType>::keyComparing(const KeyType &key)
{
    return Comparer<KeyType>::compare(key, *keyPtr);
}


//***********************   Container   ************************
template<typename KeyType, typename DataType>
Container<KeyType, DataType>::Container() : size(0), firstElement(nullptr), lastElement(nullptr) {}

template<typename KeyType, typename DataType>
Container<KeyType, DataType>::~Container()
{
    clean();
}

template<typename KeyType, typename DataType>
bool Container<KeyType, DataType>::push(const KeyType &key, const DataType &data)
{
    bool result = false;
    if (getElement(key) == nullptr)
    {
        if (size == 0)
        {
            firstElement = new ElementType(key, data);
            lastElement = firstElement;
        }
        else
        {
            lastElement->nextPtr = new ElementType(key, data);
            lastElement = lastElement->nextPtr;
        }
        this->size++;
        result = true;
    }
    return result;
}

template<typename KeyType, typename DataType>
DataType *Container<KeyType, DataType>::get(const KeyType &key)
{
    return getElement(key) != nullptr ? getElement(key)->dataPtr : nullptr;
}

template<typename KeyType, typename DataType>
bool Container<KeyType, DataType>::del(const KeyType &key)
{
    return remove(getElement(key));
}

template<typename KeyType, typename DataType>
void Container<KeyType, DataType>::clean()
{
    ElementType* it = firstElement;
    while (it != nullptr)
    {
        ElementType* tmp = it;
        it = it->nextPtr;
        delete tmp;
    }
    firstElement = nullptr;
    lastElement = nullptr;
    size = 0;
}

template<typename KeyType, typename DataType>
size_t Container<KeyType, DataType>::getSize()
{
    return size;
}

template<typename KeyType, typename DataType>
typename Container<KeyType, DataType>::ElementType* Container<KeyType, DataType>::getElement(const KeyType &key)
{
    ElementType* it = nullptr;
    for(it = firstElement; it != nullptr && !it->keyComparing(key); it = it->nextPtr);
    return it;
}

template<typename KeyType, typename DataType>
bool Container<KeyType, DataType>::remove(const ElementType *deletingElement)
{
    bool result = deletingElement != nullptr;

    if (result)
    {
        deletingElement->prevPtr != nullptr ? deletingElement->prevPtr->nextPtr = deletingElement->nextPtr :
                                              firstElement = deletingElement->nextPtr;
        deletingElement->nextPtr != nullptr ? deletingElement->nextPtr->prevPtr = deletingElement->prevPtr :
                                              lastElement  = deletingElement->prevPtr;

        delete deletingElement;
        this->size--;
    }
    return result;

}

//***********************   List    ***************************
template<typename DataType>
void List<DataType>::push(const DataType &data)
{
    Base::push(this->size, data);
}

template<typename DataType>
DataType& List<DataType>::operator[](const size_t& index)
{
    size_t validIndex = index < Base::size ? index : Base::size - 1;
    return *Base::get(validIndex);
}

}
#endif // COMMON_CPP
