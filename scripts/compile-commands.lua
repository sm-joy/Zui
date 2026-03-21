newaction({
    trigger = "compile-commands",
    description = "Run export-compile-commands and copies the debug.json to the root dir",
    execute = function()
        print("compile-commands: Generating compile commands...")
        os.execute(_PREMAKE_COMMAND .. " export-compile-commands")

        print("compile-commands: Copying compile_commands to the root directory...")
        os.copyfile("build/export-compile-commands/compile_commands/debug.json", "compile_commands.json")
    end,
})
