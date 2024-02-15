// Tobias Bilgeri, 11.02.2024
#include "Observable.h"
#include "Observer.h"

void Observable::AddObserver(Observer* obs)
{
	observers_.push_back(obs);
};

void Observable::DeleteObserver(Observer* obs)
{
	std::erase(observers_, obs);
};

void Observable::NotifyObservers() const
{
	for (Observer* p : observers_)
	{
		p->Update();
	}
};
