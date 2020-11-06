//
// Created by max on 8/24/20.
//

#include "ThreadRunner.h"

namespace mabiphmo::ioc_server{
	ThreadRunner::ThreadRunner(std::shared_ptr<boost::asio::io_context> ioContext, unsigned int count) : ioContext_(std::move(ioContext)), count_(count) {}

	void ThreadRunner::onStop()
	{
		if(ioContext_ == nullptr)
			return;
		ioContext_->stop();
	}

	void ThreadRunner::onStart()
	{
		if(count_ == 0 || ioContext_ == nullptr)
			return;
		threads_.reserve(count_ - 1);
		for(auto i = count_ - 1; i > 0; --i)
			threads_.emplace_back(
				[this]{
					ioContext_->run();
				});
		ioContext_->run();
		for(std::thread &thread : threads_)
			thread.join();
		threads_.clear();
	}

	bool ThreadRunner::stopped() {
		if(ioContext_ == nullptr)
			return true;
		return ioContext_->stopped();
	}

	void ThreadRunner::post(std::function<void()> func) {
		if(ioContext_ == nullptr)
			return;
		ioContext_->post(func);
	}
}
