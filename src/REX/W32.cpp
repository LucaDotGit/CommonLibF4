#include "REX/W32.hpp"

#include "REX/Casting.hpp"

#define REX_BASIC_W32_IMPORT(a_returnType, a_name, a_noexcept, ...)                                        \
	extern "C" __declspec(dllimport) auto WIN_API W32_IMPL_##a_name(__VA_ARGS__) a_noexcept->a_returnType; \
	__pragma(comment(linker, "/alternatename:__imp_W32_IMPL_" #a_name "=__imp_" #a_name))

#define REX_W32_IMPORT(a_returnType, a_name, ...)                           \
	REX_BASIC_W32_IMPORT(a_returnType, a_name, noexcept(true), __VA_ARGS__)

#define REX_W32_IMPORT_THROW(a_returnType, a_name, ...)                      \
	REX_BASIC_W32_IMPORT(a_returnType, a_name, noexcept(false), __VA_ARGS__)

// NOLINTBEGIN(cppcoreguidelines-pro-type-vararg)

// ADVAPI32

REX_W32_IMPORT(
	std::int32_t,
	RegGetValueA,
	REX::W32::HKEY,
	const char*,
	const char*,
	std::uint32_t,
	std::uint32_t*,
	void*,
	std::uint32_t*);
REX_W32_IMPORT(
	std::int32_t,
	RegGetValueW,
	REX::W32::HKEY,
	const wchar_t*,
	const wchar_t*,
	std::uint32_t,
	std::uint32_t*,
	void*,
	std::uint32_t*);

namespace REX::W32
{
	auto RegGetValueA(
		HKEY a_key,
		const char* a_subKey,
		const char* a_value,
		std::uint32_t a_flags,
		std::uint32_t* a_type,
		void* a_data,
		std::uint32_t* a_dataLength) noexcept -> std::int32_t
	{
		return ::W32_IMPL_RegGetValueA(a_key, a_subKey, a_value, a_flags, a_type, a_data, a_dataLength);
	}

	auto RegGetValueW(
		HKEY a_key,
		const wchar_t* a_subKey,
		const wchar_t* a_value,
		std::uint32_t a_flags,
		std::uint32_t* a_type,
		void* a_data,
		std::uint32_t* a_dataLength) noexcept -> std::int32_t
	{
		return ::W32_IMPL_RegGetValueW(a_key, a_subKey, a_value, a_flags, a_type, a_data, a_dataLength);
	}
}

// BCRYPT

REX_W32_IMPORT(REX::W32::NTSTATUS, BCryptCloseAlgorithmProvider, REX::W32::BCRYPT_ALG_HANDLE, std::uint32_t);
REX_W32_IMPORT(
	REX::W32::NTSTATUS,
	BCryptCreateHash,
	REX::W32::BCRYPT_ALG_HANDLE,
	REX::W32::BCRYPT_HASH_HANDLE*,
	std::uint8_t*,
	std::uint32_t,
	std::uint8_t*,
	std::uint32_t,
	std::uint32_t);
REX_W32_IMPORT(
	REX::W32::NTSTATUS,
	BCryptCreateMultiHash,
	REX::W32::BCRYPT_ALG_HANDLE,
	REX::W32::BCRYPT_HASH_HANDLE*,
	std::uint32_t,
	std::uint8_t*,
	std::uint32_t,
	std::uint8_t*,
	std::uint32_t,
	std::uint32_t);
REX_W32_IMPORT(
	REX::W32::NTSTATUS,
	BCryptDecapsulate,
	REX::W32::BCRYPT_KEY_HANDLE,
	std::uint8_t*,
	std::uint32_t,
	std::uint8_t*,
	std::uint32_t,
	std::uint32_t*,
	std::uint32_t);
REX_W32_IMPORT(
	REX::W32::NTSTATUS,
	BCryptDecrypt,
	REX::W32::BCRYPT_KEY_HANDLE,
	std::uint8_t*,
	std::uint32_t,
	void*,
	std::uint8_t*,
	std::uint32_t,
	std::uint8_t*,
	std::uint32_t,
	std::uint32_t*,
	std::uint32_t);
REX_W32_IMPORT(
	REX::W32::NTSTATUS,
	BCryptDeriveKey,
	REX::W32::BCRYPT_SECRET_HANDLE,
	const wchar_t*,
	REX::W32::BCryptBufferDesc*,
	std::uint8_t*,
	std::uint32_t,
	std::uint32_t*,
	std::uint32_t);
REX_W32_IMPORT(REX::W32::NTSTATUS, BCryptDestroyHash, REX::W32::BCRYPT_HASH_HANDLE);
REX_W32_IMPORT(REX::W32::NTSTATUS, BCryptDestroyKey, REX::W32::BCRYPT_KEY_HANDLE);
REX_W32_IMPORT(REX::W32::NTSTATUS, BCryptDestroySecret, REX::W32::BCRYPT_SECRET_HANDLE);
REX_W32_IMPORT(
	REX::W32::NTSTATUS,
	BCryptDuplicateHash,
	REX::W32::BCRYPT_HASH_HANDLE,
	REX::W32::BCRYPT_HASH_HANDLE*,
	std::uint8_t*,
	std::uint32_t,
	std::uint32_t);
REX_W32_IMPORT(
	REX::W32::NTSTATUS,
	BCryptDuplicateKey,
	REX::W32::BCRYPT_KEY_HANDLE,
	REX::W32::BCRYPT_KEY_HANDLE*,
	std::uint8_t*,
	std::uint32_t,
	std::uint32_t);
REX_W32_IMPORT(
	REX::W32::NTSTATUS,
	BCryptEncapsulate,
	REX::W32::BCRYPT_KEY_HANDLE,
	std::uint8_t*,
	std::uint32_t,
	std::uint32_t*,
	std::uint8_t*,
	std::uint32_t,
	std::uint32_t*,
	std::uint32_t);
REX_W32_IMPORT(
	REX::W32::NTSTATUS,
	BCryptEncrypt,
	REX::W32::BCRYPT_KEY_HANDLE,
	std::uint8_t*,
	std::uint32_t,
	void*,
	std::uint8_t*,
	std::uint32_t,
	std::uint8_t*,
	std::uint32_t,
	std::uint32_t*,
	std::uint32_t);
REX_W32_IMPORT(
	REX::W32::NTSTATUS,
	BCryptExportKey,
	REX::W32::BCRYPT_KEY_HANDLE,
	REX::W32::BCRYPT_KEY_HANDLE,
	const wchar_t*,
	REX::W32::BCryptBufferDesc*,
	std::uint8_t*,
	std::uint32_t,
	std::uint32_t*,
	std::uint32_t);
REX_W32_IMPORT(REX::W32::NTSTATUS, BCryptFinalizeKeyPair, REX::W32::BCRYPT_KEY_HANDLE, std::uint32_t);
REX_W32_IMPORT(
	REX::W32::NTSTATUS,
	BCryptFinishHash,
	REX::W32::BCRYPT_HASH_HANDLE,
	std::uint8_t*,
	std::uint32_t,
	std::uint32_t);
REX_W32_IMPORT(REX::W32::NTSTATUS, BCryptFreeBuffer, void*);
REX_W32_IMPORT(
	REX::W32::NTSTATUS,
	BCryptGenRandom,
	REX::W32::BCRYPT_ALG_HANDLE,
	std::uint8_t*,
	std::uint32_t,
	std::uint32_t);
REX_W32_IMPORT(
	REX::W32::NTSTATUS,
	BCryptGenerateKeyPair,
	REX::W32::BCRYPT_ALG_HANDLE,
	REX::W32::BCRYPT_KEY_HANDLE*,
	std::uint32_t,
	std::uint32_t);
REX_W32_IMPORT(
	REX::W32::NTSTATUS,
	BCryptGenerateSymmetricKey,
	REX::W32::BCRYPT_ALG_HANDLE,
	REX::W32::BCRYPT_KEY_HANDLE*,
	std::uint8_t*,
	std::uint32_t,
	std::uint8_t*,
	std::uint32_t,
	std::uint32_t);
REX_W32_IMPORT(
	REX::W32::NTSTATUS,
	BCryptGetProperty,
	REX::W32::BCRYPT_HANDLE,
	const wchar_t*,
	std::uint8_t*,
	std::uint32_t,
	std::uint32_t*,
	std::uint32_t);
REX_W32_IMPORT(
	REX::W32::NTSTATUS,
	BCryptHash,
	REX::W32::BCRYPT_ALG_HANDLE,
	std::uint8_t*,
	std::uint32_t,
	std::uint8_t*,
	std::uint32_t,
	std::uint8_t*,
	std::uint32_t);
REX_W32_IMPORT(
	REX::W32::NTSTATUS,
	BCryptHashData,
	REX::W32::BCRYPT_HASH_HANDLE,
	std::uint8_t*,
	std::uint32_t,
	std::uint32_t);
REX_W32_IMPORT(
	REX::W32::NTSTATUS,
	BCryptImportKey,
	REX::W32::BCRYPT_ALG_HANDLE,
	REX::W32::BCRYPT_KEY_HANDLE,
	const wchar_t*,
	REX::W32::BCRYPT_KEY_HANDLE*,
	std::uint8_t*,
	std::uint32_t,
	std::uint8_t*,
	std::uint32_t,
	std::uint32_t);
REX_W32_IMPORT(
	REX::W32::NTSTATUS,
	BCryptImportKeyPair,
	REX::W32::BCRYPT_ALG_HANDLE,
	REX::W32::BCRYPT_KEY_HANDLE,
	const wchar_t*,
	REX::W32::BCRYPT_KEY_HANDLE*,
	std::uint8_t*,
	std::uint32_t,
	std::uint32_t);
REX_W32_IMPORT(
	REX::W32::NTSTATUS,
	BCryptKeyDerivation,
	REX::W32::BCRYPT_KEY_HANDLE,
	REX::W32::BCryptBufferDesc*,
	std::uint8_t*,
	std::uint32_t,
	std::uint32_t*,
	std::uint32_t);
REX_W32_IMPORT(
	REX::W32::NTSTATUS,
	BCryptOpenAlgorithmProvider,
	REX::W32::BCRYPT_ALG_HANDLE*,
	const wchar_t*,
	const wchar_t*,
	std::uint32_t);
REX_W32_IMPORT(
	REX::W32::NTSTATUS,
	BCryptProcessMultiOperations,
	REX::W32::BCRYPT_HANDLE,
	REX::W32::BCRYPT_MULTI_OPERATION_TYPE,
	void*,
	std::uint32_t,
	std::uint32_t);
REX_W32_IMPORT(
	REX::W32::NTSTATUS,
	BCryptSecretAgreement,
	REX::W32::BCRYPT_KEY_HANDLE,
	REX::W32::BCRYPT_KEY_HANDLE,
	REX::W32::BCRYPT_SECRET_HANDLE*,
	std::uint32_t);
REX_W32_IMPORT(
	REX::W32::NTSTATUS,
	BCryptSetProperty,
	REX::W32::BCRYPT_HANDLE,
	const wchar_t*,
	std::uint8_t*,
	std::uint32_t,
	std::uint32_t);
REX_W32_IMPORT(
	REX::W32::NTSTATUS,
	BCryptSignHash,
	REX::W32::BCRYPT_KEY_HANDLE,
	void*,
	std::uint8_t*,
	std::uint32_t,
	std::uint8_t*,
	std::uint32_t,
	std::uint32_t*,
	std::uint32_t);
REX_W32_IMPORT(
	REX::W32::NTSTATUS,
	BCryptVerifySignature,
	REX::W32::BCRYPT_KEY_HANDLE,
	void*,
	std::uint8_t*,
	std::uint32_t,
	std::uint8_t*,
	std::uint32_t,
	std::uint32_t);

namespace REX::W32
{
	auto BCryptCloseAlgorithmProvider(BCRYPT_ALG_HANDLE a_algorithm, std::uint32_t a_flags) noexcept -> NTSTATUS
	{
		return ::W32_IMPL_BCryptCloseAlgorithmProvider(a_algorithm, a_flags);
	}

	auto BCryptCreateHash(
		BCRYPT_ALG_HANDLE a_algorithm,
		BCRYPT_HASH_HANDLE* a_hash,
		std::uint8_t* a_hashObject,
		std::uint32_t a_hashObjectSize,
		std::uint8_t* a_secret,
		std::uint32_t a_secretSize,
		std::uint32_t a_flags) noexcept -> NTSTATUS
	{
		return ::W32_IMPL_BCryptCreateHash(
			a_algorithm,
			a_hash,
			a_hashObject,
			a_hashObjectSize,
			a_secret,
			a_secretSize,
			a_flags);
	}

	auto BCryptCreateMultiHash(
		BCRYPT_ALG_HANDLE a_algorithm,
		BCRYPT_HASH_HANDLE* a_hash,
		std::uint32_t a_hashes,
		std::uint8_t* a_hashObject,
		std::uint32_t a_hashObjectSize,
		std::uint8_t* a_secret,
		std::uint32_t a_secretSize,
		std::uint32_t a_flags) noexcept -> NTSTATUS
	{
		return ::W32_IMPL_BCryptCreateMultiHash(
			a_algorithm,
			a_hash,
			a_hashes,
			a_hashObject,
			a_hashObjectSize,
			a_secret,
			a_secretSize,
			a_flags);
	}

	auto BCryptDecapsulate(
		BCRYPT_KEY_HANDLE a_key,
		std::uint8_t* a_cipherText,
		std::uint32_t a_cipherTextSize,
		std::uint8_t* a_secretKey,
		std::uint32_t a_secretKeySize,
		std::uint32_t* a_secretKeyResult,
		std::uint32_t a_flags) noexcept -> NTSTATUS
	{
		return ::W32_IMPL_BCryptDecapsulate(
			a_key,
			a_cipherText,
			a_cipherTextSize,
			a_secretKey,
			a_secretKeySize,
			a_secretKeyResult,
			a_flags);
	}

	auto BCryptDeriveKey(
		BCRYPT_SECRET_HANDLE a_secret,
		const wchar_t* a_kdf,
		BCryptBufferDesc* a_parameterList,
		std::uint8_t* a_derivedKey,
		std::uint32_t a_derivedKeySize,
		std::uint32_t* a_result,
		std::uint32_t a_flags) noexcept -> NTSTATUS
	{
		return ::W32_IMPL_BCryptDeriveKey(
			a_secret,
			a_kdf,
			a_parameterList,
			a_derivedKey,
			a_derivedKeySize,
			a_result,
			a_flags);
	}

	auto BCryptDestroyHash(BCRYPT_HASH_HANDLE a_hash) noexcept -> NTSTATUS
	{
		return ::W32_IMPL_BCryptDestroyHash(a_hash);
	}

	auto BCryptDestroyKey(BCRYPT_KEY_HANDLE a_key) noexcept -> NTSTATUS
	{
		return ::W32_IMPL_BCryptDestroyKey(a_key);
	}

	auto BCryptDestroySecret(BCRYPT_SECRET_HANDLE a_secret) noexcept -> NTSTATUS
	{
		return ::W32_IMPL_BCryptDestroySecret(a_secret);
	}

	auto BCryptDuplicateHash(
		BCRYPT_HASH_HANDLE a_hash,
		BCRYPT_HASH_HANDLE* a_newHash,
		std::uint8_t* a_hashObject,
		std::uint32_t a_hashObjectSize,
		std::uint32_t a_flags) noexcept -> NTSTATUS
	{
		return ::W32_IMPL_BCryptDuplicateHash(a_hash, a_newHash, a_hashObject, a_hashObjectSize, a_flags);
	}

	auto BCryptDuplicateKey(
		BCRYPT_KEY_HANDLE a_key,
		BCRYPT_KEY_HANDLE* a_newKey,
		std::uint8_t* a_keyObject,
		std::uint32_t a_keyObjectSize,
		std::uint32_t a_flags) noexcept -> NTSTATUS
	{
		return ::W32_IMPL_BCryptDuplicateKey(a_key, a_newKey, a_keyObject, a_keyObjectSize, a_flags);
	}

	auto BCryptEncapsulate(
		BCRYPT_KEY_HANDLE a_key,
		std::uint8_t* a_secretKey,
		std::uint32_t a_secretKeySize,
		std::uint32_t* a_secretKeyResult,
		std::uint8_t* a_cipherText,
		std::uint32_t a_cipherTextSize,
		std::uint32_t* a_cipherTextResult,
		std::uint32_t a_flags) noexcept -> NTSTATUS
	{
		return ::W32_IMPL_BCryptEncapsulate(
			a_key,
			a_secretKey,
			a_secretKeySize,
			a_secretKeyResult,
			a_cipherText,
			a_cipherTextSize,
			a_cipherTextResult,
			a_flags);
	}

	auto BCryptEncrypt(
		BCRYPT_KEY_HANDLE a_key,
		std::uint8_t* a_input,
		std::uint32_t a_inputSize,
		void* a_paddingInfo,
		std::uint8_t* a_iv,
		std::uint32_t a_ivSize,
		std::uint8_t* a_output,
		std::uint32_t a_outputSize,
		std::uint32_t* a_result,
		std::uint32_t a_flags) noexcept -> NTSTATUS
	{
		return ::W32_IMPL_BCryptEncrypt(
			a_key,
			a_input,
			a_inputSize,
			a_paddingInfo,
			a_iv,
			a_ivSize,
			a_output,
			a_outputSize,
			a_result,
			a_flags);
	}

	auto BCryptExportKey(
		BCRYPT_KEY_HANDLE a_key,
		BCRYPT_KEY_HANDLE a_exportKey,
		const wchar_t* a_blobType,
		BCryptBufferDesc* a_parameterList,
		std::uint8_t* a_output,
		std::uint32_t a_outputSize,
		std::uint32_t* a_result,
		std::uint32_t a_flags) noexcept -> NTSTATUS
	{
		return ::W32_IMPL_BCryptExportKey(
			a_key,
			a_exportKey,
			a_blobType,
			a_parameterList,
			a_output,
			a_outputSize,
			a_result,
			a_flags);
	}

	auto BCryptFinalizeKeyPair(BCRYPT_KEY_HANDLE a_key, std::uint32_t a_flags) noexcept -> NTSTATUS
	{
		return ::W32_IMPL_BCryptFinalizeKeyPair(a_key, a_flags);
	}

	auto BCryptFinishHash(
		BCRYPT_HASH_HANDLE a_hash,
		std::uint8_t* a_output,
		std::uint32_t a_outputSize,
		std::uint32_t a_flags) noexcept -> NTSTATUS
	{
		return ::W32_IMPL_BCryptFinishHash(a_hash, a_output, a_outputSize, a_flags);
	}

	auto BCryptFreeBuffer(void* a_buffer) noexcept -> NTSTATUS
	{
		return ::W32_IMPL_BCryptFreeBuffer(a_buffer);
	}

	auto BCryptGenRandom(
		BCRYPT_ALG_HANDLE a_algorithm,
		std::uint8_t* a_buffer,
		std::uint32_t a_bufferSize,
		std::uint32_t a_flags) noexcept -> NTSTATUS
	{
		return ::W32_IMPL_BCryptGenRandom(a_algorithm, a_buffer, a_bufferSize, a_flags);
	}

	auto BCryptGenerateKeyPair(
		BCRYPT_ALG_HANDLE a_algorithm,
		BCRYPT_KEY_HANDLE* a_key,
		std::uint32_t a_length,
		std::uint32_t a_flags) noexcept -> NTSTATUS
	{
		return ::W32_IMPL_BCryptGenerateKeyPair(a_algorithm, a_key, a_length, a_flags);
	}

	auto BCryptGenerateSymmetricKey(
		BCRYPT_ALG_HANDLE a_algorithm,
		BCRYPT_KEY_HANDLE* a_key,
		std::uint8_t* a_keyObject,
		std::uint32_t a_keyObjectSize,
		std::uint8_t* a_secret,
		std::uint32_t a_secretSize,
		std::uint32_t a_flags) noexcept -> NTSTATUS
	{
		return ::W32_IMPL_BCryptGenerateSymmetricKey(
			a_algorithm,
			a_key,
			a_keyObject,
			a_keyObjectSize,
			a_secret,
			a_secretSize,
			a_flags);
	}

	auto BCryptGetProperty(
		BCRYPT_HANDLE a_object,
		const wchar_t* a_property,
		std::uint8_t* a_output,
		std::uint32_t a_outputSize,
		std::uint32_t* a_result,
		std::uint32_t a_flags) noexcept -> NTSTATUS
	{
		return ::W32_IMPL_BCryptGetProperty(a_object, a_property, a_output, a_outputSize, a_result, a_flags);
	}

	auto BCryptHash(
		BCRYPT_ALG_HANDLE a_algorithm,
		std::uint8_t* a_secret,
		std::uint32_t a_secretSize,
		std::uint8_t* a_input,
		std::uint32_t a_inputSize,
		std::uint8_t* a_output,
		std::uint32_t a_outputSize) noexcept -> NTSTATUS
	{
		return ::W32_IMPL_BCryptHash(a_algorithm, a_secret, a_secretSize, a_input, a_inputSize, a_output, a_outputSize);
	}

	auto BCryptHashData(
		BCRYPT_HASH_HANDLE a_hash,
		std::uint8_t* a_input,
		std::uint32_t a_inputSize,
		std::uint32_t a_flags) noexcept -> NTSTATUS
	{
		return ::W32_IMPL_BCryptHashData(a_hash, a_input, a_inputSize, a_flags);
	}

	auto BCryptImportKey(
		BCRYPT_ALG_HANDLE a_algorithm,
		BCRYPT_KEY_HANDLE a_importKey,
		const wchar_t* a_blobType,
		BCRYPT_KEY_HANDLE* a_key,
		std::uint8_t* a_keyObject,
		std::uint32_t a_keyObjectSize,
		std::uint8_t* a_input,
		std::uint32_t a_inputSize,
		std::uint32_t a_flags) noexcept -> NTSTATUS
	{
		return ::W32_IMPL_BCryptImportKey(
			a_algorithm,
			a_importKey,
			a_blobType,
			a_key,
			a_keyObject,
			a_keyObjectSize,
			a_input,
			a_inputSize,
			a_flags);
	}

	auto BCryptImportKeyPair(
		BCRYPT_ALG_HANDLE a_algorithm,
		BCRYPT_KEY_HANDLE a_importKey,
		const wchar_t* a_blobType,
		BCRYPT_KEY_HANDLE* a_key,
		std::uint8_t* a_input,
		std::uint32_t a_inputSize,
		std::uint32_t a_flags) noexcept -> NTSTATUS
	{
		return ::W32_IMPL_BCryptImportKeyPair(
			a_algorithm,
			a_importKey,
			a_blobType,
			a_key,
			a_input,
			a_inputSize,
			a_flags);
	}

	auto BCryptKeyDerivation(
		BCRYPT_KEY_HANDLE a_key,
		BCryptBufferDesc* a_parameterList,
		std::uint8_t* a_derivedKey,
		std::uint32_t a_derivedKeySize,
		std::uint32_t* a_result,
		std::uint32_t a_flags) noexcept -> NTSTATUS
	{
		return ::W32_IMPL_BCryptKeyDerivation(
			a_key,
			a_parameterList,
			a_derivedKey,
			a_derivedKeySize,
			a_result,
			a_flags);
	}

	auto BCryptOpenAlgorithmProvider(
		BCRYPT_ALG_HANDLE* a_algorithm,
		const wchar_t* a_id,
		const wchar_t* a_impl,
		std::uint32_t a_flags) noexcept -> NTSTATUS
	{
		return ::W32_IMPL_BCryptOpenAlgorithmProvider(a_algorithm, a_id, a_impl, a_flags);
	}

	auto BCryptProcessMultiOperations(
		BCRYPT_HANDLE a_object,
		BCRYPT_MULTI_OPERATION_TYPE a_operationType,
		void* a_operations,
		std::uint32_t a_operationsSize,
		std::uint32_t a_flags) noexcept -> NTSTATUS
	{
		return ::W32_IMPL_BCryptProcessMultiOperations(
			a_object,
			a_operationType,
			a_operations,
			a_operationsSize,
			a_flags);
	}

	auto BCryptSecretAgreement(
		BCRYPT_KEY_HANDLE a_privateKey,
		BCRYPT_KEY_HANDLE a_publicKey,
		BCRYPT_SECRET_HANDLE* a_secret,
		std::uint32_t a_flags) noexcept -> NTSTATUS
	{
		return ::W32_IMPL_BCryptSecretAgreement(a_privateKey, a_publicKey, a_secret, a_flags);
	}

	auto BCryptSetProperty(
		BCRYPT_HANDLE a_object,
		const wchar_t* a_property,
		std::uint8_t* a_input,
		std::uint32_t a_inputSize,
		std::uint32_t a_flags) noexcept -> NTSTATUS
	{
		return ::W32_IMPL_BCryptSetProperty(a_object, a_property, a_input, a_inputSize, a_flags);
	}

	auto BCryptSignHash(
		BCRYPT_KEY_HANDLE a_key,
		void* a_paddingInfo,
		std::uint8_t* a_input,
		std::uint32_t a_inputSize,
		std::uint8_t* a_output,
		std::uint32_t a_outputSize,
		std::uint32_t* a_result,
		std::uint32_t a_flags) noexcept -> NTSTATUS
	{
		return ::W32_IMPL_BCryptSignHash(
			a_key,
			a_paddingInfo,
			a_input,
			a_inputSize,
			a_output,
			a_outputSize,
			a_result,
			a_flags);
	}

	auto BCryptVerifySignature(
		BCRYPT_KEY_HANDLE a_key,
		void* a_paddingInfo,
		std::uint8_t* a_hash,
		std::uint32_t a_hashSize,
		std::uint8_t* a_signature,
		std::uint32_t a_signatureSize,
		std::uint32_t a_flags) noexcept -> NTSTATUS
	{
		return ::W32_IMPL_BCryptVerifySignature(
			a_key,
			a_paddingInfo,
			a_hash,
			a_hashSize,
			a_signature,
			a_signatureSize,
			a_flags);
	}
}

// D3D11

REX_W32_IMPORT(
	std::int32_t,
	D3D11CreateDevice,
	REX::W32::IDXGIAdapter*,
	REX::W32::D3D_DRIVER_TYPE,
	REX::W32::HMODULE,
	std::uint32_t,
	const REX::W32::D3D_FEATURE_LEVEL*,
	std::uint32_t,
	std::uint32_t,
	REX::W32::ID3D11Device**,
	REX::W32::D3D_FEATURE_LEVEL*,
	REX::W32::ID3D11DeviceContext**);
REX_W32_IMPORT(
	std::int32_t,
	D3D11CreateDeviceAndSwapChain,
	REX::W32::IDXGIAdapter*,
	REX::W32::D3D_DRIVER_TYPE,
	REX::W32::HMODULE,
	std::uint32_t,
	const REX::W32::D3D_FEATURE_LEVEL*,
	std::uint32_t,
	std::uint32_t,
	const REX::W32::DXGI_SWAP_CHAIN_DESC*,
	REX::W32::IDXGISwapChain**,
	REX::W32::ID3D11Device**,
	REX::W32::D3D_FEATURE_LEVEL*,
	REX::W32::ID3D11DeviceContext**);

namespace REX::W32
{
	auto D3D11CreateDevice(
		IDXGIAdapter* a_adapter,
		D3D_DRIVER_TYPE a_driverType,
		HMODULE a_software,
		std::uint32_t a_flags,
		const D3D_FEATURE_LEVEL* a_pFeatureLevels,
		std::uint32_t a_featureLevels,
		std::uint32_t a_sdkVersion,
		ID3D11Device** a_device,
		D3D_FEATURE_LEVEL* a_pFeatureLevel,
		ID3D11DeviceContext** a_immediateContext) noexcept -> HRESULT
	{
		return ::W32_IMPL_D3D11CreateDevice(
			a_adapter,
			a_driverType,
			a_software,
			a_flags,
			a_pFeatureLevels,
			a_featureLevels,
			a_sdkVersion,
			a_device,
			a_pFeatureLevel,
			a_immediateContext);
	}

	auto D3D11CreateDeviceAndSwapChain(
		IDXGIAdapter* a_adapter,
		D3D_DRIVER_TYPE a_driverType,
		HMODULE a_software,
		std::uint32_t a_flags,
		const D3D_FEATURE_LEVEL* a_pFeatureLevels,
		std::uint32_t a_featureLevels,
		std::uint32_t a_sdkVersion,
		const DXGI_SWAP_CHAIN_DESC* a_swapChainDesc,
		IDXGISwapChain** a_swapChain,
		ID3D11Device** a_device,
		D3D_FEATURE_LEVEL* a_pFeatureLevel,
		ID3D11DeviceContext** a_immediateContext) noexcept -> HRESULT
	{
		return ::W32_IMPL_D3D11CreateDeviceAndSwapChain(
			a_adapter,
			a_driverType,
			a_software,
			a_flags,
			a_pFeatureLevels,
			a_featureLevels,
			a_sdkVersion,
			a_swapChainDesc,
			a_swapChain,
			a_device,
			a_pFeatureLevel,
			a_immediateContext);
	}
}

// D3DCOMPILER

REX_W32_IMPORT(
	std::int32_t,
	D3DCompile,
	const void*,
	std::size_t,
	const char*,
	const REX::W32::D3D_SHADER_MACRO*,
	REX::W32::ID3DInclude*,
	const char*,
	const char*,
	std::uint32_t,
	std::uint32_t,
	REX::W32::ID3DBlob**,
	REX::W32::ID3DBlob**);
REX_W32_IMPORT(
	std::int32_t,
	D3DCompile2,
	const void*,
	std::size_t,
	const char*,
	const REX::W32::D3D_SHADER_MACRO*,
	REX::W32::ID3DInclude*,
	const char*,
	const char*,
	std::uint32_t,
	std::uint32_t,
	std::uint32_t,
	const void*,
	std::size_t,
	REX::W32::ID3DBlob**,
	REX::W32::ID3DBlob**);
REX_W32_IMPORT(
	std::int32_t,
	D3DCompileFromFile,
	const wchar_t*,
	const REX::W32::D3D_SHADER_MACRO*,
	REX::W32::ID3DInclude*,
	const char*,
	const char*,
	std::uint32_t,
	std::uint32_t,
	REX::W32::ID3DBlob**,
	REX::W32::ID3DBlob**);
REX_W32_IMPORT(
	std::int32_t,
	D3DCompressShaders,
	std::uint32_t,
	REX::W32::D3D_SHADER_DATA*,
	std::uint32_t,
	REX::W32::ID3DBlob**);
REX_W32_IMPORT(std::int32_t, D3DCreateBlob, std::size_t, REX::W32::ID3DBlob**);
REX_W32_IMPORT(std::int32_t, D3DCreateFunctionLinkingGraph, std::uint32_t, REX::W32::ID3D11FunctionLinkingGraph**);
REX_W32_IMPORT(std::int32_t, D3DCreateLinker, REX::W32::ID3D11Linker**);
REX_W32_IMPORT(
	std::int32_t,
	D3DDecompressShaders,
	const void*,
	std::size_t,
	std::uint32_t,
	std::uint32_t,
	std::uint32_t*,
	std::uint32_t,
	REX::W32::ID3DBlob**,
	std::uint32_t*);
REX_W32_IMPORT(
	std::int32_t,
	D3DDisassemble,
	const void*,
	std::size_t,
	std::uint32_t,
	const char*,
	REX::W32::ID3DBlob**);
REX_W32_IMPORT(std::int32_t, D3DDisassemble10Effect, REX::W32::ID3D10Effect*, std::uint32_t, REX::W32::ID3DBlob**);
REX_W32_IMPORT(
	std::int32_t,
	D3DDisassembleRegion,
	const void*,
	std::size_t,
	std::uint32_t,
	const char*,
	std::size_t,
	std::size_t,
	std::size_t*,
	REX::W32::ID3DBlob**);
REX_W32_IMPORT(
	std::int32_t,
	D3DGetBlobPart,
	const void*,
	std::size_t,
	REX::W32::D3D_BLOB_PART,
	std::uint32_t a_flags,
	REX::W32::ID3DBlob**);
REX_W32_IMPORT(std::int32_t, D3DGetDebugInfo, const void*, std::size_t, REX::W32::ID3DBlob**);
REX_W32_IMPORT(std::int32_t, D3DGetInputSignatureBlob, const void*, std::size_t, REX::W32::ID3DBlob**);
REX_W32_IMPORT(std::int32_t, D3DGetInputAndOutputSignatureBlob, const void*, std::size_t, REX::W32::ID3DBlob**);
REX_W32_IMPORT(std::int32_t, D3DGetOutputSignatureBlob, const void*, std::size_t, REX::W32::ID3DBlob**);
REX_W32_IMPORT(
	std::int32_t,
	D3DGetTraceInstructionOffsets,
	const void*,
	std::size_t,
	std::uint32_t,
	std::size_t,
	std::size_t,
	std::size_t*,
	std::size_t*);
REX_W32_IMPORT(std::int32_t, D3DLoadModule, const void*, std::size_t, REX::W32::ID3D11Module**);
REX_W32_IMPORT(
	std::int32_t,
	D3DPreprocess,
	const void*,
	std::size_t,
	const char*,
	const REX::W32::D3D_SHADER_MACRO*,
	REX::W32::ID3DInclude*,
	REX::W32::ID3DBlob**,
	REX::W32::ID3DBlob**);
REX_W32_IMPORT(std::int32_t, D3DReadFileToBlob, const wchar_t*, REX::W32::ID3DBlob**);
REX_W32_IMPORT(std::int32_t, D3DReflect, const void*, std::size_t, const REX::W32::IID&, void**);
REX_W32_IMPORT(std::int32_t, D3DReflectLibrary, const void*, std::size_t, const REX::W32::IID&, void**);
REX_W32_IMPORT(
	std::int32_t,
	D3DSetBlobPart,
	const void*,
	std::size_t,
	REX::W32::D3D_BLOB_PART,
	std::uint32_t,
	const void*,
	std::size_t,
	REX::W32::ID3DBlob**);
REX_W32_IMPORT(std::int32_t, D3DStripShader, const void*, std::size_t, std::uint32_t, REX::W32::ID3DBlob**);
REX_W32_IMPORT(std::int32_t, D3DWriteBlobToFile, REX::W32::ID3DBlob*, const wchar_t*, REX::W32::BOOL);

namespace REX::W32
{
	auto D3DCompile(
		const void* a_sourceData,
		std::size_t a_sourceDataSize,
		const char* a_sourceName,
		const D3D_SHADER_MACRO* a_defines,
		ID3DInclude* a_include,
		const char* a_entrypoint,
		const char* a_target,
		std::uint32_t a_flags1,
		std::uint32_t a_flags2,
		ID3DBlob** a_code,
		ID3DBlob** a_errorMessages) noexcept -> HRESULT
	{
		return ::W32_IMPL_D3DCompile(
			a_sourceData,
			a_sourceDataSize,
			a_sourceName,
			a_defines,
			a_include,
			a_entrypoint,
			a_target,
			a_flags1,
			a_flags2,
			a_code,
			a_errorMessages);
	}

	auto D3DCompile2(
		const void* a_sourceData,
		std::size_t a_sourceDataSize,
		const char* a_sourceName,
		const D3D_SHADER_MACRO* a_defines,
		ID3DInclude* a_include,
		const char* a_entrypoint,
		const char* a_target,
		std::uint32_t a_flags1,
		std::uint32_t a_flags2,
		std::uint32_t a_secondaryDataFlags,
		const void* a_secondaryData,
		std::size_t a_secondaryDataSize,
		ID3DBlob** a_code,
		ID3DBlob** a_errorMessages) noexcept -> HRESULT
	{
		return ::W32_IMPL_D3DCompile2(
			a_sourceData,
			a_sourceDataSize,
			a_sourceName,
			a_defines,
			a_include,
			a_entrypoint,
			a_target,
			a_flags1,
			a_flags2,
			a_secondaryDataFlags,
			a_secondaryData,
			a_secondaryDataSize,
			a_code,
			a_errorMessages);
	}

	auto D3DCompileFromFile(
		const wchar_t* a_fileName,
		const D3D_SHADER_MACRO* a_defines,
		ID3DInclude* a_include,
		const char* a_entrypoint,
		const char* a_target,
		std::uint32_t a_flags1,
		std::uint32_t a_flags2,
		ID3DBlob** a_code,
		ID3DBlob** a_errorMessages) noexcept -> HRESULT
	{
		return ::W32_IMPL_D3DCompileFromFile(
			a_fileName,
			a_defines,
			a_include,
			a_entrypoint,
			a_target,
			a_flags1,
			a_flags2,
			a_code,
			a_errorMessages);
	}

	auto D3DCompressShaders(
		std::uint32_t a_numShaders,
		D3D_SHADER_DATA* a_shaderData,
		std::uint32_t a_flags,
		ID3DBlob** a_compressedData) noexcept -> HRESULT
	{
		return ::W32_IMPL_D3DCompressShaders(a_numShaders, a_shaderData, a_flags, a_compressedData);
	}

	auto D3DCreateBlob(std::size_t a_size, ID3DBlob** a_blob) noexcept -> HRESULT
	{
		return ::W32_IMPL_D3DCreateBlob(a_size, a_blob);
	}

	auto D3DCreateFunctionLinkingGraph(std::uint32_t a_flags, ID3D11FunctionLinkingGraph** a_functionLinkingGraph)
		noexcept -> HRESULT
	{
		return ::W32_IMPL_D3DCreateFunctionLinkingGraph(a_flags, a_functionLinkingGraph);
	}

	auto D3DCreateLinker(ID3D11Linker** a_linker) noexcept -> HRESULT
	{
		return ::W32_IMPL_D3DCreateLinker(a_linker);
	}

	auto D3DDecompressShaders(
		const void* a_sourceData,
		std::size_t a_sourceDataSize,
		std::uint32_t a_numShaders,
		std::uint32_t a_startIndex,
		std::uint32_t* a_indices,
		std::uint32_t a_flags,
		ID3DBlob** a_shaders,
		std::uint32_t* a_totalShaders) noexcept -> HRESULT
	{
		return ::W32_IMPL_D3DDecompressShaders(
			a_sourceData,
			a_sourceDataSize,
			a_numShaders,
			a_startIndex,
			a_indices,
			a_flags,
			a_shaders,
			a_totalShaders);
	}

	auto D3DDisassemble(
		const void* a_sourceData,
		std::size_t a_sourceDataSize,
		std::uint32_t a_flags,
		const char* a_comments,
		ID3DBlob** a_disassembly) noexcept -> HRESULT
	{
		return ::W32_IMPL_D3DDisassemble(a_sourceData, a_sourceDataSize, a_flags, a_comments, a_disassembly);
	}

	auto D3DDisassemble10Effect(ID3D10Effect* a_effect, std::uint32_t a_flags, ID3DBlob** a_disassembly) noexcept
		-> HRESULT
	{
		return ::W32_IMPL_D3DDisassemble10Effect(a_effect, a_flags, a_disassembly);
	}

	auto D3DDisassembleRegion(
		const void* a_sourceData,
		std::size_t a_sourceDataSize,
		std::uint32_t a_flags,
		const char* a_comments,
		std::size_t a_startByteOffset,
		std::size_t a_numInsts,
		std::size_t* a_finishByteOffset,
		ID3DBlob** a_disassembly) noexcept -> HRESULT
	{
		return ::W32_IMPL_D3DDisassembleRegion(
			a_sourceData,
			a_sourceDataSize,
			a_flags,
			a_comments,
			a_startByteOffset,
			a_numInsts,
			a_finishByteOffset,
			a_disassembly);
	}

	auto D3DGetBlobPart(
		const void* a_sourceData,
		std::size_t a_sourceDataSize,
		D3D_BLOB_PART a_partType,
		std::uint32_t a_flags,
		ID3DBlob** a_part) noexcept -> HRESULT
	{
		return ::W32_IMPL_D3DGetBlobPart(a_sourceData, a_sourceDataSize, a_partType, a_flags, a_part);
	}

	auto D3DGetDebugInfo(const void* a_sourceData, std::size_t a_sourceDataSize, ID3DBlob** a_debugInfo) noexcept
		-> HRESULT
	{
		return ::W32_IMPL_D3DGetDebugInfo(a_sourceData, a_sourceDataSize, a_debugInfo);
	}

	auto D3DGetInputSignatureBlob(const void* a_sourceData, std::size_t a_sourceDataSize, ID3DBlob** a_signatureBlob)
		noexcept -> HRESULT
	{
		return ::W32_IMPL_D3DGetInputSignatureBlob(a_sourceData, a_sourceDataSize, a_signatureBlob);
	}

	auto D3DGetInputAndOutputSignatureBlob(
		const void* a_sourceData,
		std::size_t a_sourceDataSize,
		ID3DBlob** a_signatureBlob) noexcept -> HRESULT
	{
		return ::W32_IMPL_D3DGetInputAndOutputSignatureBlob(a_sourceData, a_sourceDataSize, a_signatureBlob);
	}

	auto D3DGetOutputSignatureBlob(const void* a_sourceData, std::size_t a_sourceDataSize, ID3DBlob** a_signatureBlob)
		noexcept -> HRESULT
	{
		return ::W32_IMPL_D3DGetOutputSignatureBlob(a_sourceData, a_sourceDataSize, a_signatureBlob);
	}

	auto D3DGetTraceInstructionOffsets(
		const void* a_sourceData,
		std::size_t a_sourceDataSize,
		std::uint32_t a_flags,
		std::size_t a_startInstIndex,
		std::size_t a_numInsts,
		std::size_t* a_offsets,
		std::size_t* a_totalInsts) noexcept -> HRESULT
	{
		return ::W32_IMPL_D3DGetTraceInstructionOffsets(
			a_sourceData,
			a_sourceDataSize,
			a_flags,
			a_startInstIndex,
			a_numInsts,
			a_offsets,
			a_totalInsts);
	}

	auto D3DLoadModule(const void* a_sourceData, std::size_t a_sourceDataSize, ID3D11Module** a_module) noexcept
		-> HRESULT
	{
		return ::W32_IMPL_D3DLoadModule(a_sourceData, a_sourceDataSize, a_module);
	}

	auto D3DPreprocess(
		const void* a_sourceData,
		std::size_t a_sourceDataSize,
		const char* a_sourceName,
		const D3D_SHADER_MACRO* a_defines,
		ID3DInclude* a_include,
		ID3DBlob** a_codeText,
		ID3DBlob** a_errorMessages) noexcept -> HRESULT
	{
		return ::W32_IMPL_D3DPreprocess(
			a_sourceData,
			a_sourceDataSize,
			a_sourceName,
			a_defines,
			a_include,
			a_codeText,
			a_errorMessages);
	}

	auto D3DReadFileToBlob(const wchar_t* a_fileName, ID3DBlob** a_contents) noexcept -> HRESULT
	{
		return ::W32_IMPL_D3DReadFileToBlob(a_fileName, a_contents);
	}

	auto D3DReflect(const void* a_sourceData, std::size_t a_sourceDataSize, const IID& a_iid, void** a_reflector)
		noexcept -> HRESULT
	{
		return ::W32_IMPL_D3DReflect(a_sourceData, a_sourceDataSize, a_iid, a_reflector);
	}

	auto D3DReflectLibrary(const void* a_sourceData, std::size_t a_sourceDataSize, const IID& a_iid, void** a_reflector)
		noexcept -> HRESULT
	{
		return ::W32_IMPL_D3DReflectLibrary(a_sourceData, a_sourceDataSize, a_iid, a_reflector);
	}

	auto D3DSetBlobPart(
		const void* a_sourceData,
		std::size_t a_sourceDataSize,
		D3D_BLOB_PART a_partType,
		std::uint32_t a_flags,
		const void* a_part,
		std::size_t a_partSize,
		ID3DBlob** a_newShader) noexcept -> HRESULT
	{
		return ::W32_IMPL_D3DSetBlobPart(
			a_sourceData,
			a_sourceDataSize,
			a_partType,
			a_flags,
			a_part,
			a_partSize,
			a_newShader);
	}

	auto D3DStripShader(
		const void* a_sourceData,
		std::size_t a_sourceDataSize,
		std::uint32_t a_stripFlags,
		ID3DBlob** a_strippedBlob) noexcept -> HRESULT
	{
		return ::W32_IMPL_D3DStripShader(a_sourceData, a_sourceDataSize, a_stripFlags, a_strippedBlob);
	}

	auto D3DWriteBlobToFile(ID3DBlob* a_blob, const wchar_t* a_fileName, bool a_overwrite) noexcept -> HRESULT
	{
		return ::W32_IMPL_D3DWriteBlobToFile(a_blob, a_fileName, static_cast<REX::W32::BOOL>(a_overwrite));
	}
}

// DBGHELP

REX_W32_IMPORT(std::uint32_t, UnDecorateSymbolName, const char*, char*, std::uint32_t, std::uint32_t);
REX_W32_IMPORT(std::uint32_t, UnDecorateSymbolNameW, const wchar_t*, wchar_t*, std::uint32_t, std::uint32_t);

namespace REX::W32
{
	auto UnDecorateSymbolName(const char* a_name, char* a_buffer, std::uint32_t a_bufferLength, std::uint32_t a_flags)
		noexcept -> std::uint32_t
	{
		return ::W32_IMPL_UnDecorateSymbolName(a_name, a_buffer, a_bufferLength, a_flags);
	}

	auto UnDecorateSymbolNameW(
		const wchar_t* a_name,
		wchar_t* a_buffer,
		std::uint32_t a_bufferLength,
		std::uint32_t a_flags) noexcept -> std::uint32_t
	{
		return ::W32_IMPL_UnDecorateSymbolNameW(a_name, a_buffer, a_bufferLength, a_flags);
	}
}

// DXGI

REX_W32_IMPORT(std::int32_t, CreateDXGIFactory, const REX::W32::IID&, void**);
REX_W32_IMPORT(std::int32_t, CreateDXGIFactory1, const REX::W32::IID&, void**);

namespace REX::W32
{
	auto CreateDXGIFactory(const IID& a_iid, void** a_factory) noexcept -> HRESULT
	{
		return ::W32_IMPL_CreateDXGIFactory(a_iid, a_factory);
	}

	auto CreateDXGIFactory1(const IID& a_iid, void** a_factory) noexcept -> HRESULT
	{
		return ::W32_IMPL_CreateDXGIFactory1(a_iid, a_factory);
	}
}

// KERNEL32

REX_W32_IMPORT(void, AcquireSRWLockShared, REX::W32::SRWLOCK*);
REX_W32_IMPORT(void, AcquireSRWLockExclusive, REX::W32::SRWLOCK*);
REX_W32_IMPORT(REX::W32::BOOL, CloseHandle, REX::W32::HANDLE);
REX_W32_IMPORT(
	REX::W32::HANDLE,
	CreateFileA,
	const char*,
	std::uint32_t,
	std::uint32_t,
	REX::W32::SECURITY_ATTRIBUTES*,
	std::uint32_t,
	std::uint32_t,
	REX::W32::HANDLE);
REX_W32_IMPORT(
	REX::W32::HANDLE,
	CreateFileW,
	const wchar_t*,
	std::uint32_t,
	std::uint32_t,
	REX::W32::SECURITY_ATTRIBUTES*,
	std::uint32_t,
	std::uint32_t,
	REX::W32::HANDLE);
REX_W32_IMPORT(
	REX::W32::HANDLE,
	CreateFileMappingA,
	REX::W32::HANDLE,
	REX::W32::SECURITY_ATTRIBUTES*,
	std::uint32_t,
	std::uint32_t,
	std::uint32_t,
	const char*);
REX_W32_IMPORT(
	REX::W32::HANDLE,
	CreateFileMappingW,
	REX::W32::HANDLE,
	REX::W32::SECURITY_ATTRIBUTES*,
	std::uint32_t,
	std::uint32_t,
	std::uint32_t,
	const wchar_t*);
REX_W32_IMPORT(
	REX::W32::BOOL,
	CreateProcessA,
	const char*,
	char*,
	REX::W32::SECURITY_ATTRIBUTES*,
	REX::W32::SECURITY_ATTRIBUTES*,
	REX::W32::BOOL,
	std::uint32_t,
	void*,
	const char*,
	REX::W32::STARTUPINFOA*,
	REX::W32::PROCESS_INFORMATION*);
REX_W32_IMPORT(
	REX::W32::BOOL,
	CreateProcessW,
	const wchar_t*,
	wchar_t*,
	REX::W32::SECURITY_ATTRIBUTES*,
	REX::W32::SECURITY_ATTRIBUTES*,
	REX::W32::BOOL,
	std::uint32_t,
	void*,
	const wchar_t*,
	REX::W32::STARTUPINFOW*,
	REX::W32::PROCESS_INFORMATION*);
REX_W32_IMPORT_THROW(
	REX::W32::HANDLE,
	CreateRemoteThread,
	REX::W32::HANDLE,
	REX::W32::SECURITY_ATTRIBUTES*,
	std::size_t,
	REX::W32::THREAD_START_ROUTINE*,
	void*,
	std::uint32_t,
	std::uint32_t*);
REX_W32_IMPORT(
	REX::W32::HANDLE,
	CreateSemaphoreA,
	REX::W32::SECURITY_ATTRIBUTES*,
	std::int32_t,
	std::int32_t,
	const char*);
REX_W32_IMPORT_THROW(
	REX::W32::HANDLE,
	CreateThread,
	REX::W32::SECURITY_ATTRIBUTES*,
	std::size_t,
	REX::W32::THREAD_START_ROUTINE*,
	void*,
	std::uint32_t,
	std::uint32_t*);
REX_W32_IMPORT(void, DebugBreak);
REX_W32_IMPORT(void, DebugBreakProcess, REX::W32::HANDLE);
REX_W32_IMPORT(void, DeleteCriticalSection, REX::W32::CRITICAL_SECTION*);
REX_W32_IMPORT(void, EnterCriticalSection, REX::W32::CRITICAL_SECTION*);
REX_W32_IMPORT(void, ExitProcess, std::uint32_t);
REX_W32_IMPORT(std::uint32_t, ExpandEnvironmentStringsA, const char*, char*, std::uint32_t);
REX_W32_IMPORT(std::uint32_t, ExpandEnvironmentStringsW, const wchar_t*, wchar_t*, std::uint32_t);
REX_W32_IMPORT(REX::W32::BOOL, FindClose, REX::W32::HANDLE);
REX_W32_IMPORT(REX::W32::HANDLE, FindFirstFileA, const char*, REX::W32::WIN32_FIND_DATAA*);
REX_W32_IMPORT(REX::W32::HANDLE, FindFirstFileW, const wchar_t*, REX::W32::WIN32_FIND_DATAW*);
REX_W32_IMPORT(REX::W32::BOOL, FindNextFileA, REX::W32::HANDLE, REX::W32::WIN32_FIND_DATAA*);
REX_W32_IMPORT(REX::W32::BOOL, FindNextFileW, REX::W32::HANDLE, REX::W32::WIN32_FIND_DATAW*);
REX_W32_IMPORT(REX::W32::BOOL, FlushInstructionCache, REX::W32::HANDLE, const void*, std::size_t);
REX_W32_IMPORT(REX::W32::BOOL, FreeLibrary, REX::W32::HMODULE);
REX_W32_IMPORT(REX::W32::BOOL, GetComputerNameA, char*, std::uint32_t*);
REX_W32_IMPORT(REX::W32::BOOL, GetComputerNameW, wchar_t*, std::uint32_t*);
REX_W32_IMPORT(std::uint32_t, GetCurrentDirectoryA, std::uint32_t, char*);
REX_W32_IMPORT(std::uint32_t, GetCurrentDirectoryW, std::uint32_t, wchar_t*);
REX_W32_IMPORT(REX::W32::HANDLE, GetCurrentProcess);
REX_W32_IMPORT(REX::W32::THREAD_ID, GetCurrentThreadId);
REX_W32_IMPORT(std::uint32_t, GetEnvironmentVariableA, const char*, char*, std::uint32_t);
REX_W32_IMPORT(std::uint32_t, GetEnvironmentVariableW, const wchar_t*, wchar_t*, std::uint32_t);
REX_W32_IMPORT(std::uint32_t, GetFileSize, REX::W32::HANDLE, std::uint32_t*);
REX_W32_IMPORT(REX::W32::BOOL, GetFileSizeEx, REX::W32::HANDLE, std::int64_t*);
REX_W32_IMPORT(REX::W32::ERROR_CODE, GetLastError);
REX_W32_IMPORT(std::uint32_t, GetModuleFileNameA, REX::W32::HMODULE, char*, std::uint32_t);
REX_W32_IMPORT(std::uint32_t, GetModuleFileNameW, REX::W32::HMODULE, wchar_t*, std::uint32_t);
REX_W32_IMPORT(REX::W32::HMODULE, GetModuleHandleA, const char*);
REX_W32_IMPORT(REX::W32::HMODULE, GetModuleHandleW, const wchar_t*);
REX_W32_IMPORT(std::uint32_t, GetPrivateProfileIntA, const char*, const char*, std::int32_t, const char*);
REX_W32_IMPORT(std::uint32_t, GetPrivateProfileIntW, const wchar_t*, const wchar_t*, std::int32_t, const wchar_t*);
REX_W32_IMPORT(
	std::uint32_t,
	GetPrivateProfileStringA,
	const char*,
	const char*,
	const char*,
	char*,
	std::uint32_t,
	const char*);
REX_W32_IMPORT(
	std::uint32_t,
	GetPrivateProfileStringW,
	const wchar_t*,
	const wchar_t*,
	const wchar_t*,
	wchar_t*,
	std::uint32_t,
	const wchar_t*);
REX_W32_IMPORT(void*, GetProcAddress, REX::W32::HMODULE, const char*);
REX_W32_IMPORT(void, GetSystemInfo, REX::W32::SYSTEM_INFO*);
REX_W32_IMPORT(REX::W32::BOOL, GetUserNameA, char*, std::uint32_t*);
REX_W32_IMPORT(REX::W32::BOOL, GetUserNameW, wchar_t*, std::uint32_t*);
REX_W32_IMPORT(std::uint32_t, GetVersion);
REX_W32_IMPORT(void, InitializeCriticalSection, REX::W32::CRITICAL_SECTION*);
REX_W32_IMPORT(REX::W32::BOOL, InitializeCriticalSectionAndSpinCount, REX::W32::CRITICAL_SECTION*, std::uint32_t);
REX_W32_IMPORT(void, InitializeSRWLock, REX::W32::SRWLOCK*);
REX_W32_IMPORT(REX::W32::BOOL, IsDebuggerPresent);
REX_W32_IMPORT(
	std::int32_t,
	LCMapStringEx,
	const wchar_t*,
	std::uint32_t,
	const wchar_t*,
	std::int32_t,
	wchar_t*,
	std::int32_t,
	REX::W32::NLSVERSIONINFO*,
	void*,
	std::intptr_t);
REX_W32_IMPORT(void, LeaveCriticalSection, REX::W32::CRITICAL_SECTION*);
REX_W32_IMPORT(REX::W32::HMODULE, LoadLibraryA, const char*);
REX_W32_IMPORT(REX::W32::HMODULE, LoadLibraryW, const wchar_t*);
REX_W32_IMPORT(void*, MapViewOfFile, REX::W32::HANDLE, std::uint32_t, std::uint32_t, std::uint32_t, std::size_t);
REX_W32_IMPORT(
	void*,
	MapViewOfFileEx,
	REX::W32::HANDLE,
	std::uint32_t,
	std::uint32_t,
	std::uint32_t,
	std::size_t,
	void*);
REX_W32_IMPORT(
	std::int32_t,
	MultiByteToWideChar,
	std::uint32_t,
	std::uint32_t,
	const char*,
	std::int32_t,
	wchar_t*,
	std::int32_t);
REX_W32_IMPORT(REX::W32::HANDLE, OpenFileMappingA, std::uint32_t, REX::W32::BOOL, const char*);
REX_W32_IMPORT(REX::W32::HANDLE, OpenFileMappingW, std::uint32_t, REX::W32::BOOL, const wchar_t*);
REX_W32_IMPORT(void, OutputDebugStringA, const char*);
REX_W32_IMPORT(void, OutputDebugStringW, const wchar_t*);
REX_W32_IMPORT(REX::W32::BOOL, QueryPerformanceCounter, std::int64_t*);
REX_W32_IMPORT(REX::W32::BOOL, QueryPerformanceFrequency, std::int64_t*);
REX_W32_IMPORT(REX::W32::BOOL, ReadFile, REX::W32::HANDLE, void*, std::uint32_t, std::uint32_t*, REX::W32::OVERLAPPED*);
REX_W32_IMPORT(REX::W32::BOOL, ReleaseSemaphore, REX::W32::HANDLE, std::int32_t, std::int32_t*);
REX_W32_IMPORT(void, ReleaseSRWLockShared, REX::W32::SRWLOCK*);
REX_W32_IMPORT(void, ReleaseSRWLockExclusive, REX::W32::SRWLOCK*);
REX_W32_IMPORT(std::uint32_t, ResumeThread, REX::W32::HANDLE);
REX_W32_IMPORT(std::uint32_t, SetCriticalSectionSpinCount, REX::W32::CRITICAL_SECTION*, std::uint32_t);
REX_W32_IMPORT(REX::W32::BOOL, SetEndOfFile, REX::W32::HANDLE);
REX_W32_IMPORT(REX::W32::BOOL, SetEnvironmentVariableA, const char*, const char*);
REX_W32_IMPORT(REX::W32::BOOL, SetEnvironmentVariableW, const wchar_t*, const wchar_t*);
REX_W32_IMPORT(std::uint32_t, SetFilePointer, REX::W32::HANDLE, std::int32_t, std::int32_t*, std::uint32_t);
REX_W32_IMPORT(REX::W32::BOOL, SetFilePointerEx, REX::W32::HANDLE, std::int64_t, std::int64_t*, std::uint32_t);
REX_W32_IMPORT(void, SetLastError, REX::W32::ERROR_CODE);
REX_W32_IMPORT(void, Sleep, std::uint32_t);
REX_W32_IMPORT(REX::W32::BOOL, TerminateProcess, REX::W32::HANDLE, std::uint32_t);
REX_W32_IMPORT(void*, TlsGetValue, std::uint32_t);
REX_W32_IMPORT(REX::W32::BOOL, TlsSetValue, std::uint32_t, void*);
REX_W32_IMPORT(REX::W32::BOOL, TryAcquireSRWLockExclusive, REX::W32::SRWLOCK*);
REX_W32_IMPORT(REX::W32::BOOL, TryAcquireSRWLockShared, REX::W32::SRWLOCK*);
REX_W32_IMPORT(REX::W32::BOOL, TryEnterCriticalSection, REX::W32::CRITICAL_SECTION*);
REX_W32_IMPORT(REX::W32::BOOL, UnmapViewOfFile, const void*);
REX_W32_IMPORT(void*, VirtualAlloc, void*, std::size_t, std::uint32_t, std::uint32_t);
REX_W32_IMPORT(void*, VirtualAllocEx, REX::W32::HANDLE, void*, std::size_t, std::uint32_t, std::uint32_t);
REX_W32_IMPORT(REX::W32::BOOL, VirtualFree, void*, std::size_t, std::uint32_t);
REX_W32_IMPORT(REX::W32::BOOL, VirtualFreeEx, REX::W32::HANDLE, void*, std::size_t, std::uint32_t);
REX_W32_IMPORT(REX::W32::BOOL, VirtualProtect, void*, std::size_t, std::uint32_t, std::uint32_t*);
REX_W32_IMPORT(REX::W32::BOOL, VirtualProtectEx, REX::W32::HANDLE, void*, std::size_t, std::uint32_t, std::uint32_t*);
REX_W32_IMPORT(std::size_t, VirtualQuery, const void*, REX::W32::MEMORY_BASIC_INFORMATION*, std::size_t);
REX_W32_IMPORT(
	std::size_t,
	VirtualQueryEx,
	REX::W32::HANDLE,
	const void*,
	REX::W32::MEMORY_BASIC_INFORMATION*,
	std::size_t);
REX_W32_IMPORT(std::uint32_t, WaitForSingleObject, REX::W32::HANDLE, std::uint32_t);
REX_W32_IMPORT(std::uint32_t, WaitForSingleObjectEx, REX::W32::HANDLE, std::uint32_t, REX::W32::BOOL);
REX_W32_IMPORT(
	std::int32_t,
	WideCharToMultiByte,
	std::uint32_t,
	std::uint32_t,
	const wchar_t*,
	std::int32_t,
	char*,
	std::int32_t,
	const char*,
	std::int32_t*);
REX_W32_IMPORT(
	REX::W32::BOOL,
	WriteFile,
	REX::W32::HANDLE,
	const void*,
	std::uint32_t,
	std::uint32_t*,
	REX::W32::OVERLAPPED*);
REX_W32_IMPORT(REX::W32::BOOL, WriteProcessMemory, REX::W32::HANDLE, void*, const void*, std::size_t, std::size_t*);

extern "C" REX::W32::IMAGE_DOS_HEADER __ImageBase;

namespace REX::W32
{
	void AcquireSRWLockShared(SRWLOCK* a_lock) noexcept
	{
		::W32_IMPL_AcquireSRWLockShared(a_lock);
	}

	void AcquireSRWLockExclusive(SRWLOCK* a_lock) noexcept
	{
		::W32_IMPL_AcquireSRWLockExclusive(a_lock);
	}

	auto CloseHandle(HANDLE a_handle) noexcept -> bool
	{
		return ::W32_IMPL_CloseHandle(a_handle) == REX::W32::TRUE;
	}

	auto CreateFileA(
		const char* a_fileName,
		std::uint32_t a_desiredAccess,
		std::uint32_t a_shareMode,
		SECURITY_ATTRIBUTES* a_attributes,
		std::uint32_t a_creationDisposition,
		std::uint32_t a_flags,
		HANDLE a_templateFile) noexcept -> HANDLE
	{
		return ::W32_IMPL_CreateFileA(
			a_fileName,
			a_desiredAccess,
			a_shareMode,
			a_attributes,
			a_creationDisposition,
			a_flags,
			a_templateFile);
	}

	auto CreateFileW(
		const wchar_t* a_fileName,
		std::uint32_t a_desiredAccess,
		std::uint32_t a_shareMode,
		SECURITY_ATTRIBUTES* a_attributes,
		std::uint32_t a_creationDisposition,
		std::uint32_t a_flags,
		HANDLE a_templateFile) noexcept -> HANDLE
	{
		return ::W32_IMPL_CreateFileW(
			a_fileName,
			a_desiredAccess,
			a_shareMode,
			a_attributes,
			a_creationDisposition,
			a_flags,
			a_templateFile);
	}

	auto CreateFileMappingA(
		HANDLE a_file,
		SECURITY_ATTRIBUTES* a_attributes,
		std::uint32_t a_protect,
		std::uint64_t a_maxSize,
		const char* a_name) noexcept -> HANDLE
	{
		return ::W32_IMPL_CreateFileMappingA(
			a_file,
			a_attributes,
			a_protect,
			REX::CheckedReinterpretCast<REX::W32::ULARGE_INTEGER&>(a_maxSize).highPart,
			REX::CheckedReinterpretCast<REX::W32::ULARGE_INTEGER&>(a_maxSize).lowPart,
			a_name);
	}

	auto CreateFileMappingW(
		HANDLE a_file,
		SECURITY_ATTRIBUTES* a_attributes,
		std::uint32_t a_protect,
		std::uint64_t a_maxSize,
		const wchar_t* a_name) noexcept -> HANDLE
	{
		return ::W32_IMPL_CreateFileMappingW(
			a_file,
			a_attributes,
			a_protect,
			REX::CheckedReinterpretCast<REX::W32::ULARGE_INTEGER&>(a_maxSize).highPart,
			REX::CheckedReinterpretCast<REX::W32::ULARGE_INTEGER&>(a_maxSize).lowPart,
			a_name);
	}

	auto CreateProcessA(
		const char* a_name,
		char* a_cmd,
		SECURITY_ATTRIBUTES* a_procAttr,
		SECURITY_ATTRIBUTES* a_threadAttr,
		bool a_inheritHandles,
		std::uint32_t a_flags,
		void* a_env,
		const char* a_curDir,
		STARTUPINFOA* a_startInfo,
		PROCESS_INFORMATION* a_procInfo) noexcept -> bool
	{
		return ::W32_IMPL_CreateProcessA(
				   a_name,
				   a_cmd,
				   a_procAttr,
				   a_threadAttr,
				   static_cast<BOOL>(a_inheritHandles),
				   a_flags,
				   a_env,
				   a_curDir,
				   a_startInfo,
				   a_procInfo) == REX::W32::TRUE;
	}

	auto CreateProcessW(
		const wchar_t* a_name,
		wchar_t* a_cmd,
		SECURITY_ATTRIBUTES* a_procAttr,
		SECURITY_ATTRIBUTES* a_threadAttr,
		bool a_inheritHandles,
		std::uint32_t a_flags,
		void* a_env,
		const wchar_t* a_curDir,
		STARTUPINFOW* a_startInfo,
		PROCESS_INFORMATION* a_procInfo) noexcept -> bool
	{
		return ::W32_IMPL_CreateProcessW(
				   a_name,
				   a_cmd,
				   a_procAttr,
				   a_threadAttr,
				   static_cast<BOOL>(a_inheritHandles),
				   a_flags,
				   a_env,
				   a_curDir,
				   a_startInfo,
				   a_procInfo) == REX::W32::TRUE;
	}

	auto CreateRemoteThread(
		HANDLE a_process,
		SECURITY_ATTRIBUTES* a_threadAttr,
		std::size_t a_stackSize,
		THREAD_START_ROUTINE* a_startAddr,
		void* a_param,
		std::uint32_t a_flags,
		std::uint32_t* a_threadID) -> HANDLE
	{
		return ::W32_IMPL_CreateRemoteThread(
			a_process,
			a_threadAttr,
			a_stackSize,
			a_startAddr,
			a_param,
			a_flags,
			a_threadID);
	}

	auto CreateSemaphoreA(
		SECURITY_ATTRIBUTES* a_semaphoreAttr,
		std::int32_t a_initCount,
		std::int32_t a_maxCount,
		const char* a_name) noexcept -> HANDLE
	{
		return ::W32_IMPL_CreateSemaphoreA(a_semaphoreAttr, a_initCount, a_maxCount, a_name);
	}

	auto CreateThread(
		SECURITY_ATTRIBUTES* a_threadAttr,
		std::size_t a_stackSize,
		THREAD_START_ROUTINE* a_startAddr,
		void* a_param,
		std::uint32_t a_flags,
		std::uint32_t* a_threadID) -> HANDLE
	{
		return ::W32_IMPL_CreateThread(a_threadAttr, a_stackSize, a_startAddr, a_param, a_flags, a_threadID);
	}

	void DebugBreak() noexcept
	{
		::W32_IMPL_DebugBreak();
	}

	void DebugBreakProcess(HANDLE a_process) noexcept
	{
		::W32_IMPL_DebugBreakProcess(a_process);
	}

	void DeleteCriticalSection(CRITICAL_SECTION* a_criticalSection) noexcept
	{
		::W32_IMPL_DeleteCriticalSection(a_criticalSection);
	}

	void EnterCriticalSection(CRITICAL_SECTION* a_criticalSection) noexcept
	{
		::W32_IMPL_EnterCriticalSection(a_criticalSection);
	}

	void ExitProcess(std::uint32_t a_exitCode) noexcept
	{
		::W32_IMPL_ExitProcess(a_exitCode);
		std::unreachable();
	}

	auto ExpandEnvironmentStringsA(const char* a_source, char* a_target, std::uint32_t a_targetLength) noexcept
		-> std::uint32_t
	{
		return ::W32_IMPL_ExpandEnvironmentStringsA(a_source, a_target, a_targetLength);
	}

	auto ExpandEnvironmentStringsW(const wchar_t* a_source, wchar_t* a_target, std::uint32_t a_targetLength) noexcept
		-> std::uint32_t
	{
		return ::W32_IMPL_ExpandEnvironmentStringsW(a_source, a_target, a_targetLength);
	}

	auto FindClose(HANDLE a_file) noexcept -> bool
	{
		return ::W32_IMPL_FindClose(a_file) == REX::W32::TRUE;
	}

	auto FindFirstFileA(const char* a_name, WIN32_FIND_DATAA* a_data) noexcept -> HANDLE
	{
		return ::W32_IMPL_FindFirstFileA(a_name, a_data);
	}

	auto FindFirstFileW(const wchar_t* a_name, WIN32_FIND_DATAW* a_data) noexcept -> HANDLE
	{
		return ::W32_IMPL_FindFirstFileW(a_name, a_data);
	}

	auto FindNextFileA(HANDLE a_file, WIN32_FIND_DATAA* a_data) noexcept -> bool
	{
		return ::W32_IMPL_FindNextFileA(a_file, a_data) == REX::W32::TRUE;
	}

	auto FindNextFileW(HANDLE a_file, WIN32_FIND_DATAW* a_data) noexcept -> bool
	{
		return ::W32_IMPL_FindNextFileW(a_file, a_data) == REX::W32::TRUE;
	}

	auto FlushInstructionCache(HANDLE a_process, const void* a_baseAddr, std::size_t a_size) noexcept -> bool
	{
		return ::W32_IMPL_FlushInstructionCache(a_process, a_baseAddr, a_size) == REX::W32::TRUE;
	}

	auto FreeLibrary(HMODULE a_module) noexcept -> bool
	{
		return ::W32_IMPL_FreeLibrary(a_module) == REX::W32::TRUE;
	}

	auto GetComputerNameA(char* a_buffer, std::uint32_t* a_size) noexcept -> bool
	{
		return ::W32_IMPL_GetComputerNameA(a_buffer, a_size) == REX::W32::TRUE;
	}

	auto GetComputerNameW(wchar_t* a_buffer, std::uint32_t* a_size) noexcept -> bool
	{
		return ::W32_IMPL_GetComputerNameW(a_buffer, a_size) == REX::W32::TRUE;
	}

	auto GetCurrentDirectoryA(std::uint32_t a_size, char* a_buffer) noexcept -> std::uint32_t
	{
		return ::W32_IMPL_GetCurrentDirectoryA(a_size, a_buffer);
	}

	auto GetCurrentDirectoryW(std::uint32_t a_size, wchar_t* a_buffer) noexcept -> std::uint32_t
	{
		return ::W32_IMPL_GetCurrentDirectoryW(a_size, a_buffer);
	}

	auto GetCurrentModule() noexcept -> HMODULE
	{
		return std::bit_cast<HMODULE>(std::addressof(__ImageBase));
	}

	auto GetCurrentProcess() noexcept -> HANDLE
	{
		return ::W32_IMPL_GetCurrentProcess();
	}

	auto GetCurrentThreadId() noexcept -> THREAD_ID
	{
		return ::W32_IMPL_GetCurrentThreadId();
	}

	auto GetEnvironmentVariableA(const char* a_name, char* a_buffer, std::uint32_t a_bufferLength) noexcept
		-> std::uint32_t
	{
		return ::W32_IMPL_GetEnvironmentVariableA(a_name, a_buffer, a_bufferLength);
	}

	auto GetEnvironmentVariableW(const wchar_t* a_name, wchar_t* a_buffer, std::uint32_t a_bufferLength) noexcept
		-> std::uint32_t
	{
		return ::W32_IMPL_GetEnvironmentVariableW(a_name, a_buffer, a_bufferLength);
	}

	auto GetFileSize(HANDLE a_file, std::uint32_t* a_fileSizeHigh) noexcept -> std::uint32_t
	{
		return ::W32_IMPL_GetFileSize(a_file, a_fileSizeHigh);
	}

	auto GetFileSizeEx(HANDLE a_file, std::int64_t* a_fileSize) noexcept -> bool
	{
		return ::W32_IMPL_GetFileSizeEx(a_file, a_fileSize) == REX::W32::TRUE;
	}

	auto GetLastError() noexcept -> ERROR_CODE
	{
		return ::W32_IMPL_GetLastError();
	}

	auto GetModuleFileNameA(HMODULE a_module, char* a_name, std::uint32_t a_nameLength) noexcept -> std::uint32_t
	{
		return ::W32_IMPL_GetModuleFileNameA(a_module, a_name, a_nameLength);
	}

	auto GetModuleFileNameW(HMODULE a_module, wchar_t* a_name, std::uint32_t a_nameLength) noexcept -> std::uint32_t
	{
		return ::W32_IMPL_GetModuleFileNameW(a_module, a_name, a_nameLength);
	}

	auto GetModuleHandleA(const char* a_name) noexcept -> HMODULE
	{
		return ::W32_IMPL_GetModuleHandleA(a_name);
	}

	auto GetModuleHandleW(const wchar_t* a_name) noexcept -> HMODULE
	{
		return ::W32_IMPL_GetModuleHandleW(a_name);
	}

	auto GetParentModule() noexcept -> HMODULE
	{
		return GetModuleHandleA(nullptr);
	}

	auto GetPrivateProfileIntA(const char* a_app, const char* a_key, std::int32_t a_default, const char* a_name)
		noexcept -> std::uint32_t
	{
		return ::W32_IMPL_GetPrivateProfileIntA(a_app, a_key, a_default, a_name);
	}

	auto GetPrivateProfileIntW(
		const wchar_t* a_app,
		const wchar_t* a_key,
		std::int32_t a_default,
		const wchar_t* a_name) noexcept -> std::uint32_t
	{
		return ::W32_IMPL_GetPrivateProfileIntW(a_app, a_key, a_default, a_name);
	}

	auto GetPrivateProfileStringA(
		const char* a_app,
		const char* a_key,
		const char* a_default,
		char* a_buffer,
		std::uint32_t a_bufferLength,
		const char* a_name) noexcept -> std::uint32_t
	{
		return ::W32_IMPL_GetPrivateProfileStringA(a_app, a_key, a_default, a_buffer, a_bufferLength, a_name);
	}

	auto GetPrivateProfileStringW(
		const wchar_t* a_app,
		const wchar_t* a_key,
		const wchar_t* a_default,
		wchar_t* a_buffer,
		std::uint32_t a_bufferLength,
		const wchar_t* a_name) noexcept -> std::uint32_t
	{
		return ::W32_IMPL_GetPrivateProfileStringW(a_app, a_key, a_default, a_buffer, a_bufferLength, a_name);
	}

	auto GetProcAddress(HMODULE a_module, const char* a_name) noexcept -> void*
	{
		return ::W32_IMPL_GetProcAddress(a_module, a_name);
	}

	void GetSystemInfo(SYSTEM_INFO* a_info) noexcept
	{
		::W32_IMPL_GetSystemInfo(a_info);
	}

	auto GetUserNameA(char* a_buffer, std::uint32_t* a_size) noexcept -> bool
	{
		return ::W32_IMPL_GetUserNameA(a_buffer, a_size) == REX::W32::TRUE;
	}

	auto GetUserNameW(wchar_t* a_buffer, std::uint32_t* a_size) noexcept -> bool
	{
		return ::W32_IMPL_GetUserNameW(a_buffer, a_size) == REX::W32::TRUE;
	}

	auto GetVersion() noexcept -> std::uint32_t
	{
		return ::W32_IMPL_GetVersion();
	}

	auto IMAGE_SNAP_BY_ORDINAL64(std::uint64_t a_ordinal) noexcept -> bool
	{
		return (a_ordinal & IMAGE_ORDINAL_FLAG64) != 0;
	}

	auto IMAGE_FIRST_SECTION(const IMAGE_NT_HEADERS64* a_header) noexcept -> IMAGE_SECTION_HEADER*
	{
		constexpr auto HEADER_OFFSET = offsetof(IMAGE_NT_HEADERS64, optionalHeader);

		const auto headerSize = a_header->fileHeader.optionalHeaderSize;
		const auto headerSection = std::bit_cast<std::uintptr_t>(a_header) + HEADER_OFFSET + headerSize;
		return std::bit_cast<IMAGE_SECTION_HEADER*>(headerSection);
	}

	void InitializeCriticalSection(CRITICAL_SECTION* a_criticalSection) noexcept
	{
		::W32_IMPL_InitializeCriticalSection(a_criticalSection);
	}

	auto InitializeCriticalSectionAndSpinCount(CRITICAL_SECTION* a_criticalSection, std::uint32_t a_spinCount) noexcept
		-> bool
	{
		return ::W32_IMPL_InitializeCriticalSectionAndSpinCount(a_criticalSection, a_spinCount) == REX::W32::TRUE;
	}

	void InitializeSRWLock(SRWLOCK* a_lock) noexcept
	{
		::W32_IMPL_InitializeSRWLock(a_lock);
	}

	// NOLINTBEGIN(google-runtime-int)

	auto InterlockedAnd(volatile std::int32_t* a_target, std::int32_t a_value) noexcept -> std::int32_t
	{
		return ::_InterlockedAnd(REX::CheckedReinterpretCast<volatile long*>(a_target), a_value);
	}

	auto InterlockedAnd8(volatile std::int8_t* a_target, std::int8_t a_value) noexcept -> std::int8_t
	{
		return ::_InterlockedAnd8(REX::CheckedReinterpretCast<volatile char*>(a_target), a_value);
	}

	auto InterlockedAnd16(volatile std::int16_t* a_target, std::int16_t a_value) noexcept -> std::int16_t
	{
		return ::_InterlockedAnd16(a_target, a_value);
	}

	auto InterlockedAnd64(volatile std::int64_t* a_target, std::int64_t a_value) noexcept -> std::int64_t
	{
		return ::_InterlockedAnd64(a_target, a_value);
	}

	auto InterlockedDecrement(volatile std::int32_t* a_target) noexcept -> std::int32_t
	{
		return ::_InterlockedDecrement(REX::CheckedReinterpretCast<volatile long*>(a_target));
	}

	auto InterlockedDecrement16(volatile std::int16_t* a_target) noexcept -> std::int16_t
	{
		return ::_InterlockedDecrement16(a_target);
	}

	auto InterlockedDecrement64(volatile std::int64_t* a_target) noexcept -> std::int64_t
	{
		return ::_InterlockedDecrement64(a_target);
	}

	auto InterlockedCompareExchange(volatile std::int32_t* a_target, std::int32_t a_value, std::int32_t a_compare)
		noexcept -> std::int32_t
	{
		return ::_InterlockedCompareExchange(REX::CheckedReinterpretCast<volatile long*>(a_target), a_value, a_compare);
	}

	auto InterlockedCompareExchange8(volatile std::int8_t* a_target, std::int8_t a_value, std::int8_t a_compare)
		noexcept -> std::int8_t
	{
		return ::_InterlockedCompareExchange8(
			REX::CheckedReinterpretCast<volatile char*>(a_target),
			a_value,
			a_compare);
	}

	auto InterlockedCompareExchange16(volatile std::int16_t* a_target, std::int16_t a_value, std::int16_t a_compare)
		noexcept -> std::int16_t
	{
		return ::_InterlockedCompareExchange16(a_target, a_value, a_compare);
	}

	auto InterlockedCompareExchange64(volatile std::int64_t* a_target, std::int64_t a_value, std::int64_t a_compare)
		noexcept -> std::int64_t
	{
		return ::_InterlockedCompareExchange64(a_target, a_value, a_compare);
	}

	auto InterlockedCompareExchangePointer(void* volatile* a_target, void* a_value, void* a_compare) noexcept -> void*
	{
		return ::_InterlockedCompareExchangePointer(a_target, a_value, a_compare);
	}

	auto InterlockedExchange(volatile std::int32_t* a_target, std::int32_t a_value) noexcept -> std::int32_t
	{
		return ::_InterlockedExchange(REX::CheckedReinterpretCast<volatile long*>(a_target), a_value);
	}

	auto InterlockedExchange8(volatile std::int8_t* a_target, std::int8_t a_value) noexcept -> std::int8_t
	{
		return ::_InterlockedExchange8(REX::CheckedReinterpretCast<volatile char*>(a_target), a_value);
	}

	auto InterlockedExchange16(volatile std::int16_t* a_target, std::int16_t a_value) noexcept -> std::int16_t
	{
		return ::_InterlockedExchange16(a_target, a_value);
	}

	auto InterlockedExchange64(volatile std::int64_t* a_target, std::int64_t a_value) noexcept -> std::int64_t
	{
		return ::_InterlockedExchange64(a_target, a_value);
	}

	auto InterlockedExchangeAdd(volatile std::int32_t* a_target, std::int32_t a_value) noexcept -> std::int32_t
	{
		return ::_InterlockedExchangeAdd(REX::CheckedReinterpretCast<volatile long*>(a_target), a_value);
	}

	auto InterlockedExchangeAdd8(volatile std::int8_t* a_target, std::int8_t a_value) noexcept -> std::int8_t
	{
		return ::_InterlockedExchangeAdd8(REX::CheckedReinterpretCast<volatile char*>(a_target), a_value);
	}

	auto InterlockedExchangeAdd16(volatile std::int16_t* a_target, std::int16_t a_value) noexcept -> std::int16_t
	{
		return ::_InterlockedExchangeAdd16(a_target, a_value);
	}

	auto InterlockedExchangeAdd64(volatile std::int64_t* a_target, std::int64_t a_value) noexcept -> std::int64_t
	{
		return ::_InterlockedExchangeAdd64(a_target, a_value);
	}

	auto InterlockedExchangePointer(void* volatile* a_target, void* a_value) noexcept -> void*
	{
		return ::_InterlockedExchangePointer(a_target, a_value);
	}

	auto InterlockedIncrement(volatile std::int32_t* a_target) noexcept -> std::int32_t
	{
		return ::_InterlockedIncrement(REX::CheckedReinterpretCast<volatile long*>(a_target));
	}

	auto InterlockedIncrement16(volatile std::int16_t* a_target) noexcept -> std::int16_t
	{
		return ::_InterlockedIncrement16(a_target);
	}

	auto InterlockedIncrement64(volatile std::int64_t* a_target) noexcept -> std::int64_t
	{
		return ::_InterlockedIncrement64(a_target);
	}

	auto InterlockedOr(volatile std::int32_t* a_target, std::int32_t a_value) noexcept -> std::int32_t
	{
		return ::_InterlockedOr(REX::CheckedReinterpretCast<volatile long*>(a_target), a_value);
	}

	auto InterlockedOr8(volatile std::int8_t* a_target, std::int8_t a_value) noexcept -> std::int8_t
	{
		return ::_InterlockedOr8(REX::CheckedReinterpretCast<volatile char*>(a_target), a_value);
	}

	auto InterlockedOr16(volatile std::int16_t* a_target, std::int16_t a_value) noexcept -> std::int16_t
	{
		return ::_InterlockedOr16(a_target, a_value);
	}

	auto InterlockedOr64(volatile std::int64_t* a_target, std::int64_t a_value) noexcept -> std::int64_t
	{
		return ::_InterlockedOr64(a_target, a_value);
	}

	auto InterlockedXor(volatile std::int32_t* a_target, std::int32_t a_value) noexcept -> std::int32_t
	{
		return ::_InterlockedXor(REX::CheckedReinterpretCast<volatile long*>(a_target), a_value);
	}

	auto InterlockedXor8(volatile std::int8_t* a_target, std::int8_t a_value) noexcept -> std::int8_t
	{
		return ::_InterlockedXor8(REX::CheckedReinterpretCast<volatile char*>(a_target), a_value);
	}

	auto InterlockedXor16(volatile std::int16_t* a_target, std::int16_t a_value) noexcept -> std::int16_t
	{
		return ::_InterlockedXor16(a_target, a_value);
	}

	auto InterlockedXor64(volatile std::int64_t* a_target, std::int64_t a_value) noexcept -> std::int64_t
	{
		return ::_InterlockedXor64(a_target, a_value);
	}

	// NOLINTEND(google-runtime-int)

	auto IsDebuggerPresent() noexcept -> bool
	{
		return ::W32_IMPL_IsDebuggerPresent() == REX::W32::TRUE;
	}

	auto LCMapStringEx(
		const wchar_t* a_locale,
		std::uint32_t a_flags,
		const wchar_t* a_source,
		std::int32_t a_sourceLength,
		wchar_t* a_target,
		std::int32_t a_targetLength,
		NLSVERSIONINFO* a_info,
		void* a_reserved,
		std::intptr_t a_sortHandle) noexcept -> std::int32_t
	{
		return ::W32_IMPL_LCMapStringEx(
			a_locale,
			a_flags,
			a_source,
			a_sourceLength,
			a_target,
			a_targetLength,
			a_info,
			a_reserved,
			a_sortHandle);
	}

	void LeaveCriticalSection(CRITICAL_SECTION* a_criticalSection) noexcept
	{
		::W32_IMPL_LeaveCriticalSection(a_criticalSection);
	}

	auto LoadLibraryA(const char* a_name) noexcept -> HMODULE
	{
		return ::W32_IMPL_LoadLibraryA(a_name);
	}

	auto LoadLibraryW(const wchar_t* a_name) noexcept -> HMODULE
	{
		return ::W32_IMPL_LoadLibraryW(a_name);
	}

	auto MapViewOfFile(
		HANDLE a_object,
		std::uint32_t a_desiredAccess,
		std::uint64_t a_fileOffset,
		std::size_t a_numBytes) noexcept -> void*
	{
		return ::W32_IMPL_MapViewOfFile(
			a_object,
			a_desiredAccess,
			REX::CheckedReinterpretCast<REX::W32::ULARGE_INTEGER&>(a_fileOffset).highPart,
			REX::CheckedReinterpretCast<REX::W32::ULARGE_INTEGER&>(a_fileOffset).lowPart,
			a_numBytes);
	}

	auto MapViewOfFileEx(
		HANDLE a_object,
		std::uint32_t a_desiredAccess,
		std::uint64_t a_fileOffset,
		std::size_t a_numBytes,
		void* a_baseAddr) noexcept -> void*
	{
		return ::W32_IMPL_MapViewOfFileEx(
			a_object,
			a_desiredAccess,
			REX::CheckedReinterpretCast<REX::W32::ULARGE_INTEGER&>(a_fileOffset).highPart,
			REX::CheckedReinterpretCast<REX::W32::ULARGE_INTEGER&>(a_fileOffset).lowPart,
			a_numBytes,
			a_baseAddr);
	}

	auto MultiByteToWideChar(
		std::uint32_t a_codePage,
		std::uint32_t a_flags,
		const char* a_source,
		std::int32_t a_sourceLength,
		wchar_t* a_target,
		std::int32_t a_targetLength) noexcept -> std::int32_t
	{
		return ::W32_IMPL_MultiByteToWideChar(a_codePage, a_flags, a_source, a_sourceLength, a_target, a_targetLength);
	}

	auto OpenFileMappingA(std::uint32_t a_desiredAccess, bool a_inheritHandle, const char* a_name) noexcept -> HANDLE
	{
		return ::W32_IMPL_OpenFileMappingA(a_desiredAccess, static_cast<BOOL>(a_inheritHandle), a_name);
	}

	auto OpenFileMappingW(std::uint32_t a_desiredAccess, bool a_inheritHandle, const wchar_t* a_name) noexcept -> HANDLE
	{
		return ::W32_IMPL_OpenFileMappingW(a_desiredAccess, static_cast<BOOL>(a_inheritHandle), a_name);
	}

	void OutputDebugStringA(const char* a_str) noexcept
	{
		::W32_IMPL_OutputDebugStringA(a_str);
	}

	void OutputDebugStringW(const wchar_t* a_str) noexcept
	{
		::W32_IMPL_OutputDebugStringW(a_str);
	}

	auto QueryPerformanceCounter(std::int64_t* a_counter) noexcept -> bool
	{
		return ::W32_IMPL_QueryPerformanceCounter(a_counter) == REX::W32::TRUE;
	}

	auto QueryPerformanceFrequency(std::int64_t* a_frequency) noexcept -> bool
	{
		return ::W32_IMPL_QueryPerformanceFrequency(a_frequency) == REX::W32::TRUE;
	}

	auto ReadFile(
		HANDLE a_file,
		void* a_buffer,
		std::uint32_t a_bytesToRead,
		std::uint32_t* a_bytesRead,
		OVERLAPPED* a_overlapped) noexcept -> bool
	{
		return ::W32_IMPL_ReadFile(a_file, a_buffer, a_bytesToRead, a_bytesRead, a_overlapped) == REX::W32::TRUE;
	}

	auto ReleaseSemaphore(HANDLE a_semaphore, std::int32_t a_releaseCount, std::int32_t* a_previousCount) noexcept
		-> bool
	{
		return ::W32_IMPL_ReleaseSemaphore(a_semaphore, a_releaseCount, a_previousCount) == REX::W32::TRUE;
	}

	void ReleaseSRWLockShared(SRWLOCK* a_lock) noexcept
	{
		::W32_IMPL_ReleaseSRWLockShared(a_lock);
	}

	void ReleaseSRWLockExclusive(SRWLOCK* a_lock) noexcept
	{
		::W32_IMPL_ReleaseSRWLockExclusive(a_lock);
	}

	auto ResumeThread(HANDLE a_handle) noexcept -> std::uint32_t
	{
		return ::W32_IMPL_ResumeThread(a_handle);
	}

	auto SetCriticalSectionSpinCount(CRITICAL_SECTION* a_criticalSection, std::uint32_t a_spinCount) noexcept
		-> std::uint32_t
	{
		return ::W32_IMPL_SetCriticalSectionSpinCount(a_criticalSection, a_spinCount);
	}

	auto SetEndOfFile(HANDLE a_file) noexcept -> bool
	{
		return ::W32_IMPL_SetEndOfFile(a_file) == REX::W32::TRUE;
	}

	auto SetEnvironmentVariableA(const char* a_name, const char* a_value) noexcept -> bool
	{
		return ::W32_IMPL_SetEnvironmentVariableA(a_name, a_value) == REX::W32::TRUE;
	}

	auto SetEnvironmentVariableW(const wchar_t* a_name, const wchar_t* a_value) noexcept -> bool
	{
		return ::W32_IMPL_SetEnvironmentVariableW(a_name, a_value) == REX::W32::TRUE;
	}

	auto SetFilePointer(HANDLE a_file, std::int32_t a_distance, std::int32_t* a_distanceHigh, std::uint32_t a_method)
		noexcept -> std::uint32_t
	{
		return ::W32_IMPL_SetFilePointer(a_file, a_distance, a_distanceHigh, a_method);
	}

	auto SetFilePointerEx(
		HANDLE a_file,
		std::int64_t a_distance,
		std::int64_t* a_newFilePointer,
		std::uint32_t a_method) noexcept -> bool
	{
		return ::W32_IMPL_SetFilePointerEx(a_file, a_distance, a_newFilePointer, a_method) == REX::W32::TRUE;
	}

	void SetLastError(ERROR_CODE a_error) noexcept
	{
		::W32_IMPL_SetLastError(a_error);
	}

	void Sleep(std::uint32_t a_milliseconds) noexcept
	{
		::W32_IMPL_Sleep(a_milliseconds);
	}

	void TerminateCurrentProcess(std::uint32_t a_exitCode) noexcept
	{
		if (!TerminateProcess(GetCurrentProcess(), a_exitCode)) [[unlikely]] {
			std::terminate();
		}

		std::unreachable();
	}

	auto TerminateProcess(HANDLE a_process, std::uint32_t a_exitCode) noexcept -> bool
	{
		return ::W32_IMPL_TerminateProcess(a_process, a_exitCode) == REX::W32::TRUE;
	}

	auto TlsGetValue(std::uint32_t a_index) noexcept -> void*
	{
		return ::W32_IMPL_TlsGetValue(a_index);
	}

	auto TlsSetValue(std::uint32_t a_index, void* a_value) noexcept -> bool
	{
		return ::W32_IMPL_TlsSetValue(a_index, a_value) == REX::W32::TRUE;
	}

	auto TryAcquireSRWLockExclusive(SRWLOCK* a_lock) noexcept -> bool
	{
		return ::W32_IMPL_TryAcquireSRWLockExclusive(a_lock) == REX::W32::TRUE;
	}

	auto TryAcquireSRWLockShared(SRWLOCK* a_lock) noexcept -> bool
	{
		return ::W32_IMPL_TryAcquireSRWLockShared(a_lock) == REX::W32::TRUE;
	}

	auto TryEnterCriticalSection(CRITICAL_SECTION* a_criticalSection) noexcept -> bool
	{
		return ::W32_IMPL_TryEnterCriticalSection(a_criticalSection) == REX::W32::TRUE;
	}

	auto UnmapViewOfFile(const void* a_baseAddress) noexcept -> bool
	{
		return ::W32_IMPL_UnmapViewOfFile(a_baseAddress) == REX::W32::TRUE;
	}

	auto VirtualAlloc(void* a_address, std::size_t a_size, std::uint32_t a_type, std::uint32_t a_protect) noexcept
		-> void*
	{
		return ::W32_IMPL_VirtualAlloc(a_address, a_size, a_type, a_protect);
	}

	auto VirtualAllocEx(
		HANDLE a_process,
		void* a_address,
		std::size_t a_size,
		std::uint32_t a_type,
		std::uint32_t a_protect) noexcept -> void*
	{
		return ::W32_IMPL_VirtualAllocEx(a_process, a_address, a_size, a_type, a_protect);
	}

	auto VirtualFree(void* a_address, std::size_t a_size, std::uint32_t a_type) noexcept -> bool
	{
		return ::W32_IMPL_VirtualFree(a_address, a_size, a_type) == REX::W32::TRUE;
	}

	auto VirtualFreeEx(HANDLE a_process, void* a_address, std::size_t a_size, std::uint32_t a_type) noexcept -> bool
	{
		return ::W32_IMPL_VirtualFreeEx(a_process, a_address, a_size, a_type) == REX::W32::TRUE;
	}

	auto VirtualProtect(void* a_address, std::size_t a_size, std::uint32_t a_newProtect, std::uint32_t* a_oldProtect)
		noexcept -> bool
	{
		return ::W32_IMPL_VirtualProtect(a_address, a_size, a_newProtect, a_oldProtect) == REX::W32::TRUE;
	}

	auto VirtualProtectEx(
		HANDLE a_process,
		void* a_address,
		std::size_t a_size,
		std::uint32_t a_newProtect,
		std::uint32_t* a_oldProtect) noexcept -> bool
	{
		return ::W32_IMPL_VirtualProtectEx(a_process, a_address, a_size, a_newProtect, a_oldProtect) == REX::W32::TRUE;
	}

	auto VirtualQuery(const void* a_address, MEMORY_BASIC_INFORMATION* a_buffer, std::size_t a_bufferLength) noexcept
		-> std::size_t
	{
		return ::W32_IMPL_VirtualQuery(a_address, a_buffer, a_bufferLength);
	}

	auto VirtualQueryEx(
		HANDLE a_process,
		const void* a_address,
		MEMORY_BASIC_INFORMATION* a_buffer,
		std::size_t a_bufferLength) noexcept -> std::size_t
	{
		return ::W32_IMPL_VirtualQueryEx(a_process, a_address, a_buffer, a_bufferLength);
	}

	auto WaitForSingleObject(HANDLE a_handle, std::uint32_t a_milliseconds) noexcept -> std::uint32_t
	{
		return ::W32_IMPL_WaitForSingleObject(a_handle, a_milliseconds);
	}

	auto WaitForSingleObjectEx(HANDLE a_handle, std::uint32_t a_milliseconds, bool a_alertable) noexcept
		-> std::uint32_t
	{
		return ::W32_IMPL_WaitForSingleObjectEx(a_handle, a_milliseconds, static_cast<BOOL>(a_alertable));
	}

	auto WideCharToMultiByte(
		std::uint32_t a_codePage,
		std::uint32_t a_flags,
		const wchar_t* a_source,
		std::int32_t a_sourceLength,
		char* a_target,
		std::int32_t a_targetLength,
		const char* a_default,
		std::int32_t* a_defaultLength) noexcept -> std::int32_t
	{
		return ::W32_IMPL_WideCharToMultiByte(
			a_codePage,
			a_flags,
			a_source,
			a_sourceLength,
			a_target,
			a_targetLength,
			a_default,
			a_defaultLength);
	}

	auto WriteFile(
		HANDLE a_file,
		const void* a_buffer,
		std::uint32_t a_bytesToWrite,
		std::uint32_t* a_bytesWritten,
		OVERLAPPED* a_overlapped) noexcept -> bool
	{
		return ::W32_IMPL_WriteFile(a_file, a_buffer, a_bytesToWrite, a_bytesWritten, a_overlapped) == REX::W32::TRUE;
	}

	auto WriteProcessMemory(
		HANDLE a_process,
		void* a_address,
		const void* a_buffer,
		std::size_t a_bufferLength,
		std::size_t* a_bufferWritten) noexcept -> bool
	{
		return ::W32_IMPL_WriteProcessMemory(a_process, a_address, a_buffer, a_bufferLength, a_bufferWritten) ==
			   REX::W32::TRUE;
	}
}

// NT

namespace REX::W32
{
	auto NtCurrentTeb() noexcept -> TEB*
	{
		return std::bit_cast<TEB*>(__readgsqword(offsetof(NT_TIB, self)));
	}
}

// OLE32

REX_W32_IMPORT(void, CoTaskMemFree, void*);

namespace REX::W32
{
	void CoTaskMemFree(void* a_block) noexcept
	{
		::W32_IMPL_CoTaskMemFree(a_block);
	}
}

// SHELL32

REX_W32_IMPORT(std::int32_t, SHGetKnownFolderPath, const REX::W32::GUID&, std::uint32_t, void*, wchar_t**);

namespace REX::W32
{
	auto SHGetKnownFolderPath(const GUID& a_id, std::uint32_t a_flags, void* a_token, wchar_t** a_path) noexcept
		-> std::int32_t
	{
		return ::W32_IMPL_SHGetKnownFolderPath(a_id, a_flags, a_token, a_path);
	}
}

// USER32

REX_W32_IMPORT(std::int16_t, GetAsyncKeyState, std::int32_t);
REX_W32_IMPORT(REX::W32::BOOL, GetClientRect, REX::W32::HWND, REX::W32::RECT*);
REX_W32_IMPORT(std::int32_t, GetKeyNameTextA, std::int32_t, char*, std::int32_t);
REX_W32_IMPORT(std::int32_t, GetKeyNameTextW, std::int32_t, wchar_t*, std::int32_t);
REX_W32_IMPORT(std::int16_t, GetKeyState, std::int32_t);
REX_W32_IMPORT(REX::W32::BOOL, GetWindowRect, REX::W32::HWND, REX::W32::RECT*);
REX_W32_IMPORT(std::int32_t, MessageBoxA, REX::W32::HWND, const char*, const char*, std::uint32_t);
REX_W32_IMPORT(std::int32_t, MessageBoxW, REX::W32::HWND, const wchar_t*, const wchar_t*, std::uint32_t);
REX_W32_IMPORT(std::uint32_t, SendInput, std::uint32_t, REX::W32::INPUT*, std::int32_t);
REX_W32_IMPORT(std::intptr_t, SetWindowLongPtrA, REX::W32::HWND, std::int32_t, std::intptr_t);
REX_W32_IMPORT(std::int32_t, ShowCursor, REX::W32::BOOL);

namespace REX::W32
{
	auto GetAsyncKeyState(std::int32_t a_key) noexcept -> std::int16_t
	{
		return ::W32_IMPL_GetAsyncKeyState(a_key);
	}

	auto GetClientRect(HWND a_wnd, RECT* a_rect) noexcept -> bool
	{
		return ::W32_IMPL_GetClientRect(a_wnd, a_rect) == REX::W32::TRUE;
	}

	auto GetKeyNameTextA(std::int32_t a_param, char* a_buffer, std::int32_t a_bufferLength) noexcept -> std::int32_t
	{
		return ::W32_IMPL_GetKeyNameTextA(a_param, a_buffer, a_bufferLength);
	}

	auto GetKeyNameTextW(std::int32_t a_param, wchar_t* a_buffer, std::int32_t a_bufferLength) noexcept -> std::int32_t
	{
		return ::W32_IMPL_GetKeyNameTextW(a_param, a_buffer, a_bufferLength);
	}

	auto GetKeyState(std::int32_t a_key) noexcept -> std::int16_t
	{
		return ::W32_IMPL_GetKeyState(a_key);
	}

	auto GetWindowRect(HWND a_wnd, RECT* a_rect) noexcept -> bool
	{
		return ::W32_IMPL_GetWindowRect(a_wnd, a_rect) == REX::W32::TRUE;
	}

	auto MessageBoxA(HWND a_wnd, const char* a_text, const char* a_caption, std::uint32_t a_type) noexcept
		-> std::int32_t
	{
		return ::W32_IMPL_MessageBoxA(a_wnd, a_text, a_caption, a_type);
	}

	auto MessageBoxW(HWND a_wnd, const wchar_t* a_text, const wchar_t* a_caption, std::uint32_t a_type) noexcept
		-> std::int32_t
	{
		return ::W32_IMPL_MessageBoxW(a_wnd, a_text, a_caption, a_type);
	}

	auto SendInput(std::uint32_t a_inputCount, INPUT* a_inputs, std::int32_t a_inputSize) noexcept -> std::uint32_t
	{
		return ::W32_IMPL_SendInput(a_inputCount, a_inputs, a_inputSize);
	}

	auto SetWindowLongPtrA(HWND a_wnd, std::int32_t a_index, std::intptr_t a_newPtr) noexcept -> std::intptr_t
	{
		return ::W32_IMPL_SetWindowLongPtrA(a_wnd, a_index, a_newPtr);
	}

	auto ShowCursor(bool a_show) noexcept -> std::int32_t
	{
		return ::W32_IMPL_ShowCursor(static_cast<BOOL>(a_show));
	}
}

// VERSION

REX_W32_IMPORT(REX::W32::BOOL, GetFileVersionInfoA, const char*, std::uint32_t, std::uint32_t, void*);
REX_W32_IMPORT(REX::W32::BOOL, GetFileVersionInfoW, const wchar_t*, std::uint32_t, std::uint32_t, void*);
REX_W32_IMPORT(std::uint32_t, GetFileVersionInfoSizeA, const char*, std::uint32_t*);
// REX_W32_IMPORT(std::uint32_t, GetFileVersionInfoSizeExA, std::uint32_t, const char*, std::uint32_t*);
REX_W32_IMPORT(std::uint32_t, GetFileVersionInfoSizeExW, std::uint32_t, const wchar_t*, std::uint32_t*);
REX_W32_IMPORT(std::uint32_t, GetFileVersionInfoSizeW, const wchar_t*, std::uint32_t*);
REX_W32_IMPORT(REX::W32::BOOL, VerQueryValueA, const void*, const char*, void**, std::uint32_t*);
REX_W32_IMPORT(REX::W32::BOOL, VerQueryValueW, const void*, const wchar_t*, void**, std::uint32_t*);

namespace REX::W32
{
	auto GetFileVersionInfoA(const char* a_name, std::uint32_t a_handle, std::uint32_t a_dataLength, void* a_data)
		noexcept -> bool
	{
		return ::W32_IMPL_GetFileVersionInfoA(a_name, a_handle, a_dataLength, a_data) == REX::W32::TRUE;
	}

	auto GetFileVersionInfoSizeA(const char* a_name, std::uint32_t* a_handle) noexcept -> std::uint32_t
	{
		return ::W32_IMPL_GetFileVersionInfoSizeA(a_name, a_handle);
	}

	/*
	std::uint32_t GetFileVersionInfoSizeExA(std::uint32_t a_flags, const char* a_name, std::uint32_t* a_handle) noexcept
	{
		return ::W32_IMPL_GetFileVersionInfoSizeExA(a_flags, a_name, a_handle);
	}
	*/

	auto GetFileVersionInfoSizeExW(std::uint32_t a_flags, const wchar_t* a_name, std::uint32_t* a_handle) noexcept
		-> std::uint32_t
	{
		return ::W32_IMPL_GetFileVersionInfoSizeExW(a_flags, a_name, a_handle);
	}

	auto GetFileVersionInfoSizeW(const wchar_t* a_name, std::uint32_t* a_handle) noexcept -> std::uint32_t
	{
		return ::W32_IMPL_GetFileVersionInfoSizeW(a_name, a_handle);
	}

	auto GetFileVersionInfoW(const wchar_t* a_name, std::uint32_t a_handle, std::uint32_t a_dataLength, void* a_data)
		noexcept -> bool
	{
		return ::W32_IMPL_GetFileVersionInfoW(a_name, a_handle, a_dataLength, a_data) == REX::W32::TRUE;
	}

	auto VerQueryValueA(const void* a_block, const char* a_subBlock, void** a_buffer, std::uint32_t* a_bufferLength)
		noexcept -> bool
	{
		return ::W32_IMPL_VerQueryValueA(a_block, a_subBlock, a_buffer, a_bufferLength) == REX::W32::TRUE;
	}

	auto VerQueryValueW(const void* a_block, const wchar_t* a_subBlock, void** a_buffer, std::uint32_t* a_bufferLength)
		noexcept -> bool
	{
		return ::W32_IMPL_VerQueryValueW(a_block, a_subBlock, a_buffer, a_bufferLength) == REX::W32::TRUE;
	}
}

// WS2_32

REX_W32_IMPORT(std::uint16_t, htons, std::uint16_t);
REX_W32_IMPORT(std::uint32_t, ntohl, std::uint32_t);
REX_W32_IMPORT(std::int32_t, WSAGetLastError);

namespace REX::W32
{
	auto htons(std::uint16_t a_host) noexcept -> std::uint16_t
	{
		return ::W32_IMPL_htons(a_host);
	}

	auto ntohl(std::uint32_t a_net) noexcept -> std::uint32_t
	{
		return ::W32_IMPL_ntohl(a_net);
	}

	auto WSAGetLastError() noexcept -> std::int32_t
	{
		return ::W32_IMPL_WSAGetLastError();
	}
}

// NOLINTEND(cppcoreguidelines-pro-type-vararg)

#undef REX_W32_IMPORT_NO_THROW
#undef REX_W32_IMPORT
#undef REX_BASIC_W32_IMPORT
