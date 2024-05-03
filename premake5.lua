local includes = "game-engine/dependencies/include"
local static_libs = "game-engine/dependencies/static-libs"

workspace "game-engine"
    startproject "Sandbox"   
    configurations { "debug", "release" }
    architecture "x86_64"

project "game-engine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    location "game-engine"

    pchheader "pch.h"
    pchsource "%{prj.location}/src/pch.cpp"

    targetdir "bin/%{cfg.buildcfg}"
    objdir "obj/%{cfg.buildcfg}"

    files { 
        "%{prj.location}/src/**.h", 
        "%{prj.location}/src/**.cpp", 
        includes .. "/**.h", 
        includes .. "/**.cpp"
    }

    includedirs { includes, "game-engine/src" }
    libdirs { static_libs, "bin/" }

    links { "opengl32.lib", "glfw3.lib", "glew32s.lib", "OpenAL32.lib", "sndfile.lib" }

    filter "configurations:debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:release"
        defines { "NDEBUG" }
        optimize "On"

    filter ("files:" .. includes .. "/**.cpp")
        flags {"NoPCH"}

project "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    location "Sandbox"

    targetdir "bin/%{cfg.buildcfg}"
    objdir "obj/%{cfg.buildcfg}"

    files { "%{prj.location}/src/**.h", "%{prj.location}/src/**.cpp" }

    dependson "game-engine"
    links { "game-engine.lib" }

    includedirs { includes, "game-engine/src" }
    libdirs { static_libs, "%{cfg.targetdir}" }

    filter "configurations:debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:release"
        defines { "NDEBUG" }
        optimize "On"
