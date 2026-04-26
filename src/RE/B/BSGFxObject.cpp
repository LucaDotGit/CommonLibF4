#include "RE/B/BSGFxObject.hpp"

namespace RE
{
	BSGFxObject::BSGFxObject(const ::Scaleform::GFx::Value& a_flashObject)
		: ::Scaleform::GFx::Value(a_flashObject)
	{
	}

	BSGFxObject::BSGFxObject(const ::Scaleform::GFx::Value& a_flashObject, const char* a_relativePathToMember)
	{
		AcquireFlashObjectByMemberName(a_flashObject, a_relativePathToMember);
	}

	BSGFxObject::BSGFxObject(const ::Scaleform::GFx::Movie& a_parentMovie, const char* a_pathToObject)
	{
		AcquireFlashObjectByPath(a_parentMovie, a_pathToObject);
	}

	::Scaleform::GFx::Value* BSGFxObject::AcquireFlashObjectByMemberName(const ::Scaleform::GFx::Value& a_flashObject, const char* a_relativePathToMember)
	{
		using FuncType = decltype(&BSGFxObject::AcquireFlashObjectByMemberName);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BSGFxObject::AcquireFlashObjectByMemberName };
		return std::invoke(FUNC, this, a_flashObject, a_relativePathToMember);
	}

	::Scaleform::GFx::Value* BSGFxObject::AcquireFlashObjectByPath(const ::Scaleform::GFx::Movie& a_parentMovie, const char* a_absolutePathToMember)
	{
		using FuncType = decltype(&BSGFxObject::AcquireFlashObjectByPath);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BSGFxObject::AcquireFlashObjectByPath };
		return std::invoke(FUNC, this, a_parentMovie, a_absolutePathToMember);
	}
}
