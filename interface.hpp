#pragma once
#include <string>
#include "Math.hpp"
#include "checksum_crc.h"
#include <Windows.h>
#include <string_view>
#include "CVMTHooking.hpp"

template< typename Function > Function call_vfunc(PVOID Base, const size_t Index)
{
	const auto VTablePointer = static_cast<PDWORD*>(Base);
	const auto VTableFunctionBase = *VTablePointer;
	auto dw_address = VTableFunctionBase[Index];
	return reinterpret_cast<Function>(dw_address);
}



struct dll_helper
{
	using t_create_interface = void* (*)(const char* name, int* returnCode);

	explicit dll_helper(std::string_view dll_name) : dll_name_(dll_name)
	{
		module_ = GetModuleHandleA(dll_name_.c_str());
		interface_ = reinterpret_cast<t_create_interface>(GetProcAddress(module_, "CreateInterface"));
	}

	void* get_vmt(std::string_view interface_name)
	{
		vmt_ = interface_(interface_name.data(), nullptr);
		return vmt_;
	}

private:
	std::string dll_name_;
	t_create_interface interface_ = nullptr;
	void* vmt_ = nullptr;
	HMODULE module_ = nullptr;
};


class IClientNetworkable;
class IClientThinkable;
class IVEngineClient
{
public:
	void GetScreenSize(int& width, int& height)
	{
		typedef void(__thiscall* GetScreenSizeFn)(void*, int&, int&);
		return call_vfunc<GetScreenSizeFn>(this, 5)(this, width, height);
	}

	void ServerCmd(const char* szCmdString, bool bReliable = true)
	{
		typedef void(__thiscall* ServerCmdFn)(void*, const char*, bool);
		call_vfunc<ServerCmdFn>(this, 6)(this, szCmdString, bReliable);
	}

	void ClientCmd(const char* szCmdString)
	{
		typedef void(__thiscall* ClientCmdFn)(void*, const char*);
		call_vfunc<ClientCmdFn>(this, 7)(this, szCmdString);
	}

	bool GetPlayerInfo(int ent_num, void* pinfo)
	{
		typedef bool(__thiscall* GetPlayerInfoFn)(void*, int, void*);
		return call_vfunc<GetPlayerInfoFn>(this, 8)(this, ent_num, pinfo);
	}

	int GetPlayerForUserID(int userID)
	{
		typedef int(__thiscall* GetPlayerForUserIDFn)(void*, int);
		return call_vfunc<GetPlayerForUserIDFn>(this, 9)(this, userID);
	}

	void* TextMessageGet(const char* pName)
	{
		typedef void* (__thiscall* TextMessageGetFn)(void*, const char*);
		return call_vfunc<TextMessageGetFn>(this, 10)(this, pName);
	}

	bool Con_IsVisible()
	{
		typedef bool(__thiscall* Con_IsVisibleFn)(void*);
		return call_vfunc<Con_IsVisibleFn>(this, 11)(this);
	}

	int GetLocalPlayer()
	{
		typedef int(__thiscall* GetLocalPlayerFn)(void*);
		return call_vfunc<GetLocalPlayerFn>(this, 12)(this);
	}

	float GetLastTimeStamp()
	{
		typedef float(__thiscall* GetLastTimeStampFn)(void*);
		return call_vfunc<GetLastTimeStampFn>(this, 14)(this);
	}

	void* GetSentence(void* pAudioSource)
	{
		typedef void* (__thiscall* GetSentenceFn)(void*, void*);
		return call_vfunc<GetSentenceFn>(this, 15)(this, pAudioSource);
	}

	float GetSentenceLength(void* pAudioSource)
	{
		typedef float(__thiscall* GetSentenceLengthFn)(void*, void*);
		return call_vfunc<GetSentenceLengthFn>(this, 16)(this, pAudioSource);
	}

	bool IsStreaming(void* pAudioSource)
	{
		typedef bool(__thiscall* IsStreamingFn)(void*, void*);
		return call_vfunc<IsStreamingFn>(this, 17)(this, pAudioSource);
	}

