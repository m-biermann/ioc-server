//
// Created by max on 8/14/20.
//

#ifndef IOCSERVER_APPBUILDER_H
#define IOCSERVER_APPBUILDER_H

#include <mabiphmo/ioc-server/construction/IAppBuilder.h>
#include "../Server.h"

namespace mabiphmo::ioc_server::construction{
	class AppBuilder : public IAppBuilder {
		ioc_container::Container container_;
		unsigned int threadCount_;
		std::vector<std::function<std::shared_ptr<service::IStartableService>()>> iIoServiceFactories_;
	public:
		ioc_container::Container &IoCContainer() override;
		explicit AppBuilder(ioc_container::Container &&container);
		std::shared_ptr<Server> Build();
		IAppBuilder &WithThreadCount(unsigned int count) override;

		IAppBuilder &WithStartableService(std::function<std::shared_ptr<service::IStartableService>()> && serviceFactory) override;
	};
}

#endif //IOCSERVER_APPBUILDER_H
