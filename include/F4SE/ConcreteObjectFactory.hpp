#pragma once

#include "F4SE/Core.hpp"
#include "F4SE/IObject.hpp"
#include "F4SE/IObjectFactory.hpp"

#include "REX/NotNull.hpp"
#include "REX/Own.hpp"
#include "REX/Singleton.hpp"
#include "REX/StaticString.hpp"

namespace F4SE
{
	template <Impl::IObjectConstraint T, REX::StaticString ObjectName>
	class ConcreteObjectFactory final
		: public REX::Singleton<ConcreteObjectFactory<T, ObjectName>>,
		  public IObjectFactory
	{
	public:
		using value_type = T;

		inline static constexpr auto OBJECT_NAME = ObjectName;

		ConcreteObjectFactory() = default;

		ConcreteObjectFactory(const ConcreteObjectFactory&) = delete;
		ConcreteObjectFactory(ConcreteObjectFactory&&) = delete;

		ConcreteObjectFactory& operator=(const ConcreteObjectFactory&) = delete;
		ConcreteObjectFactory& operator=(ConcreteObjectFactory&&) = delete;

		~ConcreteObjectFactory() noexcept override = default; // 00

		// override (IObjectFactory)
		[[nodiscard]] REX::Owner<IObject*> Create() const override { return CreateObjectImpl(DEFAULT_SERIALIZATION_TAG).get().release(); } // 01
		void Delete(REX::Owner<IObject*> a_object) const override { DeleteObjectImpl(a_object); }										   // 02
		[[nodiscard]] const char* GetObjectName() const override { return OBJECT_NAME.data(); }											   // 03

		template <class... Args>
		[[nodiscard]] auto CreateObject() const
			-> REX::NotNull<std::unique_ptr<value_type>>
			requires(std::is_default_constructible_v<value_type>)
		{
			return CreateObjectImpl();
		}

		template <class... Args>
		[[nodiscard]] auto CreateObject(Args&&... a_args) const
			-> REX::NotNull<std::unique_ptr<value_type>>
			requires(std::is_constructible_v<value_type, Args...>)
		{
			return CreateObjectImpl(std::forward<Args>(a_args)...);
		}

		void DeleteObject(REX::Owner<value_type*> a_object) const
		{
			DeleteObjectImpl(a_object);
		}

	private:
		[[nodiscard]] static auto CreateObjectImpl()
			-> REX::NotNull<std::unique_ptr<value_type>>
			requires(std::is_default_constructible_v<value_type>)
		{
			return std::make_unique<value_type>();
		}

		template <class... Args>
		[[nodiscard]] static auto CreateObjectImpl(Args&&... a_args)
			-> REX::NotNull<std::unique_ptr<value_type>>
			requires(std::is_constructible_v<value_type, Args...>)
		{
			return std::make_unique<value_type>(std::forward<Args>(a_args)...);
		}

		static void DeleteObjectImpl(REX::Owner<IObject*> a_object)
		{
			delete a_object;
		}
	};
}
