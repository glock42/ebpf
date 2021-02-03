// test_tp.h
#undef TRACE_SYSTEM
#define TRACE_SYSTEM myprot

#if !defined(_TEST_TRACE_H) || defined(TRACE_HEADER_MULTI_READ)
#define _TEST_TRACE_H
#include <linux/tracepoint.h>

TRACE_EVENT(myprot_port,
    TP_PROTO(char *buf, int off, int count, int* table),
    TP_ARGS(buf, off, count, table),
    TP_STRUCT__entry(
        __array(char, buf, 26)
        __field(int, off)
        __field(int, count)
        __array(char, table, 256)
    ),
TP_fast_assign(
    memcpy(__entry->buf, buf, 26);
    __entry->off = off;
    __entry->count = count;
    memcpy(__entry->table, table, 256);
),

TP_printk("buf: %s, off: %d, count: %d, table[0]: %d", __entry->buf, __entry->off, __entry->count, __entry->table[0])
);

#endif

#undef TRACE_INCLUDE_PATH
#define TRACE_INCLUDE_PATH .
#define TRACE_INCLUDE_FILE test_tp 
#include <trace/define_trace.h>
