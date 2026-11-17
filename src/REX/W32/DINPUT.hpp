#pragma once

#include "REX/StaticString.hpp"
#include "REX/W32/COM.hpp"
#include "REX/W32/CORE.hpp"
#include "REX/W32/D3D.hpp"

namespace REX::W32
{
	struct IDirectInput8A;
	struct IDirectInputDevice8A;
	struct IDirectInputEffect;
}

namespace REX::W32
{
	enum DIK : std::int32_t
	{
		DIK_NONE = 0,
		DIK_ESCAPE = 1,
		DIK_1 = 2,
		DIK_2 = 3,
		DIK_3 = 4,
		DIK_4 = 5,
		DIK_5 = 6,
		DIK_6 = 7,
		DIK_7 = 8,
		DIK_8 = 9,
		DIK_9 = 10,
		DIK_0 = 11,
		DIK_MINUS = 12,
		DIK_EQUALS = 13,
		DIK_BACK = 14,
		DIK_TAB = 15,
		DIK_Q = 16,
		DIK_W = 17,
		DIK_E = 18,
		DIK_R = 19,
		DIK_T = 20,
		DIK_Y = 21,
		DIK_U = 22,
		DIK_I = 23,
		DIK_O = 24,
		DIK_P = 25,
		DIK_LBRACKET = 26,
		DIK_RBRACKET = 27,
		DIK_RETURN = 28,
		DIK_LCONTROL = 29,
		DIK_A = 30,
		DIK_S = 31,
		DIK_D = 32,
		DIK_F = 33,
		DIK_G = 34,
		DIK_H = 35,
		DIK_J = 36,
		DIK_K = 37,
		DIK_L = 38,
		DIK_SEMICOLON = 39,
		DIK_APOSTROPHE = 40,
		DIK_GRAVE = 41,
		DIK_LSHIFT = 42,
		DIK_BACKSLASH = 43,
		DIK_Z = 44,
		DIK_X = 45,
		DIK_C = 46,
		DIK_V = 47,
		DIK_B = 48,
		DIK_N = 49,
		DIK_M = 50,
		DIK_COMMA = 51,
		DIK_PERIOD = 52,
		DIK_SLASH = 53,
		DIK_RSHIFT = 54,
		DIK_MULTIPLY = 55,
		DIK_LMENU = 56,
		DIK_SPACE = 57,
		DIK_CAPITAL = 58,
		DIK_F1 = 59,
		DIK_F2 = 60,
		DIK_F3 = 61,
		DIK_F4 = 62,
		DIK_F5 = 63,
		DIK_F6 = 64,
		DIK_F7 = 65,
		DIK_F8 = 66,
		DIK_F9 = 67,
		DIK_F10 = 68,
		DIK_NUMLOCK = 69,
		DIK_SCROLL = 70,
		DIK_NUMPAD7 = 71,
		DIK_NUMPAD8 = 72,
		DIK_NUMPAD9 = 73,
		DIK_SUBTRACT = 74,
		DIK_NUMPAD4 = 75,
		DIK_NUMPAD5 = 76,
		DIK_NUMPAD6 = 77,
		DIK_ADD = 78,
		DIK_NUMPAD1 = 79,
		DIK_NUMPAD2 = 80,
		DIK_NUMPAD3 = 81,
		DIK_NUMPAD0 = 82,
		DIK_DECIMAL = 83,
		DIK_OEM_102 = 86,
		DIK_F11 = 87,
		DIK_F12 = 88,
		DIK_F13 = 100,
		DIK_F14 = 101,
		DIK_F15 = 102,
		DIK_KANA = 112,
		DIK_ABNT_C1 = 115,
		DIK_CONVERT = 121,
		DIK_NOCONVERT = 123,
		DIK_YEN = 125,
		DIK_ABNT_C2 = 126,
		DIK_NUMPADEQUALS = 141,
		DIK_PREVTRACK = 144,
		DIK_AT = 145,
		DIK_COLON = 146,
		DIK_UNDERLINE = 147,
		DIK_KANJI = 148,
		DIK_STOP = 149,
		DIK_AX = 150,
		DIK_UNLABELED = 151,
		DIK_NEXTTRACK = 153,
		DIK_NUMPADENTER = 156,
		DIK_RCONTROL = 157,
		DIK_MUTE = 160,
		DIK_CALCULATOR = 161,
		DIK_PLAYPAUSE = 162,
		DIK_MEDIASTOP = 164,
		DIK_VOLUMEDOWN = 174,
		DIK_VOLUMEUP = 176,
		DIK_WEBHOME = 178,
		DIK_NUMPADCOMMA = 179,
		DIK_DIVIDE = 181,
		DIK_SYSRQ = 183,
		DIK_RMENU = 184,
		DIK_PAUSE = 197,
		DIK_HOME = 199,
		DIK_UP = 200,
		DIK_PRIOR = 201,
		DIK_LEFT = 203,
		DIK_RIGHT = 205,
		DIK_END = 207,
		DIK_DOWN = 208,
		DIK_NEXT = 209,
		DIK_INSERT = 210,
		DIK_DELETE = 211,
		DIK_LWIN = 219,
		DIK_RWIN = 220,
		DIK_APPS = 221,
		DIK_POWER = 222,
		DIK_SLEEP = 223,
		DIK_WAKE = 227,
		DIK_WEBSEARCH = 229,
		DIK_WEBFAVORITES = 230,
		DIK_WEBREFRESH = 231,
		DIK_WEBSTOP = 232,
		DIK_WEBFORWARD = 233,
		DIK_WEBBACK = 234,
		DIK_MYCOMPUTER = 235,
		DIK_MAIL = 236,
		DIK_MEDIASELECT = 237,
		DIK_BACKSPACE = DIK_BACK,
		DIK_NUMPADSTAR = DIK_MULTIPLY,
		DIK_LALT = DIK_LMENU,
		DIK_CAPSLOCK = DIK_CAPITAL,
		DIK_NUMPADMINUS = DIK_SUBTRACT,
		DIK_NUMPADPLUS = DIK_ADD,
		DIK_NUMPADPERIOD = DIK_DECIMAL,
		DIK_NUMPADSLASH = DIK_DIVIDE,
		DIK_RALT = DIK_RMENU,
		DIK_UPARROW = DIK_UP,
		DIK_PGUP = DIK_PRIOR,
		DIK_LEFTARROW = DIK_LEFT,
		DIK_RIGHTARROW = DIK_RIGHT,
		DIK_DOWNARROW = DIK_DOWN,
		DIK_PGDN = DIK_NEXT
	};
}

