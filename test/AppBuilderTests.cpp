//
// Created by max on 8/15/20.
//

#include <boost/test/unit_test.hpp>
#include "structs.h"
#include "../src/Server.h"
#include "../src/construction/AppBuilder.h"

BOOST_AUTO_TEST_SUITE(AppBuilder)

	BOOST_AUTO_TEST_CASE(buildServerAndDestruct)
	{
		bool start = false, stop = false;
		{
			std::shared_ptr<mabiphmo::iocServer::Server> server;
			{
				{
					mabiphmo::iocServer::construction::AppBuilder uut((mabiphmo::ioc::Container()));
					uut.WithService<StartableServiceOne>(static_cast<bool&>(start), static_cast<bool&>(stop));
					server = uut.Build();
				}
				server->Start();
				BOOST_TEST(start);
			}
		}
		BOOST_TEST(stop);
	}

BOOST_AUTO_TEST_SUITE_END()