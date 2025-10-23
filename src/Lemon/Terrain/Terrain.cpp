#include "Terrain.h"

#include "GpuVertTypes.h"
#include "Tools/Colors.h"
#include "Asset Management/ShaderManager.h"
#include "Scene/SceneManager.h"
#include "Tools/Visualizer/Visualizer.h"
#include "Collision/Volumes/CollisionVolumeBSphere.h"
#include "Tools/LemonMath.h"
#include "AreaIterator.h"
#include "Area.h"

#include "../Game/Frigate.h"

Terrain::Terrain(const char* heightmapFile, float sideLen, float maxHeight, float yTrans, int repeatU, int repeatV, Texture* pTex, Vect pos)
	: m_wireframe(false), m_world(Matrix(TRANS, pos)), m_showCells(false), m_sideLen(sideLen), m_worldInv(m_world.getInv())
{
	// read heightmap image data
	char fullpath[128];
	strcpy_s(fullpath, heightmapFile);
	int imgWidth, imgHeigth, icomp;
	unsigned int dtype;
	GLbyte* imgData = gltReadTGABits(fullpath, &imgWidth, &imgHeigth, &icomp, &dtype);
	assert(imgWidth == imgHeigth && imgWidth != 0); // We need square images for heightmaps

	m_numVerts = imgWidth * imgWidth;
	VertexStride_VUN* pVerts = new VertexStride_VUN[m_numVerts];

	int numTris = (imgWidth - 1) * (imgWidth - 1) * 2;
	TriangleIndex* pTriList = new TriangleIndex[numTris];

	// set verts
	for (int y = 0; y < imgWidth; y++) // for each vert row
	{
		for (int x = 0; x < imgWidth; x++) // for each vert in row
		{
			// find height value
			int ind = 3 * (x + ((imgWidth - 1 - y) * imgWidth)); // convert our actual index to image index because array is bottom row first...
			unsigned char hval = static_cast<unsigned char>(imgData[ind]);
			// find coordinates
			float offset = sideLen * 0.5f;
			float posY = ((hval * maxHeight) / 255) + yTrans;
			float posX = -x * (sideLen / (imgWidth - 1)) + offset;
			float posZ = -y * (sideLen / (imgWidth - 1)) + offset;
			// find uvs
			float u = float(x) / (imgWidth - 1) * repeatU;
			float v = -float(y) / (imgWidth - 1) * repeatV;
			int index = x + (y * imgWidth);
			pVerts[index].set(posX, posY, posZ, u, v, 0.0f, 1.0f, 0.0f);
		}
	}
	
	// set tris, bounding boxes per cell, and face normals per tri
	int triIndex = 0;
	m_numCells = (imgWidth - 1) * (imgWidth - 1);
	m_numTris = m_numCells * 2;
	m_cellBoxes = new CollisionVolumeAABB[m_numCells];
	Vect* faceNormals = new Vect[m_numTris];
	m_normals = new Vect[m_numVerts];
	m_cellsPerSide = imgWidth - 1;

	for (int r = 0; r < imgWidth - 1; r++) // for each row of cells
	{
		for (int c = 0; c < imgWidth - 1; c++) // for each cell in row
		{
			// get verts of cell
			// v0 v1
			// v2 v3
			int v0, v1, v2, v3;
			v0 = r * imgWidth + c;
			v1 = v0 + 1;
			v2 = (r + 1) * imgWidth + c;
			v3 = v2 + 1;


			// set tris and face normals of cell
			Vect na, nb;

			// set tri
			pTriList[triIndex].set(v0, v2, v1); 
			// compute and set face normal
			na = Vect(pVerts[v1].x, pVerts[v1].y, pVerts[v1].z) - Vect(pVerts[v0].x, pVerts[v0].y, pVerts[v0].z);
			nb = Vect(pVerts[v2].x, pVerts[v2].y, pVerts[v2].z) - Vect(pVerts[v0].x, pVerts[v0].y, pVerts[v0].z);
			faceNormals[triIndex] = nb.cross(na).getNorm();
			triIndex++;

			// set tri
			pTriList[triIndex].set(v1, v2, v3);
			// compute and set face normal
			na = Vect(pVerts[v3].x, pVerts[v3].y, pVerts[v3].z) - Vect(pVerts[v1].x, pVerts[v1].y, pVerts[v1].z);
			nb = Vect(pVerts[v2].x, pVerts[v2].y, pVerts[v2].z) - Vect(pVerts[v1].x, pVerts[v1].y, pVerts[v1].z);
			faceNormals[triIndex] = nb.cross(na).getNorm();
			triIndex++;

			// set temp vert normals
			m_normals[v0] = Vect(0, 1, 0);
			m_normals[v1] = Vect(0, 1, 0);
			m_normals[v2] = Vect(0, 1, 0);
			m_normals[v3] = Vect(0, 1, 0);

			// set cell AABB
			int cellIndex = r * (imgWidth - 1) + c;
			SetCellAABB(cellIndex, v0, v1, v2, v3, pVerts);
		}
	}

	// create proper vert normals from face normals
	triIndex = 0;
	int trisPerRow = m_cellsPerSide * 2;
	for (int r = 0; r < imgWidth - 2; r++) // for each row of cells, except the bottom row
	{
		for (int c = 0; c < imgWidth - 2; c++) // for each cell in row, except the right col
		{	
			// vert to assign
			int v = (r + 1) * imgWidth + c + 1;
			// surrounding triangle indices
			int t0 = (trisPerRow * r) + (c * 2) + 1;
			int t1 = t0 + 1;
			int t2 = t0 + 2;
			int t3 = (trisPerRow * (r + 1)) + (c * 2) + 1;
			int t4 = t3 + 1;
			int t5 = t3 + 2;

			Vect avg = (faceNormals[t0] + faceNormals[t1] + faceNormals[t2] + faceNormals[t3] + faceNormals[t4] + faceNormals[t5]);
			avg.set(avg.X() / 6, avg.Y() / 6, avg.Z() / 6);
			avg.norm();

			m_normals[v] = avg;
		}
	}

	m_cellsPerSide = imgWidth - 1;
	m_min = Vect(pVerts[m_numVerts - 1].x, pVerts[m_numVerts - 1].y, pVerts[m_numVerts - 1].z); // bottom right
	m_max = Vect(pVerts[0].x, pVerts[0].y, pVerts[0].z); // top left

	// finally create model and graphics object
	m_pModel = new Model(pVerts, m_numVerts, pTriList, numTris);
	m_pGraphicsObj = new GraphicsObject_TextureFlat(m_pModel, ShaderManager::Get("LEMON_DEFAULT_TEXTURE"), pTex);
	m_pGraphicsObj->SetWorld(m_world);
	// create debug wireframe model
	Vect col = Colors::LightSlateGray;
	m_pGraphicsObjWF = new GraphicsObject_WireframeConstantColor(m_pModel, ShaderManager::Get("LEMON_DEFAULT_COLOR_CONSTANT"), col);
	m_pGraphicsObjWF->SetWorld(m_world);
	delete[] pVerts;
	delete[] pTriList;
	delete[] faceNormals;

	//ToggleWireframe();
}