namespace REX::W32
{
	struct DIENVELOPE;
	struct DIOBJECTDATAFORMAT;

	struct DIACTIONA
	{
		std::uintptr_t appData;
		std::uint32_t semantic;
		std::uint32_t flags;

		union
		{
			const char* actionName;
			std::uint32_t resIdString;
		};

		GUID guidInstance;
		std::uint32_t objID;
		std::uint32_t how;
	};

	struct DIACTIONFORMATA
	{
		std::uint32_t size;
		std::uint32_t actionSize;
		std::uint32_t dataSize;
		std::uint32_t numActions;
		DIACTIONA* action;
		GUID guidActionMap;
		std::uint32_t genre;
		std::uint32_t bufferSize;
		std::int32_t axisMin;
		std::int32_t axisMax;
		HINSTANCE instString;
		FILETIME timeStamp;
		std::uint32_t crc;
		REX::StaticString<MAX_PATH> actionMap;
	};

	struct DICOLORSET
	{
		std::uint32_t size;
		D3DCOLOR textFore;
		D3DCOLOR textHighlight;
		D3DCOLOR calloutLine;
		D3DCOLOR calloutHighlight;
		D3DCOLOR border;
		D3DCOLOR controlFill;
		D3DCOLOR highlightFill;
		D3DCOLOR areaFill;
	};

	struct DICONFIGUREDEVICESPARAMSA
	{
		std::uint32_t size;
		std::uint32_t users;
		char* userNames;
		std::uint32_t formatsSize;
		DIACTIONFORMATA* formats;
		HWND hwnd;
		DICOLORSET dics;
		IUnknown* unkDDSTarget;
	};

	struct DIDATAFORMAT
	{
		std::uint32_t size;
		std::uint32_t objSize;
		std::uint32_t flags;
		std::uint32_t dataSize;
		std::uint32_t numObjs;
		DIOBJECTDATAFORMAT* odf;
	};

