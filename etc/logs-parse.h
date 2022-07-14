#ifndef LOGS_PARSE_H
#define LOGS_PARSE_H

#include "logs-tf.h"
#include "cjson/cJSON.h"

tf2_player parse_player(cJSON *log);

tf_class idclass(char *s);

#endif
