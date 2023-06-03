#pragma once
#include "model/ModelItem.h"
#include <string>
#include <ctime>


namespace mw
{
	class Project : public ModelItem
	{
	public:
		enum ProjectStatus
		{
			DELETED = -1,
			DEFAULT
		};

	public:
		Project();
		Project(std::string name);
		~Project();
		void ChangeName(std::string new_name);
		std::time_t start_time;
		std::string name;
		int uid;
		int user_uid;
		int status;
		bool is_active;
		void StampCreationTime() override;
	};
}
