#include "model/ModelItem.h"

mw:: ModelItem::ModelItem()
{
	m_type = ItemType::ANY;
}

mw::ModelItem::~ModelItem()
{
}

void mw::ModelItem::StampCreationTime()
{
	std::time(&this->creation_time);
}

ItemType mw::ModelItem::GetType()
{
	return this->m_type;
}

