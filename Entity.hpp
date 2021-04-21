#pragma once
#include <Windows.h>

#include "Offsets.hpp"
#include "interface.hpp"
#include "Weapon.hpp"

class CBaseEntity
{
public:
	bool				IsPlayer();
	bool                IsValid();
	bool                IsDormant();
	bool				IsDead();
	bool				IsDefusing();

	int					GetArmor();
	bool				HasHelmet();
	int					GetFlags();
	int					GetHealth();
	int					GetTeamNum();
	int					GetTickBase();
	float				GetBombTimer();
	int					GetHitboxSet();
	int					GetShotsFired();
	bool				IsBroken();
	int					GetCollisionGroup();
	int					GetCrosshairID();
	Source::Vector3		GetAbsAngles();
	Source::Vector3		GetAbsOrigin();
	Source::Vector3		GetEyePosition();
	Source::Vector3		GetViewOffset();
	Source::Vector3		GetVelocity();
	Source::Vector3		GetPunchAngle();
	Source::Vector3		GetBonePosition(int nBone);
	bool SetupBones(Source::matrix3x4_t* pMatrix, int nMaxBones, int nMask, float fTime);
	Source::Vector3		GetHitboxPosition(int nHitbox);

	DWORD_PTR			GetActiveWeapon();
	CBaseWeapon* GetBaseWeapon(IClientEntityList* lst);
	CUserCmd*& m_pCurrentCommand();

	UINT* GetWeapons();

	void* GetRenderable();
	void* GetNetworkable();
	UINT				PhysicsSolidMaskForEntity(void);
};