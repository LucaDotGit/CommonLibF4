#pragma once

namespace RE
{
	class BSSaveDataSystemUtilityFile;

	class BSSaveDataSystemUtility
	{
	public:
		enum class RESULT : std::int32_t
		{
			Success = 0,
			Cancel = 1,
			Failed = 2
		};

		using SaveCompleteCallbackType = void (*)(RESULT, BSSaveDataSystemUtilityFile**);
		using LoadCompleteCallbackType = void (*)(RESULT, BSSaveDataSystemUtilityFile**);
	};
}
