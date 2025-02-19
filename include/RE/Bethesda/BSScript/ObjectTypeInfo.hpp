#pragma once

#include "RE/Bethesda/BSFixedString.hpp"
#include "RE/Bethesda/BSScript/IComplexType.hpp"
#include "RE/Bethesda/BSScript/PropertyGroupInfo.hpp"
#include "RE/Bethesda/BSScript/PropertyTypeInfo.hpp"
#include "RE/Bethesda/BSScript/Variable.hpp"
#include "RE/Bethesda/BSTArray.hpp"
#include "RE/Bethesda/BSTSmartPointer.hpp"

namespace RE::BSScript
{
	class IFunction;
	class IComplexType;
	class PropertyGroupInfo;

	class __declspec(novtable) ObjectTypeInfo
		: public IComplexType // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSScript__ObjectTypeInfo };
		inline static constexpr auto VTABLE{ VTABLE::BSScript__ObjectTypeInfo };

		enum class LinkValidState : std::uint32_t
		{
			kNotLinked,
			kCurrentlyLinking,
			kLinkedInvalid,
			kLinkedValid
		};

		[[nodiscard]] std::uint32_t GetVariableCount() const noexcept
		{
			auto count = 0ui32;
			for (auto iter = BSTSmartPointer{ this }; iter && iter->Valid(); iter = iter->parentTypeInfo) {
				count += iter->variableCount;
			}

			return count;
		}

		[[nodiscard]] bool Valid() const noexcept { return linkedValid == LinkValidState::kLinkedValid; }

		struct UnlinkedNativeFunction
		{
		public:
			// members
			UnlinkedNativeFunction* next;	 // 00
			BSTSmartPointer<IFunction> func; // 08
		};
		static_assert(sizeof(UnlinkedNativeFunction) == 0x10);

		struct UserFlagInfo
		{
		public:
			enum : std::uintptr_t
			{
				kSetOnObject = 1 << 0
			};

			BSFixedString GetUserFlag() const
			{
				auto sanitizedType = data & ~kSetOnObject;
				return *reinterpret_cast<BSFixedString*>(&sanitizedType);
			}

			// members
			std::uintptr_t data; // 00
		};
		static_assert(sizeof(UserFlagInfo) == 0x8);

		struct VariableInfo
		{
		public:
			// members
			BSFixedString name;	 // 00
			TypeInfo type;		 // 08
			std::uint64_t unk10; // 10 - Not sure what this is, maybe a hash
		};
		static_assert(sizeof(VariableInfo) == 0x18);

		struct InitialValueInfo
		{
		public:
			// members
			std::uint32_t variableIndex; // 00
			std::uint32_t pad04;		 // 04
			Variable initialValue;		 // 08
		};
		static_assert(sizeof(InitialValueInfo) == 0x18);

		struct PropertyInfo
		{
		public:
			// members
			BSFixedString name;	   // 00
			PropertyTypeInfo info; // 08
		};
		static_assert(sizeof(PropertyInfo) == 0x48);

		struct GlobalFuncInfo
		{
		public:
			// members
			BSTSmartPointer<IFunction> func; // 00
		};
		static_assert(sizeof(GlobalFuncInfo) == 0x8);

		struct MemberFuncInfo
		{
		public:
			// members
			BSTSmartPointer<IFunction> func; // 00
		};
		static_assert(sizeof(MemberFuncInfo) == 0x8);

		struct NamedStateInfo
		{
		public:
			enum : std::uint32_t
			{
				kFuncCountMask = 0x1FF,
				kFuncOffsetShift = 9
			};

			struct Func
			{
			public:
				// members
				BSTSmartPointer<IFunction> func; // 00
			};
			static_assert(sizeof(Func) == 0x8);

			[[nodiscard]] constexpr std::uint32_t GetNumFuncs() const noexcept
			{
				return memberFunctionCount;
			}

			Func* GetFuncIter()
			{
				return reinterpret_cast<Func*>((std::uintptr_t)this + memberFunctionOffset);
			}

			const Func* GetFuncIter() const
			{
				return reinterpret_cast<const Func*>((std::uintptr_t)this + memberFunctionOffset);
			}

			// members
			BSFixedString name;						// 00
			std::uint32_t memberFunctionCount : 9;	// 08 - 0
			std::uint32_t memberFunctionOffset : 9; // 09 - 1
			std::uint32_t pad0C;					// 0C
		};
		static_assert(sizeof(NamedStateInfo) == 0x10);

		~ObjectTypeInfo()
		{
			Dtor();
		}

		[[nodiscard]] const char* GetName() const
		{
			return name.c_str();
		}

		[[nodiscard]] ObjectTypeInfo* GetParent()
		{
			return parentTypeInfo.get();
		}

		[[nodiscard]] const ObjectTypeInfo* GetParent() const
		{
			return parentTypeInfo.get();
		}

		[[nodiscard]] TypeInfo::RawType GetRawType() const
		{
			return TypeInfo::RawType::kObject;
		}

		[[nodiscard]] constexpr bool IsLinked() const noexcept
		{
			switch (linkedValid) {
				case LinkValidState::kLinkedInvalid:
				case LinkValidState::kLinkedValid:
					return true;
				default:
					return false;
			}
		}

		[[nodiscard]] UnlinkedNativeFunction* GetUnlinkedFunctionIter()
		{
			return reinterpret_cast<UnlinkedNativeFunction*>(data);
		}

		[[nodiscard]] const UnlinkedNativeFunction* GetUnlinkedFunctionIter() const
		{
			return reinterpret_cast<const UnlinkedNativeFunction*>(data);
		}

