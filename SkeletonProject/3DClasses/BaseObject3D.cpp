//=============================================================================
//                              BaseObject3D
//
// Writen by Adi Bar-Lev, 2013
// EGP 300-101, Graphics Programming II  - skeleton project
//
// Base class that can handle 3D rendergin via Vertex and Index buffer
//=============================================================================
#include "BaseObject3D.h"
#include "Vertex.h"
#include "../GfxStats.h"
//=============================================================================
BaseObject3D::BaseObject3D(void)
{
    D3DXMatrixIdentity(&m_World);
	m_Material = 0;
}

//-----------------------------------------------------------------------------
BaseObject3D::~BaseObject3D(void)
{
	ReleaseCOM(m_MeshObject);
}

//-----------------------------------------------------------------------------
void BaseObject3D::Create(IDirect3DDevice9* gd3dDevice)
{
	LoadObject(gd3dDevice);

	ID3DXMesh* clone = 0;

	D3DVERTEXELEMENT9 elements[64];
	UINT numElements = 0;
	VertexNMap::Decl->GetDeclaration(elements, &numElements);
	HR(m_MeshObject->CloneMesh(D3DXMESH_SYSTEMMEM,elements,gd3dDevice, &clone));

	ReleaseCOM(m_MeshObject);

	VertexNMap* vertices = 0;
	HR(clone->LockVertexBuffer(0, (void**)&vertices));

	for (UINT i = 0; i < clone->GetNumVertices(); i++)
	{
		D3DXVECTOR3 p = vertices[i].pos;

		float theta = atan2f(p.z, p.x) + D3DX_PI;
		float phi = acosf(p.y / sqrtf(p.x*p.x + p.y*p.y + p.z*p.z));

		float u = theta / (2.0f*(D3DX_PI));
		float v = phi / D3DX_PI;

		vertices[i].tex0.x = u;
		vertices[i].tex0.y = v;
	}

	HR(clone->UnlockVertexBuffer());

	ID3DXMesh* TNB;
	HR(clone->CloneMesh(D3DXMESH_MANAGED, elements, gd3dDevice, &TNB));
	ReleaseCOM(clone);
	HR(D3DXComputeTangentFrameEx(TNB, D3DDECLUSAGE_TEXCOORD, 0,
		D3DDECLUSAGE_BINORMAL, 0, D3DDECLUSAGE_TANGENT, 0,
		D3DDECLUSAGE_NORMAL, 0, 0, 0, 0.01f, 0.25f, 0.01f,
		&m_MeshObject, 0));

	ReleaseCOM(TNB);
	int mVerts = m_MeshObject->GetNumVertices();
	int mTris = m_MeshObject->GetNumFaces();
	GfxStats::GetInstance()->addVertices(mVerts);
	GfxStats::GetInstance()->addTriangles(mTris);
}

//-----------------------------------------------------------------------------
void BaseObject3D::Render( IDirect3DDevice9* gd3dDevice,
    D3DXMATRIX& view, D3DXMATRIX& projection )
{
	HR(gd3dDevice->SetTransform(D3DTS_WORLD, &m_World));
	HR(gd3dDevice->SetTransform(D3DTS_VIEW, &view));
	HR(gd3dDevice->SetTransform(D3DTS_PROJECTION, &projection));

	// Set matrices and model relevant render date
	if (m_Material != 0)
	{
		m_Material->Render(m_World, m_World*view*projection);
	}

	HR(m_MeshObject->DrawSubset(0));

}
