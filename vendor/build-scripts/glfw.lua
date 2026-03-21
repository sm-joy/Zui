project "glfw"
    location (ROOT .. "/build/" .. _ACTION .. "/glfw")
    kind        "StaticLib"
    language    "C"
    cdialect    "C99"

    defines {
        "_GLFW_WIN32",
        "UNICODE",
        "_UNICODE",
        "_CRT_SECURE_NO_WARNINGS",
    }

    files {
        ROOT .. "/vendor/glfw/include/GLFW/glfw3.h",
        ROOT .. "/vendor/glfw/include/GLFW/glfw3native.h",
        ROOT .. "/vendor/glfw/src/internal.h",
        ROOT .. "/vendor/glfw/src/platform.h",
        ROOT .. "/vendor/glfw/src/mappings.h",
        ROOT .. "/vendor/glfw/src/context.c",
        ROOT .. "/vendor/glfw/src/init.c",
        ROOT .. "/vendor/glfw/src/input.c",
        ROOT .. "/vendor/glfw/src/monitor.c",
        ROOT .. "/vendor/glfw/src/platform.c",
        ROOT .. "/vendor/glfw/src/vulkan.c",
        ROOT .. "/vendor/glfw/src/window.c",
        ROOT .. "/vendor/glfw/src/egl_context.c",
        ROOT .. "/vendor/glfw/src/osmesa_context.c",
        ROOT .. "/vendor/glfw/src/null_platform.h",
        ROOT .. "/vendor/glfw/src/null_joystick.h",
        ROOT .. "/vendor/glfw/src/null_init.c",
        ROOT .. "/vendor/glfw/src/null_monitor.c",
        ROOT .. "/vendor/glfw/src/null_window.c",
        ROOT .. "/vendor/glfw/src/null_joystick.c",
        ROOT .. "/vendor/glfw/src/win32_platform.h",
        ROOT .. "/vendor/glfw/src/win32_joystick.h",
        ROOT .. "/vendor/glfw/src/win32_time.h",
        ROOT .. "/vendor/glfw/src/win32_thread.h",
        ROOT .. "/vendor/glfw/src/win32_init.c",
        ROOT .. "/vendor/glfw/src/win32_joystick.c",
        ROOT .. "/vendor/glfw/src/win32_monitor.c",
        ROOT .. "/vendor/glfw/src/win32_window.c",
        ROOT .. "/vendor/glfw/src/win32_module.c",
        ROOT .. "/vendor/glfw/src/win32_time.c",
        ROOT .. "/vendor/glfw/src/win32_thread.c",
        ROOT .. "/vendor/glfw/src/wgl_context.c",
    }
    includedirs {
        ROOT .. "/vendor/glfw/include",
        ROOT .. "/vendor/glfw/src",
    }

    filter "toolset:msc"
        buildoptions { "/W3" }

    filter "toolset:gcc or clang"
        buildoptions { "-Wall" }

    filter {}
