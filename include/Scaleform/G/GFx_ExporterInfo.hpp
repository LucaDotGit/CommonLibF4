#pragma once

#include "Scaleform/G/GFx_FileTypeConstants.hpp"

namespace Scaleform::GFx
{
	class ExporterInfo
	{
	public:
		enum class ExportFlagConstants : std::uint32_t
		{
			kNone = 0,
			kGlyphTexturesExported = 1 << 0,
			kGradientTexturesExported = 1 << 1,
			kGlyphsStripped = 1 << 4
		};

		// members
		REX::EnumSet<FileTypeConstants::FileFormatType, std::uint32_t> format; // 00
		const char* prefix;													   // 08
		const char* swfName;												   // 10
		std::uint16_t version;												   // 18
		REX::EnumSet<ExportFlagConstants, std::uint32_t> exportFlags;		   // 1C
	};
	static_assert(sizeof(ExporterInfo) == 0x20);
}
