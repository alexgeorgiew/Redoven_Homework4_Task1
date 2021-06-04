#pragma once
#include "Averager.hpp"
#include "Message.hpp"
#include "MovingAverager.hpp"
#include "PeriodicSampler.hpp"
#include <vector>
// You are not allowed to make breaking changes to the class interface,
// but you are allowed to add additional methods/fields, as 
// well as MODIFY the existing interface so as to make it
// "more correct" and more compact if possible

// SimplePublisher is a Publisher, which can have one
// or more subscribers and upon receiving a message
// via `signal()`, it replays that message to all the
// subscribers
class SimplePublisher {
public:
	SimplePublisher();
	~SimplePublisher();
	SimplePublisher(const SimplePublisher& input);
	SimplePublisher& operator=(const SimplePublisher& input);
	// subscribe registers a Subscriber to start receiving messages
	void virtual subscribe(Averager* input);
	void virtual subscribe(MovingAverager* input);
	void virtual subscribe(PeriodicSampler* input);
	// unsubscribe removes a Subscriber from the Publisher
	// Subscribers are removed based on their `id`
	// id's will always be unique

	void  unsubscribe(Averager* input);
	void  unsubscribe(MovingAverager* input);
	void  unsubscribe(PeriodicSampler* input);

	// signal receives a message from an external source
	// and replays that message to all the current subscribers
	void virtual signal(Message input);
protected:
	void add_element(Averager* input);
	void remove_element(Averager* input);
	void copy_memory(Averager** input, int size_of_input, int elements_in_input);
	void allocate_more_memory();
	void Delete();
	Averager** subscribers;
	int size_of_array, elements_in_array;
};