	void GetViewAngles(Source::Vector3& va)
	{
		typedef void(__thiscall* GetViewAngles)(void*, const Source::Vector3&);
		call_vfunc<GetViewAngles>(this, 18)(this, va);
	}

	void SetViewAngles(const Source::Vector3& va)
	{
		typedef void(__thiscall* SetViewAnglesFn)(void*, const Source::Vector3&);
		call_vfunc<SetViewAnglesFn>(this, 19)(this, va);
	}
	int GetMaxClients()
	{
		typedef int(__thiscall* GetMaxClientsFn)(void*);
		return call_vfunc<GetMaxClientsFn>(this, 20)(this);
	}

	const char* Key_LookupBinding(const char* pBinding)
	{
		typedef const char* (__thiscall* Key_LookupBindingFn)(void*, const char*);
		return call_vfunc<Key_LookupBindingFn>(this, 21)(this, pBinding);
	}

	const char* Key_BindingForKey(unsigned int code)
	{
		typedef const char* (__thiscall* Key_BindingForKeyFn)(void*, unsigned int);
		return call_vfunc<Key_BindingForKeyFn>(this, 22)(this, code);
	}

	int Key_SetBinding(unsigned int code, const char* pBinding)
	{
		typedef int(__thiscall* Key_SetBindingFn)(void*, int, const char*);
		return call_vfunc<Key_SetBindingFn>(this, 23)(this, code, pBinding);
	}

	bool IsInGame()
	{
		typedef bool(__thiscall* IsInGameFn)(void*);
		return call_vfunc<IsInGameFn>(this, 26)(this);
	}

	bool IsConnected()
	{
		typedef bool(__thiscall* IsConnectedFn)(void*);
		return call_vfunc<IsConnectedFn>(this, 27)(this);
	}

	bool IsDrawingLoadingImage()
	{
		typedef bool(__thiscall* IsDrawingLoadingImageFn)(void*);
		return call_vfunc<IsDrawingLoadingImageFn>(this, 28)(this);
	}

	void Con_NPrintf(int pos, const char* fmt, ...)
	{
		typedef void(__thiscall* Con_NPrintfFn)(void*, int, const char*);
		call_vfunc<Con_NPrintfFn>(this, 30)(this, pos, fmt);
	}

	const char* GetGameDirectory()
	{
		typedef const char* (__thiscall* GetGameDirectoryFn)(void*);
		return call_vfunc<GetGameDirectoryFn>(this, 36)(this);
	}

	const char* GetLevelName()
	{
		typedef const char* (__thiscall* GetLevelNameFn)(void*);
		return call_vfunc<GetLevelNameFn>(this, 52)(this);
	}

	bool IsPaused()
	{
		typedef bool(__thiscall* IsPausedFn)(void*);
		return call_vfunc<IsPausedFn>(this, 90);
	}

	bool IsTakingScreenshot()
	{
		typedef bool(__thiscall* IsTakingScreenshotFn)(void*);
		return call_vfunc<IsTakingScreenshotFn>(this, 92)(this);
	}

	bool IsHLTV()
	{
		typedef bool(__thiscall* IsHLTVFn)(void*);
		return call_vfunc<IsHLTVFn>(this, 93)(this);
	}
};
struct RecvProp;
class CBaseEntity;
struct RecvTable
{
	RecvProp* m_pProps;
	int m_nProps;
	void* m_pDecoder;
	char* m_pNetTableName;
	bool m_bInitialized;
	bool m_bInMainList;
};

struct RecvProp
{
	char* m_pVarName;
	int m_RecvType;
	int m_Flags;
	int m_StringBufferSize;
	bool m_bInsideArray;
	const void* m_pExtraData;
	RecvProp* m_pArrayProp;
	void* m_ArrayLengthProxy;
	void* m_ProxyFn;
	void* m_DataTableProxyFn;
	RecvTable* m_pDataTable;
	int m_Offset;
	int m_ElementStride;
	int m_nElements;
	const char* m_pParentArrayPropName;
};

