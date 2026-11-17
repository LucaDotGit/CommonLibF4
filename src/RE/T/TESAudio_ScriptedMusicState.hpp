#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class TESLoadGameEvent;
}

namespace RE::TESAudio
{
	class __declspec(novtable) ScriptedMusicState :
		public BSTEventSink<TESLoadGameEvent>,	   // 0x00
		public BSTSingletonSDM<ScriptedMusicState> // 0x08
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESAudio__ScriptedMusicState;
		inline static constexpr const auto& VTABLE = VTABLE::TESAudio__ScriptedMusicState;

		~ScriptedMusicState() override; // 0x00

		[[nodiscard]]
		static auto GetSingleton() noexcept -> ScriptedMusicState*
		{
			static const auto SINGLETON =
				REL::Relocation<ScriptedMusicState**>{ID::TESAudio::ScriptedMusicState::Singleton};
			return *SINGLETON;
		}

		void Remove(BGSMusicType* a_toRemove)
		{
			using FuncType = decltype(&ScriptedMusicState::Remove);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESAudio::ScriptedMusicState::Remove);
			std::invoke(FUNC, this, a_toRemove);
		}

		// members
		BSTSmallArray<BGSMusicType*, 2> currentTypes;
	};

	static_assert(sizeof(ScriptedMusicState) == 0x30);
}
