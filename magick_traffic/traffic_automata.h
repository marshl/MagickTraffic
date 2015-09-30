#ifndef TRAFFIC_AUTOMATA
#define TRAFFIC_AUTOMATA

#include <vector>

#include "base_automata.h"

enum DIRECTION
{
    UNOCCUPIED,
    VERTICAL,
    HORIZONTAL,
};

struct TrafficCell
{
    //bool occupied;
    //Colour originalColour;
    DIRECTION direction;
    short originalX;
    short originalY;
};

class TrafficAutomata : public BaseAutomata<TrafficCell>
{
public:
    TrafficAutomata( int width, int height );

    ~TrafficAutomata();

    void Randomise( float ratio );

    virtual void Step();

private:
    DIRECTION currentDirection;
};

#endif