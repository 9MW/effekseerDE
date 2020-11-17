project "EffekseerRendererDE"
kind "StaticLib"
language "C++"
cppdialect "C++17"
targetdir("%{IncludeDir.outlibdir}")
objdir("bin-int/" .. outputdir .. "/%{prj.name}")
--include "%{IncludeDir.rootdir}/pj2/3rdparty/DiligentTools/TextureLoader"
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

files {"./**.cpp",
"./**.h"}

filter "system:windows"
systemversion "latest"
defines {
    "PLATFORM_WIN32"
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
buildoptions "/MD"
