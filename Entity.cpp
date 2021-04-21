#include "Entity.hpp"

#include <cstdint>

#include "Weapon.hpp"

bool CBaseEntity::IsPlayer()
{
	typedef bool(__thiscall* IsPlayerFn)(void*);
	return call_vfunc<IsPlayerFn>(this, 152)(this);
}
bool CBaseEntity::IsValid()
{
	return (IsDead() == 0 && GetHealth() >= 1 && !IsDormant()) ? true : false;
}
bool CBaseEntity::IsDormant()
{
	typedef bool(__thiscall* IsDormantFn)(void*);
	void* pNetworkable = GetNetworkable();
	return call_vfunc<IsDormantFn>(pNetworkable, 9)(pNetworkable);
}

bool CBaseEntity::IsDead()
{
	return *(bool*)(this + netvars::m_lifeState);
}

bool CBaseEntity::IsDefusing()
{
	return *(bool*)(this + netvars::m_bIsDefusing);
}

int CBaseEntity::GetArmor()
{
	return *(int*)(this + netvars::m_ArmorValue);
}

bool CBaseEntity::HasHelmet()
{
	return *(bool*)(this + netvars::m_bHasHelmet);
}

int CBaseEntity::GetFlags()
{
	return *(int*)(this + netvars::m_fFlags);
}

int CBaseEntity::GetHealth()
{
	return *(int*)(this + netvars::m_iHealth);
}

int CBaseEntity::GetTeamNum()
{
	return *(int*)(this + netvars::m_iTeamNum);
}

int CBaseEntity::GetTickBase()
{
	return *(int*)(this + netvars::m_nTickBase);
}

int CBaseEntity::GetShotsFired()
{
	return *(int*)(this + netvars::m_iShotsFired);
}

int CBaseEntity::GetCollisionGroup()
{
	return *(int*)(this + netvars::m_CollisionGroup);
}

int CBaseEntity::GetCrosshairID()
{
	return *(int*)(this + netvars::m_iCrosshairId);
}

Source::Vector3 CBaseEntity::GetAbsAngles()
{
	Source::Vector3 angles;
	angles.x = *(float*)(this + netvars::m_angEyeAnglesX);
	angles.y = *(float*)(this + netvars::m_angEyeAnglesY);
	return angles;
}
DWORD_PTR CBaseEntity::GetActiveWeapon()
{
	return *(uintptr_t*)(this + netvars::m_hActiveWeapon);
}
CBaseWeapon* CBaseEntity::GetBaseWeapon(IClientEntityList* lst)
{
	return (CBaseWeapon*)lst->GetClientEntityFromHandle(GetActiveWeapon());
}
Source::Vector3 CBaseEntity::GetPunchAngle()
{
	return *(Source::Vector3*)(this + netvars::m_aimPunchAngle);
}

Source::Vector3 CBaseEntity::GetEyePosition()
{
	return GetAbsOrigin() + GetViewOffset() + GetVelocity() * pServer->interval_per_tick;
}

Source::Vector3 CBaseEntity::GetAbsOrigin()
{
	return *(Source::Vector3*)(this + netvars::m_vecOrigin);
}
Source::Vector3 CBaseEntity::GetBonePosition(int bone)
{
	Source::matrix3x4_t matrix[128];

	Source::Vector3 ret;

	if (!SetupBones(matrix, 128, 0x100, GetTickBase() * pServer->interval_per_tick))
		return ret;

	ret.Init(matrix[bone][0][3], matrix[bone][1][3], matrix[bone][2][3]);

	return ret;
}
bool CBaseEntity::SetupBones(Source::matrix3x4_t* pMatrix, int nMaxBones, int nMask, float fTime)
{
	typedef bool(__thiscall* SetupBonesFn)(void*, Source::matrix3x4_t*, int, int, float);
	return call_vfunc<SetupBonesFn>(GetRenderable(), 13)(GetRenderable(), pMatrix, nMaxBones, nMask, fTime);
}
Source::Vector3 CBaseEntity::GetViewOffset()
{
	return *(Source::Vector3*)(this + netvars::m_vecViewOffset);
}

Source::Vector3 CBaseEntity::GetVelocity()
{
	return *(Source::Vector3*)(this + netvars::m_vecVelocity);
}
void* CBaseEntity::GetRenderable()
{
	return (void*)(this + 4);
}
void* CBaseEntity::GetNetworkable()
{
	return (void*)(this + 8);
}