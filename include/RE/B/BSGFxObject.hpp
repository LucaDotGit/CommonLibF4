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
	class BSGFxObject
		: public ::Scaleform::GFx::Value, // 00
		  public UsesBSGFXFunctionHandler // 20
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSGFxObject };

		BSGFxObject(const ::Scaleform::GFx::Value& a_flashObject);
		BSGFxObject(const ::Scaleform::GFx::Value& a_flashObject, const char* a_relativePathToMember);
		BSGFxObject(const ::Scaleform::GFx::Movie& a_parentMovie, const char* a_pathToObject);

		GAME_HEAP_REDEFINE_NEW(BSGFxObject);

		::Scaleform::GFx::Value* AcquireFlashObjectByMemberName(const ::Scaleform::GFx::Value& a_flashObject, const char* a_relativePathToMember);
		::Scaleform::GFx::Value* AcquireFlashObjectByPath(const ::Scaleform::GFx::Movie& a_parentMovie, const char* a_absolutePathToMember);
	};
	static_assert(sizeof(BSGFxObject) == 0x38);
}
