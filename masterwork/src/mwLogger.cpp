#include "controller/mwLogger.h"

std::string mwLogger::filename = "mw.log";
std::string mwLogger::filepath = "";
std::mutex mwLogger::m_mutex;


mwLogger::mwLogger()
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

mwLogger::mwLogger(std::string path)
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

mwLogger::~mwLogger()
{
	if (m_file.is_open())
		m_file.close();
}

void mwLogger::EnableDebug()
{
	this->m_debug = true;
}

void mwLogger::DisableDebug()
{
	this->m_debug = false;
}

void mwLogger::SetFilePath(std::string path)
{
	this->filepath = path;
}

void mwLogger::Info(std::string msg)
{
	std::time_t result = std::time(nullptr);
	std::string time = std::asctime(std::localtime(&result));
	time.pop_back();
	m_mutex.lock();
	m_file << "[INFO]:" << time << " - " << msg << std::endl;
	m_mutex.unlock();
}

void mwLogger::Error(std::string msg)
{
	std::time_t result = std::time(nullptr);
	std::string time = std::asctime(std::localtime(&result));
	time.pop_back();
	m_mutex.lock();
	m_file << "[Error]:" << time << " - " << msg << std::endl;
	m_mutex.unlock();
}

void mwLogger::Warning(std::string msg)
{
	std::time_t result = std::time(nullptr);
	std::string time = std::asctime(std::localtime(&result));
	time.pop_back();
	m_mutex.lock();
	m_file << "[Warning]:" << time << " - " << msg << std::endl;
	m_mutex.unlock();
}

void mwLogger::Debug(std::string msg)
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
