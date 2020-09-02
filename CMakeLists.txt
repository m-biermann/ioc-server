cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)

if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_library(iocServer src/main.cpp src/construction/AppBuilder.cpp src/construction/AppBuilder.h src/Server.cpp src/Server.h src/ThreadRunner.cpp src/ThreadRunner.h)

target_include_directories(iocServer PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_link_libraries(iocServer PRIVATE Threads::Threads PUBLIC ${PROJECT_NAME}::ioc)

add_library(${PROJECT_NAME}::iocServer ALIAS iocServer)

add_subdirectory(test)

include(GNUInstallDirs)
install(TARGETS iocServer
        EXPORT ${PROJECT_NAME}Targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/${PROJECT_NAME}
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/mabiphmo TYPE INCLUDE)