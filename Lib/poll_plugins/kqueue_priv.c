#include <poll_priv.h>
#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>

struct kevent pevents[MAX_EVENTS] = {{ 0 }};

int poll_create(void) {
    return kqueue();
}

int poll_set_data(void **_ev, void *p) {
    *ev = malloc(sizeof(struct kevent));
    return MOD_OK;
}

int poll_set_new_evt(module_poll_t *tmp, m_context *c, enum op_type flag) {
    int f = flag == ADD ? EV_ADD : EV_DELETE;
    struct kevent *_ev = (struct kevent *)tmp->ev;
    EV_SET(_ev, tmp->fd, EVFILT_READ, f, 0, 0, (void *)tmp);
    return kevent(c->fd, _ev, 1, NULL, 0, NULL);
}

int poll_wait(int fd, int num_fds) {
    return kevent(fd, pevents, num_fds, NULL, 0, NULL);
}

module_poll_t *poll_recv(int idx) {
    return (module_poll_t *)pevents[idx].udata;
}
