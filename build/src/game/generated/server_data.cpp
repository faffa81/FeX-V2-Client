#include "server_data.h"
static CDataSound x2000[] = {
	/* x2000[0] */ {  0,  "audio/wp_gun_fire-01.wv", },
	/* x2000[1] */ {  0,  "audio/wp_gun_fire-02.wv", },
	/* x2000[2] */ {  0,  "audio/wp_gun_fire-03.wv", },
};
static CDataSound x2016[] = {
	/* x2016[0] */ {  0,  "audio/wp_shotty_fire-01.wv", },
	/* x2016[1] */ {  0,  "audio/wp_shotty_fire-02.wv", },
	/* x2016[2] */ {  0,  "audio/wp_shotty_fire-03.wv", },
};
static CDataSound x2032[] = {
	/* x2032[0] */ {  0,  "audio/wp_flump_launch-01.wv", },
	/* x2032[1] */ {  0,  "audio/wp_flump_launch-02.wv", },
	/* x2032[2] */ {  0,  "audio/wp_flump_launch-03.wv", },
};
static CDataSound x2048[] = {
	/* x2048[0] */ {  0,  "audio/wp_hammer_swing-01.wv", },
	/* x2048[1] */ {  0,  "audio/wp_hammer_swing-02.wv", },
	/* x2048[2] */ {  0,  "audio/wp_hammer_swing-03.wv", },
};
static CDataSound x2064[] = {
	/* x2064[0] */ {  0,  "audio/wp_hammer_hit-01.wv", },
	/* x2064[1] */ {  0,  "audio/wp_hammer_hit-02.wv", },
	/* x2064[2] */ {  0,  "audio/wp_hammer_hit-03.wv", },
};
static CDataSound x2080[] = {
	/* x2080[0] */ {  0,  "audio/wp_ninja_attack-01.wv", },
	/* x2080[1] */ {  0,  "audio/wp_ninja_attack-02.wv", },
	/* x2080[2] */ {  0,  "audio/wp_ninja_attack-03.wv", },
};
static CDataSound x2096[] = {
	/* x2096[0] */ {  0,  "audio/wp_flump_explo-01.wv", },
	/* x2096[1] */ {  0,  "audio/wp_flump_explo-02.wv", },
	/* x2096[2] */ {  0,  "audio/wp_flump_explo-03.wv", },
};
static CDataSound x2112[] = {
	/* x2112[0] */ {  0,  "audio/wp_ninja_hit-01.wv", },
	/* x2112[1] */ {  0,  "audio/wp_ninja_hit-02.wv", },
	/* x2112[2] */ {  0,  "audio/wp_ninja_hit-03.wv", },
};
static CDataSound x2128[] = {
	/* x2128[0] */ {  0,  "audio/wp_laser_fire-01.wv", },
	/* x2128[1] */ {  0,  "audio/wp_laser_fire-02.wv", },
	/* x2128[2] */ {  0,  "audio/wp_laser_fire-03.wv", },
};
static CDataSound x2144[] = {
	/* x2144[0] */ {  0,  "audio/wp_laser_bnce-01.wv", },
	/* x2144[1] */ {  0,  "audio/wp_laser_bnce-02.wv", },
	/* x2144[2] */ {  0,  "audio/wp_laser_bnce-03.wv", },
};
static CDataSound x2160[] = {
	/* x2160[0] */ {  0,  "audio/wp_switch-01.wv", },
	/* x2160[1] */ {  0,  "audio/wp_switch-02.wv", },
	/* x2160[2] */ {  0,  "audio/wp_switch-03.wv", },
};
static CDataSound x2176[] = {
	/* x2176[0] */ {  0,  "audio/vo_teefault_pain_short-01.wv", },
	/* x2176[1] */ {  0,  "audio/vo_teefault_pain_short-02.wv", },
	/* x2176[2] */ {  0,  "audio/vo_teefault_pain_short-03.wv", },
	/* x2176[3] */ {  0,  "audio/vo_teefault_pain_short-04.wv", },
	/* x2176[4] */ {  0,  "audio/vo_teefault_pain_short-05.wv", },
	/* x2176[5] */ {  0,  "audio/vo_teefault_pain_short-06.wv", },
	/* x2176[6] */ {  0,  "audio/vo_teefault_pain_short-07.wv", },
	/* x2176[7] */ {  0,  "audio/vo_teefault_pain_short-08.wv", },
	/* x2176[8] */ {  0,  "audio/vo_teefault_pain_short-09.wv", },
	/* x2176[9] */ {  0,  "audio/vo_teefault_pain_short-10.wv", },
	/* x2176[10] */ {  0,  "audio/vo_teefault_pain_short-11.wv", },
	/* x2176[11] */ {  0,  "audio/vo_teefault_pain_short-12.wv", },
};
static CDataSound x2219[] = {
	/* x2219[0] */ {  0,  "audio/vo_teefault_pain_long-01.wv", },
	/* x2219[1] */ {  0,  "audio/vo_teefault_pain_long-02.wv", },
};
static CDataSound x2232[] = {
	/* x2232[0] */ {  0,  "audio/foley_land-01.wv", },
	/* x2232[1] */ {  0,  "audio/foley_land-02.wv", },
	/* x2232[2] */ {  0,  "audio/foley_land-03.wv", },
	/* x2232[3] */ {  0,  "audio/foley_land-04.wv", },
};
static CDataSound x2251[] = {
	/* x2251[0] */ {  0,  "audio/foley_dbljump-01.wv", },
	/* x2251[1] */ {  0,  "audio/foley_dbljump-02.wv", },
	/* x2251[2] */ {  0,  "audio/foley_dbljump-03.wv", },
};
static CDataSound x2267[] = {
	/* x2267[0] */ {  0,  "audio/foley_foot_left-01.wv", },
	/* x2267[1] */ {  0,  "audio/foley_foot_left-02.wv", },
	/* x2267[2] */ {  0,  "audio/foley_foot_left-03.wv", },
	/* x2267[3] */ {  0,  "audio/foley_foot_left-04.wv", },
	/* x2267[4] */ {  0,  "audio/foley_foot_right-01.wv", },
	/* x2267[5] */ {  0,  "audio/foley_foot_right-02.wv", },
	/* x2267[6] */ {  0,  "audio/foley_foot_right-03.wv", },
	/* x2267[7] */ {  0,  "audio/foley_foot_right-04.wv", },
};
static CDataSound x2298[] = {
	/* x2298[0] */ {  0,  "audio/foley_body_splat-01.wv", },
	/* x2298[1] */ {  0,  "audio/foley_body_splat-02.wv", },
	/* x2298[2] */ {  0,  "audio/foley_body_splat-03.wv", },
};
static CDataSound x2314[] = {
	/* x2314[0] */ {  0,  "audio/vo_teefault_spawn-01.wv", },
	/* x2314[1] */ {  0,  "audio/vo_teefault_spawn-02.wv", },
	/* x2314[2] */ {  0,  "audio/vo_teefault_spawn-03.wv", },
	/* x2314[3] */ {  0,  "audio/vo_teefault_spawn-04.wv", },
	/* x2314[4] */ {  0,  "audio/vo_teefault_spawn-05.wv", },
	/* x2314[5] */ {  0,  "audio/vo_teefault_spawn-06.wv", },
	/* x2314[6] */ {  0,  "audio/vo_teefault_spawn-07.wv", },
};
static CDataSound x2342[] = {
	/* x2342[0] */ {  0,  "audio/sfx_skid-01.wv", },
	/* x2342[1] */ {  0,  "audio/sfx_skid-02.wv", },
	/* x2342[2] */ {  0,  "audio/sfx_skid-03.wv", },
	/* x2342[3] */ {  0,  "audio/sfx_skid-04.wv", },
};
static CDataSound x2361[] = {
	/* x2361[0] */ {  0,  "audio/vo_teefault_cry-01.wv", },
	/* x2361[1] */ {  0,  "audio/vo_teefault_cry-02.wv", },
};
static CDataSound x2374[] = {
	/* x2374[0] */ {  0,  "audio/hook_loop-01.wv", },
	/* x2374[1] */ {  0,  "audio/hook_loop-02.wv", },
};
static CDataSound x2387[] = {
	/* x2387[0] */ {  0,  "audio/hook_attach-01.wv", },
	/* x2387[1] */ {  0,  "audio/hook_attach-02.wv", },
	/* x2387[2] */ {  0,  "audio/hook_attach-03.wv", },
};
static CDataSound x2403[] = {
	/* x2403[0] */ {  0,  "audio/foley_body_impact-01.wv", },
	/* x2403[1] */ {  0,  "audio/foley_body_impact-02.wv", },
	/* x2403[2] */ {  0,  "audio/foley_body_impact-03.wv", },
};
static CDataSound x2419[] = {
	/* x2419[0] */ {  0,  "audio/hook_noattach-01.wv", },
	/* x2419[1] */ {  0,  "audio/hook_noattach-02.wv", },
};
static CDataSound x2432[] = {
	/* x2432[0] */ {  0,  "audio/sfx_pickup_hrt-01.wv", },
	/* x2432[1] */ {  0,  "audio/sfx_pickup_hrt-02.wv", },
};
static CDataSound x2445[] = {
	/* x2445[0] */ {  0,  "audio/sfx_pickup_arm-01.wv", },
	/* x2445[1] */ {  0,  "audio/sfx_pickup_arm-02.wv", },
	/* x2445[2] */ {  0,  "audio/sfx_pickup_arm-03.wv", },
	/* x2445[3] */ {  0,  "audio/sfx_pickup_arm-04.wv", },
};
static CDataSound x2464[] = {
	/* x2464[0] */ {  0,  "audio/sfx_pickup_launcher.wv", },
};
static CDataSound x2474[] = {
	/* x2474[0] */ {  0,  "audio/sfx_pickup_sg.wv", },
};
static CDataSound x2484[] = {
	/* x2484[0] */ {  0,  "audio/sfx_pickup_ninja.wv", },
};
static CDataSound x2494[] = {
	/* x2494[0] */ {  0,  "audio/sfx_spawn_wpn-01.wv", },
	/* x2494[1] */ {  0,  "audio/sfx_spawn_wpn-02.wv", },
	/* x2494[2] */ {  0,  "audio/sfx_spawn_wpn-03.wv", },
};
static CDataSound x2510[] = {
	/* x2510[0] */ {  0,  "audio/wp_noammo-01.wv", },
	/* x2510[1] */ {  0,  "audio/wp_noammo-02.wv", },
	/* x2510[2] */ {  0,  "audio/wp_noammo-03.wv", },
	/* x2510[3] */ {  0,  "audio/wp_noammo-04.wv", },
	/* x2510[4] */ {  0,  "audio/wp_noammo-05.wv", },
};
static CDataSound x2532[] = {
	/* x2532[0] */ {  0,  "audio/sfx_hit_weak-01.wv", },
	/* x2532[1] */ {  0,  "audio/sfx_hit_weak-02.wv", },
};
static CDataSound x2545[] = {
	/* x2545[0] */ {  0,  "audio/sfx_msg-server.wv", },
};
static CDataSound x2555[] = {
	/* x2555[0] */ {  0,  "audio/sfx_msg-client.wv", },
};
static CDataSound x2565[] = {
	/* x2565[0] */ {  0,  "audio/sfx_msg-highlight.wv", },
};
static CDataSound x2575[] = {
	/* x2575[0] */ {  0,  "audio/sfx_ctf_drop.wv", },
};
static CDataSound x2585[] = {
	/* x2585[0] */ {  0,  "audio/sfx_ctf_rtn.wv", },
};
static CDataSound x2595[] = {
	/* x2595[0] */ {  0,  "audio/sfx_ctf_grab_pl.wv", },
};
static CDataSound x2605[] = {
	/* x2605[0] */ {  0,  "audio/sfx_ctf_grab_en.wv", },
};
static CDataSound x2615[] = {
	/* x2615[0] */ {  0,  "audio/sfx_ctf_cap_pl.wv", },
};
static CDataSound x2625[] = {
	/* x2625[0] */ {  0,  "audio/music_menu.wv", },
};
static CDataSoundset x9[] = {
	/* x9[0] */ {  "gun_fire",  3,x2000,  -1, },
	/* x9[1] */ {  "shotgun_fire",  3,x2016,  -1, },
	/* x9[2] */ {  "grenade_fire",  3,x2032,  -1, },
	/* x9[3] */ {  "hammer_fire",  3,x2048,  -1, },
	/* x9[4] */ {  "hammer_hit",  3,x2064,  -1, },
	/* x9[5] */ {  "ninja_fire",  3,x2080,  -1, },
	/* x9[6] */ {  "grenade_explode",  3,x2096,  -1, },
	/* x9[7] */ {  "ninja_hit",  3,x2112,  -1, },
	/* x9[8] */ {  "laser_fire",  3,x2128,  -1, },
	/* x9[9] */ {  "laser_bounce",  3,x2144,  -1, },
	/* x9[10] */ {  "weapon_switch",  3,x2160,  -1, },
	/* x9[11] */ {  "player_pain_short",  12,x2176,  -1, },
	/* x9[12] */ {  "player_pain_long",  2,x2219,  -1, },
	/* x9[13] */ {  "body_land",  4,x2232,  -1, },
	/* x9[14] */ {  "player_airjump",  3,x2251,  -1, },
	/* x9[15] */ {  "player_jump",  8,x2267,  -1, },
	/* x9[16] */ {  "player_die",  3,x2298,  -1, },
	/* x9[17] */ {  "player_spawn",  7,x2314,  -1, },
	/* x9[18] */ {  "player_skid",  4,x2342,  -1, },
	/* x9[19] */ {  "tee_cry",  2,x2361,  -1, },
	/* x9[20] */ {  "hook_loop",  2,x2374,  -1, },
	/* x9[21] */ {  "hook_attach_ground",  3,x2387,  -1, },
	/* x9[22] */ {  "hook_attach_player",  3,x2403,  -1, },
	/* x9[23] */ {  "hook_noattach",  2,x2419,  -1, },
	/* x9[24] */ {  "pickup_health",  2,x2432,  -1, },
	/* x9[25] */ {  "pickup_armor",  4,x2445,  -1, },
	/* x9[26] */ {  "pickup_grenade",  1,x2464,  -1, },
	/* x9[27] */ {  "pickup_shotgun",  1,x2474,  -1, },
	/* x9[28] */ {  "pickup_ninja",  1,x2484,  -1, },
	/* x9[29] */ {  "weapon_spawn",  3,x2494,  -1, },
	/* x9[30] */ {  "weapon_noammo",  5,x2510,  -1, },
	/* x9[31] */ {  "hit",  2,x2532,  -1, },
	/* x9[32] */ {  "chat_server",  1,x2545,  -1, },
	/* x9[33] */ {  "chat_client",  1,x2555,  -1, },
	/* x9[34] */ {  "chat_highlight",  1,x2565,  -1, },
	/* x9[35] */ {  "ctf_drop",  1,x2575,  -1, },
	/* x9[36] */ {  "ctf_return",  1,x2585,  -1, },
	/* x9[37] */ {  "ctf_grab_pl",  1,x2595,  -1, },
	/* x9[38] */ {  "ctf_grab_en",  1,x2605,  -1, },
	/* x9[39] */ {  "ctf_capture",  1,x2615,  -1, },
	/* x9[40] */ {  "menu",  1,x2625,  -1, },
};
static CDataImage x15[] = {
	/* x15[0] */ {  "null",  "",  0,  IGraphics::CTextureHandle(), },
	/* x15[1] */ {  "game",  "game.png",  0,  IGraphics::CTextureHandle(), },
	/* x15[2] */ {  "particles",  "particles.png",  0,  IGraphics::CTextureHandle(), },
	/* x15[3] */ {  "cursor",  "gui_cursor.png",  0,  IGraphics::CTextureHandle(), },
	/* x15[4] */ {  "banner",  "gui_logo.png",  0,  IGraphics::CTextureHandle(), },
	/* x15[5] */ {  "emoticons",  "emoticons.png",  0,  IGraphics::CTextureHandle(), },
	/* x15[6] */ {  "background_noise",  "background_noise.png",  0,  IGraphics::CTextureHandle(), },
	/* x15[7] */ {  "speedup_arrow",  "editor/speed_arrow.png",  0,  IGraphics::CTextureHandle(), },
	/* x15[8] */ {  "guibuttons",  "gui_buttons.png",  0,  IGraphics::CTextureHandle(), },
	/* x15[9] */ {  "guiicons",  "gui_icons.png",  0,  IGraphics::CTextureHandle(), },
	/* x15[10] */ {  "arrow",  "arrow.png",  0,  IGraphics::CTextureHandle(), },
	/* x15[11] */ {  "audio_source",  "editor/audio_source.png",  0,  IGraphics::CTextureHandle(), },
	/* x15[12] */ {  "strongweak",  "strong_weak.png",  0,  IGraphics::CTextureHandle(), },
	/* x15[13] */ {  "hud",  "hud.png",  0,  IGraphics::CTextureHandle(), },
	/* x15[14] */ {  "extras",  "extras.png",  0,  IGraphics::CTextureHandle(), },
	/* x15[15] */ {  "raceflag",  "race_flag.png",  0,  IGraphics::CTextureHandle(), },
	/* x15[16] */ {  "muted_icon",  "fex/icons/muted_icon.png",  0,  IGraphics::CTextureHandle(), },
};
static CDataPickupspec x20[] = {
	/* x20[0] */ {  "health",  15,  0, },
	/* x20[1] */ {  "armor",  15,  0, },
	/* x20[2] */ {  "armor_shotgun",  15,  0, },
	/* x20[3] */ {  "armor_grenade",  15,  0, },
	/* x20[4] */ {  "armor_laser",  15,  0, },
	/* x20[5] */ {  "armor_ninja",  15,  0, },
	/* x20[6] */ {  "weapon",  15,  0, },
	/* x20[7] */ {  "ninja",  90,  90, },
};
static CDataSpriteset x30[] = {
	/* x30[0] */ {  &x15[2],  8,  8, },
	/* x30[1] */ {  &x15[1],  32,  16, },
	/* x30[2] */ {  &x15[0],  8,  4, },
	/* x30[3] */ {  &x15[5],  4,  4, },
	/* x30[4] */ {  &x15[7],  1,  1, },
	/* x30[5] */ {  &x15[8],  12,  4, },
	/* x30[6] */ {  &x15[9],  12,  2, },
	/* x30[7] */ {  &x15[11],  1,  1, },
	/* x30[8] */ {  &x15[12],  3,  1, },
	/* x30[9] */ {  &x15[13],  16,  16, },
	/* x30[10] */ {  &x15[14],  16,  16, },
	/* x30[11] */ {  &x15[16],  1,  1, },
};
static CDataSprite x47[] = {
	/* x47[0] */ {  "part_slice",  &x30[0],  0,  0,  1,  1, },
	/* x47[1] */ {  "part_ball",  &x30[0],  1,  0,  1,  1, },
	/* x47[2] */ {  "part_splat01",  &x30[0],  2,  0,  1,  1, },
	/* x47[3] */ {  "part_splat02",  &x30[0],  3,  0,  1,  1, },
	/* x47[4] */ {  "part_splat03",  &x30[0],  4,  0,  1,  1, },
	/* x47[5] */ {  "part_smoke",  &x30[0],  0,  1,  1,  1, },
	/* x47[6] */ {  "part_shell",  &x30[0],  0,  2,  2,  2, },
	/* x47[7] */ {  "part_expl01",  &x30[0],  0,  4,  4,  4, },
	/* x47[8] */ {  "part_airjump",  &x30[0],  2,  2,  2,  2, },
	/* x47[9] */ {  "part_hit01",  &x30[0],  4,  1,  2,  2, },
	/* x47[10] */ {  "health_full",  &x30[1],  21,  0,  2,  2, },
	/* x47[11] */ {  "health_empty",  &x30[1],  23,  0,  2,  2, },
	/* x47[12] */ {  "armor_full",  &x30[1],  21,  2,  2,  2, },
	/* x47[13] */ {  "armor_empty",  &x30[1],  23,  2,  2,  2, },
	/* x47[14] */ {  "star1",  &x30[1],  15,  0,  2,  2, },
	/* x47[15] */ {  "star2",  &x30[1],  17,  0,  2,  2, },
	/* x47[16] */ {  "star3",  &x30[1],  19,  0,  2,  2, },
	/* x47[17] */ {  "part1",  &x30[1],  6,  0,  1,  1, },
	/* x47[18] */ {  "part2",  &x30[1],  6,  1,  1,  1, },
	/* x47[19] */ {  "part3",  &x30[1],  7,  0,  1,  1, },
	/* x47[20] */ {  "part4",  &x30[1],  7,  1,  1,  1, },
	/* x47[21] */ {  "part5",  &x30[1],  8,  0,  1,  1, },
	/* x47[22] */ {  "part6",  &x30[1],  8,  1,  1,  1, },
	/* x47[23] */ {  "part7",  &x30[1],  9,  0,  2,  2, },
	/* x47[24] */ {  "part8",  &x30[1],  11,  0,  2,  2, },
	/* x47[25] */ {  "part9",  &x30[1],  13,  0,  2,  2, },
	/* x47[26] */ {  "weapon_gun_body",  &x30[1],  2,  4,  4,  2, },
	/* x47[27] */ {  "weapon_gun_cursor",  &x30[1],  0,  4,  2,  2, },
	/* x47[28] */ {  "weapon_gun_proj",  &x30[1],  6,  4,  2,  2, },
	/* x47[29] */ {  "weapon_gun_muzzle1",  &x30[1],  8,  4,  4,  2, },
	/* x47[30] */ {  "weapon_gun_muzzle2",  &x30[1],  12,  4,  4,  2, },
	/* x47[31] */ {  "weapon_gun_muzzle3",  &x30[1],  16,  4,  4,  2, },
	/* x47[32] */ {  "weapon_shotgun_body",  &x30[1],  2,  6,  8,  2, },
	/* x47[33] */ {  "weapon_shotgun_cursor",  &x30[1],  0,  6,  2,  2, },
	/* x47[34] */ {  "weapon_shotgun_proj",  &x30[1],  10,  6,  2,  2, },
	/* x47[35] */ {  "weapon_shotgun_muzzle1",  &x30[1],  12,  6,  4,  2, },
	/* x47[36] */ {  "weapon_shotgun_muzzle2",  &x30[1],  16,  6,  4,  2, },
	/* x47[37] */ {  "weapon_shotgun_muzzle3",  &x30[1],  20,  6,  4,  2, },
	/* x47[38] */ {  "weapon_grenade_body",  &x30[1],  2,  8,  7,  2, },
	/* x47[39] */ {  "weapon_grenade_cursor",  &x30[1],  0,  8,  2,  2, },
	/* x47[40] */ {  "weapon_grenade_proj",  &x30[1],  10,  8,  2,  2, },
	/* x47[41] */ {  "weapon_hammer_body",  &x30[1],  2,  1,  4,  3, },
	/* x47[42] */ {  "weapon_hammer_cursor",  &x30[1],  0,  0,  2,  2, },
	/* x47[43] */ {  "weapon_hammer_proj",  &x30[1],  0,  0,  0,  0, },
	/* x47[44] */ {  "weapon_ninja_body",  &x30[1],  2,  10,  8,  2, },
	/* x47[45] */ {  "weapon_ninja_cursor",  &x30[1],  0,  10,  2,  2, },
	/* x47[46] */ {  "weapon_ninja_proj",  &x30[1],  0,  0,  0,  0, },
	/* x47[47] */ {  "weapon_laser_body",  &x30[1],  2,  12,  7,  3, },
	/* x47[48] */ {  "weapon_laser_cursor",  &x30[1],  0,  12,  2,  2, },
	/* x47[49] */ {  "weapon_laser_proj",  &x30[1],  10,  12,  2,  2, },
	/* x47[50] */ {  "hook_chain",  &x30[1],  2,  0,  1,  1, },
	/* x47[51] */ {  "hook_head",  &x30[1],  3,  0,  2,  1, },
	/* x47[52] */ {  "weapon_ninja_muzzle1",  &x30[1],  25,  0,  7,  4, },
	/* x47[53] */ {  "weapon_ninja_muzzle2",  &x30[1],  25,  4,  7,  4, },
	/* x47[54] */ {  "weapon_ninja_muzzle3",  &x30[1],  25,  8,  7,  4, },
	/* x47[55] */ {  "pickup_health",  &x30[1],  10,  2,  2,  2, },
	/* x47[56] */ {  "pickup_armor",  &x30[1],  12,  2,  2,  2, },
	/* x47[57] */ {  "pickup_hammer",  &x30[1],  2,  1,  4,  3, },
	/* x47[58] */ {  "pickup_gun",  &x30[1],  2,  4,  4,  2, },
	/* x47[59] */ {  "pickup_shotgun",  &x30[1],  2,  6,  8,  2, },
	/* x47[60] */ {  "pickup_grenade",  &x30[1],  2,  8,  7,  2, },
	/* x47[61] */ {  "pickup_laser",  &x30[1],  2,  12,  7,  3, },
	/* x47[62] */ {  "pickup_ninja",  &x30[1],  2,  10,  8,  2, },
	/* x47[63] */ {  "pickup_armor_shotgun",  &x30[1],  15,  2,  2,  2, },
	/* x47[64] */ {  "pickup_armor_grenade",  &x30[1],  17,  2,  2,  2, },
	/* x47[65] */ {  "pickup_armor_ninja",  &x30[1],  10,  10,  2,  2, },
	/* x47[66] */ {  "pickup_armor_laser",  &x30[1],  19,  2,  2,  2, },
	/* x47[67] */ {  "flag_blue",  &x30[1],  12,  8,  4,  8, },
	/* x47[68] */ {  "flag_red",  &x30[1],  16,  8,  4,  8, },
	/* x47[69] */ {  "tee_body",  &x30[2],  0,  0,  3,  3, },
	/* x47[70] */ {  "tee_body_outline",  &x30[2],  3,  0,  3,  3, },
	/* x47[71] */ {  "tee_foot",  &x30[2],  6,  1,  2,  1, },
	/* x47[72] */ {  "tee_foot_outline",  &x30[2],  6,  2,  2,  1, },
	/* x47[73] */ {  "tee_hand",  &x30[2],  6,  0,  1,  1, },
	/* x47[74] */ {  "tee_hand_outline",  &x30[2],  7,  0,  1,  1, },
	/* x47[75] */ {  "tee_eye_normal",  &x30[2],  2,  3,  1,  1, },
	/* x47[76] */ {  "tee_eye_angry",  &x30[2],  3,  3,  1,  1, },
	/* x47[77] */ {  "tee_eye_pain",  &x30[2],  4,  3,  1,  1, },
	/* x47[78] */ {  "tee_eye_happy",  &x30[2],  5,  3,  1,  1, },
	/* x47[79] */ {  "tee_eye_dead",  &x30[2],  6,  3,  1,  1, },
	/* x47[80] */ {  "tee_eye_surprise",  &x30[2],  7,  3,  1,  1, },
	/* x47[81] */ {  "oop",  &x30[3],  0,  0,  1,  1, },
	/* x47[82] */ {  "exclamation",  &x30[3],  1,  0,  1,  1, },
	/* x47[83] */ {  "hearts",  &x30[3],  2,  0,  1,  1, },
	/* x47[84] */ {  "drop",  &x30[3],  3,  0,  1,  1, },
	/* x47[85] */ {  "dotdot",  &x30[3],  0,  1,  1,  1, },
	/* x47[86] */ {  "music",  &x30[3],  1,  1,  1,  1, },
	/* x47[87] */ {  "sorry",  &x30[3],  2,  1,  1,  1, },
	/* x47[88] */ {  "ghost",  &x30[3],  3,  1,  1,  1, },
	/* x47[89] */ {  "sushi",  &x30[3],  0,  2,  1,  1, },
	/* x47[90] */ {  "splattee",  &x30[3],  1,  2,  1,  1, },
	/* x47[91] */ {  "deviltee",  &x30[3],  2,  2,  1,  1, },
	/* x47[92] */ {  "zomg",  &x30[3],  3,  2,  1,  1, },
	/* x47[93] */ {  "zzz",  &x30[3],  0,  3,  1,  1, },
	/* x47[94] */ {  "wtf",  &x30[3],  1,  3,  1,  1, },
	/* x47[95] */ {  "eyes",  &x30[3],  2,  3,  1,  1, },
	/* x47[96] */ {  "question",  &x30[3],  3,  3,  1,  1, },
	/* x47[97] */ {  "speedup_arrow",  &x30[4],  0,  0,  1,  1, },
	/* x47[98] */ {  "guibutton_off",  &x30[5],  0,  0,  4,  4, },
	/* x47[99] */ {  "guibutton_on",  &x30[5],  4,  0,  4,  4, },
	/* x47[100] */ {  "guibutton_hover",  &x30[5],  8,  0,  4,  4, },
	/* x47[101] */ {  "guiicon_mute",  &x30[6],  0,  0,  4,  2, },
	/* x47[102] */ {  "guiicon_emoticon_mute",  &x30[6],  4,  0,  4,  2, },
	/* x47[103] */ {  "guiicon_friend",  &x30[6],  8,  0,  4,  2, },
	/* x47[104] */ {  "audio_source",  &x30[7],  0,  0,  1,  1, },
	/* x47[105] */ {  "muted_icon",  &x30[11],  0,  0,  1,  1, },
	/* x47[106] */ {  "hook_strong",  &x30[8],  0,  0,  1,  1, },
	/* x47[107] */ {  "hook_weak",  &x30[8],  1,  0,  1,  1, },
	/* x47[108] */ {  "hook_icon",  &x30[8],  2,  0,  1,  1, },
	/* x47[109] */ {  "hud_airjump",  &x30[9],  0,  0,  2,  2, },
	/* x47[110] */ {  "hud_airjump_empty",  &x30[9],  2,  0,  2,  2, },
	/* x47[111] */ {  "hud_solo",  &x30[9],  4,  0,  2,  2, },
	/* x47[112] */ {  "hud_collision_disabled",  &x30[9],  6,  0,  2,  2, },
	/* x47[113] */ {  "hud_endless_jump",  &x30[9],  8,  0,  2,  2, },
	/* x47[114] */ {  "hud_endless_hook",  &x30[9],  10,  0,  2,  2, },
	/* x47[115] */ {  "hud_jetpack",  &x30[9],  12,  0,  2,  2, },
	/* x47[116] */ {  "hud_freeze_bar_full_left",  &x30[9],  0,  2,  1,  1, },
	/* x47[117] */ {  "hud_freeze_bar_full",  &x30[9],  1,  2,  1,  1, },
	/* x47[118] */ {  "hud_freeze_bar_empty",  &x30[9],  2,  2,  1,  1, },
	/* x47[119] */ {  "hud_freeze_bar_empty_right",  &x30[9],  3,  2,  1,  1, },
	/* x47[120] */ {  "hud_ninja_bar_full_left",  &x30[9],  0,  3,  1,  1, },
	/* x47[121] */ {  "hud_ninja_bar_full",  &x30[9],  1,  3,  1,  1, },
	/* x47[122] */ {  "hud_ninja_bar_empty",  &x30[9],  2,  3,  1,  1, },
	/* x47[123] */ {  "hud_ninja_bar_empty_right",  &x30[9],  3,  3,  1,  1, },
	/* x47[124] */ {  "hud_hook_hit_disabled",  &x30[9],  4,  2,  2,  2, },
	/* x47[125] */ {  "hud_hammer_hit_disabled",  &x30[9],  6,  2,  2,  2, },
	/* x47[126] */ {  "hud_shotgun_hit_disabled",  &x30[9],  8,  2,  2,  2, },
	/* x47[127] */ {  "hud_grenade_hit_disabled",  &x30[9],  10,  2,  2,  2, },
	/* x47[128] */ {  "hud_laser_hit_disabled",  &x30[9],  12,  2,  2,  2, },
	/* x47[129] */ {  "hud_gun_hit_disabled",  &x30[9],  14,  2,  2,  2, },
	/* x47[130] */ {  "hud_deep_frozen",  &x30[9],  10,  4,  2,  2, },
	/* x47[131] */ {  "hud_live_frozen",  &x30[9],  12,  4,  2,  2, },
	/* x47[132] */ {  "hud_teleport_grenade",  &x30[9],  4,  4,  2,  2, },
	/* x47[133] */ {  "hud_teleport_gun",  &x30[9],  6,  4,  2,  2, },
	/* x47[134] */ {  "hud_teleport_laser",  &x30[9],  8,  4,  2,  2, },
	/* x47[135] */ {  "hud_practice_mode",  &x30[9],  4,  6,  2,  2, },
	/* x47[136] */ {  "hud_dummy_hammer",  &x30[9],  6,  6,  2,  2, },
	/* x47[137] */ {  "hud_dummy_copy",  &x30[9],  8,  6,  2,  2, },
	/* x47[138] */ {  "hud_lock_mode",  &x30[9],  10,  6,  2,  2, },
	/* x47[139] */ {  "hud_team0_mode",  &x30[9],  12,  6,  2,  2, },
	/* x47[140] */ {  "part_snowflake",  &x30[10],  0,  0,  2,  2, },
	/* x47[141] */ {  "part_sparkle",  &x30[10],  2,  0,  2,  2, },
};
static CAnimKeyframe x5135[] = {
	/* x5135[0] */ {  0.000000f,  0.000000f,  -4.000000f,  0.000000f, },
};
static CAnimKeyframe x5142[] = {
	/* x5142[0] */ {  0.000000f,  0.000000f,  10.000000f,  0.000000f, },
};
static CAnimKeyframe x5149[] = {
	/* x5149[0] */ {  0.000000f,  0.000000f,  10.000000f,  0.000000f, },
};
static CAnimKeyframe *x5156 = 0;
static CAnimKeyframe *x5180 = 0;
static CAnimKeyframe x5187[] = {
	/* x5187[0] */ {  0.000000f,  -7.000000f,  0.000000f,  0.000000f, },
};
static CAnimKeyframe x5194[] = {
	/* x5194[0] */ {  0.000000f,  7.000000f,  0.000000f,  0.000000f, },
};
static CAnimKeyframe *x5201 = 0;
static CAnimKeyframe *x5220 = 0;
static CAnimKeyframe x5227[] = {
	/* x5227[0] */ {  0.000000f,  -3.000000f,  0.000000f,  -0.100000f, },
};
static CAnimKeyframe x5234[] = {
	/* x5234[0] */ {  0.000000f,  3.000000f,  0.000000f,  -0.100000f, },
};
static CAnimKeyframe *x5241 = 0;
static CAnimKeyframe x5260[] = {
	/* x5260[0] */ {  0.000000f,  0.000000f,  3.000000f,  0.000000f, },
};
static CAnimKeyframe x5267[] = {
	/* x5267[0] */ {  0.000000f,  -12.000000f,  0.000000f,  0.100000f, },
};
static CAnimKeyframe x5274[] = {
	/* x5274[0] */ {  0.000000f,  -8.000000f,  0.000000f,  0.100000f, },
};
static CAnimKeyframe *x5281 = 0;
static CAnimKeyframe x5305[] = {
	/* x5305[0] */ {  0.000000f,  0.000000f,  3.000000f,  0.000000f, },
};
static CAnimKeyframe x5312[] = {
	/* x5312[0] */ {  0.000000f,  12.000000f,  0.000000f,  -0.100000f, },
};
static CAnimKeyframe x5319[] = {
	/* x5319[0] */ {  0.000000f,  8.000000f,  0.000000f,  -0.100000f, },
};
static CAnimKeyframe *x5326 = 0;
static CAnimKeyframe x5350[] = {
	/* x5350[0] */ {  0.000000f,  0.000000f,  0.000000f,  0.000000f, },
	/* x5350[1] */ {  0.200000f,  0.000000f,  -1.000000f,  0.000000f, },
	/* x5350[2] */ {  0.400000f,  0.000000f,  0.000000f,  0.000000f, },
	/* x5350[3] */ {  0.600000f,  0.000000f,  0.000000f,  0.000000f, },
	/* x5350[4] */ {  0.800000f,  0.000000f,  -1.000000f,  0.000000f, },
	/* x5350[5] */ {  1.000000f,  0.000000f,  0.000000f,  0.000000f, },
};
static CAnimKeyframe x5357[] = {
	/* x5357[0] */ {  0.000000f,  8.000000f,  0.000000f,  0.000000f, },
	/* x5357[1] */ {  0.200000f,  -8.000000f,  0.000000f,  0.000000f, },
	/* x5357[2] */ {  0.400000f,  -10.000000f,  -4.000000f,  0.200000f, },
	/* x5357[3] */ {  0.600000f,  -8.000000f,  -8.000000f,  0.300000f, },
	/* x5357[4] */ {  0.800000f,  4.000000f,  -4.000000f,  -0.200000f, },
	/* x5357[5] */ {  1.000000f,  8.000000f,  0.000000f,  0.000000f, },
};
static CAnimKeyframe x5364[] = {
	/* x5364[0] */ {  0.000000f,  -10.000000f,  -4.000000f,  0.200000f, },
	/* x5364[1] */ {  0.200000f,  -8.000000f,  -8.000000f,  0.300000f, },
	/* x5364[2] */ {  0.400000f,  4.000000f,  -4.000000f,  -0.200000f, },
	/* x5364[3] */ {  0.600000f,  8.000000f,  0.000000f,  0.000000f, },
	/* x5364[4] */ {  0.800000f,  8.000000f,  0.000000f,  0.000000f, },
	/* x5364[5] */ {  1.000000f,  -10.000000f,  -4.000000f,  0.200000f, },
};
static CAnimKeyframe *x5371 = 0;
static CAnimKeyframe x5470[] = {
	/* x5470[0] */ {  0.000000f,  0.000000f,  -1.000000f,  0.000000f, },
	/* x5470[1] */ {  0.200000f,  0.000000f,  0.000000f,  0.000000f, },
	/* x5470[2] */ {  0.400000f,  0.000000f,  -1.000000f,  0.000000f, },
	/* x5470[3] */ {  0.600000f,  0.000000f,  0.000000f,  0.000000f, },
	/* x5470[4] */ {  0.800000f,  0.000000f,  0.000000f,  0.000000f, },
	/* x5470[5] */ {  1.000000f,  0.000000f,  -1.000000f,  0.000000f, },
};
static CAnimKeyframe x5477[] = {
	/* x5477[0] */ {  0.000000f,  18.000000f,  -8.000000f,  -0.270000f, },
	/* x5477[1] */ {  0.200000f,  6.000000f,  0.000000f,  0.000000f, },
	/* x5477[2] */ {  0.400000f,  -7.000000f,  0.000000f,  0.000000f, },
	/* x5477[3] */ {  0.600000f,  -13.000000f,  -4.500000f,  0.050000f, },
	/* x5477[4] */ {  0.800000f,  0.000000f,  -8.000000f,  -0.200000f, },
	/* x5477[5] */ {  1.000000f,  18.000000f,  -8.000000f,  -0.270000f, },
};
static CAnimKeyframe x5484[] = {
	/* x5484[0] */ {  0.000000f,  -11.000000f,  -2.500000f,  0.050000f, },
	/* x5484[1] */ {  0.200000f,  -14.000000f,  -5.000000f,  0.100000f, },
	/* x5484[2] */ {  0.400000f,  11.000000f,  -8.000000f,  -0.300000f, },
	/* x5484[3] */ {  0.600000f,  18.000000f,  -8.000000f,  -0.270000f, },
	/* x5484[4] */ {  0.800000f,  3.000000f,  0.000000f,  0.000000f, },
	/* x5484[5] */ {  1.000000f,  -11.000000f,  -2.500000f,  0.050000f, },
};
static CAnimKeyframe *x5491 = 0;
static CAnimKeyframe x5590[] = {
	/* x5590[0] */ {  0.000000f,  0.000000f,  -1.000000f,  0.000000f, },
	/* x5590[1] */ {  0.200000f,  0.000000f,  0.000000f,  0.000000f, },
	/* x5590[2] */ {  0.400000f,  0.000000f,  0.000000f,  0.000000f, },
	/* x5590[3] */ {  0.600000f,  0.000000f,  -1.000000f,  0.000000f, },
	/* x5590[4] */ {  0.800000f,  0.000000f,  0.000000f,  0.000000f, },
	/* x5590[5] */ {  1.000000f,  0.000000f,  -1.000000f,  0.000000f, },
};
static CAnimKeyframe x5597[] = {
	/* x5597[0] */ {  0.000000f,  -18.000000f,  -8.000000f,  0.270000f, },
	/* x5597[1] */ {  0.200000f,  0.000000f,  -8.000000f,  0.200000f, },
	/* x5597[2] */ {  0.400000f,  13.000000f,  -4.500000f,  -0.050000f, },
	/* x5597[3] */ {  0.600000f,  7.000000f,  0.000000f,  0.000000f, },
	/* x5597[4] */ {  0.800000f,  -6.000000f,  0.000000f,  0.000000f, },
	/* x5597[5] */ {  1.000000f,  -18.000000f,  -8.000000f,  0.270000f, },
};
static CAnimKeyframe x5604[] = {
	/* x5604[0] */ {  0.000000f,  11.000000f,  -2.500000f,  -0.050000f, },
	/* x5604[1] */ {  0.200000f,  -3.000000f,  0.000000f,  0.000000f, },
	/* x5604[2] */ {  0.400000f,  -18.000000f,  -8.000000f,  0.270000f, },
	/* x5604[3] */ {  0.600000f,  -11.000000f,  -8.000000f,  0.300000f, },
	/* x5604[4] */ {  0.800000f,  14.000000f,  -5.000000f,  -0.100000f, },
	/* x5604[5] */ {  1.000000f,  11.000000f,  -2.500000f,  -0.050000f, },
};
static CAnimKeyframe *x5611 = 0;
static CAnimKeyframe *x5710 = 0;
static CAnimKeyframe *x5717 = 0;
static CAnimKeyframe *x5724 = 0;
static CAnimKeyframe x5731[] = {
	/* x5731[0] */ {  0.000000f,  0.000000f,  0.000000f,  -0.100000f, },
	/* x5731[1] */ {  0.300000f,  0.000000f,  0.000000f,  0.250000f, },
	/* x5731[2] */ {  0.400000f,  0.000000f,  0.000000f,  0.300000f, },
	/* x5731[3] */ {  0.500000f,  0.000000f,  0.000000f,  0.250000f, },
	/* x5731[4] */ {  1.000000f,  0.000000f,  0.000000f,  -0.100000f, },
};
static CAnimKeyframe *x5765 = 0;
static CAnimKeyframe *x5772 = 0;
static CAnimKeyframe *x5779 = 0;
static CAnimKeyframe x5786[] = {
	/* x5786[0] */ {  0.000000f,  0.000000f,  0.000000f,  -0.250000f, },
	/* x5786[1] */ {  0.100000f,  0.000000f,  0.000000f,  -0.050000f, },
	/* x5786[2] */ {  0.150000f,  0.000000f,  0.000000f,  0.350000f, },
	/* x5786[3] */ {  0.420000f,  0.000000f,  0.000000f,  0.400000f, },
	/* x5786[4] */ {  0.500000f,  0.000000f,  0.000000f,  0.350000f, },
	/* x5786[5] */ {  1.000000f,  0.000000f,  0.000000f,  -0.250000f, },
};
static CAnimation x78[] = {
	/* x78[0] */ {  "base",  /* x78[0].body */ {  1,x5135, },  /* x78[0].back_foot */ {  1,x5142, },  /* x78[0].front_foot */ {  1,x5149, },  /* x78[0].attach */ {  0,x5156, }, },
	/* x78[1] */ {  "idle",  /* x78[1].body */ {  0,x5180, },  /* x78[1].back_foot */ {  1,x5187, },  /* x78[1].front_foot */ {  1,x5194, },  /* x78[1].attach */ {  0,x5201, }, },
	/* x78[2] */ {  "inair",  /* x78[2].body */ {  0,x5220, },  /* x78[2].back_foot */ {  1,x5227, },  /* x78[2].front_foot */ {  1,x5234, },  /* x78[2].attach */ {  0,x5241, }, },
	/* x78[3] */ {  "sit_left",  /* x78[3].body */ {  1,x5260, },  /* x78[3].back_foot */ {  1,x5267, },  /* x78[3].front_foot */ {  1,x5274, },  /* x78[3].attach */ {  0,x5281, }, },
	/* x78[4] */ {  "sit_right",  /* x78[4].body */ {  1,x5305, },  /* x78[4].back_foot */ {  1,x5312, },  /* x78[4].front_foot */ {  1,x5319, },  /* x78[4].attach */ {  0,x5326, }, },
	/* x78[5] */ {  "walk",  /* x78[5].body */ {  6,x5350, },  /* x78[5].back_foot */ {  6,x5357, },  /* x78[5].front_foot */ {  6,x5364, },  /* x78[5].attach */ {  0,x5371, }, },
	/* x78[6] */ {  "run_left",  /* x78[6].body */ {  6,x5470, },  /* x78[6].back_foot */ {  6,x5477, },  /* x78[6].front_foot */ {  6,x5484, },  /* x78[6].attach */ {  0,x5491, }, },
	/* x78[7] */ {  "run_right",  /* x78[7].body */ {  6,x5590, },  /* x78[7].back_foot */ {  6,x5597, },  /* x78[7].front_foot */ {  6,x5604, },  /* x78[7].attach */ {  0,x5611, }, },
	/* x78[8] */ {  "hammer_swing",  /* x78[8].body */ {  0,x5710, },  /* x78[8].back_foot */ {  0,x5717, },  /* x78[8].front_foot */ {  0,x5724, },  /* x78[8].attach */ {  5,x5731, }, },
	/* x78[9] */ {  "ninja_swing",  /* x78[9].body */ {  0,x5765, },  /* x78[9].back_foot */ {  0,x5772, },  /* x78[9].front_foot */ {  0,x5779, },  /* x78[9].attach */ {  6,x5786, }, },
};
static CDataSprite* *x5951 = 0;
static CDataSprite* x6096[] = {
	&x47[29],
	&x47[30],
	&x47[31],
};
static CDataSprite* x6292[] = {
	&x47[35],
	&x47[36],
	&x47[37],
};
static CDataSprite* *x6488 = 0;
static CDataSprite* *x6633 = 0;
static CDataSprite* x6778[] = {
	&x47[52],
	&x47[53],
	&x47[54],
};
static CDataWeaponspec x1994[] = {
	/* x1994[0] */ {  "hammer",  &x47[41],  &x47[42],  &x47[43],  0,x5951,  96,  125,  10,  0,  3,  4.000000f,  -20.000000f,  0.000000f,  0.000000f,  5.000000f, },
	/* x1994[1] */ {  "gun",  &x47[26],  &x47[27],  &x47[28],  3,x6096,  64,  125,  10,  500,  1,  32.000000f,  4.000000f,  58.875200f,  6.000000f,  5.000000f, },
	/* x1994[2] */ {  "shotgun",  &x47[32],  &x47[33],  &x47[34],  3,x6292,  96,  500,  10,  0,  1,  24.000000f,  -2.000000f,  83.312800f,  6.000000f,  5.000000f, },
	/* x1994[3] */ {  "grenade",  &x47[38],  &x47[39],  &x47[40],  0,x6488,  96,  500,  10,  0,  1,  24.000000f,  -2.000000f,  0.000000f,  0.000000f,  5.000000f, },
	/* x1994[4] */ {  "laser",  &x47[47],  &x47[48],  &x47[49],  0,x6633,  92,  800,  10,  0,  5,  24.000000f,  -2.000000f,  0.000000f,  0.000000f,  5.000000f, },
	/* x1994[5] */ {  "ninja",  &x47[44],  &x47[45],  &x47[46],  3,x6778,  96,  800,  10,  0,  9,  0.000000f,  0.000000f,  40.000000f,  -4.000000f,  5.000000f, },
};
CDataContainer datacontainer = 
/* datacontainer */ {
	41,x9,
	17,x15,
	8,x20,
	12,x30,
	142,x47,
	10,x78,
	/* datacontainer.weapons */ { 	/* datacontainer.weapons.hammer */ { 	&x1994[0], }, 	/* datacontainer.weapons.gun */ { 	&x1994[1], 	1.250000f, 	2200.000000f, 	2.000000f, }, 	/* datacontainer.weapons.shotgun */ { 	&x1994[2], 	1.250000f, 	2200.000000f, 	0.800000f, 	0.250000f, }, 	/* datacontainer.weapons.grenade */ { 	&x1994[3], 	7.000000f, 	1000.000000f, 	2.000000f, }, 	/* datacontainer.weapons.laser */ { 	&x1994[4], 	800.000000f, 	150, 	1, 	0.000000f, }, 	/* datacontainer.weapons.ninja */ { 	&x1994[5], 	15000, 	200, 	50, }, 	6,x1994, },
}
;
CDataContainer *g_pData = &datacontainer;
