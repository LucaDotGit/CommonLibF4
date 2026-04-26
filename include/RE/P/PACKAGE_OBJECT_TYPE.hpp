#pragma once

namespace RE
{
	enum class PACKAGE_OBJECT_TYPE : std::int32_t
	{
		kNone = 0,
		kActi = 1,
		kArmo = 2,
		kBook = 3,
		kCont = 4,
		kDoor = 5,
		kIngr = 6,
		kLigh = 7,
		kMisc = 8,
		kFlor = 9,
		kFurn = 10,
		kWeap = 11,
		kAmmo = 12,
		kKeym = 13,
		kAlch = 14,
		kFood = 15,
		kClot = 16,
		kWear = 17,
		kWeapNone = 18,
		kWeapMelee = 19,
		kWeapRanged = 20,
		kSpell = 21,
		kSpellRanged = 22,
		kSpellTouch = 23,
		kSpellSelf = 24,
		kActor = 25,
		kFurnBed = 26,
		kFurnChair = 27,
		kShout = 28,
		kHeadtrack = 29
	};
}
