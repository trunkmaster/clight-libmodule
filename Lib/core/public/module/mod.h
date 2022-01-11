#pragma once

#ifndef LIBMODULE_CORE_H
    #define LIBMODULE_CORE_H
#endif

#include <module/cmn.h>
#include <module/structs/itr.h>

/* Modules states */
typedef enum {
    M_MOD_IDLE = 1 << 0,
    M_MOD_RUNNING = 1 << 1,
    M_MOD_PAUSED = 1 << 2,
    M_MOD_STOPPED = 1 << 3,
    M_MOD_ZOMBIE = 1 << 4
} m_mod_states;

/*
 * Modules flags, leave upper 16b for module permissions management;
 * First 8 bits are constant flags.
 * There is still no API to update set flags though.
 */
#define M_MOD_FL_PERM(val)         val << 16
#define M_MOD_FL_MODIFIABLE(val)   val << 8
typedef enum {
    M_MOD_NAME_DUP          = 1 << 0,         // Should module's name be strdupped? (force M_MOD_NAME_AUTOFREE flag)
    M_MOD_NAME_AUTOFREE     = 1 << 1,         // Should module's name be autofreed?
    M_MOD_ALLOW_REPLACE     = M_MOD_FL_MODIFIABLE(1 << 0),         // Can module be replaced by another module with same name?
    M_MOD_PERSIST           = M_MOD_FL_MODIFIABLE(1 << 1),         // Module cannot be deregistered by direct call to m_mod_deregister (or by FS delete) while its context is looping
    M_MOD_USERDATA_AUTOFREE = M_MOD_FL_MODIFIABLE(1 << 2),         // Automatically free module userdata upon deregister
    M_MOD_DENY_CTX          = M_MOD_FL_PERM(1 << 0), // Deny access to module's ctx through m_mod_ctx() (it means the module won't be able to call ctx API)
    M_MOD_DENY_PUB          = M_MOD_FL_PERM(1 << 1), // Deny access to module's publishing functions: m_mod_ps_{tell,publish,broadcast,poisonpill}
    M_MOD_DENY_SUB          = M_MOD_FL_PERM(1 << 2), // Deny access to m_mod_ps_(un)subscribe()
} m_mod_flags;

/* Callbacks typedefs */
typedef bool (*m_start_cb)(m_mod_t *self);
typedef bool (*m_eval_cb)(m_mod_t *self);
typedef void (*m_evt_cb)(m_mod_t *self, const m_queue_t *const evts);
typedef void (*m_stop_cb)(m_mod_t *self);

/* Struct that holds user defined callbacks */
typedef struct {
    m_start_cb on_start;
    m_eval_cb on_eval;
    m_evt_cb on_evt;
    m_stop_cb on_stop;
} m_mod_hook_t;

typedef struct {
    uint64_t inactive_ms;
    double activity_freq;
    uint64_t sent_msgs;
    uint64_t recv_msgs;
} m_mod_stats_t;

/* Module interface functions */

/* Module registration */
int m_mod_register(const char *name, m_ctx_t *c, m_mod_t **mod_ref, const m_mod_hook_t *hook,
                   m_mod_flags flags, const void *userdata);
int m_mod_deregister(m_mod_t **mod);

/* Retrieve module context */
m_ctx_t *m_mod_ctx(const m_mod_t *mod);

/* Retrieve module name */
const char *m_mod_name(const m_mod_t *mod);

/* Module state getter */
bool m_mod_is(const m_mod_t *mod, m_mod_states st);
m_mod_states m_mod_state(const m_mod_t *mod);

/* Module state setters */
int m_mod_start(m_mod_t *mod);
int m_mod_pause(m_mod_t *mod);
int m_mod_resume(m_mod_t *mod);
int m_mod_stop(m_mod_t *mod);

/* Module generic functions */
int m_mod_log(const m_mod_t *mod, const char *fmt, ...);
int m_mod_dump(const m_mod_t *mod);
int m_mod_stats(const m_mod_t *mod, m_mod_stats_t *stats);

const void *m_mod_userdata(const m_mod_t *mod);

m_mod_t *m_mod_ref(const m_mod_t *mod, const char *name);

