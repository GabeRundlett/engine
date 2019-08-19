project "testing"
	kind "ConsoleApp"
	language "C++"
	targetdir("%{wks.location}/build/bin/" .. outputdir .. "/%{prj.name}")
	objdir("%{wks.location}/build/bin/intermediates/" .. outputdir .. "/%{prj.name}")
	files { "src/**.hpp", "src/**.cpp" }
	includedirs { "%{include_dir.coel}", "%{include_dir.math}" }
	links { "coel", "math" }
	warnings "Extra"
	filter "configurations:Debug"
		defines "_CONFIG_DEBUG"
		optimize "Off"
		symbols "On"
	filter "configurations:DebugOptimized"
		defines "_CONFIG_DEBUG_OPTIMIZED"
		optimize "Off"
		symbols "Off"
	filter "configurations:Release"
		defines "_CONFIG_RELEASE"
		optimize "On"
		symbols "Off"
	filter "system:windows"
		systemversion "latest"
		defines "_CONFIG_PLATFORM_WINDOWS"
	filter "system:linux"
		defines "_CONFIG_PLATFORM_LINUX"
	filter "system:macosx"
		defines "_CONFIG_PLATFORM_MACOS"
