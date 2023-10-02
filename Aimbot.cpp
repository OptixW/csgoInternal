#include "Aimbot.hpp"

#include "Entity.hpp"
#define	HITGROUP_GENERIC	0
#define	HITGROUP_HEAD		1
#define	HITGROUP_CHEST		2
#define	HITGROUP_STOMACH	3
#define HITGROUP_LEFTARM	4
#define HITGROUP_RIGHTARM	5
#define HITGROUP_LEFTLEG	6
#define HITGROUP_RIGHTLEG	7
#define HITGROUP_GEAR		10


Source::Vector3 Aimbot::calcAngle(const Source::Vector3& source, const Source::Vector3& dst) const
{
    Source::Vector3 delta = source - dst;

    float hypotenuse = std::hypot(delta.x, delta.y);
    Source::Vector3 result;

    result.x = RAD2DEG(std::atan2(delta.z, hypotenuse));
    result.y = RAD2DEG(std::atan2(delta.y, delta.x));
    result.z = 0.0f;

    return result;
}

void Aimbot::RCS(CUserCmd* pCmd, CBaseEntity* pLocalEntity) const
{
    static Source::Vector3 previousPunch;
    static Source::Vector3 viewWithPreviousPunch;

    if (pLocalEntity->GetShotsFired() <= 1)
    {
        previousPunch = {0, 0, 0};
        return;
    }

    const auto currentPunch = pLocalEntity->GetPunchAngle() * 2.0f;

    auto compensatedView = pCmd->viewangles + previousPunch - currentPunch;
    Source::ClampAngles(compensatedView);

    pCmd->viewangles = compensatedView;
    p_Client->SetViewAngles(compensatedView);

    previousPunch = currentPunch;
}


bool Aimbot::CanHit(Source::Vector3 viewangles, CBaseEntity* LocalEntity) const
{
	CBaseEntity* pLocalEntity = LocalEntity;

	Ray_t pRay;
	trace_t pTrace;
	CTraceFilter pTraceFilter((CBaseEntity*)pLocalEntity);

	viewangles += pLocalEntity->GetPunchAngle() * 2.0f;

	Source::Vector3 vEnd;

	AngleVector(viewangles, vEnd);

	Source::Vector3 vStart = pLocalEntity->GetEyePosition();

	vEnd = vEnd * 8192.0f + vStart;
	pRay.Init(vStart, vEnd);
	if (!ptrace)
		return false;

	ptrace->TraceRay(pRay, 0x4600400B, &pTraceFilter, &pTrace);

	CBaseEntity* pEntity = (CBaseEntity*)pTrace.m_pEnt;

	if (!pEntity)
		return false;
	//
	if (pEntity->GetTeamNum() == pLocalEntity->GetTeamNum())
		return false;

	if (pTrace.hitgroup > 0 && pTrace.hitgroup < 8)
		return true;

	return false;
}

void Aimbot::AimLock(CUserCmd* pCmd, CBaseEntity* pLocalEntity) const
{
	if (CanHit(pCmd->viewangles, pLocalEntity))
	{
		CBaseEntity* pEnt = p_Entity->GetClientEntity(pLocalEntity->GetCrosshairID());

		if (!pEnt->IsValid())
			return;
		if (GetAsyncKeyState(0x01) & 0x8000)
		{
			auto Angles = calcAngle(pLocalEntity->GetEyePosition(), pEnt->GetBonePosition(7));
			Angles = smoothAngle(pCmd->viewangles, 15, Angles);
			if (pEnt->IsDead())
				return;
			pCmd->viewangles = Angles;
			p_Client->SetViewAngles(pCmd->viewangles);
		}
	}
}

Source::Vector3 Aimbot::smoothAngle(const Source::Vector3& currentAngle, float fSmoothPercentage, const Source::Vector3& angles) const
{
	const float smoothing = fSmoothPercentage;
	const Source::Vector3 viewangles = currentAngle;

	Source::Vector3 delta = angles - viewangles;

	auto target_pitch = angles.y;
	auto view_pitch = viewangles.y;

	auto smooth_factor = 100.f;
	Source::Vector3 result;

	if (angles.y < 0) target_pitch = 360.f + angles.y;
	if (viewangles.y < 0) view_pitch = 360.f + viewangles.y;

	float pitch = min(abs(target_pitch - view_pitch), 360.f - abs(target_pitch - view_pitch));

	if (viewangles.y > 90.f && angles.y < -90.f)
	{
		result.x = viewangles.x + delta.x / smooth_factor * smoothing;
		result.y = viewangles.y + pitch / smooth_factor * smoothing;
		if (angles.y > 180.f)
			result.y = -360.f + angles.y;
		return result;
	}
	if (viewangles.y < -90.f && angles.y > 90.f)
	{
		result.x = viewangles.x + delta.x / smooth_factor * smoothing;
		result.y = viewangles.y - pitch / smooth_factor * smoothing;
		if (angles.y < -180.f)
			result.y = 360.f + angles.y;
		return result;
	}

	result.x = viewangles.x + delta.x / smooth_factor * smoothing;
	result.y = viewangles.y + delta.y / smooth_factor * smoothing;
	result.z = 0.0f;
	ClampAngles(result);
	return result;
}

bool Aimbot::Visible(const Source::Vector3& vEnd, CBaseEntity* pEntity) const
{
	CBaseEntity* pLocalEntity = p_Entity->GetClientEntity(p_Client->GetLocalPlayer());
	Ray_t pRay;
	trace_t	pTrace;

	CTraceFilter pFilter((CBaseEntity*)pLocalEntity);

	pRay.Init(pLocalEntity->GetEyePosition(), vEnd);

	ptrace->TraceRay(pRay, 0x4600400B, &pFilter, &pTrace);

	if (pEntity)
		return (pTrace.m_pEnt == (CBaseEntity*)pEntity || pTrace.fraction >= 1.0f);

	return (pTrace.fraction >= 1.0f);
}
