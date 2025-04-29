#ifndef MACRO_CONFIG_INT
#error "The config macros must be defined"
#define MACRO_CONFIG_INT(Name, ScriptName, Def, Min, Max, Save, Desc) ;
#define MACRO_CONFIG_COL(Name, ScriptName, Def, Save, Desc) ;
#define MACRO_CONFIG_STR(Name, ScriptName, Len, Def, Save, Desc) ;
#endif


// FeX General
MACRO_CONFIG_INT(ClShowFrozenText, fx_frozen_tees_text, 0, 0, 2, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Show how many tees in your team are currently frozen. (0 - off, 1 - show alive, 2 - show frozen)")
MACRO_CONFIG_INT(ClShowFrozenHud, fx_frozen_tees_hud, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Show frozen tee HUD")
MACRO_CONFIG_INT(ClShowFrozenHudSkins, fx_frozen_tees_hud_skins, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Use ninja skin, or darkened skin for frozen tees on hud")

MACRO_CONFIG_INT(ClFrozenHudTeeSize, fx_frozen_tees_size, 15, 8, 20, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Size of tees in frozen tee hud. (Default : 15)")
MACRO_CONFIG_INT(ClFrozenMaxRows, fx_frozen_tees_max_rows, 1, 1, 6, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Maximum number of rows in frozen tee HUD display")
MACRO_CONFIG_INT(ClFrozenHudTeamOnly, fx_frozen_tees_only_inteam, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Only render frozen tee HUD display while in team")

MACRO_CONFIG_INT(ClSpecmenuID, fx_spec_menu_ID, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Shows player IDs in spectate menu")

MACRO_CONFIG_INT(ClLimitMouseToScreen, fx_limit_mouse_to_screen, 0, 0, 2, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Limit mouse to screen boundries")
MACRO_CONFIG_INT(ClScaleMouseDistance, fx_scale_mouse_distance, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Improve mouse precision by scaling max distance to 1000")

MACRO_CONFIG_INT(ClHammerRotatesWithCursor, fx_hammer_rotates_with_cursor, 0, 0, 2, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Allow your hammer to rotate like other weapons")

// FeX Freeze Kill

MACRO_CONFIG_INT(ClFreezeKill, fx_freeze_kill, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Kill if Frozen")
MACRO_CONFIG_INT(ClFreezeKillGrounded, fx_freeze_kill_grounded, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Kill if Frozen")
MACRO_CONFIG_INT(ClFreezeKillIgnoreKillProt, fx_freeze_kill_ignore_kill_prot, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Kill if Frozen")
MACRO_CONFIG_INT(ClFreezeKillMultOnly, fx_freeze_kill_mult_only, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Only Freeze Kills if Current Map is Multeasymap")
MACRO_CONFIG_INT(ClFreezeKillOnlyFullFrozen, fx_freeze_kill_full_frozen, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Only Starts Timer When Full Frozen")
MACRO_CONFIG_INT(ClFreezeKillWaitMs, fx_freeze_kill_wait_ms, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Wait a Certain amount of time while frozen until you kill")
MACRO_CONFIG_INT(ClFreezeKillMs, fx_freeze_kill_ms, 1000, 0, 10000, CFGFLAG_CLIENT | CFGFLAG_SAVE, "time to wait before you kill")
MACRO_CONFIG_INT(ClFreezeDontKillMoving, fx_freeze_dont_kill_moving, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Moving no kill you")

MACRO_CONFIG_COL(ClFreezeKillColorCol, fx_freeze_kill_color_col, 255, CFGFLAG_CLIENT | CFGFLAG_SAVE, "freeze kill bar color")
MACRO_CONFIG_INT(ClFreezeKillColor, fx_freeze_kill_color, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Toggles wether or not you can change the color")
MACRO_CONFIG_INT(ClFreezeKillColorY, fx_freeze_kill_color_y, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "yes i need for reazon")

MACRO_CONFIG_INT(ClFreezeKillDebug, fx_freeze_kill_debug, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "debug")

// Auto join stuff
MACRO_CONFIG_INT(ClAutoJoinTeam, fx_autojoin_team, 0, 1, 63, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Auto join this team when joining server")
MACRO_CONFIG_INT(ClAutoJoinTeamDelay, fx, 2, 0, 20, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Delay in seconds before auto joining team")
MACRO_CONFIG_INT(ClAutoJoinTeamLock, fx_autojoin_team_lock, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Lock to team after auto joining")

MACRO_CONFIG_INT(ClAutoJoinDummy, fx_autojoin_dummy, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Auto join with dummy when someone leaves")
MACRO_CONFIG_INT(ClAutoJoinDummyDelay, fx_autojoin_dummy_delay, 2, 0, 20, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Delay in seconds before auto joining with dummy")
MACRO_CONFIG_INT(ClAutoJoinDummySwitch, fx_autojoin_dummy_switch, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Switch back to player after dummy joins")

// Fast input FeX and
// Anti Latency Tools
MACRO_CONFIG_INT(ClFreezeUpdateFix, fx_freeze_update_fix, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Will change your skin faster when you enter freeze. ")
MACRO_CONFIG_INT(ClRemoveAnti, fx_remove_anti, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Removes some amount of antiping & player prediction in freeze")
MACRO_CONFIG_INT(ClUnfreezeLagTicks, fx_remove_anti_ticks, 5, 0, 20, CFGFLAG_CLIENT | CFGFLAG_SAVE, "The biggest amount of prediction ticks that are removed")
MACRO_CONFIG_INT(ClUnfreezeLagDelayTicks, fx_remove_anti_delay_ticks, 25, 5, 150, CFGFLAG_CLIENT | CFGFLAG_SAVE, "How many ticks it takes to remove the maximum prediction after being frozen")

MACRO_CONFIG_INT(ClUnpredOthersInFreeze, fx_unpred_others_in_freeze, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Dont predict other players if you are frozen")
MACRO_CONFIG_INT(ClPredMarginInFreeze, fx_pred_margin_in_freeze, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "enable changing prediction margin while frozen")
MACRO_CONFIG_INT(ClPredMarginInFreezeAmount, fx_pred_margin_in_freeze_amount, 15, 0, 2000, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Set what your prediction margin while frozen should be")

MACRO_CONFIG_INT(ClShowOthersGhosts, fx_show_others_ghosts, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Show ghosts for other players in their unpredicted position")
MACRO_CONFIG_INT(ClSwapGhosts, fx_swap_ghosts, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Show predicted players as ghost and normal players as unpredicted")
MACRO_CONFIG_INT(ClHideFrozenGhosts, fx_hide_frozen_ghosts, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Hide Ghosts of other players if they are frozen")

MACRO_CONFIG_INT(ClPredGhostsAlpha, fx_pred_ghosts_alpha, 100, 0, 100, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Alpha of predicted ghosts (0-100)")
MACRO_CONFIG_INT(ClUnpredGhostsAlpha, fx_unpred_ghosts_alpha, 50, 0, 100, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Alpha of unpredicted ghosts (0-100)")
MACRO_CONFIG_INT(ClRenderGhostAsCircle, fx_render_ghost_as_circle, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Render Ghosts as circles instead of tee")

MACRO_CONFIG_INT(ClFastInput, fx_fast_input, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Toggles fast input settings for up to (20ms) better input")
MACRO_CONFIG_INT(ClFastInputOthers, fx_fast_input_others, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Do an extra 1 tick (20ms) for other tees with your fast inputs. (increases visual latency, makes dragging easier)")

MACRO_CONFIG_INT(ClAntiPingImproved, fx_antiping_improved, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Different antiping smoothing algorithm, not compatible with cl_antiping_smooth")
MACRO_CONFIG_INT(ClAntiPingNegativeBuffer, fx_antiping_negative_buffer, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Helps in Gores. Allows internal certainty value to be negative which causes more conservative prediction")
MACRO_CONFIG_INT(ClAntiPingStableDirection, fx_antiping_stable_direction, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Predicts optimistically along the tees stable axis to reduce delay in gaining overall stability")
MACRO_CONFIG_INT(ClAntiPingUncertaintyScale, fx_antiping_uncertainty_scale, 150, 25, 400, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Determines uncertainty duration as a factor of ping, 100 = 1.0")

// Auto Reply

MACRO_CONFIG_STR(ClAutoReplyMsgTabbed, fx_auto_reply_msg_tabbed, 255, "I'm currently tabbed out", CFGFLAG_CLIENT | CFGFLAG_SAVE, "Message to reply when pinged in chat and tabbed out and fx_auto_reply is set to 1")
MACRO_CONFIG_INT(ClAutoReplyTabbedOut, fx_auto_reply_tabbed_out, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Let others know when pinged in chat that you are tabbed out")
MACRO_CONFIG_STR(ClAutoReplyMsgPinged, fx_auto_reply_msg_pinged, 255, "", CFGFLAG_CLIENT | CFGFLAG_SAVE, "Reply to players who pinged you")
MACRO_CONFIG_INT(ClAutoReplyPinged, fx_auto_reply_pinged, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Message to reply when pinged in chat and fx_auto_reply is set to 1")

// FeX Skin Profiles(TATER MY WALLAH)

MACRO_CONFIG_INT(ClApplyProfileSkin, fx_profile_skin, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Apply skin in profiles")
MACRO_CONFIG_INT(ClApplyProfileName, fx_profile_name, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Apply name in profiles")
MACRO_CONFIG_INT(ClApplyProfileClan, fx_profile_clan, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Apply clan in profiles")
MACRO_CONFIG_INT(ClApplyProfileFlag, fx_profile_flag, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Apply flag in profiles")
MACRO_CONFIG_INT(ClApplyProfileColors, fx_profile_colors, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Apply colors in profiles")
MACRO_CONFIG_INT(ClApplyProfileEmote, fx_profile_emote, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Apply emote in profiles")

// Custom Font

MACRO_CONFIG_STR(ClCustomFont, fx_custom_font, 255, "DejaVu Sans", CFGFLAG_CLIENT | CFGFLAG_SAVE, "Custom font face")

// Aidob Warlist

MACRO_CONFIG_INT(ClWarList, fx_warlist, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Toggles war list visuals")
MACRO_CONFIG_INT(ClWarListShowClan, fx_warlist_show_clan_if_war, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Show clan in nameplate if there is a war")
MACRO_CONFIG_INT(ClWarListReason, fx_warlist_reason, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Show war reason")
MACRO_CONFIG_INT(ClWarListChat, fx_warlist_chat, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Show war colors in chat")
MACRO_CONFIG_INT(ClWarlistPrefixes, fx_Warlist_Prefixes, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Toggles Warlist Prefix")
MACRO_CONFIG_INT(ClWarListScoreboard, fx_warlist_scoreboard, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Show war colors in scoreboard")
MACRO_CONFIG_INT(ClWarListAllowDuplicates, fx_warlist_allow_duplicates, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Allow duplicate war entries")

MACRO_CONFIG_INT(ClWarListIndicator, fx_warlist_indicator, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Use warlist for indicator")
MACRO_CONFIG_INT(ClWarListIndicatorAll, fx_warlist_indicator_all, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Show all groups")
MACRO_CONFIG_INT(ClWarListIndicatorEnemy, fx_warlist_indicator_enemy, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Show players from the first group")
MACRO_CONFIG_INT(ClWarListIndicatorTeam, fx_warlist_indicator_team, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Show players from second group")

// Bindchat

MACRO_CONFIG_INT(ClSendExclamation, fx_send_exclamation_mark, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Send chat messages that begin with the prefix \"!\"")

// Aidob Mutes

MACRO_CONFIG_INT(ClReplyMuted, fx_reply_muted, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "replies to muted players if they ping you")
MACRO_CONFIG_INT(ClShowMutedInConsole, fx_show_muted_in_console, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Shows messages of muted people in the console")
MACRO_CONFIG_INT(ClMutedIcon, fx_muted_icon, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Shows an Icon Next to Nameplates of Muted Players")
MACRO_CONFIG_INT(ClHideEnemyChat, fx_hide_enemy_chat, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Hides Chat Messages of Enemies")
MACRO_CONFIG_STR(ClAutoReplyMutedMsg, fx_auto_reply_muted_msg, 255, "I can't see your messages, you're muted", CFGFLAG_CLIENT | CFGFLAG_SAVE, "Message to reply with then a muted player pings you")
MACRO_CONFIG_COL(ClMutedColor, fx_muted_color, 12792139, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Muted Icon Color")
MACRO_CONFIG_INT(ClAutoReplyMuted, fx_auto_reply_muted, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Message to reply with then a muted player pings you")

// something

MACRO_CONFIG_COL(ClFXMessageColor, fx_message_color, 9633471, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Client message color of warlist cmds")
MACRO_CONFIG_INT(ClMutedConsoleColor, fx_muted_console_color, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "colors in console for warlist")

// FeX Chat Prefix

MACRO_CONFIG_STR(ClClientPrefix, fx_client_prefix, 8, "— ", CFGFLAG_CLIENT | CFGFLAG_SAVE, "Client (Echo) Message Prefix")
MACRO_CONFIG_STR(ClServerPrefix, fx_server_prefix, 8, "*** ", CFGFLAG_CLIENT | CFGFLAG_SAVE, "Server Message Prefix")
MACRO_CONFIG_STR(ClWarlistPrefix, fx_warlist_prefix, 8, "♦ ", CFGFLAG_CLIENT | CFGFLAG_SAVE, "Warlist Prefix")
MACRO_CONFIG_STR(ClFriendPrefix, fx_friend_prefix, 8, "♥ ", CFGFLAG_CLIENT | CFGFLAG_SAVE, "Friend Prefix (alt + num3 = ♥)")
MACRO_CONFIG_STR(ClSpecPrefix, fx_spec_prefix, 8, "• ", CFGFLAG_CLIENT | CFGFLAG_SAVE, "Spectating Prefix (alt + num7 = •)")

// Prefix toggles
MACRO_CONFIG_INT(ClSpectatePrefix, fx_chat_spectate_prefix, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Toggles Spectator Prefix Next to Names")
MACRO_CONFIG_INT(ClChatServerPrefix, fx_do_chat_server_prefix, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Toggles Server Prefix")
MACRO_CONFIG_INT(ClChatClientPrefix, fx_do_chat_client_prefix, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Toggles Client Prefix")

// FeX Friend name settings
MACRO_CONFIG_INT(ClDoFriendColors, fx_do_friend_colors, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Toggles Friend name colors")
MACRO_CONFIG_COL(ClFriendColor, fx_friend_color, 14745554, CFGFLAG_CLIENT | CFGFLAG_SAVE, "friend name color")

// FeX spectate color
MACRO_CONFIG_COL(ClSpecColor, fx_spec_color, 8936607, CFGFLAG_CLIENT | CFGFLAG_SAVE, "• color in scoreboard")

// Silent Messages
MACRO_CONFIG_INT(ClSilentMessages, fx_silent_messages, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "When sending a Silent Message to the chat it will still show what you typed")

// Chat Detection
MACRO_CONFIG_INT(ClDismissAdBots, fx_dismiss_adbots, 1, 0, 3, CFGFLAG_CLIENT | CFGFLAG_SAVE, "If an AdBot messages you it | 1 = hides their message | 2 = Info and Vote Kick Option | 3 = Info and Auto Vote Kick")

MACRO_CONFIG_INT(ClAutoAddOnNameChange, fx_auto_add_on_name_change, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Automatically adds a player back to a list if their name changed")

// 1v1 Mode FeX

MACRO_CONFIG_INT(Cl1v1ModeScoreLimit, fx_1v1mode_score_limit, 10, 1, 50, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Score limit for 1v1 mode") 
MACRO_CONFIG_INT(Cl1v1ModeShowHud, fx_1v1mode_show_hud, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Show 1v1 mode HUD")
MACRO_CONFIG_STR(Cl1v1ModeEnemyName, fx_1v1mode_enemy_name, 18, "", CFGFLAG_CLIENT, "Name of enemy in 1v1 mode")
MACRO_CONFIG_INT(Cl1v1ModeKillLock, fx_1v1mode_kill_lock, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Locks kill bind")
MACRO_CONFIG_INT(Cl1v1ModeEcho, fx_1v1mode_echo, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Toggles echo after counting or drawing for 1v1")

MACRO_CONFIG_COL(Cl1v1ModeTextColor, fx_1v1mode_text_color, 255, CFGFLAG_CLIENT | CFGFLAG_SAVE, "1v1 hud text color")
MACRO_CONFIG_INT(Cl1v1ModeHudColor, fx_1v1mode_color, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Toggles custom color")

MACRO_CONFIG_INT(Cl1v1ModeCustom, fx_1v1mode_custom, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Toggles custom message for 1v1")
MACRO_CONFIG_STR(Cl1v1ModeCustomMsg, fx_1v1mode_custom_msg, 128, "%s %d | %d %s", CFGFLAG_CLIENT | CFGFLAG_SAVE, "usage: %|s %|d | %|d %|s, remove the | by % but in the middle you can leave")


// FeX Clone
MACRO_CONFIG_INT(ClAlreadyCloned, zzzzzzjwebgfuwhbfuewhuif______, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "DO NOT TOUCH!")

//------------------------
// FeX Visual
//------------------------
MACRO_CONFIG_INT(ClVisualSpeed, fx_visual_speed, 100, 1, 5000, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Adjust speed of the visual speed")
MACRO_CONFIG_INT(ClVisualModeT, fx_visual_modeT, 1, 1, 4, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Visual[Tee] mode (1: rainbow, 2: pulse, 3: custom color, 4: random)")
MACRO_CONFIG_INT(ClVisualModeW, fx_visual_modeW, 1, 1, 4, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Visual[Weapon] mode (1: rainbow, 2: pulse, 3: custom color, 4: random)")
MACRO_CONFIG_INT(ClVisualModeH, fx_visual_modeH, 1, 1, 4, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Visual[Hook] mode (1: rainbow, 2: pulse, 3: custom color, 4: random)")
MACRO_CONFIG_INT(ClVisualModeC, fx_visual_modeC, 1, 1, 4, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Visual[Cursor] mode (1: rainbow, 2: pulse, 3: custom color, 4: random)")
MACRO_CONFIG_INT(ClVisual, fx_visual, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Turn on visual mode Client Side")
//------------------------
// FeX Visual Hook
//------------------------
MACRO_CONFIG_INT(ClVisualHookOthers, fx_visual_hook_others, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Turn on visual hook for others client side")
MACRO_CONFIG_INT(ClVisualHook, fx_visual_hook, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Turn on visual hook client side")
//------------------------
// FeX Visual Tees
//------------------------
MACRO_CONFIG_INT(ClVisualTeesOthers, fx_visual_player_others, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Turn on visual player client side for others")
MACRO_CONFIG_INT(ClVisualTees, fx_visual_player, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Turn on visual mode for player Client Side")
//------------------------
// FeX Visual Weapon
//------------------------
MACRO_CONFIG_INT(ClVisualWeapon, fx_visual_weapon, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Turn on visual mode for weapons Client Side")
MACRO_CONFIG_INT(ClVisualWeaponOthers, fx_visual_weapon_others, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Turn on visual weapon client side for others")
//------------------------
// FeX Visual Cursor
//------------------------
MACRO_CONFIG_INT(ClVisualCursor, fx_visual_cursor, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Turn on visual mode for cursor Client side")
MACRO_CONFIG_INT(ClVisualCursorSpec, fx_visual_cursor_spec, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Turn on visual mode for spectating others cursor Client side")
//------------------------
// FeX Visual Custom Colors
//------------------------
MACRO_CONFIG_COL(ClVisualCusColor1, fx_visual_cus_col_1, 000, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Visual Colors = Weapon")
MACRO_CONFIG_COL(ClVisualCusColor2, fx_visual_cus_col_2, 000, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Visual Colors = Hook")
MACRO_CONFIG_COL(ClVisualCusColor3, fx_visual_cus_col_3, 000, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Visual Colors = Tee")
MACRO_CONFIG_COL(ClVisualCusColor4, fx_visual_cus_col_4, 000, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Visual Colors = Cursor")
//------------------------
// FeX Visual Freeze bars
//------------------------
MACRO_CONFIG_INT(ClVisualFreezeKillBars, fx_visual_freeze_kill_bars, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Turn on visual mode for freezekill bars Client side")
//------------------------
// FeX Visual menu variables
//------------------------
MACRO_CONFIG_INT(ClVisualMenuMode, fx_visual_cursor_spec, 1, 1, 4, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Visual Menu mode (1: Weapon, 2: Hook, 3: Tees, 4: Cursor)")
//------------------------
// FeX Weapon Settings
//------------------------
MACRO_CONFIG_INT(ClVisualSync, fx_visual_sync, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Sync the colors of the weapons")
//------------------------
// FeX More stuff
//------------------------

// Indicator Variables
MACRO_CONFIG_COL(ClIndicatorAlive, fx_indicator_alive, 255, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Color of alive tees in player indicator")
MACRO_CONFIG_COL(ClIndicatorFreeze, fx_indicator_freeze, 65407, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Color of frozen tees in player indicator")
MACRO_CONFIG_COL(ClIndicatorSaved, fx_indicator_dead, 0, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Color of tees who is getting saved in player indicator")
MACRO_CONFIG_INT(ClIndicatorOffset, fx_indicator_offset, 42, 16, 200, CFGFLAG_CLIENT | CFGFLAG_SAVE, "(16-128) Offset of indicator position")
MACRO_CONFIG_INT(ClIndicatorOffsetMax, fx_indicator_offset_max, 100, 16, 200, CFGFLAG_CLIENT | CFGFLAG_SAVE, "(16-128) Max indicator offset for variable offset setting")
MACRO_CONFIG_INT(ClIndicatorVariableDistance, fx_indicator_variable_distance, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Indicator circles will be further away the further the tee is")
MACRO_CONFIG_INT(ClIndicatorMaxDistance, fx_indicator_variable_max_distance, 2500, 500, 7000, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Maximum tee distance for variable offset")
MACRO_CONFIG_INT(ClIndicatorRadius, fx_indicator_radius, 4, 1, 16, CFGFLAG_CLIENT | CFGFLAG_SAVE, "(1-16) indicator circle size")
MACRO_CONFIG_INT(ClIndicatorOpacity, fx_indicator_opacity, 50, 0, 100, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Opacity of indicator circles")
MACRO_CONFIG_INT(ClPlayerIndicator, fx_player_indicator, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Show radial indicator of other tees")
MACRO_CONFIG_INT(ClPlayerIndicatorFreeze, fx_player_indicator_freeze, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Only show frozen tees in indicator")
MACRO_CONFIG_INT(ClIndicatorHideOnScreen, fx_indicator_hide_on_screen, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Hides the Indicator if Tee is on Screen (might be a lil buggy on bigger/smaller monitors")
MACRO_CONFIG_INT(ClIndicatorOnlyTeammates, fx_indicator_only_teammates, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Only shows teammates on the indicator")

MACRO_CONFIG_INT(ClIndicatorTeamOnly, fx_indicator_inteam, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Only show indicator while in team")
MACRO_CONFIG_INT(ClIndicatorTees, fx_indicator_tees, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Show tees instead of circles")

// Bind Wheel
MACRO_CONFIG_INT(ClResetBindWheelMouse, fx_reset_bindwheel_mouse, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Reset position of mouse when opening bindwheel")

// Outline Variables
MACRO_CONFIG_INT(ClOutline, fx_outline, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Draws outlines")
MACRO_CONFIG_INT(ClOutlineEntities, fx_outline_in_entities, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Only show outlines in entities")
MACRO_CONFIG_INT(ClOutlineFreeze, fx_outline_freeze, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Draws outline around freeze and deep")
MACRO_CONFIG_INT(ClOutlineKill, fx_outline_kill, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Draws outline around kill")
MACRO_CONFIG_INT(ClOutlineUnFreeze, fx_outline_unfreeze, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Draws outline around unfreeze and undeep")
MACRO_CONFIG_INT(ClOutlineTele, fx_outline_tele, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Draws outline around teleporters")
MACRO_CONFIG_INT(ClOutlineSolid, fx_outline_solid, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Draws outline around hook and unhook")
MACRO_CONFIG_INT(ClOutlineWidth, fx_outline_width, 5, 1, 16, CFGFLAG_CLIENT | CFGFLAG_SAVE, "(1-16) Width of freeze outline")
MACRO_CONFIG_INT(ClOutlineAlpha, fx_outline_alpha, 50, 0, 100, CFGFLAG_CLIENT | CFGFLAG_SAVE, "(0-100) Outline alpha")
MACRO_CONFIG_INT(ClOutlineAlphaSolid, fx_outline_alpha_solid, 100, 0, 100, CFGFLAG_CLIENT | CFGFLAG_SAVE, "(0-100) Outline solids alpha")
MACRO_CONFIG_COL(ClOutlineColorSolid, fx_outline_color_solid, 0, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Solid outline color") // 0 0 0
MACRO_CONFIG_COL(ClOutlineColorFreeze, fx_outline_color_freeze, 0, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Freeze outline color") // 0 0 0
MACRO_CONFIG_COL(ClOutlineColorTele, fx_outline_color_tele, 0, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Tele outline color") // 0 0 0
MACRO_CONFIG_COL(ClOutlineColorUnfreeze, fx_outline_color_unfreeze, 0, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Unfreeze outline color") // 0 0 0
MACRO_CONFIG_COL(ClOutlineColorKill, fx_outline_color_kill, 0, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Unfreeze outline color") // 0 0 0

// Trails
MACRO_CONFIG_INT(ClTeeTrail, fx_tee_trail, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Enable Tee trails")
MACRO_CONFIG_INT(ClTeeTrailOthers, fx_tee_trail_others, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Show tee trails for other players")
MACRO_CONFIG_INT(ClTeeTrailWidth, fx_tee_trail_width, 15, 0, 20, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Tee trail width")
MACRO_CONFIG_INT(ClTeeTrailLength, fx_tee_trail_length, 25, 5, 200, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Tee trail length")
MACRO_CONFIG_INT(ClTeeTrailAlpha, fx_tee_trail_alpha, 80, 1, 100, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Tee trail alpha")
MACRO_CONFIG_COL(ClTeeTrailColor, fx_tee_trail_color, 255, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Tee trail color")
MACRO_CONFIG_INT(ClTeeTrailTaper, fx_tee_trail_taper, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Taper tee trail over length")
MACRO_CONFIG_INT(ClTeeTrailFade, fx_tee_trail_fade, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Fade trail alpha over length")
MACRO_CONFIG_INT(ClTeeTrailColorMode, fx_tee_trail_color_mode, 1, 1, 5, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Tee trail color mode (1: Solid color, 2: Current Tee color, 3: Rainbow, 4: Color based on Tee speed, 5: Random)")

// Status Bar
MACRO_CONFIG_INT(ClStatusBar, tc_statusbar, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Enable status bar")

MACRO_CONFIG_INT(ClStatusBar12HourClock, fx_statusbar_12_hour_clock, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Use 12 hour clock in local time")
MACRO_CONFIG_INT(ClStatusBarLocalTimeSeocnds, fx_statusbar_local_time_seconds, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Show seconds in local time")
MACRO_CONFIG_INT(ClStatusBarHeight, fx_statusbar_height, 8, 1, 16, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Height of the status bar")

MACRO_CONFIG_COL(ClStatusBarColor, fx_statusbar_color, 3221225472, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Status bar background color")
MACRO_CONFIG_COL(ClStatusBarTextColor, fx_statusbar_text_color, 4278190335, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Status bar text color")
MACRO_CONFIG_INT(ClStatusBarAlpha, fx_statusbar_alpha, 75, 0, 100, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Status bar background alpha")
MACRO_CONFIG_INT(ClStatusBarTextAlpha, fx_statusbar_text_alpha, 100, 0, 100, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Status bar text alpha")

MACRO_CONFIG_INT(ClStatusBarLabels, fx_statusbar_labels, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Show labels on status bar entries")
MACRO_CONFIG_STR(ClStatusBarScheme, fx_statusbar_scheme, 16, "ac pf r", CFGFLAG_CLIENT | CFGFLAG_SAVE, "The order in which to show status bar items")



MACRO_CONFIG_INT(ClAmIFrozen, EEEfrz, 0, 0, 1, CFGFLAG_CLIENT, "")


// FeX Menus:
MACRO_CONFIG_INT(ClMenuTab, fx_menu_tab, 1, 1, 5, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Save and load the current menu tab")

// Quick Actions
MACRO_CONFIG_INT(ClShowQuickActions, fx_show_quick_actions, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Show quick actions menu when spectating")

// Nameplates
MACRO_CONFIG_INT(ClStrongWeakColorId, fx_strong_weak_color_id, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Render ClientIds in Nameplate Same Color as Strong/Weak Hook Color")

// Inform Update
MACRO_CONFIG_INT(ClUpdate, fx_update, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Inform with a github open link when a new update is available")
