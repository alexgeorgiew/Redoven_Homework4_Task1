
#include "Averager.hpp"
#include "Message.hpp"
#include "MovingAverager.hpp"
#include "BacklogPublisher.hpp"
#include "SimplePublisher.hpp"
#include "PeriodicSampler.hpp"
#include "Repository.hpp"
#include <assert.h>
#include <iostream>


void testSimplePublisher() {
    Repository repo;

    Averager avg1("avg1");
    repo.add(&avg1);

    Averager avg2("avg2");
    repo.add(&avg2);
    SimplePublisher sp;
    sp.subscribe(static_cast<Averager*>(repo.get("avg1")));
    sp.signal({ 10 });
    sp.subscribe((Averager*)repo.get("avg2"));
    sp.signal({ 0 });
    assert(static_cast<Averager*>(repo.get("avg1"))->read() == 5);
    assert(static_cast<Averager*>(repo.get("avg2"))->read() == 0);
    assert(avg1.read() == 0);
    
}

void testBacklogPublisher() {
    Repository repo;
    Averager avg1("avg1");
    repo.add(&avg1);
    BacklogPublisher bp;

   
    bp.signal({ 10 });
    bp.signal({ 0 });

    bp.subscribe(static_cast<Averager*>(repo.get("avg1")));
    assert(static_cast<Averager*>(repo.get("avg1"))->read() == 5);
}

void testMovingAverager() {
    Repository repo;
    MovingAverager mavg1("mavg1", 2);
    repo.add(&mavg1);

    SimplePublisher sp;
    sp.subscribe(dynamic_cast<MovingAverager*>(repo.get("mavg1")));
    sp.signal({ 10 });
    sp.signal({ 0 });
    assert(dynamic_cast<MovingAverager*>(repo.get("mavg1"))->read() == 5);
    
    sp.signal({ 4 });
    assert(dynamic_cast<MovingAverager*>(repo.get("mavg1"))->read() == 2);
}

void testPeriodicSampler()
{
   
    Repository repo;
    PeriodicSampler ps2("ps2", 2);
    repo.add(&ps2);

    SimplePublisher sp;
    sp.subscribe(dynamic_cast<PeriodicSampler*>(repo.get("ps2")));
    sp.signal({ 10 });
    assert(dynamic_cast<PeriodicSampler*>(repo.get("ps2"))->read() == 10);
    sp.signal({ 0 });
    assert(dynamic_cast<PeriodicSampler*>(repo.get("ps2"))->read() == 10);
   
    sp.signal({ 4 });
    assert(dynamic_cast<PeriodicSampler*>(repo.get("ps2"))->read() == 4);
}

int main()
{
    std::cout << "Now 1 test" << std::endl;
    testSimplePublisher();
    std::cout << "Now 2 test" << std::endl;
    testBacklogPublisher();
    std::cout << "Now 3 test" << std::endl;
    testMovingAverager();
    std::cout << "Now 4 test" << std::endl;
    testPeriodicSampler();
}
