project(PID)

cmake_minimum_required (VERSION 3.5)

add_definitions(-std=c++11)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS "${CXX_FLAGS}")

set(core_sources src/PID.cpp src/hub.cpp src/OnlineTwiddle.cpp src/PIDCounter.cpp)

include_directories(/usr/local/include)
link_directories(/usr/local/lib)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

    include_directories(/usr/local/opt/openssl/include)
    link_directories(/usr/local/opt/openssl/lib)

    file(GLOB LIBUV_DIR /usr/local/Cellar/libuv/1*/lib)
    link_directories(${LIBUV_DIR})

endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin") 

add_executable(pid src/main.cpp ${core_sources})
target_link_libraries(pid z ssl uv uWS)
