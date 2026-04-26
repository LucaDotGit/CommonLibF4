#pragma once

#include "Scaleform/G/GFx_StateBag.hpp"

namespace Scaleform::GFx
{
	class LoaderImpl;
	class MovieDef;
	class ResourceLib;

	class __declspec(novtable) Loader
		: public StateBag // 00
	{
	public:
		enum class LoadConstants : std::uint32_t
		{
			kAll = 0,
			kWaitCompletion = 1 << 0,
			kWaitFrame1 = 1 << 1,
			kOrdered = 1 << 4,
			kOnThread = 1 << 6,
			kKeepBindData = 1 << 7,
			kImageFiles = 1 << 16,
			kDisableSWF = 1 << 19,
			kDisableImports = 1 << 20,
			kQuietOpen = 1 << 21,

			kDebugHeap = 1 << 28
		};

		// add
		virtual bool CheckTagLoader(std::int32_t a_tagType) const; // 04

		[[nodiscard]] MovieDef* CreateMovie(const char* a_filename, LoadConstants a_loadConstants = LoadConstants::kAll, std::size_t a_memoryArena = 0)
		{
			using FuncType = decltype(&Loader::CreateMovie);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::GFx::Loader::CreateMovie };
			return std::invoke(FUNC, this, a_filename, a_loadConstants, a_memoryArena);
		}

		// members
		LoaderImpl* impl;										 // 08
		ResourceLib* strongResourceLib;							 // 10
		REX::EnumSet<LoadConstants, std::uint32_t> defLoadFlags; // 18
	};
	static_assert(sizeof(Loader) == 0x20);
}
