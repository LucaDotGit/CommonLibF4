#pragma once

namespace RE
{
	enum class PERK_ENTRY_TYPE
	{
		kQuest,
		kAbility,
		kEntryPoint
	};

	class BGSPerkEntry
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSPerkEntry };
		inline static constexpr auto VTABLE{ VTABLE::BGSPerkEntry };

		using EntryPoint = BGSEntryPoint::ENTRY_POINT;

		struct Header // PRKE
		{
		public:
			// members
			std::uint8_t rank;	   // 00
			std::uint8_t priority; // 01
			std::uint16_t unk02;   // 02
			std::uint32_t unk04;   // 04
		};
		static_assert(sizeof(Header) == 0x8);

		[[nodiscard]] virtual bool CheckConditionFilters(std::uint32_t a_numArgs, void* a_args); // 00
		[[nodiscard]] virtual EntryPoint GetFunction();											 // 01
		[[nodiscard]] virtual void* GetFunctionData() const;									 // 02

		virtual ~BGSPerkEntry(); // 03

		[[nodiscard]] virtual PERK_ENTRY_TYPE GetType() const = 0; // 04

		// members
		Header header; // 08 - PRKE
	};
	static_assert(sizeof(BGSPerkEntry) == 0x10);

	class BGSQuestPerkEntry
		: public BGSPerkEntry
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSQuestPerkEntry };
		inline static constexpr auto VTABLE{ VTABLE::BGSQuestPerkEntry };

		virtual ~BGSQuestPerkEntry() override; // 03

		[[nodiscard]] PERK_ENTRY_TYPE GetType() const override; // 04

		// members
		TESQuest* quest;	 // 10
		std::uint16_t stage; // 18
	};

	class BGSAbilityPerkEntry
		: public BGSPerkEntry
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSAbilityPerkEntry };
		inline static constexpr auto VTABLE{ VTABLE::BGSAbilityPerkEntry };

		~BGSAbilityPerkEntry() override; // 03

		[[nodiscard]] PERK_ENTRY_TYPE GetType() const override; // 04

		// members
		SpellItem* ability; // 10
	};
	static_assert(sizeof(BGSAbilityPerkEntry) == 0x18);

	class BGSEntryPointFunctionData
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSEntryPointFunctionData };
		inline static constexpr auto VTABLE{ VTABLE::BGSEntryPointFunctionData };

		enum class FunctionType
		{
			kInvalid,
			kOneValue,
			kTwoValue,
			kLeveledList,
			kActivateChoice,
			kSpellItem,
			kBooleanGraphVariable,
			kText,
			kActorValue
		};

		virtual ~BGSEntryPointFunctionData(); // 00

		[[nodiscard]] virtual FunctionType GetType() const = 0; // 01
	};
	static_assert(sizeof(BGSEntryPointFunctionData) == 0x8);

	class BGSEntryPointPerkEntry
		: public BGSPerkEntry
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSEntryPointPerkEntry };
		inline static constexpr auto VTABLE{ VTABLE::BGSEntryPointPerkEntry };

		struct EntryData // DATA
		{
		public:
			enum class Function
			{
				kSetValue,
				kAddValue,
				kMultiplyValue,
				kAddRangeToValue,
				kAddActorValueMult,
				kAbsoluteValue,
				kNegativeAbsoluteValue,
				kAddLeveledList,
				kAddActivateChoice,
				kSelectSpell,
				kSelectText,
				kSetToActorValueMult,
				kMultiplyActorValueMult,
				kMultiply1PlusActorValueMult,
				kSetText
			};

			// members
			REX::Enum<EntryPoint, std::uint8_t> entryPoint; // 00
			REX::Enum<Function, std::uint8_t> function;		// 01
			std::uint8_t numArgs;							// 02
			std::uint8_t unk03;								// 03
			std::uint32_t unk04;							// 04
		};
		static_assert(sizeof(EntryData) == 0x8);

		~BGSEntryPointPerkEntry() override; // 03

		[[nodiscard]] PERK_ENTRY_TYPE GetType() const override; // 04

		// members
		EntryData entryData;					 // 10 - DATA
		BGSEntryPointFunctionData* functionData; // 18
		TESCondition* conditions;				 // 20
		BGSPerk* perk;							 // 28
	};
	static_assert(sizeof(BGSEntryPointPerkEntry) == 0x30);

	class BGSEntryPointFunctionDataOneValue
		: public BGSEntryPointFunctionData
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSEntryPointFunctionDataOneValue };
		inline static constexpr auto VTABLE{ VTABLE::BGSEntryPointFunctionDataOneValue };

		~BGSEntryPointFunctionDataOneValue() override; // 00

		[[nodiscard]] FunctionType GetType() const override; // 01

		// members
		std::uint64_t unk08; // 08
		std::uint64_t unk10; // 10
		float value;		 // 14
	};

	class BGSEntryPointFunctionDataTwoValue
		: public BGSEntryPointFunctionData
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSEntryPointFunctionDataTwoValue };
		inline static constexpr auto VTABLE{ VTABLE::BGSEntryPointFunctionDataTwoValue };

		virtual ~BGSEntryPointFunctionDataTwoValue() override; // 00

		[[nodiscard]] FunctionType GetType() const override; // 01

		// members
		std::uint64_t unk08; // 08
		std::uint64_t unk10; // 10
		float value01;		 // 18
		float value02;		 // 1C
	};

	class BGSEntryPointFunctionDataLeveledList
		: public BGSEntryPointFunctionData
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSEntryPointFunctionDataLeveledList };
		inline static constexpr auto VTABLE{ VTABLE::BGSEntryPointFunctionDataLeveledList };

		virtual ~BGSEntryPointFunctionDataLeveledList() override; // 00

		// members
		TESLevItem* leveledList; // 08
	};
	static_assert(sizeof(BGSEntryPointFunctionDataLeveledList) == 0x10);

	class BGSEntryPointFunctionDataActivateChoice
		: public BGSEntryPointFunctionData
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSEntryPointFunctionDataActivateChoice };
		inline static constexpr auto VTABLE{ VTABLE::BGSEntryPointFunctionDataActivateChoice };

		enum class Flags01
		{
			kNone,
			kRunImmediately,
			kReplaceDefault
		};

		~BGSEntryPointFunctionDataActivateChoice() override; // 00

		[[nodiscard]] FunctionType GetType() const override; // 01

		// members
		std::uint64_t unk08;					   // 08
		std::uint64_t unk10;					   // 10
		BSFixedString label;					   // 18
		BGSPerk* perk;							   // 20
		SpellItem* appliedSpell;				   // 28
		REX::Enum<Flags01, std::uint16_t> flags01; // 30
		std::uint16_t flags02;					   // 32
		std::uint32_t unk24;					   // 34
	};

	class BGSEntryPointFunctionDataSpellItem
		: public BGSEntryPointFunctionData
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSEntryPointFunctionDataSpellItem };
		inline static constexpr auto VTABLE{ VTABLE::BGSEntryPointFunctionDataSpellItem };

		~BGSEntryPointFunctionDataSpellItem() override; // 00

		[[nodiscard]] FunctionType GetType() const override; // 01

		// members
		SpellItem* spell; // 08
	};
	static_assert(sizeof(BGSEntryPointFunctionDataSpellItem) == 0x10);

	class BGSEntryPointFunctionDataBooleanGraphVariable
		: public BGSEntryPointFunctionData
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSEntryPointFunctionDataBooleanGraphVariable };
		inline static constexpr auto VTABLE{ VTABLE::BGSEntryPointFunctionDataBooleanGraphVariable };

		virtual ~BGSEntryPointFunctionDataBooleanGraphVariable() override; // 00

		[[nodiscard]] FunctionType GetType() const override; // 01

		// members
		BSFixedString variable; // 08
	};
	static_assert(sizeof(BGSEntryPointFunctionDataBooleanGraphVariable) == 0x10);

	class BGSEntryPointFunctionDataText
		: public BGSEntryPointFunctionData
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSEntryPointFunctionDataText };
		inline static constexpr auto VTABLE{ VTABLE::BGSEntryPointFunctionDataText };

		~BGSEntryPointFunctionDataText() override; // 00

		[[nodiscard]] FunctionType GetType() const override; // 01

		// members
		BSFixedString text; // 08
	};
	static_assert(sizeof(BGSEntryPointFunctionDataText) == 0x10);

	class BGSEntryPointFunctionDataAVAndValue
		: public BGSEntryPointFunctionData
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSEntryPointFunctionDataAVAndValue };
		inline static constexpr auto VTABLE{ VTABLE::BGSEntryPointFunctionDataAVAndValue };

		virtual ~BGSEntryPointFunctionDataAVAndValue() override; // 00

		[[nodiscard]] FunctionType GetType() const override; // 01

		// members
		std::uint64_t unk08;		// 08
		std::uint64_t unk10;		// 10
		ActorValueInfo* actorValue; // 18
		float value;				// 20
	};
}
