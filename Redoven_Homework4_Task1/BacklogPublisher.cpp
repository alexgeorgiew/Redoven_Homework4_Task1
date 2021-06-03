#include "BacklogPublisher.hpp"
#include <iostream>
void BacklogPublisher::subscribe(Averager* input)
{
	this->subscribers.push_back(input);
	for (int i = 0; i < this->old_messages.size(); i++)
	{
		this->subscribers[this->subscribers.size() - 1]->signal(this->old_messages[i]);
	}
}
void BacklogPublisher::subscribe(MovingAverager* input)
{
	this->subscribers.push_back(input);
	for (int i = 0; i < this->old_messages.size(); i++)
	{
		this->subscribers[this->subscribers.size() - 1]->signal(this->old_messages[i]);
	}
}
void BacklogPublisher::subscribe(PeriodicSampler* input)
{
	this->subscribers.push_back(input);
	for (int i = 0; i < this->old_messages.size(); i++)
	{
		this->subscribers[this->subscribers.size() - 1]->signal(this->old_messages[i]);
	}
}
void BacklogPublisher::unsubscribe(Averager* input)
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
void BacklogPublisher::unsubscribe(MovingAverager* input)
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
void BacklogPublisher::unsubscribe(PeriodicSampler* input)
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
void BacklogPublisher::signal(Message input)
{
	this->old_messages.push_back(input);
	for (int i = 0; i < this->subscribers.size(); i++)
	{
		this->subscribers[i]->signal(input);
	}
}