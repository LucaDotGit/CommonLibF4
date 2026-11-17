#pragma once

#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE::BSTextureArray
{
	class StaticTextureIndexed;
}

namespace RE::BSFaceGenUtils
{
	class FaceGenData : public BSIntrusiveRefCounted // 0x000
	{
	public:
		// members
		std::array<NiPointer<BSTextureArray::StaticTextureIndexed>, 4> textures; // 0x008
		std::array<std::byte, 0x30 - 0x28> hairLookupTexture{}; // 0x028 - To-Do: `BSResource::RHandleType`
		std::uint32_t layerCount{0};							// 0x030
		std::array<std::uint32_t, 128> lru{};					// 0x034
		std::uint32_t stamp{0};									// 0x234
	};

	static_assert(sizeof(FaceGenData) == 0x238);
}
