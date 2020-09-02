//
// Created by max on 8/28/20.
//

#ifndef IOCSERVER_SERVICEARGVALUE_H
#define IOCSERVER_SERVICEARGVALUE_H

#include <mabiphmo/iocServer/construction/IServiceArg.h>

namespace mabiphmo::iocServer::construction {
	template<class TArg>
	class ServiceArgValue : public IServiceArg<TArg> {
		TArg &&value_;
	public:
		explicit ServiceArgValue(TArg &&value) : value_(std::forward(value)) {}

		TArg operator()() override {
			return std::forward<TArg>(value_);
		}
	};
}

#endif //IOCSERVER_SERVICEARGVALUE_H
