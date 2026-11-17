#pragma once

#include "RE/S/Setting.hpp"
#include "RE/S/SettingCollectionMap.hpp"

namespace RE
{
	class __declspec(novtable) GameSettingCollection : public SettingCollectionMap<Setting> // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::GameSettingCollection;
		inline static constexpr const auto& VTABLE = VTABLE::GameSettingCollection;

		~GameSettingCollection() override; // 0x00

		// override (SettingCollection<Setting>)
		void Add(Setting* a_setting) override;					// 0x01
		void Remove(Setting* a_setting) override;				// 0x02
		auto WriteSetting(Setting& a_setting) -> bool override; // 0x03
		auto ReadSetting(Setting& a_setting) -> bool override;	// 0x04
		auto Open(bool a_write) -> bool override;				// 0x05
		auto Close() -> bool override;							// 0x06
		auto ReadSettingsFromProfile() -> bool override;		// 0x07
		auto WriteSettings() -> bool override;					// 0x08
		auto ReadSettings() -> bool override;					// 0x09

		[[nodiscard]]
		static auto GetSingleton() noexcept -> GameSettingCollection*
		{
			static const auto SINGLETON =
				REL::Relocation<GameSettingCollection**>{ID::GameSettingCollection::Singleton};
			return *SINGLETON;
		}

		static void InitCollection()
		{
			using FuncType = decltype(&GameSettingCollection::InitCollection);
			static const auto FUNC = REL::Relocation<FuncType>(ID::GameSettingCollection::InitCollection);
			std::invoke(FUNC);
		}
	};

	static_assert(sizeof(GameSettingCollection) == 0x138);
}
