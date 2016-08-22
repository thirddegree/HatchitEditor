cmake_minimum_required(VERSION 3.5)

project(HatchitEditor)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

if(WIN32)
    find_package(Qt5Widgets)

elseif(UNIX)
    add_subdirectory(Hatchit/)

    set(CMAKE_PREFIX_PATH "~/Qt/5.7/gcc_64/")

    find_package(Qt5Widgets)

    include_directories("Hatchit/HatchitCore/include"
                        "Hatchit/HatchitCore/include/linux"
                        "Hatchit/HatchitCore/source/inline"
                        SYSTEM
                        "Hatchit/ThirdParty/inih/"
                        "Hatchit/ThirdParty/cppformat/cppformat"
                        "Hatchit/ThirdParty/json/src/"
                        "Hatchit/ThirdParty/stb")

    add_executable(HEditor source/main.cpp)

    target_link_libraries(HEditor HatchitCore Qt5::Widgets)

endif()