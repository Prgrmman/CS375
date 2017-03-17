#ifndef TIMER_H
#define TIMER_H
#include <ctime>
class Timer{
    private:
        clock_t begin, end;
    public:
        void start();
        void stop();
        double getElapsed();


};



#endif
