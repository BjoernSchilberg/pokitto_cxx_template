#include <Pokitto.h>

Pokitto::Display display;
Pokitto::Buttons buttons;

/*
 * https://talk.pokitto.com/t/very-beginner-friendly-tutorial-0-2-how-to-create-a-very-simple-movement-system-using-the-knowledge-you-learnt-in-tutorial-0-1-counting-program-c-pokittooo/2920
 * API Reference
 * https://pokitto.github.io/library/reference
*/

int moveY = 0;
int moveX = 0;
int sizeX = 8;
int sizeY = 8;
int speedX = 2;
int speedY = 2;

void init()
{
}

void update()
{

    display.setColor(C_BROWN);
    display.fillRect(moveX, moveY, sizeX, sizeY);

    if (buttons.pressed(BTN_UP))
    {
        moveY = moveY - speedY;
    }

    if (buttons.pressed(BTN_DOWN))
    {
        moveY = moveY + speedY;
    }

    if (buttons.pressed(BTN_LEFT))
    {
        moveX = moveX - speedX;
    }

    if (buttons.pressed(BTN_RIGHT))
    {
        moveX = moveX + speedX;
    }
}
