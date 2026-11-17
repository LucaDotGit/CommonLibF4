#pragma once

#include "RE/B/BGSSceneAction.hpp"
#include "RE/B/BSTArray.hpp"

namespace RE
{
	class __declspec(novtable) BGSSceneActionStartScene : public BGSSceneAction // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSSceneActionStartScene;
		inline static constexpr auto VTABlE = VTABLE::BGSSceneActionStartScene;

		~BGSSceneActionStartScene() override; // 0x00

		// members
		BSTArray<STARTSCENEACTIONDATA*> scenes; // 0x20
		BGSScene* scene;						// 0x38
		std::uint16_t sceneStartPhase;			// 0x40
		bool endSceneSayGreeting;				// 0x42
	};

	static_assert(sizeof(BGSSceneActionStartScene) == 0x48);
}
