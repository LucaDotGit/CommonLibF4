#pragma once

namespace REX::W32
{
	inline constexpr auto INADDR_ANY{ 0x00000000ui32 };
	inline constexpr auto INADDR_LOOPBACK{ 0x7F000001ui32 };
	inline constexpr auto INADDR_BROADCAST{ 0xFFFFFFFFu };
	inline constexpr auto INADDR_NONE{ 0xFFFFFFFFu };

	enum ADDRESS_FAMILY : std::uint16_t
	{
		AF_UNSPEC = 0,
		AF_UNIX = 1,
		AF_INET = 2,
		AF_IMPLINK = 3,
		AF_PUP = 4,
		AF_CHAOS = 5,
		AF_NS = 6,
		AF_IPX = AF_NS,
		AF_ISO = 7,
		AF_OSI = AF_ISO,
		AF_ECMA = 8,
		AF_DATAKIT = 9,
		AF_CCITT = 10,
		AF_SNA = 11,
		AF_DECnet = 12,
		AF_DLI = 13,
		AF_LAT = 14,
		AF_HYLINK = 15,
		AF_APPLETALK = 16,
		AF_NETBIOS = 17,
		AF_VOICEVIEW = 18,
		AF_FIREFOX = 19,
		AF_UNKNOWN1 = 20,
		AF_BAN = 21,
		AF_ATM = 22,
		AF_INET6 = 23,
		AF_CLUSTER = 24,
		AF_12844 = 25,
		AF_IRDA = 26,
		AF_NETDES = 28
	};

	enum WSA_ERROR : std::int32_t
	{
		WSABASEERR = 10000,
		WSAEINTR = 10004,
		WSAEBADF = 10009,
		WSAEACCES = 10013,
		WSAEFAULT = 10014,
		WSAEINVAL = 10022,
		WSAEMFILE = 10024,
		WSAEWOULDBLOCK = 10035,
		WSAEINPROGRESS = 10036,
		WSAEALREADY = 10037,
		WSAENOTSOCK = 10038,
		WSAEDESTADDRREQ = 10039,
		WSAEMSGSIZE = 10040,
		WSAEPROTOTYPE = 10041,
		WSAENOPROTOOPT = 10042,
		WSAEPROTONOSUPPORT = 10043,
		WSAESOCKTNOSUPPORT = 10044,
		WSAEOPNOTSUPP = 10045,
		WSAEPFNOSUPPORT = 10046,
		WSAEAFNOSUPPORT = 10047,
		WSAEADDRINUSE = 10048,
		WSAEADDRNOTAVAIL = 10049,
		WSAENETDOWN = 10050,
		WSAENETUNREACH = 10051,
		WSAENETRESET = 10052,
		WSAECONNABORTED = 10053,
		WSAECONNRESET = 10054,
		WSAENOBUFS = 10055,
		WSAEISCONN = 10056,
		WSAENOTCONN = 10057,
		WSAESHUTDOWN = 10058,
		WSAETOOMANYREFS = 10059,
		WSAETIMEDOUT = 10060,
		WSAECONNREFUSED = 10061,
		WSAELOOP = 10062,
		WSAENAMETOOLONG = 10063,
		WSAEHOSTDOWN = 10064,
		WSAEHOSTUNREACH = 10065,
		WSAENOTEMPTY = 10066,
		WSAEPROCLIM = 10067,
		WSAEUSERS = 10068,
		WSAEDQUOT = 10069,
		WSAESTALE = 10070,
		WSAEREMOTE = 10071,
		WSASYSNOTREADY = 10091,
		WSAVERNOTSUPPORTED = 10092,
		WSANOTINITIALISED = 10093,
		WSAEDISCON = 10101,
		WSAENOMORE = 10102,
		WSAECANCELLED = 10103,
		WSAEINVALIDPROCTABLE = 10104,
		WSAEINVALIDPROVIDER = 10105,
		WSAEPROVIDERFAILEDINIT = 10106,
		WSASYSCALLFAILURE = 10107,
		WSASERVICE_NOT_FOUND = 10108,
		WSATYPE_NOT_FOUND = 10109,
		WSA_E_NO_MORE = 10110,
		WSA_E_CANCELLED = 10111,
		WSAEREFUSED = 10112,
		WSAHOST_NOT_FOUND = 11001,
		WSATRY_AGAIN = 11002,
		WSANO_RECOVERY = 11003,
		WSANO_DATA = 11004,
		WSA_QOS_RECEIVERS = 11005,
		WSA_QOS_SENDERS = 11006,
		WSA_QOS_NO_SENDERS = 11007,
		WSA_QOS_NO_RECEIVERS = 11008,
		WSA_QOS_REQUEST_CONFIRMED = 11009,
		WSA_QOS_ADMISSION_FAILURE = 11010,
		WSA_QOS_POLICY_FAILURE = 11011,
		WSA_QOS_BAD_STYLE = 11012,
		WSA_QOS_BAD_OBJECT = 11013,
		WSA_QOS_TRAFFIC_CTRL_ERROR = 11014,
		WSA_QOS_GENERIC_ERROR = 11015,
		WSA_QOS_ESERVICETYPE = 11016,
		WSA_QOS_EFLOWSPEC = 11017,
		WSA_QOS_EPROVSPECBUF = 11018,
		WSA_QOS_EFILTERSTYLE = 11019,
		WSA_QOS_EFILTERTYPE = 11020,
		WSA_QOS_EFILTERCOUNT = 11021,
		WSA_QOS_EOBJLENGTH = 11022,
		WSA_QOS_EFLOWCOUNT = 11023,
		WSA_QOS_EUNKOWNPSOBJ = 11024,
		WSA_QOS_EPOLICYOBJ = 11025,
		WSA_QOS_EFLOWDESC = 11026,
		WSA_QOS_EPSFLOWSPEC = 11027,
		WSA_QOS_EPSFILTERSPEC = 11028,
		WSA_QOS_ESDMODEOBJ = 11029,
		WSA_QOS_ESHAPERATEOBJ = 11030,
		WSA_QOS_RESERVED_PETYPE = 11031,
		WSA_SECURE_HOST_NOT_FOUND = 11032,
		WSA_IPSEC_NAME_POLICY_ERROR = 11033
	};

