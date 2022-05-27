#include "core.h"

#include "main_application.h"

namespace ge {
	
	void m_destruct_engine(Engine& engine_instance) noexcept {
		
	}
	
} /// namespace ge

int main() {
	ge::Engine& engine_instance = ge::Engine::instance();
	engine_instance.run();
	ge::m_destruct_engine(engine_instance);
}
