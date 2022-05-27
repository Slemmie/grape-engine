#include "main_application.h"

#include <cassert>

namespace ge {
	
	void m_destruct_engine(engine& engine_instance) noexcept {
		
	}
	
} /// namespace ge

int main() {
	ge::engine& engine_instance = ge::engine::instance();
	engine_instance.run();
	ge::m_destruct_engine(engine_instance);
}
