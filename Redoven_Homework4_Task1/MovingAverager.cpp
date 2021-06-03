#include "MovingAverager.hpp"
#include <iostream>
MovingAverager::MovingAverager(std::string id, size_t windowSize):Averager(id),windowSize(windowSize)
{
	this->nums = new int[windowSize];
	for (int i = 0; i < windowSize; i++)this->nums[i] = 0;
}
MovingAverager::~MovingAverager()
{
	delete[] nums;
}
MovingAverager::MovingAverager(const MovingAverager& input):Averager(input.id),windowSize(input.windowSize)
{
	this->nums = new int[input.windowSize];
	this->count_of_meaningful_numbers = input.count_of_meaningful_numbers;
	for (int i = 0; i < input.windowSize; i++)
	{
		this->nums[i] = input.nums[i];
	}
}
void MovingAverager::signal(Message input)
{
	if (count_of_meaningful_numbers < windowSize)
	{
		this->nums[count_of_meaningful_numbers] = input.data;
		this->count_of_meaningful_numbers++;
	}
	else
	{
		for (int i = 0; i < windowSize-1; i++)
		{
			this->nums[i] = this->nums[i + 1];
		}
		this->nums[windowSize - 1] = input.data;
	}
}
int MovingAverager::read()const
{
	return this->sum_of_numbers()/ windowSize;
}
int MovingAverager::sum_of_numbers()const
{
	int result=0;
	for (int i = 0; i < windowSize; i++)result += this->nums[i];
	return result;
}