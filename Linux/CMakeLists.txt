cmake_minimum_required(VERSION 2.8.11)

project(HatchitEditor)

#Version info
set(HatchitEditor_VERSION_MAJOR 0)
set(HatchitEditor_VERSION_MINOR 1)
set(HatchitEditor_VERSION_BUILD 1)

#Compiler flag
include (CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
if(COMPILER_SUPPORTS_CXX11)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -w -g")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

#configure header file to pass
#CMake settings to source code
configure_file (
    "../include/ht_editor_version.h.in"
    "../../include/ht_editor_version.h"
)

add_subdirectory("${PROJECT_SOURCE_DIR}/../Hatchit/Linux" "${CMAKE_CURRENT_BINARY_DIR}/Hatchit/")

#Instruct CMake to run moc automatically when needed
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

#Find the QtWidgets library
find_package(Qt5 COMPONENTS Core Gui Multimedia Network OpenGL Script Svg WebKit WebKitWidgets Xml UiTools)

include_directories("../include/"
                    "../Hatchit/HatchitCore/include/"
                    "../Hatchit/HatchitResource/include"
                    "../Hatchit/HatchitMath/include"
                    "../Hatchit/HatchitGame/include"
                    "../Hatchit/ThirdParty/inih/")

file(GLOB HT_EDITOR_INC ../include/*.h)
file(GLOB HT_EDITOR_SRC ../source/*.cpp)

#Tell CMake to create the main HatchitEditor executable
add_executable(HatchitEditor ${HT_EDITOR_INC} ${HT_EDITOR_SRC} ../source/HatchitEditor.qrc)

add_custom_command(TARGET HatchitEditor POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                   ${PROJECT_SOURCE_DIR}/../stylesheets/HatchitEditor.qss $<TARGET_FILE_DIR:HatchitEditor>)
add_custom_command(TARGET HatchitEditor POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                   ${PROJECT_SOURCE_DIR}/../LICENSE.GPLv3 $<TARGET_FILE_DIR:HatchitEditor>)

#Use the widgets module from Qt5.
target_link_libraries(HatchitEditor Qt5::Core Qt5::Gui Qt5::Network Qt5::OpenGL
  Qt5::Script Qt5::Svg Qt5::WebKit Qt5::WebKitWidgets Qt5::Xml Qt5::UiTools HatchitCore HatchitResource HatchitMath HatchitGame )

#install

#install

install (TARGETS HatchitEditor DESTINATION bin)
install (DIRECTORY ${PROJECT_SOURCE_DIR}/../icons DESTINATION bin)
install (FILES ${PROJECT_SOURCE_DIR}/../stylesheets/HatchitEditor.qss DESTINATION bin)
