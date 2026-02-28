
#include <linux/sched/signal.h>
#include <linux/syscalls.h>
SYSCALL_DEFINE0(get_task_count)
{
	struct task_struct *task;
	int count = 0;
	for_each_process(task)
		count++;
	return count;
}
