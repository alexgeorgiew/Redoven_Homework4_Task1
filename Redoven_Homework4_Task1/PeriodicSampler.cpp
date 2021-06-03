#include "PeriodicSampler.hpp"
#include <iostream>
PeriodicSampler::PeriodicSampler(std::string id, size_t period):Averager(id),period(period)
{

}
void PeriodicSampler::signal(Message input)
{
	if ((this->count_of_all_signals) % period == 0) this->non_ignored_message = input.data;
	this->count_of_all_signals++;
}
int PeriodicSampler::read()const
{
	return non_ignored_message;
}