project "glfw"
    kind        "StaticLib"
    language    "C"
    cdialect    "C99"
    targetname  "glfw3"

    defines {
        "_GLFW_WIN32",
        "UNICODE",
        "_UNICODE",
        "_CRT_SECURE_NO_WARNINGS",
    }

    files {
        "include/GLFW/glfw3.h",
        "include/GLFW/glfw3native.h",
        "src/internal.h",
        "src/platform.h",
        "src/mappings.h",
        "src/context.c",
        "src/init.c",
        "src/input.c",
        "src/monitor.c",
        "src/platform.c",
        "src/vulkan.c",
        "src/window.c",
        "src/egl_context.c",
        "src/osmesa_context.c",
        "src/null_platform.h",
        "src/null_joystick.h",
        "src/null_init.c",
        "src/null_monitor.c",
        "src/null_window.c",
        "src/null_joystick.c",
        "src/win32_platform.h",
        "src/win32_joystick.h",
        "src/win32_time.h",
        "src/win32_thread.h",
        "src/win32_init.c",
        "src/win32_joystick.c",
        "src/win32_monitor.c",
        "src/win32_window.c",
        "src/win32_module.c",
        "src/win32_time.c",
        "src/win32_thread.c",
        "src/wgl_context.c",
    }

    includedirs {
        "include",
        "src",
    }

    links { "gdi32" }

    filter "toolset:msc"
        buildoptions { "/W3" }

    filter "toolset:gcc or clang"
        buildoptions { "-Wall" }

    filter {}