Terrain::~Terrain()
{
	delete m_pModel;
	delete m_pGraphicsObj;
	delete m_pGraphicsObjWF;
	delete[] m_cellBoxes;
	delete[] m_normals;
}

void Terrain::Draw()
{
	if (m_wireframe) m_pGraphicsObjWF->Render(SceneManager::GetActiveCamera());
	else m_pGraphicsObj->Render(SceneManager::GetActiveCamera());

	if (m_showCells)
	{
		for (int i = 0; i < m_numCells; i++)
		{
			Visualizer::ShowAABB(m_cellBoxes[i]);
		}
	}
}

void Terrain::ToggleWireframe()
{
	if (m_wireframe) m_wireframe = false;
	else m_wireframe = true;
}

void Terrain::ToggleBoxes()
{
	if (m_showCells) m_showCells = false;
	else m_showCells = true;
}

void Terrain::SetCellAABB(int cellInd, int v0, int v1, int v2, int v3, VertexStride_VUN* pVerts)
{
	Vect min, max;

	// compute min
	min[x] = pVerts[v3].x;
	min[y] = std::min({
		pVerts[v0].y,
		pVerts[v1].y,
		pVerts[v2].y,
		pVerts[v3].y
		});
	min[z] = pVerts[v3].z;

	// compute max
	max[x] = pVerts[v0].x;
	max[y] = std::max({
		pVerts[v0].y,
		pVerts[v1].y,
		pVerts[v2].y,
		pVerts[v3].y
		});
	max[z] = pVerts[v0].z;

	// transform to world space
	min *= m_world;
	max *= m_world;
	m_cellBoxes[cellInd].Set(min, max);
}