	struct DIDEVCAPS
	{
		std::uint32_t size;
		std::uint32_t flags;
		std::uint32_t devType;
		std::uint32_t axes;
		std::uint32_t buttons;
		std::uint32_t povs;
		std::uint32_t ffSamplePeriod;
		std::uint32_t ffMinTimeResolution;
		std::uint32_t firmwareRevision;
		std::uint32_t hardwareRevision;
		std::uint32_t ffDriverVersion;
	};

	struct DIDEVICEIMAGEINFOA
	{
		REX::StaticString<MAX_PATH> imagePath;
		std::uint32_t flags;
		std::uint32_t viewID;
		RECT overlay;
		std::uint32_t objID;
		std::uint32_t validPts;
		std::array<POINT, 5> calloutLine;
		RECT calloutRect;
		std::uint32_t textAlign;
	};

	struct DIDEVICEIMAGEINFOHEADERA
	{
		std::uint32_t size;
		std::uint32_t sizeImageInfo;
		std::uint32_t views;
		std::uint32_t buttons;
		std::uint32_t axes;
		std::uint32_t povs;
		std::uint32_t bufferSize;
		std::uint32_t bufferUsed;
		DIDEVICEIMAGEINFOA* imageInfoArray;
	};

	struct DIDEVICEINSTANCEA
	{
		std::uint32_t size;
		GUID guidInstance;
		GUID guidProduct;
		std::uint32_t devType;
		REX::StaticString<MAX_PATH> instanceName;
		REX::StaticString<MAX_PATH> productName;
		GUID guidFFDriver;
		std::uint16_t usagePage;
		std::uint16_t usage;
	};

	struct DIDEVICEOBJECTDATA
	{
		std::uint32_t ofs;
		std::uint32_t data;
		std::uint32_t timeStamp;
		std::uint32_t sequence;
		std::uintptr_t appData;
	};

	struct DIDEVICEOBJECTINSTANCEA
	{
		std::uint32_t size;
		GUID guidType;
		std::uint32_t ofs;
		std::uint32_t type;
		std::uint32_t flags;
		REX::StaticString<MAX_PATH> name;
		std::uint32_t ffMaxForce;
		std::uint32_t ffForceResolution;
		std::uint16_t collectionNumber;
		std::uint16_t designatorIndex;
		std::uint16_t usagePage;
		std::uint16_t usage;
		std::uint32_t dimension;
		std::uint16_t exponent;
		std::uint16_t reportId;
	};

	struct DIEFFECT
	{
		std::uint32_t size;
		std::uint32_t flags;
		std::uint32_t duration;
		std::uint32_t samplePeriod;
		std::uint32_t gain;
		std::uint32_t triggerButton;
		std::uint32_t triggerRepeatInterval;
		std::uint32_t axesSize;
		std::uint32_t* axes;
		std::int32_t* direction;
		DIENVELOPE* envelope;
		std::uint32_t typeSpecificParamsSize;
		void* typeSpecificParams;
		std::uint32_t startDelay;
	};

	struct DIENVELOPE
	{
		std::uint32_t size;
		std::uint32_t attackLevel;
		std::uint32_t attackTime;
		std::uint32_t fadeLevel;
		std::uint32_t fadeTime;
	};

	struct DIEFFECTINFOA
	{
		std::uint32_t size;
		GUID guid;
		std::uint32_t effectType;
		std::uint32_t staticParams;
		std::uint32_t dynamicParams;
		REX::StaticString<MAX_PATH> name;
	};

	struct DIEFFESCAPE
	{
		std::uint32_t size;
		std::uint32_t command;
		void* inBuffer;
		std::uint32_t inBufferSize;
		void* outBuffer;
		std::uint32_t outBufferSize;
	};

	struct DIFILEEFFECT
	{
		std::uint32_t size;
		GUID guidEffect;
		const DIEFFECT* effect;
		REX::StaticString<MAX_PATH> friendlyName;
	};

	struct DIMOUSESTATE2
	{
		std::int32_t x;
		std::int32_t y;
		std::int32_t z;
		std::array<std::uint8_t, 8> rgbButtons;
	};

	struct DIOBJECTDATAFORMAT
	{
		const GUID* guid;
		std::uint32_t ofs;
		std::uint32_t type;
		std::uint32_t flags;
	};

	struct DIPROPHEADER
	{
		std::uint32_t size;
		std::uint32_t headerSize;
		std::uint32_t obj;
		std::uint32_t how;
	};
}

