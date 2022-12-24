#include "animation.hpp"

animation::animation()
{
    speed = 1.f;
    paused = false;
}

bool animation::GetPaused()
{
    return paused;
}

float animation::GetSpeed()
{
    return speed;
}

void animation::ChangeSpeed(float s)
{
    speed = speed + s;
    if (speed < 0)
        speed = 0;
}

void animation::togglePause()
{
    paused = !paused;

}