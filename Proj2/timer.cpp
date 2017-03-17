#include "timer.h"




void Timer::start(){
    begin = clock();

}
void Timer::stop(){
    end = clock();

}
// code found on http://stackoverflow.com/questions/2808398/easily-measure-elapsed-time
double Timer::getElapsed(){
    return double(end - begin) / CLOCKS_PER_SEC;
}

