//
// Created by max on 8/24/20.
//

#ifndef IOCSERVER_THREADRUNNER_H
#define IOCSERVER_THREADRUNNER_H

#include <mabiphmo/iocServer/service/IStartableService.h>
#include <thread>
#include <vector>
#include <boost/asio/io_context.hpp>

namespace mabiphmo::iocServer {
	class ThreadRunner : public service::IStartableService {
		std::shared_ptr<boost::asio::io_context> ioContext_;
		unsigned int count_;
		std::vector<std::thread> threads_;
	protected:
		void onStart() override;
		void onStop() override;
	public:
		ThreadRunner(std::shared_ptr<boost::asio::io_context> ioContext, unsigned int count);
		bool stopped();
		void post(std::function<void()> func);
	};
}

#endif //IOCSERVER_THREADRUNNER_H
