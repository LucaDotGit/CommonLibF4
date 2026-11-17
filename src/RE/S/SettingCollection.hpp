#pragma once

#include "RE/M/MemoryManager.hpp"

namespace RE
{
	class Setting;

	template <class T>
	class __declspec(novtable) SettingCollection
	{
	public:
		virtual ~SettingCollection() = default; // 0x00

		// add
		virtual void Add(T* a_setting) = 0;					 // 0x01
		virtual void Remove(T* a_setting) = 0;				 // 0x02
		virtual auto WriteSetting(T& a_setting) -> bool = 0; // 0x03
		virtual auto ReadSetting(T& a_setting) -> bool = 0;	 // 0x04

		virtual auto Open([[maybe_unused]] bool a_write) -> bool // 0x05
		{
			return false;
		}

		virtual auto Close() -> bool // 0x06
		{
			return true;
		}

		virtual auto ReadSettingsFromProfile() -> bool // 0x07
		{
			return false;
		}

		virtual auto WriteSettings() -> bool // 0x08
		{
			return handle != 0;
		}

		virtual auto ReadSettings() -> bool // 0x09
		{
			return handle != 0;
		}

		GAME_HEAP_REDEFINE_NEW(SettingCollection);

		// members
		REX::StaticString<REX::W32::MAX_PATH> settingFile{REX::EMPTY_CHAR<char>}; // 0x008
		REX::W32::HANDLE handle{0};												  // 0x110
	};

	static_assert(sizeof(SettingCollection<Setting>) == 0x118);
}
