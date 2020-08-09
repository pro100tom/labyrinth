#pragma once

namespace TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Models
{
	class BlockSlot
	{
	public:
		BlockSlot();
		BlockSlot(int columnIndex, int rowIndex);

		int columnIndex;
		int rowIndex;

		bool operator==(const BlockSlot&);
	};
}
