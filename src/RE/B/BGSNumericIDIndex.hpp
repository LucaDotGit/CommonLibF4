#pragma once

namespace RE
{
	class BGSNumericIDIndex
	{
	public:
		enum class Flags : std::uint8_t
		{
			Default = 1 << 6, // index 0x00
			Created = 1 << 7  // index 0xFF
		};

		[[nodiscard]]
		auto GetNumericID() const -> std::uint32_t
		{
			using FuncType = decltype(&BGSNumericIDIndex::GetNumericID);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BGSNumericIDIndex::GetNumericID);
			return std::invoke(FUNC, this);
		}

		void SetNumericID(TESFormID a_formID)
		{
			using FuncType = decltype(&BGSNumericIDIndex::SetNumericID);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BGSNumericIDIndex::SetNumericID);
			std::invoke(FUNC, this, a_formID);
		}

		// members
		union
		{
		public:
			struct
			{
			public:
				// members
				union
				{
				public:
					std::uint8_t data01;
					REX::EnumSet<Flags, std::uint8_t> flags;
				}; // 0x00

				std::uint8_t data02; // 0x01
				std::uint8_t data03; // 0x02
			};

			std::array<std::uint8_t, 3> data{0};
		}; // 0x00
	};

	static_assert(sizeof(BGSNumericIDIndex) == 0x03);
}
