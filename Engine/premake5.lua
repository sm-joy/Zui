project "Zui"
    if _ACTION == "export-compile-commands" then
        location (ROOT)
    else
        location (ROOT .. "/build/" .. _ACTION .. "/Zui")
    end

    kind "SharedLib"

    defines { "ZUI_BUILD_DLL" }

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

    links { "glfw", "spdlog" }


    postbuildcommands {
        ("{MKDIR} ../../bin/" .. OUTPUT_DIR_CONFIG .. "/Game"),
        ("{COPYFILE} %{!path.getabsolute(cfg.buildtarget.abspath)} " .. ROOT .. "/build/bin/" .. OUTPUT_DIR_CONFIG .. "/Game/")
    }

    filter "system:windows"
        links {
            "opengl32",
            "gdi32",
            "user32",
            "shell32",
        }

    filter "system:linux"
        links { "GL" }

    filter{}


