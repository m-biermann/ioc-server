set (Boost_USE_STATIC_LIBS OFF)
find_package (Boost REQUIRED COMPONENTS unit_test_framework)
include_directories (${Boost_INCLUDE_DIRS})

# 'Boost_Tests_run' is the target name
# 'test1.cpp tests2.cpp' are source files with tests
add_executable (Boost_Tests_run ../include/mabiphmo/iocServer/construction/IAppBuilder.h ../include/mabiphmo/iocServer/service/IStartableService.h ../src/construction/AppBuilder.cpp ../src/construction/AppBuilder.h ../src/Server.cpp ../src/Server.h ../src/ThreadRunner.cpp ../src/ThreadRunner.h ServerTests.cpp structs.h IStartableServiceTests.cpp AppBuilderTests.cpp ../include/mabiphmo/iocServer/construction/IServiceArg.h ../include/mabiphmo/iocServer/construction/ServiceArgRelation.h ../include/mabiphmo/iocServer/construction/ServiceArgBaseCast.h)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(Boost_Tests_run ${Boost_LIBRARIES} Threads::Threads)