		[[nodiscard]] constexpr std::uint32_t GetNumUserFlags() const noexcept
		{
			return userFlagCount;
		}

		[[nodiscard]] UserFlagInfo* GetUserFlagIter()
		{
			return reinterpret_cast<UserFlagInfo*>(data);
		}

		[[nodiscard]] const UserFlagInfo* GetUserFlagIter() const
		{
			return reinterpret_cast<const UserFlagInfo*>(data);
		}

		[[nodiscard]] constexpr std::uint32_t GetNumVariables() const noexcept
		{
			return variableCount;
		}

		[[nodiscard]] std::uint32_t GetTotalNumVariables() const;

		[[nodiscard]] VariableInfo* GetVariableIter()
		{
			return reinterpret_cast<VariableInfo*>(GetUserFlagIter() + GetNumUserFlags());
		}

		[[nodiscard]] const VariableInfo* GetVariableIter() const
		{
			return reinterpret_cast<const VariableInfo*>(GetUserFlagIter() + GetNumUserFlags());
		}

		[[nodiscard]] constexpr std::uint32_t GetNumInitalValues() const noexcept
		{
			return initialValueCount;
		}

		[[nodiscard]] InitialValueInfo* GetInitialValueIter()
		{
			return reinterpret_cast<InitialValueInfo*>(GetVariableIter() + GetNumVariables());
		}

		[[nodiscard]] const InitialValueInfo* GetInitialValueIter() const
		{
			return reinterpret_cast<const InitialValueInfo*>(GetVariableIter() + GetNumVariables());
		}

		[[nodiscard]] constexpr std::uint32_t GetNumProperties() const noexcept
		{
			return propertyCount;
		}

		[[nodiscard]] PropertyInfo* GetPropertyIter()
		{
			return reinterpret_cast<PropertyInfo*>(GetInitialValueIter() + GetNumInitalValues());
		}

		[[nodiscard]] const PropertyInfo* GetPropertyIter() const
		{
			return reinterpret_cast<const PropertyInfo*>(GetInitialValueIter() + GetNumInitalValues());
		}

		[[nodiscard]] constexpr std::uint32_t GetNumGlobalFuncs() const noexcept
		{
			return staticFunctionCount;
		}

		[[nodiscard]] GlobalFuncInfo* GetGlobalFuncIter()
		{
			return reinterpret_cast<GlobalFuncInfo*>(GetPropertyIter() + GetNumProperties());
		}

		[[nodiscard]] const GlobalFuncInfo* GetGlobalFuncIter() const
		{
			return reinterpret_cast<const GlobalFuncInfo*>(GetPropertyIter() + GetNumProperties());
		}

		[[nodiscard]] constexpr std::uint32_t GetNumMemberFuncs() const noexcept
		{
			return emptyStateMemberFunctionCount;
		}

		[[nodiscard]] MemberFuncInfo* GetMemberFuncIter()
		{
			return reinterpret_cast<MemberFuncInfo*>(GetGlobalFuncIter() + GetNumGlobalFuncs());
		}

		[[nodiscard]] const MemberFuncInfo* GetMemberFuncIter() const
		{
			return reinterpret_cast<const MemberFuncInfo*>(GetGlobalFuncIter() + GetNumGlobalFuncs());
		}

		[[nodiscard]] constexpr std::uint32_t GetNumNamedStates() const noexcept
		{
			return namedStateCount;
		}

		[[nodiscard]] NamedStateInfo* GetNamedStateIter()
		{
			return reinterpret_cast<NamedStateInfo*>(GetMemberFuncIter() + GetNumMemberFuncs());
		}

		[[nodiscard]] const NamedStateInfo* GetNamedStateIter() const
		{
			return reinterpret_cast<const NamedStateInfo*>(GetMemberFuncIter() + GetNumMemberFuncs());
		}

		[[nodiscard]] NamedStateInfo* GetDefaultState()
		{
			if (GetNumNamedStates() == 0) {
				return nullptr;
			}

			auto* stateIter = GetNamedStateIter();
			return &stateIter[initialState];
		}

		[[nodiscard]] const NamedStateInfo* GetDefaultState() const
		{
			if (GetNumNamedStates() == 0) {
				return nullptr;
			}

			const auto* stateIter = GetNamedStateIter();
			return &stateIter[initialState];
		}

		[[nodiscard]] std::uint32_t GetPropertyIndex(const BSFixedString& a_name) const;

		// members
		BSFixedString name;											 // 10
		BSTSmartPointer<ObjectTypeInfo> parentTypeInfo;				 // 18
		BSFixedString docString;									 // 20
		BSTArray<BSTSmartPointer<PropertyGroupInfo>> propertyGroups; // 28
		LinkValidState linkedValid : 2;								 // 40:00 - 0 or 1 -> data == UnlinkedNativeFunction*, 2 or 3 -> data == normal progression
		std::uint32_t isConst : 1;									 // 40:02
		std::uint32_t userFlagCount : 5;							 // 40:03
		std::uint32_t variableCount : 10;							 // 40:08
		std::uint32_t variableUserFlagCount : 6;					 // 40:18
		std::uint32_t initialValueCount : 10;						 // 44:00
		std::uint32_t propertyCount : 10;							 // 44:10
		std::uint32_t staticFunctionCount : 9;						 // 44:20
		std::uint32_t emptyStateMemberFunctionCount : 11;			 // 48:00
		std::uint32_t namedStateCount : 7;							 // 48:11
		std::uint32_t initialState : 7;								 // 48:18
		void* data;													 // 50

	private:
		void Dtor();
	};
	static_assert(sizeof(ObjectTypeInfo) == 0x58);
}
