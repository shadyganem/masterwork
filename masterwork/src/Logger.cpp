#include "controller/Logger.h"
#include "..\inc\controller\Logger.h"

std::string mw::Logger::filename = "mw.log";
std::string mw::Logger::filepath = "";
std::mutex mw::Logger::m_mutex;
mw::LogLevel mw::Logger::m_log_level = mw::LogLevel::INFO;

mw::Logger::Logger()
{
	try
	{
		std::string full_file_name = this->filepath + "mw.log";
		m_file.open(full_file_name, std::ofstream::app);
		m_thread_id = wxThread::GetCurrentId();
	}
	catch (...)
	{
		;
	}	
}

mw::Logger::Logger(std::string path)
{
	filepath = path;
	try 
	{
		std::string full_file_name = this->filepath + "mw.log";
		m_file.open(full_file_name, std::ofstream::app);
		m_thread_id = wxThread::GetCurrentId();
	}
	catch (...)
	{
		;
	}
}

mw::Logger::~Logger()
{
	if (m_file.is_open())
		m_file.close();
}

void mw::Logger::EnableDebug()
{
	this->m_log_level = mw::LogLevel::DEBUG;
}

void mw::Logger::DisableDebug()
{
	this->m_debug = mw::LogLevel::DEBUG;
}

void mw::Logger::Clear()
{
	try
	{
		bool file_state = m_file.is_open();
		if (file_state)
			m_file.close();
		std::string full_file_name = this->filepath + "mw.log";
		m_file.open(full_file_name);
		m_file.close();
		if(file_state)
			m_file.open(full_file_name, std::ofstream::app);
	}
	catch (...)
	{
		;
	}
}

void mw::Logger::Disable()
{
	m_log_level = mw::LogLevel::DISABLE;
}

void mw::Logger::SetLogLevel(mw::LogLevel level)
{
	m_log_level = level;
}

void mw::Logger::SetFilePath(std::string path)
{
	this->filepath = path;
}

void mw::Logger::Info(std::string msg)
{
	if (m_log_level < mw::LogLevel::INFO)
		return;
	std::time_t result = std::time(nullptr);
	std::string time = std::asctime(std::localtime(&result));
	time.pop_back();
	m_mutex.lock();
	m_file << "[INFO]::" << m_thread_id << "::" << time << " - " << msg << std::endl;
	m_mutex.unlock();
}

void mw::Logger::Error(std::string msg)
{
	if (m_log_level < mw::LogLevel::WARNING)
		return;
	std::time_t result = std::time(nullptr);
	std::string time = std::asctime(std::localtime(&result));
	time.pop_back();
	m_mutex.lock();
	m_file << "[Error]::" << m_thread_id << "::" << time << " - " << msg << std::endl;
	m_mutex.unlock();
}

void mw::Logger::Warning(std::string msg)
{
	if (m_log_level < mw::LogLevel::WARNING)
		return;
	std::time_t result = std::time(nullptr);
	std::string time = std::asctime(std::localtime(&result));
	time.pop_back();
	m_mutex.lock();
	m_file << "[Warning]::" << m_thread_id << "::" << time << " - " << msg << std::endl;
	m_mutex.unlock();
}

void mw::Logger::Debug(std::string msg)
{
	if (m_log_level < mw::LogLevel::DEBUG)
		return;
	std::time_t result = std::time(nullptr);
	std::string time = std::asctime(std::localtime(&result));
	time.pop_back();
	m_mutex.lock();
	m_file << "[Debug]::" << m_thread_id << "::" << time << " - " << msg << std::endl;
	m_mutex.unlock();
}
