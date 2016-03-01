#include "traffic_automata.h"

#include <cstdlib>
#include <memory>
#include <cassert>

TrafficAutomata::TrafficAutomata( int width, int height )
{
    this->width = width;
    this->height = height;
    this->cellTable.resize( width * height );
    this->tempTable.resize( width * height );

    this->currentDirection = rand() % 2 ? HORIZONTAL : VERTICAL;

    for ( int y = 0; y < this->height; ++y )
    {
        for ( int x = 0; x < this->width; ++x )
        {
            TrafficCell* c = this->GetCell( x, y );
            c->originalX = x;
            c->originalY = y;
        }
    }
}

void TrafficAutomata::Randomise( float ratio )
{
    for ( int y = 0; y < this->height; ++y )
    {
        for ( int x = 0; x < this->width; ++x )
        {
            TrafficCell* c = this->GetCell( x, y );
            bool occupied = (float)rand() / (float)RAND_MAX < ratio;
            c->direction = !occupied ? UNOCCUPIED : ( rand() % 2 ? VERTICAL : HORIZONTAL );
        }
    }
}

void TrafficAutomata::Step()
{
    for ( int i = 0; i < this->width * this->height; ++i )
    {
        this->tempTable[i].direction = UNOCCUPIED;
    }

    for ( int y = this->height - 1; y >= 0; --y )
    {
        for ( int x = this->width - 1; x >= 0; --x )
        {
            TrafficCell* cell = this->GetCell( x, y );

            if ( cell->direction == UNOCCUPIED )
                continue;

            
            TrafficCell* tempCell = this->GetTempCell( x, y );

            if ( this->currentDirection == HORIZONTAL )
            {
                TrafficCell* right = this->GetCellToRight( x, y );

                if ( cell->direction == HORIZONTAL && right->direction == UNOCCUPIED )
                {
                    TrafficCell* tempRight = this->GetTempCellToRight( x, y );
                    *tempRight = *cell;
                }
                else
                {
                    *tempCell = *cell;
                }
            }
            else if ( this->currentDirection == VERTICAL )
            {
                TrafficCell* down = this->GetCellBelow( x, y );

                if ( cell->direction == VERTICAL && down->direction == UNOCCUPIED )
                {
                    TrafficCell* tempDown = this->GetTempCellBelow( x, y );
                    *tempDown = *cell;
                }
                else
                {
                    *tempCell = *cell;
                }
            }
        }
    }

    this->currentDirection = ( this->currentDirection == HORIZONTAL ? VERTICAL : HORIZONTAL );
    for ( int i = 0; i < this->width * this->height; ++i )
    {
        this->cellTable[i] = this->tempTable[i];
    }
}
