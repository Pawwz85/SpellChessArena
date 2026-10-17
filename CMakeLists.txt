cmake_minimum_required(VERSION 3.28)

project(SpellChessArena VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Release builds use compiler/linker whole-program optimization (MSVC /GL and
# /LTCG, or the equivalent -flto flags on GCC/Clang).
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE ON)

option (ENABLE_IWYU "Enable include-what-you-use" OFF)


# Keep the compiler runtime self-contained in distributed Windows builds. Qt is
# still deployed beside the executable by Qt's deployment script below.
if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>" CACHE STRING "MSVC runtime library" FORCE)
elseif(MINGW)
    add_link_options(-static-libgcc -static-libstdc++)
endif()

set ( src_files 
    "src/App.cpp"
    "src/EmptyBoardWidget.cpp"
    "src/EngineAnalisysConfigDialog.cpp"
    "src/EngineRepository.cpp"
    "src/Form.cpp"
    "src/GameRunnerConfigurationDialog.cpp"
    "src/LiveAnalisis.cpp"
    "src/LiveAnalisisEngineDialog.cpp"
    "src/main.cpp"
    "src/PastePGN4Dialog.cpp"
    "src/PasteFENDialog.cpp"
)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui Concurrent)

include(FetchContent)

FetchContent_Declare(
    SpellChessLib
    URL https://github.com/Pawwz85/SpellChessLib/archive/refs/tags/v1.0.4.tar.gz
)

FetchContent_MakeAvailable(SpellChessLib)

qt_standard_project_setup()

set (all_files
    ${headers}
    ${src_files}
)

add_compile_definitions(QT_NO_EMIT)

if(ENABLE_IWYU)
    find_program(IWYU_EXECUTABLE NAMES include-what-you-use)
    if(NOT IWYU_EXECUTABLE)
        message(FATAL_ERROR
            "ENABLE_IWYU is ON, but include-what-you-use was not found.")
    endif()

    set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE
        "${IWYU_EXECUTABLE}")
endif()

add_subdirectory(Misc)
add_subdirectory(SpriteSet)
add_subdirectory(BoardGrid)
add_subdirectory(SpellButton)
add_subdirectory(EngineTools)
add_subdirectory(BoardViewer)

qt_add_executable( SpellChessArena ${src_files} )

target_compile_definitions( SpellChessArena PRIVATE QT_NO_EMIT) # Disable QT's emit keyword to avoid name conflict with UCI Loader
target_link_libraries( SpellChessArena PRIVATE Qt6::Core Qt6::Widgets Qt6::Gui Qt6::Concurrent)
target_link_libraries( SpellChessArena PRIVATE BoardGrid SpellButton SpriteSet BoardViewer spellchess Misc)
target_include_directories( SpellChessArena PRIVATE include )

enable_testing()
# add_subdirectory(tests)

set_target_properties( SpellChessArena PROPERTIES
    WIN32_EXECUTABLE ON
)


if(WIN32)
    qt_generate_deploy_app_script(
        TARGET SpellChessArena
        OUTPUT_SCRIPT deploy_script
        NO_TRANSLATIONS
        DEPLOY_TOOL_OPTIONS "--release" "--compiler-runtime"
    )
else()
    qt_generate_deploy_app_script(
        TARGET SpellChessArena
        OUTPUT_SCRIPT deploy_script
        NO_TRANSLATIONS
    )
endif()


# SpellChessLib contains UTF-8 move-notation literals. Apply the compiler
# character-set options before FetchContent creates its targets so the fetched
# spellchess target is compiled with the same settings.
if(MSVC)
    add_compile_options(/utf-8)
elseif(MINGW OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-finput-charset=UTF-8 -fexec-charset=UTF-8)
endif()

install(TARGETS SpellChessArena
    RUNTIME DESTINATION .
)

install(SCRIPT ${deploy_script})

# Qt's deployment script may place runtime DLLs in bin/ instead of beside the
# application, so move the generated directory contents to the package root.
if(WIN32)
    install(CODE [[
        set(_runtime_bin "${CMAKE_INSTALL_PREFIX}/bin")
        if(IS_DIRECTORY "${_runtime_bin}")
            file(COPY "${_runtime_bin}/" DESTINATION "${CMAKE_INSTALL_PREFIX}")
            file(REMOVE_RECURSE "${_runtime_bin}")
        endif()
    ]])
endif()

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/assets/"
    DESTINATION assets
)

if(NOT DEFINED CPACK_PACKAGE_VERSION)
    set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}" CACHE STRING "Package version")
endif()
set(CPACK_PACKAGE_NAME "SpellChessArena")
set(CPACK_PACKAGE_VENDOR "Pawwz")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "SpellChessArena")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "SpellChess desktop application")
set(CPACK_PACKAGE_CONTACT "SpellChessArena maintainers")
# FetchContent dependencies may define development install components. They are
# not part of the distributable application and can create invalid MSI input.
set(CPACK_COMPONENTS_ALL Unspecified)

if(WIN32 AND DEFINED ENV{WIX})
    file(TO_CMAKE_PATH "$ENV{WIX}" CPACK_WIX_ROOT)
endif()

# Keep this GUID unchanged so newer MSI packages upgrade older installations.
set(CPACK_WIX_UPGRADE_GUID "76bf2a1b-50f2-430e-b6b7-b4b9bd3cf5bc")
set(CPACK_GENERATOR "WIX;ZIP")
if(WIN32)
    set(CPACK_SYSTEM_NAME "win64")
elseif(UNIX)
    set(CPACK_SYSTEM_NAME "linux")
endif()
set(CPACK_PACKAGE_FILE_NAME
    "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_SYSTEM_NAME}")

include(CPack)
