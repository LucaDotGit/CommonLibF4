#pragma once

#include "RE/A/ActorValue.hpp"
#include "RE/B/BGSLocalizedString.hpp"
#include "RE/B/BSString.hpp"
#include "RE/T/TESDescription.hpp"
#include "RE/T/TESForm.hpp"
#include "RE/T/TESFullName.hpp"
#include "msvc/functional.hpp"

namespace RE
{
	class ActorValueOwner;

	class __declspec(novtable) ActorValueInfo :
		public TESForm,		  // 0x000
		public TESFullName,	  // 0x020
		public TESDescription // 0x030
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ActorValueInfo;
		inline static constexpr const auto& VTABLE = VTABLE::ActorValueInfo;
		inline static constexpr auto FORM_TYPE = FormType::ActorValue;

#define RUNTIME_DATA_CONTENT_01                                    \
	BSString formEditorID;								  /* 00 */ \
	std::array<ActorValueInfo*, 15> dependentActorValues; /* 10 */

#define RUNTIME_DATA_CONTENT_02                                    \
	std::array<const char*, 10> enumNames;				  /* 00 */ \
	BGSLocalizedString abbreviation;					  /* 50 */ \
	std::int32_t oldActorValue;							  /* 58 */ \
	REX::EnumSet<ActorValue::Flags, std::uint32_t> flags; /* 5C */ \
	REX::Enum<ActorValue::AVType, std::int32_t> avType;	  /* 60 */ \
	std::uint32_t numDependentActorValues;				  /* 64 */ \
	std::uint32_t enumCount;							  /* 68 */ \
	std::int32_t fullCacheIndex;						  /* 6C */ \
	std::int32_t permanentCacheIndex;					  /* 70 */ \
	REX::Float32 defaultValue;							  /* 74 */ \
	std::uint32_t sortIndex;							  /* 78 */

		class RuntimeData01
		{
		public:
			// members
			RUNTIME_DATA_CONTENT_01; // 0x00
		};

		static_assert(sizeof(RuntimeData01) == 0x88);

		class RuntimeData02
		{
		public:
			// members
			RUNTIME_DATA_CONTENT_02; // 0x00
		};

		static_assert(sizeof(RuntimeData02) == 0x80);

		using ModifiedCallbackType = void(
			Actor* a_actor,
			const ActorValueInfo& a_info,
			REX::Float32 a_originalValue,
			REX::Float32 a_delta,
			Actor* a_actorSource);
		using DerivationFunctionType = REX::Float32(const ActorValueOwner* a_actor, const ActorValueInfo& a_info);

		[[nodiscard]]
		auto GetRuntimeData01() noexcept -> RuntimeData01&;
		[[nodiscard]]
		auto GetRuntimeData01() const noexcept -> const RuntimeData01&;

		[[nodiscard]]
		auto GetRuntimeData02() noexcept -> RuntimeData02&;
		[[nodiscard]]
		auto GetRuntimeData02() const noexcept -> const RuntimeData02&;

		[[nodiscard]]
		auto GetModifiedCallback() noexcept -> std::variant<
			std::reference_wrapper<msvc::function<ModifiedCallbackType>>,
			std::reference_wrapper<msvc::function_old<ModifiedCallbackType>>>;

		[[nodiscard]]
		auto GetModifiedCallback() const noexcept -> std::variant<
			std::reference_wrapper<const msvc::function<ModifiedCallbackType>>,
			std::reference_wrapper<const msvc::function_old<ModifiedCallbackType>>>;

		[[nodiscard]]
		auto GetDerivationFunction() noexcept -> std::variant<
			std::reference_wrapper<msvc::function<DerivationFunctionType>>,
			std::reference_wrapper<msvc::function_old<DerivationFunctionType>>>;

		[[nodiscard]]
		auto GetDerivationFunction() const noexcept -> std::variant<
			std::reference_wrapper<const msvc::function<DerivationFunctionType>>,
			std::reference_wrapper<const msvc::function_old<DerivationFunctionType>>>;

		// members
#if (COMMONLIB_RUNTIME_NG == 0 && COMMONLIB_RUNTIME_AE == 0)
		msvc::function_old<ModifiedCallbackType> modifiedCallback;	   // 0x048
		RUNTIME_DATA_CONTENT_01;									   // 0x068
		msvc::function_old<DerivationFunctionType> derivationFunction; // 0x0F0
		RUNTIME_DATA_CONTENT_02;									   // 0x110
#elif (COMMONLIB_RUNTIME_VR == 0 && COMMONLIB_RUNTIME_OG == 0)
		msvc::function<ModifiedCallbackType> modifiedCallback;	   // 0x048
		RUNTIME_DATA_CONTENT_01;								   // 0x088
		msvc::function<DerivationFunctionType> derivationFunction; // 0x110
		RUNTIME_DATA_CONTENT_02;								   // 0x150
#endif
	};

#if (COMMONLIB_RUNTIME_NG == 0 && COMMONLIB_RUNTIME_AE == 0)
	static_assert(sizeof(ActorValueInfo) == 0x190);
#elif (COMMONLIB_RUNTIME_VR == 0 && COMMONLIB_RUNTIME_OG == 0)
	static_assert(sizeof(ActorValueInfo) == 0x1D0);
#else
	static_assert(sizeof(ActorValueInfo) == 0x048);
#endif
}

#undef RUNTIME_DATA_CONTENT_01
#undef RUNTIME_DATA_CONTENT_02
