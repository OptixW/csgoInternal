#pragma once

#include "interface.hpp"
#include "Math.hpp"

struct Aimbot
{
	Source::Vector3 calcAngle(const Source::Vector3& source, const Source::Vector3& dst) const;
	void RCS(CUserCmd* pCmd, CBaseEntity* pLocalEntity) const;
	bool CanHit(Source::Vector3 viewangles, CBaseEntity* LocalEntity) const;

	void AimLock(CUserCmd* pCmd, CBaseEntity* pLocalEntity) const;
	Source::Vector3 smoothAngle(const Source::Vector3& currentAngle, float fSmoothPercentage, const Source::Vector3& angles) const;
	bool Visible(const Source::Vector3& vEnd, CBaseEntity* pEntity) const;
};
extern Aimbot* g_aimbot;