#pragma once

#include "REX/StaticString.hpp"
#include "REX/W32/CORE.hpp"

namespace REX::W32
{
	inline constexpr auto INADDR_ANY = std::numeric_limits<std::uint32_t>::min();
	inline constexpr auto INADDR_LOOPBACK = static_cast<std::uint32_t>(0x7F00'0001);
	inline constexpr auto INADDR_BROADCAST = std::numeric_limits<std::uint32_t>::max();
	inline constexpr auto INADDR_NONE = std::numeric_limits<std::uint32_t>::max();

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
		WSABASEERR = 10'000,
		WSAEINTR = 10'004,
		WSAEBADF = 10'009,
		WSAEACCES = 10'013,
		WSAEFAULT = 10'014,
		WSAEINVAL = 10'022,
		WSAEMFILE = 10'024,
		WSAEWOULDBLOCK = 10'035,
		WSAEINPROGRESS = 10'036,
		WSAEALREADY = 10'037,
		WSAENOTSOCK = 10'038,
		WSAEDESTADDRREQ = 10'039,
		WSAEMSGSIZE = 10'040,
		WSAEPROTOTYPE = 10'041,
		WSAENOPROTOOPT = 10'042,
		WSAEPROTONOSUPPORT = 10'043,
		WSAESOCKTNOSUPPORT = 10'044,
		WSAEOPNOTSUPP = 10'045,
		WSAEPFNOSUPPORT = 10'046,
		WSAEAFNOSUPPORT = 10'047,
		WSAEADDRINUSE = 10'048,
		WSAEADDRNOTAVAIL = 10'049,
		WSAENETDOWN = 10'050,
		WSAENETUNREACH = 10'051,
		WSAENETRESET = 10'052,
		WSAECONNABORTED = 10'053,
		WSAECONNRESET = 10'054,
		WSAENOBUFS = 10'055,
		WSAEISCONN = 10'056,
		WSAENOTCONN = 10'057,
		WSAESHUTDOWN = 10'058,
		WSAETOOMANYREFS = 10'059,
		WSAETIMEDOUT = 10'060,
		WSAECONNREFUSED = 10'061,
		WSAELOOP = 10'062,
		WSAENAMETOOLONG = 10'063,
		WSAEHOSTDOWN = 10'064,
		WSAEHOSTUNREACH = 10'065,
		WSAENOTEMPTY = 10'066,
		WSAEPROCLIM = 10'067,
		WSAEUSERS = 10'068,
		WSAEDQUOT = 10'069,
		WSAESTALE = 10'070,
		WSAEREMOTE = 10'071,
		WSASYSNOTREADY = 10'091,
		WSAVERNOTSUPPORTED = 10'092,
		WSANOTINITIALISED = 10'093,
		WSAEDISCON = 10'101,
		WSAENOMORE = 10'102,
		WSAECANCELLED = 10'103,
		WSAEINVALIDPROCTABLE = 10'104,
		WSAEINVALIDPROVIDER = 10'105,
		WSAEPROVIDERFAILEDINIT = 10'106,
		WSASYSCALLFAILURE = 10'107,
		WSASERVICE_NOT_FOUND = 10'108,
		WSATYPE_NOT_FOUND = 10'109,
		WSA_E_NO_MORE = 10'110,
		WSA_E_CANCELLED = 10'111,
		WSAEREFUSED = 10'112,
		WSAHOST_NOT_FOUND = 11'001,
		WSATRY_AGAIN = 11'002,
		WSANO_RECOVERY = 11'003,
		WSANO_DATA = 11'004,
		WSA_QOS_RECEIVERS = 11'005,
		WSA_QOS_SENDERS = 11'006,
		WSA_QOS_NO_SENDERS = 11'007,
		WSA_QOS_NO_RECEIVERS = 11'008,
		WSA_QOS_REQUEST_CONFIRMED = 11'009,
		WSA_QOS_ADMISSION_FAILURE = 11'010,
		WSA_QOS_POLICY_FAILURE = 11'011,
		WSA_QOS_BAD_STYLE = 11'012,
		WSA_QOS_BAD_OBJECT = 11'013,
		WSA_QOS_TRAFFIC_CTRL_ERROR = 11'014,
		WSA_QOS_GENERIC_ERROR = 11'015,
		WSA_QOS_ESERVICETYPE = 11'016,
		WSA_QOS_EFLOWSPEC = 11'017,
		WSA_QOS_EPROVSPECBUF = 11'018,
		WSA_QOS_EFILTERSTYLE = 11'019,
		WSA_QOS_EFILTERTYPE = 11'020,
		WSA_QOS_EFILTERCOUNT = 11'021,
		WSA_QOS_EOBJLENGTH = 11'022,
		WSA_QOS_EFLOWCOUNT = 11'023,
		WSA_QOS_EUNKOWNPSOBJ = 11'024,
		WSA_QOS_EPOLICYOBJ = 11'025,
		WSA_QOS_EFLOWDESC = 11'026,
		WSA_QOS_EPSFLOWSPEC = 11'027,
		WSA_QOS_EPSFILTERSPEC = 11'028,
		WSA_QOS_ESDMODEOBJ = 11'029,
		WSA_QOS_ESHAPERATEOBJ = 11'030,
		WSA_QOS_RESERVED_PETYPE = 11'031,
		WSA_SECURE_HOST_NOT_FOUND = 11'032,
		WSA_IPSEC_NAME_POLICY_ERROR = 11'033
	};

	using SOCKET = std::uintptr_t;

	struct sockaddr
	{
		ADDRESS_FAMILY sa_family;
		REX::StaticString<14> sa_data;
	};

	// Originally a struct with several #defines that served as aliases to members.
	// The defines screwed a lot of things up, so it was made a union.
	// This means it will not have compatibility with code that uses in_addrs directly and
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
		REX::StaticString<8> sin_zero;
	};
}

namespace REX::W32
{
	auto htons(std::uint16_t a_host) noexcept -> std::uint16_t;
	auto ntohl(std::uint32_t a_net) noexcept -> std::uint32_t;
	auto WSAGetLastError() noexcept -> std::int32_t;
}
