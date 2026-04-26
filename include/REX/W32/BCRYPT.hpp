#pragma once

#include "REX/W32/CORE.hpp"

namespace REX::W32
{
	using BCRYPT_HANDLE = HANDLE_WRAPPER<void*>;
	using BCRYPT_ALG_HANDLE = HANDLE_WRAPPER<void*>;
	using BCRYPT_KEY_HANDLE = HANDLE_WRAPPER<void*>;
	using BCRYPT_HASH_HANDLE = HANDLE_WRAPPER<void*>;
	using BCRYPT_SECRET_HANDLE = HANDLE_WRAPPER<void*>;

	inline constexpr auto BCRYPT_MD2_ALG_HANDLE{ static_cast<BCRYPT_ALG_HANDLE>(0x00000001) };
	inline constexpr auto BCRYPT_MD4_ALG_HANDLE{ static_cast<BCRYPT_ALG_HANDLE>(0x00000011) };
	inline constexpr auto BCRYPT_MD5_ALG_HANDLE{ static_cast<BCRYPT_ALG_HANDLE>(0x00000021) };
	inline constexpr auto BCRYPT_HMAC_MD2_ALG_HANDLE{ static_cast<BCRYPT_ALG_HANDLE>(0x00000121) };
	inline constexpr auto BCRYPT_HMAC_MD4_ALG_HANDLE{ static_cast<BCRYPT_ALG_HANDLE>(0x00000131) };
	inline constexpr auto BCRYPT_HMAC_MD5_ALG_HANDLE{ static_cast<BCRYPT_ALG_HANDLE>(0x00000091) };
	inline constexpr auto BCRYPT_SHA1_ALG_HANDLE{ static_cast<BCRYPT_ALG_HANDLE>(0x00000031) };
	inline constexpr auto BCRYPT_SHA256_ALG_HANDLE{ static_cast<BCRYPT_ALG_HANDLE>(0x00000041) };
	inline constexpr auto BCRYPT_SHA384_ALG_HANDLE{ static_cast<BCRYPT_ALG_HANDLE>(0x00000051) };
	inline constexpr auto BCRYPT_SHA512_ALG_HANDLE{ static_cast<BCRYPT_ALG_HANDLE>(0x00000061) };
	inline constexpr auto BCRYPT_HMAC_SHA1_ALG_HANDLE{ static_cast<BCRYPT_ALG_HANDLE>(0x000000A1) };
	inline constexpr auto BCRYPT_HMAC_SHA256_ALG_HANDLE{ static_cast<BCRYPT_ALG_HANDLE>(0x000000B1) };
	inline constexpr auto BCRYPT_HMAC_SHA384_ALG_HANDLE{ static_cast<BCRYPT_ALG_HANDLE>(0x000000C1) };
	inline constexpr auto BCRYPT_HMAC_SHA512_ALG_HANDLE{ static_cast<BCRYPT_ALG_HANDLE>(0x000000D1) };
	inline constexpr auto BCRYPT_SHA3_256_ALG_HANDLE{ static_cast<BCRYPT_ALG_HANDLE>(0x000003B1) };
	inline constexpr auto BCRYPT_SHA3_384_ALG_HANDLE{ static_cast<BCRYPT_ALG_HANDLE>(0x000003C1) };
	inline constexpr auto BCRYPT_SHA3_512_ALG_HANDLE{ static_cast<BCRYPT_ALG_HANDLE>(0x000003D1) };
	inline constexpr auto BCRYPT_HMAC_SHA3_256_ALG_HANDLE{ static_cast<BCRYPT_ALG_HANDLE>(0x000003E1) };
	inline constexpr auto BCRYPT_HMAC_SHA3_384_ALG_HANDLE{ static_cast<BCRYPT_ALG_HANDLE>(0x000003F1) };
	inline constexpr auto BCRYPT_HMAC_SHA3_512_ALG_HANDLE{ static_cast<BCRYPT_ALG_HANDLE>(0x00000401) };
	inline constexpr auto BCRYPT_CSHAKE128_ALG_HANDLE{ static_cast<BCRYPT_ALG_HANDLE>(0x00000411) };
	inline constexpr auto BCRYPT_CSHAKE256_ALG_HANDLE{ static_cast<BCRYPT_ALG_HANDLE>(0x00000421) };
	inline constexpr auto BCRYPT_KMAC128_ALG_HANDLE{ static_cast<BCRYPT_ALG_HANDLE>(0x00000431) };
	inline constexpr auto BCRYPT_KMAC256_ALG_HANDLE{ static_cast<BCRYPT_ALG_HANDLE>(0x00000441) };

