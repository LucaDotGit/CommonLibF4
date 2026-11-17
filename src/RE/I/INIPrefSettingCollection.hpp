#pragma once

#include "RE/I/INISettingCollection.hpp"

namespace RE
{
	class __declspec(novtable) INIPrefSettingCollection : public INISettingCollection // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::INIPrefSettingCollection;
		inline static constexpr const auto& VTABLE = VTABLE::INIPrefSettingCollection;

		~INIPrefSettingCollection() override; // 0x00

		[[nodiscard]]
		static auto GetSingleton() noexcept -> INIPrefSettingCollection*
		{
			static const auto SINGLETON =
				REL::Relocation<INIPrefSettingCollection**>{ID::INIPrefSettingCollection::Singleton};
			return *SINGLETON;
		}
	};

	static_assert(sizeof(INIPrefSettingCollection) == 0x128);
}
