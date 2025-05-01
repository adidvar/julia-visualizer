Include(FetchContent)

FetchContent_Declare(
    glad_fetch
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG        658f48e72aee3c6582e80b05ac0f8787a64fe6bb #v2.0.6
    GIT_PROGRESS   TRUE
    SOURCE_SUBDIR  cmake
)

FetchContent_MakeAvailable(glad_fetch)
glad_add_library(glad STATIC REPRODUCIBLE LOADER API gl:core=3.3)
