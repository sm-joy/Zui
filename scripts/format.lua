newaction {
    trigger     = "format",
    description = "Format all source files with clang-format",
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

        print("format: Formatting " .. #files .. " files...")
        for _, f in ipairs(files) do
            os.execute("clang-format -i " .. f)
        end
        print("format: Execution complete")
    end
}
