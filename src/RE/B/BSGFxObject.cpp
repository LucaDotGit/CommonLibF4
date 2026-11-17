#include "RE/B/BSGFxObject.hpp"

namespace RE
{
	BSGFxObject::BSGFxObject(const Scaleform::GFx::Value& a_flashObject) :
		Scaleform::GFx::Value(a_flashObject)
	{
	}

	BSGFxObject::BSGFxObject(const Scaleform::GFx::Value& a_flashObject, const char* a_relativeMemberPath)
	{
		AcquireFlashObjectByMemberName(a_flashObject, a_relativeMemberPath);
	}

	BSGFxObject::BSGFxObject(const Scaleform::GFx::Movie& a_parentMovie, const char* a_absoluteMemberPath)
	{
		AcquireFlashObjectByPath(a_parentMovie, a_absoluteMemberPath);
	}

	auto BSGFxObject::AcquireFlashObjectByMemberName(
		const Scaleform::GFx::Value& a_flashObject,
		const char* a_relativeMemberPath) -> Scaleform::GFx::Value*
	{
		using FuncType = decltype(&BSGFxObject::AcquireFlashObjectByMemberName);
		static const auto FUNC = REL::Relocation<FuncType>(ID::BSGFxObject::AcquireFlashObjectByMemberName);
		return std::invoke(FUNC, this, a_flashObject, a_relativeMemberPath);
	}

	auto BSGFxObject::AcquireFlashObjectByPath(
		const Scaleform::GFx::Movie& a_parentMovie,
		const char* a_absoluteMemberPath) -> Scaleform::GFx::Value*
	{
		using FuncType = decltype(&BSGFxObject::AcquireFlashObjectByPath);
		static const auto FUNC = REL::Relocation<FuncType>(ID::BSGFxObject::AcquireFlashObjectByPath);
		return std::invoke(FUNC, this, a_parentMovie, a_absoluteMemberPath);
	}
}
