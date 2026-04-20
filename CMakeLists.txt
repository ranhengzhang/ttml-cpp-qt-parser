cmake_minimum_required(VERSION 3.20)

# 定义 lyric 库的版本号
project(LyricParser
    VERSION 1.2.0
    LANGUAGES CXX
    DESCRIPTION "A C++ library for parsing and converting various lyric formats"
)

# Major 加权，Minor 和 Patch 直接相加
math(EXPR LYRIC_VERSION_COMBINED "${PROJECT_VERSION_MAJOR} * 1000 + ${PROJECT_VERSION_MINOR} + ${PROJECT_VERSION_PATCH}")
set(LYRIC_VERSION_COMBINED ${LYRIC_VERSION_COMBINED} PARENT_SCOPE)

message(STATUS "LyricParser version: ${PROJECT_VERSION} → combined: ${LYRIC_VERSION_COMBINED}")

if(NOT CMAKE_PROJECT_NAME OR PROJECT_IS_TOP_LEVEL)
    set(CMAKE_CXX_STANDARD 23)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

file(GLOB_RECURSE LYRIC_SOURCES
        "lyric_line/*.cpp"
        "lyric_object/*.cpp"
        "lyric_syl/*.cpp"
        "lyric_time/*.cpp"
        "utils/*.cpp"
)

add_library(lyric STATIC ${LYRIC_SOURCES})
add_library(LyricParser::lyric ALIAS lyric)

target_compile_features(lyric PUBLIC cxx_std_23)

target_include_directories(lyric PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lyric_line>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lyric_object>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lyric_syl>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lyric_time>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/utils>
        $<INSTALL_INTERFACE:include>
        $<INSTALL_INTERFACE:include/LyricParser>
)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Xml Gui)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Xml Gui)
target_link_libraries(lyric PUBLIC
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Xml
        Qt${QT_VERSION_MAJOR}::Gui)

if(MSVC)
    target_compile_options(lyric PUBLIC /Zc:__cplusplus)
endif()

# 安装配置
include(GNUInstallDirs)

install(TARGETS lyric
        EXPORT LyricParserTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(EXPORT LyricParserTargets
        FILE LyricParserTargets.cmake
        NAMESPACE LyricParser::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/LyricParser
)

# 生成配置文件
include(CMakePackageConfigHelpers)

configure_package_config_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/LyricParserConfig.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/LyricParserConfig.cmake"
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/LyricParser
)

write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/LyricParserConfigVersion.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion
)

install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/LyricParserConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/LyricParserConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/LyricParser
)

# 安装头文件
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/LyricParser
        FILES_MATCHING PATTERN "*.hpp"
)
