#include "BlockStyle.h"

using TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Styles::BlockStyle;

namespace TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Styles
{
	BlockStyle::BlockStyle() :
		BlockStyle::BlockStyle(100, 35)
	{

	}

	BlockStyle::BlockStyle(const BlockStyle& blockStyle) :
		blockLength(blockStyle.blockLength),
		gapWidth(blockStyle.gapWidth)
	{

	}

	BlockStyle::BlockStyle(int blockLength, int gapWidth) :
		blockLength(blockLength),
		gapWidth(gapWidth)
	{

	}

	double BlockStyle::GetBlockHalfLength() const
	{
		return blockLength * 0.5;
	}

	int BlockStyle::GetPathWidth() const
	{
		return blockLength - gapWidth * 2;
	}

	double BlockStyle::GetPathHalfWidth() const
	{
		return GetPathWidth() * 0.5;
	}
}
