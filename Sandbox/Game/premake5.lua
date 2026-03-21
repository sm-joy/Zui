 project "Game"
    if _ACTION == "export-compile-commands" then
        location (ROOT)
    else
        location (ROOT .. "/build/" .. _ACTION .. "/Game")
    end
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"

    targetdir (ROOT .. "/build/bin/" .. OUTPUT_DIR_CONFIG .. "/%{prj.name}")
    objdir (ROOT .. "/build/int/" .. OUTPUT_DIR_CONFIG .. "/%{prj.name}")

    files {
        ROOT .. "/Sandbox/%{prj.name}/src/**.hpp",
        ROOT .. "/Sandbox/%{prj.name}/src/**.cpp",
    }

    includedirs {
        ROOT .. "/Engine/include",
        IncludeDir.spdlog,
    }

    links { "Zui" }

    filter "system:windows"
        systemversion "latest"

        defines {
            "ZUI_PLATFORM_WINDOWS"
        }

    filter {}

