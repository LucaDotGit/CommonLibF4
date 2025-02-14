#pragma once

#include "RE/NetImmerse/NiExtraData.hpp"

namespace RE
{
	class NiIntegersExtraData : public NiExtraData
	{
	public:
		inline static constexpr auto RTTI{ RTTI::NiIntegersExtraData };
		inline static constexpr auto Ni_RTTI{ Ni_RTTI::NiIntegersExtraData };
		inline static constexpr auto VTABLE{ VTABLE::NiIntegersExtraData };

		std::uint32_t size;	 // 18
		std::uint32_t pad1C; // 1C
		std::int32_t* data;	 // 20
	};
}
