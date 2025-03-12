add_executable(MmsTest Tests.cpp)

target_link_libraries(MmsTest PRIVATE MmsAgent Catch2::Catch2)
