//
// Created by max on 8/15/20.
//

#ifndef IOCSERVER_STRUCTS_H
#define IOCSERVER_STRUCTS_H

#include <mabiphmo/ioc-server/service/IStartableService.h>
#include <iostream>

class StartableServiceOne : public mabiphmo::ioc_server::service::IStartableService {
	bool &start_;
	bool &stop_;
protected:
	void onStart() override {
		std::cout << "One.onStart" << std::endl;
		start_ = true;
	}
	void onStop() override {
		std::cout << "One.onStop" << std::endl;
		stop_ = true;
	}
public:
	StartableServiceOne(bool &start, bool &stop) : start_(start), stop_(stop) {}
};

#endif //IOCSERVER_STRUCTS_H
