#pragma once

#include "RE/M/MemoryManager.hpp"

namespace RE::Json
{
	class Value;
}

namespace RE
{
	class BSBinarySerializer;

	class __declspec(novtable) PipboyValue
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::PipboyValue;
		inline static constexpr const auto& VTABLE = VTABLE::PipboyValue;

		enum class SERIALIZATION_DATA_TYPE : std::int32_t
		{
			Bool = 0,
			Int8 = 1,
			Uint8 = 2,
			Int32 = 3,
			Uint32 = 4,
			Float = 5,
			String = 6,
			Array = 7,
			Object = 8
		};

		explicit PipboyValue(PipboyValue* a_parentValue) :
			parentValue(a_parentValue)
		{
			REL::EmplaceVtable(this);
		}

		virtual ~PipboyValue(); // 0x00

		// add
		virtual void CleanDirtyToGame();													   // 0x01
		virtual void Serialize(Json::Value& a_json) = 0;									   // 0x02
		virtual void SerializeChanges(BSBinarySerializer& a_serializer, bool a_fullSerialize); // 0x03
		virtual auto GetType() -> SERIALIZATION_DATA_TYPE = 0;								   // 0x04

		GAME_HEAP_REDEFINE_NEW(PipboyValue);

		[[nodiscard]]
		auto GetID() const noexcept -> std::uint32_t
		{
			return id;
		}

		[[nodiscard]]
		auto GetParentValue() const noexcept -> PipboyValue*
		{
			return parentValue;
		}

		void SetParentValue(PipboyValue* a_parentValue) noexcept
		{
			parentValue = a_parentValue;
		}

		[[nodiscard]]
		auto GetIsDirty() const noexcept -> bool
		{
			return isDirtyToGame || isDirtyToCompanion;
		}

		void SetIsDirty(bool a_dirty) noexcept
		{
			isDirtyToGame = a_dirty;
			isDirtyToCompanion = a_dirty;
		}

		[[nodiscard]]
		auto GetIsDirtyToGame() const noexcept -> bool
		{
			return isDirtyToGame;
		}

		void SetIsDirtyToGame(bool a_dirty) noexcept
		{
			isDirtyToGame = a_dirty;
		}

		[[nodiscard]]
		auto GetIsDirtyToCompanion() const noexcept -> bool
		{
			return isDirtyToCompanion;
		}

		void SetIsDirtyToCompanion(bool a_dirty) noexcept
		{
			isDirtyToCompanion = a_dirty;
		}

		// members
		std::uint32_t id{0};			// 0x08
		bool isDirtyToGame{false};		// 0x0C
		bool isDirtyToCompanion{false}; // 0x0D
		PipboyValue* parentValue;		// 0x10
	};

	static_assert(sizeof(PipboyValue) == 0x18);
}
