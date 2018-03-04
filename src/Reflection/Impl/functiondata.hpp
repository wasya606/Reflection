#ifndef FUNCTIONDATA_H
#define FUNCTIONDATA_H

#include "typetools.h"
#include "internaltypes.h"

using namespace Common;

namespace Internal {

template<typename T>
struct FunctionData;

template<typename RetType, typename ...Args>
struct FunctionData<RetType (*)(Args...)>
{
    using FunctionPtr = RetType (*)(Args...);
    using ReturnType = RetType;

    static const size_t argsCount = sizeof...(Args);

    template <size_t index>
    struct Argument
    {
        using Type = typename std::tuple_element<index, std::tuple<Args...>>::type;
    };

    template <const size_t index = 0, const size_t size = argsCount, typename... FArgs>
    struct Reflector
    {
        static void invoke(UniFunctionPtr func, CharPtrList* params, FArgs... args)
        {
            using ArType = typename Argument<index>::Type;
            //using ArType = typename Argument<0, index, Args...>::Type;

            auto value = Extractor<ArType>::getValue(params->front());
            params->pop_front();
            Logger::debug() << "Value type is: " << typeid(value).name();
            Reflector<index + 1, size, FArgs..., decltype(value)>::invoke(func, params, args..., value);
        }
    };

    template <const size_t size, typename... FArgs>
    struct Reflector<size, size, FArgs...>
    {
        static void invoke(UniFunctionPtr func, CharPtrList* params, FArgs... args)
        {
            try
            {
                func(args...);
            }
            catch(...)
            {
                Logger::error() << "Invoke exception!!!";
            }

            cleanAll();
            Logger::debug() << "Clean success!!!";
            delete params;
        }
    };

    static void invoker(UniFunctionPtr functionPtr, CharPtrList* params)
    {
        Reflector<>::invoke(functionPtr, params);
    }

};
}

#endif // FUNCTIONDATA_H
