#pragma once

#include <ctime>

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
	public:
		virtual void StampCreationTime();
		ItemType GetType();

	protected:
		
		ItemType m_type;
	};
}
