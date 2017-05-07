cmake_minimum_required(VERSION 3.5)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/Hatchit/cmake")

project(HatchitEditor)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Compiler flag
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Version Info
set(HatchitEditor_VERSION_MAJOR 0)
set(HatchitEditor_VERSION_MINOR 0)
set(HatchitEditor_VERSION_BUILD 1)
set(HatchitEditor_TITLE "HatchitEditor")

configure_file(
    "${CMAKE_SOURCE_DIR}/include/editor/ht_editor_version.h.in"
    "${CMAKE_SOURCE_DIR}/include/editor/ht_editor_version.h"
)

if(WIN32)
    add_subdirectory(Hatchit/)
    
    set (CMAKE_PREFIX_PATH "C:\\Qt\\5.9\\msvc2015_64")
    
    find_package(Qt5 COMPONENTS Core Gui Widgets WebEngine WebEngineWidgets REQUIRED)

    include_directories("include"
                        "include/tools/HStringHasher"
                        "Hatchit/HatchitCore/include"
                        "Hatchit/HatchitCore/include/windows"
                        "Hatchit/HatchitCore/source/inline"
                        "Hatchit/HatchitGraphics/include"
                        "Hatchit/HatchitGraphics/include/vulkan"
                        "Hatchit/HatchitGame/include"
                        SYSTEM
                        "Hatchit/ThirdParty/inih/"
                        "Hatchit/ThirdParty/cppformat/cppformat"
                        "Hatchit/ThirdParty/json/src/"
                        "Hatchit/ThirdParty/stb")

    link_directories("Hatchit/ThirdParty/lib/glfw/lib/$(Configuration)")

    file(GLOB HT_EDITOR_INC include/*.h)
    file(GLOB HT_EDITOR_SRC source/*.cpp)
    file(GLOB HT_EDITOR_QRC source/HatchitEditor.qrc)

    file(GLOB HT_STRINGHASHER_INC include/tools/HStringHasher/*.h)
    file(GLOB HT_STRINGHASHER_SRC source/tools/HStringHasher/*.cpp)

    add_executable(HEditor WIN32 ${HT_EDITOR_INC} ${HT_EDITOR_SRC} ${HT_EDITOR_QRC})
    add_executable(HStringHasher WIN32 ${HT_STRINGHASHER_INC} ${HT_STRINGHASHER_SRC})

    add_custom_command(TARGET HEditor POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${PROJECT_SOURCE_DIR}/stylesheets/HatchitEditor.qss $<TARGET_FILE_DIR:HEditor>)
    add_custom_command(TARGET HEditor POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${PROJECT_SOURCE_DIR}/LICENSE.GPLv3 $<TARGET_FILE_DIR:HEditor>)

    target_link_libraries(HStringHasher Qt5::Core Qt5::WinMain Qt5::Widgets Qt5::Gui Qt5::WebEngine Qt5::WebEngineWidgets HatchitCore)
    target_link_libraries(HEditor Qt5::Core Qt5::WinMain Qt5::Widgets Qt5::Gui Qt5::WebEngine Qt5::WebEngineWidgets HatchitCore HatchitGraphics HatchitGame)

    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")

    set_target_properties(HEditor HStringHasher
	                    PROPERTIES
	                    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
    set_target_properties(HStringHasher PROPERTIES FOLDER Tools)

elseif(UNIX)
    add_subdirectory(Hatchit/)

    set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH} ~/Qt/5.8/gcc_64/")


    find_package(Qt5 COMPONENTS Core Gui Widgets WebEngine WebEngineWidgets REQUIRED)
    find_package(PythonLibs REQUIRED)

    include_directories("include"
                        "include/editor"
                        "include/python"
                        "include/tools/HStringHasher"
                        "Hatchit/HatchitCore/include"
                        "Hatchit/HatchitCore/include/linux"
                        "Hatchit/HatchitCore/source/inline"
                        "Hatchit/HatchitGraphics/include"
                        "Hatchit/HatchitGraphics/include/vulkan"
                        "Hatchit/HatchitGame/include"
                        SYSTEM
                        "Hatchit/ThirdParty/inih/"
                        "Hatchit/ThirdParty/cppformat/cppformat"
                        "Hatchit/ThirdParty/json/src/"
                        "Hatchit/ThirdParty/stb"
                        "Hatchit/ThirdParty/pybind11/include"
                        ${PYTHON_INCLUDE_DIR})

    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")

    add_subdirectory("${CMAKE_SOURCE_DIR}/Hatchit/ThirdParty/pybind11")
    add_subdirectory("${CMAKE_SOURCE_DIR}/cmake/python")

    file(GLOB HT_EDITOR_INC include/*.h include/editor/*.h)
    file(GLOB HT_EDITOR_SRC source/*.cpp source/editor/*.cpp)
    file(GLOB HT_EDITOR_QRC source/editor/HatchitEditor.qrc)

    file(GLOB HT_STRINGHASHER_INC include/tools/HStringHasher/*.h)
    file(GLOB HT_STRINGHASHER_SRC source/tools/HStringHasher/*.cpp)

    add_executable(HEditor ${HT_EDITOR_INC} ${HT_EDITOR_SRC} ${HT_EDITOR_QRC})
    add_executable(HStringHasher ${HT_STRINGHASHER_INC} ${HT_STRINGHASHER_SRC})


    add_custom_command(TARGET HEditor HStringHasher POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${PROJECT_SOURCE_DIR}/stylesheets/HatchitEditor.qss $<TARGET_FILE_DIR:HEditor>)
    add_custom_command(TARGET HEditor HStringHasher POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${PROJECT_SOURCE_DIR}/LICENSE.GPLv3 $<TARGET_FILE_DIR:HEditor>)

    target_link_libraries(HEditor ${PYTHON_LIBRARY} hpy Qt5::Core Qt5::Widgets Qt5::Gui Qt5::WebEngine Qt5::WebEngineWidgets HatchitCore HatchitGraphics HatchitGame)
    target_link_libraries(HStringHasher Qt5::Core Qt5::Widgets Qt5::Gui Qt5::WebEngine Qt5::WebEngineWidgets HatchitCore pthread)
 
        


    set_target_properties(HEditor HStringHasher
	                    PROPERTIES
	                    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

    install (TARGETS HEditor HStringHasher DESTINATION bin)
    install (DIRECTORY ${CMAKE_SOURCE_DIR}/icons DESTINATION bin)
    install (FILES ${CMAKE_SOURCE_DIR}/stylesheets/HatchitEditor.qss DESTINATION bin)
	
endif()
