//
// Created by max on 8/14/20.
//

#define BOOST_TEST_MODULE iocServer
#include <boost/test/unit_test.hpp>
#include "../src/Server.h"
#include "structs.h"

BOOST_AUTO_TEST_SUITE(Server)

	BOOST_AUTO_TEST_CASE(registerOneServiceStartAndStop)
	{
		bool start1 = false, stop1 = false;
		std::shared_ptr<StartableServiceOne> service1 = std::make_shared<StartableServiceOne>(start1, stop1);
		mabiphmo::iocServer::Server uut = mabiphmo::iocServer::Server(std::make_shared<mabiphmo::iocServer::ThreadRunner>(std::make_shared<boost::asio::io_context>(1), 1),
				std::vector<std::shared_ptr<mabiphmo::iocServer::service::IStartableService>>{
						std::dynamic_pointer_cast<mabiphmo::iocServer::service::IStartableService>(service1)});
		uut.Start();
		BOOST_TEST(start1);
		uut.Stop();
		BOOST_TEST(stop1);
	}

	BOOST_AUTO_TEST_CASE(registerMultipleServicesStartAndStop)
	{
		bool start1 = false, stop1 = false, start2 = false, stop2 = false;
		std::shared_ptr<StartableServiceOne> service1 = std::make_shared<StartableServiceOne>(start1, stop1);
		std::shared_ptr<StartableServiceOne> service2 = std::make_shared<StartableServiceOne>(start2, stop2);
		mabiphmo::iocServer::Server uut = mabiphmo::iocServer::Server(std::make_shared<mabiphmo::iocServer::ThreadRunner>(std::make_shared<boost::asio::io_context>(1), 1),
				std::vector<std::shared_ptr<mabiphmo::iocServer::service::IStartableService>>{
						std::dynamic_pointer_cast<mabiphmo::iocServer::service::IStartableService>(service1),
						std::dynamic_pointer_cast<mabiphmo::iocServer::service::IStartableService>(service2)});
		uut.Start();
		BOOST_TEST(start1);
		BOOST_TEST(start2);
		uut.Stop();
		BOOST_TEST(stop1);
		BOOST_TEST(stop2);
	}

	BOOST_AUTO_TEST_CASE(registerMultipleServicesStopOnDestruct)
	{
		bool start1 = false, stop1 = false, start2 = false, stop2 = false;
		std::shared_ptr<StartableServiceOne> service1 = std::make_shared<StartableServiceOne>(start1, stop1);
		std::shared_ptr<StartableServiceOne> service2 = std::make_shared<StartableServiceOne>(start2, stop2);
		{
			mabiphmo::iocServer::Server uut = mabiphmo::iocServer::Server(std::make_shared<mabiphmo::iocServer::ThreadRunner>(std::make_shared<boost::asio::io_context>(1), 1),
					std::vector<std::shared_ptr<mabiphmo::iocServer::service::IStartableService>>{
							std::dynamic_pointer_cast<mabiphmo::iocServer::service::IStartableService>(service1),
							std::dynamic_pointer_cast<mabiphmo::iocServer::service::IStartableService>(service2)});
			uut.Start();
			BOOST_TEST(start1);
			BOOST_TEST(start2);
		}
		BOOST_TEST(stop1);
		BOOST_TEST(stop2);
	}

BOOST_AUTO_TEST_SUITE_END()