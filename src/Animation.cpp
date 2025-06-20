#include "Animation.h"


void Animation::typeEffect(const string& text, int delay) {
    for (char c : text) {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(delay));
    }
}

void Animation::loadingBar(int steps, int delay) {
    cout << "Loading: [";
    for (int i = 0; i < steps; ++i) {
        cout << "#" << flush;
        this_thread::sleep_for(chrono::milliseconds(delay));
    }
    cout << "] Done!\n";
}

void Animation::blinkingMessage(const string& msg, int times) {
    for (int i = 0; i < times; ++i) {
        cout << msg << flush;
        this_thread::sleep_for(chrono::milliseconds(300));
        system("cls");
        this_thread::sleep_for(chrono::milliseconds(200));
    }
}

void Animation::splashScreen() {
    system("cls");
    typeEffect(" Logging in...\n", 30);
    loadingBar();
    this_thread::sleep_for(chrono::milliseconds(500));
    system("cls");
}

void Animation::pause(int duration) {
    this_thread::sleep_for(chrono::milliseconds(duration));
}
