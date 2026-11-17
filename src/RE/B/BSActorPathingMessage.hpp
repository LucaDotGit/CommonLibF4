#pragma once

#include "RE/B/BSTSmartPointer.hpp"

namespace RE
{
	enum class PATHING_MESSAGE_TYPE : std::int32_t;

	class BSPathingRequest;
	class BSPathingSolution;

	class BSActorPathingMessage
	{
	public:
		// members
		REX::Enum<PATHING_MESSAGE_TYPE, std::int32_t> type; // 0x00
		BSTSmartPointer<BSPathingRequest> request;			// 0x08
		BSTSmartPointer<BSPathingSolution> solution;		// 0x10
	};

	static_assert(sizeof(BSActorPathingMessage) == 0x18);
}
