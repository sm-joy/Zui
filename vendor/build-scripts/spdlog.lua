project "spdlog"
    location (ROOT .. "/build/" .. _ACTION .. "/spdlog")
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

    files
    {
        ROOT .. "/vendor/spdlog/src/spdlog.cpp",
        ROOT .. "/vendor/spdlog/src/stdout_sinks.cpp",
        ROOT .. "/vendor/spdlog/src/color_sinks.cpp",
        ROOT .. "/vendor/spdlog/src/file_sinks.cpp",
        ROOT .. "/vendor/spdlog/src/async.cpp",
        ROOT .. "/vendor/spdlog/src/cfg.cpp",
        ROOT .. "/vendor/spdlog/src/bundled_fmtlib_format.cpp",
    }

    includedirs
    {
        ROOT .. "/vendor/spdlog/include"
    }

    defines
    {
        "SPDLOG_COMPILED_LIB",
    }

    filter "system:linux or system:macosx"
        links { "pthread" }

    filter "system:windows"
        defines { "WIN32", "_WINDOWS" }
        systemversion "latest"

    filter "action:vs*"
        buildoptions { "/utf-8", "/Zc:__cplusplus" }

    filter "configurations:Debug"
        targetsuffix "d"

    filter {}
