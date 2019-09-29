cmake_minimum_required(VERSION 3.10)
project(vss_software)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread") 

find_package(Boost REQUIRED COMPONENTS system)

include_directories("include"
                    "${CMAKE_SOURCE_DIR}/ext/RxCpp/Rx/v2/src"
                    "${CMAKE_SOURCE_DIR}/lib"
                    ${Boost_INCLUDE_DIRS})

set(SRCS
    "src/geometry/field_section.cc"
    "src/geometry/point_2d.cc"
    "src/io/serial_message.cc"
    "src/io/serial_sender.cc"
    "src/system/ball.cc"
    "src/system/robot.cc"
    "src/system/system.cc")

add_library(vss_software_srcs
            ${SRCS})

add_executable(vss_software "src/main.cpp")

target_link_libraries(vss_software
                    vss_software_srcs
                    ${Boost_LIBRARIES})