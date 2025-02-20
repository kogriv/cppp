cmake_minimum_required(VERSION 3.10)
project(CPPProject)

include_directories(include)

# Enable verbose linking
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /VERBOSE:LIB")

# Add debug messages
message(STATUS "Build directory: ${CMAKE_BINARY_DIR}")

# 1. Create library first
add_library(math_lib SHARED src/math_lib.cpp)
# set_target_properties(math_lib PROPERTIES LINK_FLAGS "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/math_lib.def")
target_sources(math_lib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/math_lib.def)

# Set output directories for the library
# set_target_properties(math_lib PROPERTIES
#     RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
#     LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
#     ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
# )

# 2. Add path print command
add_custom_target(print_lib_path ALL
    COMMAND powershell.exe -Command "Write-Output 'Searching for path: ${CMAKE_BINARY_DIR}/Debug/math_lib.lib'"
)
add_dependencies(print_lib_path math_lib)

# 3. Add file existence check
add_custom_target(check_lib ALL
    COMMAND powershell.exe -Command "if (Test-Path '${CMAKE_BINARY_DIR}\\Debug\\math_lib.lib') { Write-Output 'Library FOUND at: ${CMAKE_BINARY_DIR}\\Debug\\math_lib.lib' } else { Write-Output 'Library NOT FOUND' }"
)
add_dependencies(check_lib print_lib_path)

# 4. Create and setup executable last
add_executable(main src/main.cpp)
# add_dependencies(main check_lib)
target_link_libraries(main math_lib)