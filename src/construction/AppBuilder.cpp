//
// Created by max on 8/14/20.
//

#include "AppBuilder.h"
#include <boost/asio/io_context.hpp>

namespace mabiphmo::iocServer::construction{
	AppBuilder::AppBuilder(ioc::Container &&container) : container_(std::move(container)), threadCount_(50)
	{
		WithService<boost::asio::io_context>(50);
	}

	std::shared_ptr<Server> AppBuilder::Build() {
		std::vector<std::shared_ptr<service::IStartableService>> iStartableServices = std::vector<std::shared_ptr<service::IStartableService>>();
		for(std::unique_ptr<IServiceArg<std::shared_ptr<service::IStartableService>>> &factory : iIoServiceFactories_){
			iStartableServices.push_back((*factory)());
		}
		return std::make_shared<Server>(std::make_shared<ThreadRunner>(IoCContainer().GetInstance<boost::asio::io_context>(), threadCount_), std::move(iStartableServices));
	}

	ioc::Container &AppBuilder::IoCContainer() {
		return container_;
	}

	IAppBuilder &AppBuilder::WithThreadCount(unsigned int count) {
		threadCount_ = count;
		return WithService<boost::asio::io_context>(count);
	}

	IAppBuilder &AppBuilder::WithStartableService(std::unique_ptr<IServiceArg<std::shared_ptr<service::IStartableService>>> &&factory)
	{
		iIoServiceFactories_.push_back(std::move(factory));
		return *this;
	}
}