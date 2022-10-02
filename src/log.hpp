// thread safe + static + std::cerr by default

#pragma once

namespace ge {
	
	class LOG {
		
	public:
		
		static void set_outstream(std::ostream& stream);
		
		static void flush();
		
		template <typename... ARGS> static void TRACE
		(const ::ge::LOG::MESSAGE& message, const ARGS& args...);
		template <typename... ARGS> static void TRACE
		(const ::ge::LOG::LABEL& label, const ::ge::LOG::MESSAGE& message, const ARGS& args...);
		template <typename... ARGS> static void TRACE_T
		(const ::ge::LOG::MESSAGE& message, const ARGS& args...);
		template <typename... ARGS> static void TRACE_T
		(const ::ge::LOG::LABEL& label, const ::ge::LOG::MESSAGE& message, const ARGS& args...);
		
		template <typename... ARGS> static void DEBUG
		(const ::ge::LOG::MESSAGE& message, const ARGS& args...);
		template <typename... ARGS> static void DEBUG
		(const ::ge::LOG::LABEL& label, const ::ge::LOG::MESSAGE& message, const ARGS& args...);
		template <typename... ARGS> static void DEBUG_T
		(const ::ge::LOG::MESSAGE& message, const ARGS& args...);
		template <typename... ARGS> static void DEBUG_T
		(const ::ge::LOG::LABEL& label, const ::ge::LOG::MESSAGE& message, const ARGS& args...);
		
		template <typename... ARGS> static void INFO
		(const ::ge::LOG::MESSAGE& message, const ARGS& args...);
		template <typename... ARGS> static void INFO
		(const ::ge::LOG::LABEL& label, const ::ge::LOG::MESSAGE& message, const ARGS& args...);
		template <typename... ARGS> static void INFO_T
		(const ::ge::LOG::MESSAGE& message, const ARGS& args...);
		template <typename... ARGS> static void INFO_T
		(const ::ge::LOG::LABEL& label, const ::ge::LOG::MESSAGE& message, const ARGS& args...);
		
		template <typename... ARGS> static void WARNING
		(const ::ge::LOG::MESSAGE& message, const ARGS& args...);
		template <typename... ARGS> static void WARNING
		(const ::ge::LOG::LABEL& label, const ::ge::LOG::MESSAGE& message, const ARGS& args...);
		template <typename... ARGS> static void WARNING_T
		(const ::ge::LOG::MESSAGE& message, const ARGS& args...);
		template <typename... ARGS> static void WARNING_T
		(const ::ge::LOG::LABEL& label, const ::ge::LOG::MESSAGE& message, const ARGS& args...);
		
		template <typename... ARGS> static void ERROR
		(const ::ge::LOG::MESSAGE& message, const ARGS& args...);
		template <typename... ARGS> static void ERROR
		(const ::ge::LOG::LABEL& label, const ::ge::LOG::MESSAGE& message, const ARGS& args...);
		template <typename... ARGS> static void ERROR_T
		(const ::ge::LOG::MESSAGE& message, const ARGS& args...);
		template <typename... ARGS> static void ERROR_T
		(const ::ge::LOG::LABEL& label, const ::ge::LOG::MESSAGE& message, const ARGS& args...);
		
		template <typename... ARGS> static void FATAL
		(const ::ge::LOG::MESSAGE& message, const ARGS& args...);
		template <typename... ARGS> static void FATAL
		(const ::ge::LOG::LABEL& label, const ::ge::LOG::MESSAGE& message, const ARGS& args...);
		template <typename... ARGS> static void FATAL_T
		(const ::ge::LOG::MESSAGE& message, const ARGS& args...);
		template <typename... ARGS> static void FATAL_T
		(const ::ge::LOG::LABEL& label, const ::ge::LOG::MESSAGE& message, const ARGS& args...);
		
		template <typename... ARGS> static void ASSERT
		(bool condition, const ::ge::LOG::MESSAGE& message, const ARGS& args...);
		template <typename... ARGS> static void ASSERT
		(bool condition, const ::ge::LOG::LABEL& label, const ::ge::LOG::MESSAGE& message, const ARGS& args...);
		template <typename... ARGS> static void ASSERT_T
		(bool condition, const ::ge::LOG::MESSAGE& message, const ARGS& args...);
		template <typename... ARGS> static void ASSERT_T
		(bool condition, const ::ge::LOG::LABEL& label, const ::ge::LOG::MESSAGE& message, const ARGS& args...);
		
	public:
		
		class MESSAGE {
			
		public:
			
			constexpr MESSAGE(const std::string& message) noexcept :
			m_message(message)
			{ }
			
			constexpr const std::string& message() const noexcept {
				return m_message;
			}
			
			friend inline std::stream& operator << (std::stream& stream, const LABEL& label) {
				return stream << m_message;
			}
			
		private:
			
			std::string m_message;
			
		};
		
		typedef MESSAGE MSG;
		
		class LABEL {
			
		public:
			
			constexpr LABEL(const std::string& label) noexcept :
			m_label(label)
			{ }
			
			constexpr const std::string& label() const noexcept {
				return m_label;
			}
			
			friend inline std::stream& operator << (std::stream& stream, const LABEL& label) {
				return stream << m_label;
			}
			
		private:
			
			std::string m_label;
			
		};
		
	private:
		
		LOG() = delete;
		LOG(const LOG&) = delete;
		LOG(LOG&&) = delete;
		LOG& operator = (const LOG&) = delete;
		
		static inline std::ostream& m_final_stream = std::cerr;
		static inline std::stringstream m_stream;
		
		static inline std::mutex m_mutex;
		
