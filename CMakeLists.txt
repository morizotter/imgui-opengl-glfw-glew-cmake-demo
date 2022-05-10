cmake_minimum_required(VERSION 3.6)
project(my_opengl)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_VERBOSE_MAKEFILE 1)
set(APP_VERSION_MAJOR 1)
set(APP_VERSION_MINOR 0)




add_subdirectory(dependency/imgui)
add_subdirectory(dependency/glm)
include_directories("${PROJECT_SOURCE_DIR}")

# glfw
find_package(glfw3 REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})
link_libraries(${GLFW_LIBRARY_DIRS})

# opengl
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

# glew
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

include_directories(inc)
add_subdirectory(common)


file( GLOB APP_SOURCES exec/*.cpp )
foreach( testsourcefile ${APP_SOURCES} )
get_filename_component(testname ${testsourcefile} NAME_WE)
add_executable( ${testname} ${testsourcefile} )

target_link_libraries(
        ${testname}
        glfw
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${EXTRA_LIBS}
        common
        imgui
        glm
)
endforeach( testsourcefile ${APP_SOURCES} )


