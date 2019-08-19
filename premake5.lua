workspace "engine"
	architecture "x64"
	configurations { "Debug", "DebugOptimized", "Release" }
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
include_dir = {}
include_dir["coel"] = "%{wks.location}/coel/src"
include_dir["glad"] = "%{wks.location}/glad/include"
include_dir["glfw"] = "%{wks.location}/glfw/include"
include_dir["stb"] = "%{wks.location}/stb/src"
include_dir["math"] = "%{wks.location}/math/src"

startproject "testing"

include "coel"
include "glad"
include "glfw"
include "stb"
include "math"
include "testing"

flags { "MultiProcessorCompile" }
filter "configurations:DebugOptimized"
	flags { "LinkTimeOptimization" }
filter "configurations:Release"
	flags { "LinkTimeOptimization" }
	