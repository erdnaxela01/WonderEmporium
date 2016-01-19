#include "PlatformPiece.h"

using namespace WE;

namespace Game
{
	PlatformPiece::PlatformPiece(vec3f size) :
		m_Entity("Platform Piece"),
		m_Model("cube.obj",size),
		m_Body(1, New btDefaultMotionState(), New btBoxShape(btVector3(size.x, size.y, size.z) / Config::s_PPM)),
		m_Tag(CollisionTag::FloorTag)
	{
		m_Entity.AddComponent(&m_Model);
		m_Entity.AddComponent(&m_Body);
		m_Entity.AddComponent(&m_Tag);
		
		m_Node = New Node(&m_Entity);
		m_Entity.AddComponent(m_Node);
		m_Body.GetRigidBody().setLinearFactor(btVector3(0.0f, 0.0f, 0.0f));
        //m_Entity.AddComponent(&m_Collider);
		CheckForGLErrors();
	}

	PlatformPiece::~PlatformPiece()
	{
		SafeDelete(m_Node);
	}

	Entity* PlatformPiece::GetEntity()
	{
		return &m_Entity;
	}

	RigidBodyComponent* PlatformPiece::GetBody()
	{
		return &m_Body;
	}
}