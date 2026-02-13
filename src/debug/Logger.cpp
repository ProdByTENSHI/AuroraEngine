#include "debug/Logger.hpp"

namespace Aurora {
	Logger& Logger::Instance() {
		static Logger instance;
		return instance;
	}

	Logger::Logger() {
		m_OutputFile.open(DEBUG_OUTPUT_PATH, std::ios::out | std::ios::trunc);

		// create a simple handler and subscribe it to the event
		auto _onLog = [this](LogMessage msg) {
			m_Thread = std::thread(&Logger::Process, this, msg);
			m_Thread.join();
		};
		m_OnLog += chroma::EventHandler<LogMessage>(_onLog);
	}

	Logger::~Logger() {
		if (m_Thread.joinable())
			m_Thread.join();

		m_OutputFile.close();
	}

	void Logger::Process(LogMessage msg) {
		switch (msg.m_Type) {
		case LogType::Message:
			m_OutputFile << "[LOG]: " << msg.m_Message << "\n";
			std::cout << "[LOG]: " << msg.m_Message << std::endl;
			break;

		case LogType::Error:
			m_OutputFile << "[ERROR]: " << msg.m_Message << "\n";
			std::cout << "[ERROR]: " << msg.m_Message << std::endl;
			exit((i32)msg.m_Type);
			break;

		case LogType::Warning:
			m_OutputFile << "[WARNING]: " << msg.m_Message << "\n";
			std::cout << "[WARNING]: " << msg.m_Message << std::endl;
			break;
		}
	}
}