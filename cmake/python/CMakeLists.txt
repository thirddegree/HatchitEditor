
if(WIN32)

else()

    find_package(PythonLibs REQUIRED python)

    include_directories("${CMAKE_SOURCE_DIR}/include/python")

    file(GLOB EDITOR_PYTHON_INC "${CMAKE_SOURCE_DIR}/include/python/*.h")
    file(GLOB EDITOR_PYTHON_SRC "${CMAKE_SOURCE_DIR}/source/python/*.cpp")

    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")

    pybind11_add_module(hpy SHARED ${EDITOR_PYTHON_INC} ${EDITOR_PYTHON_SRC})

    set_target_properties(hpy
            PROPERTIES
            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
            SUFFIX "")
    target_link_libraries(hpy PRIVATE ${PYTHON_LIBRARY} HatchitCore)
endif()