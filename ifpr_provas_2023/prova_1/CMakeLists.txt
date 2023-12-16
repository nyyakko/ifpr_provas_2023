add_subdirectory(source)

set(SUBPROJECT_NAME prova_1)

add_executable(${SUBPROJECT_NAME} "${prova_1_SourceFiles}")

enable_static_analyzers(${SUBPROJECT_NAME} ON)

target_include_directories(${SUBPROJECT_NAME} 
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" 
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/prova_1"
)

set_target_properties(${SUBPROJECT_NAME} PROPERTIES C_STANDARD 23)

target_compile_options(${SUBPROJECT_NAME} PRIVATE ${prova_1_CompilerOptions})
target_link_libraries(${SUBPROJECT_NAME} PRIVATE ${prova_1_ExternalLibraries})
