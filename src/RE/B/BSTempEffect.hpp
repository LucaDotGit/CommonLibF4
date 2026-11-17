#pragma once

#include "RE/N/NiObject.hpp"
#include "RE/T/TEMP_EFFECT_TYPE.hpp"

namespace RE
{
	class BSTempEffect;
}

namespace RE::Impl
{
	template <class T>
	concept BSTempEffectConstraint = std::derived_from<T, BSTempEffect> &&
									 !REX::pointer<T> &&
									 !REX::reference<T> &&
									 std::same_as<std::remove_cv_t<decltype(T::EFFECT_TYPE)>, TEMP_EFFECT_TYPE>;
}

namespace RE
{
	class BGSLoadGameBuffer;
	class BGSSaveGameBuffer;
	class NiAVObject;

	class __declspec(novtable) BSTempEffect : public NiObject // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSTempEffect;
		inline static constexpr const auto& VTABLE = VTABLE::BSTempEffect;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::BSTempEffect;
		inline static constexpr auto EFFECT_TYPE = TEMP_EFFECT_TYPE::Default;

		~BSTempEffect() override; // 0x00

		// add
		virtual void Initialize();						   // 0x25 - { initialized = true; }
		virtual void Attach();							   // 0x26 - { return; }
		virtual void Detach();							   // 0x27 - { return; }
		virtual auto Update(REX::Float32 a_arg01) -> bool; // 0x28
		[[nodiscard]]
		virtual auto Get3D() const -> NiAVObject*; // 0x29 - { return nullptr; }
		[[nodiscard]]
		virtual auto GetManagerHandlesSaveLoad() const -> bool; // 0x2A - { return true; }
		[[nodiscard]]
		virtual auto GetClearWhenCellIsUnloaded() const -> bool; // 0x2B - { return true; }
		[[nodiscard]]
		virtual auto GetType() const -> TEMP_EFFECT_TYPE;		  // 0x2C - { return TEMP_EFFECT_TYPE::Default; }
		virtual void SaveGame(BGSSaveGameBuffer* a_buffer);		  // 0x2D
		virtual void LoadGame(BGSLoadGameBuffer* a_buffer);		  // 0x2E
		virtual void FinishLoadGame(BGSLoadGameBuffer* a_buffer); // 0x2F - { return; }
		[[nodiscard]]
		virtual auto IsInterfaceEffect() const -> bool; // 0x30 - { return false; }
		virtual void SetInterfaceEffect(bool a_set);	// 0x31 - { return; }
		[[nodiscard]]
		virtual auto GetStackable() const -> bool;							  // 0x32 - { return false; }
		virtual auto GetStackableMatch(BSTempEffect* a_effect) const -> bool; // 0x33 - { return false; }
		virtual void Push();												  // 0x34 - { return; }
		virtual void Pop();													  // 0x35 - { return; }
		virtual void HandleDeferredDeleteImpl();							  // 0x36

		[[nodiscard]]
		auto Is(TEMP_EFFECT_TYPE a_type) const noexcept -> bool
		{
			return GetType() == a_type;
		}

		template <class... Args>
		[[nodiscard]]
		auto Is(Args... a_args) const noexcept -> bool
			requires((std::same_as<Args, TEMP_EFFECT_TYPE> && ...))
		{
			return (Is(a_args) || ...);
		}

		template <Impl::BSTempEffectConstraint T>
		[[nodiscard]]
		auto Is() const noexcept -> bool
		{
			return Is(T::EFFECT_TYPE);
		}

		[[nodiscard]]
		auto IsNot(TEMP_EFFECT_TYPE a_type) const noexcept -> bool
		{
			return !Is(a_type);
		}

		template <class... Args>
		[[nodiscard]]
		auto IsNot(Args... a_args) const noexcept -> bool
			requires((std::same_as<Args, TEMP_EFFECT_TYPE> && ...))
		{
			return (IsNot(a_args) && ...);
		}

		template <Impl::BSTempEffectConstraint T>
		[[nodiscard]]
		auto IsNot() const noexcept -> bool
		{
			return IsNot(T::EFFECT_TYPE);
		}

		template <Impl::BSTempEffectConstraint T>
		[[nodiscard]]
		auto As() noexcept -> T*
		{
			return Is<T>() ? static_cast<T*>(this) : nullptr;
		}

		template <Impl::BSTempEffectConstraint T>
		[[nodiscard]]
		auto As() const noexcept -> const T*
		{
			return Is<T>() ? static_cast<const T*>(this) : nullptr;
		}

		// members
		REX::Float32 lifetime;	// 0x10
		TESObjectCELL* cell;	// 0x18
		REX::Float32 age;		// 0x20
		bool initialized;		// 0x24
		std::uint32_t effectID; // 0x28
	};

	static_assert(sizeof(BSTempEffect) == 0x30);
}
