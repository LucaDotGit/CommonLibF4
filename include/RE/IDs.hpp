#pragma once

// NOLINTBEGIN(modernize-concat-nested-namespaces)

namespace RE::ID
{
	inline constexpr auto NiMalloc = F4SE::CreateVariantId(974443, 2268535, 2268535);
	inline constexpr auto NiAlignedAlloc = F4SE::CreateVariantId(442355, 2268536, 2268536);
	inline constexpr auto NiRealloc = F4SE::CreateVariantId(1493163, 2268537, 2268537);
	inline constexpr auto NiAlignedRealloc = F4SE::CreateVariantId(1572622, 2268538, 2268538);
	inline constexpr auto NiFree = F4SE::CreateVariantId(242362, 2268539, 2268539);

	inline constexpr auto RTDynamicCast = F4SE::CreateVariantId(84112, 2725673, 4818455);

	namespace AIFormulas
	{
		inline constexpr auto ComputePickpocketSuccess = F4SE::CreateVariantId(915759, 2208977, 2208977);
		inline constexpr auto GetBarterValue = F4SE::CreateVariantId(984344, 2208969, 2208969);
	}

	namespace AIProcess
	{
		inline constexpr auto AddToProcedureIndexRunning = F4SE::CreateVariantId(134486, 2718412, 2718412);
		inline constexpr auto ComputeLastTimeProcessed = F4SE::CreateVariantId(941571, 2231541, 2231541);
		inline constexpr auto GetActorLightLevel = F4SE::CreateVariantId(898888, 2231981, 2231981);
		inline constexpr auto GetCommandType = F4SE::CreateVariantId(678523, 2231825, 2231825);
		inline constexpr auto GetCurrentAmmo = F4SE::CreateVariantId(1154936, 2232300, 2232300);
		inline constexpr auto GetOccupiedFurniture = F4SE::CreateVariantId(1162965, 2232401, 2232401);
		inline constexpr auto GetPackageThatIsRunning = F4SE::CreateVariantId(148295, 2231586, 2231586);
		inline constexpr auto IsWeaponSubgraphFinishedLoading = F4SE::CreateVariantId(320183, 2231757, 2231757);
		inline constexpr auto KnockExplosion = F4SE::CreateVariantId(533106, 2232384, 2232384);
		inline constexpr auto ProcessGreet = F4SE::CreateVariantId(1174935, 2231808, 2231808);
		inline constexpr auto RequestLoadAnimationsForWeaponChange = F4SE::CreateVariantId(666002, 2231758, 2231758);
		inline constexpr auto SetActorsDetectionEvent = F4SE::CreateVariantId(1376336, 2231738, 2231738);
		inline constexpr auto SetCommandType = F4SE::CreateVariantId(1555789, 2231826, 2231826);
		inline constexpr auto SetCurrentAmmo = F4SE::CreateVariantId(795983, 2232302, 2232302);
		inline constexpr auto SetEquippedItem = F4SE::CreateVariantId(1200276, 2231627, 2231627);
		inline constexpr auto SetRunOncePackage = F4SE::CreateVariantId(155445, 2232344, 2232344);
		inline constexpr auto SetWeaponBonesCulled = F4SE::CreateVariantId(397172, 2232535, 2232535);
		inline constexpr auto SetupSpecialIdle = F4SE::CreateVariantId(1446774, 2231704, 2231704);
		inline constexpr auto StopCurrentIdle = F4SE::CreateVariantId(434460, 2231705, 2231705);
	}

	namespace ActiveEffect
	{
		inline constexpr auto CheckDisplacementSpellOnTarget = F4SE::CreateVariantId(1415178, 0, 0); // inlined post next-gen
	}

	namespace Actor
	{
		inline constexpr auto AddPerk = F4SE::CreateVariantId(187096, 2230121, 2230121);
		inline constexpr auto CalculateDetectionFormula = F4SE::CreateVariantId(589441, 2230213, 2230213);
		inline constexpr auto CanUseIdle = F4SE::CreateVariantId(1223707, 2229592, 2229592);
		inline constexpr auto ClearAttackStates = F4SE::CreateVariantId(1525555, 2229773, 2229773);
		inline constexpr auto DoHitMe = F4SE::CreateVariantId(881215, 2231148, 2231148);
		inline constexpr auto EndInterruptPackage = F4SE::CreateVariantId(575188, 2229892, 2229892);
		inline constexpr auto ExitCover = F4SE::CreateVariantId(770035, 2231166, 2231166);
		inline constexpr auto ForceDetect = F4SE::CreateVariantId(131995, 2230194, 2230194);
		inline constexpr auto GetAimVector = F4SE::CreateVariantId(554863, 2230378, 2230378);
		inline constexpr auto GetBodyPartData = F4SE::CreateVariantId(1485196, 2229571, 2229571);
		inline constexpr auto GetClosestBone = F4SE::CreateVariantId(1180004, 2230051, 2230051);
		inline constexpr auto GetCollisionFilter = F4SE::CreateVariantId(1474995, 2277949, 2277949);
		inline constexpr auto GetCombatStyle = F4SE::CreateVariantId(1270929, 2231053, 2231053);
		inline constexpr auto GetCrimeTrackingFaction = F4SE::CreateVariantId(1108024, 2229787, 2229787);
		inline constexpr auto GetCurrentCollisionGroup = F4SE::CreateVariantId(410500, 2229993, 2229993);
		inline constexpr auto GetCurrentFireLocation = F4SE::CreateVariantId(663107, 2231167, 2231167);
		inline constexpr auto GetDesiredSpeed = F4SE::CreateVariantId(106892, 2230410, 2230410);
		inline constexpr auto GetEquippedItem = F4SE::CreateVariantId(1318331, 2231089, 2231089);
		inline constexpr auto GetGhost = F4SE::CreateVariantId(1298473, 2229668, 2229668);
		inline constexpr auto GetHealthPercentage = F4SE::CreateVariantId(260817, 2229741, 2229741);
		inline constexpr auto GetHostileToActor = F4SE::CreateVariantId(1148686, 2229968, 2229968);
		inline constexpr auto GetLevel = F4SE::CreateVariantId(661617, 2229734, 2229734);
		inline constexpr auto GetMobilityCrippled = F4SE::CreateVariantId(281477, 2230996, 2230996);
		inline constexpr auto GetMountHandle = F4SE::CreateVariantId(313362, 2231230, 2231230);
		inline constexpr auto GetOfferBarter = F4SE::CreateVariantId(1482717, 2230005, 2230005);
		inline constexpr auto GetPerkRank = F4SE::CreateVariantId(1368313, 2230125, 2230125);
		inline constexpr auto HandleDefaultAnimationSwitch = F4SE::CreateVariantId(1163130, 2229780, 2229780);
		inline constexpr auto HandleItemEquip = F4SE::CreateVariantId(164912, 2229781, 2229781);
		inline constexpr auto HasObjects = F4SE::CreateVariantId(861256, 2229961, 2229961);
		inline constexpr auto InitiateDoNothingPackage = F4SE::CreateVariantId(89993, 2229807, 2229807);
		inline constexpr auto IsCrippled = F4SE::CreateVariantId(1238666, 2230998, 2230998);
		inline constexpr auto IsFollowing = F4SE::CreateVariantId(629579, 2230013, 2230013);
		inline constexpr auto IsJumping = F4SE::CreateVariantId(1041558, 2229640, 2229640);
		inline constexpr auto IsPathValid = F4SE::CreateVariantId(1522194, 2230279, 2230279);
		inline constexpr auto IsPathing = F4SE::CreateVariantId(989661, 2234312, 2234312);
		inline constexpr auto IsPathingComplete = F4SE::CreateVariantId(817283, 2230274, 2230274);
		inline constexpr auto IsQuadruped = F4SE::CreateVariantId(1552322, 2229614, 2229614);
		inline constexpr auto IsSneaking = F4SE::CreateVariantId(1173627, 2207655, 2207655);
		inline constexpr auto Jump = F4SE::CreateVariantId(1394576, 2229650, 2229650);
		inline constexpr auto Move = F4SE::CreateVariantId(737625, 2229934, 2229934);
		inline constexpr auto PerformAction = F4SE::CreateVariantId(1057231, 2231177, 2231177);
		inline constexpr auto RemovePerk = F4SE::CreateVariantId(1316475, 2230122, 2230122);
		inline constexpr auto Reset3D = F4SE::CreateVariantId(302888, 2229913, 2229913);
		inline constexpr auto RewardExperience = F4SE::CreateVariantId(262786, 2230428, 2230428);
		inline constexpr auto SPECIALModifiedCallback = F4SE::CreateVariantId(234305, 2231020, 2231020);
		inline constexpr auto SetCurrentAmmoCount = F4SE::CreateVariantId(725546, 2229952, 2229952);
		inline constexpr auto SetGunState = F4SE::CreateVariantId(977675, 2231175, 2231175);
		inline constexpr auto SetHeading = F4SE::CreateVariantId(353571, 2229625, 2229625);
		inline constexpr auto StopInteractingQuick = F4SE::CreateVariantId(129904, 2231227, 2231227);
		inline constexpr auto TrespassAlarm = F4SE::CreateVariantId(1109888, 2229834, 2229834);
		inline constexpr auto UnequipObject = F4SE::CreateVariantId(1363509, 2230479, 2230479);
		inline constexpr auto UpdateSprinting = F4SE::CreateVariantId(385539, 2230498, 2230498);
		inline constexpr auto UpdateVoiceTimer = F4SE::CreateVariantId(1160883, 2230178, 2230178);
	}

