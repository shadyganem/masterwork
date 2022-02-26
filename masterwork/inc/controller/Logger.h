#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <fstream>
#include <mutex>
#include <ctime>
#include "wx/thread.h"

namespace mw
{ 
	enum LogLevel
	{
		DISABLE,
		INFO,
		WARNING,
		DEBUG
	};

	class Logger
	{
	public:
		Logger();
		Logger(std::string path);
		~Logger();
		void EnableDebug();
		void DisableDebug();
		void Clear();
		void Disable();
		void SetLogLevel(mw::LogLevel level);
		void SetFilePath(std::string path);
		void Info(std::string msg);
		void Error(std::string msg);
		void Warning(std::string msg);
		void Debug(std::string msg);
		static std::string filename;
		static std::string filepath;
		static std::mutex m_mutex;
		static mw::LogLevel m_log_level;
	public:
		std::ofstream m_file;

	private:
		bool m_debug;
		int m_thread_id;
	};
}




