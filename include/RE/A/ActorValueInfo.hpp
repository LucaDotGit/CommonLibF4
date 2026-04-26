#pragma once

#include "RE/A/ActorValue.hpp"
#include "RE/B/BGSLocalizedString.hpp"
#include "RE/B/BSStringT.hpp"
#include "RE/T/TESDescription.hpp"
#include "RE/T/TESForm.hpp"
#include "RE/T/TESFullName.hpp"

#include "msvc/functional.hpp"

namespace RE
{
	class ActorValueOwner;

	class __declspec(novtable) ActorValueInfo
		: public TESForm,		// 000
		  public TESFullName,	// 020
		  public TESDescription // 030
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ActorValueInfo };
		inline static constexpr auto VTABLE{ VTABLE::ActorValueInfo };
		inline static constexpr auto FORM_TYPE{ FormType::kActorValue };

#define RUNTIME_DATA_CONTENT_01                                     \
	BSString formEditorID;								  /* 088 */ \
	std::array<ActorValueInfo*, 15> dependentActorValues; /* 098 */

#define RUNTIME_DATA_CONTENT_02                                     \
	std::array<const char*, 10> enumNames;				  /* 150 */ \
	BGSLocalizedString abbreviation;					  /* 1A0 */ \
	std::int32_t oldActorValue;							  /* 1A8 */ \
	REX::EnumSet<ActorValue::Flags, std::uint32_t> flags; /* 1AC */ \
	REX::Enum<ActorValue::AVType, std::int32_t> avType;	  /* 1B0 */ \
	std::uint32_t numDependentActorValues;				  /* 1B4 */ \
	std::uint32_t enumCount;							  /* 1B8 */ \
	std::int32_t fullCacheIndex;						  /* 1BC */ \
	std::int32_t permanentCacheIndex;					  /* 1C0 */ \
	REX::Float32 defaultValue;							  /* 1C4 */ \
	std::uint32_t sortIndex;							  /* 1C8 */

		class RuntimeData01
		{
		public:
			// members
			RUNTIME_DATA_CONTENT_01;
		};

		class RuntimeData02
		{
		public:
			// members
			RUNTIME_DATA_CONTENT_02;
		};

		using ModifiedCallbackType = void(Actor* a_actor, const ActorValueInfo& a_info, REX::Float32 a_originalValue, REX::Float32 a_delta, Actor* a_actorSource);
		using DerivationFunctionType = REX::Float32(const ActorValueOwner* a_actor, const ActorValueInfo& a_info);

		[[nodiscard]] RuntimeData01& GetRuntimeData01() noexcept;
		[[nodiscard]] const RuntimeData01& GetRuntimeData01() const noexcept;

		[[nodiscard]] RuntimeData02& GetRuntimeData02() noexcept;
		[[nodiscard]] const RuntimeData02& GetRuntimeData02() const noexcept;

		[[nodiscard]] auto GetModifiedCallback() noexcept
			-> std::variant<std::reference_wrapper<msvc::function<ModifiedCallbackType>>, std::reference_wrapper<msvc::function_old<ModifiedCallbackType>>>;

		[[nodiscard]] auto GetModifiedCallback() const noexcept
			-> std::variant<std::reference_wrapper<const msvc::function<ModifiedCallbackType>>, std::reference_wrapper<const msvc::function_old<ModifiedCallbackType>>>;

		[[nodiscard]] auto GetDerivationFunction() noexcept
			-> std::variant<std::reference_wrapper<msvc::function<DerivationFunctionType>>, std::reference_wrapper<msvc::function_old<DerivationFunctionType>>>;

		[[nodiscard]] auto GetDerivationFunction() const noexcept
			-> std::variant<std::reference_wrapper<const msvc::function<DerivationFunctionType>>, std::reference_wrapper<const msvc::function_old<DerivationFunctionType>>>;

#if COMMONLIB_RUNTIME_NG == 0 && COMMONLIB_RUNTIME_AE == 0
		msvc::function_old<ModifiedCallbackType> modifiedCallback;	   // 048
		RUNTIME_DATA_CONTENT_01;									   // 068
		msvc::function_old<DerivationFunctionType> derivationFunction; // 0F0
		RUNTIME_DATA_CONTENT_02;									   // 110
#elif COMMONLIB_RUNTIME_VR == 0 && COMMONLIB_RUNTIME_OG == 0
		msvc::function<ModifiedCallbackType> modifiedCallback;	   // 048
		RUNTIME_DATA_CONTENT_01;								   // 088
		msvc::function<DerivationFunctionType> derivationFunction; // 110
		RUNTIME_DATA_CONTENT_02;								   // 150
#endif
	};
#if COMMONLIB_RUNTIME_NG == 0 && COMMONLIB_RUNTIME_AE == 0
	static_assert(sizeof(ActorValueInfo) == 0x190);
#elif COMMONLIB_RUNTIME_VR == 0 && COMMONLIB_RUNTIME_OG == 0
	static_assert(sizeof(ActorValueInfo) == 0x1D0);
#else
	static_assert(sizeof(ActorValueInfo) == 0x048);
#endif
}

#undef RUNTIME_DATA_CONTENT_02

#undef RUNTIME_DATA_CONTENT_01
