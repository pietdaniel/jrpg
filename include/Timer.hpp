//Daniel Piet Apr 2013
#ifndef _TIMER_HPP
#define _TIMER_HPP
#include <SDL2/SDL.h>
#include <string>

class Timer {
    private:
        int startTicks;
        int pausedTicks;
        bool paused;
        bool started;

    public:
        Timer();
        void start();
        void stop();
        void pause();
        void unpause();
        int get_ticks();
        bool is_started();
        bool is_paused();
};

#endif
