workspace "DC-Project"
    configurations {"Debug", "Release"}
    location "build"

    project "Conway-Game-Of-Life"
        kind "ConsoleApp"
        language "C++"
        targetdir "bin/%{cfg.buildcfg}"

        files {"inc/**.h", "src/**.cpp"}

        includedirs{"Break-Release/inc/", "inc/", "Break-Release/glm/include/"}

        links {"Break_Infrastructure", "Break_Graphics", "Break_Physics"}

        filter "configurations:Debug"
            libdirs {"Break-Release/lib/vs2012/debug/"}
            defines {"DEBUG"}
            flags {"Symbols"}

        filter "configurations:Release"
            libdirs {"Break-Release/lib/vs2012/release/"}
            defines {"NDEBUG"}
            optimize "On"
