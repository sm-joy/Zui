require "vendor/export-compile-commands/export-compile-commands"
require "scripts/format"
require "scripts/format-check"
require "scripts/tidy"
require "scripts/check"
require "scripts/build"
require "scripts/build-deps"
require "scripts/compile-commands"


ROOT = path.getabsolute(".")
OUTPUT_DIR_CONFIG = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {
    spdlog = ROOT .. "/vendor/spdlog/include",
    glfw = ROOT .. "/vendor/glfw/include"
}


workspace "Zui"
    location (ROOT .. "/build/" .. _ACTION)
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


    include "Engine"

    include "Sandbox/Game"


include "vendor/build-scripts/glfw"
