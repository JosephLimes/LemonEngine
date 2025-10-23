#ifndef _Frigate
#define _Frigate

#include "GameObject\GameObject.h"
#include "Tools/Editor/LevelObject.h"

class Axis;
class CollisionVolumeBSphere;
class Terrain;
class EditorAdmin;

class Frigate : public LevelObject
{
public:
	Terrain* pTerrain;

	Frigate();
	Frigate(const Frigate&) = delete;
	Frigate& operator = (const Frigate&) = delete;
	~Frigate();

	// Level editor
	DEF_FUNC_LVL_ID
	void									LevelInitialize() override;
	void									LevelTerminate() override;
	//void									DrawEditor3D() override;

	// Game object
	void									SceneEntry() override;
	void									SceneExit() override;

	void									Draw3D() override;

	void									Update() override;
	void									Collision(Axis*);
	void									Collision(Frigate*);
	void									Collision();
	void									CollisionTerrain() override;

	// Convenience for testing
	void									SetWorld(Matrix& world);
	void									SetActive(bool state);
private:
	bool									m_active;
	bool									m_colliding;

	GraphicsObject_TextureLight*			m_pGraphicsObjLight;
	GraphicsObject_TextureLight*			m_pGOeditor;

	Matrix									m_shipRotTrans;
	Matrix									m_shipScale;

	const float								m_shipTransSpeed = 200.0f;
	const float								m_shipRotAng = .03f;

	Camera*									m_pFollowCam;
};

#endif _Frigate