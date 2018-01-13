#ifndef INTERNALTYPES_CPP
#define INTERNALTYPES_CPP

#include "internaltypes.h"
namespace Internal {


template <typename KeyType, typename DataType, typename KeyCompareType>
Map<KeyType, DataType, KeyCompareType>::Map() : map(nullptr)
{
    map = new std::map<KeyType, DataType, KeyCompareType>;
}

template <typename KeyType, typename DataType, typename KeyCompareType>
Map<KeyType, DataType, KeyCompareType>::~Map()
{
    if (map != nullptr)
    {
        delete map;
    }
}

template <typename KeyType, typename DataType, typename KeyCompareType>
bool Map<KeyType, DataType, KeyCompareType>::insert(const KeyType &key, const DataType &data, bool canOverride)
{
    bool result = false;

    if (canOverride || map->find(key) == map->end())
    {
        (*map)[key] = data;
        result = true;
    }

    return result;
}

template <typename KeyType, typename DataType, typename KeyCompareType>
bool Map<KeyType, DataType, KeyCompareType>::remove(const KeyType &key)
{
    bool result = false;
    auto it = map->find(key);
    if (it != map->end())
    {
        map->erase(it);
        result = true;
    }
    return result;
}

template <typename KeyType, typename DataType, typename KeyCompareType>
DataType *Map<KeyType, DataType, KeyCompareType>::getDataPtr(const KeyType &key) const
{
    DataType* result = nullptr;

    auto it = map->find(key);
    if (it != map->end())
    {
        result = &(it->second);
    }
    return result;
}

}

#endif // INTERNALTYPES_CPP
