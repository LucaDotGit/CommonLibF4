#pragma once

#include "RE/I/INISettingCollection.hpp"

namespace RE
{
	class __declspec(novtable) INIPrefSettingCollection
		: public INISettingCollection // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::INIPrefSettingCollection };
		inline static constexpr auto VTABLE{ VTABLE::INIPrefSettingCollection };

		~INIPrefSettingCollection() override; // 00

		[[nodiscard]] static INIPrefSettingCollection* GetSingleton()
		{
			static const auto SINGLETON = REL::Relocation<INIPrefSettingCollection**>{ ID::INIPrefSettingCollection::Singleton };
			return *SINGLETON;
		}
	};
	static_assert(sizeof(INIPrefSettingCollection) == 0x128);
}