CollisionVolumeAABB& Terrain::Cell(int i, int j) const
{
	return m_cellBoxes[i * (m_cellsPerSide) + j];
}

int Terrain::Tri(int i, int j) const
{
	return i * (m_cellsPerSide + 1) + j;
}

void Terrain::ShowCell(const CellIndex& ind) const
{
	Visualizer::ShowAABB(Cell(ind.i, ind.j));
}

Terrain::CellIndex Terrain::CellAt(const Vect& pos) const
{
	Vect posLocal = pos * m_worldInv;

	// shift so origin is at corner
	posLocal.set(posLocal.X() + m_max.X(), posLocal.Y(), posLocal.Z() + m_max.Z());
	
	int row = int((posLocal.Z() * m_cellsPerSide) / m_sideLen);
	row = (m_cellsPerSide - 1) - row;
	int col = int((posLocal.X() * m_cellsPerSide) / m_sideLen);
	col = (m_cellsPerSide - 1) - col;
	
	// ensure indices are in bounds
	row = LemonMath::Clamp(row, 0, m_cellsPerSide - 1);
	col = LemonMath::Clamp(col, 0, m_cellsPerSide - 1);

	Vect v0 = m_pModel->getVectList()[Tri(row, col)] * m_world;
	Vect v1 = m_pModel->getVectList()[Tri(row + 1, col)] * m_world;
	Vect v2 = m_pModel->getVectList()[Tri(row, col + 1)] * m_world;
	Vect v3 = m_pModel->getVectList()[Tri(row + 1, col + 1)] * m_world;
	
	return CellIndex(row, col);
}

Vect Terrain::NormAt(const Vect& pos) const
{
	Vect posLocal = pos * m_worldInv;

	// shift so origin is at corner
	posLocal.set(posLocal.X() + m_max.X(), posLocal.Y(), posLocal.Z() + m_max.Z());

	int row = int((posLocal.Z() * m_cellsPerSide) / m_sideLen);
	row = (m_cellsPerSide - 1) - row;
	int col = int((posLocal.X() * m_cellsPerSide) / m_sideLen);
	col = (m_cellsPerSide - 1) - col;

	// ensure indices are in bounds
	row = LemonMath::Clamp(row, 0, m_cellsPerSide - 1);
	col = LemonMath::Clamp(col, 0, m_cellsPerSide - 1);

	Vect v0 = m_pModel->getVectList()[Tri(row, col)] * m_world;
	Vect v1 = m_pModel->getVectList()[Tri(row + 1, col)] * m_world;
	Vect v2 = m_pModel->getVectList()[Tri(row, col + 1)] * m_world;
	Vect v3 = m_pModel->getVectList()[Tri(row + 1, col + 1)] * m_world;

	// identify triangle
	Vect v = pos - v1;
	Vect pa, pb, pc, Qa, Qb, Qc;
	if (-v.X() > v.Z())
	{
		pa = v1;
		pb = v3;
		pc = v2;

		Qa = m_normals[Tri(row + 1, col)];
		Qb = m_normals[Tri(row + 1, col + 1)];
		Qc = m_normals[Tri(row, col + 1)];
	}
	else
	{
		pa = v1;
		pb = v0;
		pc = v2;

		Qa = m_normals[Tri(row + 1, col)];
		Qb = m_normals[Tri(row, col)];
		Qc = m_normals[Tri(row, col + 1)];
	}

	Vect pos1 = pos;
	pos1[y] = pa.Y();

	float ssqr = (m_sideLen / m_cellsPerSide) * (m_sideLen / m_cellsPerSide);
	float beta = ((pos1 - pa).dot((pb - pa))) / ssqr;
	float gamma = ((pos1 - pa).dot((pc - pb))) / ssqr;

	Vect Qp = Qa + beta * (Qb - Qa) + gamma * (Qc - Qb);

	return Qp;
}

