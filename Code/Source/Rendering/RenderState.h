#ifndef __RENDER_STATE_H
#define __RENDER_STATE_H

#include "MyLibs\OpenGL\ShaderProgram.h"
#include "MyLibs\OpenGL\UniformBuffer.h"
#include "MyLibs\Math\MatrixStack.h"

namespace WE
{
    //this will be the data passed to all rendering instances
    struct RenderState
    {
        RenderState(MatrixStackf*, UniformBuffer*, MatrixStackf*);
        MatrixStackf* stack;
        MatrixStackf* normalStack;
        UniformBuffer* buffer;
    };
}


#endif //__RENDER_STATE_H