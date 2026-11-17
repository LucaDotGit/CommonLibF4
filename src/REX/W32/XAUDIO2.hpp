#pragma once

#include "REX/StaticString.hpp"
#include "REX/W32/COM.hpp"
#include "REX/W32/CORE.hpp"

namespace REX::W32
{
	struct IXAudio2EngineCallback;
	struct IXAudio2Extension;
	struct IXAudio2VoiceCallback;
	struct IXAudio27;
	struct IXAudio27Voice;
	struct IXAudio27SourceVoice;
	struct IXAudio27SubmixVoice;
	struct IXAudio27MasteringVoice;
}

namespace REX::W32
{
	inline constexpr auto XAUDIO2_MAX_BUFFER_BYTES = static_cast<std::uint32_t>(0x8000'0000);
	inline constexpr auto XAUDIO2_MAX_QUEUED_BUFFERS = static_cast<std::uint32_t>(64);
	inline constexpr auto XAUDIO2_MAX_BUFFERS_SYSTEM = static_cast<std::uint32_t>(2);
	inline constexpr auto XAUDIO2_MAX_AUDIO_CHANNELS = static_cast<std::uint32_t>(64);
	inline constexpr auto XAUDIO2_MIN_SAMPLE_RATE = static_cast<std::uint32_t>(1'000);
	inline constexpr auto XAUDIO2_MAX_SAMPLE_RATE = static_cast<std::uint32_t>(200'000);
	inline constexpr auto XAUDIO2_MAX_VOLUME_LEVEL = static_cast<REX::Float32>(16777216.0);
	inline constexpr auto XAUDIO2_MIN_FREQ_RATIO = static_cast<REX::Float32>(1.0) / static_cast<REX::Float32>(1024.0);
	inline constexpr auto XAUDIO2_MAX_FREQ_RATIO = static_cast<REX::Float32>(1024.0);
	inline constexpr auto XAUDIO2_DEFAULT_FREQ_RATIO = static_cast<REX::Float32>(2.0);
	inline constexpr auto XAUDIO2_MAX_FILTER_ONEOVERQ = static_cast<REX::Float32>(1.5);
	inline constexpr auto XAUDIO2_MAX_FILTER_FREQUENCY = static_cast<REX::Float32>(1.0);
	inline constexpr auto XAUDIO2_MAX_LOOP_COUNT = static_cast<std::uint32_t>(254);
	inline constexpr auto XAUDIO2_MAX_INSTANCES = static_cast<std::uint32_t>(8);

	inline constexpr auto XAUDIO2_MAX_RATIO_TIMES_RATE_XMA_MONO = static_cast<std::uint32_t>(600'000);
	inline constexpr auto XAUDIO2_MAX_RATIO_TIMES_RATE_XMA_MULTICHANNEL = static_cast<std::uint32_t>(300'000);

	inline constexpr auto XAUDIO2_COMMIT_NOW = static_cast<std::uint32_t>(0);
	inline constexpr auto XAUDIO2_COMMIT_ALL = static_cast<std::uint32_t>(0);
	inline constexpr auto XAUDIO2_INVALID_OPSET = std::numeric_limits<std::uint32_t>::max();
	inline constexpr auto XAUDIO2_NO_LOOP_REGION = static_cast<std::uint32_t>(0);
	inline constexpr auto XAUDIO2_LOOP_INFINITE = static_cast<std::uint32_t>(255);
	inline constexpr auto XAUDIO2_DEFAULT_CHANNELS = static_cast<std::uint32_t>(0);
	inline constexpr auto XAUDIO2_DEFAULT_SAMPLERATE = static_cast<std::uint32_t>(0);

	inline constexpr auto XAUDIO2_DEBUG_ENGINE = static_cast<std::uint32_t>(0x01);
	inline constexpr auto XAUDIO2_VOICE_NOPITCH = static_cast<std::uint32_t>(0x02);
	inline constexpr auto XAUDIO2_VOICE_NOSRC = static_cast<std::uint32_t>(0x04);
	inline constexpr auto XAUDIO2_VOICE_USEFILTER = static_cast<std::uint32_t>(0x08);
	inline constexpr auto XAUDIO2_VOICE_MUSIC = static_cast<std::uint32_t>(0x10);
	inline constexpr auto XAUDIO2_PLAY_TAILS = static_cast<std::uint32_t>(0x20);
	inline constexpr auto XAUDIO2_END_OF_STREAM = static_cast<std::uint32_t>(0x40);
	inline constexpr auto XAUDIO2_SEND_USEFILTER = static_cast<std::uint32_t>(0x80);

	inline constexpr auto XAUDIO2_DEFAULT_FILTER_TYPE = static_cast<std::uint32_t>(0);
	inline constexpr auto XAUDIO2_DEFAULT_FILTER_FREQUENCY = XAUDIO2_MAX_FILTER_FREQUENCY;
	inline constexpr auto XAUDIO2_DEFAULT_FILTER_ONEOVERQ = static_cast<REX::Float32>(1.0);
}

namespace REX::W32
{
	enum XAUDIO2_FILTER_TYPE : std::int32_t
	{
		LowPassFilter = 0,
		BandPassFilter = 1,
		HighPassFilter = 2,
		NotchFilter = 3
	};

	enum XAUDIO2_DEVICE_ROLE : std::uint32_t
	{
		NotDefaultDevice = 0,
		DefaultConsoleDevice = 0x01,
		DefaultMultimediaDevice = 0x02,
		DefaultCommunicationsDevice = 0x04,
		DefaultGameDevice = 0x08,
		GlobalDefaultDevice = 0x0F,
		InvalidDeviceRole = ~GlobalDefaultDevice
	};

	enum XAUDIO2_PROCESSOR : std::uint32_t
	{
		Processor1 = 0x01,
		Processor2 = 0x02,
		Processor3 = 0x04,
		Processor4 = 0x08,
		Processor5 = 0x10,
		Processor6 = 0x20,
		Processor7 = 0x40,
		Processor8 = 0x80,
		Processor9 = 0x100,
		Processor10 = 0x200,
		Processor11 = 0x400,
		Processor12 = 0x800,
		Processor13 = 0x1000,
		Processor14 = 0x2000,
		Processor15 = 0x4000,
		Processor16 = 0x8000,
		Processor17 = 0x1'0000,
		Processor18 = 0x2'0000,
		Processor19 = 0x4'0000,
		Processor20 = 0x8'0000,
		Processor21 = 0x10'0000,
		Processor22 = 0x20'0000,
		Processor23 = 0x40'0000,
		Processor24 = 0x80'0000,
		Processor25 = 0x100'0000,
		Processor26 = 0x200'0000,
		Processor27 = 0x400'0000,
		Processor28 = 0x800'0000,
		Processor29 = 0x1000'0000,
		Processor30 = 0x2000'0000,
		Processor31 = 0x4000'0000,
		Processor32 = 0x8000'0000,
		XAUDIO2_ANY_PROCESSOR = std::numeric_limits<std::uint32_t>::max(),
		XAUDIO2_DEFAULT_PROCESSOR = XAUDIO2_ANY_PROCESSOR
	};

	using XAUDIO2_WINDOWS_PROCESSOR_SPECIFIER = XAUDIO2_PROCESSOR;
}

namespace REX::W32
{
	struct XAUDIO2_VOICE_DETAILS
	{
		std::uint32_t creationFlags;
		std::uint32_t inputChannels;
		std::uint32_t inputSampleRate;
	};

	struct XAUDIO2_SEND_DESCRIPTOR
	{
		std::uint32_t flags;
		void* outputVoice;
	};

	struct XAUDIO2_VOICE_SENDS
	{
		std::uint32_t sendCount;
		XAUDIO2_SEND_DESCRIPTOR* sendDescriptors;
	};

	struct XAUDIO2_FILTER_PARAMETERS
	{
		XAUDIO2_FILTER_TYPE type;
		REX::Float32 frequency;
		REX::Float32 oneOverQ;
	};

	struct XAUDIO2_EFFECT_DESCRIPTOR
	{
		void* effect;
		BOOL initialState;
		std::uint32_t outputChannels;
	};

	struct XAUDIO2_EFFECT_CHAIN
	{
		std::uint32_t effectCount;
		XAUDIO2_EFFECT_DESCRIPTOR* effectDescriptors;
	};

	struct XAUDIO2_BUFFER
	{
		std::uint32_t flags;
		std::uint32_t audioBytes;
		const std::uint8_t* audioData;
		std::uint32_t playBegin;
		std::uint32_t playLength;
		std::uint32_t loopBegin;
		std::uint32_t loopLength;
		std::uint32_t loopCount;
		void* context;
	};

	struct XAUDIO2_BUFFER_WMA
	{
		const std::uint32_t* decodedPacketCumulativeBytes;
		std::uint32_t packetCount;
	};

	struct XAUDIO2_VOICE_STATE
	{
		void* currentBufferContext;
		std::uint32_t buffersQueued;
		std::uint64_t samplesPlayed;
	};

	struct XAUDIO2_PERFORMANCE_DATA
	{
		std::uint64_t audioCyclesSinceLastQuery;
		std::uint64_t totalCyclesSinceLastQuery;
		std::uint32_t minimumCyclesPerQuantum;
		std::uint32_t maximumCyclesPerQuantum;
		std::uint32_t memoryUsageInBytes;
		std::uint32_t currentLatencyInSamples;
		std::uint32_t glitchesSinceEngineStarted;
		std::uint32_t activeSourceVoiceCount;
		std::uint32_t totalSourceVoiceCount;
		std::uint32_t activeSubmixVoiceCount;
		std::uint32_t activeResamplerCount;
		std::uint32_t activeMatrixMixCount;
		std::uint32_t activeXmaSourceVoices;
		std::uint32_t activeXmaStreams;
	};

	struct XAUDIO2_DEBUG_CONFIGURATION
	{
		std::uint32_t traceMask;
		std::uint32_t breakMask;
		BOOL logThreadID;
		BOOL logFileline;
		BOOL logFunctionName;
		BOOL logTiming;
	};

	struct XAUDIO2_DEVICE_DETAILS
	{
		REX::StaticWString<0x100> deviceID;
		REX::StaticWString<0x100> displayName;
		XAUDIO2_DEVICE_ROLE role;
		WAVEFORMATEXTENSIBLE outputFormat;
	};
}

namespace REX::W32
{
#if (__clang__ == 1)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnon-virtual-dtor"
#endif

#if (_MSC_VER > 0l)
#pragma warning(push)
#pragma warning(disable : 4'265)
#endif

	// NOLINTBEGIN(cppcoreguidelines-virtual-class-destructor)

	struct __declspec(novtable) IXAudio2EngineCallback
	{
		virtual void OnProcessingPassStart() noexcept = 0;
		virtual void OnProcessingPassEnd() noexcept = 0;
		virtual void OnCriticalError(HRESULT a_error) noexcept = 0;
	};

	struct __declspec(novtable, uuid("84ac29bb-d619-44d2-b197-e4acf7df3ed6")) IXAudio2Extension : public IUnknown
	{
		virtual void GetProcessingQuantum(std::uint32_t* a_quantumNumerator, std::uint32_t* a_quantumDenominator)
			noexcept = 0;
		virtual void GetProcessor(XAUDIO2_PROCESSOR* a_processor) noexcept = 0;
	};

	struct __declspec(novtable) IXAudio2VoiceCallback
	{
		virtual void OnVoiceProcessingPassStart(std::uint32_t a_bytesRequired) noexcept = 0;
		virtual void OnVoiceProcessingPassEnd() noexcept = 0;
		virtual void OnStreamEnd() noexcept = 0;
		virtual void OnBufferStart(void* a_bufferContext) noexcept = 0;
		virtual void OnBufferEnd(void* a_bufferContext) noexcept = 0;
		virtual void OnLoopEnd(void* a_bufferContext) noexcept = 0;
		virtual void OnVoiceError(void* a_bufferContext, HRESULT a_error) noexcept = 0;
	};

	struct __declspec(novtable, uuid("8bcf1f58-9fe7-4583-8ac6-e2adc465c8bb")) IXAudio27 : public IUnknown
	{
		virtual auto GetDeviceCount(std::uint32_t* a_count) const -> HRESULT = 0;
		virtual auto GetDeviceDetails(std::uint32_t a_index, XAUDIO2_DEVICE_DETAILS* a_deviceDetails) const
			-> HRESULT = 0;
		virtual auto Initialize(
			std::uint32_t a_flags = 0,
			XAUDIO2_PROCESSOR a_audio2Processor = XAUDIO2_DEFAULT_PROCESSOR) noexcept -> HRESULT = 0;
		virtual auto RegisterForCallbacks(IXAudio2EngineCallback* a_callback) noexcept -> HRESULT = 0;
		virtual void UnregisterForCallbacks(IXAudio2EngineCallback* a_callback) noexcept = 0;
		virtual auto CreateSourceVoice(
			IXAudio27SourceVoice** a_sourceVoice,
			const WAVEFORMATEX* a_sourceFormat,
			std::uint32_t a_flags = 0,
			REX::Float32 a_maxFrequencyRatio = static_cast<REX::Float32>(2.0),
			IXAudio2VoiceCallback* a_callback = nullptr,
			const XAUDIO2_VOICE_SENDS* a_sendList = nullptr,
			const XAUDIO2_EFFECT_CHAIN* a_effectChain = nullptr) noexcept -> HRESULT = 0;
		virtual auto CreateSubmixVoice(
			IXAudio27SubmixVoice** a_submixVoice,
			std::uint32_t a_inputChannels,
			std::uint32_t a_inputSampleRate,
			std::uint32_t a_flags = 0,
			std::uint32_t a_processingStage = 0,
			const XAUDIO2_VOICE_SENDS* a_sendList = nullptr,
			const XAUDIO2_EFFECT_CHAIN* a_effectChain = nullptr) noexcept -> HRESULT = 0;
		virtual auto CreateMasteringVoice(
			IXAudio27MasteringVoice** a_masteringVoice,
			std::uint32_t a_inputChannels = XAUDIO2_DEFAULT_CHANNELS,
			std::uint32_t a_inputSampleRate = XAUDIO2_DEFAULT_SAMPLERATE,
			std::uint32_t a_flags = 0,
			std::uint32_t a_index = 0,
			const XAUDIO2_EFFECT_CHAIN* a_effectChain = nullptr) noexcept -> HRESULT = 0;
		virtual auto StartEngine() noexcept -> HRESULT = 0;
		virtual void StopEngine() noexcept = 0;
		virtual auto CommitChanges(std::uint32_t a_operationSet) noexcept -> HRESULT = 0;
		virtual void GetPerformanceData(XAUDIO2_PERFORMANCE_DATA* a_perfData) const noexcept = 0;
		virtual void SetDebugConfiguration(
			const XAUDIO2_DEBUG_CONFIGURATION* a_debugConfiguration,
			void* a_reserved = nullptr) noexcept = 0;
	};

	struct __declspec(novtable) IXAudio27Voice
	{
		virtual void GetVoiceDetails(XAUDIO2_VOICE_DETAILS* a_voiceDetails) const noexcept = 0;
		virtual auto SetOutputVoices(const XAUDIO2_VOICE_SENDS* a_sendList) noexcept -> HRESULT = 0;
		virtual auto SetEffectChain(const XAUDIO2_EFFECT_CHAIN* a_effectChain) noexcept -> HRESULT = 0;
		virtual auto EnableEffect(std::uint32_t a_effectIndex, std::uint32_t a_operationSet = 0) noexcept
			-> HRESULT = 0;
		virtual auto DisableEffect(std::uint32_t a_effectIndex, std::uint32_t a_operationSet = 0) noexcept
			-> HRESULT = 0;
		virtual void GetEffectState(std::uint32_t a_effectIndex, BOOL* a_enabled) const noexcept = 0;
		virtual auto SetEffectParameters(
			std::uint32_t a_effectIndex,
			const void* a_parameters,
			std::uint32_t a_parametersByteSize,
			std::uint32_t a_operationSet = 0) noexcept -> HRESULT = 0;
		virtual auto GetEffectParameters(
			std::uint32_t a_effectIndex,
			void* a_parameters,
			std::uint32_t a_parametersByteSize) const noexcept -> HRESULT = 0;
		virtual auto SetFilterParameters(
			const XAUDIO2_FILTER_PARAMETERS* a_parameters,
			std::uint32_t a_operationSet = 0) noexcept -> HRESULT = 0;
		virtual void GetFilterParameters(XAUDIO2_FILTER_PARAMETERS* a_parameters) const noexcept = 0;
		virtual auto SetOutputFilterParameters(
			IXAudio27Voice* a_destinationVoice,
			const XAUDIO2_FILTER_PARAMETERS* a_parameters,
			std::uint32_t a_operationSet = 0) noexcept -> HRESULT = 0;
		virtual void GetOutputFilterParameters(
			IXAudio27Voice* a_destinationVoice,
			XAUDIO2_FILTER_PARAMETERS* a_parameters) const noexcept = 0;
		virtual auto SetVolume(REX::Float32 a_volume, std::uint32_t a_operationSet = 0) noexcept -> HRESULT = 0;
		virtual void GetVolume(REX::Float32* a_volume) const noexcept = 0;
		virtual auto SetChannelVolumes(
			std::uint32_t a_channels,
			const REX::Float32* a_volumes,
			std::uint32_t a_operationSet = 0) noexcept -> HRESULT = 0;
		virtual void GetChannelVolumes(std::uint32_t a_channels, REX::Float32* a_volumes) const noexcept = 0;
		virtual auto SetOutputMatrix(
			IXAudio27Voice* a_destinationVoice,
			std::uint32_t a_sourceChannels,
			std::uint32_t a_destinationChannels,
			const REX::Float32* a_levelMatrix,
			std::uint32_t a_operationSet = 0) noexcept -> HRESULT = 0;
		virtual void GetOutputMatrix(
			IXAudio27Voice* a_destinationVoice,
			std::uint32_t a_sourceChannels,
			std::uint32_t a_destinationChannels,
			REX::Float32* a_levelMatrix) const noexcept = 0;
		virtual void DestroyVoice() noexcept = 0;
	};

	struct __declspec(novtable) IXAudio27SourceVoice : public IXAudio27Voice
	{
		virtual auto Start(std::uint32_t a_flags = 0, std::uint32_t a_operationSet = 0) noexcept -> HRESULT = 0;
		virtual auto Stop(std::uint32_t a_flags = 0, std::uint32_t a_operationSet = 0) noexcept -> HRESULT = 0;
		virtual auto SubmitSourceBuffer(XAUDIO2_BUFFER* a_buffer, const XAUDIO2_BUFFER_WMA* a_bufferWMA = nullptr)
			noexcept -> HRESULT = 0;
		virtual auto FlushSourceBuffers() noexcept -> HRESULT = 0;
		virtual auto Discontinuity() noexcept -> HRESULT = 0;
		virtual auto ExitLoop(std::uint32_t a_operationSet = 0) noexcept -> HRESULT = 0;
		virtual void GetState(XAUDIO2_VOICE_STATE* a_state) const noexcept = 0;
		virtual auto SetFrequencyRatio(REX::Float32 a_ratio, std::uint32_t a_operationSet = 0) noexcept -> HRESULT = 0;
		virtual void GetFrequencyRatio(REX::Float32* a_ratio) const noexcept = 0;
		virtual auto SetSourceSampleRate(std::uint32_t a_rate) noexcept -> HRESULT = 0;
	};

	struct __declspec(novtable) IXAudio27SubmixVoice : public IXAudio27Voice
	{
	};

	struct __declspec(novtable) IXAudio27MasteringVoice : public IXAudio27Voice
	{
	};

	// NOLINTEND(cppcoreguidelines-virtual-class-destructor)

#if (_MSC_VER > 0l)
#pragma warning(pop)
#endif

#if (__clang__ == 1)
#pragma clang diagnostic pop
#endif
}
