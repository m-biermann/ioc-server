//
// Created by max on 8/14/20.
//

#include "AppBuilder.h"
#include <boost/asio/io_context.hpp>

namespace mabiphmo::ioc_server::construction{
	AppBuilder::AppBuilder(ioc_container::Container &&container) : container_(std::move(container)), threadCount_(50)
	{
		auto ioContextHolder = container_.RegisterType(
			ioc_container::TypeHolder<boost::asio::io_context>(
				ioc_container::Scope::Singleton,
				std::function<std::shared_ptr<boost::asio::io_context>(int)>(
					[](int concurrency)
					{
						return std::make_shared<boost::asio::io_context>(concurrency);
					})));
		ioContextHolder->SetFactory(
			std::function<std::shared_ptr<boost::asio::io_context>()>(
				[parameterFactory = ioContextHolder->GetFactory<int>()]()
				{
					return (*parameterFactory)(50);
				}));
		container_.RegisterType(
			ioc_container::TypeHolder<ThreadRunner>(
				ioc_container::Scope::Singleton,
				std::function<std::shared_ptr<ThreadRunner>()>(
					[&ioc_container = std::as_const(container_),
	                    &count = threadCount_]()
                    {
						return std::make_shared<ThreadRunner>(
							ioc_container.GetTypeHolder<boost::asio::io_context>()->Get(),
							count);
                    })));
		container_.RegisterType(
			ioc_container::TypeHolder<Server>(
				ioc_container::Scope::Factory,
				std::function<std::shared_ptr<Server>(std::vector<std::shared_ptr<service::IStartableService>> &&)>(
					[&ioc_container = std::as_const(container_)](
						std::vector<std::shared_ptr<service::IStartableService>> && startableServices)
					{
						return std::make_shared<Server>(
							ioc_container.GetTypeHolder<ThreadRunner>()->Get(),
							std::move(startableServices));
					})));
	}

	std::shared_ptr<Server> AppBuilder::Build() {
		std::vector<std::shared_ptr<service::IStartableService>> iStartableServices;
		for(std::function<std::shared_ptr<service::IStartableService>()> &factory : iIoServiceFactories_){
			iStartableServices.push_back(factory());
		}
		return IoCContainer().GetTypeHolder<Server>()->Get(std::move(iStartableServices));
	}

	ioc_container::Container &AppBuilder::IoCContainer() {
		return container_;
	}

	IAppBuilder &AppBuilder::WithThreadCount(unsigned int count) {
		threadCount_ = count;
		auto ioContextHolder = IoCContainer().GetTypeHolder<boost::asio::io_context>();
		ioContextHolder->SetFactory(
			std::function<std::shared_ptr<boost::asio::io_context>()>(
				[parameterFactory = ioContextHolder->GetFactory<int>(), count]()
				{
					return (*parameterFactory)(count);
				}));
		return *this;
	}

	IAppBuilder &AppBuilder::WithStartableService(std::function<std::shared_ptr<service::IStartableService>()> && serviceFactory)
	{
		iIoServiceFactories_.push_back(std::move(serviceFactory));
		return *this;
	}
}