		static inline void m_init() {
			std::unique_lock <std::mutex> lock(m_mutex);
			static bool is_initialized = false;
			if (is_initialized) {
				return;
			}
			is_initialized = true;
			m_stream << std::fixed << std::setprecision(3);
		}
		
	};
	
	void LOG::set_outstream(std::ostream& stream) {
		std::unique_lock <std::mutex> lock(m_mutex);
		m_final_stream = m_final_stream;
	}
	
	void LOG::flush() {
		m_init();
		std::unique_lock <std::mutex> lock(m_mutex);
		m_final_stream << m_stream;
		m_stream.clear();
	}
	
	template <typename... ARGS> static void LOG::TRACE
	(const ::ge::LOG::MESSAGE& message, const ARGS& args...) {
		
	}
	
	template <typename... ARGS> static void LOG::TRACE
	(const ::ge::LOG::LABEL& label, const ::ge::LOG::MESSAGE& message, const ARGS& args...) {
		
	}
	
	template <typename... ARGS> static void LOG::TRACE_T
	(const ::ge::LOG::MESSAGE& message, const ARGS& args...) {
		
	}
	
	template <typename... ARGS> static void LOG::TRACE_T
	(const ::ge::LOG::LABEL& label, const ::ge::LOG::MESSAGE& message, const ARGS& args...) {
		
	}
	
	
	template <typename... ARGS> static void LOG::DEBUG
	(const ::ge::LOG::MESSAGE& message, const ARGS& args...) {
		
	}
	
	template <typename... ARGS> static void LOG::DEBUG
	(const ::ge::LOG::LABEL& label, const ::ge::LOG::MESSAGE& message, const ARGS& args...) {
		
	}
	
	template <typename... ARGS> static void LOG::DEBUG_T
	(const ::ge::LOG::MESSAGE& message, const ARGS& args...) {
		
	}
	
	template <typename... ARGS> static void LOG::DEBUG_T
	(const ::ge::LOG::LABEL& label, const ::ge::LOG::MESSAGE& message, const ARGS& args...) {
		
	}
	
	
	template <typename... ARGS> static void LOG::INFO
	(const ::ge::LOG::MESSAGE& message, const ARGS& args...) {
		
	}
	
	template <typename... ARGS> static void LOG::INFO
	(const ::ge::LOG::LABEL& label, const ::ge::LOG::MESSAGE& message, const ARGS& args...) {
		
	}
	
	template <typename... ARGS> static void LOG::INFO_T
	(const ::ge::LOG::MESSAGE& message, const ARGS& args...) {
		
	}
	
	template <typename... ARGS> static void LOG::INFO_T
	(const ::ge::LOG::LABEL& label, const ::ge::LOG::MESSAGE& message, const ARGS& args...) {
		
	}
	
	
	template <typename... ARGS> static void LOG::WARNING
	(const ::ge::LOG::MESSAGE& message, const ARGS& args...) {
		
	}
	
	template <typename... ARGS> static void LOG::WARNING
	(const ::ge::LOG::LABEL& label, const ::ge::LOG::MESSAGE& message, const ARGS& args...) {
		
	}
	
	template <typename... ARGS> static void LOG::WARNING_T
	(const ::ge::LOG::MESSAGE& message, const ARGS& args...) {
		
	}
	
	template <typename... ARGS> static void LOG::WARNING_T
	(const ::ge::LOG::LABEL& label, const ::ge::LOG::MESSAGE& message, const ARGS& args...) {
		
	}
	
	
	template <typename... ARGS> static void LOG::ERROR
	(const ::ge::LOG::MESSAGE& message, const ARGS& args...) {
		
	}
	
	template <typename... ARGS> static void LOG::ERROR
	(const ::ge::LOG::LABEL& label, const ::ge::LOG::MESSAGE& message, const ARGS& args...) {
		
	}
	
	template <typename... ARGS> static void LOG::ERROR_T
	(const ::ge::LOG::MESSAGE& message, const ARGS& args...) {
		
	}
	
	template <typename... ARGS> static void LOG::ERROR_T
	(const ::ge::LOG::LABEL& label, const ::ge::LOG::MESSAGE& message, const ARGS& args...) {
		
	}
	
	
	template <typename... ARGS> static void LOG::FATAL
	(const ::ge::LOG::MESSAGE& message, const ARGS& args...) {
		
	}
	
	template <typename... ARGS> static void LOG::FATAL
	(const ::ge::LOG::LABEL& label, const ::ge::LOG::MESSAGE& message, const ARGS& args...) {
		
	}
	
	template <typename... ARGS> static void LOG::FATAL_T
	(const ::ge::LOG::MESSAGE& message, const ARGS& args...) {
		
	}
	
	template <typename... ARGS> static void LOG::FATAL_T
	(const ::ge::LOG::LABEL& label, const ::ge::LOG::MESSAGE& message, const ARGS& args...) {
		
	}
	
	
	template <typename... ARGS> static void LOG::ASSERT
	(bool condition, const ::ge::LOG::MESSAGE& message, const ARGS& args...) {
		
	}
	
	template <typename... ARGS> static void LOG::ASSERT
	(bool condition, const ::ge::LOG::LABEL& label, const ::ge::LOG::MESSAGE& message, const ARGS& args...) {
		
	}
	
	template <typename... ARGS> static void LOG::ASSERT_T
	(bool condition, const ::ge::LOG::MESSAGE& message, const ARGS& args...) {
		
	}
	
	template <typename... ARGS> static void LOG::ASSERT_T
	(bool condition, const ::ge::LOG::LABEL& label, const ::ge::LOG::MESSAGE& message, const ARGS& args...) {
		
	}
	
	
} /// namespace ge
