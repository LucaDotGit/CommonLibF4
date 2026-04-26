#include "RE/B/BSGFxDisplayObject.hpp"

namespace RE
{
	BSGFxDisplayObject::BSGFxDisplayObject(const ::Scaleform::GFx::Value& a_flashObject)
		: BSGFxObject(a_flashObject)
	{
		ctor_shared();
	}

	BSGFxDisplayObject::BSGFxDisplayObject(const ::Scaleform::GFx::Value& a_flashObject, const char* a_relativePathToMember)
		: BSGFxObject(a_flashObject, a_relativePathToMember)
	{
		ctor_shared();
	}

	BSGFxDisplayObject::BSGFxDisplayObject(const ::Scaleform::GFx::Movie& a_parentMovie, const char* a_pathToObject)
		: BSGFxObject(a_parentMovie, a_pathToObject)
	{
		ctor_shared();
	}

	BSGFxDisplayObject::~BSGFxDisplayObject()
	{
		if (parentDisplayObject) {
			parentDisplayObject->RemoveChild(*this);
		}
	}

	void BSGFxDisplayObject::RemoveChild(const BSGFxDisplayObject& a_child) const
	{
		using FuncType = decltype(&BSGFxDisplayObject::RemoveChild);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BSGFxDisplayObject::RemoveChild };
		FUNC(this, a_child);
	}

	void BSGFxDisplayObject::ctor_shared()
	{
		REL::EmplaceVtable(this);

		auto width = ::Scaleform::GFx::Value();
		if (GetMember("width", std::addressof(width)) && width.IsNumber()) {
			initialState.originalWidth = static_cast<REX::Float32>(width.GetNumber());
		}

		auto height = ::Scaleform::GFx::Value();
		if (GetMember("height", std::addressof(height)) && height.IsNumber()) {
			initialState.originalHeight = static_cast<REX::Float32>(height.GetNumber());
		}
	}
}
