#include "Dimensions.h"

namespace TomasBaranauskas::LabyrinthApp::MathComponent::Models
{
	Dimensions::Dimensions() :
		numberOfColumns(10),
		numberOfRows(10)
	{

	}

	Dimensions::Dimensions(int numberOfColumns, int numberOfRows) :
		numberOfColumns(numberOfColumns),
		numberOfRows(numberOfRows)
	{

	}

	Dimensions::Dimensions(const Dimensions& dimensions) :
		numberOfColumns(dimensions.numberOfColumns),
		numberOfRows(dimensions.numberOfRows)
	{

	}
}
