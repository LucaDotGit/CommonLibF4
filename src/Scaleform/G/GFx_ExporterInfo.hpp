#pragma once

#include "Scaleform/G/GFx_FileTypeConstants.hpp"

namespace Scaleform::GFx
{
	class ExporterInfo
	{
	public:
		enum class ExportFlagConstants : std::uint32_t
		{
			None = 0,
			GlyphTexturesExported = 1 << 0,
			GradientTexturesExported = 1 << 1,
			GlyphsStripped = 1 << 4
		};

		// members
		REX::EnumSet<FileTypeConstants::FileFormatType, std::uint32_t> format; // 0x00
		const char* prefix;													   // 0x08
		const char* swfName;												   // 0x10
		std::uint16_t version;												   // 0x18
		REX::EnumSet<ExportFlagConstants, std::uint32_t> exportFlags;		   // 0x1C
	};

	static_assert(sizeof(ExporterInfo) == 0x20);
}