typedef IClientNetworkable* (*CreateClientClassFn)(int entnum, int serialNum);
typedef IClientNetworkable* (*CreateEventFn)();
class ClientClass
{
public:
	CreateClientClassFn		m_pCreateFn;
	CreateEventFn m_pCreateEventFn;
	char* m_pNetworkName;
	RecvTable* m_pRecvTable;
	ClientClass* m_pNext;
	int				m_ClassID;
};
typedef void* (*CreateInterfaceFn)(const char* pName, int* pReturnCode);
typedef void* (*InstantiateInterfaceFn)();
class CGlobalVarsBase;
class IBaseClientDLL
{
public:

	virtual int              Connect(CreateInterfaceFn appSystemFactory, CGlobalVarsBase* pGlobals) = 0;
	virtual int              Disconnect(void) = 0;
	virtual int              Init(CreateInterfaceFn appSystemFactory, CGlobalVarsBase* pGlobals) = 0;
	virtual void             PostInit() = 0;
	virtual void             Shutdown(void) = 0;
	virtual void             LevelInitPreEntity(char const* pMapName) = 0;
	virtual void             LevelInitPostEntity() = 0;
	virtual void             LevelShutdown(void) = 0;
	virtual ClientClass* GetAllClasses(void) = 0;
};

class IClientEntityList
{
public:
	CBaseEntity* GetClientEntity(int index)
	{
		typedef CBaseEntity* (__thiscall* GetClientEntityFn)(void*, int);
		return call_vfunc<GetClientEntityFn>(this, 3)(this, index);
	}

	CBaseEntity* GetClientEntityFromHandle(int handle)
	{
		typedef CBaseEntity* (__thiscall* GetClientEntityFromHandleFn)(void*, int);
		return call_vfunc<GetClientEntityFromHandleFn>(this, 4)(this, handle);
	}

	int GetHighestEntityIndex()
	{
		typedef int(__thiscall* GetHighestEntityIndexFn)(void*);
		return call_vfunc<GetHighestEntityIndexFn>(this, 6)(this);
	}
};
enum DataUpdateType_t
{
	DATA_UPDATE_CREATED = 0,
	DATA_UPDATE_DATATABLE_CHANGED,
};

class IClientUnknown;
class IClientNetworkable
{
public:
	virtual IClientUnknown* GetIClientUnknown() = 0;
	virtual void			Release() = 0;
	virtual ClientClass* GetClientClass() = 0;// FOR NETVARS FIND YOURSELF ClientClass* stuffs
	virtual void			NotifyShouldTransmit( /* ShouldTransmitState_t state*/) = 0;
	virtual void			OnPreDataChanged(DataUpdateType_t updateType) = 0;
	virtual void			OnDataChanged(DataUpdateType_t updateType) = 0;
	virtual void			PreDataUpdate(DataUpdateType_t updateType) = 0;
	virtual void			PostDataUpdate(DataUpdateType_t updateType) = 0;
	virtual void			unknown();
	virtual bool			IsDormant(void) = 0;
	virtual int				GetIndex(void) const = 0;
	virtual void			ReceiveMessage(int classID /*, bf_read &msg*/) = 0;
	virtual void* GetDataTableBasePtr() = 0;
	virtual void			SetDestroyedOnRecreateEntities(void) = 0;
};
class IClientRenderable
{
public:
	//virtual void*					GetIClientUnknown() = 0;
	virtual Source::Vector3 const& GetRenderOrigin(void) = 0;
	virtual Source::Vector3 const& GetRenderAngles(void) = 0;
	virtual bool					ShouldDraw(void) = 0;
	virtual bool					IsTransparent(void) = 0;
	virtual bool					UsesPowerOfTwoFrameBufferTexture() = 0;
	virtual bool					UsesFullFrameBufferTexture() = 0;
	virtual void					GetShadowHandle() const = 0;
	virtual void* RenderHandle() = 0;
	virtual const void* GetModel() const = 0;
	virtual int						DrawModel(int flags) = 0;
	virtual int						GetBody() = 0;
	virtual void					ComputeFxBlend() = 0;

	bool SetupBones(void* pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime)
	{
		typedef bool(__thiscall* oSetupBones)(PVOID, void*, int, int, float);
		return call_vfunc< oSetupBones>(this, 13)(this, pBoneToWorldOut, nMaxBones, boneMask, currentTime);
	}
};

