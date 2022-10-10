@echo off
:: Fix me! Clean CL path, more generic

call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"

SET files=src/main.cpp src/render/VulkanRenderer.cpp


SET config= /out:Bin\main.exe /pdb:Bin\vc140.pdb 
SET includes=/Isrc /I%VULKAN_SDK%/Include /Iexternals /Iexternals/GLFW/include
SET links=/link /LIBPATH:%VULKAN_SDK%/Lib vulkan-1.lib /LIBPATH:externals/GLFW/lib-vc2022 glfw3dll.lib
SET defines=/D DEBUG
SET flags=/Zi /EHsc /std:c++17

echo "Building main..."


cl /Fo.\Bin\ %flags% %includes% %defines% %files% %links% %config%
DEL vc140.pdb
