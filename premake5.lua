require "vendor/export-compile-commands/export-compile-commands"
require "scripts/format"
require "scripts/format-check"
require "scripts/tidy"
require "scripts/check"
require "scripts/build"
require "scripts/build-deps"
require "scripts/compile-commands"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
IncludeDir = {}
IncludeDir["spdlog"] = "vendor/spdlog/include"


workspace "Zui"
    location ("build/" .. _ACTION)
	architecture "x64"
    toolset "clang"

	configurations
	{
		"Debug",
		"Release",
		"Distribution"
	}


    filter "configurations:Debug"
		defines "ZUI_DEBUG"
        runtime "Debug"
        optimize "Off"
		symbols "On"

	filter "configurations:Release"
		defines "ZUI_RELEASE"
        runtime "Release"
        symbols "On"
		optimize "Speed"

	filter "configurations:Distribution"
		defines "ZUI_DISTRIBUTION"
        runtime "Release"
        symbols "Off"
		optimize "Full"

    filter "system:windows"
        defines { "ZUI_PLATFORM_WINDOWS" }
        systemversion "latest"

    filter "system:linux"
        defines { "ZUI_PLATFORM_LINUX" }

    filter "system:macosx"
        defines { "ZUI_PLATFORM_MACOS" }

    filter {}




project "Zui"
    if _ACTION == "export-compile-commands" then
        location (ROOT)
    else
        location ("build/" .. _ACTION .. "/Zui")
    end

    kind "StaticLib"
    language "C++"
    cppdialect "C++20"

    targetdir ("build/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("build/int/" .. outputdir .. "/%{prj.name}")

    files {
        "Engine/include/**.hpp",
        "Engine/include/**.h",
        "Engine/src/**.hpp",
        "Engine/src/**.h",
        "Engine/src/**.cpp",
    }

    includedirs {
        "Engine/include",
        "%{IncludeDir.spdlog}",
    }

    links {
    }

    libdirs {
    }

    linkoptions { "-static" }

    filter "system:windows"
        systemversion "latest"

        links { }

    filter{}

project "Game"
    if _ACTION == "export-compile-commands" then
        location (ROOT)
    else
        location ("build/" .. _ACTION .. "/Game")
    end
    kind "ConsoleApp"
	language "C++"
    cppdialect "C++20"

    targetdir ("build/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("build/int/" .. outputdir .. "/%{prj.name}")

    files {
        "Sandbox/%{prj.name}/src/**.hpp",
        "Sandbox/%{prj.name}/src/**.h",
        "Sandbox/%{prj.name}/src/**.cpp",
    }

    includedirs {
        "Engine/include",
        "%{IncludeDir.spdlog}",
    }

    links {
        "Zui"
    }

    filter "system:windows"
		systemversion "latest"

		defines
		{
			"ZUI_PLATFORM_WINDOWS"
		}


-- include "vendor/build-scripts/glfw"
