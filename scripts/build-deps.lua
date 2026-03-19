newaction {
    trigger     = "build-spdlog",
    description = "Build spdlog",
    execute     = function()
        if not os.isdir("vendor/spdlog") then
            print("build-spdlog: spdlog submodule not found, adding...")
            os.execute("git submodule add https://github.com/gabime/spdlog.git vendor/spdlog")
        end

        os.execute("git submodule update --init --recursive")

        os.chdir("vendor/spdlog")
        os.rmdir("build")
        os.execute("cmake -S . -B build -G \"MinGW Makefiles\" -DCMAKE_BUILD_TYPE=Release -DSPDLOG_BUILD_SHARED=OFF -DSPDLOG_BUILD_EXAMPLE=OFF")
        os.execute("cmake --build build")
        os.chdir("../..")

        print("build-spdlog: spdlog built successfully")
    end
}
