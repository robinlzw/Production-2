//=============================================================================
//                          MainSystem.h
//
// Created by Jesse McKinley, Edited by Abner, 2015
// EGP-300-101 - Computer Graphics II, Spring 2015.
//
// This program creates a solar system workspace.
//
//=============================================================================
#pragma once

#include "d3dApp.h"
#include <vector>
#include "SolarSystem.h"

class MainSystem : public D3DApp
{
public:
	MainSystem(HINSTANCE hInstance, std::string winCaption, D3DDEVTYPE devType, DWORD requestedVP);
	~MainSystem();

	bool checkDeviceCaps();
	void onLostDevice();
	void onResetDevice();
	void updateScene(float dt);
	void drawScene();


	void buildViewMtx();
	void buildProjMtx();
private:

	SolarSystem* mpSolarSystem;

	float mCameraRotationY;
	float mCameraRotationX;
	float mCameraRadius;

	bool i_Solid_frame;


	D3DXMATRIX mView;
	D3DXMATRIX mProj;
	D3DXMATRIX mWorld;

};