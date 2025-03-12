set(MmsAgent_SourceFiles
        include/Agent.h
        include/mmtp.pb.h
        src/Agent.cpp
        src/mmtp.pb.cc)

add_library(MmsAgent ${MmsAgent_SourceFiles})

find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIRS})

target_include_directories(MmsAgent
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(MmsAgent PRIVATE fmt::fmt fmt::fmt-header-only usockets zlib libuv protobuf::libprotobuf) #uWebSockets::uWebSockets
target_include_directories(MmsAgent PRIVATE ${UWEBSOCKETS_INCLUDE_DIRS})
add_subdirectory(test)
