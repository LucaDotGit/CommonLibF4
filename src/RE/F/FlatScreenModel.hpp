#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTSingleton.hpp"

namespace RE
{
	class UIAdvanceMenusFunctionCompleteEvent;

	class __declspec(novtable) FlatScreenModel :
		public BSTEventSink<UIAdvanceMenusFunctionCompleteEvent>, // 0x00
		public BSTSingletonSDM<FlatScreenModel>					  // 0x08
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::FlatScreenModel;
		inline static constexpr const auto& VTABLE = VTABLE::FlatScreenModel;

		[[nodiscard]]
		static auto GetSingleton() noexcept -> FlatScreenModel*
		{
			static const auto SINGLETON = REL::Relocation<FlatScreenModel**>(ID::FlatScreenModel::Singleton);
			return *SINGLETON;
		}

		// members
		BSFixedString customRendererName; // 0x10
		void* model;					  // 0x18 - To-Do: `BSResource::RHandleType<BSResource::Entry<NiPointer<NiNode>,
										  // BSResource::EntryDBTraits<BSModelDB::DBTraits,
		// BSResource::EntryDB<BSModelDB::DBTraits>>::CArgs>, BSResource::EntryDB<BSModelDB::DBTraits>>`
	};

	static_assert(sizeof(FlatScreenModel) == 0x20);
}
