workspaceName = path.getbasename(os.getcwd())

workspace (workspaceName)
    configurations { "Debug", "Release" }
    platforms { "x64" }

    project ("MatrixMul")
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++20"
        includedirs { "./" }
        files { "**.cpp" }
    
        filter "configurations:Debug"
            symbols "On"

        filter "configurations:Release"
            buildoptions { "-g", "-O3" }
