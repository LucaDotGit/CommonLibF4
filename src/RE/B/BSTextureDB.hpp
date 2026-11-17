#pragma once

namespace RE
{
	class BSTextureDB
	{
	public:
		class DBTraits
		{
		public:
			class ArgsType
			{
			public:
				// members
				std::uint32_t loadLevel; // 0x00
				bool isCubeMap;			 // 0x04
				bool replicateCubeMap;	 // 0x05
				bool isDDX;				 // 0x06
				bool isSRGB;			 // 0x07
				bool allowDegrade;		 // 0x08
			};

			static_assert(sizeof(ArgsType) == 0x0C);
		};

		static_assert(std::is_empty_v<DBTraits>);
	};
}
