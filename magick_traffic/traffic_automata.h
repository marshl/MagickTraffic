#ifndef TRAFFIC_AUTOMATA
#define TRAFFIC_AUTOMATA

#include <vector>


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

class TrafficAutomata
{
public:
    TrafficAutomata( int width, int height );

    ~TrafficAutomata();

    void Randomise( float ratio );

    void Multistep( int steps );

    void Step();

    TrafficCell* GetCell( int x, int y );

    TrafficCell* GetCellOffset( int x, int y, int xOffset, int yOffset );

    //TrafficCell* cellTable;
    std::vector<TrafficCell> cellTable;

    int width;
    int height;
private:


    DIRECTION currentDirection;

    //TrafficCell* tempTable;
    std::vector<TrafficCell> tempTable;

    TrafficCell* GetTempCell( int x, int y );

    TrafficCell* GetTempCellOffset( int x, int y, int xOffset, int yOffset );

    TrafficCell* GetCellInTable( int x, int y, std::vector<TrafficCell>& table );

    void ApplyOffset( int& x, int& y, int xOffset, int yOffset );
};

#endif