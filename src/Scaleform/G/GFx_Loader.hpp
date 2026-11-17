#pragma once

#include "Scaleform/G/GFx_StateBag.hpp"

namespace Scaleform::GFx
{
	class LoaderImpl;
	class MovieDef;
	class ResourceLib;

	class __declspec(novtable) Loader : public StateBag // 0x00
	{
	public:
		enum class LoadConstants : std::uint32_t
		{
			All = 0,
			WaitCompletion = 1 << 0,
			WaitFrame1 = 1 << 1,
			Ordered = 1 << 4,
			OnThread = 1 << 6,
			KeepBindData = 1 << 7,
			ImageFiles = 1 << 16,
			DisableSWF = 1 << 19,
			DisableImports = 1 << 20,
			QuietOpen = 1 << 21,

			DebugHeap = 1 << 28
		};

		// add
		virtual auto CheckTagLoader(std::int32_t a_tagType) const -> bool; // 0x04

		[[nodiscard]]
		auto CreateMovie(
			const char* a_filename,
			LoadConstants a_loadConstants = LoadConstants::All,
			std::size_t a_memoryArena = 0) -> MovieDef*
		{
			using FuncType = decltype(&Loader::CreateMovie);
			static const auto FUNC = REL::Relocation<FuncType>(ID::GFx::Loader::CreateMovie);
			return std::invoke(FUNC, this, a_filename, a_loadConstants, a_memoryArena);
		}

		// members
		LoaderImpl* impl;										 // 0x08
		ResourceLib* strongResourceLib;							 // 0x10
		REX::EnumSet<LoadConstants, std::uint32_t> defLoadFlags; // 0x18
	};

	static_assert(sizeof(Loader) == 0x20);
}
