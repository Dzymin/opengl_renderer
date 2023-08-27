project "stb"
    kind "StaticLib"
    language "C++"

    targetdir "%{wks.location}/bin/%{cfg.buildcfg}/%{prj.name}-%{cfg.platform}-%{cfg.architecture}"
    objdir "%{wks.location}/obj/%{cfg.buildcfg}/%{prj.name}-%{cfg.platform}-%{cfg.architecture}"

    files {
        "include/stb/*.h",
        "src/*.cpp"
    }

    includedirs {
        "include/stb"
    }

    defines {
        "_CRT_SECURE_NO_WARNINGS"
    }