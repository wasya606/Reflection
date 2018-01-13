#ifndef INTERNALTYPES_H
#define INTERNALTYPES_H
#include <map>
#include <list>
#include <vector>
#include "src/Common/common.h"
#include "functioninfo.h"
#include"src/Settings/Impl/settingsimpl.h"

using namespace Common;

enum ValidationSettings
{
    ARGS_COUNT_CHECK = BIT_0,
    ARGS_SIGN_CHECK = BIT_1,
    ARGS_FLOAT_CHECK = BIT_2,
    ARGS_TYPE_SIZE_CHECK = BIT_3
};

enum LogSettings
{
    ERRORS_ENABLED = BIT_0,
    ERRORS_LEV0 = BIT_1,
    ERRORS_LEV1 = BIT_2,
    ERRORS_TO_CONSOLE = BIT_3,

    WARNINGS_ENABLED = BIT_4,
    WARNINGS_LEV0 = BIT_5,
    WARNINGS_LEV1 = BIT_6,
    WARNINGS_TO_CONSOLE = BIT_7,

    INFO_ENABLED = BIT_8,
    INFO_LEV0 = BIT_9,
    INFO_LEV1 = BIT_10,
    INFO_TO_CONSOLE = BIT_11,

    DEBUG_ENABLED = BIT_12,
    DEBUG_LEV0 = BIT_13,
    DEBUG_LEV1 = BIT_14,
    DEBUG_TO_CONSOLE = BIT_15
};

namespace Internal {

template <typename KeyType, typename DataType, typename KeyCompareType = std::less<KeyType>>
class Map
{
public:
    Map();
    ~Map();

    bool insert(const KeyType& key, const DataType& data, bool canOverride = false);
    bool remove(const KeyType& key);
    DataType* getDataPtr(const KeyType& key) const;

private:
    std::map<KeyType, DataType, KeyCompareType>* map;
};

struct CharPtrComparer
{
    bool operator()(const char* key1, const char* key2)
    {
        return strcmp(key1, key2) < 0;
    }
};

template<typename T>
using CharPtrMap = Map<const char*, T, CharPtrComparer>;
using FunctionsList = std::vector<FunctionInfo*>;
using CommandsMap = CharPtrMap<size_t>;

}

#include "internaltypes.cpp"

#endif // INTERNALTYPES_H
