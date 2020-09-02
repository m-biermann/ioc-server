cmake_minimum_required(VERSION 3.16)
project(iocServer)

set(CMAKE_CXX_STANDARD 17)

if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

include_directories(include)

add_library(iocServer src/main.cpp include/mabiphmo/iocServer/construction/IAppBuilder.h include/mabiphmo/iocServer/service/IStartableService.h src/construction/AppBuilder.cpp src/construction/AppBuilder.h src/Server.cpp src/Server.h include/mabiphmo/iocServer/main.h src/ThreadRunner.cpp src/ThreadRunner.h include/mabiphmo/iocServer/construction/IServiceArg.h include/mabiphmo/iocServer/construction/ServiceArgRelation.h include/mabiphmo/iocServer/construction/ServiceArgBaseCast.h)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(iocServer PRIVATE Threads::Threads)

add_subdirectory(test)