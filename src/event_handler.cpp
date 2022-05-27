#include "event_handler.h"

class MOUSE_LEFT_CLICK : public ge::Event <int, int> { };
class MOUSE_RIGHT_CLICK : public ge::Event <int, int> { };

void f(int x, int y) {
    std::cerr << x << " and " << y << std::endl;
}

