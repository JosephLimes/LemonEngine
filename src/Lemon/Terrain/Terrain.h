#ifndef _Terrain
#define _Terrain

#include "AzulCore.h"
#include "TextureTGA.h"
#include "GameObject/GameObject.h"
#include "Collision/Volumes/CollisionVolumeAABB.h"

class Frigate;
class Area;
class AreaIterator;

class Terrain
{
public:
	struct CellIndex
	{
		int i;
		int j;

		CellIndex(int _i, int _j) : i(_i), j(_j) {}
		bool operator==(const CellIndex& other) { return i == other.i && j == other.j; }
		bool operator!=(const CellIndex& other) { return i != other.i || j != other.j; }
	};

	Terrain(const char* heightmapFile, float sideLen, float maxHeight, float yTrans, int repeatU, int repeatV, Texture* pTex, Vect pos = Vect(0,0,0));
	Terrain() = delete;
	Terrain(const Terrain&) = default;
	Terrain& operator = (const Terrain&) = default;
	~Terrain();

	void						Draw();
	// debugging
	void						ToggleWireframe();
	void						ToggleBoxes();

private:
	GraphicsObject_TextureFlat* m_pGraphicsObj;
	Model*						m_pModel;
	Matrix						m_world;
	CollisionVolumeAABB*		m_cellBoxes;

	// Debugging fields
	GraphicsObject_WireframeConstantColor* m_pGraphicsObjWF;
	bool						m_wireframe;
	bool						m_showCells;
	int							m_numCells;
	int							m_numVerts;
	int							m_numTris;

	// for cell collision
	float						m_sideLen;
	int							m_cellsPerSide;
	Vect						m_min;
	Vect						m_max;
	Matrix						m_worldInv;

	// normals
	Vect*						m_normals;

	void						SetCellAABB(int cellInd, int v0, int v1, int v2, int v3, VertexStride_VUN* pVerts);

	// private accessors
	CollisionVolumeAABB&		Cell(int i, int j) const;
	int							Tri(int i, int j) const;

public:
	void						ShowCell(const CellIndex& ind) const;
	CellIndex					CellAt(const Vect& pos) const;
	Vect						NormAt(const Vect& pos) const;
	float						HeightAt(const Vect& pos) const;

	// collision
	Area						CandidateArea(Collidable* pObj) const;

	// public accessor
	CollisionVolumeAABB&		CellAABB(const CellIndex& cell) const;
};



#endif _Terrain