	using SOCKET = std::uintptr_t;

	struct sockaddr
	{
		ADDRESS_FAMILY sa_family;
		std::array<char, 14> sa_data;
	};

	// Originally a struct with several #defines that served as aliases to members.
	// The defines screwed a lot of things up, so it was made a union.
	// This means it won't have compatibility with code that uses in_addrs directly and
	// also refers to it by its full type identifier (i.e. `struct in_addr`).
	union in_addr
	{
		union in_addr_D
		{
			struct
			{
				std::uint8_t s_b1;
				std::uint8_t s_b2;
				std::uint8_t s_b3;
				std::uint8_t s_b4;
			} S_un_b;

			struct
			{
				std::uint16_t s_w1;
				std::uint16_t s_w2;
			} S_un_w;

			std::uint32_t S_addr;
		} S_un;

		// getting around the #DEFINEs in inaddr.h
		struct
		{
			std::uint8_t s_net;
			std::uint8_t s_host;
			std::uint8_t s_lh;
			std::uint8_t s_impno;
		};

		struct
		{
			std::uint16_t _s_w1;
			std::uint16_t s_imp;
		};

		std::uint32_t s_addr;
	};

	struct sockaddr_in
	{
		ADDRESS_FAMILY sin_family;
		std::uint16_t sin_port;
		in_addr sin_addr;
		std::array<char, 8> sin_zero;
	};
}

namespace REX::W32
{
	std::uint16_t htons(std::uint16_t a_host) noexcept;
	std::uint32_t ntohl(std::uint32_t a_net) noexcept;
	std::int32_t WSAGetLastError() noexcept;
}
