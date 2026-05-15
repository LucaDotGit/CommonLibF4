#pragma once

#include "RE/B/BSGFxObject.hpp"

namespace RE
{
	class /*__declspec(novtable)*/ BSGFxDisplayObject
		: public BSGFxObject // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSGFxDisplayObject };
		inline static constexpr auto VTABLE{ VTABLE::BSGFxDisplayObject };

		class InitialDisplayState
		{
		public:
			// members
			REX::Float32 originalWidth{ 0.0_f32 };	// 00
			REX::Float32 originalHeight{ 0.0_f32 }; // 04
		};
		static_assert(sizeof(InitialDisplayState) == 0x08);

		BSGFxDisplayObject(const ::Scaleform::GFx::Value& a_flashObject);
		BSGFxDisplayObject(const ::Scaleform::GFx::Value& a_flashObject, const char* a_relativePathToMember);
		BSGFxDisplayObject(const ::Scaleform::GFx::Movie& a_parentMovie, const char* a_pathToObject);

		virtual ~BSGFxDisplayObject(); // 00

		void RemoveChild(const BSGFxDisplayObject& a_child) const;

		// members
		BSGFxDisplayObject* parentDisplayObject{ nullptr }; // 40
		InitialDisplayState initialState;					// 48

	private:
		void ctor_shared();
	};
	static_assert(sizeof(BSGFxDisplayObject) == 0x50);
}
