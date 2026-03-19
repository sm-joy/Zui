newaction {
    trigger     = "check",
    description = "Run clang-format and clang-tidy together",
    execute = function()
        print("=== check: Formatting ===")
        os.execute("premake5 format")
        print("\n=== check: Tidy ===")
        os.execute("premake5 tidy")
    end
}
