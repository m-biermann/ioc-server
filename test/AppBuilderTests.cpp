//
// Created by max on 8/15/20.
//

#include <boost/test/unit_test.hpp>
#include "structs.h"
#include "../src/Server.h"
#include "../src/construction/AppBuilder.h"

using namespace mabiphmo::iocServer;
using namespace mabiphmo::ioc_container;

BOOST_AUTO_TEST_SUITE(AppBuilder)

	BOOST_AUTO_TEST_CASE(buildServerAndDestruct)
	{
		bool start = false, stop = false;
		{
			std::shared_ptr<mabiphmo::iocServer::Server> server;
			{
				{
					mabiphmo::iocServer::construction::AppBuilder uut((Container()));
					auto holder = uut.IoCContainer().RegisterType(TypeHolder<StartableServiceOne>(Scope::Singleton, std::function<std::shared_ptr<StartableServiceOne>()>([&start, &stop](){return std::make_shared<StartableServiceOne>(start, stop);})));
					uut.WithStartableService([holder](){return std::dynamic_pointer_cast<service::IStartableService>(holder->Get());});
					server = uut.Build();
				}
				server->Start();
				BOOST_TEST(start);
			}
		}
		BOOST_TEST(stop);
	}

BOOST_AUTO_TEST_SUITE_END()