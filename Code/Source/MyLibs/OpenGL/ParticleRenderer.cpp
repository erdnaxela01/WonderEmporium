#include "ParticleRenderer.h"

ParticleAttributeData::ParticleAttributeData(const char* tname, unsigned short tcount, unsigned short tstride, unsigned short toffset, bool tnormalized, GLenum atribType) :
name(tname), count(tcount), stride(tstride), offset(toffset), normalized(tnormalized), type(atribType)
{

}