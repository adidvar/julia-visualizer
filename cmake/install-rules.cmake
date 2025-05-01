install(
    TARGETS julia-visualizer_exe
    RUNTIME COMPONENT julia-visualizer_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
