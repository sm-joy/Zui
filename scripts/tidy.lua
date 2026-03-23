newaction({
    trigger = "tidy",
    description = "Run clang-tidy on all source files",
    execute = function()
        os.execute(_PREMAKE_COMMAND .. " compile-commands")
        local files = {}
        for _, f in ipairs(os.matchfiles("Engine/src/**.cpp")) do
            table.insert(files, f)
        end
        for _, f in ipairs(os.matchfiles("Sandbox/Game/src/**.cpp")) do
            table.insert(files, f)
        end
        print("tidy: Running clang-tidy on " .. #files .. " files...")
        for _, f in ipairs(files) do
            if os.execute("clang-tidy --quiet " .. f) ~= true then
                print("tidy: clang-tidy found issues.")
                os.exit(1)
            end
        end
        print("tidy: All checks passed.")
    end,
})
