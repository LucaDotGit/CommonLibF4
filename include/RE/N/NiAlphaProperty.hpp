#pragma once

#include "RE/N/NiProperty.hpp"

namespace RE
{
	class __declspec(novtable) NiAlphaProperty
		: public NiProperty // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::NiAlphaProperty };
		inline static constexpr auto VTABLE{ VTABLE::NiAlphaProperty };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::NiAlphaProperty };

		enum class Flags : std::uint16_t
		{
		};

		enum class AlphaFunction : std::int32_t
		{
			kOne = 0,
			kZero = 1,
			kSrcColor = 2,
			kInvSrcColor = 3,
			kDestColor = 4,
			kInvDestColor = 5,
			kSrcAlpha = 6,
			kInvSrcAlpha = 7,
			kDestAlpha = 8,
			kInvDestAlpha = 9,
			kSrcAlphaTest = 10
		};

		enum class TestFunction : std::int32_t
		{
			kAlways = 0,
			kLess = 1,
			kEqual = 2,
			kLessEqual = 3,
			kGreater = 4,
			kNotEqual = 5,
			kGreaterEqual = 6,
			kNever = 7
		};

		NiAlphaProperty();

		~NiAlphaProperty() override; // 00

		// add
		std::int32_t Type() override; // 01 - { return 0; }

		GAME_HEAP_REDEFINE_NEW(NiAlphaProperty);

		void SetDestBlendMode(AlphaFunction a_func);
		void SetSrcBlendMode(AlphaFunction a_func);
		void SetTestMode(TestFunction a_func);
		void SetAlphaBlending(bool a_value);
		void SetAlphaTesting(bool a_value);

		// members
		REX::EnumSet<Flags, std::uint16_t> flags{ 0xEC }; // 28
		std::int8_t alphaTestRef{ 0 };					  // 2A
	};
	static_assert(sizeof(NiAlphaProperty) == 0x30);
}
