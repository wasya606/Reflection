#ifndef COMMON_H
#define COMMON_H

#include <functional>
#include <cstring>
#include <list>

namespace Common
{
    //********************   Key Comparing  ********************
    template<typename Type>
    struct Comparer
    {
        static bool compare(const Type& key1, const Type& key2);
    };

    //**********************    ContainerData    ******************
    template<typename KeyType, typename DataType>
    struct ContainerData
    {
        ContainerData() = delete;
        ContainerData(const KeyType& key, const DataType& data);
        virtual ~ContainerData();

        DataType* dataPtr;
        KeyType* keyPtr;
        ContainerData<KeyType, DataType>* prevPtr;
        ContainerData<KeyType, DataType>* nextPtr;
        bool keyComparing(const KeyType&);
    };

    //**********************    Container    ************************
    template<typename KeyType, typename DataType>
    class Container
    {
    public:
        using ElementType = ContainerData<KeyType, DataType>;
        Container();
        virtual ~Container();

        virtual bool push(const KeyType& key, const DataType& data);
        virtual DataType* get(const KeyType& key);
        virtual bool del(const KeyType& key);

        virtual void clean();
        virtual size_t getSize();

    protected:
        size_t size;
        ElementType* firstElement;
        ElementType* lastElement;

    protected:
        ElementType* getElement(const KeyType& key);
        bool remove(const ElementType* deletingElement);
    };

    //**********************    List    ******************************
    template<typename DataType>
    class List : public Container<size_t, DataType>
    {
    public:
        using Base = Container<size_t, DataType>;
        void push(const DataType& data);

        DataType& operator[](const size_t& index);
    };


    /**
     * @brief This is a simple list of char*
     */
    using StringList = List<char*>;

    /**
     * @brief This is a simple map with const char* key
     * @param T - class of map elements
     */
    template<typename T>
    using MapStr = Container<const char*, T>;

    /**
     *  Universal function type
     */
    using UniFunctionPtr = void (*)(...);

    enum SettingsFlags
    {
        FLAG_0 = 1,
        FLAG_1 = 1 << 1,
        FLAG_2 = 1 << 2,
        FLAG_3 = 1 << 3,
        FLAG_4 = 1 << 4,
        FLAG_5 = 1 << 5,
        FLAG_6 = 1 << 6,
        FLAG_7 = 1 << 7,
    };

    /**
     * @brief ParametersValidation enum
     * Defines the validations for cmd parameters and function arguments
     *
     * ARGS_COUNT   - Skip executing the command if count of parameters is less
     *                than arguments of corresponding function.
     *
     * TYPE_SIZE    - Skip executing the command if size of type for any parameter
     *                is more than size of type corresponding argument.
     *
     * INT_SIGNING  - Skip executing the command if any of integer parameters is negative
     *                but corresponding argument is unsigned.
     */
    struct ValidationFlags
    {
        static const SettingsFlags ARGS_COUNT = SettingsFlags::FLAG_0;
        static const SettingsFlags TYPE_SIZE = SettingsFlags::FLAG_1;
        static const SettingsFlags INT_SIGNING = SettingsFlags::FLAG_2;
    };

    /**
     * @brief The DebugLoggingLevel
     */
    struct LoggingFlags
    {
        static const SettingsFlags ERROR = SettingsFlags::FLAG_0;
        static const SettingsFlags WARNING = SettingsFlags::FLAG_1;
        static const SettingsFlags INFO = SettingsFlags::FLAG_2;
        static const SettingsFlags DEBUG = SettingsFlags::FLAG_3;
    };

    enum SettingsID
    {
        SETTINGS_VALIDATION,
        SETTINGS_LOGGING
    };

    /**
     * @brief This is a simple map for store settings
     */
    using SettingsMap = Container<SettingsID, size_t>;

    /**
     * @brief Get a pure type
     * Removes pointer, reference, and cv-qualifiers
     * @param T - source type
     */
    template<typename T>
    struct TypeCleaner
    {
        using PureCvType = typename std::remove_cv<T>::type;

        using PureRefType = typename std::remove_reference<T>::type;
        using PureRefCvType = typename std::remove_cv<PureRefType>::type;

        using PureCvRefType = typename std::remove_reference<PureCvType>::type;
        using PureCvRefCvType = typename std::remove_cv<PureCvRefType>::type;

        using PurePtrType = typename std::remove_pointer<T>::type;
        using PurePtrCvType = typename std::remove_cv<PurePtrType>::type;

        using PureCvPtrType = typename std::remove_pointer<PureCvType>::type;
        using PureCvPtrCvType = typename std::remove_cv<PureCvPtrType>::type;

        using PureCvRefCvPtrType = typename std::remove_pointer<PureCvRefCvType>::type;
        using PureType = typename std::remove_cv<PureCvRefCvPtrType>::type;

    };

    using CharPtrList = std::list<char*>;

    /**
     *  Type of pointer to function-wrapper that will call a target function.
     */
    using InvokerPtr = void (*)(UniFunctionPtr, CharPtrList*);
}

#include "common.cpp"

#endif // COMMON_H
