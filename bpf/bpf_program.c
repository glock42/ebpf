#include <linux/bpf.h>
#include <stdint.h>
#include <stdio.h>
#define SEC(NAME) __attribute__((section(NAME), used))

#ifndef memcmp
# define memcmp(dest, src, n)   __builtin_memcmp((dest), (src), (n))
#endif

#define MAX_LEN 26

static int (*bpf_trace_printk)(const char *fmt, int fmt_size,
                               ...) = (void *)BPF_FUNC_trace_printk;

static int (*bpf_fusionfs_crc32)(const char *data, size_t size) 
                                    = (void *)BPF_FUNC_fusionfs_crc32;

static int (*bpf_jiffies64)() = (void *) BPF_FUNC_jiffies64;
uint32_t crc32_for_byte(uint32_t r) {
    for(int j = 0; j < 8; ++j)
        r = (r & 1? 0: (uint32_t)0xEDB88320L) ^ r >> 1;
    return r ^ (uint32_t)0xFF000000L;

}
struct bpf_args {
    unsigned long long unused;
    char buf[MAX_LEN];
    int off;
    int count;
};
#if 0
//SEC("tracepoint/syscalls/sys_enter_execve")
SEC("tracepoint/myprot/myprot_port")
int bpf_prog(struct bpf_args *ctx) {
    //char msg[26];
    char msg[] = "crc: %d";
    int res = 0;
    int crc_result = 0;
    uint32_t* crc = &res;
    size_t n_bytes = ctx->count;
    uint32_t table[0x100];
    if(!*table)
        for(size_t i = 0; i < 0x100; ++i)
            table[i] = crc32_for_byte(i);
    for(size_t i = 0; i < n_bytes; ++i) {
        *crc = table[(uint8_t)*crc ^ ((uint8_t*)ctx->buf)[i]] ^ *crc >> 8;
    }
    crc_result = bpf_fusionfs_crc32(msg, 10);
    bpf_trace_printk(msg, sizeof(msg), crc_result);
    return 1;
}
#endif

SEC("tracepoint/myprot/myprot_port")
int leveldb_read_chksm(struct bpf_args *ctx) {
    char msg[] = "crc: %d";
    uint32_t nlb = 0;
    uint32_t crc = 0;
    uint32_t target_crc = *(uint32_t *)(ctx->buf);
    const uint32_t a = (uint32_t)(((char * ) ctx->buf)[4]) & 0xff;
    const uint32_t b = (uint32_t)(((char * ) ctx->buf)[5]) & 0xff;
    const uint32_t length = a | (b << 8);
    nlb = length;
    crc = bpf_fusionfs_crc32(ctx->buf, nlb);
    bpf_trace_printk(msg, sizeof(msg), crc);
    return crc == target_crc;
}


char _license[] SEC("license") = "GPL";
