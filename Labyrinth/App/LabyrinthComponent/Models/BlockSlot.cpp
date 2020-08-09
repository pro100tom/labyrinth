#include "BlockSlot.h"

namespace TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Models
{
	BlockSlot::BlockSlot() :
		columnIndex(0),
		rowIndex(0)
	{

	}

	BlockSlot::BlockSlot(int columnIndex, int rowIndex) :
		columnIndex(columnIndex),
		rowIndex(rowIndex)
	{

	}

	bool BlockSlot::operator==(const BlockSlot& blockSlot)
	{
		return columnIndex == blockSlot.columnIndex && rowIndex == blockSlot.rowIndex;
	}
}
