#include "MovingAverager.hpp"
#include <iostream>
MovingAverager::MovingAverager(std::string id, size_t windowSize):Averager(id),windowSize(windowSize)
{
}
void MovingAverager::signal(Message input)
{
	this->nums.push_back(input.data);
}
int MovingAverager::read()const
{
	
	return this->sum_of_numbers()/ windowSize;
}
int MovingAverager::sum_of_numbers()const
{
	int result=0;
	int counter = windowSize;
	for (int i = this->nums.size()-1; i >-1; --i)
	{
		if (counter==0)return result;
		result += this->nums[i];
		counter--;
	}
	return result;
}