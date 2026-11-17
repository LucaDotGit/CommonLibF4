#pragma once

#include "RE/B/BSTSmartPointer.hpp"
#include "RE/E/ExtraDataList.hpp"
#include "RE/N/NiPoint3.hpp"

namespace RE
{
	class BGSObjectInstanceExtra;
	class BGSPrimitive;
	class INSTANCE_FILTER;

#if (__clang__ == 1)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnon-virtual-dtor"
#endif

#if (_MSC_VER > 0l)
#pragma warning(push)
#pragma warning(disable : 4'265)
#endif

	// NOLINTNEXTLINE(cppcoreguidelines-virtual-class-destructor)
	class __declspec(novtable) NEW_REFR_DATA
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::NEW_REFR_DATA;
		inline static constexpr const auto& VTABLE = VTABLE::NEW_REFR_DATA;

		// add
		virtual void HandlePre3D(TESObjectREFR* a_ref); // 0x00

		// members
		NiPoint3 location;							   // 0x08
		NiPoint3 direction;							   // 0x14
		TESBoundObject* object{nullptr};			   // 0x20
		TESObjectCELL* interior{nullptr};			   // 0x28
		TESWorldSpace* world{nullptr};				   // 0x30
		TESObjectREFR* reference{nullptr};			   // 0x38
		BGSPrimitive* addPrimitive{nullptr};		   // 0x40
		void* additionalData{nullptr};				   // 0x48
		BSTSmartPointer<ExtraDataList> extra{nullptr}; // 0x50
		INSTANCE_FILTER* instanceFilter{nullptr};	   // 0x58
		BGSObjectInstanceExtra* modExtra{nullptr};	   // 0x60
		std::uint16_t maxLevel{0};					   // 0x68
		bool forcePersist{false};					   // 0x6A
		bool clearStillLoadingFlag{false};			   // 0x6B
		bool initializeScripts{true};				   // 0x6C
		bool initiallyDisabled{false};				   // 0x6D
	};

	static_assert(sizeof(NEW_REFR_DATA) == 0x70);

#if (_MSC_VER > 0l)
#pragma warning(pop)
#endif

#if (__clang__ == 1)
#pragma clang diagnostic pop
#endif
}
