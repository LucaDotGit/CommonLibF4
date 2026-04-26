#pragma once

namespace F4SE
{
	class IDelayFunctor;
	class SerializationInterface;

	class IObject
	{
	public:
		IObject() = default;

		IObject(const IObject&) = delete;
		IObject(IObject&&) = delete;

		IObject& operator=(const IObject&) = delete;
		IObject& operator=(IObject&&) = delete;

		virtual ~IObject() = default; // 00

		// add
		[[nodiscard]] virtual const char* GetObjectName() const = 0;								// 01
		[[nodiscard]] virtual std::uint32_t GetObjectVersion() const = 0;							// 02
		[[nodiscard]] virtual IDelayFunctor* GetAsDelayFunctor() { return nullptr; }				// 03
		virtual bool Save(const SerializationInterface* a_serializer) = 0;							// 04
		virtual bool Load(const SerializationInterface* a_serializer, std::uint32_t a_version) = 0; // 05
	};
	static_assert(sizeof(IObject) == 0x08);
}
