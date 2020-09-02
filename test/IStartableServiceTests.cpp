//
// Created by max on 8/15/20.
//

#include <boost/test/unit_test.hpp>
#include "structs.h"

BOOST_AUTO_TEST_SUITE(IStartableService)

	BOOST_AUTO_TEST_CASE(startTwice)
	{
		bool start, stop;
		StartableServiceOne uut(start, stop);
		uut.Start();
		BOOST_TEST(start);
		start = false;
		uut.Start();
		BOOST_TEST(!start);
	}

	BOOST_AUTO_TEST_CASE(stopTwice)
	{
		bool start, stop;
		StartableServiceOne uut(start, stop);
		uut.Start();
		uut.Stop();
		BOOST_TEST(stop);
		stop = false;
		uut.Stop();
		BOOST_TEST(!stop);
	}

BOOST_AUTO_TEST_SUITE_END()