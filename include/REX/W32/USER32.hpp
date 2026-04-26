#pragma once

#include "REX/W32/CORE.hpp"

namespace REX::W32
{
	enum GWLP : std::int32_t
	{
		GWLP_USERDATA = -21,
		GWLP_ID = -12,
		GWLP_HWNDPARENT = -8,
		GWLP_HINSTANCE = -6,
		GWLP_WNDPROC = -4
	};

	enum INPUT_TYPE : std::int32_t
	{
		INPUT_MOUSE = 0,
		INPUT_KEYBOARD = 1,
		INPUT_HARDWARE = 2
	};

	enum KEYEVENTF : std::uint32_t
	{
		KEYEVENTF_EXTENDEDKEY = 0x1,
		KEYEVENTF_KEYUP = 0x2,
		KEYEVENTF_UNICODE = 0x4,
		KEYEVENTF_SCANCODE = 0x8
	};

	enum MBID : std::int32_t
	{
		IDOK = 1,
		IDCANCEL = 2,
		IDABORT = 3,
		IDRETRY = 4,
		IDIGNORE = 5,
		IDYES = 6,
		IDNO = 7,
		IDTRYAGAIN = 10,
		IDCONTINUE = 11
	};

	enum MB : std::uint32_t
	{
		MB_OK = 0x0,
		MB_DEFBUTTON1 = 0x0,
		MB_APPLMODAL = 0x0,
		MB_OKCANCEL = 0x1,
		MB_ABORTRETRYIGNORE = 0x2,
		MB_YESNOCANCEL = 0x3,
		MB_YESNO = 0x4,
		MB_RETRYCANCEL = 0x5,
		MB_CANCELTRYCONTINUE = 0x6,
		MB_ICONHAND = 0x10,
		MB_ICONERROR = 0x10,
		MB_ICONSTOP = 0x10,
		MB_ICONQUESTION = 0x20,
		MB_ICONEXCLAMATION = 0x30,
		MB_ICONWARNING = 0x30,
		MB_ICONINFORMATION = 0x40,
		MB_ICONASTERISK = 0x40,
		MB_DEFBUTTON2 = 0x100,
		MB_DEFBUTTON3 = 0x200,
		MB_DEFBUTTON4 = 0x300,
		MB_SYSTEMMODAL = 0x1000,
		MB_TASKMODAL = 0x2000,
		MB_HELP = 0x4000,
		MB_SETFOREGROUND = 0x10000,
		MB_DEFAULT_DESKTOP_ONLY = 0x20000,
		MB_TOPMOST = 0x40000,
		MB_RIGHT = 0x80000,
		MB_RTLREADING = 0x100000
	};

	enum RI : std::int32_t
	{
		RI_MOUSE_LEFT_BUTTON_DOWN = 0x0001,
		RI_MOUSE_LEFT_BUTTON_UP = 0x0002,
		RI_MOUSE_RIGHT_BUTTON_DOWN = 0x0004,
		RI_MOUSE_RIGHT_BUTTON_UP = 0x0008,
		RI_MOUSE_MIDDLE_BUTTON_DOWN = 0x0010,
		RI_MOUSE_MIDDLE_BUTTON_UP = 0x0020,
		RI_MOUSE_BUTTON_4_DOWN = 0x0040,
		RI_MOUSE_BUTTON_4_UP = 0x0080,
		RI_MOUSE_BUTTON_5_DOWN = 0x0100,
		RI_MOUSE_BUTTON_5_UP = 0x0200,
		RI_MOUSE_WHEEL = 0x0400,
		RI_MOUSE_HWHEEL = 0x0800
	};

