#include "BTParallel.h"

BTParallel::BTParallel(EPolicy Success, EPolicy Failure)
	: m_SuccessPolicy(Success)
	, m_FailurePolicy(Failure)
{

}

BTParallel::~BTParallel()
{

}

EStatus BTParallel::OnUpdate()
{
	size_t SuccessCount = 0;
	size_t FailureCount = 0;

	for (it = m_Children.begin(); it != m_Children.end(); ++it)
	{
		auto& Task = **it;
		if (!Task.IsTerminated())
		{
			Task.Tick();
		}

		if (Task.GetStatus() == EStatus::ESuccess)
		{
			++SuccessCount;
			if (m_SuccessPolicy == EPolicy::ERequireOne)
			{
				return EStatus::ESuccess;
			}
		}

		if (Task.GetStatus() == EStatus::EFailure)
		{
			++FailureCount;
			if (m_FailurePolicy == EPolicy::ERequireOne)
			{
				return EStatus::EFailure;
			}
		}
	}

	if (m_FailurePolicy == EPolicy::ERequireAll && FailureCount == m_Children.size())
	{
		return EStatus::EFailure;
	}

	if (m_SuccessPolicy == EPolicy::ERequireAll && SuccessCount == m_Children.size())
	{
		return EStatus::ESuccess;
	}

	return EStatus::ERunning;
}

void BTParallel::OnTerminate(EStatus status)
{
	for (it = m_Children.begin(); it != m_Children.end(); ++it)
	{
		auto& Task = **it;
		if (Task.IsRunning())
		{
			Task.Abort();
		}
	}
}
