//
// Created by max on 8/14/20.
//

#include "Server.h"
#include <stdexcept>
#include <boost/bind.hpp>

namespace mabiphmo::ioc_server{

	Server::Server(std::shared_ptr<ThreadRunner> threadRunner, std::vector<std::shared_ptr<service::IStartableService>> &&startableServices) :
		threadRunner_(std::move(threadRunner)),
		startableServices_(std::move(startableServices))
	{
		if(startableServices_.empty()){
			throw std::runtime_error("No startable services registered");
		}
	}

	Server::~Server()
	{
		Stop();
	}

	void Server::onStart() {
		for(const std::shared_ptr<service::IStartableService>& startableService : startableServices_){
			startableService->Start();
		}
		threadRunner_->Start();
	}

	void Server::onStop() {
		if(!threadRunner_->stopped()){
			threadRunner_->post([capture0 = shared_from_this()] { capture0->doStop(); });
		}
		else {
			for(const std::shared_ptr<service::IStartableService>& startableService : startableServices_){
				startableService->Stop();
			}
		}
	}

	void Server::doStop() {
		for(const std::shared_ptr<service::IStartableService>& startableService : startableServices_){
			startableService->Stop();
		}
		threadRunner_->Stop();
	}
}