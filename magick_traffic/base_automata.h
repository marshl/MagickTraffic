#ifndef BASE_AUTOMATA
#define BASE_AUTOMATA

#include <vector>
#include <cassert>

template <typename T>
class BaseAutomata
{
public:
	virtual void Step() = 0;

	void Multistep(int steps);

	T* GetCell(int x, int y);

protected:
	std::vector<T> tempTable;
	std::vector<T> cellTable;

	int width;
	int height;

	T* GetTempCell(int x, int y);

	T* GetCellToRight(int x, int y);
	T* GetCellBelow(int x, int y);

	T* GetTempCellToRight(int x, int y);
	T* GetTempCellBelow(int x, int y);

	T* GetCellInTable(int x, int y, std::vector<T>& table);
};

template<typename T>
void BaseAutomata<T>::Multistep(int steps)
{
	for (int i = 0; i < steps; ++i)
	{
		this->Step();
	}
}

template<typename T>
T* BaseAutomata<T>::GetCell(int x, int y)
{
	return this->GetCellInTable(x, y, this->cellTable);
}

template<typename T>
T* BaseAutomata<T>::GetCellToRight(int x, int y)
{
	return this->GetCellInTable(x == this->width - 1 ? 0 : x + 1, y, this->cellTable);
}

template<typename T>
T* BaseAutomata<T>::GetTempCellToRight(int x, int y)
{
	return this->GetCellInTable(x == this->width - 1 ? 0 : x + 1, y, this->tempTable);
}

template<typename T>
T* BaseAutomata<T>::GetCellBelow(int x, int y)
{
	return this->GetCellInTable(x, y == this->height - 1 ? 0 : y + 1, this->cellTable);
}

template<typename T>
T* BaseAutomata<T>::GetTempCellBelow(int x, int y)
{
	return this->GetCellInTable(x, y == this->height - 1 ? 0 : y + 1, this->tempTable);
}

template<typename T>
T* BaseAutomata<T>::GetTempCell(int x, int y)
{
	return this->GetCellInTable(x, y, this->tempTable);;
}

template<typename T>
T* BaseAutomata<T>::GetCellInTable(int x, int y, std::vector<T>& table)
{
	assert(x >= 0);
	assert(x < this->width);
	assert(y >= 0);
	assert(y < this->height);

	return &table[y * this->width + x];
}

#endif