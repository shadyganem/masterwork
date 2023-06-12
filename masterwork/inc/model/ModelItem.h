#pragma once

#include <ctime>
#include <string>

enum ItemType
{
	ANY,
	USER,
	PROJECT,
	TASK,
	NOTIFICATION
};

namespace mw
{
	class ModelItem
	{
	public:
		ModelItem();
		~ModelItem();
	public:
		std::time_t creation_time;
		std::time_t last_update;
	public:
		virtual void StampCreationTime();
		virtual void StampLastUpdateTime();
		virtual std::string ConvertTimeToString(time_t time);
		ItemType GetType();

	protected:
		
		ItemType m_type;
	};
}
