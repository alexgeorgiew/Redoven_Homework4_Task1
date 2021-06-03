#include "SimplePublisher.hpp"
#include <iostream>
void SimplePublisher::subscribe(Averager* input)
{
	this->subscribers.push_back(input);
}
void SimplePublisher::subscribe(MovingAverager* input)
{
	this->subscribers.push_back(input);
}
void SimplePublisher::subscribe(PeriodicSampler* input)
{
	this->subscribers.push_back(input);
}
void SimplePublisher::unsubscribe(Averager* input)
{
	for (int i = 0; i < this->subscribers.size(); i++)
	{
		if (this->subscribers[i]->id == input->id)
		{
			this->subscribers.erase(this->subscribers.begin() + i);
			return;
		}
	}
}
void SimplePublisher::unsubscribe(MovingAverager* input)
{
	for (int i = 0; i < this->subscribers.size(); i++)
	{
		if (this->subscribers[i]->id == input->id)
		{
			this->subscribers.erase(this->subscribers.begin() + i);
			return;
		}
	}
}
void SimplePublisher::unsubscribe(PeriodicSampler* input)
{
	for (int i = 0; i < this->subscribers.size(); i++)
	{
		if (this->subscribers[i]->id == input->id)
		{
			this->subscribers.erase(this->subscribers.begin() + i);
			return;
		}
	}
}
void SimplePublisher::signal(Message input)
{
	for (int i = 0; i < this->subscribers.size(); i++)
	{
		this->subscribers[i]->signal(input);
	}
}