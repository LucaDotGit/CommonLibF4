#pragma once

#include "RE/B/BSResource_ErrorCode.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	enum class ENUM_LOD_MULT : std::int32_t;

	class NiNode;

	class BSModelDB
	{
	public:
		using Handle = void*;

		class DBTraits
		{
		public:
			class ArgsType
			{
			public:
				// members
				REX::Enum<ENUM_LOD_MULT, std::int32_t> lodFadeMult; // 0x00
				std::uint32_t loadLevel;							// 0x04
				std::uint8_t prepareAfterLoad : 1;					// 0x08:00
				std::uint8_t faceGenModel	  : 1;					// 0x08:01
				std::uint8_t useErrorMarker	  : 1;					// 0x08:02
				std::uint8_t performProcess	  : 1;					// 0x08:03
				std::uint8_t createFadeNode	  : 1;					// 0x08:04
				std::uint8_t loadTextures	  : 1;					// 0x08:05
			};

			static_assert(sizeof(ArgsType) == 0x0C);
		};

		static_assert(std::is_empty_v<DBTraits>);

		class HandelListHead
		{
		public:
			class HandleList
			{
			public:
				// members
				Handle handle;	  // 0x00
				HandleList* next; // 0x08
			};

			static_assert(sizeof(HandleList) == 0x10);

			// members
			HandleList* head; // 0x00
		};

		static_assert(sizeof(HandelListHead) == 0x08);

		static auto Demand(const char* a_name, Handle& a_result, const DBTraits::ArgsType& a_args)
			-> BSResource::ErrorCode
		{
			using FuncType = BSResource::ErrorCode (*)(const char*, Handle&, const DBTraits::ArgsType&);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BSModelDB::Demand01);
			return std::invoke(FUNC, a_name, a_result, a_args);
		}

		static auto Demand(const char* a_name, NiPointer<NiNode>* a_result, const DBTraits::ArgsType& a_args)
			-> BSResource::ErrorCode
		{
			using FuncType = BSResource::ErrorCode (*)(const char*, NiPointer<NiNode>*, const DBTraits::ArgsType&);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BSModelDB::Demand02);
			return std::invoke(FUNC, a_name, a_result, a_args);
		}
	};
}
