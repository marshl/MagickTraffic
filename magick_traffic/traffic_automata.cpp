#include "traffic_automata.h"

#include <cstdlib>
#include <memory>
#include <cassert>

TrafficAutomata::TrafficAutomata( int width, int height )
{
    this->width = width;
    this->height = height;
    //this->cellTable = new TrafficCell[width * height];
    //this->tempTable = new TrafficCell[width * height];
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

TrafficAutomata::~TrafficAutomata()
{
    //delete this->cellTable;
    //delete this->tempTable;
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
        //this->tempTable[i].occupied = false;
    }

    //memset( this->tempTable, UNOCCUPIED, sizeof( TrafficCell ) );

    for ( int y = this->height - 1; y >= 0; --y )
    {
        for ( int x = this->width - 1; x >= 0; --x )
        {
            TrafficCell* cell = this->GetCell( x, y );

            //if ( !this->GetCell( x, y )->occupied )
            if ( cell->direction == UNOCCUPIED )
                continue;

            
            TrafficCell* tempCell = this->GetTempCell( x, y );

            if ( this->currentDirection == HORIZONTAL )
            {
                TrafficCell* right = this->GetCellToRight( x, y );// this->GetCellOffset( x, y, 1, 0 );

                //if ( cell->occupied && cell->direction == HORIZONTAL && !right->occupied )
                if ( cell->direction == HORIZONTAL && right->direction == UNOCCUPIED )
                {
                    TrafficCell* tempRight = this->GetTempCellToRight( x, y );// this->GetTempCellOffset( x, y, 1, 0 );
                    //tempRight->occupied = true;
                    //tempRight->direction = HORIZONTAL;
                    *tempRight = *cell;
                }
                else
                {
                    //tempCell->occupied = cell->occupied;
                    //tempCell->direction = cell->direction;
                    *tempCell = *cell;
                }
            }
            else if ( this->currentDirection == VERTICAL )
            {
                TrafficCell* down = this->GetCellBelow( x, y );// this->GetCellOffset( x, y, 0, 1 );

                //if ( cell->occupied && cell->direction == VERTICAL && !down->occupied )
                if ( cell->direction == VERTICAL && down->direction == UNOCCUPIED )
                {
                    TrafficCell* tempDown = this->GetTempCellBelow( x, y );// this->GetTempCellOffset( x, y, 0, 1 );
                    //tempDown->occupied = true;
                    //tempDown->direction = VERTICAL;
                    *tempDown = *cell;
                }
                else
                {
                    //tempCell->occupied = cell->occupied;
                    //tempCell->direction = cell->direction;
                    *tempCell = *cell;
                }
            }
        }
    }

    this->currentDirection = ( this->currentDirection == HORIZONTAL ? VERTICAL : HORIZONTAL );
    //memcpy( this->cellTable, this->tempTable, sizeof( TrafficCell ) * this->width * this->height );
    for ( int i = 0; i < this->width * this->height; ++i )
    {
        this->cellTable[i] = this->tempTable[i];
        //this->cellTable[i].direction = this->tempTable[i].direction;
        //this->cellTable[i].occupied = this->tempTable[i].occupied;
    }
}
