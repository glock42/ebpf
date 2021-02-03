// test_tp.h
#undef TRACE_SYSTEM
#define TRACE_SYSTEM myprot

#if !defined(_TEST_TRACE_H) || defined(TRACE_HEADER_MULTI_READ)
#define _TEST_TRACE_H
#include <linux/tracepoint.h>

TRACE_EVENT(myprot_port,
    TP_PROTO(int off, int count),
    TP_ARGS(off, count),
    TP_STRUCT__entry(
        __field(int, off)
        __field(int, count)
    ),
TP_fast_assign(
    __entry->off = off;
    __entry->count = count;
),

TP_printk("off: %d, count: %d", __entry->off, __entry->count)
);

#endif

#undef TRACE_INCLUDE_PATH
#define TRACE_INCLUDE_PATH .
#define TRACE_INCLUDE_FILE test_tp 
#include <trace/define_trace.h>
