#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <fstream>
#include <mutex>
#include <ctime>

class mwLogger
{
public:
	mwLogger();
	mwLogger(std::string path);
	~mwLogger();
	void SetFilePath(std::string path);
	void Info(std::string msg);
	void Error(std::string msg);
	void Warning(std::string msg);
	static std::string filename;
	static std::string filepath;
public:
	std::ofstream m_file;
	std::mutex m_mutex;
};


