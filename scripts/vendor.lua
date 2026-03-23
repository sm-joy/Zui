newaction {
    trigger = "generate-glad",
    description = "Generate GLAD OpenGL loader",
    execute = function()
        os.execute("glad --api gl:core=4.6 --out-path vendor/glad --reproducible")
    end
}
