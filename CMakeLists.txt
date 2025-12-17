# ====================================
# 项目配置
# ====================================

cmake_minimum_required(VERSION 3.28)
project(
    anim 
    VERSION 0.1.0 
    LANGUAGES C CXX
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
if(WIN32)
    add_compile_definitions(NOMINMAX)
endif()


# ====================================
# 依赖管理
# ====================================

include(FetchContent)

set(FETCHCONTENT_QUIET OFF)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)

set(_PREV_BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS})

# 都使用静态链接
set(BUILD_SHARED_LIBS OFF)

# SDL3
set(SDL_TEST_LIBRARY OFF)
FetchContent_Declare(
    SDL3
    GIT_REPOSITORY "https://github.com/libsdl-org/SDL.git"
    GIT_TAG "release-3.2.28"
    GIT_SHALLOW ON
    GIT_PROGRESS ON
)
FetchContent_MakeAvailable(SDL3)

# spdlog
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY "https://github.com/gabime/spdlog.git"
    GIT_TAG "v1.16.0"
    GIT_SHALLOW ON
    GIT_PROGRESS ON
)
FetchContent_MakeAvailable(spdlog)

# dawn
set(DAWN_FETCH_DEPENDENCIES ON)
FetchContent_Declare(
    dawn
    GIT_REPOSITORY "https://github.com/google/dawn.git"
    GIT_TAG "v20251216.160840"
    GIT_SHALLOW ON
    GIT_PROGRESS ON
    GIT_SUBMODULES ""
    EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(dawn)

set(BUILD_SHARED_LIBS ${_PREV_BUILD_SHARED_LIBS})


# ====================================
# 目标配置
# ====================================

add_executable(anim 
    src/main.cpp
)

target_link_libraries(anim PRIVATE
    SDL3::SDL3
    spdlog::spdlog_header_only
    dawn::webgpu_dawn
)

if(MSVC)
    target_compile_options(anim PRIVATE
        /W4
    )
else()
    target_compile_options(anim PRIVATE
        -Wall 
        -Wextra
    )
endif()