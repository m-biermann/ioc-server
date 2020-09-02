//
// Created by max on 8/28/20.
//

#ifndef IOCSERVER_ISERVICEARG_H
#define IOCSERVER_ISERVICEARG_H

namespace mabiphmo::iocServer::construction {
	template <class ArgType>
	class IServiceArg
	{
	public:
		virtual ArgType operator()() = 0;
	};

}

#endif //IOCSERVER_ISERVICEARG_H
