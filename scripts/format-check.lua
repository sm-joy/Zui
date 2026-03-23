newaction({
    trigger = "format-check",
    description = "Check formatting without modifying files (CI)",
    execute = function()
        local dirs = {
            "Engine/src",
            "Engine/include",
            "Sandbox/Game/src",
        }

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
        print("format-check: Checking " .. #files .. " files...")
        for _, f in ipairs(files) do
            local result = os.execute("clang-format --dry-run --Werror " .. f)
            if result ~= true then
                print("  format-check: FAIL: " .. f)
                failed = true
            end
        end

        if failed then
            print("\nformat-check: Formatting errors found. Run: premake5 format")
            os.exit(1)
        else
            print("format-check: All files formatted correctly.")
        end
    end,
})
