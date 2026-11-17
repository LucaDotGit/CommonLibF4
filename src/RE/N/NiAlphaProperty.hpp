#pragma once

#include "RE/N/NiProperty.hpp"

namespace RE
{
	class __declspec(novtable) NiAlphaProperty : public NiProperty // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::NiAlphaProperty;
		inline static constexpr const auto& VTABLE = VTABLE::NiAlphaProperty;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::NiAlphaProperty;

		enum class Flags : std::uint16_t
		{
		};

		enum class AlphaFunction : std::int32_t
		{
			One = 0,
			Zero = 1,
			SrcColor = 2,
			InvSrcColor = 3,
			DestColor = 4,
			InvDestColor = 5,
			SrcAlpha = 6,
			InvSrcAlpha = 7,
			DestAlpha = 8,
			InvDestAlpha = 9,
			SrcAlphaTest = 10
		};

		enum class TestFunction : std::int32_t
		{
			Always = 0,
			Less = 1,
			Equal = 2,
			LessEqual = 3,
			Greater = 4,
			NotEqual = 5,
			GreaterEqual = 6,
			Never = 7
		};

		NiAlphaProperty();

		~NiAlphaProperty() override; // 0x00

		// add
		auto Type() -> std::int32_t override; // 0x01 - { return 0; }

		GAME_HEAP_REDEFINE_NEW(NiAlphaProperty);

		void SetDestBlendMode(AlphaFunction a_func);
		void SetSrcBlendMode(AlphaFunction a_func);
		void SetTestMode(TestFunction a_func);
		void SetAlphaBlending(bool a_value);
		void SetAlphaTesting(bool a_value);

		// members
		REX::EnumSet<Flags, std::uint16_t> flags{0xEC}; // 0x28
		std::int8_t alphaTestRef{0};					// 0x2A
	};

	static_assert(sizeof(NiAlphaProperty) == 0x30);
}
