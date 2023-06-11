#pragma once
#include "model/ModelItem.h"
#include <string>
#include <sstream>
#include <ctime>

namespace mw
{
	class Task : public ModelItem
	{
	public:

		enum TaskStatus
		{
			NOTSTARTED,
			WIP,
			CANCELED,
			DONE,
			BLOCKED,
			DELETED = -1
		};

		enum TaskPriority
		{
			HIGH,
			MEDIUM,
			LOW,
			SHOWSTOPPER
		};

	public:
		Task(std::string name, std::string dec);
		Task();
		~Task();
		void StampCreationTime();
		void StampLastUpdateTime();
		void StampEndTime();
		void SetProjectId(int id);
		std::string GetStatus();
		std::string GetPriority();
		std::string GetLastUpdate();
		std::string GetEndTime();

		int uid;
		int parent_uid;
		std::string name;
		std::string description;
		int status;
		int priority;
		std::time_t start_time;
		std::time_t last_update;
		std::time_t end_time;
		std::time_t deadline;
		int project_uid;
		int red;
		int green;
		int blue;
		bool notification_enabled;

	};
}