class ICollideable
{
public:
	virtual void pad0();
	virtual const Source::Vector3& OBBMins() const;
	virtual const Source::Vector3& OBBMaxs() const;
};

class IClientUnknown
{
public:
	ICollideable* GetCollideable()
	{
		return (ICollideable*)((DWORD)this + 0x318);
	}
	virtual IClientNetworkable* GetClientNetworkable() = 0;
	virtual IClientRenderable* GetClientRenderable() = 0;
	virtual CBaseEntity* GetIClientEntity() = 0;
	virtual CBaseEntity* GetBaseEntity() = 0;
	virtual IClientThinkable* GetClientThinkable() = 0;
};

class IClientThinkable
{
public:
	virtual IClientUnknown* GetIClientUnknown() = 0;
	virtual void				ClientThink() = 0;
	virtual void* GetThinkHandle() = 0;
	virtual void				SetThinkHandle(void* hThink) = 0;
	virtual void				Release() = 0;
};

#define IN_ATTACK  (1 << 0)
#define IN_JUMP   (1 << 1)
#define IN_DUCK   (1 << 2)
#define IN_FORWARD  (1 << 3)
#define IN_BACK   (1 << 4)
#define IN_USE   (1 << 5)
#define IN_CANCEL  (1 << 6)
#define IN_LEFT   (1 << 7)
#define IN_RIGHT  (1 << 8)
#define IN_MOVELEFT  (1 << 9)
#define IN_MOVERIGHT (1 << 10)
#define IN_ATTACK2  (1 << 11)
#define IN_RUN   (1 << 12)
#define IN_RELOAD  (1 << 13)
#define IN_ALT1   (1 << 14)
#define IN_ALT2   (1 << 15)
#define IN_SCORE  (1 << 16)   // Used by client.dll for when scoreboard is held down
#define IN_SPEED  (1 << 17) // Player is holding the speed key
#define IN_WALK   (1 << 18) // Player holding walk key
#define IN_ZOOM   (1 << 19) // Zoom key for HUD zoom
#define IN_WEAPON1  (1 << 20) // weapon defines these bits
#define IN_WEAPON2  (1 << 21) // weapon defines these bits
#define IN_BULLRUSH  (1 << 22)
#define IN_GRENADE1  (1 << 23) // grenade 1
#define IN_GRENADE2  (1 << 24) // grenade 2
#define IN_LOOKSPIN  (1 << 25)
#define MULTIPLAYER_BACKUP 150
class CGlobalVarsBase
{
public:
	float	realtime;
	int		framecount;
	float	absoluteframetime;
	float	absoluteframestarttimestddev;
	float	curtime;
	float	frametime;
	int		maxClients;
	int		tickcount;
	float	interval_per_tick;
	float	interpolation_amount;
	int		simTicksThisFrame;
	int		network_protocol;
	void* pSaveData;
	bool	m_bClient;
	int		nTimestampNetworkingBase;
	int		nTimestampRandomizeWindow;
};
class CUserCmd
{
public:
	CUserCmd()
	{
		memset(this, 0, sizeof(*this));
	};
	virtual ~CUserCmd() {};

	CRC32_t GetChecksum(void) const
	{
		CRC32_t crc;
		CRC32_Init(&crc);

		CRC32_ProcessBuffer(&crc, &command_number, sizeof(command_number));
		CRC32_ProcessBuffer(&crc, &tick_count, sizeof(tick_count));
		CRC32_ProcessBuffer(&crc, &viewangles, sizeof(viewangles));
		CRC32_ProcessBuffer(&crc, &aimdirection, sizeof(aimdirection));
		CRC32_ProcessBuffer(&crc, &forwardmove, sizeof(forwardmove));
		CRC32_ProcessBuffer(&crc, &sidemove, sizeof(sidemove));
		CRC32_ProcessBuffer(&crc, &upmove, sizeof(upmove));
		CRC32_ProcessBuffer(&crc, &buttons, sizeof(buttons));
		CRC32_ProcessBuffer(&crc, &impulse, sizeof(impulse));
		CRC32_ProcessBuffer(&crc, &weaponselect, sizeof(weaponselect));
		CRC32_ProcessBuffer(&crc, &weaponsubtype, sizeof(weaponsubtype));
		CRC32_ProcessBuffer(&crc, &random_seed, sizeof(random_seed));
		CRC32_ProcessBuffer(&crc, &mousedx, sizeof(mousedx));
		CRC32_ProcessBuffer(&crc, &mousedy, sizeof(mousedy));

		CRC32_Final(&crc);
		return crc;
	}

