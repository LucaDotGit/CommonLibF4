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
	concept BSTempEffectConstraint =
		std::derived_from<T, BSTempEffect> &&
		!std::is_pointer_v<T> &&
		!std::is_reference_v<T> &&
		std::same_as<std::remove_cv_t<decltype(T::EFFECT_TYPE)>, TEMP_EFFECT_TYPE>;
}

namespace RE
{
	class BGSLoadGameBuffer;
	class BGSSaveGameBuffer;
	class NiAVObject;

	class __declspec(novtable) BSTempEffect
		: public NiObject // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSTempEffect };
		inline static constexpr auto VTABLE{ VTABLE::BSTempEffect };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::BSTempEffect };
		inline static constexpr auto EFFECT_TYPE{ TEMP_EFFECT_TYPE::kDefault };

		~BSTempEffect() override; // 00

		// add
		virtual void Initialize();									   // 25 - { initialized = true; }
		virtual void Attach();										   // 26 - { return; }
		virtual void Detach();										   // 27 - { return; }
		virtual bool Update(REX::Float32 a_arg01);					   // 28
		[[nodiscard]] virtual NiAVObject* Get3D() const;			   // 29 - { return nullptr; }
		[[nodiscard]] virtual bool GetManagerHandlesSaveLoad() const;  // 2A - { return true; }
		[[nodiscard]] virtual bool GetClearWhenCellIsUnloaded() const; // 2B - { return true; }
		[[nodiscard]] virtual TEMP_EFFECT_TYPE GetType() const;		   // 2C - { return TEMP_EFFECT_TYPE::kDefault; }
		virtual void SaveGame(BGSSaveGameBuffer* a_buf);			   // 2D
		virtual void LoadGame(BGSLoadGameBuffer* a_buf);			   // 2E
		virtual void FinishLoadGame(BGSLoadGameBuffer* a_buf);		   // 2F - { return; }
		[[nodiscard]] virtual bool IsInterfaceEffect() const;		   // 30 - { return false; }
		virtual void SetInterfaceEffect(bool a_set);				   // 31 - { return; }
		[[nodiscard]] virtual bool GetStackable() const;			   // 32 - { return false; }
		virtual bool GetStackableMatch(BSTempEffect* a_effect) const;  // 33 - { return false; }
		virtual void Push();										   // 34 - { return; }
		virtual void Pop();											   // 35 - { return; }
		virtual void HandleDeferredDeleteImpl();					   // 36

		[[nodiscard]] bool Is(TEMP_EFFECT_TYPE a_type) const noexcept
		{
			return GetType() == a_type;
		}

		template <class... Args>
		[[nodiscard]] bool Is(Args... a_args) const noexcept
			requires((std::same_as<Args, TEMP_EFFECT_TYPE> && ...))
		{
			return (Is(a_args) || ...);
		}

		template <Impl::BSTempEffectConstraint T>
		[[nodiscard]] bool Is() const noexcept
		{
			return Is(T::EFFECT_TYPE);
		}

		[[nodiscard]] bool IsNot(TEMP_EFFECT_TYPE a_type) const noexcept
		{
			return !Is(a_type);
		}

		template <class... Args>
		[[nodiscard]] bool IsNot(Args... a_args) const noexcept
			requires((std::same_as<Args, TEMP_EFFECT_TYPE> && ...))
		{
			return (IsNot(a_args) && ...);
		}

		template <Impl::BSTempEffectConstraint T>
		[[nodiscard]] bool IsNot() const noexcept
		{
			return IsNot(T::EFFECT_TYPE);
		}

		template <Impl::BSTempEffectConstraint T>
		[[nodiscard]] T* As() noexcept
		{
			return Is<T>() ? static_cast<T*>(this) : nullptr;
		}

		template <Impl::BSTempEffectConstraint T>
		[[nodiscard]] const T* As() const noexcept
		{
			return Is<T>() ? static_cast<const T*>(this) : nullptr;
		}

		// members
		REX::Float32 lifetime;	// 10
		TESObjectCELL* cell;	// 18
		REX::Float32 age;		// 20
		bool initialized;		// 24
		std::uint32_t effectID; // 28
	};
	static_assert(sizeof(BSTempEffect) == 0x30);
}
