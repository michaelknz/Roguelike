workspace "Roguelike"
	configurations { "Debug", "Release" }
	startproject "Game"

project "Game"
	kind "ConsoleApp"
	location "%{prj.name}"
	language "C++"
	architecture "x64"
	targetdir "bin/%{prj.name}/%{cfg.buildcfg}"
	libdirs "%{wks.location}/libs"
	links {"SDL2.lib","SDL2main.lib","glew32.lib","SOIL.lib"}
	includedirs{ "%{wks.location}/include/sdl", 
	"%{wks.location}/include/glew", "%{wks.location}/include/soil"}
	postbuildcommands{
		("{COPY} %{wks.location}/dlls/ %{wks.location}bin/%{prj.name}/%{cfg.buildcfg}"),
		("{COPY} %{wks.location}%{prj.name}/shaders/ %{wks.location}bin/%{prj.name}/%{cfg.buildcfg}/shaders")
	}
	vpaths {
    ["Headers"] = { "**.h", "**.hpp" },
    ["Sources"] = {"**.c", "**.cpp"},
	["Shaders"] = {"**.vs", "**.fs"},
    }

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/shaders/**.vs",
		"%{prj.name}/shaders/**.fs"}

	filter { "configurations:Debug" }
		symbols "On"

	filter { "configurations:Release" }
		optimize "On"

	filter { "system:windows" }
		links { "OpenGL32" }

	filter { "system:not windows" }
		links { "GL" }