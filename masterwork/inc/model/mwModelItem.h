#pragma once

enum ItemType
{
	ANY,
	USER,
	PROJECT,
	TASK
};

class mwModelItem
{
public:
	mwModelItem();
	~mwModelItem();
public:

public:

	ItemType GetType();
	
protected:
	ItemType m_type;
};

