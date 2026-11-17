#pragma once

#include "RE/B/BSTDataBuffer.hpp"

namespace RE::BGSMod::Attachment
{
	class Instance;
}

namespace RE::BGSMod::Property
{
	class Mod;
}

namespace RE::BGSMod
{
	class Container : public BSTDataBuffer<2> // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSMod__Container;

		class Data
		{
		public:
			// members
			Attachment::Instance* attachments; // 0x00
			Property::Mod* propertyMods;	   // 0x08
			std::uint32_t attachmentCount;	   // 0x10
			std::uint32_t propertyModCount;	   // 0x14
		};

		static_assert(sizeof(Data) == 0x18);

		[[nodiscard]]
		auto GetData(Data* a_data) const -> Data*
		{
			using FuncType = decltype(&Container::GetData);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BGSMod::Container::GetData);
			return std::invoke(FUNC, this, a_data);
		}
	};

	static_assert(sizeof(Container) == 0x10);
}
