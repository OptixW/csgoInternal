#include "Weapon.hpp"



#include "Offsets.hpp"

bool CBaseWeapon::IsNotEmpty()
{
	return (GetAmmo() > 0);
}

int CBaseWeapon::GetAmmo()
{
	return *(int*)(this + netvars::m_iClip1);
}

int CBaseWeapon::GetWeaponId()
{
//todo
	return 0;
}