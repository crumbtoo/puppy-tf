#ifndef LOGS_TF_H
#define LOGS_TF_H

#include "ints.h"

typedef enum {TF_RED, TF_BLUE} tf_team;
typedef enum {TF_SCOUT = 1, TF_SOLDIER, TF_PYRO, TF_DEMOMAN, TF_HEAVY, TF_ENGINEER, TF_MEDIC, TF_SNIPER, TF_SPY} tf_class;

typedef struct
{
	tf_class class;
	u8 kills;
	u8 assists;
	u8 deaths;
	u32 dmg;
	u16 total_time;
} tf_class_stats;

typedef struct
{
	char sid3[17];	// [U:1:1128930437]
	u64 sid64;

	tf_class class_stats[9];

	tf_team team;
	u8 kills;
	u8 deaths;
	u8 assists;
	u8 suicides;
	u8 drops;
	f64 kapd;
	f64 kpd;
	u32 dmg;
	u32 dmg_real;
	u32 dt;
	u32 dt_real;
	u32 hr;			// heath received
	u32 heal;
	u16 dapd;
	u16 dapm;
	u16 ubers;
	u16 medkits;
	u16 medkits_hp;
	u16 backstabs;
	u16 headshots;
	u16 headshots_hit;
	u16 sentries;
	u16 cpc;
	u16 ic;
} tf2_player;

#endif
