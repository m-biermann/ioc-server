//
// Created by max on 8/28/20.
//

#ifndef IOCSERVER_SERVICEARGBASECAST_H
#define IOCSERVER_SERVICEARGBASECAST_H

#include <mabiphmo/iocServer/construction/IServiceArg.h>
#include <memory>

namespace mabiphmo::iocServer::construction {
	template <class TBase, class TDerived>
	class ServiceArgBaseCast : public IServiceArg<std::shared_ptr<TBase>> {
		std::unique_ptr<IServiceArg<std::shared_ptr<TDerived>>> derivedArg_;
	public:
		explicit ServiceArgBaseCast(std::unique_ptr<IServiceArg<std::shared_ptr<TDerived>>> &&derivedArg) : derivedArg_(std::move(derivedArg)) {}
		std::shared_ptr<TBase> operator()() override{
			return std::dynamic_pointer_cast<TBase>(derivedArg_());
		}
	};
}

#endif //IOCSERVER_SERVICEARGBASECAST_H
