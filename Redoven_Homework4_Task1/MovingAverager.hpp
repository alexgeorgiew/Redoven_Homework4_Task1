#pragma once
#include "Message.hpp"
#include <string>

// You are not allowed to make breaking changes to the class interface,
// but you are allowed to add additional methods/fields, as 
// well as MODIFY the existing interface so as to make it
// "more correct" and more compact if possible

// MovingAverager is a type of Subscriber, which saves data
// and returns the average of the last `windowSize` number of
// data points when `read()` is called.
// Data is provided with the `signal()` method.
// Average of N numbers = sum(all numbers) / N

#include "Averager.hpp"
class MovingAverager:virtual public Averager{
public:
	MovingAverager(std::string id, size_t windowSize);
	~MovingAverager();
	MovingAverager(const MovingAverager& input);
	//MovingAverager& operator=(const MovingAverager& input);   this for this operator?????

	// id is a unique identifier for a Subscriber
	// Should never be changed once initialized
	//std::string id;

	// windowSize specifies how many most-recent data points
	// should be saved
	// Should never be changed once initialized
	const size_t windowSize;

	void signal(Message input) override;
	// signal adds a new data point
	// Remember, you only need the last windowSize number of 
	// data points added, older data points should be ignored
	//void signal(Message);

	int read() override;
	// read calculates the average of the last windowSize number
	// of data points
	// returns 0 if there's no data points
	//int read();
private:
	int* nums;
	int count_of_meaningful_numbers=0;
	int sum_of_numbers()const;
};
