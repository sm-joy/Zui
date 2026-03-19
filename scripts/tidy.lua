newaction({
    trigger = "tidy",
    description = "Run clang-tidy on all source files",
    execute = function()
        local dirs = {
            "Engine/src",
            "Engine/include",
            "Sandbox/Game/src",
        }
        print("tidy: Generating compile commands...")
        os.execute(_PREMAKE_COMMAND .. " export-compile-commands")

        print("tidy: Copying compile_commands to the root directory...")
        os.copyfile("build/export-compile-commands/compile_commands/debug.json", "compile_commands.json")

        local files = {}
        for _, dir in ipairs(dirs) do
            for _, f in ipairs(os.matchfiles(dir .. "/**.cpp")) do
                table.insert(files, f)
            end
            for _, f in ipairs(os.matchfiles(dir .. "/**.hpp")) do
                table.insert(files, f)
            end
        end

        local failed = false
        print("tidy: Running clang-tidy on " .. #files .. " files...")
        for _, f in ipairs(files) do
            local result = os.execute("clang-tidy " .. f)
            if result ~= 0 then
                print("  FAIL: " .. f)
                failed = true
            end
        end

        if failed then
            print("tidy: clang-tidy found issues.")
            os.exit(1)
        else
            print("tidy: Execution complete")
        end
    end,
})
