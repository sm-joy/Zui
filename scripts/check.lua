newaction({
    trigger = "check",
    description = "Run clang-format and clang-tidy together",
    execute = function()
        print("PREMAKE_COMMAND: " .. _PREMAKE_COMMAND)
        print("ROOT: " .. path.getabsolute("."))
        print("=== check: Formatting ===")
        os.execute(_PREMAKE_COMMAND .. " format")
        print("\n=== check: Tidy ===")
        os.execute(_PREMAKE_COMMAND .. " tidy")
    end,
})
