//
// Created by max on 8/14/20.
//

#ifndef IOCSERVER_IAPPBUILDER_H
#define IOCSERVER_IAPPBUILDER_H

#include <mabiphmo/ioc-container/Container.h>
#include <mabiphmo/ioc-server/service/IStartableService.h>

namespace mabiphmo::ioc_server::construction {
	class IAppBuilder {
	public:
		virtual IAppBuilder &WithThreadCount(unsigned int count) = 0;

		virtual IAppBuilder &WithStartableService(std::function<std::shared_ptr<service::IStartableService>()> && serviceFactory) = 0;//std::unique_ptr<IServiceArg<std::shared_ptr<service::IStartableService>>>&& factory) = 0;
		[[nodiscard]] virtual ioc_container::Container &IoCContainer() = 0;
	};
}

#endif //IOCSERVER_IAPPBUILDER_H
