#pragma once

#include "RE/B/BGSSceneAction.hpp"
#include "RE/B/BSTArray.hpp"

namespace RE
{
	class __declspec(novtable) BGSSceneActionStartScene
		: public BGSSceneAction // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSSceneActionStartScene };
		inline static constexpr auto VTABlE{ VTABLE::BGSSceneActionStartScene };

		~BGSSceneActionStartScene() override; // 00

		// members
		BSTArray<STARTSCENEACTIONDATA*> scenes; // 20
		BGSScene* scene;						// 38
		std::uint16_t sceneStartPhase;			// 40
		bool endSceneSayGreeting;				// 42
	};
	static_assert(sizeof(BGSSceneActionStartScene) == 0x48);
}
