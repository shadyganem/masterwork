#include "model/TimeOfDay.h"

mw::TimeOfDay::TimeOfDay(int hour, int minute, int second)
{
    this->m_hour = hour;
    this->m_minute = minute;
    this->m_second = second;
    m_encoded_integer = m_hour * 10000 + m_minute * 100 + m_second;
}

mw::TimeOfDay::TimeOfDay(int encoded_intger)
{
    m_hour = encoded_intger / 10000;
    m_minute = (encoded_intger / 100) % 100;
    m_second = encoded_intger % 100;
    m_encoded_integer = encoded_intger;
}

int mw::TimeOfDay::GetAsIntger()
{
    return m_encoded_integer;
}


int mw::TimeOfDay::GetHour()
{
    return m_hour;
}

int mw::TimeOfDay::GetMinitue()
{
    return m_minute;
}

int mw::TimeOfDay::GetSecond()
{
    return m_second;
}
