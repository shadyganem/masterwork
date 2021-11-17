#include "model/mwModelItem.h"

mwModelItem::mwModelItem()
{
	m_type = ItemType::ANY;
}

mwModelItem::~mwModelItem()
{
}

ItemType mwModelItem::GetType()
{
	return this->m_type;
}

