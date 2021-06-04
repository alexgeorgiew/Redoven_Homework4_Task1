#include "BacklogPublisher.hpp"
#include <iostream>
BacklogPublisher::BacklogPublisher() :SimplePublisher()
{

}
/*BacklogPublisher::~BacklogPublisher()
{
	SimplePublisher::~SimplePublisher();
}*/
BacklogPublisher::BacklogPublisher(const BacklogPublisher& input):SimplePublisher(input),old_messages(input.old_messages)
{
	
}
BacklogPublisher& BacklogPublisher::operator=(const BacklogPublisher& input)
{
	if (this != &input)
	{
		SimplePublisher::operator=(input);
		//this->old_messages = input.old_messages; ??????
	}
	return *this;
}
void BacklogPublisher::subscribe(Averager* input)
{
	this->signal_old_message(input);
	this->add_element(input);
}
void BacklogPublisher::subscribe(MovingAverager* input)
{
	this->signal_old_message(input);
	this->add_element(input);
}
void BacklogPublisher::subscribe(PeriodicSampler* input)
{
	this->signal_old_message(input);
	this->add_element(input);
}

void BacklogPublisher::signal(Message input)
{
	this->old_messages.push_back(input);
	for (int i = 0; i < this->elements_in_array; i++)
	{
		this->subscribers[i]->signal(input);
	}
}
void BacklogPublisher::signal_old_message(Averager* input)
{
	for (int i = 0; i < this->old_messages.size(); i++)
	{
		input->signal(this->old_messages[i]);
	}
}