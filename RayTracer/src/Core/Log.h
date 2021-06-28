#pragma once

#include "Core/Base.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace RayT
{
    class Log
    {
    public:
        static void Init();

        static Ref<spdlog::logger> &GetCoreLogger()
        {
            return s_CoreLogger;
        }
        static Ref<spdlog::logger> &GetClientLogger()
        {
            return s_ClientLogger;
        }

    private:
        static Ref<spdlog::logger> s_CoreLogger;
        static Ref<spdlog::logger> s_ClientLogger;
    };

}

// Core log macros
#define RT_CORE_TRACE(...) ::Render::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define RT_CORE_INFO(...) ::Render::Log::GetCoreLogger()->info(__VA_ARGS__)
#define RT_CORE_WARN(...) ::Render::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define RT_CORE_ERROR(...) ::Render::Log::GetCoreLogger()->error(__VA_ARGS__)
#define RT_CORE_CRITICAL(...) ::Render::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define RT_TRACE(...) ::Render::Log::GetClientLogger()->trace(__VA_ARGS__)
#define RT_INFO(...) ::Render::Log::GetClientLogger()->info(__VA_ARGS__)
#define RT_WARN(...) ::Render::Log::GetClientLogger()->warn(__VA_ARGS__)
#define RT_ERROR(...) ::Render::Log::GetClientLogger()->error(__VA_ARGS__)
#define RT_CRITICAL(...) ::Render::Log::GetClientLogger()->critical(__VA_ARGS__)
