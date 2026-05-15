#pragma once

#include "RE/S/Setting.hpp"

namespace RE
{
	template <class T>
	class __declspec(novtable) SettingCollection
	{
	public:
		virtual ~SettingCollection() = default; // 00

		// add
		virtual void Add(T* a_setting) = 0;								   // 01
		virtual void Remove(T* a_setting) = 0;							   // 02
		virtual bool WriteSetting(T& a_setting) = 0;					   // 03
		virtual bool ReadSetting(T& a_setting) = 0;						   // 04
		virtual bool Open([[maybe_unused]] bool a_write) { return false; } // 05
		virtual bool Close() { return true; }							   // 06
		virtual bool ReadSettingsFromProfile() { return false; }		   // 07
		virtual bool WriteSettings() { return handle != 0; }			   // 08
		virtual bool ReadSettings() { return handle != 0; }				   // 09

		// members
		std::array<char, REX::W32::MAX_PATH> settingFile; // 008
		REX::W32::HANDLE handle{ 0 };					  // 110
	};

	extern template class SettingCollection<Setting>;
}
