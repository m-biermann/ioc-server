//
// Created by max on 8/14/20.
//

#include <mabiphmo/iocServer/main.h>
#include <iostream>
#include "construction/AppBuilder.h"

int main(int argc, char *argv[]){
	if(Startup(argc, argv)){
		mabiphmo::iocServer::construction::AppBuilder builder((mabiphmo::ioc::Container()));
		Configure(builder);
		std::shared_ptr<mabiphmo::iocServer::Server> server = builder.Build();
		ConfigureShutdown([&server](){server->Stop();});
		server->Start();
	}
	else{
		std::cerr << "Startup denied, stopping..." << std::endl;
	}
}