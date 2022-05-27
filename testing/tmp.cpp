// temporary file .. remove soon :)

#include <grape_engine.h>

#include <iostream>

void ON_GE_INIT() {
	std::cerr << "on init called..." << std::endl;
	
	ge::engine& inst = ge::engine::instance();
}
