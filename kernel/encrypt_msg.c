#include <linux/syscalls.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/errno.h>

SYSCALL_DEFINE2(encrypt_msg, char __user *, buf, size_t, len)
{
	char *kbuf;
	size_t i;
	if (len == 0 || len > 1024)
		return -EINVAL;
	kbuf = kmalloc(len, GFP_KERNEL);
	if (!kbuf)
		return -ENOMEM;
	if (copy_from_user(kbuf, buf, len)) {
		kfree(kbuf);
		return -EFAULT;
	}
	for (i = 0; i < len; i++) {
		if (kbuf[i] >= 'a' && kbuf[i] <= 'z')
			kbuf[i] = ((kbuf[i] - 'a' + 3) % 26) + 'a';
		else if (kbuf[i] >= 'A' && kbuf[i] <= 'Z')
			kbuf[i] = ((kbuf[i] - 'A' + 3) % 26) + 'A';
	}
	if (copy_to_user(buf, kbuf, len)) {
		kfree(kbuf);
		return -EFAULT;
	}
	kfree(kbuf);
	return len;
}
