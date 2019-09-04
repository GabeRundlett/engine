include "dep/glad"
include "dep/glfw"
include "dep/stb"

project "engine"
	kind "StaticLib"
	language "C++"
	targetdir("%{wks.location}/build/bin/" .. outputdir .. "/%{prj.name}")
	objdir("%{wks.location}/build/bin/intermediates/" .. outputdir .. "/%{prj.name}")
	files { "src/**.hpp", "src/**.cpp" }
	includedirs { 
        "%{prj.location}/dep/glad/include", 
        "%{prj.location}/dep/glfw/include", 
        "%{prj.location}/dep/stb/src", 
    }
	defines { "GLFW_INCLUDE_NONE" }
	links { "glad", "glfw", "stb" }
	warnings "Extra"
	filter "configurations:Debug"
		defines "_CONFIG_DEBUG"
		optimize "Off"
		symbols "On"
	filter "configurations:DebugOptimized"
		defines "_CONFIG_DEBUG_OPTIMIZED"
		optimize "Full"
		symbols "on"
	filter "configurations:Release"
		defines "_CONFIG_RELEASE"
		optimize "Full"
		symbols "Off"
	filter "system:windows"
		systemversion "latest"
		defines "_CONFIG_PLATFORM_WINDOWS"
	filter "system:linux"
		defines "_CONFIG_PLATFORM_LINUX"
        links { "X11", "dl", "pthread" }
	filter "system:macosx"
		defines "_CONFIG_PLATFORM_MACOS"
