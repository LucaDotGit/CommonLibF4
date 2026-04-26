#pragma once

#include "RE/M/MemoryManager.hpp"

namespace RE
{
	template <class T>
	class BSTSingletonImplicit
	{
	public:
		using value_type = T;

		BSTSingletonImplicit() = default;
		~BSTSingletonImplicit() = default;

		BSTSingletonImplicit(BSTSingletonImplicit&) = delete;
		BSTSingletonImplicit(BSTSingletonImplicit&&) = delete;

		BSTSingletonImplicit& operator=(BSTSingletonImplicit&) = delete;
		BSTSingletonImplicit& operator=(BSTSingletonImplicit&&) = delete;

		GAME_HEAP_REDEFINE_NEW(BSTSingletonImplicit);
	};
	static_assert(std::is_empty_v<BSTSingletonImplicit<std::any>>);

	template <class T>
	class BSTSingletonExplicit
	{
	public:
		using value_type = T;

		BSTSingletonExplicit() = default;
		~BSTSingletonExplicit() = default;

		BSTSingletonExplicit(BSTSingletonExplicit&) = delete;
		BSTSingletonExplicit(BSTSingletonExplicit&&) = delete;

		BSTSingletonExplicit& operator=(BSTSingletonExplicit&) = delete;
		BSTSingletonExplicit& operator=(BSTSingletonExplicit&&) = delete;

		GAME_HEAP_REDEFINE_NEW(BSTSingletonExplicit);
	};
	static_assert(std::is_empty_v<BSTSingletonExplicit<std::any>>);

	template <class T, class Buffer>
	class BSTSDMTraits
	{
	public:
		using value_type = T;
		using buffer_type = Buffer;

		BSTSDMTraits() = default;
		~BSTSDMTraits() = default;

		BSTSDMTraits(const BSTSDMTraits&) = delete;
		BSTSDMTraits(BSTSDMTraits&&) = delete;

		BSTSDMTraits& operator=(const BSTSDMTraits&) = delete;
		BSTSDMTraits& operator=(BSTSDMTraits&&) = delete;
	};
	static_assert(std::is_empty_v<BSTSDMTraits<std::any, std::any>>);

	template <class T>
	class BSTSingletonSDMOpStaticBuffer
	{
	public:
		using value_type = T;

		BSTSingletonSDMOpStaticBuffer() = default;
		~BSTSingletonSDMOpStaticBuffer() = default;

		BSTSingletonSDMOpStaticBuffer(BSTSingletonSDMOpStaticBuffer&) = delete;
		BSTSingletonSDMOpStaticBuffer(BSTSingletonSDMOpStaticBuffer&&) = delete;

		BSTSingletonSDMOpStaticBuffer& operator=(BSTSingletonSDMOpStaticBuffer&) = delete;
		BSTSingletonSDMOpStaticBuffer& operator=(BSTSingletonSDMOpStaticBuffer&&) = delete;
	};
	static_assert(std::is_empty_v<BSTSingletonSDMOpStaticBuffer<std::any>>);

	template <class Traits>
	class BSTSingletonSDMBase
		: public Traits,
		  public BSTSingletonSDMOpStaticBuffer<typename Traits::value_type>
	{
	public:
		using value_type = Traits::value_type;
		using traits_type = Traits;

		BSTSingletonSDMBase() = default;
		~BSTSingletonSDMBase() = default;

		BSTSingletonSDMBase(BSTSingletonSDMBase&) = delete;
		BSTSingletonSDMBase(BSTSingletonSDMBase&&) = delete;

		BSTSingletonSDMBase& operator=(BSTSingletonSDMBase&) = delete;
		BSTSingletonSDMBase& operator=(BSTSingletonSDMBase&&) = delete;

		GAME_HEAP_REDEFINE_NEW(BSTSingletonSDMBase);
	};
	static_assert(std::is_empty_v<BSTSingletonSDMBase<BSTSDMTraits<std::any, std::any>>>);

#if __EDG__ != 0
	template <class T, template <class> class Buffer = BSTSingletonSDMOpStaticBuffer>
	class BSTSingletonSDM
	{
	public:
		using value_type = T;
		using buffer_type = Buffer<T>;
		using traits_type = BSTSDMTraits<T, Buffer<T>>;

		BSTSingletonSDM() = default;
		~BSTSingletonSDM() = default;

		BSTSingletonSDM(BSTSingletonSDM&) = delete;
		BSTSingletonSDM(BSTSingletonSDM&&) = delete;

		BSTSingletonSDM& operator=(BSTSingletonSDM&) = delete;
		BSTSingletonSDM& operator=(BSTSingletonSDM&&) = delete;

		GAME_HEAP_REDEFINE_NEW(BSTSingletonSDM);

	protected:
		// members
		std::uint8_t pad00; // 00
	};
	static_assert(sizeof(BSTSingletonSDM<std::any, BSTSingletonSDMOpStaticBuffer>) == 0x01);
#else
	template <class T, template <class> class Buffer = BSTSingletonSDMOpStaticBuffer>
	class BSTSingletonSDM
		: public BSTSingletonSDMBase<BSTSDMTraits<T, Buffer<T>>>
	{
	public:
		using value_type = T;
		using buffer_type = Buffer<T>;
		using traits_type = BSTSDMTraits<T, Buffer<T>>;

		BSTSingletonSDM() = default;
		~BSTSingletonSDM() = default;

		BSTSingletonSDM(BSTSingletonSDM&) = delete;
		BSTSingletonSDM(BSTSingletonSDM&&) = delete;

		BSTSingletonSDM& operator=(BSTSingletonSDM&) = delete;
		BSTSingletonSDM& operator=(BSTSingletonSDM&&) = delete;
	};
	static_assert(std::is_empty_v<BSTSingletonSDM<std::any, BSTSingletonSDMOpStaticBuffer>>);
#endif
}
