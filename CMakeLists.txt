cmake_minimum_required(VERSION 3.20.0)
project(ZSLBox VERSION 0.0.1)

if (MSVC)
    add_compile_options("/utf-8")
    add_compile_options("/arch:AVX2")
    add_compile_options("/GL")
    add_link_options("/LTCG")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/output/)

find_package(Qt6 REQUIRED COMPONENTS Widgets Gui Core)

add_subdirectory(src)
include_directories(inc)
file(GLOB _UI_HEADS inc/ui/*hpp)

qt_add_executable(ZSLBox
    MANUAL_FINALIZATION
    src/main.cpp
    ${_UI_HEADS}

    ${_BASE_SOURCES}
    ${_UI_SOURCES}
)

target_link_libraries(ZSLBox PRIVATE Qt6::Widgets Qt6::Gui Qt6::Core)

set_target_properties(ZSLBox PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

qt_finalize_executable(ZSLBox)