#include "SimplePublisher.hpp"
#include <iostream>

SimplePublisher::SimplePublisher()
{
	this->subscribers = new Averager * [1];
	this->size_of_array = 1;
	this->elements_in_array = 0;
}

SimplePublisher:: ~SimplePublisher()
{
	this->Delete();
}

SimplePublisher::SimplePublisher(const SimplePublisher& input)
{
	this->copy_memory(input.subscribers, input.size_of_array, input.elements_in_array);
}

SimplePublisher& SimplePublisher::operator=(const SimplePublisher& input)
{
	if (this != &input)
	{
		this->Delete();
		this->copy_memory(input.subscribers, input.size_of_array, input.elements_in_array);
	}
	return *this;
}

void SimplePublisher::subscribe(Averager* input)
{
	this->add_element(input);
}

void SimplePublisher::subscribe(MovingAverager* input)
{
	this->add_element(input);
}

void SimplePublisher::subscribe(PeriodicSampler* input)
{
	this->add_element(input);
}

void SimplePublisher::unsubscribe(Averager* input)
{
	this->remove_element(input);
}

void SimplePublisher::unsubscribe(MovingAverager* input)
{
	this->remove_element(input);
}
void SimplePublisher::unsubscribe(PeriodicSampler* input)
{
	this->remove_element(input);
}

void SimplePublisher::signal(Message input)
{
	for (int i = 0; i < this->elements_in_array; i++)
	{
		if (MovingAverager* mask = dynamic_cast<MovingAverager*>(this->subscribers[i]))
		{
			mask->signal(input);
		}
		else if (PeriodicSampler* mask2 = dynamic_cast<PeriodicSampler*>(this->subscribers[i]))
		{
			mask2->signal(input);
		}
		else
		{
			this->subscribers[i]->signal(input);
		}
	}
}

void  SimplePublisher::Delete()
{
	//for (int i = 0; i < this->size_of_array; i++)
	//{
	//	delete this->subscribers[i];
	//}
	delete[] this->subscribers;
}

void  SimplePublisher::copy_memory(Averager** input,int size_of_input,int elements_in_input)
{
	Averager** result = new Averager * [size_of_array];
	for (int i = 0; i < size_of_input; i++)
	{
		result[i] = input[i];
	}
	this->Delete();
	this->subscribers = result;
	this->size_of_array = size_of_input;
	this->elements_in_array = elements_in_input;
	return;
}

void SimplePublisher::allocate_more_memory()
{
	Averager** result = new Averager * [this->size_of_array*2];
	for (int i = 0; i < this->size_of_array; i++)
	{
		result[i] = this->subscribers[i];
	}
	this->Delete();
	this->size_of_array = this->size_of_array * 2;
	this->subscribers = result;
}

void SimplePublisher::add_element(Averager* input)
{
	if (elements_in_array < size_of_array)
	{
		this->subscribers[elements_in_array] = input;
	}
	else
	{
		this->allocate_more_memory();
		this->subscribers[this->elements_in_array] = input;
	}
	this->elements_in_array++;
	return;
}

void SimplePublisher::remove_element(Averager* input)
{
	for (int i = 0; i < this->elements_in_array; i++)
	{
		if (this->subscribers[i]->id == input->id)
		{
			for (int j = i; j < this->elements_in_array; j++)
			{
				this->subscribers[j] = this->subscribers[j + 1];
			}
			this->subscribers[this->elements_in_array] = nullptr;
			this->elements_in_array--;
			return;
		}
	}
}