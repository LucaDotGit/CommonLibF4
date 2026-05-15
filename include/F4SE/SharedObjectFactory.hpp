#pragma once

#include "F4SE/Core.hpp"
#include "F4SE/IObject.hpp"
#include "F4SE/IObjectFactory.hpp"

#include "REX/NotNull.hpp"
#include "REX/Own.hpp"
#include "REX/Singleton.hpp"
#include "REX/StaticString.hpp"

namespace F4SE::Impl
{
	class SharedObjectFactoryData final
		: public REX::Singleton<SharedObjectFactoryData>
	{
	public:
		SharedObjectFactoryData() = default;
		~SharedObjectFactoryData() noexcept = default;

		SharedObjectFactoryData(const SharedObjectFactoryData&) = delete;
		SharedObjectFactoryData(SharedObjectFactoryData&&) = delete;

		SharedObjectFactoryData& operator=(const SharedObjectFactoryData&) = delete;
		SharedObjectFactoryData& operator=(SharedObjectFactoryData&&) = delete;

		mutable std::shared_mutex mutex;
		std::unordered_map<REX::Observer<const F4SE::IObject*>, REX::NotNull<std::shared_ptr<F4SE::IObject>>> objectMap;
	};
}

namespace F4SE
{
	template <Impl::IObjectConstraint T, REX::StaticString ObjectName>
	class SharedObjectFactory final
		: public REX::Singleton<SharedObjectFactory<T, ObjectName>>,
		  public IObjectFactory
	{
	public:
		using value_type = T;

		inline static constexpr auto OBJECT_NAME = ObjectName;

		SharedObjectFactory() = default;

		SharedObjectFactory(const SharedObjectFactory&) = delete;
		SharedObjectFactory(SharedObjectFactory&&) = delete;

		SharedObjectFactory& operator=(const SharedObjectFactory&) = delete;
		SharedObjectFactory& operator=(SharedObjectFactory&&) = delete;

		~SharedObjectFactory() noexcept override = default; // 00

		// override (IObjectFactory)
		[[nodiscard]] REX::Owner<IObject*> Create() const override { return CreateObjectImpl(DEFAULT_SERIALIZATION_TAG).get().get(); } // 01
		void Delete(REX::Owner<IObject*> a_object) const override { DeleteObjectImpl(a_object); }									   // 02
		[[nodiscard]] const char* GetObjectName() const override { return OBJECT_NAME.data(); }										   // 03

		[[nodiscard]] auto GetObject(const value_type* a_object) const
			-> std::shared_ptr<value_type>
		{
			return GetObjectImpl(a_object);
		}

		[[nodiscard]] auto CreateObject() const
			-> REX::NotNull<std::shared_ptr<value_type>>
			requires(std::is_default_constructible_v<value_type>)
		{
			return CreateObjectImpl();
		}

		template <class... Args>
		[[nodiscard]] auto CreateObject(Args&&... a_args) const
			-> REX::NotNull<std::shared_ptr<value_type>>
			requires(std::is_constructible_v<value_type, Args...>)
		{
			return CreateObjectImpl(std::forward<Args>(a_args)...);
		}

		bool DeleteObject(REX::Owner<value_type*> a_object) const
		{
			return DeleteObjectImpl(a_object);
		}

	private:
		[[nodiscard]] auto GetObjectImpl(const IObject* a_object) const
			-> std::shared_ptr<value_type>
		{
			if (!a_object) {
				return nullptr;
			}

			const auto& objectData = Impl::SharedObjectFactoryData::GetSingleton();
			const auto objectLock = std::shared_lock(objectData->mutex);
			const auto& objectMap = objectData->objectMap;

			const auto objectIt = objectMap.find(a_object);
			if (objectIt == objectMap.end()) {
				return nullptr;
			}

			return std::static_pointer_cast<value_type>(objectIt->second.get());
		}

		[[nodiscard]] auto CreateObjectImpl() const
			-> REX::NotNull<std::shared_ptr<value_type>>
			requires(std::is_default_constructible_v<value_type>)
		{
			const auto& objectData = Impl::SharedObjectFactoryData::GetSingleton();
			const auto objectLock = std::scoped_lock(objectData->mutex);
			auto& objectMap = objectData->objectMap;

			auto object = std::make_shared<value_type>();
			objectMap.emplace(object.get(), object);
			return object;
		}

		template <class... Args>
		[[nodiscard]] auto CreateObjectImpl(Args&&... a_args) const
			-> REX::NotNull<std::shared_ptr<value_type>>
			requires(std::is_constructible_v<value_type, Args...>)
		{
			const auto& objectData = Impl::SharedObjectFactoryData::GetSingleton();
			const auto objectLock = std::scoped_lock(objectData->mutex);
			auto& objectMap = objectData->objectMap;

			auto object = std::make_shared<value_type>(std::forward<Args>(a_args)...);
			objectMap.emplace(object.get(), object);
			return object;
		}

		bool DeleteObjectImpl(REX::Owner<IObject*> a_object) const
		{
			if (!a_object) {
				return false;
			}

			const auto& objectData = Impl::SharedObjectFactoryData::GetSingleton();
			const auto objectLock = std::scoped_lock(objectData->mutex);
			auto& objectMap = objectData->objectMap;

			const auto objectIt = objectMap.find(a_object);
			if (objectIt == objectMap.end()) {
				return false;
			}

			objectMap.erase(objectIt);
			return true;
		}
	};
}
