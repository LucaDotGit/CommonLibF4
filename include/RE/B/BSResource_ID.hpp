#pragma once

#include "RE/B/BSResource_FileID.hpp"

namespace RE::BSResource
{
	class ID
		: public FileID // 00
	{
	public:
		explicit ID() = default;

		explicit ID(const char* a_path)
		{
			GenerateFromPath(a_path);
		}

		~ID() noexcept = default;

		ID(const ID&) = default;
		ID(ID&&) noexcept = default;

		ID& operator=(const ID&) = default;
		ID& operator=(ID&&) noexcept = default;

		void GenerateFromPath(const char* a_path)
		{
			using FuncType = decltype(&ID::GenerateFromPath);
			static const auto FUNC = REL::Relocation<FuncType>{ RE::ID::BSResource::ID::GenerateFromPath };
			std::invoke(FUNC, this, a_path);
		}

		// members
		std::uint32_t directory{ 0 }; // 08
	};
	static_assert(sizeof(ID) == 0x0C);
}
