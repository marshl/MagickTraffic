#ifndef BASE_AUTOMATA
#define BASE_AUTOMATA

#include <vector>
#include <cassert>

template <typename T>
class BaseAutomata
{
public:
    virtual void Step() = 0;

    void Multistep( int steps );

    T* GetCell( int x, int y );

    //T* GetCellOffset( int x, int y, int xOffset, int yOffset );

protected:
    std::vector<T> tempTable;
    std::vector<T> cellTable;

    int width;
    int height;

    T* GetTempCell( int x, int y );

    T* GetCellToRight( int x, int y );
    T* GetCellBelow( int x, int y );

    T* GetTempCellToRight( int x, int y );
    T* GetTempCellBelow( int x, int y );

    //T* GetTempCellOffset( int x, int y, int xOffset, int yOffset );

    T* GetCellInTable( int x, int y, std::vector<T>& table );

    //void ApplyOffset( int& x, int& y, int xOffset, int yOffset );
};

template<typename T>
void BaseAutomata<T>::Multistep( int steps )
{
    for ( int i = 0; i < steps; ++i )
    {
        this->Step();
    }
}

template<typename T>
T * BaseAutomata<T>::GetCell( int x, int y )
{
    return this->GetCellInTable( x, y, this->cellTable );
}

template<typename T>
T * BaseAutomata<T>::GetCellToRight( int x, int y )
{
    return this->GetCellInTable( x == this->width - 1 ? 0 : x + 1, y, this->cellTable );
}

template<typename T>
T * BaseAutomata<T>::GetTempCellToRight( int x, int y )
{
    return this->GetCellInTable( x == this->width - 1 ? 0 : x + 1, y, this->tempTable );
}

template<typename T>
T * BaseAutomata<T>::GetCellBelow( int x, int y )
{
    return this->GetCellInTable( x, y == this->height - 1 ? 0 : y + 1, this->cellTable );
}

template<typename T>
T * BaseAutomata<T>::GetTempCellBelow( int x, int y )
{
    return this->GetCellInTable( x, y == this->height - 1 ? 0 : y + 1, this->tempTable );
}

/*
template<typename T>
T * BaseAutomata<T>::GetCellOffset( int x, int y, int xOffset, int yOffset )
{
    this->ApplyOffset( x, y, xOffset, yOffset );
    return this->GetCell( x, y );
}
*/
template<typename T>
T * BaseAutomata<T>::GetTempCell( int x, int y )
{
    return this->GetCellInTable( x, y, this->tempTable );;
}

/*
template<typename T>
T * BaseAutomata<T>::GetTempCellOffset( int x, int y, int xOffset, int yOffset )
{
    this->ApplyOffset( x, y, xOffset, yOffset );
    return this->GetTempCell( x, y );
}
*/
template<typename T>
T * BaseAutomata<T>::GetCellInTable( int x, int y, std::vector<T>& table )
{
    assert( x >= 0 );
    assert( x < this->width );
    assert( y >= 0 );
    assert( y < this->height );

    return &table[y * this->width + x];
}

/*
template<typename T>
void BaseAutomata<T>::ApplyOffset( int & x, int & y, int xOffset, int yOffset )
{
    x += xOffset;
    y += yOffset;

    while ( x < 0 )
    {
        x += this->width;
    }

    while ( x >= this->width )
    {
        x -= this->width;
    }

    while ( y < 0 )
    {
        y += this->height;
    }

    while ( y >= this->height )
    {
        y -= this->height;
    }
}
*/

#endif