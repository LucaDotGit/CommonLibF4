#pragma once

#include "RE/B/BSGFxObject.hpp"

namespace RE
{
	class /*__declspec(novtable)*/ BSGFxDisplayObject : public BSGFxObject // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSGFxDisplayObject;
		inline static constexpr const auto& VTABLE = VTABLE::BSGFxDisplayObject;

		class InitialDisplayState
		{
		public:
			// members
			REX::Float32 originalWidth{static_cast<REX::Float32>(0.0)};	 // 0x00
			REX::Float32 originalHeight{static_cast<REX::Float32>(0.0)}; // 0x04
		};

		static_assert(sizeof(InitialDisplayState) == 0x08);

		explicit BSGFxDisplayObject(const Scaleform::GFx::Value& a_flashObject);
		BSGFxDisplayObject(const Scaleform::GFx::Value& a_flashObject, const char* a_relativePathToMember);
		BSGFxDisplayObject(const Scaleform::GFx::Movie& a_parentMovie, const char* a_pathToObject);

		BSGFxDisplayObject(const BSGFxDisplayObject&) = delete;
		BSGFxDisplayObject(BSGFxDisplayObject&&) = delete;

		auto operator=(const BSGFxDisplayObject&) -> BSGFxDisplayObject& = delete;
		auto operator=(BSGFxDisplayObject&&) -> BSGFxDisplayObject& = delete;

		virtual ~BSGFxDisplayObject(); // 0x00

		void RemoveChild(const BSGFxDisplayObject& a_child) const;

	private:
		void ctor_shared();

	public:
		// members
		BSGFxDisplayObject* parentDisplayObject{nullptr}; // 0x40
		InitialDisplayState initialState;				  // 0x48
	};

	static_assert(sizeof(BSGFxDisplayObject) == 0x50);
}
