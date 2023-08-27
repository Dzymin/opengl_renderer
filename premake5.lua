workspace "OpenglRenderer"
    startproject "App"
    architecture "x64"
    configurations { "Debug", "Release" }
    platforms { "Windows" }

group "Dependencies"
include "Dependencies/GLFW"
include "Dependencies/glad"
include "Dependencies/stb"

group ""
include "App"