workspace "effekseerDE"
architecture "x86_64"
startproject "examplede"

configurations {
    "Debug",
    "Release"
}

flags {
    "MultiProcessorCompile"
}
project "EffekseerRendererDE"
kind "StaticLib"
language "C++"
cppdialect "C++17"
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

targetdir("lib/" .. outputdir .. "/%{prj.name}")
objdir("lib-int/" .. outputdir .. "/%{prj.name}")
-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["DiligentCore"] = "3rdparty/DiligentCore-Windows-x64-%{cfg.buildcfg}/include"
IncludeDir["Effekseer"] = "3rdparty/Effekseer/Effekseer"
includedirs{
    --"%{IncludeDir.trdparty}",
    "%{IncludeDir.DiligentCore}",
    "%{IncludeDir.rootdir}/3rdparty/DiligentTools/TextureLoader/interface",
    "%{IncludeDir.DiligentCore}/Common/interface",
    "%{IncludeDir.DiligentCore}/Platforms/Win32/interface",
    "%{IncludeDir.DiligentCore}/Platforms/Basic/interface",
    "%{IncludeDir.DiligentCore}/Primitives/interface",
    "%{IncludeDir.DiligentCore}/Platforms/interface",
    "%{IncludeDir.DiligentCore}/Graphics/GraphicsEngine/interface",
    "%{IncludeDir.DiligentCore}/Graphics/GraphicsAccessories/interface",
    "%{IncludeDir.DiligentCore}/Graphics/GraphicsTools/interface",
    "%{IncludeDir.Effekseer}"
}

files {
    "src/*.h",
    "src/EffekseerRendererCommon/*.cpp",
    "src/EffekseerRendererCommon/*.h",
    "src/*.cpp",
}
filter "configurations:Debug"
defines "DEBUG"
runtime "Debug"
symbols "on"
buildoptions{"/MDd"} 

filter "configurations:Release"
defines "RELEASE"
runtime "Release"
optimize "on"
buildoptions {"/MDd"} 

filter "system:windows"
systemversion "latest"
defines {
    "PLATFORM_WIN32"
}
filter "system:windows"
systemversion "latest"
defines {
    "PLATFORM_WIN32"
}


project "examplede"
location "Example"
kind "WindowedApp"
language "C++"
cppdialect "C++17"
staticruntime "on"

configurations {
    "Debug",
    "Release"
}


flags {
    "MultiProcessorCompile"
}
targetdir("bin/" .. outputdir .. "/%{prj.name}")
objdir("bin-int/" .. outputdir .. "/%{prj.name}")
-- need switch use to create on vs precompile head setting

--pchheader "PCH.h"
--pchsource "pj2/src/PCH.cpp"
entrypoint "WinMainCRTStartup"
-- pchsource "pj2stdafx.cpp"


libdirs {
    "lib/%{outputdir}/**",
    "lib/%{outputdir}",
    "3rdparty/DiligentCore-Windows-x64-%{cfg.buildcfg}/lib/%{cfg.buildcfg}"
    -- "G:/CPPLib/DiligentCore-Windows-x64-%{cfg.buildcfg}/lib/%{cfg.buildcfg}"
}

includedirs{
    --"%{IncludeDir.trdparty}",
    "%{IncludeDir.DiligentCore}",
    "%{IncludeDir.rootdir}/3rdparty/DiligentTools/TextureLoader/interface",
    "%{IncludeDir.DiligentCore}/Common/interface",
    "%{IncludeDir.DiligentCore}/Platforms/Win32/interface",
    "%{IncludeDir.DiligentCore}/Platforms/Basic/interface",
    "%{IncludeDir.DiligentCore}/Primitives/interface",
    "%{IncludeDir.DiligentCore}/Platforms/interface",
    "%{IncludeDir.DiligentCore}/Graphics/GraphicsEngine/interface",
    "%{IncludeDir.DiligentCore}/Graphics/GraphicsAccessories/interface",
    "%{IncludeDir.DiligentCore}/Graphics/GraphicsTools/interface",
    "%{IncludeDir.Effekseer}",
    "src"
}
group "Dependencies"
include "."
files {
    "Example/*.cpp",
"Example/*.h",
"Example/Win32/*.cpp",
}

configurations {
    "Debug",
    "Release"
}
links {
    "Effekseerd.lib",
    "EffekseerRendererDE.lib","DiligentCore.lib"
}
filter "configurations:Debug"
defines "DEBUG"
runtime "Debug"
symbols "on"
buildoptions{"/MDd"} 
links {
    "GraphicsEngineVk_64d.lib"
}

filter "configurations:Release"
defines "RELEASE"
runtime "Release"
optimize "on"
    buildoptions "/MD"

    links {
        "GraphicsEngineVk_64r.lib",
    }
filter "system:windows"
systemversion "latest"
defines {
    "PLATFORM_WIN32"
}