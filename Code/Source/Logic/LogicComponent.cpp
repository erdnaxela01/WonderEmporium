#include "LogicComponent.h"

namespace WE
{
    LogicComponent::LogicComponent() :m_Enabled(true)
    {

    }

    LogicComponent::~LogicComponent()
    {

    }

    //set if the logic component is enabled
    void LogicComponent::SetEnabled(bool enabled)
    {
        m_Enabled = enabled;
    }

    //check if the logic component is enabled
    bool LogicComponent::IsEnabled()
    {
        return m_Enabled;
    }
}