workspace "OpenCircuit"
    configurations {"Debug", "Release"}


project "OpenCircuit"
    kind "ConsoleApp"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"
    architecture "x64"

    files {"%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp"}

    includedirs{
        "%{prj.name}/depen/SFML/include"
    }

    libdirs{
        "%{prj.name}/depen/SFML/lib",
    }

    defines "SFML_STATIC"

    links{
            "opengl32.lib",
            "freetype.lib",
            "winmm.lib",
            "gdi32.lib",
            "openal32.lib",
            "flac.lib",
            "vorbisenc.lib",
            "vorbisfile.lib",
            "vorbis.lib",
            "ogg.lib"
    }

    filter "configurations:Debug"
        links{
            "sfml-graphics-s-d.lib",
            "sfml-window-s-d.lib",
            "sfml-system-s-d.lib",
            "sfml-network-s-d.lib"
        }
        symbols "On"
        
    filter "configurations:Release"
        links{
            "sfml-graphics-s.lib",
            "sfml-window-s.lib",
            "sfml-system-s.lib",
            "sfml-network-s.lib"
        }
        optimize "On"

    filter {}

