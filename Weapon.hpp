#pragma once
class CBaseWeapon
{
public:
	bool		IsNotEmpty();

	int			GetAmmo();
	int			GetWeaponId();

	float		GetNextAttack();

	const char* GetName();
	const char* GetPrintName();
	int* GetItemDefinitionIndex();
	int* GetItemIDHigh();
	int* GetAccountID();
	int* GetEntityQuality();
	char* GetCustomName();
	int* GetOriginalOwnerXuidLow();
	int* GetOriginalOwnerXuidHigh();
	int* GetFallbackPaintKit();
	int* GetFallbackSeed();
	float* GetFallbackWear();
	int* GetFallbackStatTrak();
};
enum  WeaponId_t
{
	ITEM_NONE = 0,
	WEAPON_DEAGLE = 1,
	WEAPON_DUALS = 2,
	WEAPON_FIVE7 = 3,
	WEAPON_GLOCK = 4,
	WEAPON_AK47 = 7,
	WEAPON_AUG = 8,
	WEAPON_AWP = 9,
	WEAPON_FAMAS = 10,
	WEAPON_G3SG1 = 11,
	WEAPON_GALIL = 13,
	WEAPON_M249 = 14,
	WEAPON_M4A4 = 16,
	WEAPON_MAC10 = 17,
	WEAPON_P90 = 19,
	WEAPON_UMP45 = 24,
	WEAPON_XM1014 = 25,
	WEAPON_BIZON = 26,
	WEAPON_MAG7 = 27,
	WEAPON_NEGEV = 28,
	WEAPON_SAWEDOFF = 29,
	WEAPON_TEC9 = 30,
	WEAPON_TASER = 31,
	WEAPON_USPS = 32,
	WEAPON_MP7 = 33,
	WEAPON_MP9 = 34,
	WEAPON_NOVA = 35,
	WEAPON_P250 = 36,
	WEAPON_SCAR20 = 38,
	WEAPON_SG553 = 39,
	WEAPON_SCOUT = 40,
	WEAPON_KNIFE_CT = 42,
	WEAPON_FLASH = 43,
	WEAPON_HE = 44,
	WEAPON_SMOKE = 45,
	WEAPON_MOLOTOV = 46,
	WEAPON_DECOY = 47,
	WEAPON_INC = 48,
	WEAPON_C4 = 49,
	WEAPON_KNIFE_T = 59,
	WEAPON_M4A1S = 60,
	WEAPON_P2000 = 61,
	WEAPON_CZ75 = 63,
	WEAPON_REVOLVER = 64,
};

inline bool IsPistol(int id)
{
	switch (id)
	{
	case WEAPON_P2000:
	case WEAPON_DUALS:
	case WEAPON_P250:
	case WEAPON_FIVE7:
	case WEAPON_CZ75:
	case WEAPON_DEAGLE:
	case WEAPON_USPS:
	case WEAPON_GLOCK:
	case WEAPON_TEC9:
	case WEAPON_REVOLVER:
		return true;
	default:
		return false;
	}
}

inline bool IsGrenade(int id)
{
	switch (id)
	{
	case WEAPON_HE:
	case WEAPON_MOLOTOV:
	case WEAPON_SMOKE:
	case WEAPON_FLASH:
	case WEAPON_DECOY:
	case WEAPON_INC:
		return true;
	default:
		return false;
	}
}

inline bool IsKnife(int id) {
	switch (id) {
	case WEAPON_KNIFE_CT:
	case WEAPON_KNIFE_T:
		return true;
	default:
		return false;
	}
}