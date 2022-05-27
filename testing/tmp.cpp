// temporary file .. remove soon :)

#include <grape_engine.h>
#include "../src/thread_pool.h"
#include "../src/event_handler.h"

#include <iostream>
#include <string.h>

void a(std::string l) {
	std::cerr << l + " called\n";
}

void b() {
	std::cerr << "Yeehaw!!!\n";
}

class E1 : public ge::Event <int, int> { };

void f(int x, int y) {
    std::cerr << x << " and " << y << std::endl;
}

void ON_GE_INIT() {
	std::cerr << "on init called..." << std::endl;
	
	ge::Engine& inst = ge::Engine::instance();

	ge::Thread_pool& pool = ge::Thread_pool::instance();
	std::string e = "abc";
	for(int i = 0; i < 30; i++) {
		pool.push(a, e.substr(i%3,1));
	}
	pool.push(b);

	E1 event;
	auto ptr = std::make_shared <std::function <void (int, int)>> (f);
	event.push(ptr);
	event.callback(3, 5);

	while(true);
}

