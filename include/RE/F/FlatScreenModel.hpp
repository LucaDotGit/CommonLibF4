#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTSingleton.hpp"

namespace RE
{
	class UIAdvanceMenusFunctionCompleteEvent;

	class __declspec(novtable) FlatScreenModel
		: public BSTEventSink<UIAdvanceMenusFunctionCompleteEvent>, // 00
		  public BSTSingletonSDM<FlatScreenModel>					// 08
	{
	public:
		inline static constexpr auto RTTI{ RTTI::FlatScreenModel };
		inline static constexpr auto VTABLE{ VTABLE::FlatScreenModel };

		[[nodiscard]] static FlatScreenModel* GetSingleton()
		{
			static const auto SINGLETON = REL::Relocation<FlatScreenModel**>{ ID::FlatScreenModel::Singleton };
			return *SINGLETON;
		}

		// members
		BSFixedString customRendererName; // 10
		void* model;					  // 18 - TODO: `BSResource::RHandleType<BSResource::Entry<NiPointer<NiNode>, BSResource::EntryDBTraits<BSModelDB::DBTraits, BSResource::EntryDB<BSModelDB::DBTraits>>::CArgs>, BSResource::EntryDB<BSModelDB::DBTraits>>`
	};
	static_assert(sizeof(FlatScreenModel) == 0x20);
}
