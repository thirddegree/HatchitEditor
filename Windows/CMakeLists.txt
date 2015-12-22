cmake_minimum_required (VERSION 3.1)

set (CMAKE_PREFIX_PATH "C:\\Qt\\5.5\\msvc2013_64\\")
cmake_policy(SET CMP0020 NEW)
set(CMAKE_AUTOMOC ON)

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

#Find QtWidgets library
find_package(Qt5Widgets)

include_directories("../include/"
                    "../Hatchit/HatchitCore/include/"
                    "../Hatchit/ThirdParty/inih/")

file(GLOB HT_EDITOR_INC ../include/*.h)
file(GLOB HT_EDITOR_SRC ../source/*.cpp)
file(GLOB HT_EDITOR_MOC /_build/${PLATFORM_TOOLSET}/moc/*.cpp)

add_definitions(-D_UNICODE)

source_group("Moc\\" FILES ${HT_EDITOR_MOC})

add_executable(HatchitEditor ${HT_EDITOR_INC} ${HT_EDITOR_SRC} ${HT_EDITOR_MOC})


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
                  
#Use the widgets module from Qt5.
target_link_libraries(HatchitEditor Qt5::Widgets HatchitCore)