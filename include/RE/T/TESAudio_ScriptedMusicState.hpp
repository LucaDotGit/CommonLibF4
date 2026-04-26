#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class TESLoadGameEvent;
}

namespace RE::TESAudio
{
	class __declspec(novtable) ScriptedMusicState
		: public BSTEventSink<TESLoadGameEvent>,	 // 00
		  public BSTSingletonSDM<ScriptedMusicState> // 08
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESAudio__ScriptedMusicState };
		inline static constexpr auto VTABLE{ VTABLE::TESAudio__ScriptedMusicState };

		~ScriptedMusicState() override; // 00

		[[nodiscard]] static ScriptedMusicState* GetSingleton()
		{
			static const auto SINGLETON = REL::Relocation<ScriptedMusicState**>{ ID::TESAudio::ScriptedMusicState::Singleton };
			return *SINGLETON;
		}

		void Remove(BGSMusicType* a_toRemove)
		{
			using FuncType = decltype(&ScriptedMusicState::Remove);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESAudio::ScriptedMusicState::Remove };
			FUNC(this, a_toRemove);
		}

		// members
		BSTSmallArray<BGSMusicType*, 2> currentTypes;
	};
	static_assert(sizeof(ScriptedMusicState) == 0x30);
}