	enum VK : std::int32_t
	{
		VK_NONE = 0,
		VK_LBUTTON = 1,
		VK_RBUTTON = 2,
		VK_CANCEL = 3,
		VK_MBUTTON = 4,
		VK_XBUTTON1 = 5,
		VK_XBUTTON2 = 6,
		VK_BACK = 8,
		VK_TAB = 9,
		VK_RESERVED_0A = 10,
		VK_RESERVED_0B = 11,
		VK_CLEAR = 12,
		VK_RETURN = 13,
		VK_SHIFT = 16,
		VK_CONTROL = 17,
		VK_MENU = 18,
		VK_PAUSE = 19,
		VK_CAPITAL = 20,
		VK_KANA = 21,
		VK_HANGUEL = 21,
		VK_HANGUL = 21,
		VK_IME_ON = 22,
		VK_JUNJA = 23,
		VK_FINAL = 24,
		VK_HANJA = 25,
		VK_KANJI = 25,
		VK_IME_OFF = 26,
		VK_ESCAPE = 27,
		VK_CONVERT = 28,
		VK_NONCONVERT = 29,
		VK_ACCEPT = 30,
		VK_MODECHANGE = 31,
		VK_SPACE = 32,
		VK_PRIOR = 33,
		VK_NEXT = 34,
		VK_END = 35,
		VK_HOME = 36,
		VK_LEFT = 37,
		VK_UP = 38,
		VK_RIGHT = 39,
		VK_DOWN = 40,
		VK_SELECT = 41,
		VK_PRINT = 42,
		VK_EXECUTE = 43,
		VK_SNAPSHOT = 44,
		VK_INSERT = 45,
		VK_DELETE = 46,
		VK_HELP = 47,
		VK_0 = 48,
		VK_1 = 49,
		VK_2 = 50,
		VK_3 = 51,
		VK_4 = 52,
		VK_5 = 53,
		VK_6 = 54,
		VK_7 = 55,
		VK_8 = 56,
		VK_9 = 57,
		VK_A = 65,
		VK_B = 66,
		VK_C = 67,
		VK_D = 68,
		VK_E = 69,
		VK_F = 70,
		VK_G = 71,
		VK_H = 72,
		VK_I = 73,
		VK_J = 74,
		VK_K = 75,
		VK_L = 76,
		VK_M = 77,
		VK_N = 78,
		VK_O = 79,
		VK_P = 80,
		VK_Q = 81,
		VK_R = 82,
		VK_S = 83,
		VK_T = 84,
		VK_U = 85,
		VK_V = 86,
		VK_W = 87,
		VK_X = 88,
		VK_Y = 89,
		VK_Z = 90,
		VK_LWIN = 91,
		VK_RWIN = 92,
		VK_APPS = 93,
		VK_RESERVED_5E = 94,
		VK_SLEEP = 95,
		VK_NUMPAD0 = 96,
		VK_NUMPAD1 = 97,
		VK_NUMPAD2 = 98,
		VK_NUMPAD3 = 99,
		VK_NUMPAD4 = 100,
		VK_NUMPAD5 = 101,
		VK_NUMPAD6 = 102,
		VK_NUMPAD7 = 103,
		VK_NUMPAD8 = 104,
		VK_NUMPAD9 = 105,
		VK_MULTIPLY = 106,
		VK_ADD = 107,
		VK_SEPARATOR = 108,
		VK_SUBTRACT = 109,
		VK_DECIMAL = 110,
		VK_DIVIDE = 111,
		VK_F1 = 112,
		VK_F2 = 113,
		VK_F3 = 114,
		VK_F4 = 115,
		VK_F5 = 116,
		VK_F6 = 117,
		VK_F7 = 118,
		VK_F8 = 119,
		VK_F9 = 120,
		VK_F10 = 121,
		VK_F11 = 122,
		VK_F12 = 123,
		VK_F13 = 124,
		VK_F14 = 125,
		VK_F15 = 126,
		VK_F16 = 127,
		VK_F17 = 128,
		VK_F18 = 129,
		VK_F19 = 130,
		VK_F20 = 131,
		VK_F21 = 132,
		VK_F22 = 133,
		VK_F23 = 134,
		VK_F24 = 135,
		VK_NUMLOCK = 144,
		VK_SCROLL = 145,
		VK_OEMSPECIFIC_92 = 146,
		VK_OEMSPECIFIC_93 = 147,
		VK_OEMSPECIFIC_94 = 148,
		VK_OEMSPECIFIC_95 = 149,
		VK_OEMSPECIFIC_96 = 150,
		VK_LSHIFT = 160,
		VK_RSHIFT = 161,
		VK_LCONTROL = 162,
		VK_RCONTROL = 163,
		VK_LMENU = 164,
		VK_RMENU = 165,
		VK_BROWSER_BACK = 166,
		VK_BROWSER_FORWARD = 167,
		VK_BROWSER_REFRESH = 168,
		VK_BROWSER_STOP = 169,
		VK_BROWSER_SEARCH = 170,
		VK_BROWSER_FAVORITES = 171,
		VK_BROWSER_HOME = 172,
		VK_VOLUME_MUTE = 173,
		VK_VOLUME_DOWN = 174,
		VK_VOLUME_UP = 175,
		VK_MEDIA_NEXT_TRACK = 176,
		VK_MEDIA_PREV_TRACK = 177,
		VK_MEDIA_STOP = 178,
		VK_MEDIA_PLAY_PAUSE = 179,
		VK_LAUNCH_MAIL = 180,
		VK_LAUNCH_MEDIA_SELECT = 181,
		VK_LAUNCH_APP1 = 182,
		VK_LAUNCH_APP2 = 183,
		VK_RESERVED_B8 = 184,
		VK_RESERVED_B9 = 185,
		VK_OEM_1 = 186,
		VK_OEM_PLUS = 187,
		VK_OEM_COMMA = 188,
		VK_OEM_MINUS = 189,
		VK_OEM_PERIOD = 190,
		VK_OEM_2 = 191,
		VK_OEM_3 = 192,
		VK_RESERVED_C1 = 193,
		VK_RESERVED_C2 = 194,
		VK_RESERVED_C3 = 195,
		VK_RESERVED_C4 = 196,
		VK_RESERVED_C5 = 197,
		VK_RESERVED_C6 = 198,
		VK_RESERVED_C7 = 199,
		VK_RESERVED_C8 = 200,
		VK_RESERVED_C9 = 201,
		VK_RESERVED_CA = 202,
		VK_RESERVED_CB = 203,
		VK_RESERVED_CC = 204,
		VK_RESERVED_CD = 205,
		VK_RESERVED_CE = 206,
		VK_RESERVED_CF = 207,
		VK_RESERVED_D0 = 208,
		VK_RESERVED_D1 = 209,
		VK_RESERVED_D2 = 210,
		VK_RESERVED_D3 = 211,
		VK_RESERVED_D4 = 212,
		VK_RESERVED_D5 = 213,
		VK_RESERVED_D6 = 214,
		VK_RESERVED_D7 = 215,
		VK_OEM_4 = 219,
		VK_OEM_5 = 220,
		VK_OEM_6 = 221,
		VK_OEM_7 = 222,
		VK_OEM_8 = 223,
		VK_RESERVED_E0 = 224,
		VK_OEMSPECIFIC_E1 = 225,
		VK_OEM_102 = 226,
		VK_OEMSPECIFIC_E3 = 227,
		VK_OEMSPECIFIC_E4 = 228,
		VK_PROCESSKEY = 229,
		VK_OEMSPECIFIC_E6 = 230,
		VK_PACKET = 231,
		VK_OEMSPECIFIC_E9 = 233,
		VK_OEMSPECIFIC_EA = 234,
		VK_OEMSPECIFIC_EB = 235,
		VK_OEMSPECIFIC_EC = 236,
		VK_OEMSPECIFIC_ED = 237,
		VK_OEMSPECIFIC_EE = 238,
		VK_OEMSPECIFIC_EF = 239,
		VK_OEMSPECIFIC_F0 = 240,
		VK_OEMSPECIFIC_F1 = 241,
		VK_OEMSPECIFIC_F2 = 242,
		VK_OEMSPECIFIC_F3 = 243,
		VK_OEMSPECIFIC_F4 = 244,
		VK_OEMSPECIFIC_F5 = 245,
		VK_ATTN = 246,
		VK_CRSEL = 247,
		VK_EXSEL = 248,
		VK_EREOF = 249,
		VK_PLAY = 250,
		VK_ZOOM = 251,
		VK_NONAME = 252,
		VK_PA1 = 253,
		VK_OEM_CLEAR = 254,
		VK_RESERVED_FF = 255,

