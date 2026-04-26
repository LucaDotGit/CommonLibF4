#pragma once

#include "RE/F/FormType.hpp"
#include "RE/M/MemoryManager.hpp"

namespace RE
{
	class BSInputEnableLayer
	{
	public:
		inline static constexpr auto FORM_TYPE{ FormType::kInputEnableLayer };

		constexpr BSInputEnableLayer() noexcept = default;
		constexpr ~BSInputEnableLayer() noexcept = default;

		constexpr BSInputEnableLayer(std::uint32_t a_layerID) noexcept
			: layerID(a_layerID)
		{
		}

		BSInputEnableLayer(const BSInputEnableLayer&) = delete;
		BSInputEnableLayer(BSInputEnableLayer&&) = delete;

		BSInputEnableLayer& operator=(const BSInputEnableLayer&) = delete;
		BSInputEnableLayer& operator=(BSInputEnableLayer&&) = delete;

		GAME_HEAP_REDEFINE_NEW(BSInputEnableLayer);

		[[nodiscard]] std::uint32_t GetLayerID() const noexcept { return layerID; }

		[[nodiscard]] FormType GetFormType() const noexcept;

		[[nodiscard]] constexpr std::uint32_t QLayerID() const noexcept { return layerID; }
		[[nodiscard]] constexpr std::uint32_t QRefCount() const noexcept { return refCount; }

		std::uint32_t IncRef() noexcept;
		std::uint32_t DecRef() noexcept;

		// members
		std::uint32_t layerID{ 0 };			  // 00
		volatile std::uint32_t refCount{ 0 }; // 04
	};
	static_assert(sizeof(BSInputEnableLayer) == 0x08);
}
