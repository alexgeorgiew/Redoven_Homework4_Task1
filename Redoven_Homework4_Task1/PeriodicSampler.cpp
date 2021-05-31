#include "PeriodicSampler.hpp"
PeriodicSampler::PeriodicSampler(std::string id, size_t period):Averager(id),period(period)
{

}
void PeriodicSampler::signal(Message input)
{
	this->count_of_all_signals++;
	if (this->count_of_all_signals % period != 0) this->non_ignored_message = input.data;
}
int PeriodicSampler::read()
{
	return non_ignored_message;
}