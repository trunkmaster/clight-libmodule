#include "test_commons.h"

void test_module_register_NULL_name(void **state);
void test_module_register_NULL_ctx(void **state);
void test_module_register_NULL_self(void **state);
void test_module_register_NULL_hook(void **state);
void test_module_register(void **state);
void test_module_register_already_registered(void **state);
void test_module_register_same_name(void **state);
void test_module_deregister_NULL_self(void **state);
void test_module_deregister(void **state);
void test_module_false_init(void **state);
void test_module_pause_NULL_self(void **state);
void test_module_pause(void **state);
void test_module_resume_NULL_self(void **state);
void test_module_resume(void **state);
void test_module_stop_NULL_self(void **state);
void test_module_stop(void **state);
void test_module_start_NULL_self(void **state);
void test_module_start(void **state);
void test_module_log_NULL_self(void **state);
void test_module_log(void **state);
void test_module_dump_NULL_self(void **state);
void test_module_dump(void **state);
void test_module_set_userdata_NULL_self(void **state);
void test_module_set_userdata(void **state);
void test_module_become_NULL_self(void **state);
void test_module_become_NULL_func(void **state);
void test_module_become(void **state);
void test_module_unbecome_NULL_self(void **state);
void test_module_unbecome(void **state);
void test_module_add_wrong_fd(void **state);
void test_module_add_fd_NULL_self(void **state);
void test_module_add_fd(void **state);
void test_module_rm_wrong_fd(void **state);
void test_module_rm_wrong_fd_2(void **state);
void test_module_rm_fd_NULL_self(void **state);
void test_module_rm_fd(void **state);
void test_module_subscribe_NULL_topic(void **state);
void test_module_subscribe_NULL_self(void **state);
void test_module_subscribe(void **state);
void test_module_ref_NULL_name(void **state);
void test_module_ref_unexhistent_name(void **state);
void test_module_ref_NULL_ref(void **state);
void test_module_ref(void **state);
void test_module_tell_NULL_recipient(void **state);
void test_module_tell_NULL_self(void **state);
void test_module_tell_NULL_msg(void **state);
void test_module_tell_wrong_size(void **state);
void test_module_tell(void **state);
void test_module_publish_NULL_self(void **state);
void test_module_publish_NULL_msg(void **state);
void test_module_publish_NULL_topic(void **state);
void test_module_publish_wrong_size(void **state);
void test_module_publish(void **state);
void test_module_broadcast_NULL_self(void **state);
void test_module_broadcast_NULL_msg(void **state);
void test_module_broadcast_wrong_size(void **state);
void test_module_broadcast(void **state);
