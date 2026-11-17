#pragma once

#include "RE/B/BSResource_FileID.hpp"

namespace RE::BSResource
{
	class ID : public FileID // 0x00
	{
	public:
		constexpr ID() noexcept = default;
		constexpr ~ID() noexcept = default;

		explicit ID(const char* a_path)
		{
			GenerateFromPath(a_path);
		}

		constexpr ID(const ID&) noexcept = default;
		constexpr ID(ID&&) noexcept = default;

		constexpr auto operator=(const ID&) noexcept -> ID& = default;
		constexpr auto operator=(ID&&) noexcept -> ID& = default;

		void GenerateFromPath(const char* a_path)
		{
			using FuncType = decltype(&ID::GenerateFromPath);
			static const auto FUNC = REL::Relocation<FuncType>(RE::ID::BSResource::ID::GenerateFromPath);
			std::invoke(FUNC, this, a_path);
		}

		// members
		std::uint32_t directory{0}; // 0x08
	};

	static_assert(sizeof(ID) == 0x0C);
}