	inline constexpr auto BCRYPT_DH_ALG_HANDLE{ static_cast<BCRYPT_ALG_HANDLE>(0x00000281) };
	inline constexpr auto BCRYPT_DSA_ALG_HANDLE{ static_cast<BCRYPT_ALG_HANDLE>(0x000002D1) };
	inline constexpr auto BCRYPT_ECDH_ALG_HANDLE{ static_cast<BCRYPT_ALG_HANDLE>(0x00000291) };
	inline constexpr auto BCRYPT_ECDH_P256_ALG_HANDLE{ static_cast<BCRYPT_ALG_HANDLE>(0x000002A1) };
	inline constexpr auto BCRYPT_ECDH_P384_ALG_HANDLE{ static_cast<BCRYPT_ALG_HANDLE>(0x000002B1) };
	inline constexpr auto BCRYPT_ECDH_P521_ALG_HANDLE{ static_cast<BCRYPT_ALG_HANDLE>(0x000002C1) };
	inline constexpr auto BCRYPT_ECDSA_ALG_HANDLE{ static_cast<BCRYPT_ALG_HANDLE>(0x000000F1) };
	inline constexpr auto BCRYPT_ECDSA_P256_ALG_HANDLE{ static_cast<BCRYPT_ALG_HANDLE>(0x000002E1) };
	inline constexpr auto BCRYPT_ECDSA_P384_ALG_HANDLE{ static_cast<BCRYPT_ALG_HANDLE>(0x000002F1) };
	inline constexpr auto BCRYPT_ECDSA_P521_ALG_HANDLE{ static_cast<BCRYPT_ALG_HANDLE>(0x00000301) };
	inline constexpr auto BCRYPT_RSA_ALG_HANDLE{ static_cast<BCRYPT_ALG_HANDLE>(0x000000E1) };
	inline constexpr auto BCRYPT_RSA_SIGN_ALG_HANDLE{ static_cast<BCRYPT_ALG_HANDLE>(0x00000311) };

	inline constexpr auto BCRYPT_MD2_ALGORITHM{ L"MD2"sv };
	inline constexpr auto BCRYPT_MD4_ALGORITHM{ L"MD4"sv };
	inline constexpr auto BCRYPT_MD5_ALGORITHM{ L"MD5"sv };
	inline constexpr auto BCRYPT_HMAC_MD2_ALGORITHM{ L"HMAC-MD2"sv };
	inline constexpr auto BCRYPT_HMAC_MD4_ALGORITHM{ L"HMAC-MD4"sv };
	inline constexpr auto BCRYPT_HMAC_MD5_ALGORITHM{ L"HMAC-MD5"sv };
	inline constexpr auto BCRYPT_SHA1_ALGORITHM{ L"SHA1"sv };
	inline constexpr auto BCRYPT_SHA256_ALGORITHM{ L"SHA256"sv };
	inline constexpr auto BCRYPT_SHA384_ALGORITHM{ L"SHA384"sv };
	inline constexpr auto BCRYPT_SHA512_ALGORITHM{ L"SHA512"sv };
	inline constexpr auto BCRYPT_HMAC_SHA1_ALGORITHM{ L"HMAC-SHA1"sv };
	inline constexpr auto BCRYPT_HMAC_SHA256_ALGORITHM{ L"HMAC-SHA256"sv };
	inline constexpr auto BCRYPT_HMAC_SHA384_ALGORITHM{ L"HMAC-SHA384"sv };
	inline constexpr auto BCRYPT_HMAC_SHA512_ALGORITHM{ L"HMAC-SHA512"sv };
	inline constexpr auto BCRYPT_SHA3_256_ALGORITHM{ L"SHA3-256"sv };
	inline constexpr auto BCRYPT_SHA3_384_ALGORITHM{ L"SHA3-384"sv };
	inline constexpr auto BCRYPT_SHA3_512_ALGORITHM{ L"SHA3-512"sv };
	inline constexpr auto BCRYPT_HMAC_SHA3_256_ALGORITHM{ L"HMAC-SHA3-256"sv };
	inline constexpr auto BCRYPT_HMAC_SHA3_384_ALGORITHM{ L"HMAC-SHA3-384"sv };
	inline constexpr auto BCRYPT_HMAC_SHA3_512_ALGORITHM{ L"HMAC-SHA3-512"sv };
	inline constexpr auto BCRYPT_CSHAKE128_ALGORITHM{ L"CSHAKE128"sv };
	inline constexpr auto BCRYPT_CSHAKE256_ALGORITHM{ L"CSHAKE256"sv };
	inline constexpr auto BCRYPT_KMAC128_ALGORITHM{ L"KMAC128"sv };
	inline constexpr auto BCRYPT_KMAC256_ALGORITHM{ L"KMAC256"sv };

