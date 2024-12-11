cmake_minimum_required(VERSION 3.25)
project(OpenCircuit)

set(CMAKE_CXX_STANDARD 17)

if(WIN32)
	set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
	set(VCPKG_HOST_TRIPLET "x64-windows")
	set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
elseif (LINUX)
	set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
	set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
endif()

find_package(OpenGL REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(ImGui-SFML CONFIG REQUIRED)
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

file(GLOB_RECURSE SOURCES
    "OpenCircuit/*/*.cpp"
)

file(GLOB_RECURSE HEADERS
    "OpenCircuit/*/*.h"
)

add_executable(OpenCircuit ${SOURCES} ${HEADERS})

target_include_directories(OpenCircuit PUBLIC ${CMAKE_SOURCE_DIR}/OpenCircuit/depen/ImGUI/include)
target_include_directories(OpenCircuit PUBLIC ${CMAKE_SOURCE_DIR}/OpenCircuit/src)
target_link_libraries(OpenCircuit PUBLIC ${OPENGL_gl_LIBRARY} sfml-graphics sfml-audio sfml-window sfml-system)
target_link_libraries(OpenCircuit PUBLIC imgui::imgui ImGui-SFML::ImGui-SFML)