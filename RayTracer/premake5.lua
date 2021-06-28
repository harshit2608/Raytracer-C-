project "RayTracer"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "rtpch.h"
	pchsource "src/rtpch.cpp"

	files
	{	
		"src/**.h",
		"src/**.cpp",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"src",
		"thirdparty/spdlog/include"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
		}

	filter "system:linux"
		systemversion "latest"

	filter "configurations:Debug"
		defines "RT_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "RT_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "RT_DIST"
		runtime "Release"
		optimize "on"
