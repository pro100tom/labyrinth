#include "LabyrinthRenderer.h"

#include "LabyrinthComponent/Models/BlockSlot.h"
#include "LabyrinthComponent/ViewModels/Block.h"
#include "LabyrinthComponent/ViewModels/Labyrinth.h"
#include "MathComponent/Models/GeometryModels/Line.h"
#include "MathComponent/Models/GeometryModels/Rectangle.h"
#include "MathComponent/Models/Dimensions.h"

#include <stdlib.h> 
#include <algorithm>
#include <math.h>

using TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Models::BlockSlot;
using TomasBaranauskas::LabyrinthApp::LabyrinthComponent::ViewModels::Labyrinth;
using TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Styles::LabyrinthRenderingStyle;
using TomasBaranauskas::LabyrinthApp::MathComponent::Models::GeometryModels::Line;
using LocalRectangle = TomasBaranauskas::LabyrinthApp::MathComponent::Models::GeometryModels::Rectangle;
using TomasBaranauskas::LabyrinthApp::MathComponent::Models::Dimensions;

using namespace Gdiplus;
using namespace std;

namespace TomasBaranauskas::LabyrinthApp::LabyrinthComponent::Services
{
    LabyrinthRenderer::LabyrinthRenderer(
        Labyrinth labyrinth,
        const HWND& hWnd,
        LabyrinthRenderingStyle labyrinthRenderingStyle
    ) :
        labyrinth(labyrinth),
        hWnd(hWnd),
        routeGroupIndex(0),
        routeGroupCount(labyrinth.GetRouteGroupCount()),
        labyrinthRenderingStyle(labyrinthRenderingStyle),
        visualInitRequired(true),
        clientRectangle(RECT()),
        paintStruct(PAINTSTRUCT())
    {
        ULONG_PTR gdiplusToken;
        GdiplusStartupInput gdiplusStartupInput;
        GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

        PrepareRenderingTools();
    }

    void LabyrinthRenderer::PrepareRenderingTools()
    {
        auto dimensions = labyrinth.GetDimensions();
        HDC hdc = GetDC(hWnd);

        for (int columnIndex = 0; columnIndex < dimensions.numberOfColumns; columnIndex++)
        {
            hdcGrid.push_back(vector<HDC>());
            for (int rowIndex = 0; rowIndex < dimensions.numberOfRows; rowIndex++)
                hdcGrid[columnIndex].push_back(CreateCompatibleDC(hdc));
        }
    }

    bool LabyrinthRenderer::TryRenderNextLabyrinthRouteGroup(bool resetCounter)
    {
        if (resetCounter)
            routeGroupIndex = 0;

        return TryRenderLabyrinthRouteGroup(routeGroupIndex++);
    }

    bool LabyrinthRenderer::TryRenderLabyrinthRouteGroup(int index)
    {
        HDC hdcMain = BeginPaint(hWnd, &paintStruct);
        auto blockLength = labyrinth.GetBlockStyle().blockLength;
        if (visualInitRequired)
        {
            Graphics graphics(hdcMain);
            GetClientRect(hWnd, &clientRectangle);
            graphics.FillRectangle(
                labyrinthRenderingStyle.backgroundBrush.get(),
                Rect(0, 0, clientRectangle.right - clientRectangle.left, clientRectangle.bottom - clientRectangle.top)
            );

            auto dimensions = labyrinth.GetDimensions();
            graphics.FillRectangle(
                labyrinthRenderingStyle.labyrinthFillBrush.get(),
                Rect(0, 0, blockLength * dimensions.numberOfColumns, blockLength * dimensions.numberOfRows)
            );

            visualInitRequired = false;
        }

        if (index >= routeGroupCount)
            return false;

        auto routeIndices = labyrinth.GetRouteIndicesList(index);
        if (routeIndices == nullptr)
            return false;
        
        for (auto const& routeIndexTuple : *routeIndices)
        {
            auto blockSlot = std::get<0>(routeIndexTuple);
            auto routeIndex = std::get<1>(routeIndexTuple);

            auto hdc = hdcGrid[blockSlot.columnIndex][blockSlot.rowIndex];
            auto routes = labyrinth.GetBlock(blockSlot).GetRoutes();
            auto left = blockSlot.columnIndex * blockLength;
            auto top = blockSlot.rowIndex * blockLength;

            auto bitmap = CreateCompatibleBitmap(hdcMain, blockLength, blockLength);
            SelectObject(hdc, bitmap);
            Graphics graphics(hdc);
            
            graphics.FillRectangle(
                labyrinthRenderingStyle.labyrinthFillBrush.get(),
                Rect(0, 0, blockLength, blockLength)
            );

            for (int i = 0; i <= routeIndex; i++)
            {
                auto rectangles = routes[i].GetRectangles();
                auto count = rectangles.size();
                if (!count)
                    continue;

                graphics.FillRectangles(
                    labyrinthRenderingStyle.pathFillBrush.get(),
                    &ConvertRectangles(rectangles)[0],
                    count
                );

                for (auto const& rectangle : rectangles)
                    for (auto const& line : rectangle.GetBorderLines())
                        graphics.DrawLine(
                            labyrinthRenderingStyle.pathBorderPen.get(),
                            Point(line.from.X, line.from.Y),
                            Point(line.to.X, line.to.Y)
                        );
            }

            // Todo: add some debugging mode settings
            
            /*
            graphics.DrawRectangle(
                labyrinthRenderingStyle.labyrinthBorderPen.get(),
                Rect(0, 0, blockLength, blockLength)
            );
            */

            BitBlt(hdcMain, left, top, left + blockLength, top + blockLength, hdc, 0, 0, SRCCOPY);
            DeleteObject(bitmap);
        }

        return EndPaint(hWnd, &paintStruct);
    }

    vector<RectF> LabyrinthRenderer::ConvertRectangles(const vector<LocalRectangle>& rectangles) const 
    {
        auto gdiRectangles = vector<RectF>();
        for (auto const& rectangle : rectangles)
            gdiRectangles.push_back(ConvertRectangle(rectangle));

        return gdiRectangles;
    }

    RectF LabyrinthRenderer::ConvertRectangle( const LocalRectangle& rectangle) const 
    {
        return RectF(
            rectangle.topLeft.X,
            rectangle.topLeft.Y,
            rectangle.width,
            rectangle.height
        );
    }
}