		VK_TOTAL = 256
	};

	enum WM : std::uint32_t
	{
		WM_NULL = 0,
		WM_CREATE = 1,
		WM_DESTROY = 2,
		WM_MOVE = 3,
		WM_SIZE = 5,
		WM_ACTIVATE = 6,
		WM_SETFOCUS = 7,
		WM_KILLFOCUS = 8,
		WM_ENABLE = 10,
		WM_SETREDRAW = 11,
		WM_SETTEXT = 12,
		WM_GETTEXT = 13,
		WM_GETTEXTLENGTH = 14,
		WM_PAINT = 15,
		WM_CLOSE = 16,
		WM_QUIT = 18,
		WM_ERASEBKGND = 20,
		WM_SHOWWINDOW = 24,
		WM_ACTIVATEAPP = 28,
		WM_FONTCHANGE = 29,
		WM_TIMECHANGE = 30,
		WM_CANCELMODE = 31,
		WM_SETCURSOR = 32,
		WM_MOUSEACTIVATE = 33,
		WM_CHILDACTIVATE = 34
	};
}

namespace REX::W32
{
	using WNDPROC = std::intptr_t (*)(HWND, std::uint32_t, std::uintptr_t, std::intptr_t);

	struct INPUT
	{
		std::uint32_t type; // 00
		union
		{
			struct
			{
				std::uint32_t posX;		  // 08
				std::uint32_t posY;		  // 0C
				std::uint32_t mouseData;  // 10
				std::uint32_t flags;	  // 14
				std::uint32_t time;		  // 18
				std::uintptr_t extraInfo; // 20
			} mouseInput;
			struct
			{
				std::uint16_t virtualKey; // 08
				std::uint16_t scanCode;	  // 0A
				std::uint32_t flags;	  // 0C
				std::uint32_t time;		  // 10
				std::uintptr_t extraInfo; // 18
			} keyboardInput;
			struct
			{
				std::uint32_t message;	  // 08
				std::uint16_t paramL;	  // 0C
				std::uint16_t paramH;	  // 0E
				std::uint32_t time;		  // 10
				std::uintptr_t extraInfo; // 18
			} hardwareInput;
		}; // 08
	};

