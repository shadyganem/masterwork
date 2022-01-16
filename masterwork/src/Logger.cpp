#include "controller/Logger.h"

std::string mw::Logger::filename = "mw.log";
std::string mw::Logger::filepath = "";
std::mutex mw::Logger::m_mutex;


mw::Logger::Logger()
{
	try
	{
		std::string full_file_name = this->filepath + "mw.log";
		m_file.open(full_file_name, std::ofstream::app);
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
	this->m_debug = true;
}

void mw::Logger::DisableDebug()
{
	this->m_debug = false;
}

void mw::Logger::SetFilePath(std::string path)
{
	this->filepath = path;
}

void mw::Logger::Info(std::string msg)
{
	std::time_t result = std::time(nullptr);
	std::string time = std::asctime(std::localtime(&result));
	time.pop_back();
	m_mutex.lock();
	m_file << "[INFO]:" << time << " - " << msg << std::endl;
	m_mutex.unlock();
}

void mw::Logger::Error(std::string msg)
{
	std::time_t result = std::time(nullptr);
	std::string time = std::asctime(std::localtime(&result));
	time.pop_back();
	m_mutex.lock();
	m_file << "[Error]:" << time << " - " << msg << std::endl;
	m_mutex.unlock();
}

void mw::Logger::Warning(std::string msg)
{
	std::time_t result = std::time(nullptr);
	std::string time = std::asctime(std::localtime(&result));
	time.pop_back();
	m_mutex.lock();
	m_file << "[Warning]:" << time << " - " << msg << std::endl;
	m_mutex.unlock();
}

void mw::Logger::Debug(std::string msg)
{
	if (!this->m_debug)
		return;
	std::time_t result = std::time(nullptr);
	std::string time = std::asctime(std::localtime(&result));
	time.pop_back();
	m_mutex.lock();
	m_file << "[Debug]:" << time << " - " << msg << std::endl;
	m_mutex.unlock();
}
