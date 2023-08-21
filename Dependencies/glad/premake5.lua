project "glad"
    kind "StaticLib"
    language "C"

    targetdir "%{wks.location}/bin/%{cfg.buildcfg}/%{prj.name}-%{cfg.platform}-%{cfg.architecture}"
    objdir "%{wks.location}/obj/%{cfg.buildcfg}/%{prj.name}-%{cfg.platform}-%{cfg.architecture}"

    files {
        "src/glad.c",
        "include/glad/glad.h",
        "include/KHR/khrplatform.h"
    }

    includedirs {
        "include/"
    }

    filter "system:Windows"
        systemversion "latest"