cmake_minimum_required (VERSION 3.1)

set (CMAKE_PREFIX_PATH "C:\\Qt\\5.5\\msvc2013_64\\")
cmake_policy(SET CMP0020 NEW)

set(CMAKE_INCLUDE_CURRENT_DIR ON )
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

project(HatchitEditor)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

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

add_subdirectory("${PROJECT_SOURCE_DIR}/../Hatchit/Windows/HatchitCore" "${CMAKE_CURRENT_BINARY_DIR}/HatchitCore")
add_subdirectory("${PROJECT_SOURCE_DIR}/../Hatchit/Windows/HatchitResource" "${CMAKE_CURRENT_BINARY_DIR}/HatchitResource")
add_subdirectory("${PROJECT_SOURCE_DIR}/../Hatchit/Windows/HatchitGame" "${CMAKE_CURRENT_BINARY_DIR}/HatchitGame")

#Find QtWidgets library
find_package(Qt5 COMPONENTS Core Gui Multimedia Network OpenGL Script Svg WebKit WebKitWidgets Xml UiTools)

include_directories("../include/"
                    "../Hatchit/HatchitCore/include/"
                    "../Hatchit/HatchitResource/include/"
                    "../Hatchit/HatchitGame/include/"
                    "../Hatchit/ThirdParty/assimp/include"
                    "../Hatchit/ThirdParty/SDL2/include"
                    "../Hatchit/ThirdParty/inih/")
                    
link_directories("${PROJECT_SOURCE_DIR}/../Hatchit/Windows/_build/dependencies/assimp/lib/Release/"
                 "${PROJECT_SOURCE_DIR}/../Hatchit/Windows/_build/dependencies/SDL2/lib/Release/")

file(GLOB HT_EDITOR_INC ../include/*.h)
file(GLOB HT_EDITOR_SRC ../source/*.cpp)
file(GLOB HT_EDITOR_MOC /_build/${PLATFORM_TOOLSET}/moc/*.cpp)

add_definitions(-D_UNICODE)

source_group("Moc\\" FILES ${HT_EDITOR_MOC})

add_executable(HatchitEditor ${HT_EDITOR_INC} ${HT_EDITOR_SRC} ${HT_EDITOR_MOC} ${PROJECT_SOURCE_DIR}/HatchitEditor.qrc ../stylesheets/HatchitEditor.qss)


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
                  $<TARGET_FILE_DIR:HatchitGame>/HatchitGame.dll $<TARGET_FILE_DIR:HatchitEditor>)
add_custom_command(TARGET HatchitEditor POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                  "${PROJECT_SOURCE_DIR}/../Hatchit/Windows/_build/dependencies/assimp/bin/Release/assimp.dll" $<TARGET_FILE_DIR:HatchitEditor>)
add_custom_command(TARGET HatchitEditor POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                  "${PROJECT_SOURCE_DIR}/../Hatchit/Windows/_build/dependencies/SDL2/bin/Release/SDL2.dll" $<TARGET_FILE_DIR:HatchitEditor>)
add_custom_command(TARGET HatchitEditor POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                  ${CMAKE_SOURCE_DIR}/../LICENSE.GPLv3 $<TARGET_FILE_DIR:HatchitEditor>)
                                 
#Use the widgets module from Qt5.
target_link_libraries(HatchitEditor Qt5::Core Qt5::Gui Qt5::Network Qt5::OpenGL 
  Qt5::Script Qt5::Svg Qt5::WebKit Qt5::WebKitWidgets Qt5::Xml Qt5::UiTools HatchitCore HatchitResource HatchitGame assimp SDL2)