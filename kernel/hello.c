#include <linux/kernel.h>
#include <linux/syscalls.h>

SYSCALL_DEFINE0(hello){
	printk(KERN_INFO "HELLO WORLD\n");
	return 0;
}
