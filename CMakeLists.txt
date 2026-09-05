cmake_minimum_required(VERSION 3.28)

project(Boids VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

include(FetchContent)

set(SFML_BUILD_AUDIO OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)

FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM
)
FetchContent_MakeAvailable(SFML)

add_executable(BOIDS
    main.cpp
    src/boid.cpp
    src/game.cpp
    src/pvector.cpp
    src/uielements.cpp
    src/utility.cpp
)

set_target_properties(BOIDS PROPERTIES OUTPUT_NAME BOIDS.out)

target_compile_features(BOIDS PRIVATE cxx_std_17)
target_include_directories(BOIDS PRIVATE "${PROJECT_SOURCE_DIR}/inc")
target_link_libraries(BOIDS PRIVATE SFML::Graphics SFML::Window SFML::System)

if(WIN32)
    target_link_libraries(BOIDS PRIVATE SFML::Main)
endif()

target_compile_options(BOIDS PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-Wall -Wextra>
    $<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:GNU,Clang,AppleClang>>:-O2>
    $<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:GNU,Clang,AppleClang>>:-O0>
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
)

option(BOIDS_ENABLE_SANITIZERS "Enable Address/UndefinedBehavior sanitizers for BOIDS." OFF)
if(BOIDS_ENABLE_SANITIZERS AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
    include(CheckCXXSourceCompiles)

    set(BOIDS_SANITIZER_FLAGS -fsanitize=address,undefined,signed-integer-overflow)
    set(CMAKE_REQUIRED_FLAGS_SAVE "${CMAKE_REQUIRED_FLAGS}")
    set(CMAKE_REQUIRED_LINK_OPTIONS_SAVE "${CMAKE_REQUIRED_LINK_OPTIONS}")
    string(REPLACE ";" " " BOIDS_SANITIZER_FLAGS_TEXT "${BOIDS_SANITIZER_FLAGS}")
    set(CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS} ${BOIDS_SANITIZER_FLAGS_TEXT}")
    set(CMAKE_REQUIRED_LINK_OPTIONS ${CMAKE_REQUIRED_LINK_OPTIONS} ${BOIDS_SANITIZER_FLAGS})

    check_cxx_source_compiles("int main() { return 0; }" BOIDS_SANITIZERS_SUPPORTED)

    set(CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS_SAVE}")
    set(CMAKE_REQUIRED_LINK_OPTIONS "${CMAKE_REQUIRED_LINK_OPTIONS_SAVE}")

    if(BOIDS_SANITIZERS_SUPPORTED)
        target_compile_options(BOIDS PRIVATE ${BOIDS_SANITIZER_FLAGS} -fno-omit-frame-pointer)
        target_link_options(BOIDS PRIVATE ${BOIDS_SANITIZER_FLAGS})
    else()
        message(WARNING "BOIDS_ENABLE_SANITIZERS is ON, but this compiler/linker cannot build with the requested sanitizer runtime. Building without sanitizers.")
    endif()
endif()

add_custom_target(run
    COMMAND $<TARGET_FILE:BOIDS>
    DEPENDS BOIDS
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    USES_TERMINAL
)

set_property(DIRECTORY "${PROJECT_SOURCE_DIR}" PROPERTY VS_STARTUP_PROJECT BOIDS)
