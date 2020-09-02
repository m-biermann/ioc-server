//
// Created by max on 8/14/20.
//

#ifndef IOCSERVER_SERVER_H
#define IOCSERVER_SERVER_H

#include <mabiphmo/iocServer/service/IStartableService.h>
#include <vector>
#include <memory>
#include "ThreadRunner.h"

namespace mabiphmo::iocServer {
class Server : public service::IStartableService, std::enable_shared_from_this<Server> {
		std::shared_ptr<ThreadRunner> threadRunner_;
		std::vector<std::shared_ptr<service::IStartableService>> startableServices_;

		void doStop();
	protected:
		void onStart() override;
		void onStop() override;
	public:
		Server(std::shared_ptr<ThreadRunner> threadRunner, std::vector<std::shared_ptr<service::IStartableService>> &&startableServices);
		~Server();
	};
}

#endif //IOCSERVER_SERVER_H
