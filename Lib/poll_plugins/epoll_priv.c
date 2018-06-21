#include <poll_priv.h>
#include <sys/epoll.h>

int poll_create(void) {
    return epoll_create1(EPOLL_CLOEXEC);
}

int poll_set_data(void **_ev, void *p) {
    *_ev = malloc(sizeof(struct epoll_event));
    MOD_ASSERT(*_ev, "Failed to malloc", MOD_ERR);
    struct epoll_event *ev = (struct epoll_event *)*_ev;

    ev->data.ptr = p;
    ev->events = EPOLLIN;
    return MOD_OK;
}

int poll_set_new_evt(module_poll_t *tmp, m_context *c, enum op_type flag) {
    int f = flag == ADD ? EPOLL_CTL_ADD : EPOLL_CTL_DEL;
    return epoll_ctl(c->fd, f, tmp->fd, (struct epoll_event *)tmp->ev);
}

int poll_init_pevents(void **pevents, int max_events) {
    *pevents = memhook._calloc(max_events, sizeof(struct epoll_event));
    if (*pevents) {
        return MOD_OK;
    }
    return MOD_ERR;
}

int poll_wait(int fd, int max_events, void *pevents) {
    return epoll_wait(fd, (struct epoll_event *)pevents, max_events, -1);
}

module_poll_t *poll_recv(int idx, void *pevents) {
    struct epoll_event *pev = (struct epoll_event *) pevents;
    return (module_poll_t *)pev[idx].data.ptr;
}

int poll_destroy_pevents(void **pevents, int *max_events) {
    memhook._free(*pevents);
    *pevents = NULL;
    *max_events = 0;
}

int poll_close(int fd, void **pevents, int *max_events) {
    poll_destroy_pevents(pevents, max_events);
    return close(fd);
}
