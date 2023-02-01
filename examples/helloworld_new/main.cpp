#include "Pokitto.h"

void init() {
    //Here put any code you want to execute at startup
}

void update() {
    //This should be executed at the required FPS
    using PD = Pokitto::Display;
    PD::print("hello world");
}
