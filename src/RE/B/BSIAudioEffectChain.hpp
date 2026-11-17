#pragma once

#include "RE/M/MemoryManager.hpp"

namespace RE
{
	class BSIAudioEffectVisitorBase;

	class __declspec(novtable) BSIAudioEffectChain
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSIAudioEffectChain;
		inline static constexpr const auto& VTABLE = VTABLE::BSIAudioEffectChain;

		virtual ~BSIAudioEffectChain() = default; // 0x00

		// add
		virtual auto QEffectCount() const -> std::uint32_t = 0;								  // 0x01
		virtual auto GetDebugID() const -> const char* = 0;									  // 0x02
		virtual void ForEachEffectImpl(const BSIAudioEffectVisitorBase& a_visitor) const = 0; // 0x03

		GAME_HEAP_REDEFINE_NEW(BSIAudioEffectChain);
	};

	static_assert(sizeof(BSIAudioEffectChain) == 0x08);
}
