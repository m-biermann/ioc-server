//
// Created by max on 8/14/20.
//

#ifndef IOCSERVER_IAPPBUILDER_H
#define IOCSERVER_IAPPBUILDER_H

#include <mabiphmo/ioc/Container.h>
#include <mabiphmo/iocServer/service/IStartableService.h>
#include <mabiphmo/iocServer/construction/IServiceArg.h>
#include <mabiphmo/iocServer/construction/ServiceArgRelation.h>
#include <mabiphmo/iocServer/construction/ServiceArgBaseCast.h>

namespace mabiphmo::iocServer::construction {
	class IAppBuilder {
	public:
		virtual IAppBuilder &WithThreadCount(unsigned int count) = 0;

		template <class TService,
				typename ...TDependencies,
				typename... TArgs>
		IAppBuilder &WithService(TArgs &&...args){
			if constexpr(std::is_base_of<service::IStartableService, TService>::value){
				WithStartableService(std::unique_ptr<IServiceArg<std::shared_ptr<service::IStartableService>>>(new ServiceArgBaseCast<service::IStartableService, TService>(ServiceArgRelationFactory<TService>())));
			}
			IoCContainer().RegisterSingletonClassFactory<TService, TDependencies...>(std::forward<TArgs>(args) ...);
			return *this;
		}

		template <class TInterface, class TService,
				typename ...TDependencies,
				typename... TArgs>
		IAppBuilder &WithServiceOnInterface(TArgs &&...args){
			if constexpr(std::is_base_of<service::IStartableService, TInterface>::value){
				WithStartableService(std::unique_ptr<IServiceArg<std::shared_ptr<service::IStartableService>>>(new ServiceArgBaseCast<service::IStartableService, TInterface>(ServiceArgRelationFactory<TInterface>())));
			}
			IoCContainer().RegisterSingletonClassFactoryOnInterface<TInterface, TService, TDependencies...>(std::forward<TArgs>(args)...);
			return *this;
		}

		template <class TService,
				class TArgumentWrapper,
				class TDependencyWrapper,
				typename... TArgs>
		IAppBuilder &WithFactory(TArgs &&...args){
			IoCContainer().RegisterClassFactory<TService, TArgumentWrapper, TDependencyWrapper>(std::forward<TArgs>(args)...);
			return *this;
		}

		template <class TInterface, class TService,
				class TArgumentWrapper,
				class TDependencyWrapper,
				typename... TArgs>
		IAppBuilder &WithFactoryOnInterface(TArgs &&...args){
			IoCContainer().RegisterClassFactoryOnInterface<TInterface, TService, TArgumentWrapper, TDependencyWrapper>(std::forward<TArgs>(args)...);
			return *this;
		}

		template <class T, typename...TArgs>
		std::unique_ptr<IServiceArg<std::shared_ptr<T>>> ServiceArgRelationFactory(std::unique_ptr<IServiceArg<TArgs>>&&...args){
			return std::unique_ptr<IServiceArg<std::shared_ptr<T>>>(new ServiceArgRelation<T>(IoCContainer(), std::move(args)...));
		}

		virtual IAppBuilder &WithStartableService(std::unique_ptr<IServiceArg<std::shared_ptr<service::IStartableService>>>&& factory) = 0;
		virtual ioc::Container &IoCContainer() = 0;
	};
}

#endif //IOCSERVER_IAPPBUILDER_H
