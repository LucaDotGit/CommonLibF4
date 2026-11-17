#pragma once

#include "REX/W32/CORE.hpp"

namespace REX::W32
{
	using BCRYPT_HANDLE = HANDLE_WRAPPER<void*>;
	using BCRYPT_ALG_HANDLE = HANDLE_WRAPPER<void*>;
	using BCRYPT_KEY_HANDLE = HANDLE_WRAPPER<void*>;
	using BCRYPT_HASH_HANDLE = HANDLE_WRAPPER<void*>;
	using BCRYPT_SECRET_HANDLE = HANDLE_WRAPPER<void*>;

	enum BCRYPT_MULTI_OPERATION_TYPE : std::int32_t
	{
		BCRYPT_OPERATION_TYPE_HASH = 0x01
	};

	struct BCryptBufferDesc
	{
		std::uint32_t version;
		std::uint32_t count;
		void* buffers;
	};

	// Algorithm Pseudo-Handles

	inline constexpr auto BCRYPT_MD2_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0x01);
	inline constexpr auto BCRYPT_MD4_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0x11);
	inline constexpr auto BCRYPT_MD5_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0x21);
	inline constexpr auto BCRYPT_SHA1_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0x31);
	inline constexpr auto BCRYPT_SHA256_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0x41);
	inline constexpr auto BCRYPT_SHA384_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0x51);
	inline constexpr auto BCRYPT_SHA512_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0x61);
	inline constexpr auto BCRYPT_HMAC_SHA1_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0xA1);
	inline constexpr auto BCRYPT_HMAC_SHA256_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0xB1);
	inline constexpr auto BCRYPT_HMAC_SHA384_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0xC1);
	inline constexpr auto BCRYPT_HMAC_SHA512_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0xD1);
	inline constexpr auto BCRYPT_HMAC_MD2_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0x121);
	inline constexpr auto BCRYPT_HMAC_MD4_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0x131);
	inline constexpr auto BCRYPT_HMAC_MD5_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0x91);
	inline constexpr auto BCRYPT_SHA3_256_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0x3B1);
	inline constexpr auto BCRYPT_SHA3_384_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0x3C1);
	inline constexpr auto BCRYPT_SHA3_512_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0x3D1);
	inline constexpr auto BCRYPT_HMAC_SHA3_256_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0x3E1);
	inline constexpr auto BCRYPT_HMAC_SHA3_384_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0x3F1);
	inline constexpr auto BCRYPT_HMAC_SHA3_512_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0x401);
	inline constexpr auto BCRYPT_CSHAKE128_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0x411);
	inline constexpr auto BCRYPT_CSHAKE256_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0x421);
	inline constexpr auto BCRYPT_KMAC128_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0x431);
	inline constexpr auto BCRYPT_KMAC256_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0x441);

	inline constexpr auto BCRYPT_RC4_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0x71);

	inline constexpr auto BCRYPT_RNG_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0x81);

	inline constexpr auto BCRYPT_CAPI_KDF_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0x321);
	inline constexpr auto BCRYPT_PBKDF2_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0x331);
	inline constexpr auto BCRYPT_SP800108_CTR_HMAC_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0x341);
	inline constexpr auto BCRYPT_SP80056A_CONCAT_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0x351);
	inline constexpr auto BCRYPT_HKDF_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0x391);

	inline constexpr auto BCRYPT_DH_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0x281);
	inline constexpr auto BCRYPT_DSA_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0x2D1);
	inline constexpr auto BCRYPT_ECDH_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0x291);
	inline constexpr auto BCRYPT_ECDH_P256_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0x2A1);
	inline constexpr auto BCRYPT_ECDH_P384_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0x2B1);
	inline constexpr auto BCRYPT_ECDH_P521_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0x2C1);
	inline constexpr auto BCRYPT_ECDSA_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0xF1);
	inline constexpr auto BCRYPT_ECDSA_P256_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0x2E1);
	inline constexpr auto BCRYPT_ECDSA_P384_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0x2F1);
	inline constexpr auto BCRYPT_ECDSA_P521_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0x301);
	inline constexpr auto BCRYPT_RSA_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0xE1);
	inline constexpr auto BCRYPT_RSA_SIGN_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0x311);

	inline constexpr auto BCRYPT_AES_CMAC_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0x101);
	inline constexpr auto BCRYPT_AES_GMAC_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0x111);
	inline constexpr auto BCRYPT_3DES_CBC_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0x141);
	inline constexpr auto BCRYPT_3DES_ECB_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0x151);
	inline constexpr auto BCRYPT_3DES_CFB_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0x161);
	inline constexpr auto BCRYPT_3DES_112_CBC_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0x171);
	inline constexpr auto BCRYPT_3DES_112_ECB_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0x181);
	inline constexpr auto BCRYPT_3DES_112_CFB_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0x191);
	inline constexpr auto BCRYPT_AES_CBC_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0x1A1);
	inline constexpr auto BCRYPT_AES_ECB_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0x1B1);
	inline constexpr auto BCRYPT_AES_CFB_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0x1C1);
	inline constexpr auto BCRYPT_AES_CCM_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0x1D1);
	inline constexpr auto BCRYPT_AES_GCM_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0x1E1);
	inline constexpr auto BCRYPT_DES_CBC_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0x1F1);
	inline constexpr auto BCRYPT_DES_ECB_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0x201);
	inline constexpr auto BCRYPT_DES_CFB_ALG_HANDLE = static_cast<BCRYPT_ALG_HANDLE>(0x211);

	// Algorithm Identifiers

	inline constexpr auto BCRYPT_3DES_ALGORITHM = L"3DES"sv;
	inline constexpr auto BCRYPT_3DES_112_ALGORITHM = L"3DES_112"sv;
	inline constexpr auto BCRYPT_AES_ALGORITHM = L"AES"sv;
	inline constexpr auto BCRYPT_AES_CMAC_ALGORITHM = L"AES-CMAC"sv;
	inline constexpr auto BCRYPT_AES_GMAC_ALGORITHM = L"AES-GMAC"sv;
	inline constexpr auto BCRYPT_CAPI_KDF_ALGORITHM = L"CAPI_KDF"sv;
	inline constexpr auto BCRYPT_CHACHA20_POLY1305_ALGORITHM = L"CHACHA20_POLY1305"sv;
	inline constexpr auto BCRYPT_CSHAKE128_ALGORITHM = L"CSHAKE128"sv;
	inline constexpr auto BCRYPT_CSHAKE256_ALGORITHM = L"CSHAKE256"sv;
	inline constexpr auto BCRYPT_DES_ALGORITHM = L"DES"sv;
	inline constexpr auto BCRYPT_DESX_ALGORITHM = L"DESX"sv;
	inline constexpr auto BCRYPT_DH_ALGORITHM = L"DH"sv;
	inline constexpr auto BCRYPT_DSA_ALGORITHM = L"DSA"sv;
	inline constexpr auto BCRYPT_ECDH_ALGORITHM = L"ECDH"sv;
	inline constexpr auto BCRYPT_ECDSA_ALGORITHM = L"ECDSA"sv;
	inline constexpr auto BCRYPT_ECDH_P256_ALGORITHM = L"ECDH_P256"sv;
	inline constexpr auto BCRYPT_ECDH_P384_ALGORITHM = L"ECDH_P384"sv;
	inline constexpr auto BCRYPT_ECDH_P521_ALGORITHM = L"ECDH_P521"sv;
	inline constexpr auto BCRYPT_ECDSA_P256_ALGORITHM = L"ECDSA_P256"sv;
	inline constexpr auto BCRYPT_ECDSA_P384_ALGORITHM = L"ECDSA_P384"sv;
	inline constexpr auto BCRYPT_ECDSA_P521_ALGORITHM = L"ECDSA_P521"sv;
	inline constexpr auto BCRYPT_HKDF_ALGORITHM = L"HKDF"sv;
	inline constexpr auto BCRYPT_KMAC128_ALGORITHM = L"KMAC128"sv;
	inline constexpr auto BCRYPT_KMAC256_ALGORITHM = L"KMAC256"sv;
	inline constexpr auto BCRYPT_LMS_ALGORITHM = L"LMS"sv;
	inline constexpr auto BCRYPT_MD2_ALGORITHM = L"MD2"sv;
	inline constexpr auto BCRYPT_MD4_ALGORITHM = L"MD4"sv;
	inline constexpr auto BCRYPT_MD5_ALGORITHM = L"MD5"sv;
	inline constexpr auto BCRYPT_MLDSA_ALGORITHM = L"ML-DSA"sv;
	inline constexpr auto BCRYPT_MLKEM_ALGORITHM = L"ML-KEM"sv;
	inline constexpr auto BCRYPT_RC2_ALGORITHM = L"RC2"sv;
	inline constexpr auto BCRYPT_RC4_ALGORITHM = L"RC4"sv;
	inline constexpr auto BCRYPT_RNG_ALGORITHM = L"RNG"sv;
	inline constexpr auto BCRYPT_RNG_DUAL_EC_ALGORITHM = L"DUALECRNG"sv;
	inline constexpr auto BCRYPT_RNG_FIPS186_DSA_ALGORITHM = L"FIPS186DSARNG"sv;
	inline constexpr auto BCRYPT_RSA_ALGORITHM = L"RSA"sv;
	inline constexpr auto BCRYPT_RSA_SIGN_ALGORITHM = L"RSA_SIGN"sv;
	inline constexpr auto BCRYPT_SHA1_ALGORITHM = L"SHA1"sv;
	inline constexpr auto BCRYPT_SHA256_ALGORITHM = L"SHA256"sv;
	inline constexpr auto BCRYPT_SHA384_ALGORITHM = L"SHA384"sv;
	inline constexpr auto BCRYPT_SHA512_ALGORITHM = L"SHA512"sv;
	inline constexpr auto BCRYPT_SHA3_256_ALGORITHM = L"SHA3-256"sv;
	inline constexpr auto BCRYPT_SHA3_384_ALGORITHM = L"SHA3-384"sv;
	inline constexpr auto BCRYPT_SHA3_512_ALGORITHM = L"SHA3-512"sv;
	inline constexpr auto BCRYPT_SLHDSA_ALGORITHM = L"SLH-DSA"sv;
	inline constexpr auto BCRYPT_SP800108_CTR_HMAC_ALGORITHM = L"SP800_108_CTR_HMAC"sv;
	inline constexpr auto BCRYPT_SP80056A_CONCAT_ALGORITHM = L"SP800_56A_CONCAT"sv;
	inline constexpr auto BCRYPT_PBKDF2_ALGORITHM = L"PBKDF2"sv;
	inline constexpr auto BCRYPT_XMSS_ALGORITHM = L"XMSS"sv;
	inline constexpr auto BCRYPT_XTS_AES_ALGORITHM = L"XTS-AES"sv;

	// DPAPI Constants

	inline constexpr auto NCRYPT_DESCR_DELIMITER_AND = L" AND "sv;
	inline constexpr auto NCRYPT_DESCR_EQUAL = L"="sv;
	inline constexpr auto NCRYPT_DESCR_DELIMITER_OR = L" OR "sv;

	inline constexpr auto NCRYPT_KEY_PROTECTION_ALGORITHM_LOCAL = "LOCAL"sv;
	inline constexpr auto NCRYPT_KEY_PROTECTION_ALGORITHM_SDDL = "SDDL"sv;
	inline constexpr auto NCRYPT_KEY_PROTECTION_ALGORITHM_SID = "SID"sv;
	inline constexpr auto NCRYPT_KEY_PROTECTION_ALGORITHM_WEBCREDENTIALS = "WEBCREDENTIALS"sv;

	inline constexpr auto NCRYPT_KEY_PROTECTION_LOCAL_LOGON = "logon"sv;
	inline constexpr auto NCRYPT_KEY_PROTECTION_LOCAL_MACHINE = "machine"sv;
	inline constexpr auto NCRYPT_KEY_PROTECTION_LOCAL_USER = "user"sv;

	inline constexpr auto MS_KEY_PROTECTION_PROVIDER = "Microsoft Key Protection Provider"sv;
	inline constexpr auto WINDOWS_CLIENT_KEY_PROTECTION_PROVIDER = "Windows Client Key Protection Provider"sv;

	// Interface Identifiers

	inline constexpr auto BCRYPT_CIPHER_INTERFACE = static_cast<std::uint32_t>(0x01);
	inline constexpr auto BCRYPT_HASH_INTERFACE = static_cast<std::uint32_t>(0x02);
	inline constexpr auto BCRYPT_ASYMMETRIC_ENCRYPTION_INTERFACE = static_cast<std::uint32_t>(0x03);
	inline constexpr auto BCRYPT_SECRET_AGREEMENT_INTERFACE = static_cast<std::uint32_t>(0x04);
	inline constexpr auto BCRYPT_SIGNATURE_INTERFACE = static_cast<std::uint32_t>(0x05);
	inline constexpr auto BCRYPT_RNG_INTERFACE = static_cast<std::uint32_t>(0x06);
	inline constexpr auto BCRYPT_KEY_DERIVATION_INTERFACE = static_cast<std::uint32_t>(0x07);
	inline constexpr auto BCRYPT_KEY_ENCAPSULATION_INTERFACE = static_cast<std::uint32_t>(0x08);

	inline constexpr auto NCRYPT_KEY_STORAGE_INTERFACE = static_cast<std::uint32_t>(0x1'0001);
	inline constexpr auto NCRYPT_SCHANNEL_INTERFACE = static_cast<std::uint32_t>(0x1'0002);
	inline constexpr auto NCRYPT_SCHANNEL_SIGNATURE_INTERFACE = static_cast<std::uint32_t>(0x1'0003);

	// Primitive Property Identifiers

	inline constexpr auto BCRYPT_ALGORITHM_NAME = L"AlgorithmName"sv;
	inline constexpr auto BCRYPT_AUTH_TAG_LENGTH = L"AuthTagLength"sv;
	inline constexpr auto BCRYPT_BLOCK_LENGTH = L"BlockLength"sv;
	inline constexpr auto BCRYPT_BLOCK_SIZE_LIST = L"BlockSizeList"sv;
	inline constexpr auto BCRYPT_CHAINING_MODE = L"ChainingMode"sv;
	inline constexpr auto BCRYPT_DH_PARAMETERS = L"DHParameters"sv;
	inline constexpr auto BCRYPT_DSA_PARAMETERS = L"DSAParameters"sv;
	inline constexpr auto BCRYPT_EFFECTIVE_KEY_LENGTH = L"EffectiveKeyLength"sv;
	inline constexpr auto BCRYPT_HASH_BLOCK_LENGTH = L"HashBlockLength"sv;
	inline constexpr auto BCRYPT_HASH_LENGTH = L"HashDigestLength"sv;
	inline constexpr auto BCRYPT_HASH_OID_LIST = L"HashOIDList"sv;
	inline constexpr auto BCRYPT_INITIALIZATION_VECTOR = L"IV"sv;
	inline constexpr auto BCRYPT_KEM_SHARED_SECRET_LENGTH = L"KEMSharedSecretLength"sv;
	inline constexpr auto BCRYPT_KEM_CIPHERTEXT_LENGTH = L"KEMCiphertextLength"sv;
	inline constexpr auto BCRYPT_PUBLIC_KEY_LENGTH = L"PublicKeyLength"sv;
	inline constexpr auto BCRYPT_KEY_LENGTH = L"KeyLength"sv;
	inline constexpr auto BCRYPT_KEY_LENGTHS = L"KeyLengths"sv;
	inline constexpr auto BCRYPT_KEY_OBJECT_LENGTH = L"KeyObjectLength"sv;
	inline constexpr auto BCRYPT_KEY_STRENGTH = L"KeyStrength"sv;
	inline constexpr auto BCRYPT_MESSAGE_BLOCK_LENGTH = L"MessageBlockLength"sv;
	inline constexpr auto BCRYPT_MULTI_OBJECT_LENGTH = L"MultiObjectLength"sv;
	inline constexpr auto BCRYPT_OBJECT_LENGTH = L"ObjectLength"sv;
	inline constexpr auto BCRYPT_PADDING_SCHEMES = L"PaddingSchemes"sv;
	inline constexpr auto BCRYPT_PARAMETER_SET_NAME = L"ParameterSetName"sv;
	inline constexpr auto BCRYPT_PROVIDER_HANDLE = L"ProviderHandle"sv;
	inline constexpr auto BCRYPT_SIGNATURE_LENGTH = L"SignatureLength"sv;

	// Key Storage Property Identifiers

	inline constexpr auto NCRYPT_ALGORITHM_GROUP_PROPERTY = L"Algorithm Group"sv;

	inline constexpr auto NCRYPT_RSA_ALGORITHM_GROUP = L"RSA"sv;
	inline constexpr auto NCRYPT_DH_ALGORITHM_GROUP = L"DH"sv;
	inline constexpr auto NCRYPT_DSA_ALGORITHM_GROUP = L"DSA"sv;
	inline constexpr auto NCRYPT_ECDSA_ALGORITHM_GROUP = L"ECDSA"sv;
	inline constexpr auto NCRYPT_ECDH_ALGORITHM_GROUP = L"ECDH"sv;

	inline constexpr auto NCRYPT_ALGORITHM_PROPERTY = L"Algorithm Name"sv;
	inline constexpr auto NCRYPT_ASSOCIATED_ECDH_KEY = L"SmartCardAssociatedECDHKey"sv;
	inline constexpr auto NCRYPT_BLOCK_LENGTH_PROPERTY = L"Block Length"sv;
	inline constexpr auto NCRYPT_CERTIFICATE_PROPERTY = L"SmartCardKeyCertificate"sv;
	inline constexpr auto NCRYPT_DH_PARAMETERS_PROPERTY = L"DHParameters"sv;
	inline constexpr auto NCRYPT_EXPORT_POLICY_PROPERTY = L"Export Policy"sv;

	inline constexpr auto NCRYPT_IMPL_TYPE_PROPERTY = L"Impl Type"sv;

	inline constexpr auto NCRYPT_KEM_CIPHERTEXT_LENGTH_PROPERTY = L"KEM Ciphertext Length"sv;
	inline constexpr auto NCRYPT_KEM_SHARED_SECRET_LENGTH_PROPERTY = L"KEM Shared Secret Length"sv;

	inline constexpr auto NCRYPT_KEY_TYPE_PROPERTY = L"Key Type"sv;
	inline constexpr auto NCRYPT_KEY_USAGE_PROPERTY = L"Key Usage"sv;
	inline constexpr auto NCRYPT_LAST_MODIFIED_PROPERTY = L"Modified"sv;
	inline constexpr auto NCRYPT_LENGTH_PROPERTY = L"Length"sv;
	inline constexpr auto NCRYPT_LENGTHS_PROPERTY = L"Lengths"sv;
	inline constexpr auto NCRYPT_MAX_NAME_LENGTH_PROPERTY = L"_Max Name Length"sv;
	inline constexpr auto NCRYPT_NAME_PROPERTY = L"Name"sv;
	inline constexpr auto NCRYPT_PIN_PROMPT_PROPERTY = L"SmartCardPinPrompt"sv;
	inline constexpr auto NCRYPT_PIN_PROPERTY = L"SmartCardPin"sv;
	inline constexpr auto NCRYPT_PROVIDER_HANDLE_PROPERTY = L"Provider Handle"sv;
	inline constexpr auto NCRYPT_READER_PROPERTY = L"SmartCardReader"sv;
	inline constexpr auto NCRYPT_ROOT_CERTSTORE_PROPERTY = L"SmartcardRootCertStore"sv;
	inline constexpr auto NCRYPT_SCARD_PIN_ID = L"SmartCardPinId"sv;
	inline constexpr auto NCRYPT_SCARD_PIN_INFO = L"SmartCardPinInfo"sv;
	inline constexpr auto NCRYPT_SECURE_PIN_PROPERTY = L"SmartCardSecurePin"sv;
	inline constexpr auto NCRYPT_SECURITY_DESCR_PROPERTY = L"Security Descr"sv;
	inline constexpr auto NCRYPT_SECURITY_DESCR_SUPPORT_PROPERTY = L"Security Descr Support"sv;
	inline constexpr auto NCRYPT_SMARTCARD_GUID_PROPERTY = L"SmartCardGuid"sv;
	inline constexpr auto NCRYPT_UI_POLICY_PROPERTY = L"UI Policy"sv;
	inline constexpr auto NCRYPT_UNIQUE_NAME_PROPERTY = L"Unique Name"sv;
	inline constexpr auto NCRYPT_USE_CONTEXT_PROPERTY = L"Use Context"sv;
	inline constexpr auto NCRYPT_USE_COUNT_ENABLED_PROPERTY = L"Enabled Use Count"sv;
	inline constexpr auto NCRYPT_USE_COUNT_PROPERTY = L"Use Count"sv;
	inline constexpr auto NCRYPT_USER_CERTSTORE_PROPERTY = L"SmartCardUserCertStore"sv;
	inline constexpr auto NCRYPT_VBS_ROOT_PUB_PROPERTY = L"VBS_ROOT_PUB"sv;
	inline constexpr auto NCRYPT_VERSION_PROPERTY = L"Version"sv;
	inline constexpr auto NCRYPT_WINDOW_HANDLE_PROPERTY = L"HWND Handle"sv;

	inline constexpr auto NCRYPT_ALLOW_EXPORT_FLAG = static_cast<std::uint32_t>(0x01);
	inline constexpr auto NCRYPT_ALLOW_PLAINTEXT_EXPORT_FLAG = static_cast<std::uint32_t>(0x02);
	inline constexpr auto NCRYPT_ALLOW_ARCHIVING_FLAG = static_cast<std::uint32_t>(0x04);
	inline constexpr auto NCRYPT_ALLOW_PLAINTEXT_ARCHIVING_FLAG = static_cast<std::uint32_t>(0x08);

	inline constexpr auto NCRYPT_IMPL_HARDWARE_FLAG = static_cast<std::uint32_t>(0x01);
	inline constexpr auto NCRYPT_IMPL_SOFTWARE_FLAG = static_cast<std::uint32_t>(0x02);
	inline constexpr auto NCRYPT_IMPL_REMOVABLE_FLAG = static_cast<std::uint32_t>(0x08);
	inline constexpr auto NCRYPT_IMPL_HARDWARE_RNG_FLAG = static_cast<std::uint32_t>(0x10);
	inline constexpr auto NCRYPT_IMPL_VIRTUAL_ISOLATION_FLAG = static_cast<std::uint32_t>(0x20);

	inline constexpr auto NCRYPT_MACHINE_KEY_FLAG = static_cast<std::uint32_t>(0x20);

	inline constexpr auto NCRYPT_ALLOW_DECRYPT_FLAG = static_cast<std::uint32_t>(0x01);
	inline constexpr auto NCRYPT_ALLOW_SIGNING_FLAG = static_cast<std::uint32_t>(0x02);
	inline constexpr auto NCRYPT_ALLOW_KEY_AGREEMENT_FLAG = static_cast<std::uint32_t>(0x04);
	inline constexpr auto NCRYPT_ALLOW_KEY_ATTESTATION_FLAG = static_cast<std::uint32_t>(0x10);
	inline constexpr auto NCRYPT_ALLOW_ALL_USAGES = static_cast<std::uint32_t>(0xFF'FFFF);

	inline constexpr auto NCRYPT_MAX_PROPERTY_DATA = static_cast<std::uint32_t>(0x10'0000);
	inline constexpr auto NCRYPT_MAX_PROPERTY_NAME = static_cast<std::uint32_t>(64);
}

namespace REX::W32
{
	auto BCryptCloseAlgorithmProvider(BCRYPT_ALG_HANDLE a_algorithm, std::uint32_t a_flags = 0) noexcept -> NTSTATUS;
	auto BCryptCreateHash(
		BCRYPT_ALG_HANDLE a_algorithm,
		BCRYPT_HASH_HANDLE* a_hash,
		std::uint8_t* a_hashObject = nullptr,
		std::uint32_t a_hashObjectSize = 0,
		std::uint8_t* a_secret = nullptr,
		std::uint32_t a_secretSize = 0,
		std::uint32_t a_flags = 0) noexcept -> NTSTATUS;
	auto BCryptCreateMultiHash(
		BCRYPT_ALG_HANDLE a_algorithm,
		BCRYPT_HASH_HANDLE* a_hash,
		std::uint32_t a_hashes,
		std::uint8_t* a_hashObject,
		std::uint32_t a_hashObjectSize,
		std::uint8_t* a_secret = nullptr,
		std::uint32_t a_secretSize = 0,
		std::uint32_t a_flags = 0) noexcept -> NTSTATUS;
	auto BCryptDecapsulate(
		BCRYPT_KEY_HANDLE a_key,
		std::uint8_t* a_cipherText,
		std::uint32_t a_cipherTextSize,
		std::uint8_t* a_secretKey,
		std::uint32_t a_secretKeySize,
		std::uint32_t* a_secretKeyResult,
		std::uint32_t a_flags = 0) noexcept -> NTSTATUS;
	auto BCryptDecrypt(
		BCRYPT_KEY_HANDLE a_key,
		std::uint8_t* a_input,
		std::uint32_t a_inputSize,
		void* a_paddingInfo = nullptr,
		std::uint8_t* a_iv = nullptr,
		std::uint32_t a_ivSize = 0,
		std::uint8_t* a_output = nullptr,
		std::uint32_t a_outputSize = 0,
		std::uint32_t* a_result = nullptr,
		std::uint32_t a_flags = 0) noexcept -> NTSTATUS;
	auto BCryptDeriveKey(
		BCRYPT_SECRET_HANDLE a_secret,
		const wchar_t* a_kdf,
		BCryptBufferDesc* a_parameterList = nullptr,
		std::uint8_t* a_derivedKey = nullptr,
		std::uint32_t a_derivedKeySize = 0,
		std::uint32_t* a_result = nullptr,
		std::uint32_t a_flags = 0) noexcept -> NTSTATUS;
	auto BCryptDestroyHash(BCRYPT_HASH_HANDLE a_hash) noexcept -> NTSTATUS;
	auto BCryptDestroyKey(BCRYPT_KEY_HANDLE a_key) noexcept -> NTSTATUS;
	auto BCryptDestroySecret(BCRYPT_SECRET_HANDLE a_secret) noexcept -> NTSTATUS;
	auto BCryptDuplicateHash(
		BCRYPT_HASH_HANDLE a_hash,
		BCRYPT_HASH_HANDLE* a_newHash,
		std::uint8_t* a_hashObject = nullptr,
		std::uint32_t a_hashObjectSize = 0,
		std::uint32_t a_flags = 0) noexcept -> NTSTATUS;
	auto BCryptDuplicateKey(
		BCRYPT_KEY_HANDLE a_key,
		BCRYPT_KEY_HANDLE* a_newKey,
		std::uint8_t* a_keyObject = nullptr,
		std::uint32_t a_keyObjectSize = 0,
		std::uint32_t a_flags = 0) noexcept -> NTSTATUS;
	auto BCryptEncapsulate(
		BCRYPT_KEY_HANDLE a_key,
		std::uint8_t* a_secretKey,
		std::uint32_t a_secretKeySize,
		std::uint32_t* a_secretKeyResult,
		std::uint8_t* a_cipherText,
		std::uint32_t a_cipherTextSize,
		std::uint32_t* a_cipherTextResult,
		std::uint32_t a_flags = 0) noexcept -> NTSTATUS;
	auto BCryptEncrypt(
		BCRYPT_KEY_HANDLE a_key,
		std::uint8_t* a_input,
		std::uint32_t a_inputSize,
		void* a_paddingInfo = nullptr,
		std::uint8_t* a_iv = nullptr,
		std::uint32_t a_ivSize = 0,
		std::uint8_t* a_output = nullptr,
		std::uint32_t a_outputSize = 0,
		std::uint32_t* a_result = nullptr,
		std::uint32_t a_flags = 0) noexcept -> NTSTATUS;
	auto BCryptExportKey(
		BCRYPT_KEY_HANDLE a_key,
		BCRYPT_KEY_HANDLE a_exportKey,
		const wchar_t* a_blobType,
		BCryptBufferDesc* a_parameterList,
		std::uint8_t* a_output,
		std::uint32_t a_outputSize,
		std::uint32_t* a_result,
		std::uint32_t a_flags = 0) noexcept -> NTSTATUS;
	auto BCryptFinalizeKeyPair(BCRYPT_KEY_HANDLE a_key, std::uint32_t a_flags = 0) noexcept -> NTSTATUS;
	auto BCryptFinishHash(
		BCRYPT_HASH_HANDLE a_hash,
		std::uint8_t* a_output,
		std::uint32_t a_outputSize,
		std::uint32_t a_flags = 0) noexcept -> NTSTATUS;
	auto BCryptFreeBuffer(void* a_buffer) noexcept -> NTSTATUS;
	auto BCryptGenRandom(
		BCRYPT_ALG_HANDLE a_algorithm,
		std::uint8_t* a_buffer,
		std::uint32_t a_bufferSize,
		std::uint32_t a_flags = 0) noexcept -> NTSTATUS;
	auto BCryptGenerateKeyPair(
		BCRYPT_ALG_HANDLE a_algorithm,
		BCRYPT_KEY_HANDLE* a_key,
		std::uint32_t a_length,
		std::uint32_t a_flags = 0) noexcept -> NTSTATUS;
	auto BCryptGenerateSymmetricKey(
		BCRYPT_ALG_HANDLE a_algorithm,
		BCRYPT_KEY_HANDLE* a_key,
		std::uint8_t* a_keyObject = nullptr,
		std::uint32_t a_keyObjectSize = 0,
		std::uint8_t* a_secret = nullptr,
		std::uint32_t a_secretSize = 0,
		std::uint32_t a_flags = 0) noexcept -> NTSTATUS;
	auto BCryptGetProperty(
		BCRYPT_HANDLE a_object,
		const wchar_t* a_property,
		std::uint8_t* a_output,
		std::uint32_t a_outputSize,
		std::uint32_t* a_result,
		std::uint32_t a_flags = 0) noexcept -> NTSTATUS;
	auto BCryptHash(
		BCRYPT_ALG_HANDLE a_algorithm,
		std::uint8_t* a_secret,
		std::uint32_t a_secretSize,
		std::uint8_t* a_input,
		std::uint32_t a_inputSize,
		std::uint8_t* a_output,
		std::uint32_t a_outputSize) noexcept -> NTSTATUS;
	auto BCryptHashData(
		BCRYPT_HASH_HANDLE a_hash,
		std::uint8_t* a_input,
		std::uint32_t a_inputSize,
		std::uint32_t a_flags = 0) noexcept -> NTSTATUS;
	auto BCryptImportKey(
		BCRYPT_ALG_HANDLE a_algorithm,
		BCRYPT_KEY_HANDLE a_importKey,
		const wchar_t* a_blobType,
		BCRYPT_KEY_HANDLE* a_key,
		std::uint8_t* a_keyObject = nullptr,
		std::uint32_t a_keyObjectSize = 0,
		std::uint8_t* a_input = nullptr,
		std::uint32_t a_inputSize = 0,
		std::uint32_t a_flags = 0) noexcept -> NTSTATUS;
	auto BCryptImportKeyPair(
		BCRYPT_ALG_HANDLE a_algorithm,
		BCRYPT_KEY_HANDLE a_importKey,
		const wchar_t* a_blobType,
		BCRYPT_KEY_HANDLE* a_key,
		std::uint8_t* a_input,
		std::uint32_t a_inputSize,
		std::uint32_t a_flags = 0) noexcept -> NTSTATUS;
	auto BCryptKeyDerivation(
		BCRYPT_KEY_HANDLE a_key,
		BCryptBufferDesc* a_parameterList = nullptr,
		std::uint8_t* a_derivedKey = nullptr,
		std::uint32_t a_derivedKeySize = 0,
		std::uint32_t* a_result = nullptr,
		std::uint32_t a_flags = 0) noexcept -> NTSTATUS;
	auto BCryptOpenAlgorithmProvider(
		BCRYPT_ALG_HANDLE* a_algorithm,
		const wchar_t* a_id,
		const wchar_t* a_impl = nullptr,
		std::uint32_t a_flags = 0) noexcept -> NTSTATUS;
	auto BCryptProcessMultiOperations(
		BCRYPT_HANDLE a_object,
		BCRYPT_MULTI_OPERATION_TYPE a_operationType,
		void* a_operations,
		std::uint32_t a_operationsSize,
		std::uint32_t a_flags = 0) noexcept -> NTSTATUS;
	auto BCryptSecretAgreement(
		BCRYPT_KEY_HANDLE a_privateKey,
		BCRYPT_KEY_HANDLE a_publicKey,
		BCRYPT_SECRET_HANDLE* a_secret,
		std::uint32_t a_flags = 0) noexcept -> NTSTATUS;
	auto BCryptSetProperty(
		BCRYPT_HANDLE a_object,
		const wchar_t* a_property,
		std::uint8_t* a_input,
		std::uint32_t a_inputSize,
		std::uint32_t a_flags = 0) noexcept -> NTSTATUS;
	auto BCryptSignHash(
		BCRYPT_KEY_HANDLE a_key,
		void* a_paddingInfo = nullptr,
		std::uint8_t* a_input = nullptr,
		std::uint32_t a_inputSize = 0,
		std::uint8_t* a_output = nullptr,
		std::uint32_t a_outputSize = 0,
		std::uint32_t* a_result = nullptr,
		std::uint32_t a_flags = 0) noexcept -> NTSTATUS;
	auto BCryptVerifySignature(
		BCRYPT_KEY_HANDLE a_key,
		void* a_paddingInfo = nullptr,
		std::uint8_t* a_hash = nullptr,
		std::uint32_t a_hashSize = 0,
		std::uint8_t* a_signature = nullptr,
		std::uint32_t a_signatureSize = 0,
		std::uint32_t a_flags = 0) noexcept -> NTSTATUS;
}
