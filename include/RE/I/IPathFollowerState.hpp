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
		inline static constexpr auto RTTI{ RTTI::IPathFollowerState };
		inline static constexpr auto VTABLE{ VTABLE::IPathFollowerState };

		enum class PATH_FOLLOWER_STATE_RESULT : std::uint32_t
		{
			kContinue = 0,
			kDone = 1
		};

		virtual ~IPathFollowerState(); // 00

		// add
		virtual PATH_FOLLOWER_STATE_RESULT Update(const PathFollowerStateUpdateData& a_updateData, MovementPlannerAgentReturnDataSmallDelta& a_returnData, MovementTweenerAgentOutputData& a_outputData); // 01
		virtual void SaveGame(BSPathingStreamWrite& a_streamWrite, const ICheckEndReachedFunctorMapper& a_functorMapper) = 0;																			  // 02
		virtual void LoadGame(BSPathingStreamRead& a_streamRead, const ICheckEndReachedFunctorMapper& a_functorMapper) = 0;																				  // 03
	};
	static_assert(sizeof(IPathFollowerState) == 0x08);
}
