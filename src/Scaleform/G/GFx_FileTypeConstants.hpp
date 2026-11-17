#pragma once

namespace Scaleform::GFx
{
	class FileTypeConstants
	{
	public:
		enum class FileFormatType : std::int32_t
		{
			Unopened,
			Unknown,

			SWF,
			GFX,

			JPEG = 10,
			PNG = 11,
			GIF = 12,
			TGA = 13,
			DDS = 14,
			HDR = 15,
			BMP = 16,
			DIB = 17,
			PFM = 18,
			TIFF = 19,

			WAVE = 20,

			PVR = 21,
			ETC = 22,
			SIF = 23,
			GXT = 24,
			GTX = 25,

			NextAvail,
			MultiFormat = 0xFFFF - 1,
			Original = 0xFFFF
		};
	};

	static_assert(std::is_empty_v<FileTypeConstants>);
}
