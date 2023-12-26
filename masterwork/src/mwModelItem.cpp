#include "model/ModelItem.h"
#include <iostream>
#include <iomanip> // for setw
#include <sstream> // for stringstream

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
	if (time < 0)
	{
		return "N/A";
	}
	// Convert the epoch timestamp to a struct tm
	std::tm timeinfo;
	#ifdef _WIN32
		localtime_s(&timeinfo, &time);
	#else
		localtime_r(&now, &localTime);
	#endif
	// Format the date and time as a string
	char buffer[80];
	std::strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", &timeinfo);
	std::string string_time = buffer;
	return string_time;
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

