#pragma once

namespace RE
{
	class BGSNumericIDIndex
	{
	public:
		enum class Flags : std::uint8_t
		{
			kDefault = 1 << 6, // index 0x00
			kCreated = 1 << 7  // index 0xFF
		};

		[[nodiscard]] std::uint32_t GetNumericID() const
		{
			using FuncType = decltype(&BGSNumericIDIndex::GetNumericID);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSNumericIDIndex::GetNumericID };
			return std::invoke(FUNC, this);
		}

		void SetNumericID(TESFormID a_formID)
		{
			using FuncType = decltype(&BGSNumericIDIndex::SetNumericID);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSNumericIDIndex::SetNumericID };
			std::invoke(FUNC, this, a_formID);
		}

		// members
		union
		{
			struct
			{
				union
				{
					std::uint8_t data01;
					REX::EnumSet<Flags, std::uint8_t> flags;
				}; // 00
				std::uint8_t data02; // 01
				std::uint8_t data03; // 02
			};
			std::array<std::uint8_t, 3> data{ 0 };
		}; // 00
	};
	static_assert(sizeof(BGSNumericIDIndex) == 0x03);
}
