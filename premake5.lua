function os.winSdkVersion()
  local reg_arch = iif( os.is64bit(), "\\Wow6432Node\\", "\\" )
  local sdk_version = os.getWindowsRegistry( "HKLM:SOFTWARE" .. reg_arch .."Microsoft\\Microsoft SDKs\\Windows\\v10.0\\ProductVersion" )
  if sdk_version ~= nil then return sdk_version end
end

solution "gm_execute"
  language     "C++"
  location     "project"
  targetdir    "bin"
  architecture "x86"
  
  -- Statically link the C-Runtime to reduce dependencies needed to run our
  --   module.  We may want to get rid of this in the future as this can cause
  --   security issues.
  flags "StaticRuntime"
  
  configurations { "Release" }
  configuration "Release"
    flags "symbols"  -- Generate debugging information
    optimize "On"    	  -- Optimize the build output for size and speed
  
  project "reproc"
    kind "StaticLib"
    files {
      "vendor/reproc/reproc/src/common/*.c",
      "vendor/reproc/reproc/src/common/*.h",
    }

    defines {
      "THREADS_PREFER_PTHREAD_FLAG",
      "HAVE_ATTRIBUTE_LIST",
    }
    includedirs { "vendor/reproc/reproc/include" }

    filter "system:Unix"
      files { "vendor/reproc/reproc/src/posix/*.c" }
    filter "system:Windows"
      files { "vendor/reproc/reproc/src/windows/*.c" }
      systemversion(os.winSdkVersion() .. ".0")

  project "reproc++"
    kind "StaticLib"
    files {
      "vendor/reproc/reproc++/src/*.cpp",
    }
    links { "reproc" }

    includedirs {
      "vendor/reproc/reproc/include",
      "vendor/reproc/reproc++/include",
    }

    filter "system:Windows"
      systemversion(os.winSdkVersion() .. ".0")

  project "execute"
    kind "SharedLib"
    include "vendor/gloo"
  
    files {
      "src/**.hpp",
      "src/**.cpp",
    }

    includedirs {
      "vendor/tiny-process-library"
    }

    filter "system:Windows"
      systemversion(os.winSdkVersion() .. ".0")
