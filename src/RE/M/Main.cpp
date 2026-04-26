#include "RE/M/Main.hpp"

namespace RE
{
	Main* Main::GetSingleton()
	{
		static const auto SINGLETON = REL::Relocation<Main**>{ ID::Main::Singleton };
		return *SINGLETON;
	}

	NiPointer<SceneGraph>& Main::GetWorldRootNode()
	{
		static const auto WORLD_ROOT_NODE = REL::Relocation<NiPointer<SceneGraph>*>{ ID::Main::WorldRootNode };
		return *WORLD_ROOT_NODE;
	}

	NiPointer<SceneGraph>& Main::GetMenuRootNode()
	{
		static const auto MENU_ROOT_NODE = REL::Relocation<NiPointer<SceneGraph>*>{ ID::Main::MenuRootNode };
		return *MENU_ROOT_NODE;
	}

	bool& Main::GetDoneNewOrLoadGame()
	{
		static const auto DONE_NEW_OR_LOAD_GAME = REL::Relocation<bool*>{ ID::Main::DoneNewOrLoadGame };
		return *DONE_NEW_OR_LOAD_GAME;
	}

	bool& Main::GetGameDataLoaded()
	{
		static const auto GAME_DATE_LOADED = REL::Relocation<bool*>{ ID::Main::GameDataLoaded };
		return *GAME_DATE_LOADED;
	}

	bool& Main::GetGameSystemsShouldUpdate()
	{
		static const auto GAME_SYSTEMS_SHOULD_UPDATE = REL::Relocation<bool*>{ ID::Main::GameSystemsShouldUpdate };
		return *GAME_SYSTEMS_SHOULD_UPDATE;
	}

	void Main::SetCameraFOV(REX::Float32 a_fov)
	{
		using FuncType = decltype(&Main::SetCameraFOV);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::Main::SetCameraFOV };
		FUNC(this, a_fov);
	}
}
