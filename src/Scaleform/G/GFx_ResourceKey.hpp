#pragma once

namespace Scaleform::GFx
{
	class ResourceKey
	{
	public:
		using KeyHandle = void*;

		enum class KeyType : std::int32_t
		{
			None,
			Unique,
			File,
			Gradient,
			SubImage
		};

		class __declspec(novtable) KeyInterface
		{
		public:
			virtual ~KeyInterface() = default; // 0x00

			// add
			virtual void AddRef(KeyHandle a_data) = 0;										  // 0x01
			virtual void Release(KeyHandle a_data) = 0;										  // 0x02
			virtual auto GetKeyType(KeyHandle a_data) const -> KeyType = 0;					  // 0x03
			virtual auto GetHashCode(KeyHandle a_data) const -> std::size_t = 0;			  // 0x04
			virtual auto KeyEquals(KeyHandle a_data, const ResourceKey& a_other) -> bool = 0; // 0x05
			virtual auto GetFileURL(KeyHandle) const -> const char*; // 0x06 - { return nullptr; }
		};

		static_assert(sizeof(KeyInterface) == 0x08);

		// members
		KeyInterface* keyInterface; // 0x00
		KeyHandle keyData;			// 0x08
	};

	static_assert(sizeof(ResourceKey) == 0x10);
}
