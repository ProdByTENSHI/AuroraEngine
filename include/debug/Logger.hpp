#pragma once

#include <fstream>
#include <iostream>
#include <string_view>
#include <thread>

#include "globals/AuroraTypes.hpp"
#include "tenshiUtil/eventsystem/EventSystem.h"

namespace Aurora {
	constexpr charStr DEBUG_OUTPUT_PATH = "Log.txt";

	enum class LogType {
		Message = 0x0,
		Error = 0x1,
		Warning = 0x2
	};

	struct LogMessage {
	public:
		LogMessage(LogType type, charStr message)
			: m_Type(type), m_Message(message) {
		}

		LogType m_Type;
		charStr m_Message;
	};

	// -- I/O Debugging Tools run in a seperate Thread to reduce IO Blocking
	class Logger {
	public:
		static Logger& Instance();

		Logger();
		~Logger();

		void Log(const std::string& msg,
			LogType type = LogType::Message) {
			m_OnLog.Dispatch(LogMessage(type, msg.c_str()));
		}

	private:
		Aurora::Event<LogMessage> m_OnLog;

	private:
		void Process(LogMessage msg);

	private:
		std::thread m_Thread;
		std::ofstream m_OutputFile;
	};
}