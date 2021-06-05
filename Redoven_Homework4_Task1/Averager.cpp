#include "Averager.hpp"

Averager::Averager(std::string id):id(id)
{
	
}
void Averager::signal(Message input)
{
	this->sum_of_all_signals += input.data;
	this->count_of_all_signals++;
}
int Averager::read()const
{
	if (this->count_of_all_signals == 0)
	{
		return 0;
	}
	else
	{
		return this->sum_of_all_signals / this->count_of_all_signals;
	}
}