#pragma once

namespace RE
{
	class BSIAudioEffectVisitorBase;

	class __declspec(novtable) BSIAudioEffectChain
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSIAudioEffectChain };
		inline static constexpr auto VTABLE{ VTABLE::BSIAudioEffectChain };

		virtual ~BSIAudioEffectChain() = default; // 00

		// add
		virtual std::uint32_t QEffectCount() const = 0;										  // 01
		virtual const char* GetDebugID() const = 0;											  // 02
		virtual void ForEachEffectImpl(const BSIAudioEffectVisitorBase& a_visitor) const = 0; // 03
	};
	static_assert(sizeof(BSIAudioEffectChain) == 0x08);
}