	struct OVERLAPPED
	{
		// members
		std::uintptr_t internal;	 // 00
		std::uintptr_t internalHigh; // 08
		union
		{
			struct
			{
				std::uint32_t offset;	  // 10
				std::uint32_t offsetHigh; // 14
			};
			void* ptr; // 10
		}; // 10
		REX::W32::HANDLE hEvent; // 18
	};

	struct RAWINPUTHEADER
	{
		// members
		std::uint32_t type;	   // 00
		std::uint32_t size;	   // 04
		std::uintptr_t device; // 08
		std::uintptr_t param;  // 10
	};

	struct RAWMOUSE
	{
		// members
		std::uint16_t flags; // 00
		union
		{
			std::uint64_t buttons; // 08
			struct
			{
				std::uint16_t buttonFlags; // 08
				std::uint16_t buttonData;  // 0A
			};
		}; // 08
		std::int32_t rawButtons; // 10
		std::int32_t lastX;		 // 14
		std::int32_t lastY;		 // 18
		std::uint32_t extraInfo; // 1C
	};

	struct RAWKEYBOARD
	{
		// members
		std::uint16_t makeCode;	 // 00
		std::uint16_t flags;	 // 02
		std::uint16_t reserved;	 // 04
		std::uint16_t vKey;		 // 06
		std::uint32_t message;	 // 08
		std::uint32_t extraInfo; // 0C
	};

	struct RAWHID
	{
		// members
		std::uint32_t sizeHid;				 // 00
		std::uint32_t count;				 // 04
		std::array<std::uint8_t, 1> rawData; // 08
	};

	struct RAWINPUT
	{
		// members
		RAWINPUTHEADER header; // 00
		union
		{
			RAWMOUSE mouse;		  // 18
			RAWKEYBOARD keyboard; // 18
			RAWHID hid;			  // 18
		} data;					  // 18
	};
}

namespace REX::W32
{
	std::int16_t GetAsyncKeyState(std::int32_t a_key) noexcept;
	bool GetClientRect(HWND a_wnd, RECT* a_rect) noexcept;
	std::int32_t GetKeyNameTextA(std::int32_t a_param, char* a_buffer, std::int32_t a_bufLen) noexcept;
	std::int32_t GetKeyNameTextW(std::int32_t a_param, wchar_t* a_buffer, std::int32_t a_bufLen) noexcept;
	std::int16_t GetKeyState(std::int32_t a_key) noexcept;
	bool GetWindowRect(HWND a_wnd, RECT* a_rect) noexcept;
	std::int32_t MessageBoxA(HWND a_wnd, const char* a_text, const char* a_caption, std::uint32_t a_type) noexcept;
	std::int32_t MessageBoxW(HWND a_wnd, const wchar_t* a_text, const wchar_t* a_caption, std::uint32_t a_type) noexcept;
	std::uint32_t SendInput(std::uint32_t a_inputCount, INPUT* a_inputs, std::int32_t a_inputSize) noexcept;
	std::intptr_t SetWindowLongPtrA(HWND a_wnd, std::int32_t a_index, std::intptr_t a_newPtr) noexcept;
	std::int32_t ShowCursor(bool a_show) noexcept;
}
