#include "REX/Crypto.hpp"

#include "REX/Contract.hpp"
#include "REX/Format.hpp"
#include "REX/ScopeExit.hpp"

namespace REX
{
	auto HashCrypto(std::span<const std::byte> a_data, REX::zwstring_view a_algorithm) noexcept
		-> std::expected<std::vector<std::byte>, REX::SystemError>
	{
		auto algorithmHandle = REX::W32::BCRYPT_ALG_HANDLE();
		if (!REX::W32::NT_SUCCESS(REX::W32::BCryptOpenAlgorithmProvider(std::addressof(algorithmHandle), a_algorithm.data()))) {
			return std::unexpected(REX::GetCurrentSystemError());
		}

		const auto cleanupAlgo = ScopeExit([algorithmHandle]() -> void {
			if (!REX::W32::NT_SUCCESS(REX::W32::BCryptCloseAlgorithmProvider(algorithmHandle))) [[unlikely]] {
				REX::Assert(false);
			}
		});

		return HashCrypto(a_data, algorithmHandle);
	}

	auto HashCrypto(std::span<const std::byte> a_data, REX::W32::BCRYPT_ALG_HANDLE a_algorithmHandle) noexcept
		-> std::expected<std::vector<std::byte>, REX::SystemError>
	{
		auto hashHandle = REX::W32::BCRYPT_HASH_HANDLE();
		if (!REX::W32::NT_SUCCESS(REX::W32::BCryptCreateHash(a_algorithmHandle, std::addressof(hashHandle)))) {
			return std::unexpected(REX::GetCurrentSystemError());
		}

		const auto cleanupHash = ScopeExit([hashHandle]() -> void {
			if (!REX::W32::NT_SUCCESS(REX::W32::BCryptDestroyHash(hashHandle))) [[unlikely]] {
				REX::Assert(false);
			}
		});

		if (!REX::W32::NT_SUCCESS(REX::W32::BCryptHashData(
				hashHandle, reinterpret_cast<std::uint8_t*>(const_cast<std::byte*>(a_data.data())), static_cast<std::uint32_t>(a_data.size())))) {
			return std::unexpected(REX::GetCurrentSystemError());
		}

		auto bufferSize = 0ui32;

		{
			auto tempOutput = 0ui32;

			if (!REX::W32::NT_SUCCESS(REX::W32::BCryptGetProperty(
					hashHandle, REX::W32::BCRYPT_HASH_LENGTH.data(), reinterpret_cast<std::uint8_t*>(std::addressof(bufferSize)), sizeof(bufferSize), std::addressof(tempOutput)))) {
				return std::unexpected(REX::GetCurrentSystemError());
			}
		}

		auto buffer = std::vector<std::byte>();

		try {
			buffer.resize(bufferSize);
		}
		catch ([[maybe_unused]] const std::bad_alloc& error) {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::not_enough_memory));
		}

		if (!REX::W32::NT_SUCCESS(REX::W32::BCryptFinishHash(hashHandle, reinterpret_cast<std::uint8_t*>(buffer.data()), static_cast<std::uint32_t>(buffer.size())))) {
			return std::unexpected(REX::GetCurrentSystemError());
		}

		return std::move(buffer);
	}

	auto HashCrypto(std::string_view a_data, REX::zwstring_view a_algorithm) noexcept
		-> std::expected<std::string, REX::SystemError>
	{
		auto algorithmHandle = REX::W32::BCRYPT_ALG_HANDLE();
		if (!REX::W32::NT_SUCCESS(REX::W32::BCryptOpenAlgorithmProvider(std::addressof(algorithmHandle), a_algorithm.data()))) {
			return std::unexpected(REX::GetCurrentSystemError());
		}

		const auto cleanupAlgo = ScopeExit([algorithmHandle]() -> void {
			if (!REX::W32::NT_SUCCESS(REX::W32::BCryptCloseAlgorithmProvider(algorithmHandle))) [[unlikely]] {
				REX::Assert(false);
			}
		});

		return HashCrypto(a_data, algorithmHandle);
	}

	auto HashCrypto(std::string_view a_data, REX::W32::BCRYPT_ALG_HANDLE a_algorithmHandle) noexcept
		-> std::expected<std::string, REX::SystemError>
	{
		auto hashHandle = REX::W32::BCRYPT_HASH_HANDLE();
		if (!REX::W32::NT_SUCCESS(REX::W32::BCryptCreateHash(a_algorithmHandle, std::addressof(hashHandle)))) {
			return std::unexpected(REX::GetCurrentSystemError());
		}

		const auto cleanupHash = ScopeExit([hashHandle]() -> void {
			if (!REX::W32::NT_SUCCESS(REX::W32::BCryptDestroyHash(hashHandle))) [[unlikely]] {
				REX::Assert(false);
			}
		});

		if (!REX::W32::NT_SUCCESS(REX::W32::BCryptHashData(
				hashHandle, reinterpret_cast<std::uint8_t*>(const_cast<char*>(a_data.data())), static_cast<std::uint32_t>(a_data.size())))) {
			return std::unexpected(REX::GetCurrentSystemError());
		}

		auto bufferSize = 0ui32;

		{
			auto tempOutput = 0ui32;

			if (!REX::W32::NT_SUCCESS(REX::W32::BCryptGetProperty(
					hashHandle, REX::W32::BCRYPT_HASH_LENGTH.data(), reinterpret_cast<std::uint8_t*>(std::addressof(bufferSize)), sizeof(bufferSize), std::addressof(tempOutput)))) {
				return std::unexpected(REX::GetCurrentSystemError());
			}
		}

		auto buffer = std::vector<std::uint8_t>();

		try {
			buffer.resize(bufferSize);
		}
		catch ([[maybe_unused]] const std::bad_alloc& error) {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::not_enough_memory));
		}

		if (!REX::W32::NT_SUCCESS(REX::W32::BCryptFinishHash(hashHandle, buffer.data(), static_cast<std::uint32_t>(buffer.size())))) {
			return std::unexpected(REX::GetCurrentSystemError());
		}

		try {
			auto result = std::string();
			result.reserve(buffer.size() * 2);

			for (const auto byte : buffer) {
				result += REX::Format("{:02X}"sv, byte);
			}

			return std::move(result);
		}
		catch ([[maybe_unused]] const std::bad_alloc& error) {
			return std::unexpected(REX::CreateSystemError(REX::PosixErrorCode::not_enough_memory));
		}
	}

	auto HashMd5(std::span<const std::byte> a_data) noexcept
		-> std::expected<std::vector<std::byte>, REX::SystemError>
	{
		return HashCrypto(a_data, REX::W32::BCRYPT_MD5_ALG_HANDLE);
	}

	auto HashSha1(std::span<const std::byte> a_data) noexcept
		-> std::expected<std::vector<std::byte>, REX::SystemError>
	{
		return HashCrypto(a_data, REX::W32::BCRYPT_SHA1_ALG_HANDLE);
	}

	auto HashSha256(std::span<const std::byte> a_data) noexcept
		-> std::expected<std::vector<std::byte>, REX::SystemError>
	{
		return HashCrypto(a_data, REX::W32::BCRYPT_SHA256_ALG_HANDLE);
	}

	auto HashSha384(std::span<const std::byte> a_data) noexcept
		-> std::expected<std::vector<std::byte>, REX::SystemError>
	{
		return HashCrypto(a_data, REX::W32::BCRYPT_SHA384_ALG_HANDLE);
	}

	auto HashSha512(std::span<const std::byte> a_data) noexcept
		-> std::expected<std::vector<std::byte>, REX::SystemError>
	{
		return HashCrypto(a_data, REX::W32::BCRYPT_SHA512_ALG_HANDLE);
	}

	auto HashMd5(std::string_view a_data) noexcept
		-> std::expected<std::string, REX::SystemError>
	{
		return HashCrypto(a_data, REX::W32::BCRYPT_MD5_ALG_HANDLE);
	}

	auto HashSha1(std::string_view a_data) noexcept
		-> std::expected<std::string, REX::SystemError>
	{
		return HashCrypto(a_data, REX::W32::BCRYPT_SHA1_ALG_HANDLE);
	}

	auto HashSha256(std::string_view a_data) noexcept
		-> std::expected<std::string, REX::SystemError>
	{
		return HashCrypto(a_data, REX::W32::BCRYPT_SHA256_ALG_HANDLE);
	}

	auto HashSha384(std::string_view a_data) noexcept
		-> std::expected<std::string, REX::SystemError>
	{
		return HashCrypto(a_data, REX::W32::BCRYPT_SHA384_ALG_HANDLE);
	}

	auto HashSha512(std::string_view a_data) noexcept
		-> std::expected<std::string, REX::SystemError>
	{
		return HashCrypto(a_data, REX::W32::BCRYPT_SHA512_ALG_HANDLE);
	}
}
