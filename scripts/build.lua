newoption {
    trigger     = "config",
    value       = "CONFIG",
    description = "Build configuration",
    default     = "debug",
    allowed     = {
        { "debug",        "Debug build"        },
        { "release",      "Release build"      },
        { "distribution", "Distribution build" },
    }
}

newoption {
    trigger     = "target",
    value       = "TARGET",
    description = "Target to build (default: all)",
    default     = "all",
}

newaction {
    trigger     = "make-build",
    description = "Build via gmake",
    execute     = function()
        local config = _OPTIONS["config"] or "debug"
        local target = _OPTIONS["target"] or "all"

        local cmd = "mingw32-make -C build/gmake"
                 .. " config=" .. config
                 .. (target ~= "all" and " " .. target or "")

        print("make-build: " .. cmd)
        if not os.execute(cmd) then
            os.exit(1)
        end
    end
}

newaction {
    trigger     = "make-clean",
    description = "Clean all build artifacts",
    execute     = function()
        os.execute("mingw32-make -C build/gmake clean")
        os.rmdir("build/bin")
        os.rmdir("build/int")
        print("make-clean: done")
    end
}
