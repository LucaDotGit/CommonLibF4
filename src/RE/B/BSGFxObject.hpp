#pragma once

#include "RE/M/MemoryManager.hpp"
#include "RE/U/UsesBSGFXFunctionHandler.hpp"

namespace Scaleform::GFx
{
	class Value;
	class Movie;
}

namespace RE
{
	class BSGFxObject :
		public Scaleform::GFx::Value,	// 0x00
		public UsesBSGFXFunctionHandler // 0x20
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSGFxObject;

		explicit BSGFxObject(const Scaleform::GFx::Value& a_flashObject);
		BSGFxObject(const Scaleform::GFx::Value& a_flashObject, const char* a_relativeMemberPath);
		BSGFxObject(const Scaleform::GFx::Movie& a_parentMovie, const char* a_absoluteMemberPath);

		~BSGFxObject() = default;

		BSGFxObject(const BSGFxObject&) = delete;
		BSGFxObject(BSGFxObject&&) = delete;

		auto operator=(const BSGFxObject&) -> BSGFxObject& = delete;
		auto operator=(BSGFxObject&&) -> BSGFxObject& = delete;

		GAME_HEAP_REDEFINE_NEW(BSGFxObject);

		auto AcquireFlashObjectByMemberName(
			const Scaleform::GFx::Value& a_flashObject,
			const char* a_relativeMemberPath) -> Scaleform::GFx::Value*;
		auto AcquireFlashObjectByPath(const Scaleform::GFx::Movie& a_parentMovie, const char* a_absoluteMemberPath)
			-> Scaleform::GFx::Value*;
	};

	static_assert(sizeof(BSGFxObject) == 0x38);
}
