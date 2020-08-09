#include "RectangleCreationService.h"

#include "LabyrinthComponent/Enums/BlockPartSelector.h"
#include "LabyrinthComponent/Models/Route.h"
#include "MathComponent/Enums/RightAngleSelector.h"
#include "MathComponent/Models/GeometryModels/Rectangle.h"

#include <tuple>

using TomasBaranauskas::LabyrinthApp::MathComponent::Models::GeometryModels::Border;
using LocalRectangle = TomasBaranauskas::LabyrinthApp::MathComponent::Models::GeometryModels::Rectangle;
using TomasBaranauskas::LabyrinthApp::MathComponent::Enums::RightAngleSelector;
using TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Styles::BlockStyle;
using TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Enums::BlockPartSelector;
using TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Models::Route;

using std::tuple;
using std::vector;
using Gdiplus::PointF;

namespace TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Services
{
	RectangleCreationService::RectangleCreationService() :
		RectangleCreationService::RectangleCreationService(BlockStyle())
	{

	}

	RectangleCreationService::RectangleCreationService(const BlockStyle& blockStyle) :
		blockStyle(blockStyle)
	{
	
	}

	LocalRectangle RectangleCreationService::CreateLeftRectangle(Border border) const
	{
		auto height = blockStyle.GetPathWidth();

		return TomasBaranauskas::LabyrinthApp::MathComponent::Models::GeometryModels::Rectangle(
			PointF(0, blockStyle.gapWidth),
			blockStyle.gapWidth,
			height,
			border
		);
	}

	LocalRectangle RectangleCreationService::CreateLeftDeadendRectangle(Border border) const
	{
		auto height = blockStyle.GetPathWidth();

		return TomasBaranauskas::LabyrinthApp::MathComponent::Models::GeometryModels::Rectangle(
			PointF(0, blockStyle.gapWidth),
			roundf(blockStyle.gapWidth * 0.5),
			height,
			border
		);
	}

	LocalRectangle RectangleCreationService::CreateRectangle(
		BlockPartSelector blockPartSelector,
		Border leftRectangleBorder,
		bool isDeadend
	) const {
		auto rectangle = isDeadend ? CreateLeftDeadendRectangle(leftRectangleBorder) : CreateLeftRectangle(leftRectangleBorder);
		auto rotationAngle = ObtainRectangleRotationAngle(blockPartSelector);
		auto center = blockStyle.GetBlockHalfLength();
		auto rotatedRectangle = transformationManager.RotateRectangle(rectangle, rotationAngle, PointF(center, center));
		
		return rotatedRectangle;
	}

	LocalRectangle RectangleCreationService::CreateCenterRectangle(Border border) const
	{
		auto pathWidth = blockStyle.GetPathWidth();

		return TomasBaranauskas::LabyrinthApp::MathComponent::Models::GeometryModels::Rectangle(
			PointF(blockStyle.gapWidth, blockStyle.gapWidth),
			pathWidth,
			pathWidth
		);
	}

	vector<LocalRectangle> RectangleCreationService::CreateRectangles(const Route& route) const 
	{
		auto startingBlockPartOptional = route.GetStartingBlockPart();
		if (!startingBlockPartOptional.has_value())
			return vector<LocalRectangle>();

		auto destinationBlockParts = route.GetDestinationBlockParts();
		if (destinationBlockParts.size() <= 0)
			return vector<LocalRectangle>{ CreateRectangle(startingBlockPartOptional.value(), Border(0, 1, 1, 1), true) };

		auto border = Border(1.0, 1.0, 1.0, 1.0);
		vector<tuple<BlockPartSelector, double*>> mappedSelectorItems =
		{
			{ BlockPartSelector::Left, &border.left },
			{ BlockPartSelector::Top, &border.top },
			{ BlockPartSelector::Right, &border.right },
			{ BlockPartSelector::Bottom, &border.bottom }
		};

		auto rectangles = vector<LocalRectangle>();
		auto blockPartsInUse = route.GetBlockPartsInUse();
		for (auto item : mappedSelectorItems)
		{
			auto blockPart = std::get<0>(item);
			if (std::find(blockPartsInUse.begin(), blockPartsInUse.end(), blockPart) == blockPartsInUse.end())
				continue;

			*(std::get<1>(item)) = 0.0;
			rectangles.push_back(CreateRectangle(blockPart));
		}

		auto centerRectangle = CreateCenterRectangle();
		centerRectangle.border = border;
		rectangles.push_back(centerRectangle);

		return rectangles;
	}

	RightAngleSelector RectangleCreationService::ObtainRectangleRotationAngle(BlockPartSelector blockPartPosition) const
	{
		switch (blockPartPosition)
		{
			case BlockPartSelector::Top:
				return RightAngleSelector::Rotate90;
			case BlockPartSelector::Right:
				return RightAngleSelector::Rotate180;
			case BlockPartSelector::Bottom:
				return RightAngleSelector::Rotate270;
			default:
				break;
		}

		return RightAngleSelector::None;
	}

	const TransformationManager RectangleCreationService::transformationManager = TransformationManager();
	const BlockPartManager RectangleCreationService::blockPartManager = BlockPartManager();
}
