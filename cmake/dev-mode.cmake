include(cmake/folders.cmake)

add_custom_target(
    run-exe
    COMMAND julia-visualizer_exe
    VERBATIM
)
add_dependencies(run-exe julia-visualizer_exe)

include(cmake/lint-targets.cmake)
include(cmake/spell-targets.cmake)

add_folders(Project)
