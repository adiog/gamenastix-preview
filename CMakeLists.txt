cmake_minimum_required(VERSION 3.0)
project(treadmill-t2-opengl CXX)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/deps/sensor-fusion)

add_definitions(-DGLM_ENABLE_EXPERIMENTAL)

if(UNIX)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/deps/abseil)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/deps/abseil)
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/deps/glut)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/deps/glm)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/deps/udpbox/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/deps/sensor-fusion/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/deps/sensor-fusion/variant/imu-kalman)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/source)

file(GLOB_RECURSE sources ${CMAKE_CURRENT_SOURCE_DIR}/source/**.cpp)
file(GLOB_RECURSE headers ${CMAKE_CURRENT_SOURCE_DIR}/source/**.h)
add_library(openglStickyman start/main.cpp ${sources} ${headers})
if(UNIX)
    target_link_libraries(openglStickyman sensorFusion GL glut GLU absl_strings pthread)
else()
    target_link_libraries(openglStickyman ${CMAKE_CURRENT_SOURCE_DIR}/deps/glut/glut32.lib ws2_32 sensorFusion opengl32 glu32 pthread)
    file(
            COPY
            ${CMAKE_CURRENT_SOURCE_DIR}/deps/glut/glut32.dll
            DESTINATION
            ${CMAKE_CURRENT_BINARY_DIR}
    )
endif()

add_executable(treadmill-t2-opengl ${CMAKE_CURRENT_SOURCE_DIR}/start/main.cpp)
target_link_libraries(treadmill-t2-opengl openglStickyman)

add_executable(template_test test/template_test.cpp)
target_link_libraries(template_test gtest pthread)
