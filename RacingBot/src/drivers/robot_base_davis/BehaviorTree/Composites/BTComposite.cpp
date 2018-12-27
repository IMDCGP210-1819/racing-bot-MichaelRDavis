#include "BTComposite.h"

BTComposite::BTComposite()
	: it(m_Children.begin())
{

}

BTComposite::~BTComposite()
{
	m_Children.clear();
}

void BTComposite::InsertChildNode(std::shared_ptr<BTTask> NewTaskNode)
{
	m_Children.push_back(NewTaskNode);
}
