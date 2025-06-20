#ifndef ANIMATION_H
#define ANIMATION_H

#include <iostream>
#include "Animation.h"
#include <string>
#include <thread>
#include <chrono>

using namespace std;

class Animation {
public:
    
    static void typeEffect(const string& text, int delay = 20);
    static void loadingBar(int steps = 20, int delay = 100);
    static void blinkingMessage(const string& msg, int times = 3);
    static void splashScreen();
    static void pause(int duration);
};

#endif // ANIMATION_H
