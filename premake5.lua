workspace "ImGuiApp"
    architecture "x64"
    startproject "SimpleApp"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "ImGuiApp"
    location "ImGuiApp"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/imgui/**.h",
        "%{prj.name}/vendor/imgui/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/vendor/GLEW/include",
        "%{prj.name}/vendor/GLFW/include",
        "%{prj.name}/vendor/imgui"
    } 

    libdirs
    {
        "%{prj.name}/vendor/GLFW",
        "%{prj.name}/vendor/GLEW"
    }

    defines{
        "GLEW_STATIC"
    }

    links{
        "glew32s.lib",
        "glfw3.lib",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "Off"
        systemversion "latest"
        defines
        {
            "CFG_PLATFORM_WINDOWS",
        }
    
    filter "configurations:Debug"
        defines "CFG_DEBUG"
        symbols "On"
    
    filter "configurations:Release"
        defines "CFG_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "CFG_DIST"
        optimize "On"