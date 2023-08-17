

workspace "bqlang"
architecture "x64"
startproject "test"

configurations
{
    "Debug",
    "Release"
}


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}


project "interpreter"
	location "interpreter"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")


	files
	{
		"%{prj.name}/include/**.hpp",
		"%{prj.name}/source/**.cpp",
    }
    includedirs
	{
        "%{prj.name}/include",
	}

	filter "system:windows"
		systemversion "latest"
		defines{ "PLATFORM_WINDOWS" }


	
		
	filter "configurations:Debug"
		defines "DEBUG"
		runtime "Debug"


	filter "configurations:Release"
		defines "NDEBUG"
		runtime "Release"
		optimize "on"



		
project "test"
	location "test"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")
	filter "system:windows"
		systemversion "latest"
		defines{ "PLATFORM_WINDOWS" }
	filter "configurations:*"
		libdirs { "test/deps/boost/libs" }	
	links
	{
		"interpreter"
	}
	files
	{
		"%{prj.name}/source/**.cpp"
	}
	includedirs
	{
		"interpreter/include",
		"test/deps/boost",
	}
	
	

	filter "configurations:Debug"
		defines "DEBUG"
		runtime "Debug"
		symbols "on"
	filter "configurations:Release"
		defines "NDEBUG"
		runtime "Release"
		optimize "on"



project "ui"
	location "ui"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")
	filter "system:windows"
		systemversion "latest"
		defines{ "PLATFORM_WINDOWS" }

	links
	{
		"interpreter"
	}
	files
	{
		"%{prj.name}/include/**.hpp",
		"%{prj.name}/source/**.cpp",
	}
	includedirs
	{
		"interpreter/include",
	}

	filter "configurations:Debug"
		defines "DEBUG"
		runtime "Debug"
		symbols "on"
	filter "configurations:Release"
		defines "NDEBUG"
		runtime "Release"
		optimize "on"