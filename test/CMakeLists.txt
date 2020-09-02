# 'Boost_Tests_run' is the target name
# 'test1.cpp tests2.cpp' are source files with tests
add_executable (iocServerTests ServerTests.cpp structs.h IStartableServiceTests.cpp AppBuilderTests.cpp )

target_link_libraries(iocServerTests PRIVATE ${Boost_LIBRARIES} Threads::Threads ${PROJECT_NAME}::iocServer)
target_include_directories(iocServerTests PRIVATE ${Boost_INCLUDE_DIRS})