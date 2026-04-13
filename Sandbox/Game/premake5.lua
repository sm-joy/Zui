 project "Game"
    if _ACTION == "export-compile-commands" then
        location (ROOT)
    else
        location (ROOT .. "/build/" .. _ACTION .. "/Game")
    end

    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"

     files {
        ROOT .. "/Sandbox/%{prj.name}/src/**.hpp",
        ROOT .. "/Sandbox/%{prj.name}/src/**.cpp",
    }

    includedirs {
        ROOT .. "/Engine/include",
        IncludeDir.spdlog,
        IncludeDir.glm
    }

    links { "Zui" }

    filter {}

