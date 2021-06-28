include "./thirdparty/premake/premake_customization/solution_items.lua"

workspace "RayTracer"
    architecture "x86_64"
    startproject "RayTracer"

    configurations
    {
        "Debug",
        "Realease",
        "Dist"
    }

    solution_items
	{
		".editorconfig"
	}

    flags
    {
        "MultiProcessorCompile"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["Stb_Image"] = "%{wks.location}/RayTracer/thirdparty/stb_image"

group "Dependencies"
	include "thirdparty/premake"
group ""

include "RayTracer"
