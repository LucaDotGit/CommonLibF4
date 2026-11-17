#pragma once

namespace RE::PowerUtils
{
	class TraverseConnectionsOptions
	{
	public:
		// members
		std::uint32_t ignoreMode; // 0x00
		bool wiredOnly;			  // 0x04
		bool inputsOnly;		  // 0x05
	};

	static_assert(sizeof(TraverseConnectionsOptions) == 0x08);
}
