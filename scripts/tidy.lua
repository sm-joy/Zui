newaction {
    trigger     = "tidy",
    description = "Run clang-tidy on all source files",
    execute = function()
        print("tidy: Generating compile commands...")
        os.execute("premake5 export-compile-commands")

        print("tidy: Running clang-tidy...")
        local result = os.execute("run-clang-tidy -p compile_commands/debug/ -j4")
        if result ~= 0 then
            print("tidy: clang-tidy found issues.")
            os.exit(1)
        else
            print("tidy: Execution complete")
        end
    end
}
