cmake_minimum_required (VERSION 3.1)

set (CMAKE_PREFIX_PATH "C:\\Qt\\Qt5.6.0\\5.6\\msvc2015_64")
cmake_policy(SET CMP0020 NEW)

set(CMAKE_INCLUDE_CURRENT_DIR ON )
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

project(HatchitEditor)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#If we've asked for Vulkan support
if(DEFINED ENV{VK_SDK_PATH} AND VK_SUPPORT)
set(VK_INCLUDES "$ENV{VK_SDK_PATH}/Include")
set(VK_LIB_DIR "$ENV{VK_SDK_PATH}/Source/lib")
set(VK_LIBS debug vulkan-1 optimized vulkan-1)
set(HT_VK_INCLUDES "${PROJECT_SOURCE_DIR}../HatchitGraphics/include/vulkan")
else()
set(VK_INCLUDES "")
set(VK_LIB_DIR "")
set(VK_LIBS "")
set(HT_VK_INCLUDES "")
endif()

# If we've asked for OpenGL support
if(GL_SUPPORT)
set(GL_LIBS debug opengl32 glu32 optimized opengl32 glu32)
set(GLEW_LIBS debug glew32d optimized glew32)
set(GLEW_INCLUDES "${PROJECT_SOURCE_DIR}../ThirdParty/glew/include")
set(GLEW_LIB_DIR "${PROJECT_SOURCE_DIR}/_build/dependencies/glew/lib/$(Configuration)/")
set(HT_GL_INCLUDES "${PROJECT_SOURCE_DIR}../HatchitGraphics/include/opengl")
else()
set(GL_LIBS "")
set(GLEW_LIBS "")
set(GLEW_INCLUDES "")
set(HT_GL_INCLUDES "")
endif()

# If we've asked for DirectX 12 Support
if(DX12_SUPPORT)
set(DX12_LIBS debug d3d12 d3dcompiler dxgi optimized d3d12 d3dcompiler dxgi)
set(HT_DX12_INCLUDES "${PROJECT_SOURCE_DIR}../HatchitGraphics/include/directx/dx12")
else()
set(DX12_LIBS "")
set(HT_DX12_INCLUDES "")
endif()

# If we've asked for DirectX 11 Support
if(DX11_SUPPORT)
set(DX11_LIBS debug d3d11 d3dcompiler optimized d3d11 d3dcompiler)
set(HT_DX11_INCLUDES "${PROJECT_SOURCE_DIR}../HatchitGraphics/include/directx/dx11")
else()
set(DX11_LIBS "")
set(HT_DX11_INCLUDES "")
endif()

# If we've asked for either DX11 or DX12 Support
if(DX11_SUPPORT OR DX12_SUPPORT)
set(HT_DX_INCLUDES "${PROJECT_SOURCE_DIR}../HatchitGraphics/include/directx")
else()
set(HT_DX_INCLUDES "")
endif()

