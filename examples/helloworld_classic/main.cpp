#include "Pokitto.h"
int main(){
    using PC=Pokitto::Core;
    using PD=Pokitto::Display;
    PC::begin();
    while( PC::isRunning() ){
        if( !PC::update() )
            continue;
        PD::print("hello world");
    }
    return 0;
}
