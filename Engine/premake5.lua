project "Zui"
    if _ACTION == "export-compile-commands" then
        location (ROOT)
    else
        location (ROOT .. "/build/" .. _ACTION .. "/Zui")
    end

    kind "SharedLib"
    language "C++"
    cppdialect "C++20"

    defines { "ZUI_BUILD_DLL" }

    targetdir (ROOT .. "/build/bin/" .. OUTPUT_DIR_CONFIG .. "/%{prj.name}")
    objdir (ROOT .. "/build/int/" .. OUTPUT_DIR_CONFIG .. "/%{prj.name}")

    files {
        ROOT .. "/Engine/include/**.hpp",
        ROOT .. "/Engine/src/**.hpp",
        ROOT .. "/Engine/src/**.cpp",
    }

    includedirs {
        ROOT .. "/Engine/include",
        IncludeDir.spdlog,
        IncludeDir.glfw,
    }

    links { "glfw" }


    postbuildcommands {
        ("{MKDIR} ../../bin/" .. OUTPUT_DIR_CONFIG .. "/Game"),
        ("{COPYFILE} %{!path.getabsolute(cfg.buildtarget.abspath)} " .. ROOT .. "/build/bin/" .. OUTPUT_DIR_CONFIG .. "/Game/")
    }

    filter "system:windows"
        systemversion "latest"

        links {
            "opengl32",
            "gdi32",
            "user32",
            "shell32",
        }

    filter "system:linux"
        links { "GL" }

    filter{}


