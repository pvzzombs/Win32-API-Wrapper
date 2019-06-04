workspace "Win-32-Api-Wrapper"
    configurations
    {
        "Debug", 
        "Dist",
        "Release"
    }

out = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "WIN32Wrapper"
    location "WIN32Wrapper"
    kind "ConsoleApp"
    language "C++"
    targetdir ("bin/" .. out .. "/%{prj.name}")
    objdir ("bin-int/" .. out .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**"
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        defines
        {
            "WR_WIN"
        }

    filter "configurations:Debug"
        defines { "WR_DEBUG" }
        symbols "On"

    filter "configurations:Dist"
        defines { "WR_NDEBUG" }
        optimize "On"

    filter "configurations:Release"
        defines { "WR_NDEBUG" }
        optimize "On"