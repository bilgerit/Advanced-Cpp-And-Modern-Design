// Observable ABC
// Tobias Bilgeri, 11.02.2024
#pragma once
#include <vector>
class Observer;

class Observable
{
private:
	std::vector<Observer*> observers_;
public:
	void AddObserver(Observer* obs);
	void DeleteObserver(Observer* obs);
	void NotifyObservers() const;

	virtual ~Observable() {}
};