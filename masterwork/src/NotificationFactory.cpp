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
		if (search_flag & SEARCH_FLAG::DUE_IN_15 == SEARCH_FLAG::DUE_IN_15)
		{
			if (m_tasks[i].deadline > now.m_time_t - 900)
			{
				notification.task_uid = m_tasks[i].uid;
				notification.text = "Due in 15: " + m_tasks[i].name;
				notifications.push_back(notification);
			}
		}
		if (search_flag & SEARCH_FLAG::IGNORED == SEARCH_FLAG::IGNORED)
		{
			if (m_tasks[i].last_update < now.m_time_t - 432000)
			{
				notification.task_uid = m_tasks[i].uid;
				notification.text = "Update Required: " + m_tasks[i].name;
				notifications.push_back(notification);
			}
		}
	}
}

void mw::NotificationFactory::GetNotifications(std::vector<mw::Notification>& notifications, std::vector<mw::Task>& tasks, SEARCH_FLAG search_flag)
{
	mw::Notification notification;
	mw::DateTime now;

	for (int i = 0; i < tasks.size(); i++)
	{
		if (tasks[i].notification_enabled == true)
		{
			if (search_flag & SEARCH_FLAG::DUE_IN_15 == SEARCH_FLAG::DUE_IN_15)
			{
				if ((tasks[i].deadline < ((int)now.m_time_t + 900)) && (tasks[i].deadline >= now.m_time_t))
				{
					notification.task_uid = tasks[i].uid;
					notification.text = "Due in 15: " + tasks[i].name;
					notification.SetHashToken(tasks[i].deadline);
					notifications.push_back(notification);
				}
			}
			if (search_flag & SEARCH_FLAG::IGNORED == SEARCH_FLAG::IGNORED)
			{
				if (tasks[i].last_update < now.m_time_t - 432000)
				{
					notification.task_uid = tasks[i].uid;
					notification.text = "Update Required: " + tasks[i].name;
					notification.SetHashToken(tasks[i].last_update);
					notifications.push_back(notification);
				}
			}
		}
	}
}
