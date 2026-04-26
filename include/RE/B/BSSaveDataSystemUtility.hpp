#pragma once

namespace RE
{
	class BSSaveDataSystemUtilityFile;

	class BSSaveDataSystemUtility
	{
	public:
		enum class RESULT : std::int32_t
		{
			kSuccess = 0,
			kCancel = 1,
			kFailed = 2
		};

		using SaveCompleteCallbackType = void (*)(RESULT, BSSaveDataSystemUtilityFile**);
		using LoadCompleteCallbackType = void (*)(RESULT, BSSaveDataSystemUtilityFile**);
	};
}
