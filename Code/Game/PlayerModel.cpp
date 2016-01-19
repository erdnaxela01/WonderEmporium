#include "PlayerModel.h"

namespace Game
{
    const std::string PlayerModel::PLAYER_SHADERS[2] = {"Player.GVert", "Player.GFrag"};
    const float PlayerModel::AMPLITUDE = 200.0;

    PlayerModel::PlayerModel(PlayerLogic* logic, const char* model, vec3f dimensions) :ModelComponent(model, dimensions, { PLAYER_SHADERS[0].c_str(), PLAYER_SHADERS[1].c_str() }),
        m_Logic(logic), m_Amplitude(AMPLITUDE)
    {
        m_Logic->SetTotalTime(1.0f);
    }

    PlayerModel::~PlayerModel()
    {

    }

    void PlayerModel::ActivateAmplitude(bool b)
    {
        //casts the bool to a 1 or 0 to set or unset the amplitude
        m_Amplitude = AMPLITUDE * (int)b;
    }

    void PlayerModel::SetState(WE::RenderState* state)
    {
        ModelComponent::SetState(state);

        /*if (m_Logic->GetTime() == 0.0f)
        {
            m_Amplitude = 0.0f;
        }*/

        int loc = glGetUniformLocation(GetProgram()->GetProgram(), "u_TotalTime");
        glUniform1f(loc, m_Logic->GetTotalTime());

        loc = glGetUniformLocation(GetProgram()->GetProgram(), "u_DeltaTime");
        glUniform1f(loc, m_Logic->GetTime());


    }
}