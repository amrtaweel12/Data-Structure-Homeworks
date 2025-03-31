#include <stddef.h>
#include "../include/process.h"

Process create_process(int pid, int nice) {
    if (nice < -20) nice = -20;
    if (nice > 19) nice = 19;

    Process p = {
        .pid = pid,
        .vruntime = 0,
        .nice = nice,
        .is_running = false
    };

    return p;
}

void update_vruntime(Process* process, int execution_time) {
    if (process == NULL || execution_time <= 0) {
        return;
    }


    int nice_factor = process->nice + 21;

    process->vruntime += execution_time * nice_factor;
}