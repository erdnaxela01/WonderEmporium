#ifndef __PLAYER_MODEL_H
#define __PLAYER_MODEL_H

#include "../Source/Rendering/ModelComponent.h"

#include "PlayerLogic.h"

namespace Game
{
    //handles the model and sending uniforms off to the shader
    class PlayerModel : public WE::ModelComponent
    {
    public:
        PlayerModel(PlayerLogic* logic, const char* model, vec3f dimensions = vec3f(1.0f, 1.0f, 1.0f));

        virtual ~PlayerModel();

        //set the uniform for the amplitude
        virtual void SetState(WE::RenderState* state);

        //activate the amplitude
        void ActivateAmplitude(bool b);
    private:
        static const std::string PLAYER_SHADERS[2];
        static const float AMPLITUDE;

        float m_Amplitude;
        PlayerLogic* m_Logic;

    };
}

#endif //__PLAYER_MODEL_H