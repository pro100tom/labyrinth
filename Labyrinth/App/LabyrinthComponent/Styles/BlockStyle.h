#pragma once

namespace TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Styles
{
	class BlockStyle
	{
	public:
		BlockStyle();
		BlockStyle(const BlockStyle&);
		BlockStyle(int blockLength, int gapWidth);

		double GetBlockHalfLength() const;
		int GetPathWidth() const;
		double GetPathHalfWidth() const;

		int blockLength;
		int gapWidth;
	};
}

