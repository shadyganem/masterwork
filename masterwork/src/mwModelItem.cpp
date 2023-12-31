#include "model/ModelItem.h"
#include <iostream>
#include <iomanip> // for setw
#include <sstream> // for stringstream
#include <chrono>

mw:: ModelItem::ModelItem()
{
	m_type = ItemType::ANY;
}

mw::ModelItem::~ModelItem()
{
}

std::string mw::ModelItem::GetLastUpdateTime()
{
	return this->ConvertTimeToString(this->last_update);
}

std::string mw::ModelItem::GetCreationTime()
{
	return this->ConvertTimeToString(this->creation_time);
}

void mw::ModelItem::StampCreationTime()
{
	std::time(&this->creation_time);
}

void mw::ModelItem::StampLastUpdateTime()
{
	std::time(&this->last_update);
}

std::string mw::ModelItem::ConvertTimeToString(time_t time)
{
	if (time < 0) {
		return "N/A";
	}
	try
	{
		std::chrono::system_clock::time_point timePoint = std::chrono::system_clock::from_time_t(time);
		std::time_t t = std::chrono::system_clock::to_time_t(timePoint);

		std::tm timeinfo;
#ifdef _WIN32
		localtime_s(&timeinfo, &t);
#else
		localtime_r(&t, &timeinfo);
#endif

		std::ostringstream oss;
		oss << std::put_time(&timeinfo, "%d-%m-%Y %H:%M:%S");

		return oss.str();
	}
	catch (...) 
	{
		return "N/A";
	}
	
}

std::string mw::ModelItem::RGBToHexString(int red, int green, int blue)
{
	std::stringstream ss;
	ss << std::uppercase << std::hex << std::setw(2) << std::setfill('0') << red
		<< std::setw(2) << green << std::setw(2) << blue;
	return "#" + ss.str();
	
}

ItemType mw::ModelItem::GetType()
{
	return this->m_type;
}