namespace REX::W32
{
	using LPDICONFIGUREDEVICESCALLBACK = BOOL(__stdcall*)(IUnknown*, void*);
	using LPDIENUMCREATEDEFFECTOBJECTSCALLBACK = BOOL(__stdcall*)(IDirectInputEffect*, void*);
	using LPDIENUMDEVICESBYSEMANTICSCBA =
		BOOL(__stdcall*)(const DIDEVICEINSTANCEA*, IDirectInputDevice8A*, std::uint32_t, std::uint32_t, void*);
	using LPDIENUMDEVICESCALLBACKA = BOOL(__stdcall*)(const DIDEVICEINSTANCEA*, void*);
	using LPDIENUMDEVICEOBJECTSCALLBACKA = BOOL(__stdcall*)(const DIDEVICEOBJECTINSTANCEA*, void*);
	using LPDIENUMEFFECTSCALLBACKA = BOOL(__stdcall*)(const DIEFFECTINFOA*, void*);
	using LPDIENUMEFFECTSINFILECALLBACK = BOOL(__stdcall*)(const DIFILEEFFECT*, void*);
}

namespace REX::W32
{
#if (__clang__ == 1)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnon-virtual-dtor"
#endif

#if (_MSC_VER > 0l)
#pragma warning(push)
#pragma warning(disable : 4'265)
#endif

	// NOLINTBEGIN(cppcoreguidelines-virtual-class-destructor)

	struct __declspec(novtable, uuid("BF798030-483A-4DA2-AA99-5D64ED369700")) IDirectInput8A : public IUnknown
	{
		virtual auto CreateDevice(const GUID&, IDirectInputDevice8A**, IUnknown*) noexcept -> HRESULT = 0;
		virtual auto EnumDevices(std::uint32_t, LPDIENUMDEVICESCALLBACKA, void*, std::uint32_t) noexcept -> HRESULT = 0;
		virtual auto GetDeviceStatus(const GUID&) noexcept -> HRESULT = 0;
		virtual auto RunControlPanel(HWND, std::uint32_t) noexcept -> HRESULT = 0;
		virtual auto Initialize(HINSTANCE, std::uint32_t) noexcept -> HRESULT = 0;
		virtual auto FindDevice(const GUID&, const char*, GUID*) noexcept -> HRESULT = 0;
		virtual auto EnumDevicesBySemantics(
			const char*,
			DIACTIONFORMATA*,
			LPDIENUMDEVICESBYSEMANTICSCBA,
			void*,
			std::uint32_t) noexcept -> HRESULT = 0;
		virtual auto ConfigureDevices(LPDICONFIGUREDEVICESCALLBACK, DICONFIGUREDEVICESPARAMSA*, std::uint32_t, void*)
			noexcept -> HRESULT = 0;
	};