	int     command_number;     // 0x04 For matching server and client commands for debugging
	int     tick_count;         // 0x08 the tick the client created this command
	Source::Vector3  viewangles;         // 0x0C Player instantaneous view angles.
	Source::Vector3  aimdirection;       // 0x18
	float   forwardmove;        // 0x24
	float   sidemove;           // 0x28
	float   upmove;             // 0x2C
	int     buttons;            // 0x30 Attack button states
	char    impulse;            // 0x34
	int     weaponselect;       // 0x38 Current weapon id
	int     weaponsubtype;      // 0x3C
	int     random_seed;        // 0x40 For shared random functions
	short   mousedx;            // 0x44 mouse accum in x from create move
	short   mousedy;            // 0x46 mouse accum in y from create move
	bool    hasbeenpredicted;   // 0x48 Client only, tracks whether we've predicted this command at least once
	char    pad_0x4C[0x18];     // 0x4C Current sizeof( usercmd ) =  100  = 0x64
};

class CVerifiedUserCmd
{
public:
	CUserCmd m_cmd;
	CRC32_t  m_crc;
};

class CInput
{
public:
	char                pad_0x00[0x0C];
	bool                m_trackir_available;
	bool                m_mouse_initiated;
	bool                m_mouse_active;
	bool                m_fJoystickAdvancedInit;
	char                pad_0x08[0x2C];
	void* m_pKeys;
	char                pad_0x38[0x6C];
	bool                m_fCameraInterceptingMouse;
	bool                m_fCameraInThirdPerson;
	bool                m_fCameraMovingWithMouse;
	Source::Vector3		    m_vecCameraOffset;
	bool                m_fCameraDistanceMove;
	int                 m_nCameraOldX;
	int                 m_nCameraOldY;
	int                 m_nCameraX;
	int                 m_nCameraY;
	bool                m_CameraIsOrthographic;
	Source::Vector3             m_angPreviousViewAngles;
	Source::Vector3              m_angPreviousViewAnglesTilt;
	float               m_flLastForwardMove;
	int                 m_nClearInputState;
	char                pad_0xE4[0x8];
	CUserCmd* m_pCommands;
	CVerifiedUserCmd* m_pVerifiedCommands;

	inline CUserCmd* GetUserCmd(int sequence_number);
	inline CUserCmd* GetUserCmd(int nSlot, int sequence_number);
	inline CVerifiedUserCmd* GetVerifiedCmd(int sequence_number);
};

CUserCmd* CInput::GetUserCmd(int sequence_number)
{
	using OriginalFn = CUserCmd * (__thiscall*)(void*, int, int);
	return call_vfunc<OriginalFn>(this, 8)(this, 0, sequence_number);
}

CUserCmd* CInput::GetUserCmd(int nSlot, int sequence_number)
{
	typedef CUserCmd* (__thiscall* GetUserCmd_t)(void*, int, int);
	return call_vfunc<GetUserCmd_t>(this, 8)(this, nSlot, sequence_number);
}

CVerifiedUserCmd* CInput::GetVerifiedCmd(int sequence_number)
{
	auto verifiedCommands = *(CVerifiedUserCmd**)(reinterpret_cast<uint32_t>(this) + 0xF8);
	return &verifiedCommands[sequence_number % MULTIPLAYER_BACKUP];
}

enum TraceType_t
{
	TRACE_EVERYTHING = 0,
	TRACE_WORLD_ONLY,
	TRACE_ENTITIES_ONLY,
	TRACE_EVERYTHING_FILTER_PROPS
};

struct cplane_t
{
	Source::Vector3	normal;
	float	dist;
	BYTE	type;
	BYTE	signbits;
	BYTE	pad[2];
};

