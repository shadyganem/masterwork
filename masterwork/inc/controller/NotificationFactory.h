#pragma once

#include "model/Task.h"
#include "model/Notification.h"
#include <vector>
#include <model/DateTime.h>

namespace mw
{
	class NotificationFactory
	{
	public:
		enum SEARCH_FLAG
		{
			IGNORED_TASKS = (1 << 0),
			DUE_IN_15_TASKS = (1 << 1),
			ALL = IGNORED_TASKS | DUE_IN_15_TASKS
		};
	public:
		NotificationFactory();
		NotificationFactory(const std::vector<mw::Task>& tasks);
		~NotificationFactory();
		void SetTasks(const std::vector<mw::Task>& tasks);

		void GetNotifications(std::vector<mw::Notification>& notifications, SEARCH_FLAG search_flag=ALL);

	private:
		std::vector<mw::Task> m_tasks;
	};
}


