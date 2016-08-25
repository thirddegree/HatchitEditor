cmake_minimum_required(VERSION 3.5)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/Hatchit/cmake")

project(HatchitEditor)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Compiler flag
include (CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++1y" COMPILER_SUPPORTS_CXX14)
if(COMPILER_SUPPORTS_CXX14)
    if(CMAKE_BUILD_TYPE MATCHES DEBUG)
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall -g -msse")
    else()
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall -msse")
    endif()
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

if(WIN32)
    find_package(Qt5Widgets)

elseif(UNIX)
    #add_subdirectory(Hatchit/)

    set(CMAKE_PREFIX_PATH "~/Qt/5.7/gcc_64/")

    find_package(Qt5 COMPONENTS Core Gui Widgets)
    find_package(SDL2 REQUIRED)

    include_directories("include"
                        "Hatchit/HatchitCore/include"
                        "Hatchit/HatchitCore/include/linux"
                        "Hatchit/HatchitCore/source/inline"
                        "Hatchit/HatchitGraphics/include"
                        "Hatchit/HatchitGraphics/include/vulkan"
                        "Hatchit/HatchitGame/include"
                        "Hatchit/HatchitGame/include/sdl"
                        SYSTEM
                        "Hatchit/ThirdParty/inih/"
                        "Hatchit/ThirdParty/cppformat/cppformat"
                        "Hatchit/ThirdParty/json/src/"
                        "Hatchit/ThirdParty/stb")

    file(GLOB HT_EDITOR_INC include/*.h)
    file(GLOB HT_EDITOR_SRC source/*.cpp)

    add_executable(HEditor ${HT_EDITOR_SRC})

    target_link_libraries(HEditor Qt5::Core Qt5::Widgets Qt5::Gui) #HatchitCore HatchitGraphics HatchitGame ${SDL2_LIBRARY} Qt5::Core Qt5::Widgets Qt5::Gui)

endif()