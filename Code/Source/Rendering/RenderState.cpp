#include "RenderState.h"
namespace WE
{
    RenderState::RenderState(MatrixStackf* m, UniformBuffer* s, MatrixStackf* n) :stack(m), buffer(s), normalStack(n)
    {

    }
}