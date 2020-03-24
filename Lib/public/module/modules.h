#pragma once

#include "module_cmn.h"

/* Modules interface functions */
_public_ mod_ret modules_set_memhook(const memhook_t *hook);
_public_ mod_ret modules_ctx_set_logger(const char *ctx_name, const log_cb logger);
_public_ mod_ret modules_ctx_loop_events(const char *ctx_name, const int max_events);
_public_ mod_ret modules_ctx_quit(const char *ctx_name, const uint8_t quit_code);

_public_ mod_ret modules_ctx_get_fd(const char *ctx_name, int *fd);
_public_ mod_ret modules_ctx_dispatch(const char *ctx_name, int *ret);

_public_ mod_ret modules_ctx_dump(const char *ctx_name);

_public_ size_t modules_ctx_trim(const char *ctx_name, const stats_t *thres);

/* External shared object module runtime loading */
_public_ mod_ret modules_ctx_load(const char *ctx_name, const char *module_path);
_public_ mod_ret modules_ctx_unload(const char *ctx_name, const char *module_path);
