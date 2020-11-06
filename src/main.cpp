//
// Created by max on 8/14/20.
//

#include <mabiphmo/ioc-server/main.h>
#include <iostream>
#include "construction/AppBuilder.h"

int main(int argc, char *argv[]){
	if(Startup(argc, argv)){
		mabiphmo::ioc_server::construction::AppBuilder builder((mabiphmo::ioc_container::Container()));
		Configure(builder);
		std::shared_ptr<mabiphmo::ioc_server::Server> server = builder.Build();
		ConfigureShutdown([&server](){server->Stop();});
		server->Start();
	}
	else{
		std::cerr << "Startup denied, stopping..." << std::endl;
	}
}