	struct __declspec(novtable, uuid("54D41080-DC15-4833-A41B-748F73A38179")) IDirectInputDevice8A : public IUnknown
	{
		virtual auto GetCapabilities(DIDEVCAPS*) noexcept -> HRESULT = 0;
		virtual auto EnumObjects(LPDIENUMDEVICEOBJECTSCALLBACKA, void*, std::uint32_t) noexcept -> HRESULT = 0;
		virtual auto GetProperty(const GUID&, DIPROPHEADER*) noexcept -> HRESULT = 0;
		virtual auto SetProperty(const GUID&, const DIPROPHEADER*) noexcept -> HRESULT = 0;
		virtual auto Acquire() noexcept -> HRESULT = 0;
		virtual auto Unacquire() noexcept -> HRESULT = 0;
		virtual auto GetDeviceState(std::uint32_t, void*) noexcept -> HRESULT = 0;
		virtual auto GetDeviceData(std::uint32_t, DIDEVICEOBJECTDATA*, std::uint32_t*, std::uint32_t) noexcept
			-> HRESULT = 0;
		virtual auto SetDataFormat(const DIDATAFORMAT*) noexcept -> HRESULT = 0;
		virtual auto SetEventNotification(HANDLE) noexcept -> HRESULT = 0;
		virtual auto SetCooperativeLevel(HWND, std::uint32_t) noexcept -> HRESULT = 0;
		virtual auto GetObjectInfo(DIDEVICEOBJECTINSTANCEA*, std::uint32_t, std::uint32_t) noexcept -> HRESULT = 0;
		virtual auto GetDeviceInfo(DIDEVICEINSTANCEA*) noexcept -> HRESULT = 0;
		virtual auto RunControlPanel(HWND, std::uint32_t) noexcept -> HRESULT = 0;
		virtual auto Initialize(HINSTANCE, std::uint32_t, const GUID&) noexcept -> HRESULT = 0;
		virtual auto CreateEffect(const GUID&, const DIEFFECT*, IDirectInputEffect*, IUnknown*) noexcept -> HRESULT = 0;
		virtual auto EnumEffects(LPDIENUMEFFECTSCALLBACKA, void*, std::uint32_t) noexcept -> HRESULT = 0;
		virtual auto GetEffectInfo(DIEFFECTINFOA*, const GUID&) noexcept -> HRESULT = 0;
		virtual auto GetForceFeedbackState(std::uint32_t*) noexcept -> HRESULT = 0;
		virtual auto SendForceFeedbackCommand(std::uint32_t) noexcept -> HRESULT = 0;
		virtual auto EnumCreatedEffectObjects(LPDIENUMCREATEDEFFECTOBJECTSCALLBACK, void*, std::uint32_t) noexcept
			-> HRESULT = 0;
		virtual auto Escape(DIEFFESCAPE*) noexcept -> HRESULT = 0;
		virtual auto Poll() noexcept -> HRESULT = 0;
		virtual auto SendDeviceData(std::uint32_t, const DIDEVICEOBJECTDATA*, std::uint32_t*, std::uint32_t) noexcept
			-> HRESULT = 0;
		virtual auto EnumEffectsInFile(const char*, LPDIENUMEFFECTSINFILECALLBACK, void*, std::uint32_t) noexcept
			-> HRESULT = 0;
		virtual auto WriteEffectToFile(const char*, std::uint32_t, DIFILEEFFECT*, std::uint32_t) noexcept
			-> HRESULT = 0;
		virtual auto BuildActionMap(DIACTIONFORMATA*, const char*, std::uint32_t) noexcept -> HRESULT = 0;
		virtual auto SetActionMap(DIACTIONFORMATA*, const char*, std::uint32_t) noexcept -> HRESULT = 0;
		virtual auto GetImageInfo(DIDEVICEIMAGEINFOHEADERA*) noexcept -> HRESULT = 0;
	};

	struct __declspec(novtable, uuid("E7E1F7C0-88D2-11D0-9AD0-00A0C9A06E35")) IDirectInputEffect : public IUnknown
	{
		virtual auto Initialize(HINSTANCE, std::uint32_t, const GUID&) noexcept -> HRESULT = 0;
		virtual auto GetEffectGuid(GUID*) noexcept -> HRESULT = 0;
		virtual auto GetParameters(DIEFFECT*, std::uint32_t) noexcept -> HRESULT = 0;
		virtual auto SetParameters(const DIEFFECT*, std::uint32_t) noexcept -> HRESULT = 0;
		virtual auto Start(std::uint32_t, std::uint32_t) noexcept -> HRESULT = 0;
		virtual auto Stop() noexcept -> HRESULT = 0;
		virtual auto GetEffectStatus(std::uint32_t*) noexcept -> HRESULT = 0;
		virtual auto Download() noexcept -> HRESULT = 0;
		virtual auto Unload() noexcept -> HRESULT = 0;
		virtual auto Escape(DIEFFESCAPE*) noexcept -> HRESULT = 0;
	};

	// NOLINTEND(cppcoreguidelines-virtual-class-destructor)

#if (_MSC_VER > 0l)
#pragma warning(pop)
#endif

#if (__clang__ == 1)
#pragma clang diagnostic pop
#endif
}

namespace REX::W32
{
	inline constexpr auto IID_IDirectInput8A =
		IID{0xBF79'8030, 0x483A, 0x4DA2, {0xAA, 0x99, 0x5D, 0x64, 0xED, 0x36, 0x97, 0x00}};
	inline constexpr auto IID_IDirectInputDevice8A =
		IID{0x54D4'1080, 0xDC15, 0x4833, {0xA4, 0x1B, 0x74, 0x8F, 0x73, 0xA3, 0x81, 0x79}};
	inline constexpr auto IID_IDirectInputEffect =
		IID{0xE7E1'F7C0, 0x88D2, 0x11D0, {0x9A, 0xD0, 0x00, 0xA0, 0xC9, 0xA0, 0x6E, 0x35}};
}
