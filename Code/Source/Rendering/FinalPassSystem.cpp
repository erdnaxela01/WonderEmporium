#include "FinalPassSystem.h"

namespace WE
{
    FinalPassSystem::FinalPassSystem(DeferedRenderer* renderer) :m_Renderer(renderer)
    {

    }

    std::vector<SystemCallback*> FinalPassSystem::GetCallbacks()
    {
        return{ New SystemCallback(&FinalPassSystem::Render, this) };
    }

    void FinalPassSystem::Render()
    {
        m_Renderer->FinalPass();
    }
}