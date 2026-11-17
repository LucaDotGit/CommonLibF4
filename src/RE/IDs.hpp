#pragma once

// NOLINTBEGIN(modernize-concat-nested-namespaces)

namespace RE::ID
{
	inline constexpr auto NiMalloc = F4SE::CreateVariantId(974'443, 2'268'535);
	inline constexpr auto NiAlignedAlloc = F4SE::CreateVariantId(442'355, 2'268'536);
	inline constexpr auto NiRealloc = F4SE::CreateVariantId(1'493'163, 2'268'537);
	inline constexpr auto NiAlignedRealloc = F4SE::CreateVariantId(1'572'622, 2'268'538);
	inline constexpr auto NiFree = F4SE::CreateVariantId(242'362, 2'268'539);

	inline constexpr auto RTDynamicCast = F4SE::CreateVariantId(84'112, 2'725'673, 4'818'455);

	namespace AIFormulas
	{
		inline constexpr auto ComputePickpocketSuccess = F4SE::CreateVariantId(915'759, 2'208'977);
		inline constexpr auto GetBarterValue = F4SE::CreateVariantId(984'344, 2'208'969);
	}

	namespace AIProcess
	{
		inline constexpr auto AddToProcedureIndexRunning = F4SE::CreateVariantId(134'486, 2'718'412);
		inline constexpr auto ComputeLastTimeProcessed = F4SE::CreateVariantId(941'571, 2'231'541);
		inline constexpr auto GetActorLightLevel = F4SE::CreateVariantId(898'888, 2'231'981);
		inline constexpr auto GetCommandType = F4SE::CreateVariantId(678'523, 2'231'825);
		inline constexpr auto GetCurrentAmmo = F4SE::CreateVariantId(1'154'936, 2'232'300);
		inline constexpr auto GetCurrentAmmoCount = F4SE::CreateVariantId(184'463, 2'232'301);
		inline constexpr auto GetOccupiedFurniture = F4SE::CreateVariantId(1'162'965, 2'232'401);
		inline constexpr auto GetPackageThatIsRunning = F4SE::CreateVariantId(148'295, 2'231'586);
		inline constexpr auto IsWeaponSubgraphFinishedLoading = F4SE::CreateVariantId(320'183, 2'231'757);
		inline constexpr auto KnockExplosion = F4SE::CreateVariantId(533'106, 2'232'384);
		inline constexpr auto ProcessGreet = F4SE::CreateVariantId(1'174'935, 2'231'808);
		inline constexpr auto RequestLoadAnimationsForWeaponChange = F4SE::CreateVariantId(666'002, 2'231'758);
		inline constexpr auto SetActorsDetectionEvent = F4SE::CreateVariantId(1'376'336, 2'231'738);
		inline constexpr auto SetCommandType = F4SE::CreateVariantId(1'555'789, 2'231'826);
		inline constexpr auto SetCurrentAmmo = F4SE::CreateVariantId(795'983, 2'232'302);
		inline constexpr auto SetCurrentAmmoCount = F4SE::CreateVariantId(795'983, 2'232'303);
		inline constexpr auto SetEquippedItem = F4SE::CreateVariantId(1'200'276, 2'231'627);
		inline constexpr auto SetRunOncePackage = F4SE::CreateVariantId(155'445, 2'232'344);
		inline constexpr auto SetWeaponBonesCulled = F4SE::CreateVariantId(397'172, 2'232'535);
		inline constexpr auto SetupSpecialIdle = F4SE::CreateVariantId(1'446'774, 2'231'704);
		inline constexpr auto StopCurrentIdle = F4SE::CreateVariantId(434'460, 2'231'705);
	}

	namespace AITimer
	{
		inline constexpr auto Timer = F4SE::CreateVariantId(936'770, 2'698'609);
	}

	namespace ActiveEffect
	{
		inline constexpr auto CheckDisplacementSpellOnTarget = F4SE::CreateVariantId(1'415'178, 2'226'001);
	}

	namespace Actor
	{
		inline constexpr auto AddPerk = F4SE::CreateVariantId(187'096, 2'230'121);
		inline constexpr auto CalculateDetectionFormula = F4SE::CreateVariantId(589'441, 2'230'213);
		inline constexpr auto CanUseIdle = F4SE::CreateVariantId(1'223'707, 2'229'592);
		inline constexpr auto ClearAttackStates = F4SE::CreateVariantId(1'525'555, 2'229'773);
		inline constexpr auto DoHitMe = F4SE::CreateVariantId(881'215, 2'231'148);
		inline constexpr auto EndInterruptPackage = F4SE::CreateVariantId(575'188, 2'229'892);
		inline constexpr auto ExitCover = F4SE::CreateVariantId(770'035, 2'231'166);
		inline constexpr auto ForceDetect = F4SE::CreateVariantId(131'995, 2'230'194);
		inline constexpr auto GetAimVector = F4SE::CreateVariantId(554'863, 2'230'378);
		inline constexpr auto GetBodyPartData = F4SE::CreateVariantId(1'485'196, 2'229'571);
		inline constexpr auto GetClosestBone = F4SE::CreateVariantId(1'180'004, 2'230'051);
		inline constexpr auto GetCollisionFilter = F4SE::CreateVariantId(1'474'995, 2'229'991);
		inline constexpr auto GetCombatStyle = F4SE::CreateVariantId(1'270'929, 2'231'053);
		inline constexpr auto GetCrimeTrackingFaction = F4SE::CreateVariantId(1'108'024, 2'229'787);
		inline constexpr auto GetCurrentCollisionGroup = F4SE::CreateVariantId(410'500, 2'229'993);
		inline constexpr auto GetCurrentFireLocation = F4SE::CreateVariantId(663'107, 2'231'167);
		inline constexpr auto GetDesiredSpeed = F4SE::CreateVariantId(106'892, 2'230'410);
		inline constexpr auto GetEquippedItem = F4SE::CreateVariantId(1'318'331, 2'231'089);
		inline constexpr auto GetGhost = F4SE::CreateVariantId(1'298'473, 2'229'668);
		inline constexpr auto GetHealthPercentage = F4SE::CreateVariantId(260'817, 2'229'741);
		inline constexpr auto GetHostileToActor = F4SE::CreateVariantId(1'148'686, 2'229'968);
		inline constexpr auto GetLevel = F4SE::CreateVariantId(661'617, 2'229'734);
		inline constexpr auto GetMobilityCrippled = F4SE::CreateVariantId(281'477, 2'230'996);
		inline constexpr auto GetMountHandle = F4SE::CreateVariantId(313'362, 2'231'230);
		inline constexpr auto GetOfferBarter = F4SE::CreateVariantId(1'482'717, 2'230'005);
		inline constexpr auto GetPerkRank = F4SE::CreateVariantId(1'368'313, 2'230'125);
		inline constexpr auto HandleDefaultAnimationSwitch = F4SE::CreateVariantId(1'163'130, 2'229'780);
		inline constexpr auto HandleItemEquip = F4SE::CreateVariantId(164'912, 2'229'781);
		inline constexpr auto HasObjects = F4SE::CreateVariantId(861'256, 2'229'961);
		inline constexpr auto InitiateDoNothingPackage = F4SE::CreateVariantId(89'993, 2'229'807);
		inline constexpr auto IsCrippled = F4SE::CreateVariantId(1'238'666, 2'230'998);
		inline constexpr auto IsFollowing = F4SE::CreateVariantId(629'579, 2'230'013);
		inline constexpr auto IsJumping = F4SE::CreateVariantId(1'041'558, 2'229'640);
		inline constexpr auto IsPathValid = F4SE::CreateVariantId(1'522'194, 2'230'279);
		inline constexpr auto IsPathing = F4SE::CreateVariantId(989'661, 2'234'312);
		inline constexpr auto IsPathingComplete = F4SE::CreateVariantId(817'283, 2'230'274);
		inline constexpr auto IsQuadruped = F4SE::CreateVariantId(1'552'322, 2'229'614);
		inline constexpr auto IsSneaking = F4SE::CreateVariantId(1'173'627, 2'207'655);
		inline constexpr auto Jump = F4SE::CreateVariantId(1'394'576, 2'229'650);
		inline constexpr auto Move = F4SE::CreateVariantId(737'625, 2'229'934);
		inline constexpr auto PerformAction = F4SE::CreateVariantId(1'057'231, 2'231'177);
		inline constexpr auto PlaySoundByEditorName = F4SE::CreateVariantId(763'587, 2'230'172);
		inline constexpr auto RemovePerk = F4SE::CreateVariantId(1'316'475, 2'230'122);
		inline constexpr auto Reset3D = F4SE::CreateVariantId(302'888, 2'229'913);
		inline constexpr auto RewardExperience = F4SE::CreateVariantId(262'786, 2'230'428);
		inline constexpr auto StopAttack = F4SE::CreateVariantId(1'042'905, 2'231'137);
		inline constexpr auto SPECIALModifiedCallback = F4SE::CreateVariantId(234'305, 2'231'020);
		inline constexpr auto SetGunState = F4SE::CreateVariantId(977'675, 2'231'175);
		inline constexpr auto SetHeading = F4SE::CreateVariantId(353'571, 2'229'625);
		inline constexpr auto StopInteractingQuick = F4SE::CreateVariantId(129'904, 2'231'227);
		inline constexpr auto TrespassAlarm = F4SE::CreateVariantId(1'109'888, 2'229'834);
		inline constexpr auto UnequipObject = F4SE::CreateVariantId(1'363'509, 2'230'479);
		inline constexpr auto UpdateSprinting = F4SE::CreateVariantId(385'539, 2'230'498);
		inline constexpr auto UpdateVoiceTimer = F4SE::CreateVariantId(1'160'883, 2'230'178);
	}

	namespace ActorEquipManager
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(1'174'340, 2'690'994, 4'798'287);
		inline constexpr auto CanEquip = F4SE::CreateVariantId(702'912, 2'231'405);
		inline constexpr auto EquipObject = F4SE::CreateVariantId(988'029, 2'231'392);
		inline constexpr auto UnequipItem = F4SE::CreateVariantId(1'316'852, 2'231'399);
		inline constexpr auto UnequipObject = F4SE::CreateVariantId(1'292'493, 2'231'395);
	}

	namespace ActorUtils
	{
		inline constexpr auto GetEquippedArmorDamageResistance = F4SE::CreateVariantId(1'204'866, 2'227'189);

		namespace ArmorRatingVisitorBase
		{
			inline constexpr auto ctor = F4SE::CreateVariantId(1'212'617, 2'227'205);
			inline constexpr auto call_operator = F4SE::CreateVariantId(1'119'011, 2'227'206);
		}
	}

	namespace ActorValue
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(405'390, 2'189'587);
	}

	namespace AnimationSystemUtils
	{
		inline constexpr auto WillEventChangeState = F4SE::CreateVariantId(35'074, 2'214'271);
	}

	namespace ApplyColorUpdateEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(421'543, 2'707'340);
	}

	namespace BGSAddToPlayerInventoryEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(1'163'657, 2'663'428);
	}

	namespace BGSAnimationSystemUtils
	{
		inline constexpr auto GetActiveSyncInfo = F4SE::CreateVariantId(1'349'978, 2'214'289);
		inline constexpr auto InitializeActorInstant = F4SE::CreateVariantId(672'857, 2'236'393);
		inline constexpr auto IsActiveGraphInTransition = F4SE::CreateVariantId(839'650, 2'214'305);
	}

	namespace BGSArrestEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(309'362, 2'663'413);
	}

	namespace BGSAssaultActorEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(355'870, 2'663'399);
	}

	namespace BGSAttachParentArray
	{
		inline constexpr auto SetParentGroupNumber = F4SE::CreateVariantId(1'412'266, 2'189'125);
	}

	namespace BGSAttractionObject
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(967'451, 2'663'419);
	}

	namespace BGSAudio
	{
		inline constexpr auto GetSoundDescriptor01 = F4SE::CreateVariantId(694'182, 2'214'757);
		inline constexpr auto GetSoundDescriptor02 = F4SE::CreateVariantId(1'305'215, 2'214'758);
		inline constexpr auto GetUIOutputModel = F4SE::CreateVariantId(1'381'590, 2'214'800);
	}

	namespace BGSBribeNPCEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(113'293, 2'663'404);
	}

	namespace BGSCastMagicEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(1'210'444, 2'663'414);
	}

	namespace BGSChangeLocationEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(528'859, 2'663'415);
	}

	namespace BGSClearLocationEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(1'406'072, 2'663'423);
	}

	namespace BGSCraftItemEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(1'382'765, 2'663'430);
	}

	namespace BGSCreatedObjectManager
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(1'000'678, 2'689'006, 4'796'296);
		inline constexpr auto IncrementRef = F4SE::CreateVariantId(1'042'515, 2'228'454);
		inline constexpr auto DecrementRef = F4SE::CreateVariantId(230'928, 2'228'455);
	}

	namespace BGSCrimeGoldEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(990'529, 2'663'412);
	}

	namespace BGSCureEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(920'813, 2'663'433);
	}

	namespace BGSDecalManager
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(716'374, 2'689'264, 4'796'551);
	}

	namespace BGSDefaultObject
	{
		inline constexpr auto ctor = F4SE::CreateVariantId(1'144'014, 2'197'003);
		inline constexpr auto GetDefaultObjects = F4SE::CreateVariantId(561'749, 2'690'473, 4'797'762);
	}

	namespace BGSDefaultObjectManager
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(484'974, 2'192'850);
	}

	namespace BGSDialogueEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(43'243, 2'663'425);
	}

	namespace BGSDiscoverDeadBodyEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(1'140'233, 2'663'435);
	}

	namespace BGSDynamicPersistenceManager
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(109'630, 2'689'026, 4'796'312);
		inline constexpr auto DemoteReference = F4SE::CreateVariantId(222'813, 2'193'820);
		inline constexpr auto PromoteReference = F4SE::CreateVariantId(1'300'345, 2'193'819);
	}

	namespace BGSEntryPoint
	{
		inline constexpr auto HandleEntryPoint = F4SE::CreateVariantId(714'336, 2'206'243);
	}

	namespace BGSEscapeJailEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(771'655, 2'663'410);
	}

	namespace BGSEventProcessedEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1'167'364, 2'201'803);
	}

	namespace BGSFavorEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(262'770, 2'663'427);
	}

	namespace BGSFlatterNPCEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(1'014'013, 2'663'405);
	}

	namespace BGSHackTerminal
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(1'186'942, 2'663'421);
	}

	namespace BGSHelloEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(944'155, 2'663'426);
	}

	namespace BGSIncreaseLevelEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(575'487, 2'663'401);
	}

	namespace BGSInfectionEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(19'653, 2'663'432);
	}

	namespace BGSIntimidateNPCEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(795'005, 2'663'403);
	}

	namespace BGSInventoryInterface
	{
		inline constexpr auto ForceMergeStacks = F4SE::CreateVariantId(1'356'509, 2'194'032);
		inline constexpr auto RequestInventoryItem = F4SE::CreateVariantId(1'200'959, 2'194'009);
		inline constexpr auto Singleton = F4SE::CreateVariantId(501'899, 2'689'299, 4'796'586);
	}

	namespace BGSInventoryItem
	{
		inline constexpr auto FindAndWriteStackData = F4SE::CreateVariantId(770'140, 2'194'123);
		inline constexpr auto GetDisplayFullName01 = F4SE::CreateVariantId(277'641, 2'194'079);
		inline constexpr auto GetDisplayFullName02 = F4SE::CreateVariantId(623'232, 2'194'080);
		inline constexpr auto GetExtraDataAt = F4SE::CreateVariantId(851'493, 2'194'092);
		inline constexpr auto GetInstanceData = F4SE::CreateVariantId(491'493, 2'194'072);
		inline constexpr auto GetInventoryValue = F4SE::CreateVariantId(430'292, 2'194'099);
		inline constexpr auto GetStackCount = F4SE::CreateVariantId(82'050, 2'194'107);
		inline constexpr auto GetTotalWeight = F4SE::CreateVariantId(571'297, 2'194'074);
		inline constexpr auto IsEquipped = F4SE::CreateVariantId(806'787, 2'194'086);
		inline constexpr auto IsQuestObject = F4SE::CreateVariantId(823'447, 2'194'076);
		inline constexpr auto MergeStacks = F4SE::CreateVariantId(1'132'179, 2'194'109);
	}

	namespace BGSInventoryList
	{
		inline constexpr auto ctor = F4SE::CreateVariantId(845'050, 2'194'153);
		inline constexpr auto AddItem = F4SE::CreateVariantId(98'986, 2'194'160);
		inline constexpr auto AddStack = F4SE::CreateVariantId(1'212'559, 2'194'191);
		inline constexpr auto BuildFromContainer = F4SE::CreateVariantId(551'792, 2'194'158);
		inline constexpr auto Clear = F4SE::CreateVariantId(1'080'446, 2'194'162);
		inline constexpr auto GetItemCount = F4SE::CreateVariantId(894'081, 2'194'163);
		inline constexpr auto GetQuestItemCount = F4SE::CreateVariantId(800'903, 2'194'164);
		inline constexpr auto FindAndWriteStackDataForItem = F4SE::CreateVariantId(1'354'005, 2'194'179);
		inline constexpr auto FindItemIndex = F4SE::CreateVariantId(2'111, 2'194'165);
		inline constexpr auto RemoveItem = F4SE::CreateVariantId(400'062, 2'194'169);
	}

	namespace BGSIronSights
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(285'964, 2'663'420);
	}

	namespace BGSJailEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(552'352, 2'663'408);
	}

	namespace BGSKeyword
	{
		inline constexpr auto TypedKeywords = F4SE::CreateVariantId(1'095'775, 2'692'038, 4'799'330);
	}

	namespace BGSKillActorEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(1'037'338, 2'663'398);
	}

	namespace BGSLoadGameBuffer
	{
		inline constexpr auto LoadDataEndian = F4SE::CreateVariantId(1'451'631, 2'228'270);
	}

	namespace BGSLocalizedStringDL
	{
		inline constexpr auto StringInfoMap = F4SE::CreateVariantId(181'435, 2'661'467);
		inline constexpr auto GetText = F4SE::CreateVariantId(472'297, 2'194'238);
	}

	namespace BGSLocalizedStringIL
	{
		inline constexpr auto StringInfoMap = F4SE::CreateVariantId(1'497'866, 2'661'471);
	}

	namespace BGSLocalizedStringPL
	{
		inline constexpr auto StringInfoMap = F4SE::CreateVariantId(446'944, 2'661'461);
	}

	namespace BGSLocation
	{
		inline constexpr auto LinkedLocations = F4SE::CreateVariantId(319'631, 2'661'720);
	}

	namespace BGSLocationLoadedEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(808'292, 2'201'804);
	}

	namespace BGSLocationLoadedStoryEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(748'430, 2'663'417);
	}

	namespace BGSMaterialType
	{
		inline constexpr auto MaterialIDMap = F4SE::CreateVariantId(430'602, 2'661'839);
	}

	namespace BGSMessage
	{
		inline constexpr auto GetConvertedDescription = F4SE::CreateVariantId(8'331, 2'203'353);
	}

	namespace BGSMod
	{
		namespace Attachment
		{
			inline constexpr auto LooseModMap = F4SE::CreateVariantId(1'108'112, 2'661'611);

			namespace Mod
			{
				inline constexpr auto FindFilesForLooseMod = F4SE::CreateVariantId(410'363, 2'197'524);
				inline constexpr auto GetData = F4SE::CreateVariantId(33'658, 0); // inlined post next-gen
				inline constexpr auto GetLooseMod = F4SE::CreateVariantId(1'359'613, 2'197'514);
				inline constexpr auto SetLooseMod = F4SE::CreateVariantId(123'132, 2'197'558);
			}
		}

		namespace Container
		{
			inline constexpr auto GetData = F4SE::CreateVariantId(659'507, 2'189'206);
		}

		namespace Template
		{
			namespace Items
			{
				inline constexpr auto CreateInstanceDataForObjectAndExtra = F4SE::CreateVariantId(147'297, 2'189'244);
			}
		}
	}

	namespace BGSNewVoicePowerEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(239'479, 2'663'434);
	}

	namespace BGSNumericIDIndex
	{
		inline constexpr auto GetNumericID = F4SE::CreateVariantId(915'982, 2'228'199);
		inline constexpr auto SetNumericID = F4SE::CreateVariantId(1'527'703, 2'228'200);
	}

	namespace BGSObjectInstance
	{
		inline constexpr auto ctor = F4SE::CreateVariantId(1'095'748, 2'197'563);
	}

	namespace BGSObjectInstanceExtra
	{
		inline constexpr auto ctor = F4SE::CreateVariantId(1'222'521, 2'189'015);
		inline constexpr auto AddMod = F4SE::CreateVariantId(1'191'757, 2'189'025);
		inline constexpr auto AttachModToReference = F4SE::CreateVariantId(3'303, 2'189'033);
		inline constexpr auto GetNumMods = F4SE::CreateVariantId(1'526'690, 2'189'019);
		inline constexpr auto HasMod = F4SE::CreateVariantId(963'890, 2'189'026);
		inline constexpr auto RemoveInvalidMods = F4SE::CreateVariantId(1'548'060, 2'189'028);
		inline constexpr auto RemoveMod = F4SE::CreateVariantId(1'136'607, 2'189'027);
	}

	namespace BGSOnActorAttachEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(66'772, 2'663'418);
	}

	namespace BGSOnPlayerCompanionDismiss
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(448'593, 2'201'805);
	}

	namespace BGSOnPlayerCreateRobotEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(89'625, 2'201'806);
	}

	namespace BGSOnPlayerEnterVertibirdEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1'312'499, 2'201'807);
	}

	namespace BGSOnPlayerFallLongDistances
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(953'392, 2'201'808);
	}

	namespace BGSOnPlayerFireWeaponEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(594'318, 2'201'809);
	}

	namespace BGSOnPlayerHealTeammateEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(234'967, 2'201'810);
	}

	namespace BGSOnPlayerModArmorWeaponEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1'457'918, 2'201'811);
	}

	namespace BGSOnPlayerModRobotEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1'098'671, 2'201'812);
	}

	namespace BGSOnPlayerSwimmingEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(739'665, 2'201'813);
	}

	namespace BGSOnPlayerUseWorkbenchEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(379'998, 2'201'814);
	}

	namespace BGSOnSpeechChallengeAvailable
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(20'387, 2'201'815);
	}

	namespace BGSOpenCloseForm
	{
		inline constexpr auto AutoCloseRef = F4SE::CreateVariantId(1'175'698, 2'192'797);
		inline constexpr auto GetOpenState = F4SE::CreateVariantId(1'480'253, 2'192'799);
		inline constexpr auto HasOnlyOpenCloseAnims = F4SE::CreateVariantId(45'754, 2'192'796);
		inline constexpr auto IsAnimating = F4SE::CreateVariantId(495'235, 2'192'801);
		inline constexpr auto IsOpenCloseEvent = F4SE::CreateVariantId(1'016'560, 2'192'795);
		inline constexpr auto IsOpenCloseForm = F4SE::CreateVariantId(860'629, 2'192'790);
		inline constexpr auto SetOpenState = F4SE::CreateVariantId(895'942, 2'192'798);
	}

	namespace BGSPayFine
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(1'233'594, 2'663'407);
	}

	namespace BGSPickLockEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(701'969, 2'663'431);
	}

	namespace BGSPickPocket
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(505'459, 2'663'422);
	}

	namespace BGSPlayerGetsFavorEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(332'712, 2'663'406);
	}

	namespace BGSPrimitive
	{
		inline constexpr auto CreateAbstract = F4SE::CreateVariantId(1'095'144, 2'194'290);
	}

	namespace BGSQuestInstanceText
	{
		inline constexpr auto ParseString = F4SE::CreateVariantId(141'681, 2'206'630);
	}

	namespace BGSRadiationDamageEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1'244'003, 2'201'816);
	}

	namespace BGSRelationshipChangeRankEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(1'476'498, 2'663'402);
	}

	namespace BGSRemoveFromPlayerEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(482'080, 2'663'429);
	}

	namespace BGSSaveGameBuffer
	{
		inline constexpr auto SaveDataEndian = F4SE::CreateVariantId(594'281, 2'228'319);
	}

	namespace BGSSaveLoadFileEntry
	{
		inline constexpr auto DeleteGame = F4SE::CreateVariantId(91'575, 2'227'855);
		inline constexpr auto LoadData = F4SE::CreateVariantId(741'580, 2'227'871);
	}

	namespace BGSSaveLoadGame
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(177'947, 2'697'789);
	}

	namespace BGSSaveLoadManager
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(1'247'320, 2'697'802);
		inline constexpr auto BufferSceneScreenShot = F4SE::CreateVariantId(1'234'898, 2'228'079);
		inline constexpr auto BuildSaveGameList = F4SE::CreateVariantId(1'342'984, 2'228'053);
		inline constexpr auto GetFullPath = F4SE::CreateVariantId(505'311, 2'228'030);
		inline constexpr auto GetSaveDirectoryPath = F4SE::CreateVariantId(1'569'549, 2'228'028);
		inline constexpr auto IsLoadingAllowed = F4SE::CreateVariantId(361'558, 2'228'047);
		inline constexpr auto IsSavingAllowed = F4SE::CreateVariantId(735'045, 2'228'045);
		inline constexpr auto QueueSaveLoadTask = F4SE::CreateVariantId(1'487'308, 2'228'080);
		inline constexpr auto Quickload = F4SE::CreateVariantId(603'305, 2'228'042);
		inline constexpr auto Quicksave = F4SE::CreateVariantId(1'055'666, 2'228'041);
		inline constexpr auto AutosaveImpl = F4SE::CreateVariantId(1'280'471, 2'228'043);
		inline constexpr auto DeleteSaveFileImpl = F4SE::CreateVariantId(809'711, 2'228'033);
		inline constexpr auto GenerateSaveFileNameImpl = F4SE::CreateVariantId(434'834, 2'228'059);
		inline constexpr auto LoadGameImpl = F4SE::CreateVariantId(540'706, 2'228'040);
		inline constexpr auto SaveGameImpl = F4SE::CreateVariantId(954'817, 2'228'036);
	}

	namespace BGSScene
	{
		inline constexpr auto ResetAllSceneActions = F4SE::CreateVariantId(1'356'678, 2'206'864);
		inline constexpr auto SetSceneActive = F4SE::CreateVariantId(820'354, 2'206'845);
	}

	namespace BGSSceneActionNPCResponseDialogue
	{
		inline constexpr auto GetCurrentTopicInfo = F4SE::CreateVariantId(1'369'299, 2'206'977);
	}

	namespace BGSSceneActionPlayerDialogue
	{
		inline constexpr auto GetCurrentTopicInfo = F4SE::CreateVariantId(781'358, 2'196'825);
	}

	namespace BGSScriptEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(725'199, 2'663'424);
	}

	namespace BGSServedTime
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(1'482'083, 2'663'409);
	}

	namespace BGSStartQuestEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(1'429'380, 2'663'416);
	}

	namespace BGSStoryEventManager
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(1'160'067, 2'693'504, 4'800'796);
		inline constexpr auto AddEvent = F4SE::CreateVariantId(312'533, 2'214'088);
	}

	namespace BGSStoryTeller
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(562'259, 2'689'008, 4'796'298);
		inline constexpr auto QuestsLock = F4SE::CreateVariantId(315'357, 2'693'510, 4'800'802);
		inline constexpr auto FindQuestLock = F4SE::CreateVariantId(534'915, 2'693'512, 4'800'804);
	}

	namespace BGSSynchronizedAnimationManager
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(1'346'879, 2'690'996, 4'798'289);
		inline constexpr auto IsReferenceInSynchronizedScene = F4SE::CreateVariantId(915'329, 2'214'437);
	}

	namespace BGSTerminal
	{
		inline constexpr auto GetHackDifficultyLockLevel = F4SE::CreateVariantId(537'273, 2'197'777);
		inline constexpr auto IsTerminalRefInUse = F4SE::CreateVariantId(1'093'565, 2'197'779);
		inline constexpr auto Show = F4SE::CreateVariantId(1'069'012, 2'197'776);
	}

	namespace BGSTerrainManager
	{
		inline constexpr auto RecomputeQuickCullData = F4SE::CreateVariantId(1'483'119, 2'213'622);
	}

	namespace BGSTrespassEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(90'057, 2'663'411);
	}

	namespace BGSTriggerMineExplosionEvent
	{
		inline constexpr auto EventIndex = F4SE::CreateVariantId(1'256'916, 2'663'400);
	}

	namespace BSAudioManager
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(1'321'158, 2'703'058);
		inline constexpr auto PlatformInstance = F4SE::CreateVariantId(1'540'790, 2'703'059);
		inline constexpr auto ClearCache = F4SE::CreateVariantId(114'073, 2'267'197);
		inline constexpr auto ClearMaps = F4SE::CreateVariantId(583'644, 2'267'194);
		inline constexpr auto GetSoundHandle = F4SE::CreateVariantId(1'419'045, 2'267'105);
		inline constexpr auto GetSoundHandleByFile = F4SE::CreateVariantId(37'039, 2'267'103);
		inline constexpr auto GetSoundHandleByName = F4SE::CreateVariantId(196'484, 2'267'104);
		inline constexpr auto Init = F4SE::CreateVariantId(40'086, 2'267'098);
		inline constexpr auto KillAll = F4SE::CreateVariantId(580'105, 2'267'108);
		inline constexpr auto Play = F4SE::CreateVariantId(590'936, 2'267'115);
		inline constexpr auto PlayAfter = F4SE::CreateVariantId(1'108'952, 2'267'116);
		inline constexpr auto ResumeAudioThread = F4SE::CreateVariantId(1'274'072, 2'267'101);
		inline constexpr auto Shutdown = F4SE::CreateVariantId(64'750, 2'267'099);
		inline constexpr auto SuspendAudioThread = F4SE::CreateVariantId(1'366'970, 2'267'100);
	}

	namespace BSAwardsSystemUtility
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(1'569'384, 2'255'115);
	}

	namespace BSBloodSplatterShaderProperty
	{
		inline constexpr auto SetFadeSourceRecurse = F4SE::CreateVariantId(160'657, 2'317'965);
	}

	namespace BSGFxDisplayObject
	{
		inline constexpr auto RemoveChild = F4SE::CreateVariantId(1'229'383, 2'287'327);
	}

	namespace BSGFxObject
	{
		inline constexpr auto AcquireFlashObjectByMemberName = F4SE::CreateVariantId(1'172'680, 2'287'014);
		inline constexpr auto AcquireFlashObjectByPath = F4SE::CreateVariantId(1'065'592, 2'287'015);
	}

	namespace BSGFxShaderFXTarget
	{
		inline constexpr auto ProcessEvent = F4SE::CreateVariantId(848'563, 2'287'033);
		inline constexpr auto AppendShaderFXInfos = F4SE::CreateVariantId(544'646, 2'287'021);
		inline constexpr auto CreateAndSetFiltersToColor01 = F4SE::CreateVariantId(1'487'925, 2'287'028);
		inline constexpr auto CreateAndSetFiltersToColor02 = F4SE::CreateVariantId(783'104, 2'287'029);
		inline constexpr auto CreateAndSetFiltersToHUD = F4SE::CreateVariantId(876'001, 2'287'027);
		inline constexpr auto EnableShadedBackground = F4SE::CreateVariantId(278'402, 2'287'022);
	}

	namespace BSGraphics
	{
		inline constexpr auto CurrentRendererWindow = F4SE::CreateVariantId(91'810, 2'704'431);

		namespace RenderData
		{
			inline constexpr auto Singleton = F4SE::CreateVariantId(1'235'449, 2'704'429);
		}

		namespace RenderTargetManager
		{
			inline constexpr auto Singleton = F4SE::CreateVariantId(1'508'457, 2'666'735);
			inline constexpr auto SetEnableDynamicResolution = F4SE::CreateVariantId(116'947, 2'277'197);
		}

		namespace Renderer
		{
			inline constexpr auto IncRef = F4SE::CreateVariantId(1'337'764, 2'276'869);
			inline constexpr auto DecRef = F4SE::CreateVariantId(194'808, 2'276'870);
			inline constexpr auto Begin = F4SE::CreateVariantId(288'964, 2'276'833);
			inline constexpr auto End = F4SE::CreateVariantId(700'869, 2'276'834);
		}

		namespace State
		{
			inline constexpr auto Singleton = F4SE::CreateVariantId(600'795, 2'704'621);
		}

		namespace Utility
		{
			inline constexpr auto ConvertHALFToNiPoint3Stream = F4SE::CreateVariantId(463'129, 2'277'113);
			inline constexpr auto ConvertNiPoint3ToHALFStream = F4SE::CreateVariantId(1'247'946, 2'277'114);
			inline constexpr auto PackVertexData = F4SE::CreateVariantId(156'126, 2'277'106);
			inline constexpr auto UnpackVertexData = F4SE::CreateVariantId(990'748, 2'277'129);
		}
	}

	namespace BSIdleInputWatcher
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(487'306, 2'693'716, 4'801'008);
	}

	namespace BSInputDevice
	{
		inline constexpr auto CreateButtonEvent = F4SE::CreateVariantId(250'821, 2'268'476);
	}

	namespace BSInputDeviceManager
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(1'284'221, 2'694'300, 4'807'767);
	}

	namespace BSInputEnableLayer
	{
		inline constexpr auto DecRef = F4SE::CreateVariantId(659'989, 2'268'272);
	}

	namespace BSInputEnableManager
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(781'703, 2'689'007, 4'796'297);
		inline constexpr auto AllocateNewLayer = F4SE::CreateVariantId(537'494, 2'268'244);
		inline constexpr auto EnableOtherEvent = F4SE::CreateVariantId(1'419'268, 2'268'265);
		inline constexpr auto EnableUserEvent = F4SE::CreateVariantId(1'432'984, 2'268'263);
	}

	namespace BSInputEventQueue
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(664'562, 2'694'386, 4'801'677);
	}

	namespace BSModelDB
	{
		inline constexpr auto Demand01 = F4SE::CreateVariantId(1'066'398, 2'275'153);
		inline constexpr auto Demand02 = F4SE::CreateVariantId(1'225'688, 2'275'154);
	}

	namespace BSPointerHandle
	{
		namespace BSPointerHandleManagerInterface
		{
			inline constexpr auto GetHandle = F4SE::CreateVariantId(901'626, 2'188'676);
			inline constexpr auto GetSmartPointer = F4SE::CreateVariantId(967'277, 2'188'681);
		}
	}

	namespace BSPrecisionTimer
	{
		inline constexpr auto FrequencyMS = F4SE::CreateVariantId(711'608, 2'666'309);
		inline constexpr auto FrequencyMSRecip = F4SE::CreateVariantId(29'307, 2'666'310);
	}

	namespace BSRandom
	{
		inline constexpr auto Generator = F4SE::CreateVariantId(254'053, 2'666'295);
	}

	namespace BSResource
	{
		inline constexpr auto GetOrCreateStream = F4SE::CreateVariantId(1'143'155, 2'269'490);
		inline constexpr auto RegisterLocation = F4SE::CreateVariantId(918'408, 2'269'481);

		namespace EntryDBBaseUtil
		{
			inline constexpr auto ReleaseEntryAction = F4SE::CreateVariantId(777'279, 2'269'463);
		}

		namespace GlobalLocations
		{
			inline constexpr auto Singleton = F4SE::CreateVariantId(1'573'818, 2'703'394);
		}

		namespace GlobalPaths
		{
			inline constexpr auto Singleton = F4SE::CreateVariantId(210'868, 2'703'393);
		}

		namespace ID
		{
			inline constexpr auto GenerateFromPath = F4SE::CreateVariantId(570'861, 2'269'259);
		}
	}

	namespace BSResourceNiBinaryStream
	{
		inline constexpr auto ctor = F4SE::CreateVariantId(1'198'116, 2'269'830);
		inline constexpr auto dtor = F4SE::CreateVariantId(1'516'202, 2'269'832);
		inline constexpr auto BinaryStreamWithRescan = F4SE::CreateVariantId(543'595, 2'205'871);
		inline constexpr auto DoRead = F4SE::CreateVariantId(424'286, 2'269'839);
		inline constexpr auto DoWrite = F4SE::CreateVariantId(1'208'863, 2'269'840);
		inline constexpr auto GetBufferInfo = F4SE::CreateVariantId(265'501, 2'269'836);
		inline constexpr auto Seek = F4SE::CreateVariantId(358'512, 2'269'834);
	}

	namespace BSScaleformManager
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(106'578, 2'689'600, 4'796'889);
		inline constexpr auto GetMovieFilename = F4SE::CreateVariantId(1'191'277, 2'287'428);
		inline constexpr auto InitMovieViewport = F4SE::CreateVariantId(206'895, 2'287'430, 4'494'254);
		inline constexpr auto LoadMovieImpl = F4SE::CreateVariantId(1'526'234, 2'287'422);
	}

	namespace BSScaleformRenderer
	{
		inline constexpr auto Initialize = F4SE::CreateVariantId(1'403'529, 2'284'938);
	}

	namespace BSScaleformTranslator
	{
		inline constexpr auto AddTranslations = F4SE::CreateVariantId(810'671, 2'295'298);
	}

	namespace BSScript
	{
		namespace Internal
		{
			namespace Stack
			{
				inline constexpr auto GetPageForFrame = F4SE::CreateVariantId(1'429'302, 2'314'680);
				inline constexpr auto GetStackFrameVariable = F4SE::CreateVariantId(897'539, 2'314'681);
			}

			namespace VirtualMachine
			{
				inline constexpr auto AttemptFunctionCall = F4SE::CreateVariantId(1'500'402, 2'315'231);
			}
		}

		namespace NF_util
		{
			namespace NativeFunctionBase
			{
				inline constexpr auto Call = F4SE::CreateVariantId(571'037, 2'314'780);
			}
		}

		namespace Object
		{
			inline constexpr auto IncRef = F4SE::CreateVariantId(461'710, 2'314'436);
			inline constexpr auto DecRef = F4SE::CreateVariantId(541'793, 2'314'437);
		}
	}

	namespace BSShaderProperty
	{
		inline constexpr auto SetMaterial = F4SE::CreateVariantId(706'318, 2'316'285);
	}

	namespace BSShaderTextureSet
	{
		inline constexpr auto CreateObject = F4SE::CreateVariantId(993'063, 2'316'324);
	}

	namespace BSShaderUtil
	{
		inline constexpr auto SetMaterialAlpha = F4SE::CreateVariantId(211'260, 2'317'566);
	}

	namespace BSSoundHandle
	{
		inline constexpr auto HolotapeSoundHandle = F4SE::CreateVariantId(965'852, 2'664'207);
		inline constexpr auto ClearFollowedObject = F4SE::CreateVariantId(208'569, 2'267'067);
		inline constexpr auto FadeInPlay = F4SE::CreateVariantId(353'528, 2'267'075);
		inline constexpr auto FadeOutAndRelease = F4SE::CreateVariantId(260'328, 2'267'076);
		inline constexpr auto FadeTo = F4SE::CreateVariantId(446'556, 2'267'074);
		inline constexpr auto GetDuration = F4SE::CreateVariantId(1'192'939, 2'267'062);
		inline constexpr auto GetVolume = F4SE::CreateVariantId(688'691, 2'267'056);
		inline constexpr auto IsEnvelopeLoop = F4SE::CreateVariantId(529'498, 2'267'051);
		inline constexpr auto IsReady = F4SE::CreateVariantId(926'805, 2'267'063);
		inline constexpr auto Pause = F4SE::CreateVariantId(1'168'427, 2'267'044);
		inline constexpr auto Play = F4SE::CreateVariantId(384'073, 2'267'042);
		inline constexpr auto PlayAfter = F4SE::CreateVariantId(557'072, 2'267'043);
		inline constexpr auto Release = F4SE::CreateVariantId(1'511'135, 2'267'072);
		inline constexpr auto SetOutputModel = F4SE::CreateVariantId(170'407, 2'267'053);
		inline constexpr auto SetPosition = F4SE::CreateVariantId(1'538'508, 2'267'064);
		inline constexpr auto SetSoundCategory = F4SE::CreateVariantId(1'140'884, 2'267'052);
		inline constexpr auto SetStaticAttenuation = F4SE::CreateVariantId(581'557, 2'267'061);
		inline constexpr auto SetVolume = F4SE::CreateVariantId(422'259, 2'267'057);
		inline constexpr auto Stop = F4SE::CreateVariantId(1'340'948, 2'267'045);
	}

	namespace BSStringPool
	{
		inline constexpr auto FindEntry_char = F4SE::CreateVariantId(1'239'592, 2'268'727);
		inline constexpr auto FindEntry_wchar = F4SE::CreateVariantId(82'204, 2'268'728);
		inline constexpr auto GetEntry_char = F4SE::CreateVariantId(507'142, 2'268'729);
		inline constexpr auto GetEntry_wchar = F4SE::CreateVariantId(345'043, 2'268'730);

		namespace Entry
		{
			inline constexpr auto Release = F4SE::CreateVariantId(1'204'430, 2'268'720);
		}
	}

	namespace BSSystemFileStreamer
	{
		inline constexpr auto UncacheAll = F4SE::CreateVariantId(40'925, 2'268'797);
	}

	namespace BSTEvent
	{
		namespace BSTGlobalEvent
		{
			inline constexpr auto Singleton = F4SE::CreateVariantId(1'424'022, 2'688'814, 4'796'078);
		}
	}

	namespace BSTempEffectDebris
	{
		inline constexpr auto ctor = F4SE::CreateVariantId(1'075'623, 2'212'059);
	}

	namespace BSTempEffectWeaponBlood
	{
		inline constexpr auto ClearEffectForWeapon = F4SE::CreateVariantId(718'866, 2'212'158);
	}

	namespace BSThreadEvent
	{
		inline constexpr auto InitSDM = F4SE::CreateVariantId(1'425'097, 2'268'180);
	}

	namespace BSTimer
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(1'256'126, 2'703'179);
		inline constexpr auto GlobalTimeMultiplier = F4SE::CreateVariantId(365'546, 2'666'307);
		inline constexpr auto GlobalTimeMultiplierTarget = F4SE::CreateVariantId(1'266'509, 2'666'308);
		inline constexpr auto SetGlobalTimeMultiplier = F4SE::CreateVariantId(1'419'977, 2'267'970);
	}

	namespace BSUIMessageData
	{
		inline constexpr auto SendUIBoolMessage = F4SE::CreateVariantId(1'388'308, 2'284'981);
		inline constexpr auto SendUIPtrMessage = F4SE::CreateVariantId(1'374'542, 2'284'982);
		inline constexpr auto SendUIStringMessage = F4SE::CreateVariantId(1'270'833, 2'284'977);
		inline constexpr auto SendUIStringUIntMessage = F4SE::CreateVariantId(99'795, 2'284'979);
	}

	namespace BSUtilities
	{
		inline constexpr auto ConvertFloatToHalf = F4SE::CreateVariantId(10'414, 2'212'098);
		inline constexpr auto ConvertHalfToFloat = F4SE::CreateVariantId(1'502'141, 2'195'843);
		inline constexpr auto GetObjectByName = F4SE::CreateVariantId(843'650, 2'274'841);
	}

	namespace BSXAudio2Audio
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(1'345'596, 2'703'147);
	}

	namespace BSXAudio2Graph
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(1'219'921, 2'703'127);
	}

	namespace BarterMenu
	{
		inline constexpr auto ClearTradingData = F4SE::CreateVariantId(1'112'285, 2'222'700);
		inline constexpr auto CompleteTrade = F4SE::CreateVariantId(379'932, 2'222'701);
		inline constexpr auto GetCapsOwedByPlayer = F4SE::CreateVariantId(672'405, 2'222'714);
	}

	namespace BobbleheadCollected
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(1'542'436, 2'233'716);
		}
	}

	namespace Bounty
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(212'496, 2'233'717);
		}
	}

	namespace BucketTable
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(1'390'486, 2'268'736);
	}

	namespace Calendar
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(1'444'952, 2'689'092, 4'796'378);
	}

	namespace CanDisplayNextHUDMessage
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(344'866, 2'695'041, 4'802'332);
	}

	namespace CellAttachDetachEvent
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(862'142, 2'192'250);
	}

	namespace ChestLooted
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(464'264, 2'233'718);
		}
	}

	namespace ColorUpdateEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1'226'590, 2'695'540, 4'802'831);
	}

	namespace CombatFormulas
	{
		inline constexpr auto CalcResistedPercentage = F4SE::CreateVariantId(420'470, 2'209'007);
		inline constexpr auto CalcScopeSteadyActionPointDrain = F4SE::CreateVariantId(380'926, 2'209'045);
		inline constexpr auto CalcTargetedLimbDamage = F4SE::CreateVariantId(1'530'751, 2'209'033);
		inline constexpr auto CalcWeaponDamage = F4SE::CreateVariantId(651'643, 2'209'001);
		inline constexpr auto CalculateAimModelWobble = F4SE::CreateVariantId(211'411, 2'209'001);
		inline constexpr auto GetNumCrippledAttackConditions = F4SE::CreateVariantId(170'270, 2'209'041);
		inline constexpr auto GetWeaponDisplayAccuracy = F4SE::CreateVariantId(1'137'654, 2'209'049);
		inline constexpr auto GetWeaponDisplayDamage = F4SE::CreateVariantId(1'431'014, 2'209'046);
		inline constexpr auto GetWeaponDisplayRange = F4SE::CreateVariantId(1'324'037, 2'209'047);
		inline constexpr auto GetWeaponDisplayRateOfFire = F4SE::CreateVariantId(1'403'591, 2'209'048);
	}

	namespace CombatUtilities
	{
		inline constexpr auto CalculateProjectileLOS01 = F4SE::CreateVariantId(798'616, 2'240'617);
		inline constexpr auto CalculateProjectileLOS02 = F4SE::CreateVariantId(55'339, 2'240'616);
		inline constexpr auto CalculateProjectileTrajectory = F4SE::CreateVariantId(1'575'156, 2'240'611);
		inline constexpr auto WorldGravity = F4SE::CreateVariantId(1'378'547, 2'700'340);
	}

	namespace ComparisonQualifiers
	{
		inline constexpr auto ContainerQualifier = F4SE::CreateVariantId(883'895, 2'190'674);
		inline constexpr auto UIQualifier = F4SE::CreateVariantId(179'412, 2'190'675);
	}

	namespace Console
	{
		inline constexpr auto ExecuteCommand = F4SE::CreateVariantId(1'061'864, 2'248'537);
		inline constexpr auto ExecuteQueuedCommand = F4SE::CreateVariantId(675'475, 2'248'538);
		inline constexpr auto CurrentPickIndex = F4SE::CreateVariantId(1'407'033, 2'701'382);
		inline constexpr auto PickRef = F4SE::CreateVariantId(170'742, 2'701'395);
		inline constexpr auto PickRefs = F4SE::CreateVariantId(875'116, 2'701'391);
		inline constexpr auto SetCurrentPickRef = F4SE::CreateVariantId(79'066, 2'248'551);
	}

	namespace ConsoleLog
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(689'441, 2'690'148, 4'797'437);
		inline constexpr auto AddStringLock = F4SE::CreateVariantId(1'174'138, 2'701'408);
		inline constexpr auto AddString = F4SE::CreateVariantId(764, 2'248'593);
	}

	namespace ContainerMenu
	{
		inline constexpr auto TakeAllItems = F4SE::CreateVariantId(1'323'703, 2'248'619);
	}

	namespace ContainerMenuBase
	{
		namespace ItemSorter
		{
			inline constexpr auto IncrementSort = F4SE::CreateVariantId(1'307'263, 2'222'848);
		}
	}

	namespace ControlMap
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(325'206, 2'692'014, 4'799'307);
		inline constexpr auto PopInputContext = F4SE::CreateVariantId(74'587, 2'268'336);
		inline constexpr auto PushInputContext = F4SE::CreateVariantId(1'404'410, 2'268'335);
		inline constexpr auto RemapButton = F4SE::CreateVariantId(11'351, 2'268'330);
		inline constexpr auto SaveRemappings = F4SE::CreateVariantId(1'141'541, 2'268'331);
		inline constexpr auto SetTextEntryMode = F4SE::CreateVariantId(1'270'079, 2'268'339, 4'491'359);
	}

	namespace CorpseEaten
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(717'261, 2'233'719);
		}
	}

	namespace CriticalHitEvent
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(969'000, 2'233'720);
		}
	}

	namespace CurrentRadiationSourceCount
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(696'410, 2'696'196, 4'803'487);
	}

	namespace CustomMarkerUpdate
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(1'221'626, 2'233'721);
		}
	}

	namespace DEFAULT_OBJECT_DATA
	{
		inline constexpr auto DefaultObjects = F4SE::CreateVariantId(838'886, 838'886); // same for all versions
	}

	namespace DaysJailed
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(1'473'833, 2'233'722);
		}
	}

	namespace DialogueMenuUtils
	{
		inline constexpr auto CloseMenu = F4SE::CreateVariantId(764'651, 2'249'659);
		inline constexpr auto OpenMenu = F4SE::CreateVariantId(1'562'703, 2'249'658);
		inline constexpr auto ShowButtons = F4SE::CreateVariantId(191'452, 2'249'663);
		inline constexpr auto ShowSpeechChallengeAnim = F4SE::CreateVariantId(868'159, 2'249'665);
	}

	namespace DoBeforeNewOrLoadCompletedEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(787'908, 2'695'542, 4'802'833);
	}

	namespace EffectItem
	{
		inline constexpr auto GetDescription = F4SE::CreateVariantId(949'839, 2'189'612);
	}

	namespace EquippedWeaponData
	{
		inline constexpr auto SetupFireSounds = F4SE::CreateVariantId(1'468'462, 2'232'275);
	}

	namespace ExamineMenu
	{
		inline constexpr auto BuildConfirmed = F4SE::CreateVariantId(1'396'668, 2'223'013);
		inline constexpr auto BuildWeaponScrappingArray = F4SE::CreateVariantId(646'841, 2'223'077);
		inline constexpr auto ConsumeSelectedItems = F4SE::CreateVariantId(686'586, 2'223'052);
		inline constexpr auto GetSelectedIndex = F4SE::CreateVariantId(776'503, 2'223'022);
		inline constexpr auto ShowConfirmMenu = F4SE::CreateVariantId(443'081, 2'223'081);
	}

	namespace Explosion
	{
		inline constexpr auto GetDamage = F4SE::CreateVariantId(1'270'292, 2'236'658);
		inline constexpr auto ProcessTargets = F4SE::CreateVariantId(1'146'379, 2'236'664);
	}

	namespace ExteriorCellSingleton
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(128'691, 2'689'084, 4'796'370);
	}

	namespace ExtraDataList
	{
		inline constexpr auto CompareList = F4SE::CreateVariantId(585'876, 2'190'098);
		inline constexpr auto CopyList = F4SE::CreateVariantId(561'304, 2'190'094);
		inline constexpr auto CreateInstanceData = F4SE::CreateVariantId(1'280'130, 2'190'185);
	}

	namespace ExtraTextDisplayData
	{
		inline constexpr auto GetDisplayName = F4SE::CreateVariantId(1'523'343, 2'191'318);
	}

	namespace FORM_ENUM_STRING
	{
		inline constexpr auto FormTypeStrings = F4SE::CreateVariantId(1'309'967, 1'309'967); // same for all versions
	}

	namespace FatmanDeaths
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(143'539, 2'233'723);
		}
	}

	namespace FavoritesManager
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(198'281, 2'694'399, 4'801'690);
		inline constexpr auto ClearCurrentAmmoCount = F4SE::CreateVariantId(541'959, 2'248'745);
		inline constexpr auto UseQuickkeyItem = F4SE::CreateVariantId(303'130, 2'248'744);
	}

	namespace FinePaid
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(395'763, 2'233'724);
		}
	}

	namespace FirstThirdPersonSwitch
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(648'220, 2'233'725);
		}
	}

	namespace FlatScreenModel
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(847'741, 2'694'427, 4'801'718);
	}

	namespace FusionCoreConsumed
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(900'334, 2'233'726);
		}
	}

	namespace FusionCoreEjected
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(1'152'491, 2'233'727);
		}
	}

	namespace GameMenuBase
	{
		inline constexpr auto SetIsTopButtonBar = F4SE::CreateVariantId(1'367'353, 2'223'204);
		inline constexpr auto OnMenuDisplayStateChanged = F4SE::CreateVariantId(1'274'450, 2'223'205);
		inline constexpr auto CacheShaderFXQuadsForRenderer_Impl = F4SE::CreateVariantId(863'029, 2'223'200);
		inline constexpr auto TransferCachedShaderFXQuadsForRenderer = F4SE::CreateVariantId(65'166, 2'223'201);
		inline constexpr auto SetViewportRect = F4SE::CreateVariantId(1'554'334, 2'223'202);
		inline constexpr auto AppendShaderFXInfos = F4SE::CreateVariantId(583'584, 2'223'203);
		inline constexpr auto SetUpButtonBar = F4SE::CreateVariantId(531'584, 2'223'197);
	}

	namespace GamePlayFormulas
	{
		inline constexpr auto CalcSprintingActionPoints = F4SE::CreateVariantId(1'053'786, 2'209'071);
		inline constexpr auto CalculateItemHealthDamageBonus = F4SE::CreateVariantId(612'133, 2'209'087);
		inline constexpr auto CalculateItemValue = F4SE::CreateVariantId(960'532, 2'209'074);
		inline constexpr auto CanHackGateCheck = F4SE::CreateVariantId(269'668, 2'209'069);
		inline constexpr auto CanPickLockGateCheck = F4SE::CreateVariantId(1'160'841, 2'209'066);
		inline constexpr auto GetExperienceReward = F4SE::CreateVariantId(853'500, 2'209'076);
		inline constexpr auto GetHackingWordCount = F4SE::CreateVariantId(190'347, 2'209'067);
		inline constexpr auto GetLockXPReward = F4SE::CreateVariantId(880'926, 2'209'070);
	}

	namespace GameScript
	{
		inline constexpr auto BindCObject01 = F4SE::CreateVariantId(1'505'389, 2'249'772);
		inline constexpr auto BindCObject02 = F4SE::CreateVariantId(81'787, 2'249'773);

		namespace BasicEventHandler
		{
			inline constexpr auto Singleton = F4SE::CreateVariantId(1'460'997, 2'702'014);
		}

		namespace CombatEventHandler
		{
			inline constexpr auto Singleton = F4SE::CreateVariantId(459'907, 2'701'831);
		}

		namespace CustomEventHandler
		{
			inline constexpr auto Singleton = F4SE::CreateVariantId(7'183, 2'701'855);
		}

		namespace DistanceEventHandler
		{
			inline constexpr auto Singleton = F4SE::CreateVariantId(764'245, 2'692'010, 4'799'303);
		}

		namespace FragmentEventHandler
		{
			inline constexpr auto Singleton = F4SE::CreateVariantId(1'417'043, 2'701'848);
		}

		namespace GameVM
		{
			inline constexpr auto Singleton = F4SE::CreateVariantId(996'227, 2'689'134, 4'796'420);
			inline constexpr auto QueuePostRenderCall = F4SE::CreateVariantId(34'412, 2'251'314);
			inline constexpr auto RegisterForAllGameEvents = F4SE::CreateVariantId(680'454, 2'251'353);
			inline constexpr auto SendEventToObjectAndRelated = F4SE::CreateVariantId(367'992, 2'251'344);
		}

		namespace HandlePolicy
		{
			inline constexpr auto DropSaveLoadRemapData = F4SE::CreateVariantId(647'657, 2'249'995);
			inline constexpr auto GetInventoryObjFromHandle = F4SE::CreateVariantId(66'597, 2'249'989);
			inline constexpr auto GetInventoryObjOrFormFromHandle = F4SE::CreateVariantId(1'316'930, 2'249'988);
			inline constexpr auto UpdatePersistence = F4SE::CreateVariantId(11'020, 2'249'991);
		}

		namespace InventoryEventHandler
		{
			inline constexpr auto Singleton = F4SE::CreateVariantId(1'576'434, 2'701'878);
		}

		namespace LOSEventHandler
		{
			inline constexpr auto Singleton = F4SE::CreateVariantId(983'179, 2'692'011, 4'799'304);
		}

		namespace MenuEventHandler
		{
			inline constexpr auto Singleton = F4SE::CreateVariantId(1'562'790, 2'701'898);
		}

		namespace ObjectBindPolicy
		{
			inline constexpr auto EndSaveLoad = F4SE::CreateVariantId(1'558'837, 2'250'482);
		}

		namespace SleepEventHandler
		{
			inline constexpr auto Singleton = F4SE::CreateVariantId(1'455'597, 2'701'936);
		}

		namespace TeleportEventHandler
		{
			inline constexpr auto Singleton = F4SE::CreateVariantId(97'940, 2'702'013);
		}

		namespace TimerEventHandler
		{
			inline constexpr auto Singleton = F4SE::CreateVariantId(1'202'884, 2'692'012, 4'799'305);
		}

		namespace TrackedStatsEventHandler
		{
			inline constexpr auto Singleton = F4SE::CreateVariantId(317'348, 2'702'012);
		}

		namespace WaitEventHandler
		{
			inline constexpr auto Singleton = F4SE::CreateVariantId(536'926, 2'702'011);
		}
	}

	namespace GameSettingCollection
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(8'308, 2'690'301, 4'797'590);
		inline constexpr auto InitCollection = F4SE::CreateVariantId(948'832, 2'188'690);
	}

	namespace GameUIModel
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(17'419, 2'695'523, 4'802'814);
		inline constexpr auto SetGameColors = F4SE::CreateVariantId(523'665, 2'220'911);
		inline constexpr auto UpdateDataModels = F4SE::CreateVariantId(1'269'653, 2'220'905);
	}

	namespace HUDDataModel
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(910'584, 2'694'613, 4'801'904);
	}

	namespace HUDMenu
	{
		inline constexpr auto SetHUDColor = F4SE::CreateVariantId(505'571, 2'248'918);
	}

	namespace HUDMenuUtils
	{
		inline constexpr auto GetGameplayHUDBackgroundColor = F4SE::CreateVariantId(698'605, 2'248'845);
		inline constexpr auto GetGameplayHUDColor = F4SE::CreateVariantId(34'363, 2'248'840);
		inline constexpr auto WorldPtToScreenPt3 = F4SE::CreateVariantId(1'132'313, 2'222'464);
	}

	namespace HUDModeEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(683'142, 2'694'697, 4'801'988);
	}

	namespace HUDQuickContainerDataModel
	{
		inline constexpr auto TakeSelectedItem = F4SE::CreateVariantId(1'401'485, 2'221'653);
		inline constexpr auto PopulateItemList = F4SE::CreateVariantId(1'280'441, 2'221'647);
	}

	namespace HitData
	{
		inline constexpr auto CollectDamage = F4SE::CreateVariantId(15'680, 2'236'861);
	}

	namespace HolotapeChatterEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(884'534, 2'201'817);
	}

	namespace HolotapeMenu
	{
		inline constexpr auto ShowHolotapeInPipboy = F4SE::CreateVariantId(217'953, 2'224'028);
		inline constexpr auto ShowHolotapeInTerminal = F4SE::CreateVariantId(390'509, 2'224'029);
	}

	namespace HolotapePlayEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(525'346, 2'201'818);
	}

	namespace HolotapeStateChanged
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(1'404'654, 2'233'728);
		}
	}

	namespace IAnimationGraphManagerHolder
	{
		inline constexpr auto RevertAnimationGraphManager = F4SE::CreateVariantId(41'382, 2'214'541);
		inline constexpr auto SetGraphVariableBool = F4SE::CreateVariantId(1'437'197, 2'214'543);
		inline constexpr auto SetGraphVariableFloat = F4SE::CreateVariantId(27'400, 2'214'545);
		inline constexpr auto SetGraphVariableInt = F4SE::CreateVariantId(732'926, 2'214'544);
	}

	namespace IFormFactory
	{
		inline constexpr auto Factories = F4SE::CreateVariantId(228'366, 2'689'177, 4'796'464);
	}

	namespace IMenu
	{
		inline constexpr auto ShouldHandleEvent = F4SE::CreateVariantId(1'241'790, 2'287'392);
		inline constexpr auto PassesRenderConditionText = F4SE::CreateVariantId(937'304, 2'287'379);
		inline constexpr auto OnSetSafeRect = F4SE::CreateVariantId(964'859, 2'287'375);
		inline constexpr auto ProcessScaleformEvent = F4SE::CreateVariantId(150'211, 2'287'395);
		inline constexpr auto RefreshPlatform = F4SE::CreateVariantId(1'071'829, 2'287'374);
	}

	namespace INIPrefSettingCollection
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(767'844, 2'703'234);
	}

	namespace INISettingCollection
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(791'183, 2'704'108);
	}

	namespace IRendererResourceManager
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(583'240, 2'703'483);
	}

	namespace ImageSpaceEffectFullScreenBlur
	{
		inline constexpr auto IsDisabled = F4SE::CreateVariantId(372'489, 2'713'225);
	}

	namespace ImageSpaceEffectGetHit
	{
		inline constexpr auto IsDisabled = F4SE::CreateVariantId(1'523'708, 2'713'237);
	}

	namespace ImageSpaceEffectHDR
	{
		inline constexpr auto UsePipboyScreenMask = F4SE::CreateVariantId(405'286, 2'678'029, 4'784'697);
	}

	namespace ImageSpaceEffectPipboyScreen
	{
		inline constexpr auto IsPowerArmorPipboy = F4SE::CreateVariantId(1'065'542, 2'713'203);
	}

	namespace ImageSpaceEffectRadialBlur
	{
		inline constexpr auto IsDisabled = F4SE::CreateVariantId(1'500'590, 2'713'225);
	}

	namespace ImageSpaceEffectTemporalAA
	{
		inline constexpr auto MaskS = F4SE::CreateVariantId(775'377, 2'713'052);
	}

	namespace ImageSpaceManager
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(161'743, 2'712'627);
	}

	namespace ImageSpaceModifierInstance
	{
		inline constexpr auto Stop = F4SE::CreateVariantId(1'298'537, 2'199'897);
	}

	namespace ImageSpaceModifierInstanceDOF
	{
		inline constexpr auto Trigger = F4SE::CreateVariantId(1'158'048, 2'199'922);
	}

	namespace ImageSpaceModifierInstanceForm
	{
		inline constexpr auto Stop01 = F4SE::CreateVariantId(217'873, 2'199'909);
		inline constexpr auto Stop02 = F4SE::CreateVariantId(549'773, 2'199'910);
		inline constexpr auto Trigger01 = F4SE::CreateVariantId(179'769, 2'199'906);
		inline constexpr auto Trigger02 = F4SE::CreateVariantId(1'216'312, 2'199'907);
	}

	namespace Interface3D
	{
		inline constexpr auto Create = F4SE::CreateVariantId(88'488, 2'222'519);
		inline constexpr auto Disable = F4SE::CreateVariantId(938'370, 2'222'523);
		inline constexpr auto DisableAll = F4SE::CreateVariantId(1'470'633, 2'222'521);
		inline constexpr auto Enable = F4SE::CreateVariantId(326'895, 2'222'522);
		inline constexpr auto GetByName = F4SE::CreateVariantId(140'387, 2'222'524);
		inline constexpr auto MainScreen_AddPointLight = F4SE::CreateVariantId(1'335'675, 2'222'531);
		inline constexpr auto MainScreen_AddSpotLight = F4SE::CreateVariantId(1'056'093, 2'222'532);
		inline constexpr auto MainScreen_ClearLights = F4SE::CreateVariantId(683'530, 2'222'533);
		inline constexpr auto MainScreen_SetScreenAttached3D = F4SE::CreateVariantId(817'727, 2'222'528);
		inline constexpr auto MainScreen_SetWorldAttached3D = F4SE::CreateVariantId(724'778, 2'222'529);
		inline constexpr auto Offscreen_AddLight = F4SE::CreateVariantId(1'267'198, 2'222'543);
		inline constexpr auto Offscreen_Clear3D = F4SE::CreateVariantId(1'533'262, 2'222'542);
		inline constexpr auto Offscreen_ClearLights = F4SE::CreateVariantId(1'039'253, 2'222'545);
		inline constexpr auto Offscreen_GetRenderTargetHeight = F4SE::CreateVariantId(1'280'897, 2'222'538);
		inline constexpr auto Offscreen_GetRenderTargetWidth = F4SE::CreateVariantId(403'273, 2'222'537);
		inline constexpr auto Offscreen_Set3D = F4SE::CreateVariantId(43'983, 2'222'541);
		inline constexpr auto Offscreen_SetDebugMode = F4SE::CreateVariantId(1'277'879, 2'222'549);
		inline constexpr auto Offscreen_SetDirectionalLight = F4SE::CreateVariantId(987'144, 2'222'544);
		inline constexpr auto Release = F4SE::CreateVariantId(74'749, 2'222'520);
		inline constexpr auto SetViewport = F4SE::CreateVariantId(825'410, 2'222'552);
	}

	namespace Inventory3DManager
	{
		inline constexpr auto Begin3D = F4SE::CreateVariantId(662'659, 2'249'084);
		inline constexpr auto ClearModel = F4SE::CreateVariantId(63'218, 2'249'113);
		inline constexpr auto DisableRendering = F4SE::CreateVariantId(255'893, 2'249'099);
		inline constexpr auto EnableRendering = F4SE::CreateVariantId(176'578, 2'249'098);
		inline constexpr auto End3D = F4SE::CreateVariantId(1'512'675, 2'249'086);
		inline constexpr auto SetModelScale = F4SE::CreateVariantId(1'319'701, 2'249'097);
		inline constexpr auto SetModelScreenPosition = F4SE::CreateVariantId(2'967, 2'249'096);
	}

	namespace InventoryItemDisplayData
	{
		inline constexpr auto ctor = F4SE::CreateVariantId(679'373, 2'222'612);
	}

	namespace InventoryUserUIUtils
	{
		inline constexpr auto AddItemCardInfoEntry = F4SE::CreateVariantId(489'521, 2'222'648);
		inline constexpr auto PopulateItemCardInfo_Helper = F4SE::CreateVariantId(475'551, 2'222'625);
	}

	namespace InvestmentMade
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(74'865, 2'233'729);
		}
	}

	namespace ItemCrafted
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(922'450, 2'233'730);
		}
	}

	namespace ItemPickpocketed
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(1'362'222, 2'233'731);
		}
	}

	namespace ItemSteal
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(831'553, 2'233'732);
		}
	}

	namespace JailEscape
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(1'083'747, 2'233'733);
		}
	}

	namespace Jailing
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(1'335'790, 2'233'734);
		}
	}

	namespace JunkItemFound
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(5'404, 2'233'735);
		}
	}

	namespace LevelIncrease
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(349'120, 2'233'736);
		}
	}

	namespace LoadingMenu
	{
		inline constexpr auto PopulateLoadScreens = F4SE::CreateVariantId(316'170, 2'249'232);
		inline constexpr auto StartTestingLoadingMenu = F4SE::CreateVariantId(933'696, 2'249'224);
	}

	namespace LocationMarkerArrayUpdate
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(510'524, 2'233'737);
		}
	}

	namespace LockpickingMenu
	{
		inline constexpr auto CurrentLockRef = F4SE::CreateVariantId(1'190'207, 2'701'603);
		inline constexpr auto CurrentLockLevel = F4SE::CreateVariantId(1'495'416, 2'665'059);
		inline constexpr auto DamageLockpick = F4SE::CreateVariantId(1'118'991, 2'249'275);
		inline constexpr auto OpenLockpickingMenu = F4SE::CreateVariantId(129'892, 2'249'263);
	}

	namespace LocksPicked
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(594'991, 2'249'292);
		}
	}

	namespace MagicCaster
	{
		inline constexpr auto FindTargets = F4SE::CreateVariantId(1'558'908, 2'226'296);
	}

	namespace MagicTarget
	{
		inline constexpr auto IsTakingHealthDamageFromActiveEffect = F4SE::CreateVariantId(999'442, 2'226'397);
		inline constexpr auto IsTakingRadDamageFromActiveEffect = F4SE::CreateVariantId(1'079'111, 2'226'398);
	}

	namespace Main
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(756'304, 2'698'043);
		inline constexpr auto WorldRootNode = F4SE::CreateVariantId(569'647, 2'698'065);
		inline constexpr auto MenuRootNode = F4SE::CreateVariantId(789'152, 2'698'066);
		inline constexpr auto LandLODNode = F4SE::CreateVariantId(1'208'715, 2'698'035);
		inline constexpr auto ObjectLODNode = F4SE::CreateVariantId(1'115'209, 2'698'036);
		inline constexpr auto DoneNewOrLoadGame = F4SE::CreateVariantId(1'229'840, 2'698'033);
		inline constexpr auto GameDataLoaded = F4SE::CreateVariantId(1'004'331, 2'698'032);
		inline constexpr auto GameSystemsShouldUpdate = F4SE::CreateVariantId(779'552, 2'698'031);
		inline constexpr auto SetCameraFOV = F4SE::CreateVariantId(1'348'813, 2'228'973);
	}

	namespace MemoryManager
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(343'176, 2'193'197, 4'471'522);
		inline constexpr auto RegisterMemoryManager = F4SE::CreateVariantId(453'212, 2'228'356);
		inline constexpr auto GetThreadScrapHeap = F4SE::CreateVariantId(1'495'205, 2'267'850);
		inline constexpr auto Allocate = F4SE::CreateVariantId(652'767, 2'267'872);
		inline constexpr auto Reallocate = F4SE::CreateVariantId(1'502'917, 2'267'873);
		inline constexpr auto Deallocate = F4SE::CreateVariantId(1'582'181, 2'267'874);
		inline constexpr auto Size = F4SE::CreateVariantId(1'453'698, 2'267'858);
	}

	namespace MenuControls
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(520'890, 2'689'089, 4'796'375);
		inline constexpr auto ForcePauseGame = F4SE::CreateVariantId(1'307'560, 2'249'384);
		inline constexpr auto ForceResumeGame = F4SE::CreateVariantId(668'856, 2'249'385);
	}

	namespace MenuCursor
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(695'696, 2'696'546, 4'803'837);
		inline constexpr auto CenterCursor = F4SE::CreateVariantId(1'107'298, 2'287'473);
		inline constexpr auto RegisterCursor = F4SE::CreateVariantId(1'318'193, 2'287'485);
		inline constexpr auto SetCursorConstraintsRaw = F4SE::CreateVariantId(907'092, 2'287'480);
		inline constexpr auto UnregisterCursor = F4SE::CreateVariantId(1'225'249, 2'287'486);
	}

	namespace MenuTopicManager
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(1'391'114, 2'688'800, 4'796'064);
	}

	namespace MessageBoxMenu
	{
		inline constexpr auto ShowMessage = F4SE::CreateVariantId(442'479, 2'249'469);
	}

	namespace MessageMenuManager
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(959'572, 2'689'087, 4'796'373);
		inline constexpr auto CreateImpl = F4SE::CreateVariantId(89'563, 2'249'456);
		inline constexpr auto ShowMessages = F4SE::CreateVariantId(843'289, 2'249'461);
	}

	namespace MineDisarmed
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(762'974, 2'233'738);
		}
	}

	namespace MiscStatManager
	{
		inline constexpr auto MiscStats = F4SE::CreateVariantId(803'089, 2'689'603, 4'796'892);
	}

	namespace MysteriousStrangerVisits
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(1'014'921, 2'233'739);
		}
	}

	namespace NavMeshObstacleManager
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(1'398'127, 2'689'085, 4'796'371);
		inline constexpr auto UpdateLock = F4SE::CreateVariantId(1'235'889, 2'693'124, 4'800'416);
	}

	namespace NiAlphaProperty
	{
		inline constexpr auto SetAlphaBlending = F4SE::CreateVariantId(645'586, 0); // inlined post next-gen
		inline constexpr auto SetAlphaTesting = F4SE::CreateVariantId(645'586, 0);	// inlined post next-gen
		inline constexpr auto SetDestBlendMode = F4SE::CreateVariantId(725'249, 0); // inlined post next-gen
		inline constexpr auto SetSrcBlendMode = F4SE::CreateVariantId(976'961, 0);	// inlined post next-gen
		inline constexpr auto SetTestMode = F4SE::CreateVariantId(976'961, 0);		// inlined post next-gen
	}

	namespace NiCamera
	{
		inline constexpr auto BoundInFrustum = F4SE::CreateVariantId(781'526, 2'194'525);
		inline constexpr auto ViewPointToRay = F4SE::CreateVariantId(460'613, 2'270'338);
		inline constexpr auto WorldPtToScreenPt3 = F4SE::CreateVariantId(109'441, 2'270'344);
	}

	namespace NiControllerManager
	{
		inline constexpr auto GetNiControllerManager = F4SE::CreateVariantId(1'013'515, 2'271'798);
		inline constexpr auto GetSequenceByName = F4SE::CreateVariantId(846'648, 2'192'808);
	}

	namespace NiControllerSequence
	{
		inline constexpr auto Activate = F4SE::CreateVariantId(829'033, 2'271'861);
	}

	namespace NiCullingProcess
	{
		inline constexpr auto SetFrustum = F4SE::CreateVariantId(1'142'496, 2'270'782);
	}

	namespace NiMatrix3
	{
		inline constexpr auto ToEulerAnglesXYZ = F4SE::CreateVariantId(34'114, 2'269'806);
		inline constexpr auto ToEulerAnglesXZY = F4SE::CreateVariantId(1'164'218, 2'269'807);
		inline constexpr auto ToEulerAnglesYXZ = F4SE::CreateVariantId(272'989, 2'269'808);
		inline constexpr auto ToEulerAnglesYZX = F4SE::CreateVariantId(963'829, 2'269'809);
		inline constexpr auto ToEulerAnglesZYX = F4SE::CreateVariantId(511'385, 2'269'810);
		inline constexpr auto ToEulerAnglesZXY = F4SE::CreateVariantId(606'387, 2'269'824);
		inline constexpr auto FromEulerAnglesXYZ = F4SE::CreateVariantId(124'665, 2'269'813);
		inline constexpr auto FromEulerAnglesXZY = F4SE::CreateVariantId(1'319'962, 2'269'814);
		inline constexpr auto FromEulerAnglesYXZ = F4SE::CreateVariantId(55'761, 2'269'815);
		inline constexpr auto FromEulerAnglesYZX = F4SE::CreateVariantId(373'803, 2'269'816);
		inline constexpr auto FromEulerAnglesZYX = F4SE::CreateVariantId(1'569'564, 2'269'817);
		inline constexpr auto FromEulerAnglesZXY = F4SE::CreateVariantId(326'460, 2'269'825);
	}

	namespace NiRefObject
	{
		inline constexpr auto TotalObjectCount = F4SE::CreateVariantId(1'161'724, 2'703'471);
	}

	namespace NiTexture
	{
		inline constexpr auto SetAllowDegrade = F4SE::CreateVariantId(948'181, 2'270'148);
	}

	namespace ObjectiveState
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(524'087, 2'206'676);
	}

	namespace PerkPointIncreaseEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(685'859, 2'697'359, 4'804'734);
	}

	namespace PerkUtilities
	{
		inline constexpr auto RemoveGrenadeTrajectory = F4SE::CreateVariantId(672'186, 2'233'303);
	}

	namespace PickRefUpdateEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1'572'336, 2'195'292);
	}

	namespace PipboyDataManager
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(1'178'971, 2'689'086, 4'796'372);
	}

	namespace PipboyInventoryData
	{
		inline constexpr auto AddItemCardInfoEntry = F4SE::CreateVariantId(1'191'786, 2'225'267);
		inline constexpr auto BaseAddItemCardInfoEntry = F4SE::CreateVariantId(1'150'364, 2'225'270);
		inline constexpr auto PopulateItemCardInfo = F4SE::CreateVariantId(54'211, 2'225'266);
		inline constexpr auto QueueItemCardRepopulate = F4SE::CreateVariantId(1'034'299, 2'225'281);
		inline constexpr auto RepopulateItemCardsOnSection = F4SE::CreateVariantId(892'255, 2'225'279);
		inline constexpr auto SortItems = F4SE::CreateVariantId(1'292'464, 2'225'244);
	}

	namespace PipboyInventoryMenu
	{
		inline constexpr auto SetQuickkey = F4SE::CreateVariantId(539'741, 2'224'159);
		inline constexpr auto SortItems = F4SE::CreateVariantId(1'082'239, 2'224'164);
	}

	namespace PipboyInventoryUtils
	{
		inline constexpr auto DoSlotsOverlap = F4SE::CreateVariantId(1'035'436, 2'225'230);
		inline constexpr auto FillDamageTypeInfo = F4SE::CreateVariantId(928'518, 2'225'234);
		inline constexpr auto FillResistTypeInfo = F4SE::CreateVariantId(1'578'434, 2'225'235);
	}

	namespace PipboyLightEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1'140'080, 2'696'280, 4'803'571);
	}

	namespace PipboyManager
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(553'234, 2'691'945, 4'799'238);
		inline constexpr auto AddMenuToPipboy = F4SE::CreateVariantId(394'568, 2'225'453);
		inline constexpr auto ClosedownPipboy = F4SE::CreateVariantId(731'410, 2'225'480);
		inline constexpr auto DisablePipboyShader = F4SE::CreateVariantId(662'519, 2'225'484);
		inline constexpr auto EnablePipboyShader = F4SE::CreateVariantId(157'921, 2'225'483);
		inline constexpr auto InitPipboy = F4SE::CreateVariantId(1'477'369, 2'225'479);
		inline constexpr auto LowerPipboy = F4SE::CreateVariantId(1'444'875, 2'225'454);
		inline constexpr auto OnPipboyCloseAnim = F4SE::CreateVariantId(1'231'000, 2'225'457);
		inline constexpr auto OnPipboyCloseAnimFailed = F4SE::CreateVariantId(1'362'084, 2'225'459);
		inline constexpr auto OnPipboyClosed = F4SE::CreateVariantId(592'088, 2'225'458);
		inline constexpr auto OnPipboyOpenAnim = F4SE::CreateVariantId(1'500'318, 2'225'448);
		inline constexpr auto OnPipboyOpenAnimFailed = F4SE::CreateVariantId(702'357, 2'225'449);
		inline constexpr auto OnPipboyOpened = F4SE::CreateVariantId(1'299'608, 2'225'450);
		inline constexpr auto PlayItemAnimOnClose = F4SE::CreateVariantId(377'837, 2'225'461);
		inline constexpr auto PlayPipboyCloseAnim = F4SE::CreateVariantId(273'927, 2'225'456);
		inline constexpr auto PlayPipboyGenericOpenAnim = F4SE::CreateVariantId(809'076, 2'225'447);
		inline constexpr auto PlayPipboyLoadHolotapeAnim = F4SE::CreateVariantId(477'096, 2'225'446);
		inline constexpr auto PlayPipboyOpenAnim = F4SE::CreateVariantId(663'900, 2'225'444);
		inline constexpr auto PlayPipboyOpenTerminalAnim = F4SE::CreateVariantId(743'427, 2'225'445);
		inline constexpr auto ProcessLoweringReason = F4SE::CreateVariantId(302'903, 2'225'486);
		inline constexpr auto QPipboyActive = F4SE::CreateVariantId(470'886, 2'225'460);
		inline constexpr auto RaisePipboy = F4SE::CreateVariantId(726'763, 2'225'455);
		inline constexpr auto RefreshPipboyRenderSurface = F4SE::CreateVariantId(81'339, 2'225'478);
		inline constexpr auto StartAnimationGraphListening = F4SE::CreateVariantId(714'713, 2'225'490);
		inline constexpr auto StopAnimationGraphListening = F4SE::CreateVariantId(621'144, 2'225'491);
		inline constexpr auto UpdateCursorConstraint = F4SE::CreateVariantId(900'802, 2'225'488);
	}

	namespace PipboyMapData
	{
		inline constexpr auto GetTravelLocationRefr = F4SE::CreateVariantId(501'825, 2'225'515);
		inline constexpr auto UpdateQuestMarkers = F4SE::CreateVariantId(1'440'569, 2'225'549);
	}

	namespace PipboyMenu
	{
		inline constexpr auto RefreshMapMarkers = F4SE::CreateVariantId(434'114, 2'224'187);
	}

	namespace PipboyPlayerInfoData
	{
		inline constexpr auto UpdateArmorData = F4SE::CreateVariantId(362'497, 2'225'790);
		inline constexpr auto UpdateCarryWeightData = F4SE::CreateVariantId(338'096, 2'225'788);
		inline constexpr auto UpdateGoldData = F4SE::CreateVariantId(1'423'427, 2'225'791);
		inline constexpr auto UpdateWeaponData = F4SE::CreateVariantId(1'108'639, 2'225'789);
	}

	namespace PlayerActiveEffectChanged
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(1'267'315, 2'233'740);
		}
	}

	namespace PlayerAddicted
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(1'519'765, 2'233'741);
		}
	}

	namespace PlayerCamera
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(1'171'980, 2'688'801, 4'796'065);
		inline constexpr auto SetState = F4SE::CreateVariantId(858'847, 2'214'742);
		inline constexpr auto GetCameraPosition = F4SE::CreateVariantId(1'574'794, 2'248'334);
		inline constexpr auto ToggleFreeCameraMode = F4SE::CreateVariantId(224'913, 2'248'368);
		inline constexpr auto StartPipboyMode = F4SE::CreateVariantId(998'069, 2'248'358);
		inline constexpr auto StopPipboyMode = F4SE::CreateVariantId(811'954, 2'248'359);
	}

	namespace PlayerCharacter
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(303'410, 2'690'919, 4'798'212);
		inline constexpr auto ClearPrison = F4SE::CreateVariantId(920'390, 2'233'196);
		inline constexpr auto EnableRadio = F4SE::CreateVariantId(741'937, 2'233'211);
		inline constexpr auto GetDifficultyLevel = F4SE::CreateVariantId(922'962, 2'233'056);
		inline constexpr auto GetPlayerHandle = F4SE::CreateVariantId(522'947, 2'698'072);
		inline constexpr auto HandlePositionPlayerRequest = F4SE::CreateVariantId(146'861, 2'232'905);
		inline constexpr auto HasLOSToTarget = F4SE::CreateVariantId(449'775, 2'233'004);
		inline constexpr auto IsGodMode = F4SE::CreateVariantId(1'032'309, 2'232'986);
		inline constexpr auto IsHolotapePlaying = F4SE::CreateVariantId(530'826, 2'233'206);
		inline constexpr auto IsImmortal = F4SE::CreateVariantId(500'346, 2'232'988);
		inline constexpr auto IsPlayerInDialogue = F4SE::CreateVariantId(60'126, 2'188'686);
		inline constexpr auto PauseHolotape = F4SE::CreateVariantId(1'567'456, 2'233'208);
		inline constexpr auto PlayHolotape = F4SE::CreateVariantId(1'581'042, 2'233'207);
		inline constexpr auto QueueFastTravel = F4SE::CreateVariantId(556'824, 2'232'918);
		inline constexpr auto RemoveLastUsedPowerArmor = F4SE::CreateVariantId(1'488'486, 2'233'024);
		inline constexpr auto SelectPerk = F4SE::CreateVariantId(1'397'326, 2'232'926);
		inline constexpr auto SetAIControlledPackage = F4SE::CreateVariantId(1'431'972, 2'233'087);
		inline constexpr auto SetEscaping = F4SE::CreateVariantId(25'528, 2'233'142);
		inline constexpr auto SetLastDialogueInput = F4SE::CreateVariantId(696'117, 2'233'190);
		inline constexpr auto SetPerkCount = F4SE::CreateVariantId(616'372, 2'233'187);
		inline constexpr auto SetTintingData = F4SE::CreateVariantId(802'946, 2'233'185);
		inline constexpr auto SetVATSCriticalCount = F4SE::CreateVariantId(327'338, 2'233'219);
		inline constexpr auto ShowPipboyLight = F4SE::CreateVariantId(1'304'102, 2'233'203);
		inline constexpr auto StopHolotape = F4SE::CreateVariantId(1'021'305, 2'233'209);
	}

	namespace PlayerCharacterQuestEvent
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(189'797, 2'233'742);
		}
	}

	namespace PlayerControls
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(544'871, 2'692'013, 4'799'306);
		inline constexpr auto CanPerformAction = F4SE::CreateVariantId(565'925, 2'234'795);
		inline constexpr auto DoAction = F4SE::CreateVariantId(818'081, 2'234'796);
	}

	namespace PlayerCrosshairModeEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1'231'665, 2'694'517, 4'801'808);
	}

	namespace PlayerDifficultySettingChanged
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(135'270, 2'233'743);
		}
	}

	namespace PlayerInDialogueChanged
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(694'363, 2'233'744);
		}
	}

	namespace PlayerLifeStateChanged
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(946'172, 2'233'745);
		}
	}

	namespace PoisonedWeapon
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(1'198'663, 2'233'746);
		}
	}

	namespace PowerArmor
	{
		inline constexpr auto ActorInPowerArmor = F4SE::CreateVariantId(1'176'757, 2'219'437);
		inline constexpr auto GetArmorKeyword = F4SE::CreateVariantId(961'172, 2'194'743);
		inline constexpr auto GetBatteryKeyword = F4SE::CreateVariantId(1'493'537, 2'194'740);
		inline constexpr auto GetDefaultBatteryObject = F4SE::CreateVariantId(1'279'247, 2'194'761);
		inline constexpr auto IsPowerArmorBattery = F4SE::CreateVariantId(1'012'910, 2'219'422);
		inline constexpr auto SyncFurnitureVisualsToInventory = F4SE::CreateVariantId(1'078'979, 2'219'453);
	}

	namespace PowerArmorGeometry
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(1'365'745, 2'694'441, 4'801'732);
		inline constexpr auto HidePipboyPAGeometry = F4SE::CreateVariantId(976'332, 2'248'877);
		inline constexpr auto ShowPipboyPAGeometry = F4SE::CreateVariantId(19'066, 2'248'876);
	}

	namespace PowerArmorLightData
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(120'809, 2'701'547);
	}

	namespace PowerUtils
	{
		inline constexpr auto ItemIsPowerConnection = F4SE::CreateVariantId(17'704, 2'195'078);
		inline constexpr auto ItemIsPowerReceiver = F4SE::CreateVariantId(210'626, 2'195'060);
	}

	namespace ProcessLists
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(1'569'706, 2'688'869, 4'796'160);
		inline constexpr auto AreHostileActorsNear = F4SE::CreateVariantId(1'053'584, 2'234'105);
		inline constexpr auto IsActorTargetingREFinPackage = F4SE::CreateVariantId(559'542, 2'234'033);
		inline constexpr auto RequestHighestDetectionLevelAgainstActor = F4SE::CreateVariantId(1'036'693, 2'234'111);
	}

	namespace REFR_LOCK
	{
		inline constexpr auto GetLockLevel = F4SE::CreateVariantId(782'953, 2'191'018);
	}

	namespace RadioManager
	{
		inline constexpr auto QPlayerRadioEnabled = F4SE::CreateVariantId(811'921, 2'227'674);
		inline constexpr auto QCurrentPlayerFreq = F4SE::CreateVariantId(227'903, 2'227'670);
		inline constexpr auto EnablePlayerRadio = F4SE::CreateVariantId(653'012, 2'227'673);
	}

	namespace RelationshipChange
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(1'450'835, 2'233'747);
		}
	}

	namespace RicochetHit
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(120'692, 2'233'748);
		}
	}

	namespace SCRIPT_FUNCTION
	{
		inline constexpr auto ConsoleFunctions = F4SE::CreateVariantId(901'511, 901'511); // same for all versions
		inline constexpr auto ScriptFunctions = F4SE::CreateVariantId(75'173, 75'173);	  // same for all versions
	}

	namespace SWFToCodeFunctionHandler
	{
		inline constexpr auto MapCodeMethodToASFunction = F4SE::CreateVariantId(1'263'128, 2'287'419);
		inline constexpr auto RegisterCodeObject = F4SE::CreateVariantId(67'637, 2'287'415);
	}

	namespace SandmanKill
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(372'944, 2'233'749);
		}
	}

	namespace SavefileMetadata
	{
		inline constexpr auto FillDataFromFileName = F4SE::CreateVariantId(116'131, 2'228'156);
	}

	namespace ScrapHeap
	{
		inline constexpr auto Allocate = F4SE::CreateVariantId(1'085'394, 2'267'983);
		inline constexpr auto Deallocate = F4SE::CreateVariantId(923'307, 2'267'984);
	}

	namespace ScreenSplatter
	{
		inline constexpr auto Clear = F4SE::CreateVariantId(1'478'405, 2'194'783);
		inline constexpr auto CreateGeometry = F4SE::CreateVariantId(26'875, 2'194'786);
		inline constexpr auto Camera = F4SE::CreateVariantId(1'504'969, 2'689'675, 4'796'964);
		inline constexpr auto Count = F4SE::CreateVariantId(869'591, 2'689'669, 4'796'958);
		inline constexpr auto RootNode = F4SE::CreateVariantId(141'695, 2'689'676, 4'796'965);
		inline constexpr auto IsEnabled = F4SE::CreateVariantId(1'551'380, 2'689'668, 4'796'957);
		inline constexpr auto Update = F4SE::CreateVariantId(907'893, 2'194'781);
	}

	namespace Script
	{
		inline constexpr auto CompileAndRunImpl = F4SE::CreateVariantId(526'625, 2'204'287);
		inline constexpr auto ParseParameters = F4SE::CreateVariantId(1'607, 2'204'298);
		inline constexpr auto ProcessScripts = F4SE::CreateVariantId(175'133, 2'661'858);
	}

	namespace SendHUDMessage
	{
		inline constexpr auto PopHUDMode = F4SE::CreateVariantId(1'495'042, 2'222'444);
		inline constexpr auto PushHUDMode = F4SE::CreateVariantId(1'321'764, 2'222'443);
		inline constexpr auto SetPowerArmorMode = F4SE::CreateVariantId(361'745, 2'222'459);
		inline constexpr auto ShowHUDMessage = F4SE::CreateVariantId(1'163'005, 2'222'440);
	}

	namespace SitWaitMenu
	{
		inline constexpr auto OnEnterFurniture = F4SE::CreateVariantId(562'238, 2'249'503);
		inline constexpr auto OnExitFurniture = F4SE::CreateVariantId(454'795, 2'249'504);
	}

	namespace Sky
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(484'694, 2'192'448);
		inline constexpr auto ForceWeather = F4SE::CreateVariantId(698'558, 2'208'861);
		inline constexpr auto ResetWeather = F4SE::CreateVariantId(6'511, 2'208'860);
	}

	namespace SpeechChallengeSucceeded
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(625'391, 2'233'750);
		}
	}

	namespace SplineUtils
	{
		inline constexpr auto ConnectSpline = F4SE::CreateVariantId(59'311, 2'195'073);
		inline constexpr auto DisconnectSpline = F4SE::CreateVariantId(750'682, 2'195'074);
	}

	namespace SubtitleManager
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(740'511, 2'689'088, 4'796'374);
		inline constexpr auto RWLock = F4SE::CreateVariantId(589'656, 2'701'704);
	}

	namespace TES
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(1'194'835, 2'698'044);
		inline constexpr auto CreateTextureImage = F4SE::CreateVariantId(848'961, 2'192'059);
		inline constexpr auto UpdateMultiBoundVisibility = F4SE::CreateVariantId(1'281'872, 2'192'134);
	}

	namespace TESActivateEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(166'230, 2'201'819);
	}

	namespace TESActiveEffectApplyRemoveEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1'388'854, 2'201'820);
	}

	namespace TESActorBaseData
	{
		inline constexpr auto GetLevel = F4SE::CreateVariantId(151'866, 2'192'891);
	}

	namespace TESActorLocationChangeEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1'029'687, 2'201'821);
	}

	namespace TESAmmo
	{
		inline constexpr auto GetReloadsWithAmmoRef = F4SE::CreateVariantId(1'035'622, 2'197'864);
	}

	namespace TESAudio
	{
		namespace ScriptedMusicState
		{
			inline constexpr auto Singleton = F4SE::CreateVariantId(1'216'761, 2'691'985, 4'799'278);
			inline constexpr auto Remove = F4SE::CreateVariantId(544'747, 2'226'976);
		}
	}

	namespace TESBookReadEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(670'837, 2'201'822);
	}

	namespace TESBoundObject
	{
		inline constexpr auto ApplyMods = F4SE::CreateVariantId(113'585, 2'198'325);
	}

	namespace TESCellAttachDetachEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(311'270, 2'201'823);
	}

	namespace TESCellFullyLoadedEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1'534'478, 2'201'824);
	}

	namespace TESCellReadyToApplyDecalsEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1'175'067, 2'201'825);
	}

	namespace TESCombatEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(815'924, 2'201'826);
	}

	namespace TESCommandModeCompleteCommandEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(456'275, 2'201'827);
	}

	namespace TESCommandModeEnterEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(97'273, 2'201'828);
	}

	namespace TESCommandModeExitEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1'320'161, 2'201'829);
	}

	namespace TESCommandModeGiveCommandEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(960'995, 2'201'830);
	}

	namespace TESCondition
	{
		inline constexpr auto ClearAllConditionItems = F4SE::CreateVariantId(757'713, 2'211'988);
		inline constexpr auto IsTrue = F4SE::CreateVariantId(1'275'731, 2'211'989);
		inline constexpr auto IsTrueForAllButFunction = F4SE::CreateVariantId(1'182'457, 0); // inlined post next-gen
	}

	namespace TESConditionItem
	{
		inline constexpr auto GetComparisonValue = F4SE::CreateVariantId(1'373'349, 2'212'007);
		inline constexpr auto IsTrue01 = F4SE::CreateVariantId(1'453'240, 2'212'008);
		inline constexpr auto IsTrue02 = F4SE::CreateVariantId(43'452, 2'212'009);
	}

	namespace TESConsciousnessEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(601'920, 2'201'831);
	}

	namespace TESContainerChangedEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(242'538, 2'201'832);
	}

	namespace TESDataHandler
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(711'558, 2'688'883, 4'796'135);
		inline constexpr auto AddFormToDataHandler = F4SE::CreateVariantId(350'112, 2'192'271);
		inline constexpr auto CreateReferenceAtLocation = F4SE::CreateVariantId(500'304, 2'192'301);
		inline constexpr auto GetExtCellDataFromFileByEditorID = F4SE::CreateVariantId(1'411'233, 2'192'293);
		inline constexpr auto CollectGoodLoadingScreensFunctor = F4SE::CreateVariantId(259'735, 2'249'240);
		inline constexpr auto IsFormIDInUse = F4SE::CreateVariantId(1'448'838, 2'192'351);
		inline constexpr auto CheckModsLoaded = F4SE::CreateVariantId(1'432'894, 2'192'323);
	}

	namespace TESDeathEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1'465'690, 2'201'833);
	}

	namespace TESDeferredKillEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1'106'254, 2'201'834);
	}

	namespace TESDescription
	{
		inline constexpr auto GetDescription = F4SE::CreateVariantId(523'613, 2'193'019);
	}

	namespace TESDestructionStageChangedEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(747'291, 2'201'835);
	}

	namespace TESEnterBleedoutEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(387'731, 2'201'836);
	}

	namespace TESEnterSneakingEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(28'138, 2'201'837);
	}

	namespace TESEquipEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1'251'703, 2'201'838);
	}

	namespace TESEscortWaitStartEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(892'350, 2'201'839);
	}

	namespace TESEscortWaitStopEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(533'153, 2'201'840);
	}

	namespace TESExitFurnitureEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(174'010, 2'201'841);
	}

	namespace TESFile
	{
		inline constexpr auto dtor = F4SE::CreateVariantId(226'797, 2'192'487);
		inline constexpr auto ChangeBufferSize = F4SE::CreateVariantId(352'143, 2'192'567);
		inline constexpr auto CloseTES = F4SE::CreateVariantId(766'555, 2'192'491);
		inline constexpr auto FindForm = F4SE::CreateVariantId(1'324'254, 2'192'521);
		inline constexpr auto GetChunkData = F4SE::CreateVariantId(188'910, 2'192'538);
		inline constexpr auto GetTESChunk = F4SE::CreateVariantId(641'361, 2'192'536);
		inline constexpr auto GetThreadSafeFileForThread = F4SE::CreateVariantId(1'004'882, 2'192'565);
		inline constexpr auto LoadForm = F4SE::CreateVariantId(1'183'915, 2'192'544);
		inline constexpr auto NextChunk = F4SE::CreateVariantId(1'252'764, 2'192'537);
		inline constexpr auto NextForm = F4SE::CreateVariantId(644'374, 2'192'527);
		inline constexpr auto NextGroup = F4SE::CreateVariantId(339'855, 2'192'522);
		inline constexpr auto OpenTES = F4SE::CreateVariantId(728'465, 2'192'490);
		inline constexpr auto TESRewind = F4SE::CreateVariantId(1'096'742, 2'192'525);
		inline constexpr auto TESRewindChunk = F4SE::CreateVariantId(737'725, 2'192'526);
	}

	namespace TESForm
	{
		inline constexpr auto AddCompileIndex = F4SE::CreateVariantId(1'315'637, 2'193'152);
		inline constexpr auto TotalFormCount = F4SE::CreateVariantId(1'104'561, 2'689'176, 4'796'463);
		inline constexpr auto FormEditorIDMap = F4SE::CreateVariantId(642'758, 2'689'179, 4'796'466);
		inline constexpr auto FormEditorIDMapLock = F4SE::CreateVariantId(910'917, 2'689'190, 4'796'477);
		inline constexpr auto FormNumericIDMap = F4SE::CreateVariantId(422'985, 2'689'178, 4'796'465);
		inline constexpr auto FormNumericIDMapLock = F4SE::CreateVariantId(691'815, 2'689'189, 4'796'476);
		inline constexpr auto SetTemporary = F4SE::CreateVariantId(482'454, 2'193'125);
	}

	namespace TESFormDeleteEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1'396'562, 2'201'842);
	}

	namespace TESFormIDRemapEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1'037'385, 2'201'843);
	}

	namespace TESFullName
	{
		inline constexpr auto SparseFullNameMap = F4SE::CreateVariantId(226'372, 2'533'149);
	}

	namespace TESFurniture
	{
		inline constexpr auto GetContainer = F4SE::CreateVariantId(1'049'933, 2'198'043);
	}

	namespace TESFurnitureEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(678'665, 2'201'844);
	}

	namespace TESGrabReleaseEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(319'018, 2'201'845);
	}

	namespace TESHarvestEvent
	{
		namespace ItemHarvested
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(11'738, 2'193'351);
		}
	}

	namespace TESHitEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1'411'899, 2'201'886);
	}

	namespace TESInitScriptEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1'542'080, 2'201'846);
	}

	namespace TESLevItem
	{
		inline constexpr auto OverrideNameMap = F4SE::CreateVariantId(1'524'252, 2'661'643);
	}

	namespace TESLeveledList
	{
		inline constexpr auto CalculateCurrentFormList = F4SE::CreateVariantId(603'811, 2'193'259);
		inline constexpr auto CalculateCurrentFormListForRef = F4SE::CreateVariantId(507'405, 2'193'260);
		inline constexpr auto SpecialChanceGlobalMap = F4SE::CreateVariantId(1'043'289, 2'661'411);
	}

	namespace TESLimbCrippleEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1'182'805, 2'201'847);
	}

	namespace TESLoadGameEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(823'570, 2'201'848);
	}

	namespace TESLocationClearedEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1'372'013, 2'201'849);
	}

	namespace TESLockChangedEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(105'061, 2'201'850);
	}

	namespace TESMagicEffectApplyEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1'327'824, 2'201'851);
	}

	namespace TESMagicWardHitEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(968'652, 2'201'852);
	}

	namespace TESNPC
	{
		inline constexpr auto AlternateHeadPartListMap = F4SE::CreateVariantId(1'306'546, 2'662'364);
		inline constexpr auto GetFacialBoneMorphIntensity = F4SE::CreateVariantId(272'217, 2'207'416);
		inline constexpr auto GetShortName = F4SE::CreateVariantId(1'221'705, 2'207'405);
		inline constexpr auto SetTintingData = F4SE::CreateVariantId(452'734, 2'207'493);
	}

	namespace TESObjectARMO
	{
		inline constexpr auto Protects = F4SE::CreateVariantId(1'028'523, 2'198'535);
	}

	namespace TESObjectCELL
	{
		inline constexpr auto AttachReference3D = F4SE::CreateVariantId(125'567, 2'200'620);
		inline constexpr auto FindInFileFast = F4SE::CreateVariantId(577'761, 2'200'375);
		inline constexpr auto GetInteriorOffset = F4SE::CreateVariantId(655'838, 2'200'350);
		inline constexpr auto Load = F4SE::CreateVariantId(165'674, 2'200'163);
		inline constexpr auto RemoveReference = F4SE::CreateVariantId(650'855, 2'200'299);
		inline constexpr auto SetCullCellMarkers = F4SE::CreateVariantId(192'259, 2'192'259);
		inline constexpr auto SetInteriorOffset = F4SE::CreateVariantId(1'439'668, 2'200'351);
		inline constexpr auto UpdateAllDecals = F4SE::CreateVariantId(283'071, 2'200'643);
		inline constexpr auto UpdateAllRefsLoaded = F4SE::CreateVariantId(374'552, 2'200'415);
	}

	namespace TESObjectLoadedEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(609'604, 2'201'853);
	}

	namespace TESObjectREFR
	{
		inline constexpr auto ActivateRef = F4SE::CreateVariantId(753'531, 2'201'147);
		inline constexpr auto AddInventoryItem = F4SE::CreateVariantId(78'185, 2'200'949);
		inline constexpr auto AddLockChange = F4SE::CreateVariantId(1'578'706, 2'200'731);
		inline constexpr auto ApplyArtObject = F4SE::CreateVariantId(357'908, 2'205'200);
		inline constexpr auto ApplyEffectShader = F4SE::CreateVariantId(652'173, 2'205'201);
		inline constexpr auto CanBeMoved = F4SE::CreateVariantId(683'719, 2'200'898);
		inline constexpr auto Enable = F4SE::CreateVariantId(1'396'707, 2'201'150);
		inline constexpr auto FindReferenceFor3D = F4SE::CreateVariantId(766'937, 2'201'082);
		inline constexpr auto GetCurrentLocation = F4SE::CreateVariantId(1'135'470, 2'201'163);
		inline constexpr auto GetEditorDead = F4SE::CreateVariantId(941'388, 2'200'781);
		inline constexpr auto GetGoldAmount = F4SE::CreateVariantId(564'356, 2'200'923);
		inline constexpr auto GetHasOwner = F4SE::CreateVariantId(1'016'277, 2'202'622);
		inline constexpr auto GetInventoryObjectCount = F4SE::CreateVariantId(333'415, 2'200'939);
		inline constexpr auto GetItemCount = F4SE::CreateVariantId(635'042, 2'200'996);
		inline constexpr auto GetLinkedRef = F4SE::CreateVariantId(897'287, 2'202'683);
		inline constexpr auto GetObjectCenter = F4SE::CreateVariantId(777'738, 2'201'092);
		inline constexpr auto GetOwner = F4SE::CreateVariantId(1'323'437, 2'202'616);
		inline constexpr auto GetWeightInContainer = F4SE::CreateVariantId(1'377'567, 2'201'001);
		inline constexpr auto HasContainer = F4SE::CreateVariantId(1'213'017, 2'201'022);
		inline constexpr auto IsAnOwner = F4SE::CreateVariantId(933'798, 2'202'635);
		inline constexpr auto IsCrimeToActivate = F4SE::CreateVariantId(836'011, 2'201'180);
		inline constexpr auto IsDecalRef = F4SE::CreateVariantId(686'485, 2'200'794);
		inline constexpr auto IsLeveledCreature = F4SE::CreateVariantId(1'341'859, 2'202'655);
		inline constexpr auto IsMarker = F4SE::CreateVariantId(364'958, 2'201'157);
		inline constexpr auto MarkAsDeleted = F4SE::CreateVariantId(192'661, 2'201'156);
		inline constexpr auto MoveRefToNewSpace = F4SE::CreateVariantId(629'658, 2'201'149);
		inline constexpr auto RebuildBendableSpline = F4SE::CreateVariantId(340'319, 2'201'119);
		inline constexpr auto SetAngleOnReference = F4SE::CreateVariantId(1'049'748, 2'201'134);
		inline constexpr auto SetLinkedRef = F4SE::CreateVariantId(192'840, 2'202'684);
		inline constexpr auto SetLocationOnReference = F4SE::CreateVariantId(1'101'832, 2'201'138);
		inline constexpr auto SetScale = F4SE::CreateVariantId(817'930, 2'200'893);
		inline constexpr auto SetWantsDelete = F4SE::CreateVariantId(761'346, 2'201'199);
		inline constexpr auto UpdateDynamicNavmesh = F4SE::CreateVariantId(1'518'094, 2'201'206);
		inline constexpr auto UpdateReference3D = F4SE::CreateVariantId(1'568'075, 2'201'071);
	}

	namespace TESObjectREFRTranslationEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(250'283, 2'201'854);
	}

	namespace TESObjectWEAP
	{
		inline constexpr auto GetMeleeAttackSpeed = F4SE::CreateVariantId(817'670, 2'198'957);
		inline constexpr auto GetMeleeAttackSpeedLabel = F4SE::CreateVariantId(178'784, 2'198'959);
		inline constexpr auto GetShotsPerSecond = F4SE::CreateVariantId(752'116, 2'198'956);
	}

	namespace TESOnPCDialogueTargetEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1'473'468, 2'201'855);
	}

	namespace TESOpenCloseEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1'113'930, 2'201'856);
	}

	namespace TESPackageEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(755'003, 2'201'857);
	}

	namespace TESPerkEntryRunEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(395'379, 2'201'858);
	}

	namespace TESPickNewIdleEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(35'951, 2'201'859);
	}

	namespace TESPickpocketFailedEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1'259'305, 2'201'860);
	}

	namespace TESQuest
	{
		inline constexpr auto GetAliasedRef = F4SE::CreateVariantId(847'223, 2'207'810);
		inline constexpr auto SetStage = F4SE::CreateVariantId(952'799, 2'207'743);
	}

	namespace TESQuestInitEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(899'964, 2'201'861);
	}

	namespace TESQuestStageEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(540'905, 2'201'862);
	}

	namespace TESQuestStageItemDoneEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(181'651, 2'201'863);
	}

	namespace TESQuestStartStopEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1'404'315, 2'201'864);
	}

	namespace TESResetEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1'045'137, 2'201'865);
	}

	namespace TESResolveNPCTemplatesEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(686'294, 2'201'866);
	}

	namespace TESResponse
	{
		inline constexpr auto GetResponseText = F4SE::CreateVariantId(992'447, 2'208'288);
		inline constexpr auto GetSpeakerIdle = F4SE::CreateVariantId(606'043, 2'208'293);
	}

	namespace TESSceneActionEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(326'650, 2'201'867);
	}

	namespace TESSceneEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1'549'776, 2'201'868);
	}

	namespace TESScenePhaseEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1'190'467, 2'201'869);
	}

	namespace TESSellEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(831'202, 2'201'870);
	}

	namespace TESSleepStartEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(471'701, 2'201'871);
	}

	namespace TESSleepStopEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(112'659, 2'201'872);
	}

	namespace TESSpellCastEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1'335'446, 2'201'873);
	}

	namespace TESSwitchRaceCompleteEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(976'262, 2'201'874);
	}

	namespace TESTopic
	{
		inline constexpr auto InitDialogueItem = F4SE::CreateVariantId(49'777, 2'208'360);
	}

	namespace TESTopicInfo
	{
		inline constexpr auto GetChallengeLevel = F4SE::CreateVariantId(613'016, 2'208'441);
		inline constexpr auto GetParentInfoGroup = F4SE::CreateVariantId(163'538, 2'208'435);
		inline constexpr auto GetScene = F4SE::CreateVariantId(820'897, 2'208'453);
		inline constexpr auto GetSpeaker = F4SE::CreateVariantId(1'048'628, 2'208'449);
		inline constexpr auto GetSuccessLevel = F4SE::CreateVariantId(1'023'955, 2'208'444);
		inline constexpr auto StartScene = F4SE::CreateVariantId(269'139, 2'208'469);
		inline constexpr auto StartSceneOnEnd = F4SE::CreateVariantId(376'042, 2'208'466);
	}

	namespace TESTopicInfoEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(617'263, 2'201'875);
	}

	namespace TESTrackedStatsEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(257'918, 2'201'876);
	}

	namespace TESTrapHitEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1'481'256, 2'201'877);
	}

	namespace TESTriggerEnterEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1'121'550, 2'201'878);
	}

	namespace TESTriggerEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(762'621, 2'201'879);
	}

	namespace TESTriggerLeaveEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(403'011, 2'201'880);
	}

	namespace TESUniqueIDChangeEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(43'761, 2'201'881);
	}

	namespace TESWaitStartEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1'266'964, 2'201'882);
	}

	namespace TESWaitStopEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(907'679, 2'201'883);
	}

	namespace TESWaterForm
	{
		inline constexpr auto DefaultWater = F4SE::CreateVariantId(289'864, 2'691'845, 4'799'138);
	}

	namespace TESWorldSpace
	{
		inline constexpr auto Load = F4SE::CreateVariantId(701'354, 2'202'844);
		inline constexpr auto LoadPartial = F4SE::CreateVariantId(1'015'763, 2'202'845);
		inline constexpr auto FindInFileFast = F4SE::CreateVariantId(1'116'717, 2'202'851);
		inline constexpr auto PrefetchCellData = F4SE::CreateVariantId(719'753, 2'202'848);
		inline constexpr auto FindCellInFile = F4SE::CreateVariantId(1'012'650, 2'202'847);
		inline constexpr auto GetOffsetData = F4SE::CreateVariantId(1'384'464, 2'202'941);
		inline constexpr auto CreateOffsetData = F4SE::CreateVariantId(320'570, 2'202'942);
		inline constexpr auto FreeOffsetData = F4SE::CreateVariantId(479'563, 2'202'943);
	}

	namespace TaskQueueInterface
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(7'491, 2'698'331);
		inline constexpr auto QueueClosePipboy = F4SE::CreateVariantId(69'886, 2'229'289);
		inline constexpr auto QueueRebuildBendableSpline = F4SE::CreateVariantId(198'419, 2'229'302);
		inline constexpr auto QueueShow1stPerson = F4SE::CreateVariantId(994'377, 2'229'268);
		inline constexpr auto QueueShowPipboy = F4SE::CreateVariantId(1'133'684, 2'229'288);
		inline constexpr auto QueueUpdate3D = F4SE::CreateVariantId(581'890, 2'229'234);
		inline constexpr auto QueueWeaponFire = F4SE::CreateVariantId(15'449, 2'229'186);
		inline constexpr auto TaskUnpackFunc = F4SE::CreateVariantId(1'546'751, 2'229'323);
	}

	namespace TerminalHacked
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(425'579, 2'233'751);
		}
	}

	namespace TerminalMenuItemRunEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(548'625, 2'201'884);
	}

	namespace TravelMarkerStateChange
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(1'129'589, 2'233'752);
		}
	}

	namespace UI
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(548'587, 2'689'028, 4'796'314);
		inline constexpr auto MenuStackLock = F4SE::CreateVariantId(358'824, 2'707'104);
		inline constexpr auto MenuMapLock = F4SE::CreateVariantId(578'487, 2'707'105);
		inline constexpr auto GFxStateChangeLock = F4SE::CreateVariantId(797'969, 2'707'106);
		inline constexpr auto CustomRendererHasQuads = F4SE::CreateVariantId(1'401'451, 2'284'757);
		inline constexpr auto RefreshCursor = F4SE::CreateVariantId(1'436'639, 2'284'772);
		inline constexpr auto UpdateControllerType = F4SE::CreateVariantId(175'796, 2'284'768);
	}

	namespace UIAdvanceMenusFunctionCompleteEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(1'067'039, 2'694'428, 4'801'719);
	}

	namespace UIMessageQueue
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(82'123, 2'689'091, 4'796'377);
	}

	namespace UIUtils
	{
		inline constexpr auto GetComparisonItems = F4SE::CreateVariantId(593'818, 0); // inlined post next-gen
		inline constexpr auto HasRequiredInventoryForCraftingMenu = F4SE::CreateVariantId(639'634, 2'249'717);
		inline constexpr auto PlayMenuSound = F4SE::CreateVariantId(1'227'993, 2'249'707);
		inline constexpr auto PlayPipboySound = F4SE::CreateVariantId(1'320'952, 2'249'706);
		inline constexpr auto ShowCraftingMenu = F4SE::CreateVariantId(877'836, 2'249'718);
		inline constexpr auto UpdateGamepadDependentButtonCodes = F4SE::CreateVariantId(190'238, 2'249'714, 4'483'350);
	}

	namespace VATS
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(570'121, 2'690'444, 4'797'733);
	}

	namespace ViewCasterUpdateEvent
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(1'536'643, 2'694'310, 4'801'601);
	}

	namespace WeaponAttack
	{
		namespace Event
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(1'381'764, 2'233'753);
		}
	}

	namespace WorkbenchMenuBase
	{
		inline constexpr auto UpdateOptimizedAutoBuildInv = F4SE::CreateVariantId(769'581, 2'224'955);
	}

	namespace Workshop
	{
		inline constexpr auto FindNearestValidWorkshop = F4SE::CreateVariantId(905'705, 2'194'970);
		inline constexpr auto FreeBuild = F4SE::CreateVariantId(1'583'365, 2'194'924);
		inline constexpr auto GetSelectedWorkshopMenuNode = F4SE::CreateVariantId(763'948, 2'195'024);
		inline constexpr auto InitializePlacementReference =
			F4SE::CreateVariantId(1'577'199, 0); // inlined post next-gen
		inline constexpr auto IsLocationWithinBuildableArea = F4SE::CreateVariantId(990'965, 2'194'956);
		inline constexpr auto IsWorkshopItem = F4SE::CreateVariantId(1'386'903, 2'194'912);
		inline constexpr auto PlaceCurrentReference = F4SE::CreateVariantId(1'058'211, 2'195'155);
		inline constexpr auto RequestExitWorkshop = F4SE::CreateVariantId(209'891, 2'195'135);
		inline constexpr auto ScrapReference = F4SE::CreateVariantId(636'327, 2'195'125);
		inline constexpr auto SetSelectedEditItem = F4SE::CreateVariantId(2'562, 2'195'119);
		inline constexpr auto StartWorkshop = F4SE::CreateVariantId(171'771, 2'195'134);
		inline constexpr auto ToggleEditMode = F4SE::CreateVariantId(1'243'386, 2'195'130);
		inline constexpr auto UpdateActiveEdit = F4SE::CreateVariantId(69'261, 2'195'210);
		inline constexpr auto WorkshopCanShowRecipe = F4SE::CreateVariantId(239'190, 2'194'978);
		inline constexpr auto CurrentPlacementItemData = F4SE::CreateVariantId(1'279'207, 2'689'973, 4'797'261);
		inline constexpr auto CurrentRow = F4SE::CreateVariantId(833'923, 2'689'868, 4'797'160);
		inline constexpr auto PlacementItem = F4SE::CreateVariantId(526'727, 2'689'906, 4'797'235);

		namespace BuildableAreaEvent
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(922'238, 2'195'285);
		}

		namespace ItemDestroyedEvent
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(563'220, 2'195'286);
		}

		namespace ItemGrabbedEvent
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(203'989, 2'195'287);
		}

		namespace ItemMovedEvent
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(1'426'604, 2'195'288);
		}

		namespace ItemPlacedEvent
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(1'067'439, 2'195'289);
		}

		namespace ItemRepairedEvent
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(708'832, 2'195'290);
		}

		namespace ItemScrappedEvent
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(348'916, 2'195'291);
		}

		namespace PlacementItemData
		{
			inline constexpr auto Set = F4SE::CreateVariantId(1'460'935, 2'195'643);
		}

		namespace PlacementStatusEvent
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(1'213'076, 2'195'293);
		}

		namespace PowerOffEvent
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(853'526, 2'195'294);
		}

		namespace PowerOnEvent
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(494'172, 2'195'295);
		}

		namespace WorkshopMenuNode
		{
			inline constexpr auto FindAndSetSelectedNode = F4SE::CreateVariantId(1'309'368, 2'195'022);
		}

		namespace WorkshopModeEvent
		{
			inline constexpr auto GetEventSource = F4SE::CreateVariantId(135'059, 2'195'296);
		}
	}

	namespace WorkshopMenu
	{
		inline constexpr auto CheckAndSetItemForPlacement = F4SE::CreateVariantId(1'541'862, 2'224'991);
		inline constexpr auto UpdateButtonText = F4SE::CreateVariantId(1'089'189, 2'224'992);
	}

	namespace WorkshopNPCTransferEvent
	{
		inline constexpr auto GetEventSource = F4SE::CreateVariantId(189'426, 2'201'885);
	}

	namespace bhkCharacterController
	{
		inline constexpr auto Jump = F4SE::CreateVariantId(1'067'306, 2'278'191);
	}

	namespace bhkNPCollisionObject
	{
		inline constexpr auto CreateObject = F4SE::CreateVariantId(1'264'820, 2'277'912);
		inline constexpr auto CopyMembers = F4SE::CreateVariantId(1'558'409, 2'277'907);
		inline constexpr auto GetBody = F4SE::CreateVariantId(1'127'049, 2'277'926);
		inline constexpr auto GetBodyId = F4SE::CreateVariantId(1'286'222, 2'277'928);
		inline constexpr auto GetShape = F4SE::CreateVariantId(315'427, 2'277'929);
		inline constexpr auto GetTransform = F4SE::CreateVariantId(1'508'189, 2'277'944);
		inline constexpr auto Getbhk = F4SE::CreateVariantId(730'034, 2'277'919);
		inline constexpr auto SetMotionType = F4SE::CreateVariantId(200'912, 2'277'913);
		inline constexpr auto SetTransform = F4SE::CreateVariantId(178'085, 2'277'945);
	}

	namespace bhkPhysicsSystem
	{
		inline constexpr auto ctor = F4SE::CreateVariantId(1'338'184, 2'278'008);
		inline constexpr auto AddToWorld = F4SE::CreateVariantId(512'878, 2'278'019);
		inline constexpr auto CopyMembers = F4SE::CreateVariantId(301'764, 2'278'007);
	}

	namespace bhkPickData
	{
		inline constexpr auto ctor = F4SE::CreateVariantId(526'783, 2'230'668);
		inline constexpr auto GetAllCollectorRayHitAt = F4SE::CreateVariantId(583'997, 2'277'766);
		inline constexpr auto GetAllCollectorRayHitSize = F4SE::CreateVariantId(1'288'513, 2'277'765);
		inline constexpr auto GetBody = F4SE::CreateVariantId(1'223'055, 2'277'762);
		inline constexpr auto GetHitFraction = F4SE::CreateVariantId(476'687, 2'277'771);
		inline constexpr auto GetNiAVObject = F4SE::CreateVariantId(863'406, 2'277'763);
		inline constexpr auto HasHit = F4SE::CreateVariantId(1'181'584, 2'277'770);
		inline constexpr auto Reset = F4SE::CreateVariantId(438'299, 2'277'761);
		inline constexpr auto SetStartEnd = F4SE::CreateVariantId(747'470, 2'236'622);
		inline constexpr auto SortAllCollectorHits = F4SE::CreateVariantId(1'274'842, 2'277'767);
	}

	namespace bhkUtilFunctions
	{
		inline constexpr auto FindFirstCollisionObject = F4SE::CreateVariantId(507'243, 2'278'093);
		inline constexpr auto GetAVObjectFromBodyID = F4SE::CreateVariantId(962'716, 2'278'085);
	}

	namespace bhkWorld
	{
		inline constexpr auto Activate = F4SE::CreateVariantId(1'207'639, 2'277'728);
		inline constexpr auto AddObjects = F4SE::CreateVariantId(585'426, 2'277'719);
		inline constexpr auto AddPhysicsSystem = F4SE::CreateVariantId(82'382, 2'277'752);
		inline constexpr auto IsBodyAdded = F4SE::CreateVariantId(1'062'018, 2'277'997);
		inline constexpr auto Enable = F4SE::CreateVariantId(343'580, 2'277'725);
		inline constexpr auto EnableCollision = F4SE::CreateVariantId(50'037, 2'277'730);
		inline constexpr auto IsActive = F4SE::CreateVariantId(848'114, 2'277'729);
		inline constexpr auto RemoveObjects = F4SE::CreateVariantId(1'514'984, 2'277'721);
		inline constexpr auto RemovePhysicsSystem = F4SE::CreateVariantId(1'039'226, 2'277'753);
		inline constexpr auto SetCollisionGroup = F4SE::CreateVariantId(717'116, 2'277'722);
		inline constexpr auto SetDismemberedLimb = F4SE::CreateVariantId(1'566'977, 2'277'726);
		inline constexpr auto SetMotion = F4SE::CreateVariantId(357'289, 2'277'723);
	}

	namespace hkContainerDebugAllocator
	{
		inline constexpr auto Allocator = F4SE::CreateVariantId(629'588, 2'665'427);
	}

	namespace hkContainerHeapAllocator
	{
		inline constexpr auto Allocator = F4SE::CreateVariantId(409'811, 2'665'426);
	}

	namespace hkContainerTempAllocator
	{
		inline constexpr auto Allocator = F4SE::CreateVariantId(190'918, 2'665'425);
	}

	namespace hkHardwareInfo
	{
		inline constexpr auto CalcNumHardwareThreads = F4SE::CreateVariantId(1'392'261, 2'260'765);
	}

	namespace hkMemoryRouter
	{
		inline constexpr auto ThreadLocalIndex = F4SE::CreateVariantId(878'080, 2'787'927);
	}

	namespace hkMonitorStream
	{
		inline constexpr auto ThreadLocalIndex = F4SE::CreateVariantId(1'467'653, 2'702'743);
		inline constexpr auto Clear = F4SE::CreateVariantId(667'853, 2'257'312);
		inline constexpr auto Resize = F4SE::CreateVariantId(854'140, 2'257'310);
	}

	namespace hkProcessFactory
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(111'134, 2'702'978);
		inline constexpr auto CreateProcess = F4SE::CreateVariantId(1'489'919, 2'263'377);
	}

	namespace hkReferencedObject
	{
		inline constexpr auto AddReference = F4SE::CreateVariantId(866'015, 2'259'213);
		inline constexpr auto RemoveReference = F4SE::CreateVariantId(1'379'897, 2'195'747);
	}

	namespace hkVisualDebugger
	{
		inline constexpr auto ctor = F4SE::CreateVariantId(1'503'084, 2'263'295);
		inline constexpr auto AddContext = F4SE::CreateVariantId(136'058, 2'263'313);
		inline constexpr auto AddDefaultProcess = F4SE::CreateVariantId(926'323, 2'263'302);
		inline constexpr auto Serve = F4SE::CreateVariantId(1'036'317, 2'263'296);
		inline constexpr auto Shutdown = F4SE::CreateVariantId(156'043, 2'263'300);
	}

	namespace hkVtableClassRegistry
	{
		inline constexpr auto Singleton = F4SE::CreateVariantId(1'281'220, 2'702'926);
	}

	namespace hknpBSWorld
	{
		inline constexpr auto AccessMotion = F4SE::CreateVariantId(979'298, 2'277'680);
		inline constexpr auto ActivateBody = F4SE::CreateVariantId(1'259'285, 2'277'677);
		inline constexpr auto SetBodyAngularVelocity = F4SE::CreateVariantId(1'020'581, 2'277'672);
		inline constexpr auto SetBodyKeyframed = F4SE::CreateVariantId(527'037, 2'277'684);
		inline constexpr auto SetBodyLinearVelocity = F4SE::CreateVariantId(1'552'859, 2'277'671);
		inline constexpr auto SetBodyStatic = F4SE::CreateVariantId(1'058'828, 2'277'683);
		inline constexpr auto SetBodyVelocity = F4SE::CreateVariantId(1'300'379, 2'277'670);
	}

	namespace hknpBodyCinfo
	{
		inline constexpr auto ctor = F4SE::CreateVariantId(718'403, 2'255'967);
	}

	namespace hknpCapsuleShape
	{
		inline constexpr auto CreateCapsuleShape = F4SE::CreateVariantId(1'316'723, 2'257'207);
		inline constexpr auto Init = F4SE::CreateVariantId(647'475, 2'257'217);
	}

	namespace hknpConvexPolytopeShape
	{
		inline constexpr auto CreateFromVerticesInternal = F4SE::CreateVariantId(720'930, 2'257'201);
	}

	namespace hknpConvexShape
	{
		inline constexpr auto CreateFromAabb = F4SE::CreateVariantId(1'144'958, 2'257'125);
		inline constexpr auto CreateFromCylinder = F4SE::CreateVariantId(39'591, 2'257'126);
		inline constexpr auto CreateFromHalfExtents = F4SE::CreateVariantId(972'150, 2'257'124);
		inline constexpr auto CreateFromIndexedVertices = F4SE::CreateVariantId(308'779, 2'257'123);
		inline constexpr auto CreateFromVertices = F4SE::CreateVariantId(1'389'383, 2'257'122);
	}

	namespace hknpMotionCinfo
	{
		inline constexpr auto ctor = F4SE::CreateVariantId(1'248'706, 2'258'369);
		inline constexpr auto InitializeAsKeyFramed = F4SE::CreateVariantId(1'204'390, 2'258'373);
	}

	namespace hknpPhysicsSystem
	{
		inline constexpr auto AddToWorld = F4SE::CreateVariantId(189'542, 2'255'984);
		inline constexpr auto RemoveFromWorld = F4SE::CreateVariantId(773'481, 2'255'985);
	}

	namespace hknpSphereShape
	{
		inline constexpr auto CreateSphereShape = F4SE::CreateVariantId(1'116'388, 2'256'377);
	}

	namespace hknpTriangleShape
	{
		inline constexpr auto CreateEmptyTriangleShape = F4SE::CreateVariantId(1'355'865, 2'256'226);
		inline constexpr auto SetVertices = F4SE::CreateVariantId(1'435'439, 2'256'228);
	}

	namespace hknpWorld
	{
		inline constexpr auto AddBodies = F4SE::CreateVariantId(1'454'855, 2'255'681);
		inline constexpr auto CreateBody = F4SE::CreateVariantId(72'830, 2'255'680);
		inline constexpr auto CreateMotion = F4SE::CreateVariantId(1'574'333, 2'255'688);
		inline constexpr auto DisableBodyFlags = F4SE::CreateVariantId(1'506'647, 2'255'636);
		inline constexpr auto EnableBodyFlags = F4SE::CreateVariantId(987'833, 2'255'635);
		inline constexpr auto GetActionManager = F4SE::CreateVariantId(1'548'356, 2'255'709);
		inline constexpr auto SetBodyCollisionFilterInfo = F4SE::CreateVariantId(1'114'792, 2'255'626);
		inline constexpr auto SetBodyMotion = F4SE::CreateVariantId(618'186, 2'255'634);
	}

	namespace msvc
	{
		namespace type_info
		{
			inline constexpr auto name = F4SE::CreateVariantId(1'419'793, 2'729'709, 4'823'662);
			inline constexpr auto compare = F4SE::CreateVariantId(0, 2'729'710, 4'823'660); // post next-gen only
			inline constexpr auto equal = F4SE::CreateVariantId(808'703, 0);				// pre next-gen only
			inline constexpr auto root_node = F4SE::CreateVariantId(161'235, 2'713'441);
		}
	}

	namespace nsStatsMenuUtils
	{
		inline constexpr auto GetEffectDisplayInfo = F4SE::CreateVariantId(294'691, 2'224'586);
	}
}

namespace Scaleform::ID
{
	namespace GFx
	{
		namespace ASStringManager
		{
			inline constexpr auto CreateStringNode = F4SE::CreateVariantId(419'974, 2'290'014);
		}

		namespace Loader
		{
			inline constexpr auto CreateMovie = F4SE::CreateVariantId(912'291, 2'284'723);
		}

		namespace Movie
		{
			inline constexpr auto Release = F4SE::CreateVariantId(404'814, 2'287'230);
		}

		namespace Value
		{
			inline constexpr auto ObjectAddRef = F4SE::CreateVariantId(244'786, 2'286'228);
			inline constexpr auto ObjectRelease = F4SE::CreateVariantId(856'221, 2'286'229);
			inline constexpr auto IsInstanceOf = F4SE::CreateVariantId(616'029, 2'286'137);
			inline constexpr auto GetParent = F4SE::CreateVariantId(227'189, 2'285'968);
			inline constexpr auto HasMember = F4SE::CreateVariantId(788'691, 2'286'078);
			inline constexpr auto GetMember = F4SE::CreateVariantId(1'517'430, 2'285'936, 4'494'126);
			inline constexpr auto SetMember = F4SE::CreateVariantId(1'360'149, 2'286'589);
			inline constexpr auto DeleteMember = F4SE::CreateVariantId(1'397'711, 2'285'595);
			inline constexpr auto VisitMembers = F4SE::CreateVariantId(1'276'961, 2'286'786);
			inline constexpr auto GetArraySize = F4SE::CreateVariantId(254'218, 2'285'791);
			inline constexpr auto SetArraySize = F4SE::CreateVariantId(1'479'924, 2'286'563);
			inline constexpr auto GetElement = F4SE::CreateVariantId(827'659, 2'285'881);
			inline constexpr auto SetElement = F4SE::CreateVariantId(433'707, 2'286'575);
			inline constexpr auto PushBack = F4SE::CreateVariantId(1'330'475, 2'286'424);
			inline constexpr auto PopBack = F4SE::CreateVariantId(13'718, 2'286'392);
			inline constexpr auto RemoveElements = F4SE::CreateVariantId(1'286'586, 2'286'475);
			inline constexpr auto VisitElements = F4SE::CreateVariantId(851'872, 2'286'785);
			inline constexpr auto GetDisplayInfo = F4SE::CreateVariantId(498'814, 2'285'873);
			inline constexpr auto SetDisplayInfo = F4SE::CreateVariantId(146'578, 2'286'572);
			inline constexpr auto GetDisplayMatrix = F4SE::CreateVariantId(1'494'470, 2'285'874);
			inline constexpr auto SetDisplayMatrix = F4SE::CreateVariantId(22'308, 2'286'573);
			inline constexpr auto GetCxform = F4SE::CreateVariantId(307'708, 2'285'854);
			inline constexpr auto SetCxform = F4SE::CreateVariantId(692'629, 2'286'570);
			inline constexpr auto AttachMovie = F4SE::CreateVariantId(373'078, 2'285'650);
			inline constexpr auto CreateEmptyMovieClip = F4SE::CreateVariantId(1'579'893, 2'285'573);
			inline constexpr auto GotoAndPlay_Int = F4SE::CreateVariantId(166'362, 2'286'057);
			inline constexpr auto GotoAndPlay_String = F4SE::CreateVariantId(1'562'220, 2'286'058);
			inline constexpr auto Invoke = F4SE::CreateVariantId(655'847, 2'286'101);
		}
	}

	namespace Memory
	{
		inline constexpr auto Heap = F4SE::CreateVariantId(939'898, 2'707'353);
	}
}

// NOLINTEND(modernize-concat-nested-namespaces)
