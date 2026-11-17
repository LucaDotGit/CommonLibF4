#include "RE/M/Main.hpp"

#include "RE/N/NiNode.hpp"

namespace RE
{
	auto Main::GetSingleton() noexcept -> Main*
	{
		static const auto SINGLETON = REL::Relocation<Main**>(ID::Main::Singleton);
		return *SINGLETON;
	}

	auto Main::GetWorldRootNode() noexcept -> NiPointer<SceneGraph>&
	{
		static const auto WORLD_ROOT_NODE = REL::Relocation<NiPointer<SceneGraph>*>(ID::Main::WorldRootNode);
		return *WORLD_ROOT_NODE;
	}

	auto Main::GetMenuRootNode() noexcept -> NiPointer<SceneGraph>&
	{
		static const auto MENU_ROOT_NODE = REL::Relocation<NiPointer<SceneGraph>*>(ID::Main::MenuRootNode);
		return *MENU_ROOT_NODE;
	}

	auto Main::GetLandLODNode() noexcept -> NiNode*&
	{
		static const auto LAND_LOD_NODE = REL::Relocation<NiNode**>(ID::Main::LandLODNode);
		return *LAND_LOD_NODE;
	}

	auto Main::GetObjectLODNode() noexcept -> NiNode*&
	{
		static const auto OBJECT_LOD_NODE = REL::Relocation<NiNode**>(ID::Main::ObjectLODNode);
		return *OBJECT_LOD_NODE;
	}

	auto Main::GetDoneNewOrLoadGame() noexcept -> bool&
	{
		static const auto DONE_NEW_OR_LOAD_GAME = REL::Relocation<bool*>(ID::Main::DoneNewOrLoadGame);
		return *DONE_NEW_OR_LOAD_GAME;
	}

	auto Main::GetGameDataLoaded() noexcept -> bool&
	{
		static const auto GAME_DATE_LOADED = REL::Relocation<bool*>(ID::Main::GameDataLoaded);
		return *GAME_DATE_LOADED;
	}

	auto Main::GetGameSystemsShouldUpdate() noexcept -> bool&
	{
		static const auto GAME_SYSTEMS_SHOULD_UPDATE = REL::Relocation<bool*>(ID::Main::GameSystemsShouldUpdate);
		return *GAME_SYSTEMS_SHOULD_UPDATE;
	}

	void Main::SetCameraFOV(REX::Float32 a_fov)
	{
		using FuncType = decltype(&Main::SetCameraFOV);
		static const auto FUNC = REL::Relocation<FuncType>(ID::Main::SetCameraFOV);
		std::invoke(FUNC, this, a_fov);
	}
}
