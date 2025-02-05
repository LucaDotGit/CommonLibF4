#pragma once

#include "REL/Version.hpp"
#ifdef ENABLE_FALLOUT_VR
#include <rapidcsv.h>
#endif

namespace REL
{
	class IDDB
	{
	private:
		struct mapping_t
		{
			std::uint64_t id;
			std::uint64_t offset;
		};

	public:
		IDDB(const IDDB&) = delete;
		IDDB(IDDB&&) = delete;

		IDDB& operator=(const IDDB&) = delete;
		IDDB& operator=(IDDB&&) = delete;

		[[nodiscard]] static IDDB& get()
		{
			static IDDB singleton;
			return singleton;
		}

		[[nodiscard]] std::size_t id2offset(std::uint64_t a_id) const;

#ifdef ENABLE_FALLOUT_VR
		bool IsVRAddressLibraryAtLeastVersion(const char* a_minimalVRAddressLibVersion, bool a_reportAndFail = false) const;
#endif

	protected:
		friend class Offset2ID;

		[[nodiscard]] std::span<const mapping_t> get_id2offset() const noexcept { return _id2offset; }

	private:
#ifdef ENABLE_FALLOUT_VR
		bool load_csv(std::string a_filename, Version a_version, bool a_failOnError);
#endif
		IDDB();
		~IDDB() = default;

		mmio::mapped_file_source _mmap;
		std::span<const mapping_t> _id2offset;
#ifdef ENABLE_FALLOUT_VR
		Version _vrAddressLibraryVersion;
#endif
	};
}
