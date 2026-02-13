#include "debug/Logger.hpp"

namespace Aurora {
	Logger& Logger::Instance() {
		static Logger instance;
		return instance;
	}

	Logger::Logger() {
		// start the processing thread (bind member function to this)

		// create a simple handler and subscribe it to the event
		auto _onLog = [this](LogMessage msg) {
			m_Thread = std::thread(&Logger::Process, this, msg);
			m_Thread.join();
		};
		m_OnLog += chroma::EventHandler<LogMessage>(_onLog);
	}

	void Logger::Log(charStr msg, LogType type)
	{
		m_OnLog.Dispatch(LogMessage(type, msg));
	}

	void Logger::Process(LogMessage msg) {
		switch (msg.m_Type) {
		case LogType::Message:
			std::cout << "[LOG]: " << msg.m_Message << std::endl;
			break;

		case LogType::Error:
			std::cout << "[ERROR]: " << msg.m_Message << std::endl;
			break;

		case LogType::Warning:
			std::cout << "[WARNING]: " << msg.m_Message << std::endl;
			break;
		}
	}
}