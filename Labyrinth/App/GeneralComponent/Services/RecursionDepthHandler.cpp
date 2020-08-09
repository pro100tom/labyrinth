#include "RecursionDepthHandler.h"

namespace TomasBaranauskas::LabyrinthApp::GeneralComponent::Services
{
    RecursionDepthHandler::RecursionDepthHandler() :
        RecursionDepthHandler::RecursionDepthHandler(1)
    {

    }

    RecursionDepthHandler::RecursionDepthHandler(int depthIndexLimit) :
        depthIndex(0)
    {
        if (depthIndexLimit < 1)
            depthIndexLimit = 1;

        this->depthIndexLimit = depthIndexLimit;
    }

    RecursionDepthHandler::RecursionDepthHandler(const RecursionDepthHandler& recursionDepthSettings) :
        depthIndex(recursionDepthSettings.GetDepthIndex()),
        depthIndexLimit(recursionDepthSettings.GetDepthIndexLimit())
    {

    }

    bool RecursionDepthHandler::TryIncrementDepthIndex()
    {
        if (depthIndex + 1 >= depthIndexLimit)
            return false;

        return ++depthIndex;
    }

    bool RecursionDepthHandler::CanIncrement() const
    {
        return GetDepthIndex() != GetDepthIndexLimit();
    }

    int RecursionDepthHandler::GetDepthIndex() const
    {
        return depthIndex;
    }

    int RecursionDepthHandler::GetDepthIndexLimit() const
    {
        return depthIndexLimit;
    }
}
