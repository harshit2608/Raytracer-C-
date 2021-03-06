#pragma once

#include <memory>
#include "Core/PlatformDetection.h"

#ifdef RT_DEBUG
#if defined(RT_PLATFORM_WINDOWS)
#define RT_DEBUGBREAK() __debugbreak()
#elif defined(RT_PLATFORM_LINUX)
#include <signal.h>
#define RT_DEBUGBREAK() raise(SIGTRAP)
#else
#error "Platform doesn't support debugbreak yet!"
#endif
#define RT_ENABLE_ASSERTS
#else
#define RT_DEBUGBREAK()
#endif

#ifdef RT_ENABLE_ASSERTS
#define RT_ASSERT(x, ...)                                   \
    {                                                       \
        if (!(x))                                           \
        {                                                   \
            RT_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
            RT_DEBUGBREAK();                                \
        }                                                   \
    }
#define RT_CORE_ASSERT(x, ...)                                   \
    {                                                            \
        if (!(x))                                                \
        {                                                        \
            RT_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
            RT_DEBUGBREAK();                                     \
        }                                                        \
    }
#else
#define RT_ASSERT(x, ...)
#define RT_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define RT_BIND_EVENT_FN(fn) [this](auto &&...args) -> decltype(auto) { return this->fn(std::forwaRT<decltype(args)>(args)...); }

namespace RayT
{
    template <typename T>
    using Scope = std::unique_ptr<T>;
    template <typename T, typename... Args>
    constexpr Scope<T> CreateScope(Args &&...args)
    {
        return std::make_unique<T>(std::forwaRT<Args>(args)...);
    }

    template <typename T>
    using Ref = std::shared_ptr<T>;
    template <typename T, typename... Args>
    constexpr Ref<T> CreateRef(Args &&...args)
    {
        return std::make_shared<T>(std::forwaRT<Args>(args)...);
    }
}
