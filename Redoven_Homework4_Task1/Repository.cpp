#include "Repository.hpp"
#include <iostream>
Repository::~Repository()
{
	for(Averager* pointer : subscibers)
	{
		delete pointer;
	}
	subscibers.clear();
}
Repository::Repository(const Repository& input)
{
	for (int i = 0; i < input.subscibers.size(); i++)
	{
		Averager* variable = new Averager(*input.subscibers[i]);
		this->subscibers.push_back(variable);
	}
}
Repository& Repository::operator=(const Repository& input)
{
	if (this != &input)
	{
		for (Averager* pointer : this->subscibers)
		{
			delete pointer;
		}
		subscibers.clear();
		for (int i = 0; i < input.subscibers.size(); i++)
		{
			Averager* variable = new Averager(*input.subscibers[i]);
			this->subscibers.push_back(variable);
		}
	}
	return *this;
}
void Repository::add(Averager* input)
{
	Averager* current = new Averager(*input);
	this->subscibers.push_back(current);
}
void Repository::add(MovingAverager* input)
{
	MovingAverager* current = new MovingAverager(*input);
	this->subscibers.push_back(current);
}
void Repository::add(PeriodicSampler* input)
{
	PeriodicSampler* current = new PeriodicSampler(*input);
	this->subscibers.push_back(current);
}
Averager* Repository::get(std::string id)
{
	for (int i = 0; i < this->subscibers.size(); i++) {
		if (this->subscibers[i]->id == id)
		{
			return this->subscibers[i];
		}
	}
	return nullptr;

}