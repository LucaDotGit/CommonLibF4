#pragma once

#include "RE/F/FormType.hpp"
#include "RE/M/MemoryManager.hpp"

namespace RE
{
	class BSInputEnableLayer
	{
	public:
		inline static constexpr auto FORM_TYPE = FormType::InputEnableLayer;

		constexpr BSInputEnableLayer() noexcept = default;
		constexpr ~BSInputEnableLayer() noexcept = default;

		constexpr explicit BSInputEnableLayer(std::uint32_t a_layerID) noexcept :
			layerID(a_layerID)
		{
		}

		BSInputEnableLayer(const BSInputEnableLayer&) = delete;
		BSInputEnableLayer(BSInputEnableLayer&&) = delete;

		auto operator=(const BSInputEnableLayer&) -> BSInputEnableLayer& = delete;
		auto operator=(BSInputEnableLayer&&) -> BSInputEnableLayer& = delete;

		GAME_HEAP_REDEFINE_NEW(BSInputEnableLayer);

		[[nodiscard]]
		auto GetLayerID() const noexcept -> std::uint32_t
		{
			return layerID;
		}

		[[nodiscard]]
		auto GetFormType() const noexcept -> FormType;

		[[nodiscard]]
		constexpr auto QLayerID() const noexcept -> std::uint32_t
		{
			return layerID;
		}

		[[nodiscard]]
		constexpr auto QRefCount() const noexcept -> std::uint32_t
		{
			return refCount;
		}

		auto IncRef() const noexcept -> std::uint32_t;
		auto DecRef() const noexcept -> std::uint32_t;

		// members
		std::uint32_t layerID{0};					// 0x00
		mutable volatile std::uint32_t refCount{0}; // 0x04
	};

	static_assert(sizeof(BSInputEnableLayer) == 0x08);
}
