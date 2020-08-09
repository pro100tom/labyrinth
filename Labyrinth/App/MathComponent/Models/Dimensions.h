#pragma once

namespace TomasBaranauskas::LabyrinthApp::MathComponent::Models
{
	class Dimensions
	{
	public:
		Dimensions();
		Dimensions(int, int);
		Dimensions(const Dimensions&);

		int numberOfColumns;
		int numberOfRows;
	};
}

