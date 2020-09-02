//
// Created by max on 8/28/20.
//

#ifndef IOCSERVER_SERVICEARGRELATION_H
#define IOCSERVER_SERVICEARGRELATION_H

#include <mabiphmo/ioc/Container.h>
#include <mabiphmo/iocServer/construction/IServiceArg.h>

namespace mabiphmo::iocServer::construction {
	template <class TService, typename...TArgs>
	class ServiceArgRelation : public IServiceArg<std::shared_ptr<TService>>{
		ioc::Container &container_;
		std::tuple<std::unique_ptr<IServiceArg<TArgs>>...> args_;
	public:
		explicit ServiceArgRelation(ioc::Container &container, std::unique_ptr<IServiceArg<TArgs>>&&...args) : container_(container), args_(std::move(args)...) {}
		std::shared_ptr<TService> operator()() override{
			return std::apply([this](auto&&...args) -> std::shared_ptr<TService>{return container_.GetInstance<TService>(args()...);}, args_);
		}
	};
}

#endif //IOCSERVER_SERVICEARGRELATION_H
