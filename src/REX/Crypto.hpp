#pragma once

#include "REX/Error.hpp"
#include "REX/W32/CORE.hpp"
#include "REX/ZString.hpp"

namespace REX::W32
{
	using BCRYPT_ALG_HANDLE = HANDLE_WRAPPER<void*>;
}

namespace REX
{
	[[nodiscard]]
	auto HashCrypto(std::span<const std::byte> a_data, REX::ZWStringView a_algorithmName) noexcept
		-> std::expected<std::vector<std::byte>, REX::SystemError>;
	[[nodiscard]]
	auto HashCrypto(std::span<const std::byte> a_data, REX::W32::BCRYPT_ALG_HANDLE a_algorithmHandle) noexcept
		-> std::expected<std::vector<std::byte>, REX::SystemError>;

	[[nodiscard]]
	auto HashCrypto(std::string_view a_data, REX::ZWStringView a_algorithmName) noexcept
		-> std::expected<std::string, REX::SystemError>;
	[[nodiscard]]
	auto HashCrypto(std::string_view a_data, REX::W32::BCRYPT_ALG_HANDLE a_algorithmHandle) noexcept
		-> std::expected<std::string, REX::SystemError>;

	[[nodiscard]]
	auto HashMd5(std::span<const std::byte> a_data) noexcept -> std::expected<std::vector<std::byte>, REX::SystemError>;
	[[nodiscard]]
	auto HashSha1(std::span<const std::byte> a_data) noexcept
		-> std::expected<std::vector<std::byte>, REX::SystemError>;
	[[nodiscard]]
	auto HashSha256(std::span<const std::byte> a_data) noexcept
		-> std::expected<std::vector<std::byte>, REX::SystemError>;
	[[nodiscard]]
	auto HashSha384(std::span<const std::byte> a_data) noexcept
		-> std::expected<std::vector<std::byte>, REX::SystemError>;
	[[nodiscard]]
	auto HashSha512(std::span<const std::byte> a_data) noexcept
		-> std::expected<std::vector<std::byte>, REX::SystemError>;

	[[nodiscard]]
	auto HashMd5(std::string_view a_data) noexcept -> std::expected<std::string, REX::SystemError>;
	[[nodiscard]]
	auto HashSha1(std::string_view a_data) noexcept -> std::expected<std::string, REX::SystemError>;
	[[nodiscard]]
	auto HashSha256(std::string_view a_data) noexcept -> std::expected<std::string, REX::SystemError>;
	[[nodiscard]]
	auto HashSha384(std::string_view a_data) noexcept -> std::expected<std::string, REX::SystemError>;
	[[nodiscard]]
	auto HashSha512(std::string_view a_data) noexcept -> std::expected<std::string, REX::SystemError>;
}
