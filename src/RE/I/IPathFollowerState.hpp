#pragma once

namespace RE
{
	class BSPathingStreamRead;
	class BSPathingStreamWrite;
	class ICheckEndReachedFunctorMapper;
	class MovementPlannerAgentReturnDataSmallDelta;
	class MovementTweenerAgentOutputData;
	class PathFollowerStateUpdateData;

	class IPathFollowerState
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::IPathFollowerState;
		inline static constexpr const auto& VTABLE = VTABLE::IPathFollowerState;

		enum class PATH_FOLLOWER_STATE_RESULT : std::uint32_t
		{
			Continue = 0,
			Done = 1
		};

		virtual ~IPathFollowerState(); // 0x00

		// add
		virtual auto Update(
			const PathFollowerStateUpdateData& a_updateData,
			MovementPlannerAgentReturnDataSmallDelta& a_returnData,
			MovementTweenerAgentOutputData& a_outputData) -> PATH_FOLLOWER_STATE_RESULT; // 0x01
		virtual void SaveGame(
			BSPathingStreamWrite& a_streamWrite,
			const ICheckEndReachedFunctorMapper& a_functorMapper) = 0; // 0x02
		virtual void LoadGame(
			BSPathingStreamRead& a_streamRead,
			const ICheckEndReachedFunctorMapper& a_functorMapper) = 0; // 0x03
	};

	static_assert(sizeof(IPathFollowerState) == 0x08);
}