	namespace ActorEquipManager
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(1174340, 2690994, 4798287);
		inline constexpr auto EquipObject = F4SE::CreateVariantId(988029, 2231392, 2231392);
		inline constexpr auto UnequipItem = F4SE::CreateVariantId(1316852, 2231399, 2231399);
		inline constexpr auto UnequipObject = F4SE::CreateVariantId(1292493, 2231395, 2231395);
	}

	namespace ActorUtils
	{
		inline constexpr auto GetEquippedArmorDamageResistance = F4SE::CreateVariantId(1204866, 2227189, 2227189);

		namespace ArmorRatingVisitorBase
		{
			inline constexpr auto ctor = F4SE::CreateVariantId(1212617, 2227205, 2227205);
			inline constexpr auto call_operator = F4SE::CreateVariantId(1119011, 2227206, 2227206);
		}
	}

	namespace ActorValue
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(405390, 2189587, 2189587);
	}

	namespace AITimer
	{
		inline constexpr auto Timer = F4SE::CreateVariantId(936770, 2698609, 2698609);
	}

	namespace AnimationSystemUtils
	{
		inline constexpr auto WillEventChangeState = F4SE::CreateVariantId(35074, 2214271, 2214271);
	}

	namespace ApplyColorUpdateEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(421543, 2707340, 2707340);
	}

	namespace BGSAddToPlayerInventoryEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(1163657, 2663428, 2663428);
	}

	namespace BGSAnimationSystemUtils
	{
		inline constexpr auto GetActiveSyncInfo = F4SE::CreateVariantId(1349978, 2214289, 2214289);
		inline constexpr auto InitializeActorInstant = F4SE::CreateVariantId(672857, 2236393, 2236393);
		inline constexpr auto IsActiveGraphInTransition = F4SE::CreateVariantId(839650, 2214305, 2214305);
	}

	namespace BGSArrestEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(309362, 2663413, 2663413);
	}

	namespace BGSAssaultActorEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(355870, 2663399, 2663399);
	}

	namespace BGSAttachParentArray
	{
		inline constexpr auto SetParentGroupNumber = F4SE::CreateVariantId(1412266, 2189125, 2189125);
	}

	namespace BGSAttractionObject
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(967451, 2663419, 2663419);
	}

	namespace BGSBribeNPCEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(113293, 2663404, 2663404);
	}

	namespace BGSCastMagicEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(1210444, 2663414, 2663414);
	}

	namespace BGSChangeLocationEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(528859, 2663415, 2663415);
	}

	namespace BGSClearLocationEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(1406072, 2663423, 2663423);
	}

	namespace BGSCraftItemEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(1382765, 2663430, 2663430);
	}

	namespace BGSCreatedObjectManager
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(1000678, 2689006, 4796296);
		inline constexpr auto DecrementRef = F4SE::CreateVariantId(230928, 2228455, 2228455);
		inline constexpr auto IncrementRef = F4SE::CreateVariantId(1042515, 2228454, 2228454);
	}

	namespace BGSCrimeGoldEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(990529, 2663412, 2663412);
	}

	namespace BGSCureEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(920813, 2663433, 2663433);
	}

	namespace BGSDecalManager
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(716374, 2689264, 4796551);
	}

	namespace BGSDefaultObject
	{
		inline constexpr auto ctor = F4SE::CreateVariantId(1144014, 2197003, 2197003);
		inline constexpr auto Singleton = F4SE::CreateVariantId(561749, 2690473, 4797762);
	}

	namespace BGSDefaultObjectManager
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(484974, 2192850, 2192850);
	}

	namespace BGSDialogueEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(43243, 2663425, 2663425);
	}

	namespace BGSDiscoverDeadBodyEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(1140233, 2663435, 2663435);
	}

	namespace BGSDynamicPersistenceManager
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(109630, 2689026, 4796312);
		inline constexpr auto DemoteReference = F4SE::CreateVariantId(222813, 2193820, 2193820);
		inline constexpr auto PromoteReference = F4SE::CreateVariantId(1300345, 2193819, 2193819);
	}

	namespace BGSEntryPoint
	{
		inline constexpr auto HandleEntryPoint = F4SE::CreateVariantId(714336, 2206243, 2206243);
	}

	namespace BGSEscapeJailEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(771655, 2663410, 2663410);
	}

	namespace BGSEventProcessedEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1167364, 2201803, 2201803);
	}

	namespace BGSFavorEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(262770, 2663427, 2663427);
	}

	namespace BGSFlatterNPCEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(1014013, 2663405, 2663405);
	}

	namespace BGSHackTerminal
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(1186942, 2663421, 2663421);
	}

	namespace BGSHelloEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(944155, 2663426, 2663426);
	}

	namespace BGSIncreaseLevelEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(575487, 2663401, 2663401);
	}

	namespace BGSInfectionEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(19653, 2663432, 2663432);
	}

	namespace BGSIntimidateNPCEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(795005, 2663403, 2663403);
	}

	namespace BGSInventoryInterface
	{
		inline constexpr auto ForceMergeStacks = F4SE::CreateVariantId(1356509, 2194032, 2194032);
		inline constexpr auto RequestInventoryItem = F4SE::CreateVariantId(1200959, 2194009, 2194009);
		inline constexpr auto Singleton = F4SE::CreateVariantId(501899, 2689299, 4796586);
	}

	namespace BGSInventoryItem
	{
		inline constexpr auto FindAndWriteStackData = F4SE::CreateVariantId(770140, 2194123, 2194123);
		inline constexpr auto GetDisplayFullName01 = F4SE::CreateVariantId(277641, 2194079, 2194079);
		inline constexpr auto GetDisplayFullName02 = F4SE::CreateVariantId(623232, 2194080, 2194080);
		inline constexpr auto GetExtraDataAt = F4SE::CreateVariantId(851493, 2194092, 2194092);
		inline constexpr auto GetInstanceData = F4SE::CreateVariantId(491493, 2194072, 2194072);
		inline constexpr auto GetInventoryValue = F4SE::CreateVariantId(430292, 2194099, 2194099);
		inline constexpr auto GetStackCount = F4SE::CreateVariantId(82050, 2194107, 2194107);
		inline constexpr auto GetTotalWeight = F4SE::CreateVariantId(571297, 2194074, 2194074);
		inline constexpr auto IsEquipped = F4SE::CreateVariantId(806787, 2194086, 2194086);
		inline constexpr auto IsQuestObject = F4SE::CreateVariantId(823447, 2194076, 2194076);
		inline constexpr auto MergeStacks = F4SE::CreateVariantId(1132179, 2194109, 2194109);
	}

	namespace BGSInventoryList
	{
		inline constexpr auto ctor = F4SE::CreateVariantId(845050, 2194153, 2194153);
		inline constexpr auto BuildFromContainer = F4SE::CreateVariantId(551792, 2194158, 2194158);
		inline constexpr auto FindAndWriteStackDataForItem = F4SE::CreateVariantId(1354005, 2194179, 2194179);
	}

	namespace BGSIronSights
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(285964, 2663420, 2663420);
	}

	namespace BGSJailEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(552352, 2663408, 2663408);
	}

	namespace BGSKeyword
	{
		inline constexpr auto TypedKeywords = F4SE::CreateVariantId(1095775, 2692038, 4799330);
	}

	namespace BGSKillActorEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(1037338, 2663398, 2663398);
	}

	namespace BGSLoadGameBuffer
	{
		inline constexpr auto LoadDataEndian = F4SE::CreateVariantId(1451631, 2228270, 2228270);
	}

	namespace BGSLocalizedStringDL
	{
		inline constexpr auto StringInfoMap = F4SE::CreateVariantId(181435, 2661467, 2661467);
		inline constexpr auto GetText = F4SE::CreateVariantId(472297, 2194238, 2194238);
	}

	namespace BGSLocalizedStringIL
	{
		inline constexpr auto StringInfoMap = F4SE::CreateVariantId(1497866, 2661471, 2661471);
	}

	namespace BGSLocalizedStringPL
	{
		inline constexpr auto StringInfoMap = F4SE::CreateVariantId(446944, 2661461, 2661461);
	}

	namespace BGSLocation
	{
		inline constexpr auto LinkedLocations = F4SE::CreateVariantId(319631, 2661720, 2661720);
	}

	namespace BGSLocationLoadedEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(808292, 2201804, 2201804);
	}

	namespace BGSLocationLoadedStoryEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(748430, 2663417, 2663417);
	}

	namespace BGSMaterialType
	{
		inline constexpr auto MaterialIDMap = F4SE::CreateVariantId(430602, 2661839, 2661839);
	}

	namespace BGSMessage
	{
		inline constexpr auto GetConvertedDescription = F4SE::CreateVariantId(8331, 2203353, 2203353);
	}

	namespace BGSMod
	{
		namespace Attachment
		{
			inline constexpr auto LooseModMap = F4SE::CreateVariantId(1108112, 2661616, 2661616);

			namespace Mod
			{
				inline constexpr auto FindFilesForLooseMod = F4SE::CreateVariantId(410363, 2197524, 2197524);
				inline constexpr auto GetData = F4SE::CreateVariantId(33658, 0, 0); // inlined post next-gen
				inline constexpr auto GetLooseMod = F4SE::CreateVariantId(1359613, 2197514, 2197514);
				inline constexpr auto SetLooseMod = F4SE::CreateVariantId(123132, 2197558, 2197558);
			}
		}

		namespace Container
		{
			inline constexpr auto GetData = F4SE::CreateVariantId(659507, 2189206, 2189206);
		}

		namespace Template
		{
			namespace Items
			{
				inline constexpr auto CreateInstanceDataForObjectAndExtra = F4SE::CreateVariantId(147297, 2189244, 2189244);
			}
		}
	}

	namespace BGSNewVoicePowerEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(239479, 2663434, 2663434);
	}

	namespace BGSNumericIDIndex
	{
		inline constexpr auto GetNumericID = F4SE::CreateVariantId(915982, 2228199, 2228199);
		inline constexpr auto SetNumericID = F4SE::CreateVariantId(1527703, 2228200, 2228200);
	}

	namespace BGSObjectInstance
	{
		inline constexpr auto ctor = F4SE::CreateVariantId(1095748, 2197563, 2197563);
	}

	namespace BGSObjectInstanceExtra
	{
		inline constexpr auto ctor = F4SE::CreateVariantId(1222521, 2189015, 2189015);
		inline constexpr auto AddMod = F4SE::CreateVariantId(1191757, 2189025, 2189025);
		inline constexpr auto AttachModToReference = F4SE::CreateVariantId(3303, 2189033, 2189033);
		inline constexpr auto GetNumMods = F4SE::CreateVariantId(1526690, 2189019, 2189019);
		inline constexpr auto HasMod = F4SE::CreateVariantId(963890, 2189026, 2189026);
		inline constexpr auto RemoveInvalidMods = F4SE::CreateVariantId(1548060, 2189028, 2189028);
		inline constexpr auto RemoveMod = F4SE::CreateVariantId(1136607, 2189027, 2189027);
	}

	namespace BGSOnActorAttachEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(66772, 2663418, 2663418);
	}

	namespace BGSOnPlayerCompanionDismiss
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(448593, 2201805, 2201805);
	}

	namespace BGSOnPlayerCreateRobotEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(89625, 2201806, 2201806);
	}

	namespace BGSOnPlayerEnterVertibirdEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1312499, 2201807, 2201807);
	}

	namespace BGSOnPlayerFallLongDistances
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(953392, 2201808, 2201808);
	}

	namespace BGSOnPlayerFireWeaponEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(594318, 2201809, 2201809);
	}

	namespace BGSOnPlayerHealTeammateEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(234967, 2201810, 2201810);
	}

	namespace BGSOnPlayerModArmorWeaponEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1457918, 2201811, 2201811);
	}

	namespace BGSOnPlayerModRobotEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1098671, 2201812, 2201812);
	}

	namespace BGSOnPlayerSwimmingEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(739665, 2201813, 2201813);
	}

	namespace BGSOnPlayerUseWorkbenchEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(379998, 2201814, 2201814);
	}

	namespace BGSOnSpeechChallengeAvailable
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(20387, 2201815, 2201815);
	}

	namespace BGSOpenCloseForm
	{
		inline constexpr auto AutoCloseRef = F4SE::CreateVariantId(1175698, 2192797, 2192797);
		inline constexpr auto GetOpenState = F4SE::CreateVariantId(1480253, 2192799, 2192799);
		inline constexpr auto HasOnlyOpenCloseAnims = F4SE::CreateVariantId(45754, 2192796, 2192796);
		inline constexpr auto IsAnimating = F4SE::CreateVariantId(495235, 2192801, 2192801);
		inline constexpr auto IsOpenCloseEvent = F4SE::CreateVariantId(1016560, 2192795, 2192795);
		inline constexpr auto IsOpenCloseForm = F4SE::CreateVariantId(860629, 2192790, 2192790);
		inline constexpr auto SetOpenState = F4SE::CreateVariantId(895942, 2192798, 2192798);
	}

	namespace BGSPayFine
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(1233594, 2663407, 2663407);
	}

	namespace BGSPickLockEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(701969, 2663431, 2663431);
	}

	namespace BGSPickPocket
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(505459, 2663422, 2663422);
	}

	namespace BGSPlayerGetsFavorEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(332712, 2663406, 2663406);
	}

	namespace BGSPrimitive
	{
		inline constexpr auto CreateAbstract = F4SE::CreateVariantId(1095144, 2194290, 2194290);
	}

	namespace BGSQuestInstanceText
	{
		inline constexpr auto ParseString = F4SE::CreateVariantId(141681, 2206630, 2206630);
	}

	namespace BGSRadiationDamageEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1244003, 2201816, 2201816);
	}

	namespace BGSRelationshipChangeRankEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(1476498, 2663402, 2663402);
	}

	namespace BGSRemoveFromPlayerEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(482080, 2663429, 2663429);
	}

	namespace BGSSaveGameBuffer
	{
		inline constexpr auto SaveDataEndian = F4SE::CreateVariantId(594281, 2228319, 2228319);
	}

	namespace BGSSaveLoadFileEntry
	{
		inline constexpr auto DeleteGame = F4SE::CreateVariantId(91575, 2227855, 2227855);
		inline constexpr auto LoadData = F4SE::CreateVariantId(741580, 2227871, 2227871);
	}

	namespace BGSSaveLoadManager
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(1247320, 2697802, 2697802);
		inline constexpr auto BufferSceneScreenShot = F4SE::CreateVariantId(1234898, 2228079, 2228079);
		inline constexpr auto BuildSaveGameList = F4SE::CreateVariantId(1342984, 2228053, 2228053);
		inline constexpr auto GetFullPath = F4SE::CreateVariantId(505311, 2228030, 2228030);
		inline constexpr auto GetSaveDirectoryPath = F4SE::CreateVariantId(1569549, 2228028, 2228028);
		inline constexpr auto IsLoadingAllowed = F4SE::CreateVariantId(361558, 2228047, 2228047);
		inline constexpr auto IsSavingAllowed = F4SE::CreateVariantId(735045, 2228045, 2228045);
		inline constexpr auto QueueSaveLoadTask = F4SE::CreateVariantId(1487308, 2228080, 2228080);
		inline constexpr auto Quickload = F4SE::CreateVariantId(603305, 2228042, 2228042);
		inline constexpr auto Quicksave = F4SE::CreateVariantId(1055666, 2228041, 2228041);
		inline constexpr auto AutosaveImpl = F4SE::CreateVariantId(1280471, 2228043, 2228043);
		inline constexpr auto DeleteSaveFileImpl = F4SE::CreateVariantId(809711, 2228033, 2228033);
		inline constexpr auto GenerateSaveFileNameImpl = F4SE::CreateVariantId(434834, 2228059, 2228059);
		inline constexpr auto LoadGameImpl = F4SE::CreateVariantId(540706, 2228040, 2228040);
		inline constexpr auto SaveGameImpl = F4SE::CreateVariantId(954817, 2228036, 2228036);
	}

	namespace BGSScene
	{
		inline constexpr auto ResetAllSceneActions = F4SE::CreateVariantId(1356678, 2206864, 2206864);
		inline constexpr auto SetSceneActive = F4SE::CreateVariantId(820354, 2206845, 2206845);
	}

	namespace BGSSceneActionNPCResponseDialogue
	{
		inline constexpr auto GetCurrentTopicInfo = F4SE::CreateVariantId(1369299, 2206977, 2206977);
	}

	namespace BGSSceneActionPlayerDialogue
	{
		inline constexpr auto GetCurrentTopicInfo = F4SE::CreateVariantId(781358, 2196825, 2196825);
	}

	namespace BGSScriptEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(725199, 2663424, 2663424);
	}

	namespace BGSServedTime
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(1482083, 2663409, 2663409);
	}

	namespace BGSStartQuestEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(1429380, 2663416, 2663416);
	}

	namespace BGSStoryEventManager
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(1160067, 2693504, 4800796);
		inline constexpr auto AddEvent = F4SE::CreateVariantId(312533, 2214088, 2214088);
	}

	namespace BGSStoryTeller
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(562259, 2689008, 4796298);
		inline constexpr auto QuestsLock = F4SE::CreateVariantId(315357, 2693510, 4800802);
		inline constexpr auto FindQuestLock = F4SE::CreateVariantId(534915, 2693512, 4800804);
	}

	namespace BGSSynchronizedAnimationManager
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(1346879, 2690996, 4798289);
		inline constexpr auto IsReferenceInSynchronizedScene = F4SE::CreateVariantId(915329, 2214437, 2214437);
	}

	namespace BGSTerminal
	{
		inline constexpr auto GetHackDifficultyLockLevel = F4SE::CreateVariantId(537273, 2197777, 2197777);
		inline constexpr auto IsTerminalRefInUse = F4SE::CreateVariantId(1093565, 2197779, 2197779);
		inline constexpr auto Show = F4SE::CreateVariantId(1069012, 2197776, 2197776);
	}

	namespace BGSTrespassEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(90057, 2663411, 2663411);
	}

	namespace BGSTriggerMineExplosionEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(1256916, 2663400, 2663400);
	}

	namespace BSAudioManager
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(1321158, 2703058, 2703058);
		inline constexpr auto GetSoundHandleByFile = F4SE::CreateVariantId(37039, 2267103, 2267103);
		inline constexpr auto GetSoundHandleByName = F4SE::CreateVariantId(196484, 2267105, 2267105);
	}

	namespace BSAwardsSystemUtility
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(1569384, 2255115, 2255115);
	}

	namespace BSGFxDisplayObject
	{
		inline constexpr auto RemoveChild = F4SE::CreateVariantId(1229383, 2287327, 2287327);
	}

	namespace BSGFxObject
	{
		inline constexpr auto AcquireFlashObjectByMemberName = F4SE::CreateVariantId(1172680, 2287014, 2287014);
		inline constexpr auto AcquireFlashObjectByPath = F4SE::CreateVariantId(1065592, 2287015, 2287015);
	}

	namespace BSGFxShaderFXTarget
	{
		inline constexpr auto AppendShaderFXInfos = F4SE::CreateVariantId(544646, 2287021, 2287021);
		inline constexpr auto CreateAndSetFiltersToColor01 = F4SE::CreateVariantId(1487925, 2287028, 2287028);
		inline constexpr auto CreateAndSetFiltersToColor02 = F4SE::CreateVariantId(783104, 2287029, 2287029);
		inline constexpr auto CreateAndSetFiltersToHUD = F4SE::CreateVariantId(876001, 2287027, 2287027);
		inline constexpr auto EnableShadedBackground = F4SE::CreateVariantId(278402, 2287022, 2287022);
		inline constexpr auto ProcessEvent = F4SE::CreateVariantId(848563, 2287033, 2287033);
	}

	namespace BSGraphics
	{
		inline constexpr auto CurrentRendererWindow = F4SE::CreateVariantId(91810, 2704431, 2704431);

		namespace RenderData
		{
			inline constexpr auto Singleton = F4SE::CreateVariantId(1235449, 2704429, 2704429);
		}

		namespace RenderTargetManager
		{
			inline constexpr auto Singleton = F4SE::CreateVariantId(1508457, 2666735, 2666735);
			inline constexpr auto SetEnableDynamicResolution = F4SE::CreateVariantId(116947, 2277197, 2277197);
		}

		namespace Renderer
		{
			inline constexpr auto IncRef = F4SE::CreateVariantId(1337764, 2276869, 2276869);
			inline constexpr auto DecRef = F4SE::CreateVariantId(194808, 2276870, 2276870);
			inline constexpr auto Begin = F4SE::CreateVariantId(288964, 2276833, 2276833);
			inline constexpr auto End = F4SE::CreateVariantId(700869, 2276834, 2276834);
		}

		namespace State
		{
			inline constexpr auto Singleton = F4SE::CreateVariantId(600795, 2704621, 2704621);
		}

		namespace Utility
		{
			inline constexpr auto ConvertHALFToNiPoint3Stream = F4SE::CreateVariantId(463129, 2277113, 2277113);
			inline constexpr auto ConvertNiPoint3ToHALFStream = F4SE::CreateVariantId(1247946, 2277114, 2277114);
			inline constexpr auto PackVertexData = F4SE::CreateVariantId(156126, 2277106, 2277106);
			inline constexpr auto UnpackVertexData = F4SE::CreateVariantId(990748, 2277129, 2277129);
		}
	}

	namespace BSIdleInputWatcher
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(487306, 2693716, 4801008);
	}

	namespace BSInputDevice
	{
		inline constexpr auto CreateButtonEvent = F4SE::CreateVariantId(250821, 2268476, 2268476);
	}

	namespace BSInputDeviceManager
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(1284221, 2694300, 4807767);
	}

	namespace BSInputEnableLayer
	{
		inline constexpr auto DecRef = F4SE::CreateVariantId(659989, 2268272, 2268272);
	}

	namespace BSInputEnableManager
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(781703, 2689007, 4796297);
		inline constexpr auto AllocateNewLayer = F4SE::CreateVariantId(537494, 2268244, 2268244);
		inline constexpr auto EnableOtherEvent = F4SE::CreateVariantId(1419268, 2268265, 2268265);
		inline constexpr auto EnableUserEvent = F4SE::CreateVariantId(1432984, 2268263, 2268263);
	}

	namespace BSInputEventQueue
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(664562, 2694386, 4801677);
	}

	namespace BSModelDB
	{
		inline constexpr auto Demand01 = F4SE::CreateVariantId(1066398, 2275153, 2275153);
		inline constexpr auto Demand02 = F4SE::CreateVariantId(1225688, 2275154, 2275154);
	}

	namespace BSPointerHandle
	{
		namespace BSPointerHandleManagerInterface
		{
			inline constexpr auto GetHandle = F4SE::CreateVariantId(901626, 2188676, 2188676);
			inline constexpr auto GetSmartPointer = F4SE::CreateVariantId(967277, 2188681, 2188681);
		}
	}

	namespace BSPrecisionTimer
	{
		inline constexpr auto FrequencyMS = F4SE::CreateVariantId(711608, 2666309, 2666309);
		inline constexpr auto FrequencyMSRecip = F4SE::CreateVariantId(29307, 2666310, 2666310);
	}

	namespace BSRandom
	{
		inline constexpr auto Generator = F4SE::CreateVariantId(254053, 2666295, 2666295);
	}

	namespace BSResource
	{
		inline constexpr auto GetOrCreateStream = F4SE::CreateVariantId(1143155, 2269490, 2269490);
		inline constexpr auto RegisterLocation = F4SE::CreateVariantId(918408, 2269481, 2269481);

		namespace EntryDBBaseUtil
		{
			inline constexpr auto ReleaseEntryAction = F4SE::CreateVariantId(777279, 2269463, 2269463);
		}

		namespace GlobalLocations
		{
			inline constexpr auto Singleton = F4SE::CreateVariantId(1573818, 2703394, 2703394);
		}

		namespace GlobalPaths
		{
			inline constexpr auto Singleton = F4SE::CreateVariantId(210868, 2703393, 2703393);
		}

		namespace ID
		{
			inline constexpr auto GenerateFromPath = F4SE::CreateVariantId(570861, 2269259, 2269259);
		}
	}

	namespace BSResourceNiBinaryStream
	{
		inline constexpr auto ctor = F4SE::CreateVariantId(1198116, 2269830, 2269830);
		inline constexpr auto dtor = F4SE::CreateVariantId(1516202, 2269832, 2269832);
		inline constexpr auto BinaryStreamWithRescan = F4SE::CreateVariantId(543595, 2205871, 2205871);
		inline constexpr auto DoRead = F4SE::CreateVariantId(424286, 2269839, 2269839);
		inline constexpr auto DoWrite = F4SE::CreateVariantId(1208863, 2269840, 2269840);
		inline constexpr auto GetBufferInfo = F4SE::CreateVariantId(265501, 2269836, 2269836);
		inline constexpr auto Seek = F4SE::CreateVariantId(358512, 2269834, 2269834);
	}

	namespace BSScaleformManager
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(106578, 2689600, 4796889);
		inline constexpr auto GetMovieFilename = F4SE::CreateVariantId(1191277, 2287428, 2287428);
		inline constexpr auto InitMovieViewport = F4SE::CreateVariantId(206895, 2287430, 4494254);
		inline constexpr auto LoadMovieImpl = F4SE::CreateVariantId(1526234, 2287422, 2287422);
	}

	namespace BSScaleformRenderer
	{
		inline constexpr auto Initialize = F4SE::CreateVariantId(1403529, 2284938, 2284938);
	}

	namespace BSScaleformTranslator
	{
		inline constexpr auto AddTranslations = F4SE::CreateVariantId(810671, 2295298, 2295298);
	}

	namespace BSScript
	{
		namespace Internal
		{
			namespace Stack
			{
				inline constexpr auto GetPageForFrame = F4SE::CreateVariantId(1429302, 2314680, 2314680);
				inline constexpr auto GetStackFrameVariable = F4SE::CreateVariantId(897539, 2314681, 2314681);
			}
		}

		namespace NF_util
		{
			namespace NativeFunctionBase
			{
				inline constexpr auto Call = F4SE::CreateVariantId(571037, 2314780, 2314780);
			}
		}

		namespace Object
		{
			inline constexpr auto IncRef = F4SE::CreateVariantId(461710, 2314436, 2314436);
			inline constexpr auto DecRef = F4SE::CreateVariantId(541793, 2314437, 2314437);
		}
	}

	namespace BSShaderProperty
	{
		inline constexpr auto SetMaterial = F4SE::CreateVariantId(706318, 2316285, 2316285);
	}

	namespace BSShaderTextureSet
	{
		inline constexpr auto CreateObject = F4SE::CreateVariantId(993063, 2316324, 2316324);
	}

	namespace BSShaderUtil
	{
		inline constexpr auto SetMaterialAlpha = F4SE::CreateVariantId(211260, 2317566, 2317566);
	}

	namespace BSSoundHandle
	{
		inline constexpr auto FadeInPlay = F4SE::CreateVariantId(353528, 2267075, 2267075);
		inline constexpr auto FadeOutAndRelease = F4SE::CreateVariantId(260328, 2267076, 2267076);
		inline constexpr auto HolotapeSoundHandle = F4SE::CreateVariantId(965852, 2664207, 2664207);
		inline constexpr auto Pause = F4SE::CreateVariantId(1168427, 2267044, 2267044);
		inline constexpr auto Play = F4SE::CreateVariantId(384073, 2267042, 2267042);
		inline constexpr auto PlayAfter = F4SE::CreateVariantId(557072, 2267043, 2267043);
		inline constexpr auto Stop = F4SE::CreateVariantId(1340948, 2267045, 2267045);
		inline constexpr auto SetOutputModel = F4SE::CreateVariantId(170407, 2267053, 2267053);
	}

	namespace BSStringPool
	{
		inline constexpr auto FindEntry_char = F4SE::CreateVariantId(1239592, 2268727, 2268727);
		inline constexpr auto FindEntry_wchar = F4SE::CreateVariantId(82204, 2268728, 2268728);
		inline constexpr auto GetEntry_char = F4SE::CreateVariantId(507142, 2268729, 2268729);
		inline constexpr auto GetEntry_wchar = F4SE::CreateVariantId(345043, 2268730, 2268730);

		namespace Entry
		{
			inline constexpr auto Release = F4SE::CreateVariantId(1204430, 2268720, 2268720);
		}
	}

	namespace BSSystemFileStreamer
	{
		inline constexpr auto UncacheAll = F4SE::CreateVariantId(40925, 2268797, 2268797);
	}

	namespace BSTempEffectWeaponBlood
	{
		inline constexpr auto ClearEffectForWeapon = F4SE::CreateVariantId(718866, 2212158, 2212158);
	}

	namespace BSTEvent
	{
		namespace BSTGlobalEvent
		{
			inline constexpr auto Singleton = F4SE::CreateVariantId(1424022, 2688814, 4796078);
		}
	}

	namespace BSTempEffectDebris
	{
		inline constexpr auto ctor = F4SE::CreateVariantId(1075623, 2212059, 2212059);
	}

	namespace BSThreadEvent
	{
		inline constexpr auto InitSDM = F4SE::CreateVariantId(1425097, 2268180, 2268180);
	}

	namespace BSTimer
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(1256126, 2703179, 2703179);
		inline constexpr auto GlobalTimeMultiplier = F4SE::CreateVariantId(365546, 2666307, 2666307);
		inline constexpr auto GlobalTimeMultiplierTarget = F4SE::CreateVariantId(1266509, 2666308, 2666308);
		inline constexpr auto SetGlobalTimeMultiplier = F4SE::CreateVariantId(1419977, 2267970, 2267970);
	}

	namespace BSUIMessageData
	{
		inline constexpr auto SendUIBoolMessage = F4SE::CreateVariantId(1388308, 2284981, 2284981);
		inline constexpr auto SendUIPtrMessage = F4SE::CreateVariantId(1374542, 2284982, 2284982);
		inline constexpr auto SendUIStringMessage = F4SE::CreateVariantId(1270833, 2284977, 2284977);
		inline constexpr auto SendUIStringUIntMessage = F4SE::CreateVariantId(99795, 2284979, 2284979);
	}

	namespace BSUtilities
	{
		inline constexpr auto ConvertFloatToHalf = F4SE::CreateVariantId(10414, 2212098, 2212098);
		inline constexpr auto ConvertHalfToFloat = F4SE::CreateVariantId(1502141, 2195843, 2195843);
		inline constexpr auto GetObjectByName = F4SE::CreateVariantId(843650, 2274841, 2274841);
	}

	namespace BarterMenu
	{
		inline constexpr auto ClearTradingData = F4SE::CreateVariantId(1112285, 2222700, 2222700);
		inline constexpr auto CompleteTrade = F4SE::CreateVariantId(379932, 2222701, 2222701);
		inline constexpr auto GetCapsOwedByPlayer = F4SE::CreateVariantId(672405, 2222714, 2222714);
	}

	namespace BobbleheadCollected
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(1542436, 2233716, 2233716);
		}
	}

	namespace Bounty
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(212496, 2233717, 2233717);
		}
	}

	namespace BucketTable
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(1390486, 2268736, 2268736);
	}

	namespace Calendar
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(1444952, 2689092, 4796378);
	}

	namespace CanDisplayNextHUDMessage
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(344866, 2695041, 4802332);
	}

	namespace CellAttachDetachEvent
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(862142, 2192250, 2192250);
	}

	namespace ChestLooted
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(464264, 2233718, 2233718);
		}
	}

	namespace ColorUpdateEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1226590, 2695540, 4802831);
	}

	namespace CombatFormulas
	{
		inline constexpr auto CalcResistedPercentage = F4SE::CreateVariantId(420470, 2209007, 2209007);
		inline constexpr auto CalcScopeSteadyActionPointDrain = F4SE::CreateVariantId(380926, 2209045, 2209045);
		inline constexpr auto CalcTargetedLimbDamage = F4SE::CreateVariantId(1530751, 2209033, 2209033);
		inline constexpr auto CalculateAimModelWobble = F4SE::CreateVariantId(211411, 2209001, 2209001);
		inline constexpr auto GetNumCrippledAttackConditions = F4SE::CreateVariantId(170270, 2209041, 2209041);
		inline constexpr auto GetWeaponDisplayAccuracy = F4SE::CreateVariantId(1137654, 2209049, 2209049);
		inline constexpr auto GetWeaponDisplayDamage = F4SE::CreateVariantId(1431014, 2209046, 2209046);
		inline constexpr auto GetWeaponDisplayRange = F4SE::CreateVariantId(1324037, 2209047, 2209047);
		inline constexpr auto GetWeaponDisplayRateOfFire = F4SE::CreateVariantId(1403591, 2209048, 2209048);
	}

	namespace CombatUtilities
	{
		inline constexpr auto CalculateProjectileLOS01 = F4SE::CreateVariantId(798616, 2240617, 2240617);
		inline constexpr auto CalculateProjectileLOS02 = F4SE::CreateVariantId(55339, 2240616, 2240616);
		inline constexpr auto CalculateProjectileTrajectory = F4SE::CreateVariantId(1575156, 2240611, 2240611);
		inline constexpr auto WorldGravity = F4SE::CreateVariantId(1378547, 2700340, 2700340);
	}

	namespace ComparisonQualifiers
	{
		inline constexpr auto ContainerQualifier = F4SE::CreateVariantId(883895, 2190674, 2190674);
		inline constexpr auto UIQualifier = F4SE::CreateVariantId(179412, 2190675, 2190675);
	}

	namespace Console
	{
		inline constexpr auto CurrentPickIndex = F4SE::CreateVariantId(1407033, 2701382, 2701382);
		inline constexpr auto ExecuteCommand = F4SE::CreateVariantId(1061864, 2248537, 2248537);
		inline constexpr auto PickRef = F4SE::CreateVariantId(170742, 2701395, 2701395);
		inline constexpr auto PickRefs = F4SE::CreateVariantId(875116, 2701391, 2701391);
		inline constexpr auto SetCurrentPickREFR = F4SE::CreateVariantId(79066, 2248551, 2248551);
	}

	namespace ConsoleLog
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(689441, 2690148, 4797437);
		inline constexpr auto AddStringLock = F4SE::CreateVariantId(1174138, 2701408, 2701408);
		inline constexpr auto AddString = F4SE::CreateVariantId(764, 2248593, 2248593);
	}

	namespace ContainerMenu
	{
		inline constexpr auto TakeAllItems = F4SE::CreateVariantId(1323703, 2248619, 2248619);
	}

	namespace ContainerMenuBase
	{
		namespace ItemSorter
		{
			inline constexpr auto IncrementSort = F4SE::CreateVariantId(1307263, 2222848, 2222848);
		}
	}

	namespace ControlMap
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(325206, 2692014, 4799307);
		inline constexpr auto PopInputContext = F4SE::CreateVariantId(74587, 2268336, 2268336);
		inline constexpr auto PushInputContext = F4SE::CreateVariantId(1404410, 2268335, 2268335);
		inline constexpr auto RemapButton = F4SE::CreateVariantId(11351, 2268330, 2268330);
		inline constexpr auto SaveRemappings = F4SE::CreateVariantId(1141541, 2268331, 2268331);
		inline constexpr auto SetTextEntryMode = F4SE::CreateVariantId(1270079, 2268339, 4491359);
	}

	namespace CorpseEaten
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(717261, 2233719, 2233719);
		}
	}

	namespace CriticalHitEvent
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(969000, 2233720, 2233720);
		}
	}

	namespace CurrentRadiationSourceCount
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(696410, 2696196, 4803487);
	}

	namespace CustomMarkerUpdate
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(1221626, 2233721, 2233721);
		}
	}

	namespace DEFAULT_OBJECT_DATA
	{
		inline constexpr auto DefaultObjects = F4SE::CreateVariantId(838886, 838886, 838886); // same for all versions
	}

	namespace DaysJailed
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(1473833, 2233722, 2233722);
		}
	}

	namespace DialogueMenuUtils
	{
		inline constexpr auto CloseMenu = F4SE::CreateVariantId(764651, 2249659, 2249659);
		inline constexpr auto OpenMenu = F4SE::CreateVariantId(1562703, 2249658, 2249658);
		inline constexpr auto ShowSpeechChallengeAnim = F4SE::CreateVariantId(868159, 2249665, 2249665);
	}

	namespace DoBeforeNewOrLoadCompletedEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(787908, 2695542, 4802833);
	}

	namespace EffectItem
	{
		inline constexpr auto GetDescription = F4SE::CreateVariantId(949839, 2189612, 2189612);
	}

	namespace EquippedWeaponData
	{
		inline constexpr auto SetupFireSounds = F4SE::CreateVariantId(1468462, 2232275, 2232275);
	}

	namespace ExamineMenu
	{
		inline constexpr auto BuildConfirmed = F4SE::CreateVariantId(1396668, 2223013, 2223013);
		inline constexpr auto BuildWeaponScrappingArray = F4SE::CreateVariantId(646841, 2223077, 2223077);
		inline constexpr auto ConsumeSelectedItems = F4SE::CreateVariantId(686586, 2223052, 2223052);
		inline constexpr auto GetSelectedIndex = F4SE::CreateVariantId(776503, 2223022, 2223022);
		inline constexpr auto ShowConfirmMenu = F4SE::CreateVariantId(443081, 2223081, 2223081);
	}

	namespace ExteriorCellSingleton
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(128691, 2689084, 4796370);
	}

	namespace ExtraDataList
	{
		inline constexpr auto CompareList = F4SE::CreateVariantId(585876, 2190098, 2190098);
		inline constexpr auto CreateInstanceData = F4SE::CreateVariantId(1280130, 2190185, 2190185);
	}

	namespace ExtraTextDisplayData
	{
		inline constexpr auto GetDisplayName = F4SE::CreateVariantId(1523343, 2191318, 2191318);
	}

	namespace FORM_ENUM_STRING
	{
		inline constexpr auto FormTypeStrings = F4SE::CreateVariantId(1309967, 1309967, 1309967); // same for all versions
	}

	namespace FatmanDeaths
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(143539, 2233723, 2233723);
		}
	}

	namespace FavoritesManager
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(198281, 2694399, 4801690);
		inline constexpr auto ClearCurrentAmmoCount = F4SE::CreateVariantId(541959, 2248745, 2248745);
		inline constexpr auto UseQuickkeyItem = F4SE::CreateVariantId(303130, 2248744, 2248744);
	}

	namespace FinePaid
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(395763, 2233724, 2233724);
		}
	}

	namespace FirstThirdPersonSwitch
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(648220, 2233725, 2233725);
		}
	}

	namespace FlatScreenModel
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(847741, 2694427, 4801718);
	}

	namespace FusionCoreConsumed
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(900334, 2233726, 2233726);
		}
	}

	namespace FusionCoreEjected
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(1152491, 2233727, 2233727);
		}
	}

	namespace GameMenuBase
	{
		inline constexpr auto AppendShaderFXInfos = F4SE::CreateVariantId(583584, 2223203, 2223203);
		inline constexpr auto CacheShaderFXQuadsForRenderer_Impl = F4SE::CreateVariantId(863029, 2223200, 2223200);
		inline constexpr auto OnMenuDisplayStateChanged = F4SE::CreateVariantId(1274450, 2223205, 2223205);
		inline constexpr auto SetIsTopButtonBar = F4SE::CreateVariantId(1367353, 2223204, 2223204);
		inline constexpr auto SetUpButtonBar = F4SE::CreateVariantId(531584, 2223197, 2223197);
		inline constexpr auto SetViewportRect = F4SE::CreateVariantId(1554334, 2223202, 2223202);
		inline constexpr auto TransferCachedShaderFXQuadsForRenderer = F4SE::CreateVariantId(65166, 2223201, 2223201);
	}

	namespace GamePlayFormulas
	{
		inline constexpr auto CalcSprintingActionPoints = F4SE::CreateVariantId(1053786, 2209071, 2209071);
		inline constexpr auto CalculateItemHealthDamageBonus = F4SE::CreateVariantId(612133, 2209087, 2209087);
		inline constexpr auto CanHackGateCheck = F4SE::CreateVariantId(269668, 2209069, 2209069);
		inline constexpr auto CanPickLockGateCheck = F4SE::CreateVariantId(1160841, 2209066, 2209066);
		inline constexpr auto GetExperienceReward = F4SE::CreateVariantId(853500, 2209076, 2209076);
		inline constexpr auto GetHackingWordCount = F4SE::CreateVariantId(190347, 2209067, 2209067);
		inline constexpr auto GetLockXPReward = F4SE::CreateVariantId(880926, 2209070, 2209070);
	}

	namespace GameScript
	{
		inline constexpr auto BindCObject01 = F4SE::CreateVariantId(1505389, 2249772, 2249772);
		inline constexpr auto BindCObject02 = F4SE::CreateVariantId(81787, 2249773, 2249773);

		namespace BasicEventHandler
		{
			inline constexpr auto Singleton = F4SE::CreateVariantId(1460997, 2702014, 2702014);
		}

		namespace CombatEventHandler
		{
			inline constexpr auto Singleton = F4SE::CreateVariantId(459907, 2701831, 2701831);
		}

		namespace CustomEventHandler
		{
			inline constexpr auto Singleton = F4SE::CreateVariantId(7183, 2701855, 2701855);
		}

		namespace DistanceEventHandler
		{
			inline constexpr auto Singleton = F4SE::CreateVariantId(764245, 2692010, 4799303);
		}

		namespace FragmentEventHandler
		{
			inline constexpr auto Singleton = F4SE::CreateVariantId(1417043, 2701848, 2701848);
		}

		namespace GameVM
		{
			inline constexpr auto Singleton = F4SE::CreateVariantId(996227, 2689134, 4796420);
			inline constexpr auto QueuePostRenderCall = F4SE::CreateVariantId(34412, 2251314, 2251314);
			inline constexpr auto RegisterForAllGameEvents = F4SE::CreateVariantId(680454, 2251353, 2251353);
			inline constexpr auto SendEventToObjectAndRelated = F4SE::CreateVariantId(367992, 2251344, 2251344);
		}

		namespace HandlePolicy
		{
			inline constexpr auto DropSaveLoadRemapData = F4SE::CreateVariantId(647657, 2249995, 2249995);
			inline constexpr auto GetInventoryObjFromHandle = F4SE::CreateVariantId(66597, 2249989, 2249989);
			inline constexpr auto GetInventoryObjOrFormFromHandle = F4SE::CreateVariantId(1316930, 2249988, 2249988);
			inline constexpr auto UpdatePersistence = F4SE::CreateVariantId(11020, 2249991, 2249991);
		}

		namespace InventoryEventHandler
		{
			inline constexpr auto Singleton = F4SE::CreateVariantId(1576434, 2701878, 2701878);
		}

		namespace LOSEventHandler
		{
			inline constexpr auto Singleton = F4SE::CreateVariantId(983179, 2692011, 4799304);
		}

		namespace MenuEventHandler
		{
			inline constexpr auto Singleton = F4SE::CreateVariantId(1562790, 2701898, 2701898);
		}

		namespace ObjectBindPolicy
		{
			inline constexpr auto EndSaveLoad = F4SE::CreateVariantId(1558837, 2250482, 2250482);
		}

		namespace SleepEventHandler
		{
			inline constexpr auto Singleton = F4SE::CreateVariantId(1455597, 2701936, 2701936);
		}

		namespace TeleportEventHandler
		{
			inline constexpr auto Singleton = F4SE::CreateVariantId(97940, 2702013, 2702013);
		}

		namespace TimerEventHandler
		{
			inline constexpr auto Singleton = F4SE::CreateVariantId(1202884, 2692012, 4799305);
		}

		namespace TrackedStatsEventHandler
		{
			inline constexpr auto Singleton = F4SE::CreateVariantId(317348, 2702012, 2702012);
		}

		namespace WaitEventHandler
		{
			inline constexpr auto Singleton = F4SE::CreateVariantId(536926, 2702011, 2702011);
		}
	}

	namespace GameSettingCollection
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(8308, 2690301, 4797590);
		inline constexpr auto InitCollection = F4SE::CreateVariantId(948832, 2188690, 2188690);
	}

	namespace GameUIModel
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(17419, 2695523, 4802814);
		inline constexpr auto SetGameColors = F4SE::CreateVariantId(523665, 2220911, 2220911);
		inline constexpr auto UpdateDataModels = F4SE::CreateVariantId(1269653, 2220905, 2220905);
	}

	namespace HUDDataModel
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(910584, 2694613, 4801904);
	}

	namespace HUDMenu
	{
		inline constexpr auto SetHUDColor = F4SE::CreateVariantId(505571, 2248918, 2248918);
	}

	namespace HUDMenuUtils
	{
		inline constexpr auto GetGameplayHUDBackgroundColor = F4SE::CreateVariantId(698605, 2248845, 2248845);
		inline constexpr auto GetGameplayHUDColor = F4SE::CreateVariantId(34363, 2248840, 2248840);
		inline constexpr auto WorldPtToScreenPt3 = F4SE::CreateVariantId(1132313, 2222464, 2222464);
	}

	namespace HUDModeEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(683142, 2694697, 4801988);
	}

	namespace HUDQuickContainerDataModel
	{
		inline constexpr auto TakeSelectedItem = F4SE::CreateVariantId(1401485, 2221653, 2221653);
	}

	namespace HolotapeChatterEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(884534, 2201817, 2201817);
	}

	namespace HolotapeMenu
	{
		inline constexpr auto ShowHolotapeInPipboy = F4SE::CreateVariantId(217953, 2224028, 2224028);
		inline constexpr auto ShowHolotapeInTerminal = F4SE::CreateVariantId(390509, 2224029, 2224029);
	}

	namespace HolotapePlayEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(525346, 2201818, 2201818);
	}

	namespace HolotapeStateChanged
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(1404654, 2233728, 2233728);
		}
	}

	namespace IAnimationGraphManagerHolder
	{
		inline constexpr auto RevertAnimationGraphManager = F4SE::CreateVariantId(41382, 2214541, 2214541);
		inline constexpr auto SetGraphVariableBool = F4SE::CreateVariantId(1437197, 2214543, 2214543);
		inline constexpr auto SetGraphVariableFloat = F4SE::CreateVariantId(27400, 2214545, 2214545);
		inline constexpr auto SetGraphVariableInt = F4SE::CreateVariantId(732926, 2214544, 2214544);
	}

	namespace IFormFactory
	{
		inline constexpr auto Factories = F4SE::CreateVariantId(228366, 2689177, 4796464);
	}

	namespace IMenu
	{
		inline constexpr auto OnSetSafeRect = F4SE::CreateVariantId(964859, 2287375, 2287375);
		inline constexpr auto PassesRenderConditionText = F4SE::CreateVariantId(937304, 2287379, 2287379);
		inline constexpr auto ProcessScaleformEvent = F4SE::CreateVariantId(150211, 2287395, 2287395);
		inline constexpr auto RefreshPlatform = F4SE::CreateVariantId(1071829, 2287374, 2287374);
		inline constexpr auto ShouldHandleEvent = F4SE::CreateVariantId(1241790, 2287392, 2287392);
	}

	namespace INIPrefSettingCollection
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(767844, 2703234, 2703234);
	}

	namespace INISettingCollection
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(791183, 2704108, 2704108);
	}

	namespace ImageSpaceEffectFullScreenBlur
	{
		inline constexpr auto IsDisabled = F4SE::CreateVariantId(372489, 2713225, 2713225);
	}

	namespace ImageSpaceEffectGetHit
	{
		inline constexpr auto IsDisabled = F4SE::CreateVariantId(1523708, 2713237, 2713237);
	}

	namespace ImageSpaceEffectHDR
	{
		inline constexpr auto UsePipboyScreenMask = F4SE::CreateVariantId(405286, 2678029, 4784697);
	}

	namespace ImageSpaceEffectPipboyScreen
	{
		inline constexpr auto IsPowerArmorPipboy = F4SE::CreateVariantId(1065542, 2713203, 2713203);
	}

	namespace ImageSpaceEffectRadialBlur
	{
		inline constexpr auto IsDisabled = F4SE::CreateVariantId(1500590, 2713225, 2713225);
	}

	namespace ImageSpaceEffectTemporalAA
	{
		inline constexpr auto MaskS = F4SE::CreateVariantId(775377, 2713052, 2713052);
	}

	namespace ImageSpaceManager
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(161743, 2712627, 2712627);
	}

	namespace ImageSpaceModifierInstance
	{
		inline constexpr auto Stop = F4SE::CreateVariantId(1298537, 2199897, 2199897);
	}

	namespace ImageSpaceModifierInstanceDOF
	{
		inline constexpr auto Trigger = F4SE::CreateVariantId(1158048, 2199922, 2199922);
	}

	namespace ImageSpaceModifierInstanceForm
	{
		inline constexpr auto Stop01 = F4SE::CreateVariantId(217873, 2199909, 2199909);
		inline constexpr auto Stop02 = F4SE::CreateVariantId(549773, 2199910, 2199910);
		inline constexpr auto Trigger01 = F4SE::CreateVariantId(179769, 2199906, 2199906);
		inline constexpr auto Trigger02 = F4SE::CreateVariantId(1216312, 2199907, 2199907);
	}

	namespace Interface3D
	{
		inline constexpr auto Create = F4SE::CreateVariantId(88488, 2222519, 2222519);
		inline constexpr auto Disable = F4SE::CreateVariantId(938370, 2222523, 2222523);
		inline constexpr auto DisableAll = F4SE::CreateVariantId(1470633, 2222521, 2222521);
		inline constexpr auto Enable = F4SE::CreateVariantId(326895, 2222522, 2222522);
		inline constexpr auto GetByName = F4SE::CreateVariantId(140387, 2222524, 2222524);
		inline constexpr auto MainScreen_AddPointLight = F4SE::CreateVariantId(1335675, 2222531, 2222531);
		inline constexpr auto MainScreen_AddSpotLight = F4SE::CreateVariantId(1056093, 2222532, 2222532);
		inline constexpr auto MainScreen_ClearLights = F4SE::CreateVariantId(683530, 2222533, 2222533);
		inline constexpr auto MainScreen_SetScreenAttached3D = F4SE::CreateVariantId(817727, 2222528, 2222528);
		inline constexpr auto MainScreen_SetWorldAttached3D = F4SE::CreateVariantId(724778, 2222529, 2222529);
		inline constexpr auto Offscreen_AddLight = F4SE::CreateVariantId(1267198, 2222543, 2222543);
		inline constexpr auto Offscreen_Clear3D = F4SE::CreateVariantId(1533262, 2222542, 2222542);
		inline constexpr auto Offscreen_ClearLights = F4SE::CreateVariantId(1039253, 2222545, 2222545);
		inline constexpr auto Offscreen_GetRenderTargetHeight = F4SE::CreateVariantId(1280897, 2222538, 2222538);
		inline constexpr auto Offscreen_GetRenderTargetWidth = F4SE::CreateVariantId(403273, 2222537, 2222537);
		inline constexpr auto Offscreen_Set3D = F4SE::CreateVariantId(43983, 2222541, 2222541);
		inline constexpr auto Offscreen_SetDebugMode = F4SE::CreateVariantId(1277879, 2222549, 2222549);
		inline constexpr auto Offscreen_SetDirectionalLight = F4SE::CreateVariantId(987144, 2222544, 2222544);
		inline constexpr auto Release = F4SE::CreateVariantId(74749, 2222520, 2222520);
		inline constexpr auto SetViewport = F4SE::CreateVariantId(825410, 2222552, 2222552);
	}

	namespace Inventory3DManager
	{
		inline constexpr auto Begin3D = F4SE::CreateVariantId(662659, 2249084, 2249084);
		inline constexpr auto ClearModel = F4SE::CreateVariantId(63218, 2249113, 2249113);
		inline constexpr auto DisableRendering = F4SE::CreateVariantId(255893, 2249099, 2249099);
		inline constexpr auto EnableRendering = F4SE::CreateVariantId(176578, 2249098, 2249098);
		inline constexpr auto End3D = F4SE::CreateVariantId(1512675, 2249086, 2249086);
		inline constexpr auto SetModelScale = F4SE::CreateVariantId(1319701, 2249097, 2249097);
		inline constexpr auto SetModelScreenPosition = F4SE::CreateVariantId(2967, 2249096, 2249096);
	}

	namespace InventoryItemDisplayData
	{
		inline constexpr auto ctor = F4SE::CreateVariantId(679373, 2222612, 2222612);
	}

	namespace InventoryUserUIUtils
	{
		inline constexpr auto AddItemCardInfoEntry = F4SE::CreateVariantId(489521, 2222648, 2222648);
	}

	namespace InvestmentMade
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(74865, 2233729, 2233729);
		}
	}

	namespace ItemCrafted
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(922450, 2233730, 2233730);
		}
	}

	namespace ItemPickpocketed
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(1362222, 2233731, 2233731);
		}
	}

	namespace ItemSteal
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(831553, 2233732, 2233732);
		}
	}

	namespace JailEscape
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(1083747, 2233733, 2233733);
		}
	}

	namespace Jailing
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(1335790, 2233734, 2233734);
		}
	}

	namespace JunkItemFound
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(5404, 2233735, 2233735);
		}
	}

	namespace LevelIncrease
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(349120, 2233736, 2233736);
		}
	}

	namespace LoadingMenu
	{
		inline constexpr auto PopulateLoadScreens = F4SE::CreateVariantId(316170, 2249232, 2249232);
		inline constexpr auto StartTestingLoadingMenu = F4SE::CreateVariantId(933696, 2249224, 2249224);
	}

	namespace LocationMarkerArrayUpdate
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(510524, 2233737, 2233737);
		}
	}

	namespace LockpickingMenu
	{
		inline constexpr auto CurrentLockRef = F4SE::CreateVariantId(1190207, 2701603, 2701603);
		inline constexpr auto CurrentLockLevel = F4SE::CreateVariantId(1495416, 2665059, 2665059);
		inline constexpr auto DamageLockpick = F4SE::CreateVariantId(1118991, 2249275, 2249275);
		inline constexpr auto OpenLockpickingMenu = F4SE::CreateVariantId(129892, 2249263, 2249263);
	}

	namespace LocksPicked
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(594991, 2249292, 2249292);
		}
	}

	namespace MagicTarget
	{
		inline constexpr auto IsTakingHealthDamageFromActiveEffect = F4SE::CreateVariantId(999442, 2226397, 2226397);
		inline constexpr auto IsTakingRadDamageFromActiveEffect = F4SE::CreateVariantId(1079111, 2226398, 2226398);
	}

	namespace Main
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(756304, 2698043, 2698043);
		inline constexpr auto WorldRootNode = F4SE::CreateVariantId(569647, 2698065, 2698065);
		inline constexpr auto MenuRootNode = F4SE::CreateVariantId(789152, 2698066, 2698066);
		inline constexpr auto DoneNewOrLoadGame = F4SE::CreateVariantId(1229840, 2698033, 2698033);
		inline constexpr auto GameDataLoaded = F4SE::CreateVariantId(1004331, 2698032, 2698032);
		inline constexpr auto GameSystemsShouldUpdate = F4SE::CreateVariantId(779552, 2698031, 2698031);
		inline constexpr auto SetCameraFOV = F4SE::CreateVariantId(1348813, 2228973, 2228973);
	}

	namespace MemoryManager
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(343176, 2193197, 4471522);
		inline constexpr auto RegisterMemoryManager = F4SE::CreateVariantId(453212, 2228356, 2228356);
		inline constexpr auto GetThreadScrapHeap = F4SE::CreateVariantId(1495205, 2267850, 2267850);
		inline constexpr auto Allocate = F4SE::CreateVariantId(652767, 2267872, 2267872);
		inline constexpr auto Reallocate = F4SE::CreateVariantId(1502917, 2267873, 2267873);
		inline constexpr auto Deallocate = F4SE::CreateVariantId(1582181, 2267874, 2267874);
		inline constexpr auto Size = F4SE::CreateVariantId(1453698, 2267858, 2267858);
	}

	namespace MenuControls
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(520890, 2689089, 4796375);
	}

	namespace MenuCursor
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(695696, 2696546, 4803837);
		inline constexpr auto CenterCursor = F4SE::CreateVariantId(1107298, 2287473, 2287473);
		inline constexpr auto RegisterCursor = F4SE::CreateVariantId(1318193, 2287475, 2287475);
		inline constexpr auto SetCursorConstraintsRaw = F4SE::CreateVariantId(907092, 2287480, 2287480);
		inline constexpr auto UnregisterCursor = F4SE::CreateVariantId(1225249, 2287486, 2287486);
	}

	namespace MenuTopicManager
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(1391114, 2688725, 4795989);
	}

	namespace MessageBoxMenu
	{
		inline constexpr auto ShowMessage = F4SE::CreateVariantId(442479, 2249469, 2249469);
	}

	namespace MessageMenuManager
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(959572, 2689087, 4796373);
		inline constexpr auto CreateImpl = F4SE::CreateVariantId(89563, 2249456, 2249456);
		inline constexpr auto ShowMessages = F4SE::CreateVariantId(843289, 2249461, 2249461);
	}

	namespace MineDisarmed
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(762974, 2233738, 2233738);
		}
	}

	namespace MiscStatManager
	{
		inline constexpr auto MiscStats = F4SE::CreateVariantId(803089, 2689603, 4796892);
	}

	namespace MysteriousStrangerVisits
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(1014921, 2233739, 2233739);
		}
	}

	namespace NavMeshObstacleManager
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(1398127, 2689085, 4796371);
		inline constexpr auto UpdateLock = F4SE::CreateVariantId(1235889, 2693124, 4800416);
	}

	namespace NiAlphaProperty
	{
		inline constexpr auto SetAlphaBlending = F4SE::CreateVariantId(645586, 0, 0); // inlined post next-gen
		inline constexpr auto SetAlphaTesting = F4SE::CreateVariantId(645586, 0, 0);  // inlined post next-gen
		inline constexpr auto SetDestBlendMode = F4SE::CreateVariantId(725249, 0, 0); // inlined post next-gen
		inline constexpr auto SetSrcBlendMode = F4SE::CreateVariantId(976961, 0, 0);  // inlined post next-gen
		inline constexpr auto SetTestMode = F4SE::CreateVariantId(976961, 0, 0);	  // inlined post next-gen
	}

	namespace NiCamera
	{
		inline constexpr auto BoundInFrustum = F4SE::CreateVariantId(781526, 2194525, 2194525);
		inline constexpr auto ViewPointToRay = F4SE::CreateVariantId(460613, 2270338, 2270338);
		inline constexpr auto WorldPtToScreenPt3 = F4SE::CreateVariantId(109441, 2270344, 2270344);
	}

	namespace NiControllerManager
	{
		inline constexpr auto GetNiControllerManager = F4SE::CreateVariantId(1013515, 2271798, 2271798);
		inline constexpr auto GetSequenceByName = F4SE::CreateVariantId(846648, 2192808, 2192808);
	}

	namespace NiControllerSequence
	{
		inline constexpr auto Activate = F4SE::CreateVariantId(829033, 2271861, 2271861);
	}

	namespace NiMatrix3
	{
		inline constexpr auto ToEulerAnglesXYZ = F4SE::CreateVariantId(34114, 2269806, 2269806);
		inline constexpr auto ToEulerAnglesXZY = F4SE::CreateVariantId(1164218, 2269807, 2269807);
		inline constexpr auto ToEulerAnglesYXZ = F4SE::CreateVariantId(272989, 2269808, 2269808);
		inline constexpr auto ToEulerAnglesYZX = F4SE::CreateVariantId(963829, 2269809, 2269809);
		inline constexpr auto ToEulerAnglesZYX = F4SE::CreateVariantId(511385, 2269810, 2269810);
		inline constexpr auto ToEulerAnglesZXY = F4SE::CreateVariantId(606387, 2269824, 2269824);
		inline constexpr auto FromEulerAnglesXYZ = F4SE::CreateVariantId(124665, 2269813, 2269813);
		inline constexpr auto FromEulerAnglesXZY = F4SE::CreateVariantId(1319962, 2269814, 2269814);
		inline constexpr auto FromEulerAnglesYXZ = F4SE::CreateVariantId(55761, 2269815, 2269815);
		inline constexpr auto FromEulerAnglesYZX = F4SE::CreateVariantId(373803, 2269816, 2269816);
		inline constexpr auto FromEulerAnglesZYX = F4SE::CreateVariantId(1569564, 2269817, 2269817);
		inline constexpr auto FromEulerAnglesZXY = F4SE::CreateVariantId(326460, 2269825, 2269825);
	}

	namespace NiRefObject
	{
		inline constexpr auto TotalObjectCount = F4SE::CreateVariantId(1161724, 2703471, 2703471);
	}

	namespace NiTexture
	{
		inline constexpr auto SetAllowDegrade = F4SE::CreateVariantId(948181, 2270148, 2270148);
	}

	namespace ObjectiveState
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(524087, 2206676, 2206676);
	}

	namespace PerkPointIncreaseEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(685859, 2697359, 4804734);
	}

	namespace PerkUtilities
	{
		inline constexpr auto RemoveGrenadeTrajectory = F4SE::CreateVariantId(672186, 2233303, 2233303);
	}

	namespace PickRefUpdateEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1572336, 2195292, 2195292);
	}

	namespace PipboyDataManager
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(1178971, 2689086, 4796372);
	}

	namespace PipboyInventoryData
	{
		inline constexpr auto AddItemCardInfoEntry = F4SE::CreateVariantId(1191786, 2225267, 2225267);
		inline constexpr auto BaseAddItemCardInfoEntry = F4SE::CreateVariantId(1150364, 2225270, 2225270);
		inline constexpr auto PopulateItemCardInfo = F4SE::CreateVariantId(54211, 2225266, 2225266);
		inline constexpr auto RepopulateItemCardsOnSection = F4SE::CreateVariantId(892255, 2225279, 2225279);
	}

	namespace PipboyInventoryMenu
	{
		inline constexpr auto SetQuickkey = F4SE::CreateVariantId(539741, 2224159, 2224159);
	}

	namespace PipboyInventoryUtils
	{
		inline constexpr auto DoSlotsOverlap = F4SE::CreateVariantId(1035436, 2225230, 2225230);
		inline constexpr auto FillDamageTypeInfo = F4SE::CreateVariantId(928518, 2225234, 2225234);
		inline constexpr auto FillResistTypeInfo = F4SE::CreateVariantId(1578434, 2225235, 2225235);
	}

	namespace PipboyLightEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1140080, 2696280, 4803571);
	}

	namespace PipboyManager
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(553234, 2691945, 4799238);
		inline constexpr auto AddMenuToPipboy = F4SE::CreateVariantId(394568, 2225453, 2225453);
		inline constexpr auto ClosedownPipboy = F4SE::CreateVariantId(731410, 2225480, 2225480);
		inline constexpr auto DisablePipboyShader = F4SE::CreateVariantId(662519, 2225484, 2225484);
		inline constexpr auto EnablePipboyShader = F4SE::CreateVariantId(157921, 2225483, 2225483);
		inline constexpr auto InitPipboy = F4SE::CreateVariantId(1477369, 2225479, 2225479);
		inline constexpr auto LowerPipboy = F4SE::CreateVariantId(1444875, 2225454, 2225454);
		inline constexpr auto OnPipboyCloseAnim = F4SE::CreateVariantId(1231000, 2225457, 2225457);
		inline constexpr auto OnPipboyCloseAnimFailed = F4SE::CreateVariantId(1362084, 2225459, 2225459);
		inline constexpr auto OnPipboyClosed = F4SE::CreateVariantId(592088, 2225458, 2225458);
		inline constexpr auto OnPipboyOpenAnim = F4SE::CreateVariantId(1500318, 2225448, 2225448);
		inline constexpr auto OnPipboyOpenAnimFailed = F4SE::CreateVariantId(702357, 2225449, 2225449);
		inline constexpr auto OnPipboyOpened = F4SE::CreateVariantId(1299608, 2225450, 2225450);
		inline constexpr auto PlayItemAnimOnClose = F4SE::CreateVariantId(377837, 2225461, 2225461);
		inline constexpr auto PlayPipboyCloseAnim = F4SE::CreateVariantId(273927, 2225456, 2225456);
		inline constexpr auto PlayPipboyGenericOpenAnim = F4SE::CreateVariantId(809076, 2225447, 2225447);
		inline constexpr auto PlayPipboyLoadHolotapeAnim = F4SE::CreateVariantId(477096, 2225446, 2225446);
		inline constexpr auto PlayPipboyOpenAnim = F4SE::CreateVariantId(663900, 2225444, 2225444);
		inline constexpr auto PlayPipboyOpenTerminalAnim = F4SE::CreateVariantId(743427, 2225445, 2225445);
		inline constexpr auto ProcessLoweringReason = F4SE::CreateVariantId(302903, 2225486, 2225486);
		inline constexpr auto QPipboyActive = F4SE::CreateVariantId(470886, 2225460, 2225460);
		inline constexpr auto RaisePipboy = F4SE::CreateVariantId(726763, 2225455, 2225455);
		inline constexpr auto RefreshPipboyRenderSurface = F4SE::CreateVariantId(81339, 2225478, 2225478);
		inline constexpr auto StartAnimationGraphListening = F4SE::CreateVariantId(714713, 2225490, 2225490);
		inline constexpr auto StopAnimationGraphListening = F4SE::CreateVariantId(621144, 2225491, 2225491);
		inline constexpr auto UpdateCursorConstraint = F4SE::CreateVariantId(900802, 2225488, 2225488);
	}

	namespace PipboyMenu
	{
		inline constexpr auto RefreshMapMarkers = F4SE::CreateVariantId(434114, 2224187, 2224187);
	}

	namespace PipboyObject
	{
		inline constexpr auto AddMember = F4SE::CreateVariantId(1499797, 2225699, 2225699);
	}

	namespace PipboyPlayerInfoData
	{
		inline constexpr auto UpdateArmorData = F4SE::CreateVariantId(362497, 2225790, 2225790);
		inline constexpr auto UpdateCarryWeightData = F4SE::CreateVariantId(338096, 2225788, 2225788);
		inline constexpr auto UpdateGoldData = F4SE::CreateVariantId(1423427, 2225791, 2225791);
		inline constexpr auto UpdateWeaponData = F4SE::CreateVariantId(1108639, 2225789, 2225789);
	}

	namespace PlayerActiveEffectChanged
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(1267315, 2233740, 2233740);
		}
	}

	namespace PlayerAddicted
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(1519765, 2233741, 2233741);
		}
	}

	namespace PlayerCamera
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(1171980, 2688801, 4796065);
		inline constexpr auto SetState = F4SE::CreateVariantId(858847, 2214742, 2214742);
		inline constexpr auto StartPipboyMode = F4SE::CreateVariantId(998069, 2248358, 2248358);
		inline constexpr auto StopPipboyMode = F4SE::CreateVariantId(811954, 2248359, 2248359);
		inline constexpr auto ToggleFreeCameraMode = F4SE::CreateVariantId(224913, 2248368, 2248368);
	}

	namespace PlayerCharacter
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(303410, 2690919, 4798212);
		inline constexpr auto ClearPrison = F4SE::CreateVariantId(920390, 2233196, 2233196);
		inline constexpr auto EnableRadio = F4SE::CreateVariantId(741937, 2233211, 2233211);
		inline constexpr auto GetDifficultyLevel = F4SE::CreateVariantId(922962, 2233056, 2233056);
		inline constexpr auto GetPlayerHandle = F4SE::CreateVariantId(522947, 2698072, 2698072);
		inline constexpr auto HasLOSToTarget = F4SE::CreateVariantId(449775, 2233004, 2233004);
		inline constexpr auto IsGodMode = F4SE::CreateVariantId(1032309, 2232986, 2232986);
		inline constexpr auto IsHolotapePlaying = F4SE::CreateVariantId(530826, 2233206, 2233206);
		inline constexpr auto IsImmortal = F4SE::CreateVariantId(500346, 2232988, 2232988);
		inline constexpr auto PauseHolotape = F4SE::CreateVariantId(1567456, 2233208, 2233208);
		inline constexpr auto PlayHolotape = F4SE::CreateVariantId(1581042, 2233207, 2233207);
		inline constexpr auto QueueFastTravel = F4SE::CreateVariantId(556824, 2232918, 2232918);
		inline constexpr auto RemoveLastUsedPowerArmor = F4SE::CreateVariantId(1488486, 2233024, 2233024);
		inline constexpr auto SelectPerk = F4SE::CreateVariantId(1397326, 2232926, 2232926);
		inline constexpr auto SetAIControlledPackage = F4SE::CreateVariantId(1431972, 2233087, 2233087);
		inline constexpr auto SetEscaping = F4SE::CreateVariantId(25528, 2233142, 2233142);
		inline constexpr auto SetLastDialogueInput = F4SE::CreateVariantId(696117, 2233190, 2233190);
		inline constexpr auto SetPerkCount = F4SE::CreateVariantId(616372, 2233187, 2233187);
		inline constexpr auto SetTintingData = F4SE::CreateVariantId(802946, 2233185, 2233185);
		inline constexpr auto SetVATSCriticalCount = F4SE::CreateVariantId(327338, 2233219, 2233219);
		inline constexpr auto ShowPipboyLight = F4SE::CreateVariantId(1304102, 2233203, 2233203);
		inline constexpr auto StopHolotape = F4SE::CreateVariantId(1021305, 2233209, 2233209);
		inline constexpr auto IsPlayerInDialogue = F4SE::CreateVariantId(60126, 2188686, 2188686);
	}

	namespace PlayerCharacterQuestEvent
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(189797, 2233742, 2233742);
		}
	}

	namespace PlayerControls
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(544871, 2692013, 4799306);
		inline constexpr auto CanPerformAction = F4SE::CreateVariantId(565925, 2234795, 2234795);
		inline constexpr auto DoAction = F4SE::CreateVariantId(818081, 2234796, 2234796);
	}

	namespace PlayerCrosshairModeEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1231665, 2694517, 4801808);
	}

	namespace PlayerDifficultySettingChanged
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(135270, 2233743, 2233743);
		}
	}

	namespace PlayerInDialogueChanged
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(694363, 2233744, 2233744);
		}
	}

	namespace PlayerLifeStateChanged
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(946172, 2233745, 2233745);
		}
	}

	namespace PoisonedWeapon
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(1198663, 2233746, 2233746);
		}
	}

	namespace PowerArmor
	{
		inline constexpr auto ActorInPowerArmor = F4SE::CreateVariantId(1176757, 2219437, 2219437);
		inline constexpr auto GetArmorKeyword = F4SE::CreateVariantId(961172, 2194743, 2194743);
		inline constexpr auto GetBatteryKeyword = F4SE::CreateVariantId(1493537, 2194740, 2194740);
		inline constexpr auto GetDefaultBatteryObject = F4SE::CreateVariantId(1279247, 2194761, 2194761);
		inline constexpr auto IsPowerArmorBattery = F4SE::CreateVariantId(1012910, 2219422, 2219422);
		inline constexpr auto SyncFurnitureVisualsToInventory = F4SE::CreateVariantId(1078979, 2219453, 2219453);
	}

	namespace PowerArmorGeometry
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(1365745, 2694441, 4801732);
		inline constexpr auto HidePipboyPAGeometry = F4SE::CreateVariantId(976332, 2248877, 2248877);
		inline constexpr auto ShowPipboyPAGeometry = F4SE::CreateVariantId(19066, 2248876, 2248876);
	}

	namespace PowerArmorLightData
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(120809, 2701547, 2701547);
	}

	namespace PowerUtils
	{
		inline constexpr auto ItemIsPowerConnection = F4SE::CreateVariantId(17704, 2195078, 2195078);
		inline constexpr auto ItemIsPowerReceiver = F4SE::CreateVariantId(210626, 2195060, 2195060);
	}

	namespace ProcessLists
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(1569706, 2688869, 4796160);
		inline constexpr auto AreHostileActorsNear = F4SE::CreateVariantId(1053584, 2234105, 2234105);
		inline constexpr auto IsActorTargetingREFinPackage = F4SE::CreateVariantId(559542, 2234033, 2234033);
		inline constexpr auto RequestHighestDetectionLevelAgainstActor = F4SE::CreateVariantId(1036693, 2234111, 2234111);
	}

	namespace RadioManager
	{
		inline constexpr auto QPlayerRadioEnabled = F4SE::CreateVariantId(811921, 2227674, 2227674);
		inline constexpr auto QCurrentPlayerFreq = F4SE::CreateVariantId(227903, 2227670, 2227670);
		inline constexpr auto EnablePlayerRadio = F4SE::CreateVariantId(653012, 2227673, 2227673);
	}

	namespace REFR_LOCK
	{
		inline constexpr auto GetLockLevel = F4SE::CreateVariantId(782953, 2191018, 2191018);
	}

	namespace RelationshipChange
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(1450835, 2233747, 2233747);
		}
	}

	namespace RicochetHit
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(120692, 2233748, 2233748);
		}
	}

	namespace ScreenSplatter
	{
		inline constexpr auto Clear = F4SE::CreateVariantId(1478405, 2194783, 2194783);
		inline constexpr auto Update = F4SE::CreateVariantId(907893, 2194781, 2194781);
	}

	namespace SCRIPT_FUNCTION
	{
		inline constexpr auto ConsoleFunctions = F4SE::CreateVariantId(901511, 901511, 901511); // same for all versions
		inline constexpr auto ScriptFunctions = F4SE::CreateVariantId(75173, 75173, 75173);		// same for all versions
	}

	namespace SWFToCodeFunctionHandler
	{
		inline constexpr auto MapCodeMethodToASFunction = F4SE::CreateVariantId(1263128, 2287419, 2287419);
		inline constexpr auto RegisterCodeObject = F4SE::CreateVariantId(67637, 2287415, 2287415);
	}

	namespace SandmanKill
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(372944, 2233749, 2233749);
		}
	}

	namespace SavefileMetadata
	{
		inline constexpr auto FillDataFromFileName = F4SE::CreateVariantId(116131, 2228156, 2228156);
	}

	namespace ScrapHeap
	{
		inline constexpr auto Allocate = F4SE::CreateVariantId(1085394, 2267983, 2267983);
		inline constexpr auto Deallocate = F4SE::CreateVariantId(923307, 2267984, 2267984);
	}

	namespace Script
	{
		inline constexpr auto CompileAndRunImpl = F4SE::CreateVariantId(526625, 2204287, 2204287);
		inline constexpr auto ParseParameters = F4SE::CreateVariantId(1607, 2204298, 2204298);
		inline constexpr auto ProcessScripts = F4SE::CreateVariantId(175133, 2661858, 2661858);
	}

	namespace SendHUDMessage
	{
		inline constexpr auto PopHUDMode = F4SE::CreateVariantId(1495042, 2222444, 2222444);
		inline constexpr auto PushHUDMode = F4SE::CreateVariantId(1321764, 2222443, 2222443);
		inline constexpr auto SetPowerArmorMode = F4SE::CreateVariantId(361745, 2222459, 2222459);
		inline constexpr auto ShowHUDMessage = F4SE::CreateVariantId(1163005, 2222440, 2222440);
	}

	namespace SitWaitMenu
	{
		inline constexpr auto OnEnterFurniture = F4SE::CreateVariantId(562238, 2249503, 2249503);
		inline constexpr auto OnExitFurniture = F4SE::CreateVariantId(454795, 2249504, 2249504);
	}

	namespace Sky
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(484694, 2192448, 2192448);
		inline constexpr auto ForceWeather = F4SE::CreateVariantId(698558, 2208861, 2208861);
		inline constexpr auto ResetWeather = F4SE::CreateVariantId(6511, 2208860, 2208860);
	}

	namespace SpeechChallengeSucceeded
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(625391, 2233750, 2233750);
		}
	}

	namespace SplineUtils
	{
		inline constexpr auto ConnectSpline = F4SE::CreateVariantId(59311, 2195073, 2195073);
		inline constexpr auto DisconnectSpline = F4SE::CreateVariantId(750682, 2195074, 2195074);
	}

	namespace SubtitleManager
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(740511, 2689088, 4796374);
		inline constexpr auto RWLock = F4SE::CreateVariantId(589656, 2701704, 2701704);
	}

	namespace TES
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(1194835, 2698044, 2698044);
	}

	namespace TESActivateEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(166230, 2201819, 2201819);
	}

	namespace TESActiveEffectApplyRemoveEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1388854, 2201820, 2201820);
	}

	namespace TESActorBaseData
	{
		inline constexpr auto GetLevel = F4SE::CreateVariantId(151866, 2192891, 2192891);
	}

	namespace TESActorLocationChangeEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1029687, 2201821, 2201821);
	}

	namespace TESAmmo
	{
		inline constexpr auto GetReloadsWithAmmoRef = F4SE::CreateVariantId(1035622, 2197864, 2197864);
	}

	namespace TESAudio
	{
		namespace ScriptedMusicState
		{
			inline constexpr auto Singleton = F4SE::CreateVariantId(1216761, 2691985, 4799278);
			inline constexpr auto Remove = F4SE::CreateVariantId(544747, 2226976, 2226976);
		}
	}

	namespace TESBookReadEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(670837, 2201822, 2201822);
	}

	namespace TESBoundObject
	{
		inline constexpr auto ApplyMods = F4SE::CreateVariantId(113585, 2198325, 2198325);
	}

	namespace TESCellAttachDetachEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(311270, 2201823, 2201823);
	}

	namespace TESCellFullyLoadedEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1534478, 2201824, 2201824);
	}

	namespace TESCellReadyToApplyDecalsEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1175067, 2201825, 2201825);
	}

	namespace TESCombatEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(815924, 2201826, 2201826);
	}

	namespace TESCommandModeCompleteCommandEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(456275, 2201827, 2201827);
	}

	namespace TESCommandModeEnterEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(97273, 2201828, 2201828);
	}

	namespace TESCommandModeExitEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1320161, 2201829, 2201829);
	}

	namespace TESCommandModeGiveCommandEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(960995, 2201830, 2201830);
	}

	namespace TESCondition
	{
		inline constexpr auto ClearAllConditionItems = F4SE::CreateVariantId(757713, 2211988, 2211988);
		inline constexpr auto IsTrue = F4SE::CreateVariantId(1275731, 2211989, 2211989);
		inline constexpr auto IsTrueForAllButFunction = F4SE::CreateVariantId(1182457, 0, 0); // inlined post next-gen
	}

	namespace TESConditionItem
	{
		inline constexpr auto GetComparisonValue = F4SE::CreateVariantId(1373349, 2212007, 2212007);
		inline constexpr auto IsTrue01 = F4SE::CreateVariantId(1453240, 2212008, 2212008);
		inline constexpr auto IsTrue02 = F4SE::CreateVariantId(43452, 2212009, 2212009);
	}

	namespace TESConsciousnessEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(601920, 2201831, 2201831);
	}

	namespace TESContainerChangedEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(242538, 2201832, 2201832);
	}

	namespace TESDataHandler
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(711558, 2688883, 4796135);
		inline constexpr auto AddFormToDataHandler = F4SE::CreateVariantId(350112, 2192271, 2192271);
		inline constexpr auto CreateReferenceAtLocation = F4SE::CreateVariantId(500304, 2192301, 2192301);
		inline constexpr auto GetExtCellDataFromFileByEditorID = F4SE::CreateVariantId(1411233, 2192293, 2192293);
		inline constexpr auto IsFormIDInUse = F4SE::CreateVariantId(1448838, 2192351, 2192351);
		inline constexpr auto CheckModsLoaded = F4SE::CreateVariantId(1432894, 2192323, 2192323);
	}

	namespace TESDeathEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1465690, 2201833, 2201833);
	}

	namespace TESDeferredKillEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1106254, 2201834, 2201834);
	}

	namespace TESDescription
	{
		inline constexpr auto GetDescription = F4SE::CreateVariantId(523613, 2193019, 2193019);
	}

	namespace TESDestructionStageChangedEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(747291, 2201835, 2201835);
	}

	namespace TESEnterBleedoutEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(387731, 2201836, 2201836);
	}

	namespace TESEnterSneakingEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(28138, 2201837, 2201837);
	}

	namespace TESEquipEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1251703, 2201838, 2201838);
	}

	namespace TESEscortWaitStartEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(892350, 2201839, 2201839);
	}

	namespace TESEscortWaitStopEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(533153, 2201840, 2201840);
	}

	namespace TESExitFurnitureEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(174010, 2201841, 2201841);
	}

	namespace TESFile
	{
		inline constexpr auto dtor = F4SE::CreateVariantId(226797, 2192487, 2192487);
		inline constexpr auto ChangeBufferSize = F4SE::CreateVariantId(352143, 2192567, 2192567);
		inline constexpr auto CloseTES = F4SE::CreateVariantId(766555, 2192491, 2192491);
		inline constexpr auto FindForm = F4SE::CreateVariantId(1324254, 2192521, 2192521);
		inline constexpr auto GetChunkData = F4SE::CreateVariantId(188910, 2192538, 2192538);
		inline constexpr auto GetTESChunk = F4SE::CreateVariantId(641361, 2192536, 2192536);
		inline constexpr auto GetThreadSafeFileForThread = F4SE::CreateVariantId(1004882, 2192565, 2192565);
		inline constexpr auto LoadForm = F4SE::CreateVariantId(1183915, 2192544, 2192544);
		inline constexpr auto NextChunk = F4SE::CreateVariantId(1252764, 2192537, 2192537);
		inline constexpr auto NextForm = F4SE::CreateVariantId(644374, 2192527, 2192527);
		inline constexpr auto NextGroup = F4SE::CreateVariantId(339855, 2192522, 2192522);
		inline constexpr auto OpenTES = F4SE::CreateVariantId(728465, 2192490, 2192490);
		inline constexpr auto TESRewind = F4SE::CreateVariantId(1096742, 2192525, 2192525);
		inline constexpr auto TESRewindChunk = F4SE::CreateVariantId(737725, 2192526, 2192526);
	}

	namespace TESForm
	{
		inline constexpr auto AddCompileIndex = F4SE::CreateVariantId(1315637, 2193152, 2193152);
		inline constexpr auto TotalFormCount = F4SE::CreateVariantId(1104561, 2689176, 4796463);
		inline constexpr auto FormEditorIDMap = F4SE::CreateVariantId(642758, 2689179, 4796466);
		inline constexpr auto FormEditorIDMapLock = F4SE::CreateVariantId(910917, 2689190, 4796477);
		inline constexpr auto FormNumericIDMap = F4SE::CreateVariantId(422985, 2689178, 4796465);
		inline constexpr auto FormNumericIDMapLock = F4SE::CreateVariantId(691815, 2689189, 4796476);
		inline constexpr auto SetTemporary = F4SE::CreateVariantId(482454, 2193125, 2193125);
	}

	namespace TESFormDeleteEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1396562, 2201842, 2201842);
	}

	namespace TESFormIDRemapEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1037385, 2201843, 2201843);
	}

	namespace TESFullName
	{
		inline constexpr auto SparseFullNameMap = F4SE::CreateVariantId(226372, 2533149, 2533149);
	}

	namespace TESFurniture
	{
		inline constexpr auto GetContainer = F4SE::CreateVariantId(1049933, 2198043, 2198043);
	}

	namespace TESFurnitureEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(678665, 2201844, 2201844);
	}

	namespace TESGrabReleaseEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(319018, 2201845, 2201845);
	}

	namespace TESHarvestEvent
	{
		namespace ItemHarvested
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(11738, 2193351, 2193351);
		}
	}

	namespace TerminalMenuItemRunEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(548625, 2201884, 2201884);
	}

	namespace TESHitEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1411899, 2201886, 2201886);
	}

	namespace TESInitScriptEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1542080, 2201846, 2201846);
	}

	namespace TESLevItem
	{
		inline constexpr auto OverrideNameMap = F4SE::CreateVariantId(1524252, 2661643, 2661643);
	}

	namespace TESLeveledList
	{
		inline constexpr auto CalculateCurrentFormList = F4SE::CreateVariantId(603811, 2193259, 2193259);
		inline constexpr auto CalculateCurrentFormListForRef = F4SE::CreateVariantId(507405, 2193260, 2193260);
		inline constexpr auto SpecialChanceGlobalMap = F4SE::CreateVariantId(1043289, 2661411, 2661411);
	}

	namespace TESLimbCrippleEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1182805, 2201847, 2201847);
	}

	namespace TESLoadGameEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(823570, 2201848, 2201848);
	}

	namespace TESLocationClearedEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1372013, 2201849, 2201849);
	}

	namespace TESLockChangedEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(105061, 2201850, 2201850);
	}

	namespace TESMagicEffectApplyEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1327824, 2201851, 2201851);
	}

	namespace TESMagicWardHitEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(968652, 2201852, 2201852);
	}

	namespace TESNPC
	{
		inline constexpr auto AlternateHeadPartListMap = F4SE::CreateVariantId(1306546, 2662364, 2662364);
		inline constexpr auto GetFacialBoneMorphIntensity = F4SE::CreateVariantId(272217, 2207416, 2207416);
		inline constexpr auto GetShortName = F4SE::CreateVariantId(1221705, 2207405, 2207405);
		inline constexpr auto SetTintingData = F4SE::CreateVariantId(452734, 2207493, 2207493);
	}

	namespace TESObjectARMO
	{
		inline constexpr auto Protects = F4SE::CreateVariantId(1028523, 2198535, 2198535);
	}

	namespace TESObjectCELL
	{
		inline constexpr auto AttachReference3D = F4SE::CreateVariantId(125567, 2200620, 2200620);
		inline constexpr auto FindInFileFast = F4SE::CreateVariantId(577761, 2200375, 2200375);
		inline constexpr auto GetInteriorOffset = F4SE::CreateVariantId(655838, 2200350, 2200350);
		inline constexpr auto Load = F4SE::CreateVariantId(165674, 2200163, 2200163);
		inline constexpr auto RemoveReference = F4SE::CreateVariantId(650855, 2200299, 2200299);
		inline constexpr auto SetCullCellMarkers = F4SE::CreateVariantId(192259, 2192259, 2192259);
		inline constexpr auto SetInteriorOffset = F4SE::CreateVariantId(1439668, 2200351, 2200351);
		inline constexpr auto UpdateAllDecals = F4SE::CreateVariantId(283071, 2200643, 2200643);
		inline constexpr auto UpdateAllRefsLoaded = F4SE::CreateVariantId(374552, 2200415, 2200415);
	}

	namespace TESObjectLoadedEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(609604, 2201853, 2201853);
	}

	namespace TESObjectREFR
	{
		inline constexpr auto ActivateRef = F4SE::CreateVariantId(753531, 2201147, 2201147);
		inline constexpr auto AddInventoryItem = F4SE::CreateVariantId(78185, 2200949, 2200949);
		inline constexpr auto AddLockChange = F4SE::CreateVariantId(1578706, 2200731, 2200731);
		inline constexpr auto ApplyArtObject = F4SE::CreateVariantId(357908, 2205200, 2205200);
		inline constexpr auto ApplyEffectShader = F4SE::CreateVariantId(652173, 2205201, 2205201);
		inline constexpr auto CanBeMoved = F4SE::CreateVariantId(683719, 2200898, 2200898);
		inline constexpr auto Enable = F4SE::CreateVariantId(1396707, 2201150, 2201150);
		inline constexpr auto FindReferenceFor3D = F4SE::CreateVariantId(766937, 2201082, 2201082);
		inline constexpr auto GetCurrentLocation = F4SE::CreateVariantId(1135470, 2201163, 2201163);
		inline constexpr auto GetEditorDead = F4SE::CreateVariantId(941388, 2200781, 2200781);
		inline constexpr auto GetGoldAmount = F4SE::CreateVariantId(564356, 2200923, 2200923);
		inline constexpr auto GetHasOwner = F4SE::CreateVariantId(1016277, 2202622, 2202622);
		inline constexpr auto GetInventoryObjectCount = F4SE::CreateVariantId(333415, 2200939, 2200939);
		inline constexpr auto GetItemCount = F4SE::CreateVariantId(635042, 2200996, 2200996);
		inline constexpr auto GetLinkedRef = F4SE::CreateVariantId(897287, 2202683, 2202683);
		inline constexpr auto GetObjectCenter = F4SE::CreateVariantId(777738, 2201092, 2201092);
		inline constexpr auto GetOwner = F4SE::CreateVariantId(1323437, 2202616, 2202616);
		inline constexpr auto GetWeightInContainer = F4SE::CreateVariantId(1377567, 2201001, 2201001);
		inline constexpr auto HasContainer = F4SE::CreateVariantId(1213017, 2201022, 2201022);
		inline constexpr auto IsAnOwner = F4SE::CreateVariantId(933798, 2202635, 2202635);
		inline constexpr auto IsCrimeToActivate = F4SE::CreateVariantId(836011, 2201180, 2201180);
		inline constexpr auto IsDecalRef = F4SE::CreateVariantId(686485, 2200794, 2200794);
		inline constexpr auto IsLeveledCreature = F4SE::CreateVariantId(1341859, 2202655, 2202655);
		inline constexpr auto IsMarker = F4SE::CreateVariantId(364958, 2201157, 2201157);
		inline constexpr auto MarkAsDeleted = F4SE::CreateVariantId(192661, 2201156, 2201156);
		inline constexpr auto MoveRefToNewSpace = F4SE::CreateVariantId(629658, 2201149, 2201149);
		inline constexpr auto RebuildBendableSpline = F4SE::CreateVariantId(340319, 2201119, 2201119);
		inline constexpr auto SetAngleOnReference = F4SE::CreateVariantId(1049748, 2201134, 2201134);
		inline constexpr auto SetLinkedRef = F4SE::CreateVariantId(192840, 2202684, 2202684);
		inline constexpr auto SetLocationOnReference = F4SE::CreateVariantId(1101832, 2201138, 2201138);
		inline constexpr auto SetScale = F4SE::CreateVariantId(817930, 2200893, 2200893);
		inline constexpr auto SetWantsDelete = F4SE::CreateVariantId(761346, 2201199, 2201199);
		inline constexpr auto UpdateDynamicNavmesh = F4SE::CreateVariantId(1518094, 2201206, 2201206);
		inline constexpr auto UpdateReference3D = F4SE::CreateVariantId(1568075, 2201071, 2201071);
	}

	namespace TESObjectREFRTranslationEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(250283, 2201854, 2201854);
	}

	namespace TESObjectWEAP
	{
		inline constexpr auto GetMeleeAttackSpeed = F4SE::CreateVariantId(817670, 2198957, 2198957);
		inline constexpr auto GetMeleeAttackSpeedLabel = F4SE::CreateVariantId(178784, 2198959, 2198959);
		inline constexpr auto GetShotsPerSecond = F4SE::CreateVariantId(752116, 2198956, 2198956);
	}

	namespace TESOnPCDialogueTargetEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1473468, 2201855, 2201855);
	}

	namespace TESOpenCloseEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1113930, 2201856, 2201856);
	}

	namespace TESPackageEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(755003, 2201857, 2201857);
	}

	namespace TESPerkEntryRunEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(395379, 2201858, 2201858);
	}

	namespace TESPickNewIdleEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(35951, 2201859, 2201859);
	}

	namespace TESPickpocketFailedEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1259305, 2201860, 2201860);
	}

	namespace TESQuest
	{
		inline constexpr auto GetAliasedRef = F4SE::CreateVariantId(847223, 2207810, 2207810);
		inline constexpr auto SetStage = F4SE::CreateVariantId(952799, 2207743, 2207743);
	}

	namespace TESQuestInitEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(899964, 2201861, 2201861);
	}

	namespace TESQuestStageEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(540905, 2201862, 2201862);
	}

	namespace TESQuestStageItemDoneEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(181651, 2201863, 2201863);
	}

	namespace TESQuestStartStopEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1404315, 2201864, 2201864);
	}

	namespace TESResetEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1045137, 2201865, 2201865);
	}

	namespace TESResolveNPCTemplatesEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(686294, 2201866, 2201866);
	}

	namespace TESResponse
	{
		inline constexpr auto GetResponseText = F4SE::CreateVariantId(992447, 2208288, 2208288);
		inline constexpr auto GetSpeakerIdle = F4SE::CreateVariantId(606043, 2208293, 2208293);
	}

	namespace TESSceneActionEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(326650, 2201867, 2201867);
	}

	namespace TESSceneEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1549776, 2201868, 2201868);
	}

	namespace TESScenePhaseEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1190467, 2201869, 2201869);
	}

	namespace TESSellEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(831202, 2201870, 2201870);
	}

	namespace TESSleepStartEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(471701, 2201871, 2201871);
	}

	namespace TESSleepStopEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(112659, 2201872, 2201872);
	}

	namespace TESSpellCastEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1335446, 2201873, 2201873);
	}

	namespace TESSwitchRaceCompleteEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(976262, 2201874, 2201874);
	}

	namespace TESTopic
	{
		inline constexpr auto InitDialogueItem = F4SE::CreateVariantId(49777, 2208360, 2208360);
	}

	namespace TESTopicInfo
	{
		inline constexpr auto GetChallengeLevel = F4SE::CreateVariantId(613016, 2208441, 2208441);
		inline constexpr auto GetParentInfoGroup = F4SE::CreateVariantId(163538, 2208435, 2208435);
		inline constexpr auto GetScene = F4SE::CreateVariantId(820897, 2208453, 2208453);
		inline constexpr auto GetSpeaker = F4SE::CreateVariantId(1048628, 2208449, 2208449);
		inline constexpr auto GetSuccessLevel = F4SE::CreateVariantId(1023955, 2208444, 2208444);
		inline constexpr auto StartScene = F4SE::CreateVariantId(269139, 2208469, 2208469);
		inline constexpr auto StartSceneOnEnd = F4SE::CreateVariantId(376042, 2208466, 2208466);
	}

	namespace TESTopicInfoEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(617263, 2201875, 2201875);
	}

	namespace TESTrackedStatsEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(257918, 2201876, 2201876);
	}

	namespace TESTrapHitEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1481256, 2201877, 2201877);
	}

	namespace TESTriggerEnterEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1121550, 2201878, 2201878);
	}

	namespace TESTriggerEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(762621, 2201879, 2201879);
	}

	namespace TESTriggerLeaveEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(403011, 2201880, 2201880);
	}

	namespace TESUniqueIDChangeEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(43761, 2201881, 2201881);
	}

	namespace TESWaitStartEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1266964, 2201882, 2201882);
	}

	namespace TESWaitStopEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(907679, 2201883, 2201883);
	}

	namespace TESWaterForm
	{
		inline constexpr auto DefaultWater = F4SE::CreateVariantId(289864, 2691845, 4799138);
	}

	namespace TESWorldSpace
	{
		inline constexpr auto Load = F4SE::CreateVariantId(701354, 2202844, 2202844);
		inline constexpr auto LoadPartial = F4SE::CreateVariantId(1015763, 2202845, 2202845);
		inline constexpr auto FindInFileFast = F4SE::CreateVariantId(1116717, 2202851, 2202851);
		inline constexpr auto PrefetchCellData = F4SE::CreateVariantId(719753, 2202848, 2202848);
		inline constexpr auto FindCellInFile = F4SE::CreateVariantId(1012650, 2202847, 2202847);
		inline constexpr auto GetOffsetData = F4SE::CreateVariantId(1384464, 2202941, 2202941);
		inline constexpr auto CreateOffsetData = F4SE::CreateVariantId(320570, 2202942, 2202942);
		inline constexpr auto FreeOffsetData = F4SE::CreateVariantId(479563, 2202943, 2202943);
	}

	namespace TaskQueueInterface
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(7491, 2698331, 2698331);
		inline constexpr auto QueueClosePipboy = F4SE::CreateVariantId(69886, 2229289, 2229289);
		inline constexpr auto QueueRebuildBendableSpline = F4SE::CreateVariantId(198419, 2229302, 2229302);
		inline constexpr auto QueueShow1stPerson = F4SE::CreateVariantId(994377, 2229268, 2229268);
		inline constexpr auto QueueShowPipboy = F4SE::CreateVariantId(1133684, 2229288, 2229288);
		inline constexpr auto QueueUpdate3D = F4SE::CreateVariantId(581890, 2229234, 2229234);
		inline constexpr auto QueueWeaponFire = F4SE::CreateVariantId(15449, 2229186, 2229186);
		inline constexpr auto TaskUnpackFunc = F4SE::CreateVariantId(1546751, 2229323, 2229323);
	}

	namespace TerminalHacked
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(425579, 2233751, 2233751);
		}
	}

	namespace TravelMarkerStateChange
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(1129589, 2233752, 2233752);
		}
	}

	namespace UI
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(548587, 2689028, 4796314);
		inline constexpr auto MenuMapRWLock = F4SE::CreateVariantId(578487, 2707105, 2707105);
		inline constexpr auto CustomRendererHasQuads = F4SE::CreateVariantId(1401451, 2284757, 2284757);
		inline constexpr auto RefreshCursor = F4SE::CreateVariantId(1436639, 2284772, 2284772);
		inline constexpr auto UpdateControllerType = F4SE::CreateVariantId(175796, 2284768, 2284768);
	}

	namespace UIAdvanceMenusFunctionCompleteEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1067039, 2694428, 4801719);
	}

	namespace UIMessageQueue
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(82123, 2689091, 4796377);
	}

	namespace UIUtils
	{
		inline constexpr auto GetComparisonItems = F4SE::CreateVariantId(593818, 0, 0); // inlined post next-gen
		inline constexpr auto HasRequiredInventoryForCraftingMenu = F4SE::CreateVariantId(639634, 2249717, 2249717);
		inline constexpr auto PlayMenuSound = F4SE::CreateVariantId(1227993, 2249707, 2249707);
		inline constexpr auto PlayPipboySound = F4SE::CreateVariantId(1320952, 2249706, 2249706);
		inline constexpr auto ShowCraftingMenu = F4SE::CreateVariantId(877836, 2249718, 2249718);
		inline constexpr auto UpdateGamepadDependentButtonCodes = F4SE::CreateVariantId(190238, 2249714, 4483350);
	}

	namespace VATS
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(570121, 2690444, 4797733);
	}

	namespace ViewCasterUpdateEvent
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(1536643, 2694310, 4801601);
	}

	namespace WeaponAttack
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(1381764, 2233753, 2233753);
		}
	}

	namespace WorkbenchMenuBase
	{
		inline constexpr auto UpdateOptimizedAutoBuildInv = F4SE::CreateVariantId(769581, 2224955, 2224955);
	}

	namespace Workshop
	{
		inline constexpr auto FindNearestValidWorkshop = F4SE::CreateVariantId(905705, 2194970, 2194970);
		inline constexpr auto FreeBuild = F4SE::CreateVariantId(1583365, 2194924, 2194924);
		inline constexpr auto GetSelectedWorkshopMenuNode = F4SE::CreateVariantId(763948, 2195024, 2195024);
		inline constexpr auto InitializePlacementReference = F4SE::CreateVariantId(1577199, 0, 0); // inlined post next-gen
		inline constexpr auto IsLocationWithinBuildableArea = F4SE::CreateVariantId(990965, 2194956, 2194956);
		inline constexpr auto IsWorkshopItem = F4SE::CreateVariantId(1386903, 2194912, 2194912);
		inline constexpr auto PlaceCurrentReference = F4SE::CreateVariantId(1058211, 2195155, 2195155);
		inline constexpr auto RequestExitWorkshop = F4SE::CreateVariantId(209891, 2195135, 2195135);
		inline constexpr auto ScrapReference = F4SE::CreateVariantId(636327, 2195125, 2195125);
		inline constexpr auto SetSelectedEditItem = F4SE::CreateVariantId(2562, 2195119, 2195119);
		inline constexpr auto StartWorkshop = F4SE::CreateVariantId(171771, 2195134, 2195134);
		inline constexpr auto ToggleEditMode = F4SE::CreateVariantId(1243386, 2195130, 2195130);
		inline constexpr auto UpdateActiveEdit = F4SE::CreateVariantId(69261, 2195210, 2195210);
		inline constexpr auto WorkshopCanShowRecipe = F4SE::CreateVariantId(239190, 2194978, 2194978);
		inline constexpr auto CurrentPlacementItemData = F4SE::CreateVariantId(1279207, 2689973, 4797261);
		inline constexpr auto CurrentRow = F4SE::CreateVariantId(833923, 2689868, 4797160);
		inline constexpr auto PlacementItem = F4SE::CreateVariantId(526727, 2689906, 4797235);

		namespace BuildableAreaEvent
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(922238, 2195285, 2195285);
		}

		namespace ItemDestroyedEvent
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(563220, 2195286, 2195286);
		}

		namespace ItemGrabbedEvent
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(203989, 2195287, 2195287);
		}

		namespace ItemMovedEvent
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(1426604, 2195288, 2195288);
		}

		namespace ItemPlacedEvent
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(1067439, 2195289, 2195289);
		}

		namespace ItemRepairedEvent
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(708832, 2195290, 2195290);
		}

		namespace ItemScrappedEvent
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(348916, 2195291, 2195291);
		}

		namespace PlacementItemData
		{
			inline constexpr auto Set = F4SE::CreateVariantId(1460935, 2195643, 2195643);
		}

		namespace PlacementStatusEvent
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(1213076, 2195293, 2195293);
		}

		namespace PowerOffEvent
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(853526, 2195294, 2195294);
		}

		namespace PowerOnEvent
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(494172, 2195295, 2195295);
		}

		namespace WorkshopMenuNode
		{
			inline constexpr auto FindAndSetSelectedNode = F4SE::CreateVariantId(1309368, 2195022, 2195022);
		}

		namespace WorkshopModeEvent
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(135059, 2195296, 2195296);
		}
	}

	namespace WorkshopMenu
	{
		inline constexpr auto CheckAndSetItemForPlacement = F4SE::CreateVariantId(1541862, 2224991, 2224991);
		inline constexpr auto UpdateButtonText = F4SE::CreateVariantId(1089189, 2224992, 2224992);
	}

	namespace WorkshopNPCTransferEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(189426, 2201885, 2201885);
	}

	namespace bhkCharacterController
	{
		inline constexpr auto Jump = F4SE::CreateVariantId(1067306, 2278191, 2278191);
	}

	namespace bhkNPCollisionObject
	{
		inline constexpr auto CopyMembers = F4SE::CreateVariantId(1558409, 2277907, 2277907);
		inline constexpr auto GetBody = F4SE::CreateVariantId(1127049, 2277926, 2277926);
		inline constexpr auto GetBodyId = F4SE::CreateVariantId(1286222, 2277928, 2277928);
		inline constexpr auto GetShape = F4SE::CreateVariantId(315427, 2277929, 2277929);
		inline constexpr auto GetTransform = F4SE::CreateVariantId(1508189, 2277944, 2277944);
		inline constexpr auto Getbhk = F4SE::CreateVariantId(730034, 2277919, 2277919);
		inline constexpr auto SetMotionType = F4SE::CreateVariantId(200912, 2277913, 2277913);
		inline constexpr auto SetTransform = F4SE::CreateVariantId(178085, 2277945, 2277945);
	}

	namespace bhkPhysicsSystem
	{
		inline constexpr auto ctor = F4SE::CreateVariantId(1338184, 2278008, 2278008);
		inline constexpr auto AddToWorld = F4SE::CreateVariantId(512878, 2278019, 2278019);
		inline constexpr auto CopyMembers = F4SE::CreateVariantId(301764, 2278007, 2278007);
	}

	namespace bhkPickData
	{
		inline constexpr auto ctor = F4SE::CreateVariantId(526783, 2230668, 2230668);
		inline constexpr auto GetAllCollectorRayHitAt = F4SE::CreateVariantId(583997, 2277766, 2277766);
		inline constexpr auto GetAllCollectorRayHitSize = F4SE::CreateVariantId(1288513, 2277765, 2277765);
		inline constexpr auto GetBody = F4SE::CreateVariantId(1223055, 2277762, 2277762);
		inline constexpr auto GetHitFraction = F4SE::CreateVariantId(476687, 2277772, 2277772);
		inline constexpr auto GetNiAVObject = F4SE::CreateVariantId(863406, 2277764, 2277764);
		inline constexpr auto HasHit = F4SE::CreateVariantId(1181584, 2277770, 2277770);
		inline constexpr auto Reset = F4SE::CreateVariantId(438299, 2277761, 2277761);
		inline constexpr auto SetStartEnd = F4SE::CreateVariantId(747470, 2236622, 2236622);
		inline constexpr auto SortAllCollectorHits = F4SE::CreateVariantId(1274842, 2277767, 2277767);
	}

	namespace bhkUtilFunctions
	{
		inline constexpr auto FindFirstCollisionObject = F4SE::CreateVariantId(507243, 2278093, 2278093);
	}

	namespace bhkWorld
	{
		inline constexpr auto AddPhysicsSystem = F4SE::CreateVariantId(82382, 2277752, 2277752);
		inline constexpr auto RemoveObjects = F4SE::CreateVariantId(1514984, 2277721, 2277721);
		inline constexpr auto RemovePhysicsSystem = F4SE::CreateVariantId(1039226, 2277753, 2277753);
	}

	namespace hkContainerDebugAllocator
	{
		inline constexpr auto Allocator = F4SE::CreateVariantId(629588, 2665427, 2665427);
	}

	namespace hkContainerHeapAllocator
	{
		inline constexpr auto Allocator = F4SE::CreateVariantId(409811, 2665426, 2665426);
	}

	namespace hkContainerTempAllocator
	{
		inline constexpr auto Allocator = F4SE::CreateVariantId(190918, 2665425, 2665425);
	}

	namespace hkMemoryRouter
	{
		inline constexpr auto ThreadLocalInstance = F4SE::CreateVariantId(878080, 2787927, 2787927);
	}

	namespace hkReferencedObject
	{
		inline constexpr auto AddReference = F4SE::CreateVariantId(866015, 2259213, 2259213);
		inline constexpr auto RemoveReference = F4SE::CreateVariantId(1379897, 2195747, 2195747);
	}

	namespace msvc
	{
		namespace type_info
		{
			inline constexpr auto name = F4SE::CreateVariantId(1419793, 2729709, 4823662);
			inline constexpr auto compare = F4SE::CreateVariantId(0, 2729710, 4823660); // post next-gen only
			inline constexpr auto equal = F4SE::CreateVariantId(808703, 0, 0);			// pre next-gen only
			inline constexpr auto root_node = F4SE::CreateVariantId(161235, 2713441, 2713441);
		}
	}

	namespace nsStatsMenuUtils
	{
		inline constexpr auto GetEffectDisplayInfo = F4SE::CreateVariantId(294691, 2224586, 2224586);
	}
}

