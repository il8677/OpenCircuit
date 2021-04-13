workspace "OpenCircuit"
    configurations {"Debug", "Release"}


project "OpenCircuit"
    kind "WindowedApp"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"

    files {"%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp"}

    includedirs{
        "%{prj.name}/depen/SFML/include"
    }

    defines "SFML_STATIC"

    links{
            "opengl32.lib",
            "freetype.lib",
            "winmm.lib",
            "gdi32.lib"
    }

    filter "configurations:Debug"
        links{
            "sfml-window-s-d.lib",
            "sfml-system-s-d.lib"
        }
        symbols "On"
        
    filter "configurations:Release"
        links{
            "sfml-window-s.lib",
            "sfml-system-s.lib"
        }
        optimize "On"
