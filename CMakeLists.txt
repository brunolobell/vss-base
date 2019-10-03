cmake_minimum_required(VERSION 3.10)
project(vss_software)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread") 

find_package(Boost REQUIRED COMPONENTS system)

include_directories("include"
                    "${CMAKE_SOURCE_DIR}/ext/RxCpp/Rx/v2/src"
                    "${CMAKE_SOURCE_DIR}/lib"
                    ${Boost_INCLUDE_DIRS})

set(SRCS
    "src/geometry/field_line.cc"
    "src/geometry/point_2d.cc"
    "src/geometry/vector_2d.cc"
    "src/io/serial_sender.cc"
    "src/io/tcp_receiver.cc"
    "src/operation/operation.cc"
    "src/system/ball.cc"
    "src/system/robot.cc"
    "src/system/system.cc")

add_library(vss_software_srcs
            ${SRCS})

set (VSS_CORE libvss-core.so)

add_executable(vss_software "src/main.cpp")

target_link_libraries(vss_software
                    vss_software_srcs
                    ${VSS_CORE}
                    ${Boost_LIBRARIES})