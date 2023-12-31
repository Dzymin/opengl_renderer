project "App"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    targetdir "%{wks.location}/bin/%{cfg.buildcfg}/%{prj.name}-%{cfg.platform}-%{cfg.architecture}"
    objdir "%{wks.location}/obj/%{cfg.buildcfg}/%{prj.name}-%{cfg.platform}-%{cfg.architecture}"

    files {
        "src/*.h",
        "src/*.cpp"
    }

    includedirs {
        "%{wks.location}/Dependencies/GLFW/include",
        "%{wks.location}/Dependencies/glad/include",
        "%{wks.location}/Dependencies/stb/include",
        "src/"
    }

    links {
        "GLFW",
        "glad",
        "stb",
        "opengl32.lib"
    }

    pchheader "pch.h"
    pchsource "src/pch.cpp"

    filter "configurations:Debug"
        defines { "APP_DEBUG" }
    
    filter "configurations:Release"
        defines { "APP_RELEASE" }

    filter "system:Windows"
        systemversion "latest"
        defines { "APP_PLATFORM_WINDOWS" }