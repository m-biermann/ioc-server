//
// Created by max on 8/14/20.
//

#ifndef IOCSERVER_MAIN_H
#define IOCSERVER_MAIN_H

#include <mabiphmo/ioc-server/construction/IAppBuilder.h>
#include <functional>

bool Startup(int argc, char *argv[]);
void Configure(mabiphmo::ioc_server::construction::IAppBuilder &builder);
void ConfigureShutdown(std::function<void()> &&shutdownFunc);

#endif //IOCSERVER_MAIN_H
