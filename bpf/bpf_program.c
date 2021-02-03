#include <linux/bpf.h>
#include <stdint.h>
#include <stdio.h>
#define SEC(NAME) __attribute__((section(NAME), used))

static int (*bpf_trace_printk)(const char *fmt, int fmt_size,
                               ...) = (void *)BPF_FUNC_trace_printk;
uint32_t crc32_for_byte(uint32_t r) {
    for(int j = 0; j < 8; ++j)
        r = (r & 1? 0: (uint32_t)0xEDB88320L) ^ r >> 1;
    return r ^ (uint32_t)0xFF000000L;

}
struct bpf_args {
    unsigned long long unused;
    char buf[26];
    int off;
    int count;
};
//SEC("tracepoint/syscalls/sys_enter_execve")
SEC("tracepoint/myprot/myprot_port")
int bpf_prog(struct bpf_args *ctx) {
    //char msg[26];
    char msg[] = "Hello world";
    int res = 0;
    uint32_t* crc = &res;
    size_t n_bytes = ctx->count;
    uint32_t table[0x100];
    if(!*table)
        for(size_t i = 0; i < 0x100; ++i)
            table[i] = crc32_for_byte(i);
    for(size_t i = 0; i < n_bytes; ++i) {
        *crc = table[(uint8_t)*crc ^ ((uint8_t*)ctx->buf)[i]] ^ *crc >> 8;
    }
    bpf_trace_printk(msg, sizeof(msg));
    return 1;
}

char _license[] SEC("license") = "GPL";
