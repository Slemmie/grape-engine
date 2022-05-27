#include "event_handler.h"

class MOUSE_LEFT_CLICK : public ge::Event <int, int> { };
class MOUSE_RIGHT_CLICK : public ge::Event <int, int> { };

void f(int x, int y) {
    std::cerr << x << " and " << y << std::endl;
}

int main() {
	MOUSE_LEFT_CLICK event;
	auto ptr = std::make_shared <std::function <void (int, int)>> (f);
	event.push(ptr);
	event.callback(3,5);
}
