#include "model/ModelItem.h"

mw:: ModelItem::ModelItem()
{
	m_type = ItemType::ANY;
}

mw::ModelItem::~ModelItem()
{
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

ItemType mw::ModelItem::GetType()
{
	return this->m_type;
}

