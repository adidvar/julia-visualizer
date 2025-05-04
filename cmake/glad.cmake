include(FetchContent)

FetchContent_Declare(
  glad
  GIT_REPOSITORY https://github.com/Dav1dde/glad.git
  GIT_TAG 658f48e72aee3c6582e80b05ac0f8787a64fe6bb
  SOURCE_SUBDIR cmake
)

FetchContent_MakeAvailable(glad)

glad_add_library(glad STATIC REPRODUCIBLE LOADER API gl:core=3.3)