set(SDL_LIBS "")
# If we've asked to build a Universal Windows App
if(UNIVERSAL_APP)
    set(HT_WINDOW_INCLUDE ${PROJECT_SOURCE_DIR}/../HatchitGame/include/uwa)
    file(GLOB HT_WINDOW_HEADERS ${PROJECT_SOURCE_DIR}/../HatchitGame/include/uwa/*.h)
    file(GLOB HT_WINDOW_SOURCE ${PROJECT_SOURCE_DIR}/../HatchitGame/source/uwa/*.cpp)
    source_group("Header Files\\uwa" FILES ${HT_WINDOW_HEADERS})
    source_group("Source Files\\uwa" FILES ${HT_WINDOW_SOURCE})
elseif(DESKTOP_APP)
    set(HT_WINDOW_INCLUDE ${PROJECT_SOURCE_DIR}/../ThirdParty/SDL2/include ${PROJECT_SOURCE_DIR}/../HatchitGame/include/sdl)
    file(GLOB HT_WINDOW_HEADERS ${PROJECT_SOURCE_DIR}/../HatchitGame/include/sdl/*.h)
    file(GLOB HT_WINDOW_SOURCE ${PROJECT_SOURCE_DIR}/../HatchitGame/source/sdl/*.cpp)
    source_group("Header Files\\sdl" FILES ${HT_WINDOW_HEADERS})
    source_group("Source Files\\sdl" FILES ${HT_WINDOW_SOURCE})
    set(SDL_LIBS debug SDL2d optimized SDL2)
endif()



# Version info
set (HatchitEditor_VERSION_MAJOR 0)
set (HatchitEditor_VERSION_MINOR 1)
set (HatchitEditor_VERSION_BUILD 1)


#configure header file to pass
#CMake settings to source code
configure_file (
    "${PROJECT_SOURCE_DIR}/../include/ht_editor_version.h.in"
    "${PROJECT_SOURCE_DIR}/../include/ht_editor_version.h"
)

#add_subdirectory("${PROJECT_SOURCE_DIR}/../Hatchit/Windows/HatchitCore" "${CMAKE_CURRENT_BINARY_DIR}/HatchitCore")
#add_subdirectory("${PROJECT_SOURCE_DIR}/../Hatchit/Windows/HatchitResource" "${CMAKE_CURRENT_BINARY_DIR}/HatchitResource")
#add_subdirectory("${PROJECT_SOURCE_DIR}/../Hatchit/Windows/HatchitGraphics" "${CMAKE_CURRENT_BINARY_DIR}/HatchitGraphics")
#add_subdirectory("${PROJECT_SOURCE_DIR}/../Hatchit/Windows/HatchitMath" "${CMAKE_CURRENT_BINARY_DIR}/HatchitMath")
#add_subdirectory("${PROJECT_SOURCE_DIR}/../Hatchit/Windows/HatchitGame" "${CMAKE_CURRENT_BINARY_DIR}/HatchitGame")
add_subdirectory("${PROJECT_SOURCE_DIR}/../Hatchit/Windows" "${CMAKE_CURRENT_BINARY_DIR}/Hatchit")
set_target_properties(HatchitCore HatchitResource HatchitMath HatchitGraphics HatchitGame HatchitNetwork HatchitClient HatchitServer HatchitTest PROPERTIES FOLDER Hatchit)



#Find QtWidgets library
find_package(Qt5 COMPONENTS Core Gui Multimedia Network OpenGL Script Svg Xml UiTools)

include_directories("../include/"
                    "../Hatchit/HatchitCore/include/"
                    "../Hatchit/HatchitResource/include/"
                    "../Hatchit/HatchitMath/include/"
                    "../Hatchit/HatchitGraphics/include/"
                    "../Hatchit/HatchitGraphics/include/opengl/"
                    "../Hatchit/HatchitGraphics/include/directx/"
                    "../Hatchit/HatchitGame/include/"
                    "../Hatchit/ThirdParty/assimp/include"
                    "../Hatchit/ThirdParty/SDL2/include"
                    "../Hatchit/ThirdParty/inih/")
                    
link_directories("${PROJECT_SOURCE_DIR}/../Hatchit/Windows/_build/dependencies/assimp/lib/$(Configuration)/"
                 "${PROJECT_SOURCE_DIR}/../Hatchit/Windows/_build/dependencies/glew/lib/$(Configuration)/"
                 "${PROJECT_SOURCE_DIR}/../Hatchit/Windows/_build/dependencies/SDL2/lib/$(Configuration)/"
                 "${PROJECT_SOURCE_DIR}/../Hatchit/Windows/_build/dependencies/bullet/lib/$(Configuration)/"
                 "${PROJECT_SOURCE_DIR}/../Hatchit/Windows/_build/dependencies/tinyxml2/lib/$(Configuration)/"
                 "${PROJECT_SOURCE_DIR}/../Hatchit/Windows/_build/dependencies/Python/lib/$(Configuration)/")

file(GLOB HT_EDITOR_INC ../include/*.h)
file(GLOB HT_EDITOR_SRC ../source/*.cpp)
file(GLOB HT_EDITOR_MOC /_build/${PLATFORM_TOOLSET}/moc/*.cpp)

add_definitions(-D_UNICODE)

source_group("Moc\\" FILES ${HT_EDITOR_MOC})

add_executable(HatchitEditor ${HT_EDITOR_INC} ${HT_EDITOR_SRC} ${HT_EDITOR_MOC} ${PROJECT_SOURCE_DIR}/../source/HatchitEditor.qrc ../stylesheets/HatchitEditor.qss)

set_target_properties(HatchitEditor
                      PROPERTIES
                      ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/_build/bin/"
                      LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/_build/bin/"
                      RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/_build/bin/")

add_custom_command(TARGET HatchitEditor POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                  ${Qt5Core_DIR}/../../../bin/Qt5Guid.dll $<TARGET_FILE_DIR:HatchitEditor>)
add_custom_command(TARGET HatchitEditor POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                  ${Qt5Core_DIR}/../../../bin/Qt5Cored.dll $<TARGET_FILE_DIR:HatchitEditor>)
add_custom_command(TARGET HatchitEditor POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                  ${Qt5Core_DIR}/../../../bin/Qt5Widgetsd.dll $<TARGET_FILE_DIR:HatchitEditor>)
add_custom_command(TARGET HatchitEditor POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                  ${Qt5Core_DIR}/../../../bin/libGLESv2d.dll $<TARGET_FILE_DIR:HatchitEditor>)
add_custom_command(TARGET HatchitEditor POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                  ${Qt5Core_DIR}/../../../bin/icuin54.dll $<TARGET_FILE_DIR:HatchitEditor>)
add_custom_command(TARGET HatchitEditor POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                  ${Qt5Core_DIR}/../../../bin/icuuc54.dll $<TARGET_FILE_DIR:HatchitEditor>)
add_custom_command(TARGET HatchitEditor POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                  ${Qt5Core_DIR}/../../../bin/icudt54.dll $<TARGET_FILE_DIR:HatchitEditor>)
add_custom_command(TARGET HatchitEditor POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                  ${CMAKE_SOURCE_DIR}/../stylesheets/HatchitEditor.qss $<TARGET_FILE_DIR:HatchitEditor>)
add_custom_command(TARGET HatchitEditor POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                  $<TARGET_FILE_DIR:HatchitCore>/HatchitCore.dll $<TARGET_FILE_DIR:HatchitEditor>)
add_custom_command(TARGET HatchitEditor POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                  $<TARGET_FILE_DIR:HatchitResource>/HatchitResource.dll $<TARGET_FILE_DIR:HatchitEditor>)
add_custom_command(TARGET HatchitEditor POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                  $<TARGET_FILE_DIR:HatchitMath>/HatchitMath.dll $<TARGET_FILE_DIR:HatchitEditor>)
add_custom_command(TARGET HatchitEditor POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                  $<TARGET_FILE_DIR:HatchitGraphics>/HatchitGraphics.dll $<TARGET_FILE_DIR:HatchitEditor>)                  
add_custom_command(TARGET HatchitEditor POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                  $<TARGET_FILE_DIR:HatchitGame>/HatchitGame.dll $<TARGET_FILE_DIR:HatchitEditor>)
add_custom_command(TARGET HatchitEditor POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                  ${CMAKE_SOURCE_DIR}/../LICENSE.GPLv3 $<TARGET_FILE_DIR:HatchitEditor>)
                                 
#Use the widgets module from Qt5.
set(ASSIMP_LIBS debug assimpd optimized assimp)

target_link_libraries(HatchitEditor Qt5::Core Qt5::Gui Qt5::Network Qt5::OpenGL 
  Qt5::Script Qt5::Svg Qt5::Xml Qt5::UiTools HatchitCore HatchitResource HatchitGame ${ASSIMP_LIBS} ${SDL_LIBS} ${DX11_LIBS} ${DX12_LIBS} ${GL_LIBS} ${GLEW_LIBS})