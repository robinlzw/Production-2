//=============================================================================
//                             Cone
//
// Writen by Jesse McKinley, 2015
// EGP 300-101, Graphics Programming II  - skeleton project
//
// inherites from BaseObject3D class
//=============================================================================
#ifndef _CYLINDER_OBJECT_3D_H
#define _CYLINDER_OBJECT_3D_H
//=============================================================================
#pragma once
//=============================================================================
#include "3DClasses\BaseObject3D.h"
//=============================================================================
struct IDirect3DVertexBuffer9;
struct IDirect3DIndexBuffer9;
//=============================================================================
class Cylinder : public BaseObject3D
{
private:
	float mHeight;
	float mRadius;
	int mSideFacetsNum;

protected:

	void LoadObject(IDirect3DDevice9* gd3dDevice);

public:
	Cylinder(int height = 6, float radius = 1, int sideFacetsNum = 12);
	~Cylinder(void);

};
//=============================================================================
#endif // _BASE_OBJECT_3D_H