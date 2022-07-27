#ifndef LOGS_PARSE_H
#define LOGS_PARSE_H

#include "logs-tf.h"
#include "../../deps/tbs/types.h"
#include "cjson/cJSON.h"

tf_player parse_player(cJSON *playerlog);

tf_class idclass(char *s);

tf_game parse_game(cJSON *log);

u8 getPlayerCount(cJSON *players);

void sortplayers(cJSON **playerlist);

#endif