	inline constexpr auto BCRYPT_DH_ALGORITHM{ L"DH"sv };
	inline constexpr auto BCRYPT_DSA_ALGORITHM{ L"DSA"sv };
	inline constexpr auto BCRYPT_ECDH_ALGORITHM{ L"ECDH"sv };
	inline constexpr auto BCRYPT_ECDH_P256_ALGORITHM{ L"ECDH_P256"sv };
	inline constexpr auto BCRYPT_ECDH_P384_ALGORITHM{ L"ECDH_P384"sv };
	inline constexpr auto BCRYPT_ECDH_P521_ALGORITHM{ L"ECDH_P521"sv };
	inline constexpr auto BCRYPT_ECDSA_ALGORITHM{ L"ECDSA"sv };
	inline constexpr auto BCRYPT_ECDSA_P256_ALGORITHM{ L"ECDSA_P256"sv };
	inline constexpr auto BCRYPT_ECDSA_P384_ALGORITHM{ L"ECDSA_P384"sv };
	inline constexpr auto BCRYPT_ECDSA_P521_ALGORITHM{ L"ECDSA_P521"sv };
	inline constexpr auto BCRYPT_RSA_ALGORITHM{ L"RSA"sv };
	inline constexpr auto BCRYPT_RSA_SIGN_ALGORITHM{ L"RSA_SIGN"sv };

	inline constexpr auto BCRYPT_OBJECT_LENGTH{ L"ObjectLength"sv };
	inline constexpr auto BCRYPT_ALGORITHM_NAME{ L"AlgorithmName"sv };
	inline constexpr auto BCRYPT_PROVIDER_HANDLE{ L"ProviderHandle"sv };
	inline constexpr auto BCRYPT_CHAINING_MODE{ L"ChainingMode"sv };
	inline constexpr auto BCRYPT_BLOCK_LENGTH{ L"BlockLength"sv };
	inline constexpr auto BCRYPT_KEY_LENGTH{ L"KeyLength"sv };
	inline constexpr auto BCRYPT_KEY_OBJECT_LENGTH{ L"KeyObjectLength"sv };
	inline constexpr auto BCRYPT_KEY_STRENGTH{ L"KeyStrength"sv };
	inline constexpr auto BCRYPT_KEY_LENGTHS{ L"KeyLengths"sv };
	inline constexpr auto BCRYPT_BLOCK_SIZE_LIST{ L"BlockSizeList"sv };
	inline constexpr auto BCRYPT_EFFECTIVE_KEY_LENGTH{ L"EffectiveKeyLength"sv };
	inline constexpr auto BCRYPT_HASH_LENGTH{ L"HashDigestLength"sv };
	inline constexpr auto BCRYPT_HASH_OID_LIST{ L"HashOIDList"sv };
	inline constexpr auto BCRYPT_PADDING_SCHEMES{ L"PaddingSchemes"sv };
	inline constexpr auto BCRYPT_SIGNATURE_LENGTH{ L"SignatureLength"sv };
	inline constexpr auto BCRYPT_HASH_BLOCK_LENGTH{ L"HashBlockLength"sv };
	inline constexpr auto BCRYPT_AUTH_TAG_LENGTH{ L"AuthTagLength"sv };
}

namespace REX::W32
{
	NTSTATUS BCryptOpenAlgorithmProvider(BCRYPT_ALG_HANDLE* a_algorithm, const wchar_t* a_id, const wchar_t* a_impl = nullptr, std::uint32_t a_flags = 0) noexcept;
	NTSTATUS BCryptCloseAlgorithmProvider(BCRYPT_ALG_HANDLE a_algorithm, std::uint32_t a_flags = 0) noexcept;
	NTSTATUS BCryptCreateHash(BCRYPT_ALG_HANDLE a_algorithm, BCRYPT_HASH_HANDLE* a_hash, std::uint8_t* a_hashObject = nullptr, std::uint32_t a_hashObjectSize = 0, std::uint8_t* a_secret = nullptr, std::uint32_t a_secretSize = 0, std::uint32_t a_flags = 0) noexcept;
	NTSTATUS BCryptDestroyHash(BCRYPT_HASH_HANDLE a_hash) noexcept;
	NTSTATUS BCryptFinishHash(BCRYPT_HASH_HANDLE a_hash, std::uint8_t* a_output, std::uint32_t a_outputSize, std::uint32_t a_flags = 0) noexcept;
	NTSTATUS BCryptGetProperty(BCRYPT_HANDLE a_object, const wchar_t* a_property, std::uint8_t* a_output, std::uint32_t a_outputSize, std::uint32_t* a_result, std::uint32_t a_flags = 0) noexcept;
	NTSTATUS BCryptHashData(BCRYPT_HASH_HANDLE a_hash, std::uint8_t* a_input, std::uint32_t a_inputSize, std::uint32_t a_flags = 0) noexcept;
}
