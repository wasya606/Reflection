#ifndef SETTINGSIMPL_H
#define SETTINGSIMPL_H
#include "src/Common/common.h"
#include "src/Common/nameencoder.h"
#include <map>

using namespace Common;

using FieldID = size_t;
using BitField = long long unsigned int;

enum BitMask
{
    BIT_0   = 1,      BIT_1   = 1 << 1,  BIT_2   = 1 << 2,  BIT_3   = 1 << 3,
    BIT_4   = 1 << 4, BIT_5   = 1 << 5,  BIT_6   = 1 << 6,  BIT_7   = 1 << 7,
    BIT_8   = 1 << 8, BIT_9   = 1 << 9,  BIT_10  = 1 << 10, BIT_11  = 1 << 11,
    BIT_12  = 1 << 9, BIT_13  = 1 << 13, BIT_14  = 1 << 14, BIT_15  = 1 << 15
};

class Settings;

class SettingsImpl
{
public:
    friend class Settings;
    SettingsImpl();
    SettingsImpl(const SettingsImpl& obj);
    SettingsImpl(SettingsImpl&& obj);

    ~SettingsImpl();

public:
    bool addBitField(FieldID fieldId, const BitField initValue = 0);
    bool addBitField(const char* fieldName, const BitField initValue = 0);

    bool setBits(FieldID fieldId, const BitField value, const BitField mask = 0xFFFF);
    bool setBits(const char* fieldName, const BitField value, const BitField mask = 0xFFFF);

    bool setBit(FieldID fieldId, const BitMask bitMask, const bool bitValue);
    bool setBit(const char* fieldName, const BitMask bitMask, const bool bitValue);

    BitField getBits(FieldID fieldId, const BitField mask = 0xFFFF) const;
    BitField getBits(const char* fieldName, const BitField mask = 0xFFFF) const;

    bool getBit(FieldID fieldId, const BitMask bitMask);
    bool getBit(const char* fieldName, const BitMask bitMask);


    template<typename ValueType>
    bool addField(FieldID fieldId);
    template<typename ValueType>
    bool addField(const char* fieldName);

    template<typename ValueType>
    bool addField(FieldID fieldId, const ValueType& initValue);
    template<typename ValueType>
    bool addField(const char* fieldName, const ValueType& initValue);

    template<typename ValueType>
    bool setValue(FieldID fieldId, const ValueType& value);
    template<typename ValueType>
    bool setValue(const char* fieldName, const ValueType& value);

    template<typename ValueType>
    ValueType getValue(FieldID fieldId) const;
    template<typename ValueType>
    ValueType getValue(const char* fieldName) const;

    bool bitFieldExist(FieldID fieldId) const;
    bool bitFieldExist(const char* fieldName) const;

    bool fieldExist(FieldID fieldId) const;
    bool fieldExist(const char* fieldName) const;

private:

    std::map<NameId, BitField> *bitFieldsMap;
    std::map<NameId, void*> *anyFieldsMap;

};


//======================================================================
//--------------
template<typename ValueType>
bool SettingsImpl::addField(FieldID fieldId)
{
    if (!fieldExist(fieldId))
    {
        (*anyFieldsMap)[fieldId] = (static_cast<void*>(new ValueType));
        return true;
    }
    return false;
}

template<typename ValueType>
bool SettingsImpl::addField(const char* fieldName)
{
    return addField<ValueType>(NameEncoder::encode(fieldName));
}
//-----------
template<typename ValueType>
bool SettingsImpl::addField(FieldID fieldId, const ValueType& initValue)
{
    if (!fieldExist(fieldId))
    {
        ValueType* valuePtr = new ValueType;
        *valuePtr = initValue;
        (*anyFieldsMap)[fieldId] = static_cast<void*>(valuePtr);
        return true;
    }
    return false;
}

template<typename ValueType>
bool SettingsImpl::addField(const char* fieldName, const ValueType& initValue)
{
    return addField<ValueType>(NameEncoder::encode(fieldName), initValue);
}
//-------------------
template<typename ValueType>
bool SettingsImpl::setValue(FieldID fieldId, const ValueType& value)
{
    if (fieldExist(fieldId))
    {
        ValueType* valuePtr = static_cast<ValueType*>(anyFieldsMap->at(fieldId));
        *valuePtr = value;
        return true;
    }
    return false;
}

template<typename ValueType>
bool SettingsImpl::setValue(const char* fieldName, const ValueType& value)
{
    return setValue<ValueType>(NameEncoder::encode(fieldName), value);
}
//------------------
template<typename ValueType>
ValueType SettingsImpl::getValue(FieldID fieldId) const
{
    if (fieldExist(fieldId))
    {
        ValueType* valuePtr = static_cast<ValueType*>(anyFieldsMap->at(fieldId));
        return *valuePtr;
    }
    return ValueType();

}

template<typename ValueType>
ValueType SettingsImpl::getValue(const char* fieldName) const
{
    return getValue<ValueType>(NameEncoder::encode(fieldName));
}


#endif // SETTINGSIMPL_H
