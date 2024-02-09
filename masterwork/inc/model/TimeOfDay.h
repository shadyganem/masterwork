#pragma once
namespace mw
{
	class TimeOfDay
	{
	public:
		TimeOfDay(int hour, int minute, int second);
		TimeOfDay(int encoded_intger);
		int GetAsIntger();
		int GetHour();
		int GetMinitue();
		int GetSecond();
	private:
		int m_hour;
		int m_minute;
		int m_second;
		int m_encoded_integer;
	};
}


