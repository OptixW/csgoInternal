#pragma once

#include "Aimbot.hpp"
#include "Entity.hpp"
#include "includes.hpp"

Aimbot* g_aimbot;
dll_helper* engine = new dll_helper("engine.dll");
dll_helper* client = new dll_helper("client.dll");

IVEngineClient* p_Client = static_cast<IVEngineClient*>(engine->get_vmt("VEngineClient014"));
IClientEntityList* p_Entity = static_cast<IClientEntityList*>(client->get_vmt("VClientEntityList003"));
CInput* input = nullptr;
IBaseClientDLL* p_ClientBase = static_cast<IBaseClientDLL*>(client->get_vmt("VClient018"));
IEngineTrace* ptrace = static_cast<IEngineTrace*>(engine->get_vmt("EngineTraceClient004"));
CVMTHookManager* hook = new CVMTHookManager(static_cast<PDWORD*>(client->get_vmt("VClient018")));
CGlobalVarsBase* pServer = nullptr;

#define COLLISION_GROUP_NONE 0
#define COLLISION_GROUP_BREAKABLE_GLASS 6
#define COLLISION_GROUP_PUSHAWAY 17

#define PHYSICS_MULTIPLAYER_SOLID 1

#define FL_ONGROUND			(1 << 0)
#define FL_DUCKING			(1 << 1)

#define IN_ATTACK			(1 << 0)
#define IN_JUMP				(1 << 1)
#define IN_DUCK				(1 << 2)

using create_move_t = void(__thiscall*)(IBaseClientDLL*, int, float, bool);
static create_move_t ofunc;
void __stdcall CHLCreateMove(int sequence_number, float input_sample_frametime, bool active, bool& bSendPacket)
{
    __try
    {
        ofunc(p_ClientBase, sequence_number, input_sample_frametime, active);

        if (!p_Client || !p_Entity || !p_Client->IsInGame())
            return;

        auto* pCmd = input->GetUserCmd(sequence_number);
        if (!pCmd)
            return;

        auto* verified = input->GetVerifiedCmd(sequence_number);
        if (!verified)
            return;

        auto* pLocal = dynamic_cast<CBaseEntity*>(p_Entity->GetClientEntity(p_Client->GetLocalPlayer()));
        if (!pLocal)
            return;

        g_aimbot->AimLock(pCmd, pLocal);
        
        if (!(pLocal->GetFlags() & FL_ONGROUND))
            pCmd->buttons &= ~IN_JUMP;

        if (pCmd->buttons & IN_JUMP && !(pLocal->GetFlags() & FL_ONGROUND))
        {
            pCmd->sidemove = (pCmd->mousedx < 0) ? -400.0f : 400.0f;
        }

        if (pLocal->GetHealth() > 0 && g_aimbot->CanHit(pCmd->viewangles, pLocal) && (GetAsyncKeyState(VK_MENU) & 0x8000))
        {
            pCmd->buttons |= IN_ATTACK;
        }

        g_aimbot->RCS(pCmd, pLocal);

        verified->m_cmd = *pCmd;
        verified->m_crc = pCmd->GetChecksum();
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        // Обработка исключений
    }
}


__declspec(naked) void __stdcall hkCreateMove(int sequence_number, float input_sample_frametime, bool active)
{
	__asm
	{
		PUSH	EBP
		MOV		EBP, ESP
		PUSH	EBX
		LEA		ECX, [ESP]
		PUSH	ECX
		PUSH	active
		PUSH	input_sample_frametime
		PUSH	sequence_number
		CALL	CHLCreateMove
		POP		EBX
		POP		EBP
		RETN	0xC
	}
}

void WINAPI start_thread(HMODULE module)
{
	input = *(CInput**)(PatternScan("client.dll", "B9 ?? ?? ?? ?? F3 0F 11 04 24 FF 50 10") + 1); // A1 ? ? ? ? B9 ? ? ? ? FF 60 5C + 1
	g_aimbot = new Aimbot();
	if (!input)
	{
		MessageBox(NULL, "About", "лох", NULL);
		Sleep(10000);
		FreeLibraryAndExitThread(NULL, 0);
	}
	pServer = **(CGlobalVarsBase***)(PatternScan("client.dll", "A1 ?? ?? ?? ?? 5E 8B 40 10") + 1);//client, "A1 ? ? ? ? 5E 8B 40 10") + 1)

	auto new_method = hkCreateMove;
	ofunc = reinterpret_cast<create_move_t>(hook->dwHookMethod(reinterpret_cast<DWORD>(new_method), 22));

	while (true)
	{
		if (GetAsyncKeyState(VK_F11) & 0x8000)
		{
			hook->UnHook();
			FreeLibraryAndExitThread(module, 0);
		}
		Sleep(10);
	}
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)start_thread, hModule, NULL, NULL);
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