float Terrain::HeightAt(const Vect& pos) const
{
	Vect posLocal = pos * m_worldInv;

	// shift so origin is at corner
	posLocal.set(posLocal.X() + m_max.X(), posLocal.Y(), posLocal.Z() + m_max.Z());

	int row = int((posLocal.Z() * m_cellsPerSide) / m_sideLen);
	row = (m_cellsPerSide - 1) - row;
	int col = int((posLocal.X() * m_cellsPerSide) / m_sideLen);
	col = (m_cellsPerSide - 1) - col;

	// ensure indices are in bounds
	row = LemonMath::Clamp(row, 0, m_cellsPerSide - 1);
	col = LemonMath::Clamp(col, 0, m_cellsPerSide - 1);

	Vect v0 = m_pModel->getVectList()[Tri(row, col)] * m_world;
	Vect v1 = m_pModel->getVectList()[Tri(row + 1, col)] * m_world;
	Vect v2 = m_pModel->getVectList()[Tri(row, col + 1)] * m_world;
	Vect v3 = m_pModel->getVectList()[Tri(row + 1, col + 1)] * m_world;

	// identify triangle
	Vect v = pos - v1;
	Vect pa, pb, pc, Qa, Qb, Qc;
	if (-v.X() > v.Z())
	{
		pa = v1;
		pb = v3;
		pc = v2;
	}
	else
	{
		pa = v1;
		pb = v0;
		pc = v2;
	}
	Qa = Vect(0, pa.Y(), 0);
	Qb = Vect(0, pb.Y(), 0);
	Qc = Vect(0, pc.Y(), 0);

	float ssqr = (m_sideLen / m_cellsPerSide) * (m_sideLen / m_cellsPerSide);

	Vect pos1 = pos;
	pos1[y] = pa.Y();
	float beta = ((pos1 - pa).dot((pb - pa))) / ssqr;
	float gamma = ((pos1 - pa).dot((pc - pb))) / ssqr;

	Vect Qp = Qa + (beta * (Qb - Qa)) + (gamma * (Qc - Qb));

	return Qp.Y();
}

Area Terrain::CandidateArea(Collidable* pObj) const
{
	// Checking AABB based off BSphere
	Vect center = pObj->GetBSphere().GetCenter();
	float radius = pObj->GetBSphere().GetRadius();

	CellIndex min = CellAt(Vect(
		center.X() - radius,
		center.Y() - radius,
		center.Z() - radius
	));

	CellIndex max = CellAt(Vect(
		center.X() + radius,
		center.Y() + radius,
		center.Z() + radius
	));

	return Area(this, max, min); // max/min swapped for i/j because higher x/z values are closer to top left of terrain (i = 0, j = 0)
}

CollisionVolumeAABB& Terrain::CellAABB(const CellIndex& cell) const
{
	return Cell(cell.i, cell.j);
}
