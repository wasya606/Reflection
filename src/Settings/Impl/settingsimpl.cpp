#include "settingsimpl.h"

SettingsImpl::SettingsImpl() : bitFieldsMap(new std::map<NameId, BitField>),
                               anyFieldsMap(new std::map<NameId, void*>)
{

}

SettingsImpl::SettingsImpl(const SettingsImpl &obj)
{

}

SettingsImpl::SettingsImpl(SettingsImpl &&obj)
{

}

SettingsImpl::~SettingsImpl()
{

}

bool SettingsImpl::addBitField(FieldID fieldId, const BitField initValue)
{
    if (!bitFieldExist(fieldId))
    {
        (*bitFieldsMap)[fieldId] = initValue;
        return true;
    }
    return false;
}

bool SettingsImpl::addBitField(const char *fieldName, const BitField initValue)
{
    return addBitField(NameEncoder::encode(fieldName), initValue);
}

bool SettingsImpl::setBits(FieldID fieldId, const BitField value, const BitField mask)
{
    if (bitFieldExist(fieldId))
    {
        (*bitFieldsMap)[fieldId] = value & mask;
        return true;
    }
    return false;
}

bool SettingsImpl::setBits(const char *fieldName, const BitField value, const BitField mask)
{
    return setBits(NameEncoder::encode(fieldName), value, mask);
}

bool SettingsImpl::setBit(FieldID fieldId, const BitMask bitMask, const bool bitValue)
{
    if (bitFieldExist(fieldId))
    {
        (*bitFieldsMap)[fieldId] ^= ((bitValue ? 0xFFFF : 0) & bitMask);
        return true;
    }
    return false;
}

bool SettingsImpl::setBit(const char *fieldName, const BitMask bitMask, const bool bitValue)
{
    return setBit(NameEncoder::encode(fieldName), bitMask, bitValue);
}

BitField SettingsImpl::getBits(FieldID fieldId, const BitField mask) const
{
    if (bitFieldExist(fieldId))
    {
        return bitFieldsMap->at(fieldId) & mask;
    }
    return false;
}

BitField SettingsImpl::getBits(const char *fieldName, const BitField mask) const
{
    return getBits(NameEncoder::encode(fieldName));
}

bool SettingsImpl::getBit(FieldID fieldId, const BitMask bitMask)
{
    if (bitFieldExist(fieldId))
    {
        return bitFieldsMap->at(fieldId) & bitMask;
    }
    return false;
}

bool SettingsImpl::getBit(const char *fieldName, const BitMask bitMask)
{
    return getBit(NameEncoder::encode(fieldName), bitMask);
}

bool SettingsImpl::bitFieldExist(const char *fieldName) const
{
    return bitFieldExist(NameEncoder::encode(fieldName));
}

bool SettingsImpl::fieldExist(const char *fieldName) const
{
    return fieldExist(NameEncoder::encode(fieldName));
}

bool SettingsImpl::bitFieldExist(FieldID fieldId) const
{
    return bitFieldsMap->find(fieldId) != bitFieldsMap->end();
}

bool SettingsImpl::fieldExist(FieldID fieldId) const
{
    return anyFieldsMap->find(fieldId) != anyFieldsMap->end();
}