struct csurface_t
{
	const char* name;
	short			surfaceProps;
	unsigned short	flags;
};

class player_info_t
{
public:
	BYTE	                pad[8];
	int						xuidlow;
	int						xuidhigh;
	char                    name[128];
	int                     userID;
	char                    guid[32 + 1];
	unsigned int            friendsID;
	char                    friendsName[128];
	bool                    fakeplayer;
	bool                    ishltv;
	unsigned long           customFiles[4];
	unsigned char           filesDownloaded;
};

class CBaseTrace
{
public:
	Source::Vector3			startpos;
	Source::Vector3			endpos;
	cplane_t		plane;
	float			fraction;
	int				contents;
	unsigned short	dispFlags;
	bool			allsolid;
	bool			startsolid;
};

class CGameTrace : public CBaseTrace
{
public:
	float			fractionleftsolid;
	csurface_t		surface;
	int				hitgroup;
	short			physicsbone;
	unsigned short	worldsurfaceidx;
	CBaseEntity* m_pEnt;
	int				hitbox;

	bool DidHit() const
	{
		return fraction < 1 || allsolid || startsolid;
	}
};

typedef CGameTrace trace_t;

struct Ray_t
{
	Source::Vector4				m_Start;
	Source::Vector4				m_Delta;
	Source::Vector4				m_StartOffset;
	Source::Vector4				m_Extents;

	const Source::matrix3x4_t* m_WorldAxisTransform;

	bool				m_IsRay;
	bool				m_IsSwept;

	Ray_t(void)
		: m_WorldAxisTransform(0)
	{
	}

	void Init(const Source::Vector3& start, const Source::Vector3& end)
	{
		m_Delta = end - start;

		m_IsSwept = (m_Delta.LengthSqr() != 0);

		m_Extents.Init();

		m_WorldAxisTransform = 0;

		m_IsRay = true;

		m_StartOffset.Init();

		m_Start = start;
	}
};

class ITraceFilter
{
public:
	virtual bool ShouldHitEntity(PVOID pEntity, int contentsMask) = 0;
	virtual TraceType_t	GetTraceType() const = 0;
};
class CTraceFilter : public ITraceFilter
{
public:
	CTraceFilter(PVOID pEntToSkip = NULL)
	{
		pSkip = pEntToSkip;
	}
	bool ShouldHitEntity(PVOID pEntityHandle, int contentsMask)
	{
		return !(pEntityHandle == pSkip);
	}
	virtual TraceType_t GetTraceType() const
	{
		return TRACE_EVERYTHING;
	}
	void* pSkip;
};
class IEngineTrace
{
public:
	int GetPointContents(const Source::Vector3& vecAbsPosition, UINT nMask, CBaseEntity** ppEntity = NULL)
	{
		typedef int(__thiscall* GetPointContentsFn)(void*, const Source::Vector3&, UINT, CBaseEntity**);
		return call_vfunc<GetPointContentsFn>(this, 0)(this, vecAbsPosition, nMask, ppEntity);
	}

	void TraceRay(const Ray_t& ray, unsigned int fMask, ITraceFilter* pTraceFilter, trace_t* pTrace)
	{
		typedef void(__thiscall* TraceRayFn)(void*, const Ray_t&, unsigned int, ITraceFilter*, trace_t*);
		call_vfunc<TraceRayFn>(this, 5)(this, ray, fMask, pTraceFilter, pTrace);
	}
};
struct FireBulletData
{
	FireBulletData(const Source::Vector3& eye_pos) : src(eye_pos)
	{
	}

	Source::Vector3		  src;
	trace_t       enter_trace;
	Source::Vector3		  direction;
	CTraceFilter  filter;
	float				  trace_length;
	float				  trace_length_remaining;
	float				  current_damage;
	int					  penetrate_count;
};

extern dll_helper* engine;

extern dll_helper* client;

extern IVEngineClient* p_Client;
extern IClientEntityList* p_Entity;
extern IBaseClientDLL* p_ClientBase;
extern IEngineTrace* ptrace;
extern CVMTHookManager* hook;
extern CInput* input;
extern CGlobalVarsBase* pServer;