namespace Scaleform::ID
{
	namespace GFx
	{
		namespace ASStringManager
		{
			inline constexpr auto CreateStringNode = F4SE::CreateVariantId(419974, 2290014, 2290014);
		}

		namespace Loader
		{
			inline constexpr auto CreateMovie = F4SE::CreateVariantId(912291, 2284723, 2284723);
		}

		namespace Movie
		{
			inline constexpr auto Release = F4SE::CreateVariantId(404814, 2287230, 2287230);
		}

		namespace Value
		{
			inline constexpr auto ObjectAddRef = F4SE::CreateVariantId(244786, 2286228, 2286228);
			inline constexpr auto ObjectRelease = F4SE::CreateVariantId(856221, 2286229, 2286229);
			inline constexpr auto IsInstanceOf = F4SE::CreateVariantId(616029, 2286137, 2286137);
			inline constexpr auto GetParent = F4SE::CreateVariantId(227189, 2285968, 2285968);
			inline constexpr auto HasMember = F4SE::CreateVariantId(788691, 2286078, 2286078);
			inline constexpr auto GetMember = F4SE::CreateVariantId(1517430, 2285936, 4494126);
			inline constexpr auto SetMember = F4SE::CreateVariantId(1360149, 2286589, 2286589);
			inline constexpr auto DeleteMember = F4SE::CreateVariantId(1397711, 2285595, 2285595);
			inline constexpr auto VisitMembers = F4SE::CreateVariantId(1276961, 2286786, 2286786);
			inline constexpr auto GetArraySize = F4SE::CreateVariantId(254218, 2285791, 2285791);
			inline constexpr auto SetArraySize = F4SE::CreateVariantId(1479924, 2286563, 2286563);
			inline constexpr auto GetElement = F4SE::CreateVariantId(827659, 2285881, 2285881);
			inline constexpr auto SetElement = F4SE::CreateVariantId(433707, 2286575, 2286575);
			inline constexpr auto PushBack = F4SE::CreateVariantId(1330475, 2286424, 2286424);
			inline constexpr auto PopBack = F4SE::CreateVariantId(13718, 2286392, 2286392);
			inline constexpr auto RemoveElements = F4SE::CreateVariantId(1286586, 2286475, 2286475);
			inline constexpr auto VisitElements = F4SE::CreateVariantId(851872, 2286785, 2286785);
			inline constexpr auto GetDisplayInfo = F4SE::CreateVariantId(498814, 2285873, 2285873);
			inline constexpr auto SetDisplayInfo = F4SE::CreateVariantId(146578, 2286572, 2286572);
			inline constexpr auto GetDisplayMatrix = F4SE::CreateVariantId(1494470, 2285874, 2285874);
			inline constexpr auto SetDisplayMatrix = F4SE::CreateVariantId(22308, 2286573, 2286573);
			inline constexpr auto GetCxform = F4SE::CreateVariantId(307708, 2285854, 2285854);
			inline constexpr auto SetCxform = F4SE::CreateVariantId(692629, 2286570, 2286570);
			inline constexpr auto AttachMovie = F4SE::CreateVariantId(373078, 2285650, 2285650);
			inline constexpr auto CreateEmptyMovieClip = F4SE::CreateVariantId(1579893, 2285573, 2285573);
			inline constexpr auto GotoAndPlay_Int = F4SE::CreateVariantId(166362, 2286057, 2286057);
			inline constexpr auto GotoAndPlay_String = F4SE::CreateVariantId(1562220, 2286058, 2286058);
			inline constexpr auto Invoke = F4SE::CreateVariantId(655847, 2286101, 2286101);
		}
	}

	namespace Memory
	{
		inline constexpr auto Heap = F4SE::CreateVariantId(939898, 2707353, 2707353);
	}
}

// NOLINTEND(modernize-concat-nested-namespaces)
