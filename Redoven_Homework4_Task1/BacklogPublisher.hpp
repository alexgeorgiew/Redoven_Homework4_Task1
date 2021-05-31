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

// BacklogPublisher is a Publisher, which can have one
// or more subscribers and upon receiving a message
// via `signal()`, it replays that message to all the
// subscribers
// Also it keeps a backlog of previous messages so when a new
// Subscriber subscribes, the Publisher replays all
// backlogged messages to the new Subscriber
class BacklogPublisher {
public:
	// subscribe registers a Subscriber to start receiving messages
	// The new subscriber should receive all previous messages
	void subscribe(Averager* input);
	void subscribe(MovingAverager* input);
	void subscribe(PeriodicSampler* input);

	// unsubscribe removes a Subscriber from the Publisher
	// Subscribers are removed based on their `id`
	// id-s will always be unique
	void unsubscribe(Averager* input);
	void unsubscribe(MovingAverager* input);
	void unsubscribe(PeriodicSampler* input);

	// signal receives a message from an external source
	// and replays that message to all the current subscribers
	void signal(Message);
	private:
		std::vector<Message>old_messages;
		std::vector<Averager*>subscribers;

};
