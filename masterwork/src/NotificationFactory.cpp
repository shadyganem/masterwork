#include "controller/NotificationFactory.h"

mw::NotificationFactory::NotificationFactory()
{
}

mw::NotificationFactory::NotificationFactory(const std::vector<mw::Task>& tasks)
{
	for (int i = 0; i < tasks.size(); i++)
	{
		m_tasks.push_back(tasks[i]);
	}
}

mw::NotificationFactory::~NotificationFactory()
{
}

void mw::NotificationFactory::SetTasks(const std::vector<mw::Task>& tasks)
{
	m_tasks.clear();
	for (int i = 0; i < tasks.size(); i++)
	{
		m_tasks.push_back(tasks[i]);
	}
}

void mw::NotificationFactory::GetNotifications(std::vector<mw::Notification>& notifications, SEARCH_FLAG search_flag)
{
	mw::Notification notification;

	mw::DateTime now;

	for (int i = 0; i < m_tasks.size(); i++)
	{
		if (search_flag | SEARCH_FLAG::DUE_IN_15_TASKS == 1)
		{
			if (m_tasks[i].deadline > now.m_time_t - 900)
			{
				notification.task_uid = m_tasks[i].uid;
				notification.text = "Due in 15: " + m_tasks[i].name;
				notifications.push_back(notification);
			}
		}
		if (search_flag | SEARCH_FLAG::IGNORED_TASKS == 1)
		{
			if (m_tasks[i].last_update < now.m_time_t - 2505600)
			{
				notification.task_uid = m_tasks[i].uid;
				notification.text = "Update Required: " + m_tasks[i].name;
				notifications.push_back(notification);
			}
		}
	}
}
