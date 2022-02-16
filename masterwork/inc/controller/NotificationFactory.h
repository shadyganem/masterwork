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
			IGNORED = (1 << 0),
			DUE_IN_15 = (1 << 1),
			ALL = IGNORED | DUE_IN_15
		};
	public:
		NotificationFactory();
		NotificationFactory(const std::vector<mw::Task>& tasks);
		~NotificationFactory();
		void SetTasks(const std::vector<mw::Task>& tasks);

		void GetNotifications(std::vector<mw::Notification>& notifications, SEARCH_FLAG search_flag=ALL);
		static void GetNotifications(std::vector<mw::Notification>& notifications, std::vector<mw::Task>& tasks, SEARCH_FLAG search_flag = ALL);

	private:
		std::vector<mw::Task> m_tasks;
	};
}


