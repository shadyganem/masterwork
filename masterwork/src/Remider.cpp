#include "model/Reminder.h"

mw::Reminder::Reminder()
{
	this->StampCreationTime();
}

mw::Reminder::~Reminder()
{
}

void mw::Reminder::Hash()
{
	this->hash = 0;
}

