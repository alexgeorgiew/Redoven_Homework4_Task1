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
	if (this->nums.size() == 0)return 0;
	if (windowSize > this->nums.size())
	{
		return   this->sum_of_numbers() / this->nums.size();
	}
	return this->sum_of_numbers()/ static_cast<int>(windowSize);
}
int MovingAverager::sum_of_numbers()const
{
	int result=0;
	if (static_cast<int>(windowSize) >= this->nums.size())
	{
		for (int i = 0; i < this->nums.size(); i++)result += this->nums[i];
		return result;
	}
	else
	{
		for (int i = this->nums.size()  - static_cast<int>(windowSize); i < this->nums.size(); i++)
		{
			result += this->nums[i];
		}
		return result;
	}
}