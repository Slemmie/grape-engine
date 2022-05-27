#pragma once

#include "thread_pool.cpp"
#include <iostream>
#include <vector>
#include <memory>
#include <functional>

namespace ge{

	static Thread_pool pool = Thread_pool(10);
	
	template <typename... ARGS> class Event {
		public:
			void callback(ARGS&&... args) {
				for (int i = 0; i < (int)functions.size(); ++i) {
					if (*functions[i] != nullptr) {
						pool.push(*functions[i],args...);
					}
					else{
						delete_function(functions[i]);
						i--;
					}
				}
			}

			void push(const std::shared_ptr <std::function <void (ARGS...)>>& func) {
				functions.emplace_back(func);
			}

			void delete_function(std::shared_ptr<std::function<void (ARGS...)>>& func) {
				swap(functions.back(),func);
				functions.pop_back();
			}

			int getsize() { return functions.size(); }


		protected:
			std::vector<std::shared_ptr<std::function <void(ARGS...)>>> functions; 
	};


}


