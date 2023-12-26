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
		virtual std::string GetLastUpdateTime();
		virtual std::string GetCreationTime();
		virtual void StampCreationTime();
		virtual void StampLastUpdateTime();
		virtual std::string ConvertTimeToString(time_t time);
		virtual std::string RGBToHexString(int red, int green, int blue);
		ItemType GetType();

		bool operator==(const ModelItem& other) const
		{
			return uid == other.uid;
		}

		bool operator<(const ModelItem& other) const
		{
			return uid < other.uid;
		}

		bool operator<=(const ModelItem& other) const
		{
			return uid <= other.uid;
		}

		bool operator>(const ModelItem& other) const
		{
			return uid > other.uid;
		}

		bool operator>=(const ModelItem& other) const
		{
			return uid >= other.uid;
		}

		bool operator!=(const ModelItem& other) const
		{
			return uid != other.uid;
		}

		int uid;

	protected:
		
		ItemType m_type;
	};
}