int m_mod_become(m_mod_t *mod, m_evt_cb new_on_evt);
int m_mod_unbecome(m_mod_t *mod);

/* Module PubSub interface */
int m_mod_ps_tell(m_mod_t *mod, const m_mod_t *recipient, const void *message, m_ps_flags flags);
int m_mod_ps_publish(m_mod_t *mod, const char *topic, const void *message, m_ps_flags flags);
int m_mod_ps_broadcast(m_mod_t *mod, const void *message, m_ps_flags flags);
int m_mod_ps_poisonpill(m_mod_t *mod, const m_mod_t *recipient);
int m_mod_ps_subscribe(m_mod_t *mod, const char *topic, m_src_flags flags, const void *userptr);
int m_mod_ps_unsubscribe(m_mod_t *mod, const char *topic);

/* Events' stashing API */
int m_mod_stash(m_mod_t *mod, const m_evt_t *evt);
ssize_t m_mod_unstash(m_mod_t *mod, size_t len);

/* Event Sources management */
ssize_t m_mod_src_len(const m_mod_t *mod, m_src_types type);

int m_mod_src_register_fd(m_mod_t *mod, int fd, m_src_flags flags, const void *userptr);
int m_mod_src_deregister_fd(m_mod_t *mod, int fd);

int m_mod_src_register_tmr(m_mod_t *mod, const m_src_tmr_t *its, m_src_flags flags, const void *userptr);
int m_mod_src_deregister_tmr(m_mod_t *mod, const m_src_tmr_t *its);

int m_mod_src_register_sgn(m_mod_t *mod, const m_src_sgn_t *sgs, m_src_flags flags, const void *userptr);
int m_mod_src_deregister_sgn(m_mod_t *mod, const m_src_sgn_t *sgs);

int m_mod_src_register_path(m_mod_t *mod, const m_src_path_t *pts, m_src_flags flags, const void *userptr);
int m_mod_src_deregister_path(m_mod_t *mod, const m_src_path_t *pts);

int m_mod_src_register_pid(m_mod_t *mod, const m_src_pid_t *pid, m_src_flags flags, const void *userptr);
int m_mod_src_deregister_pid(m_mod_t *mod, const m_src_pid_t *pid);

int m_mod_src_register_task(m_mod_t *mod, const m_src_task_t *tid, m_src_flags flags, const void *userptr);
int m_mod_src_deregister_task(m_mod_t *mod, const m_src_task_t *tid);

int m_mod_src_register_thresh(m_mod_t *mod, const m_src_thresh_t *thr, m_src_flags flags, const void *userptr);
int m_mod_src_deregister_thresh(m_mod_t *mod, const m_src_thresh_t *thr);

/* Event batch management */
int m_mod_set_batch_size(m_mod_t *mod, size_t len);
int m_mod_set_batch_timeout(m_mod_t *mod, uint64_t timeout_ms);

/* Generic event source registering functions */
#define m_mod_src_register(mod, X, flags, userptr) _Generic((X) + 0, \
    int: m_mod_src_register_fd, \
    char *: m_mod_ps_subscribe, \
    m_src_tmr_t *: m_mod_src_register_tmr, \
    m_src_sgn_t *: m_mod_src_register_sgn, \
    m_src_path_t *: m_mod_src_register_path, \
    m_src_pid_t *: m_mod_src_register_pid, \
    m_src_task_t *: m_mod_src_register_task, \
    m_src_thresh_t *: m_mod_src_register_thresh \
    )(mod, X, flags, userptr)

#define m_mod_src_deregister(mod, X) _Generic((X) + 0, \
    int: m_mod_src_deregister_fd, \
    char *: m_mod_ps_unsubscribe, \
    m_src_tmr_t *: m_mod_src_deregister_tmr, \
    m_src_sgn_t *: m_mod_src_deregister_sgn, \
    m_src_path_t *: m_mod_src_deregister_path, \
    m_src_pid_t *: m_mod_src_deregister_pid, \
    m_src_task_t *: m_mod_src_deregister_task, \
    m_src_thresh_t *: m_mod_src_deregister_thresh \
    )(mod, X)
