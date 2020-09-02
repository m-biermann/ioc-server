//
// Created by max on 8/14/20.
//

#ifndef IOCSERVER_APPBUILDER_H
#define IOCSERVER_APPBUILDER_H

#include <mabiphmo/iocServer/construction/IAppBuilder.h>
#include "../Server.h"

namespace mabiphmo::iocServer::construction{
	class AppBuilder : public IAppBuilder {
		ioc::Container container_;
		unsigned int threadCount_;
		std::vector<std::unique_ptr<IServiceArg<std::shared_ptr<service::IStartableService>>>> iIoServiceFactories_;
	public:
		ioc::Container &IoCContainer() override;
		explicit AppBuilder(ioc::Container &&container);
		std::shared_ptr<Server> Build();
		IAppBuilder &WithThreadCount(unsigned int count) override;
		IAppBuilder &WithStartableService(std::unique_ptr<IServiceArg<std::shared_ptr<service::IStartableService>>>&& factory) override;
	};
}

#endif //IOCSERVER_APPBUILDER_H
