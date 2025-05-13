
/*
 * Generic /dev/nvram driver for architectures providing some
 * "generic" hooks, that is :
 *
 * nvram_read_byte, nvram_write_byte, nvram_sync, nvram_get_size
 *
 * Note that an additional hook is supported for PowerMac only
 * for getting the nvram "partition" informations
 *
 */

#include <pthread.h>
#include <linux/types.h>

extern _Bool __VERIFIER_nondet_bool(void);
extern char __VERIFIER_nondet_char(void);
extern uint __VERIFIER_nondet_uint(void);
extern int __VERIFIER_nondet_int(void);
extern ulong __VERIFIER_nondet_ulong(void);
extern long __VERIFIER_nondet_long(void);

extern void __VERIFIER_atomic_begin(void);

extern void __VERIFIER_atomic_end(void);

extern void abort(void); 
#include <assert.h>
void reach_error() { assert(0); }

extern void abort(void); 
void assume_abort_if_not(int cond) { 
  if(!cond) {abort();}
}

void __VERIFIER_assert(int cond) {
  if (!(cond)) {
    ERROR: {reach_error();abort();}
  }
  return;
}

#define NVRAM_VERSION "1.1"

#include <linux/module.h>

#include <linux/types.h>
#include <linux/errno.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/fcntl.h>
#include <linux/init.h>
#include <linux/mutex.h>
#include <linux/uaccess.h>
#include <linux/errno.h>
#include <linux/list.h>

/* Signatures for nvram partitions */
#define NVRAM_SIG_SP	0x02	/* support processor */
#define NVRAM_SIG_OF	0x50	/* open firmware config */
#define NVRAM_SIG_FW	0x51	/* general firmware */
#define NVRAM_SIG_HW	0x52	/* hardware (VPD) */
#define NVRAM_SIG_FLIP	0x5a	/* Apple flip/flop header */
#define NVRAM_SIG_APPL	0x5f	/* Apple "system" (???) */
#define NVRAM_SIG_SYS	0x70	/* system env vars */
#define NVRAM_SIG_CFG	0x71	/* config data */
#define NVRAM_SIG_ELOG	0x72	/* error log */
#define NVRAM_SIG_VEND	0x7e	/* vendor defined */
#define NVRAM_SIG_FREE	0x7f	/* Free space */
#define NVRAM_SIG_OS	0xa0	/* OS defined */
#define NVRAM_SIG_PANIC	0xa1	/* Apple OSX "panic" */


/* PowerMac specific nvram stuffs */

enum {
	pmac_nvram_OF,		/* Open Firmware partition */
	pmac_nvram_XPRAM,	/* MacOS XPRAM partition */
	pmac_nvram_NR		/* MacOS Name Registry partition */
};


/* Some offsets in XPRAM */
#define PMAC_XPRAM_MACHINE_LOC	0xe4
#define PMAC_XPRAM_SOUND_VOLUME	0x08

/* Machine location structure in PowerMac XPRAM */
struct pmac_machine_location {
	unsigned int	latitude;	/* 2+30 bit Fractional number */
	unsigned int	longitude;	/* 2+30 bit Fractional number */
	unsigned int	delta;		/* mix of GMT delta and DLS */
};

/*
* /dev/nvram ioctls
*
* Note that PMAC_NVRAM_GET_OFFSET is still supported, but is
* definitely obsolete. Do not use it if you can avoid it
*/

#define OBSOLETE_PMAC_NVRAM_GET_OFFSET \
_IOWR('p', 0x40, int)

#define IOC_NVRAM_GET_OFFSET	_IOWR('p', 0x42, int)	/* Get NVRAM partition offset */
#define IOC_NVRAM_SYNC		_IO('p', 0x43)		/* Sync NVRAM image */

#ifdef CONFIG_PPC_PSERIES
extern int nvram_write_error_log(char * buff, int length,
					 unsigned int err_type, unsigned int err_seq);
extern int nvram_read_error_log(char * buff, int length,
					 unsigned int * err_type, unsigned int *err_seq);
extern int nvram_clear_error_log(void);
extern int pSeries_nvram_init(void);
#endif /* CONFIG_PPC_PSERIES */

#ifdef CONFIG_MMIO_NVRAM
extern int mmio_nvram_init(void);
#else
static inline int mmio_nvram_init(void)
{
	return -ENODEV;
}
#endif

extern int __init nvram_scan_partitions(void);
extern loff_t nvram_create_partition(const char *name, int sig,
				     int req_size, int min_size);
extern int nvram_remove_partition(const char *name, int sig,
					const char *exceptions[]);
extern int nvram_get_partition_size(loff_t data_index);
extern loff_t nvram_find_partition(const char *name, int sig, int *out_size);

/* Return partition offset in nvram */
extern int	pmac_get_partition(int partition);

/* Direct access to XPRAM on PowerMacs */
extern u8	pmac_xpram_read(int xpaddr);
extern void	pmac_xpram_write(int xpaddr, u8 data);

/* Synchronize NVRAM */
extern void	nvram_sync(void);

/* Determine NVRAM size */
extern ssize_t nvram_get_size(void);

/* Normal access to NVRAM */
extern unsigned char nvram_read_byte(int i);
extern void nvram_write_byte(unsigned char c, int i);
#ifdef CONFIG_PPC_PMAC
#include <asm/machdep.h>
#endif

const unsigned int default_alloc_size = 4;

// Function: external_alloc
// with type: void *external_alloc(unsigned int size)
// with return type: void *
void *external_alloc(unsigned int size)
{
  char *p = malloc(size);
  for(unsigned i = 0; i < size; ++i)
    p[i] = __VERIFIER_nondet_char();
  return p;
}

// Function: __bit_spin_unlock
// with type: void __bit_spin_unlock(int, unsigned long *)
// with return type: void
void __bit_spin_unlock(int arg0, unsigned long *arg1) {
  // Void type
  return;
}

// Function: __get_user
// with type: int __get_user(int size, const void *ptr)
// with return type: int
int __VERIFIER_nondet_int(void);
int __get_user(int arg0, const void *arg1) {
  // Simple type
  return __VERIFIER_nondet_int();
}

// Function: __iter_div_u64_rem
// with type: u32 __iter_div_u64_rem(u64 , u32 , u64 *)
// with return type: u32 
unsigned int __VERIFIER_nondet_uint(void);
u32 __iter_div_u64_rem(u64 arg0, u32 arg1, u64 *arg2) {
  // Typedef type
  // Real type: unsigned int
  // Simple type
  return __VERIFIER_nondet_uint();
}

// Function: __put_user
// with type: int __put_user(int size, void *ptr)
// with return type: int
int __VERIFIER_nondet_int(void);
int __put_user(int arg0, void *arg1) {
  // Simple type
  return __VERIFIER_nondet_int();
}

// Function: __tty_alloc_driver
// with type: struct tty_driver *__tty_alloc_driver(unsigned int lines, struct module *owner, unsigned long flags)
// with return type: (struct tty_driver)*
void *external_alloc(unsigned int size);
struct tty_driver *__tty_alloc_driver(unsigned int arg0, struct module *arg1, unsigned long arg2) {
  // Pointer type
  return (struct tty_driver *)external_alloc(sizeof(struct tty_driver));
}

// Function: access_ok
// with type: int access_ok(int type, const void *addr, unsigned long size)
// with return type: int
int __VERIFIER_nondet_int(void);
int access_ok(int arg0, const void *arg1, unsigned long arg2) {
  // Simple type
  return __VERIFIER_nondet_int();
}

// Function: atomic_add_unless
// with type: int atomic_add_unless(atomic_t *v, int a, int u)
// with return type: int
int __VERIFIER_nondet_int(void);
int atomic_add_unless(atomic_t *arg0, int arg1, int arg2) {
  // Simple type
  return __VERIFIER_nondet_int();
}

// Function: barrier
// with type: void barrier()
// with return type: void
void barrier() {
  // Void type
  return;
}

// Function: bit_spin_is_locked
// with type: bool bit_spin_is_locked(int, unsigned long *)
// with return type: bool 
bool __VERIFIER_nondet_bool(void);
bool bit_spin_is_locked(int arg0, unsigned long *arg1) {
  // Typedef type
  // Real type: _Bool
  // Simple type
  return __VERIFIER_nondet_bool();
}

// Function: bit_spin_lock
// with type: void bit_spin_lock(int, unsigned long *)
// with return type: void
void bit_spin_lock(int arg0, unsigned long *arg1) {
  // Void type
  return;
}

// Function: clear_bit
// with type: void clear_bit(long nr, volatile unsigned long *addr)
// with return type: void
void clear_bit(long arg0, volatile unsigned long *arg1) {
  // Void type
  return;
}

// Function: cpu_relax
// with type: void cpu_relax()
// with return type: void
void cpu_relax() {
  // Void type
  return;
}

// Function: current_kernel_time
// with type: struct timespec current_kernel_time()
// with return type: struct timespec
void *external_alloc(unsigned int size);
struct timespec current_kernel_time() {
  // Composite type
  struct timespec *tmp = (struct timespec*)external_alloc(sizeof(struct timespec));
  assume_abort_if_not(tmp != 0);
  return *tmp;
}

// Function: d_instantiate
// with type: void d_instantiate(struct dentry *, struct inode *)
// with return type: void
void d_instantiate(struct dentry *arg0, struct inode *arg1) {
  // Void type
  return;
}

// Function: d_instantiate_unique
// with type: struct dentry *d_instantiate_unique(struct dentry *, struct inode *)
// with return type: (struct dentry)*
void *external_alloc(unsigned int size);
struct dentry *d_instantiate_unique(struct dentry *arg0, struct inode *arg1) {
  // Pointer type
  return (struct dentry *)external_alloc(sizeof(struct dentry));
}

// Function: d_rehash
// with type: void d_rehash(struct dentry *)
// with return type: void
void d_rehash(struct dentry *arg0) {
  // Void type
  return;
}

// Function: dev_get_drvdata
// with type: void *dev_get_drvdata(struct device *dev)
// with return type: (void)*
void *external_alloc(unsigned int size);
void *dev_get_drvdata(struct device *arg0) {
  // Pointer type
  return (void *)external_alloc(sizeof(default_alloc_size));
}

// Function: dev_set_drvdata
// with type: void dev_set_drvdata(struct device *dev, void *data)
// with return type: void
void dev_set_drvdata(struct device *arg0, void *arg1) {
  // Void type
  return;
}

// Function: ida_get_new_above
// with type: int ida_get_new_above(struct ida *ida, int starting_id, int *p_id)
// with return type: int
int __VERIFIER_nondet_int(void);
int ida_get_new_above(struct ida *arg0, int arg1, int *arg2) {
  // Simple type
  return __VERIFIER_nondet_int();
}

// Function: idr_find_slowpath
// with type: void *idr_find_slowpath(struct idr *idp, int id)
// with return type: (void)*
void *external_alloc(unsigned int size);
void *idr_find_slowpath(struct idr *arg0, int arg1) {
  // Pointer type
  return (void *)external_alloc(sizeof(default_alloc_size));
}

// Function: kobject_get
// with type: struct kobject *kobject_get(struct kobject *kobj)
// with return type: (struct kobject)*
void *external_alloc(unsigned int size);
struct kobject *kobject_get(struct kobject *arg0) {
  // Pointer type
  return (struct kobject *)external_alloc(sizeof(struct kobject));
}

// Function: kobject_put
// with type: void kobject_put(struct kobject *kobj)
// with return type: void
void kobject_put(struct kobject *arg0) {
  // Void type
  return;
}

// Function: llist_add_batch
// with type: bool llist_add_batch(struct llist_node *new_first, struct llist_node *new_last, struct llist_head *head)
// with return type: bool 
bool __VERIFIER_nondet_bool(void);
bool llist_add_batch(struct llist_node *arg0, struct llist_node *arg1, struct llist_head *arg2) {
  // Typedef type
  // Real type: _Bool
  // Simple type
  return __VERIFIER_nondet_bool();
}

// Function: local_irq_restore
// with type: void local_irq_restore(unsigned long)
// with return type: void
void local_irq_restore(unsigned long arg0) {
  // Void type
  return;
}

// Function: misc_deregister
// with type: int misc_deregister(struct miscdevice *misc)
// with return type: int
int __VERIFIER_nondet_int(void);
int misc_deregister(struct miscdevice *arg0) {
  // Simple type
  return __VERIFIER_nondet_int();
}

// Function: misc_register
// with type: int misc_register(struct miscdevice *misc)
// with return type: int
int __VERIFIER_nondet_int(void);
int misc_register(struct miscdevice *arg0) {
  // Simple type
  return __VERIFIER_nondet_int();
}

// Function: mm_tlb_flush_pending
// with type: bool mm_tlb_flush_pending(struct mm_struct *mm)
// with return type: bool 
bool __VERIFIER_nondet_bool(void);
bool mm_tlb_flush_pending(struct mm_struct *arg0) {
  // Typedef type
  // Real type: _Bool
  // Simple type
  return __VERIFIER_nondet_bool();
}

// Function: nvram_get_size
// with type: ssize_t nvram_get_size()
// with return type: ssize_t 
long __VERIFIER_nondet_long(void);
ssize_t nvram_get_size() {
  // Typedef type
  // Real type: __kernel_ssize_t 
  // Typedef type
  // Real type: __kernel_long_t 
  // Typedef type
  // Real type: long
  // Simple type
  return __VERIFIER_nondet_long();
}

// Function: nvram_read_byte
// with type: unsigned char nvram_read_byte(int i)
// with return type: unsigned char
unsigned char __VERIFIER_nondet_uchar(void);
unsigned char nvram_read_byte(int arg0) {
  // Simple type
  return __VERIFIER_nondet_uchar();
}

// Function: nvram_sync
// with type: void nvram_sync()
// with return type: void
void nvram_sync() {
  // Void type
  return;
}

// Function: nvram_write_byte
// with type: void nvram_write_byte(unsigned char c, int i)
// with return type: void
void nvram_write_byte(unsigned char arg0, int arg1) {
  // Void type
  return;
}

// Function: page_to_phys
// with type: dma_addr_t page_to_phys(struct page *)
// with return type: dma_addr_t 
unsigned int __VERIFIER_nondet_uint(void);
dma_addr_t page_to_phys(struct page *arg0) {
  // Typedef type
  // Real type: u32 
  // Typedef type
  // Real type: unsigned int
  // Simple type
  return __VERIFIER_nondet_uint();
}

// Function: printk
// with type: int printk(const char *fmt, ...)
// with return type: int
int __VERIFIER_nondet_int(void);
int printk(const char *arg0, ...) {
  // Simple type
  return __VERIFIER_nondet_int();
}

// Skip function: pthread_create

// Skip function: pthread_join

// Function: rcu_dereference_check
// with type: void *rcu_dereference_check(void *, int)
// with return type: (void)*
void *external_alloc(unsigned int size);
void *rcu_dereference_check(void *arg0, int arg1) {
  // Pointer type
  return (void *)external_alloc(sizeof(default_alloc_size));
}

// Function: rcu_dereference_raw
// with type: void *rcu_dereference_raw(void *)
// with return type: (void)*
void *external_alloc(unsigned int size);
void *rcu_dereference_raw(void *arg0) {
  // Pointer type
  return (void *)external_alloc(sizeof(default_alloc_size));
}

// Function: set_normalized_timespec
// with type: void set_normalized_timespec(struct timespec *ts, time_t sec, s64 nsec)
// with return type: void
void set_normalized_timespec(struct timespec *arg0, time_t arg1, s64 arg2) {
  // Void type
  return;
}

// Function: smp_mb
// with type: void smp_mb()
// with return type: void
void smp_mb() {
  // Void type
  return;
}

// Function: smp_rmb
// with type: void smp_rmb()
// with return type: void
void smp_rmb() {
  // Void type
  return;
}

// Function: timespec_trunc
// with type: struct timespec timespec_trunc(struct timespec t, unsigned gran)
// with return type: struct timespec
void *external_alloc(unsigned int size);
void assume_abort_if_not(int);
struct timespec timespec_trunc(struct timespec arg0, unsigned arg1) {
  // Composite type
  struct timespec *tmp = (struct timespec*)external_alloc(sizeof(struct timespec));
  assume_abort_if_not(tmp != 0);
  return *tmp;
}

// Function: tty_lock
// with type: void tty_lock(struct tty_struct *tty)
// with return type: void
void tty_lock(struct tty_struct *arg0) {
  // Void type
  return;
}

// Function: tty_termios_baud_rate
// with type: speed_t tty_termios_baud_rate(struct ktermios *termios)
// with return type: speed_t 
unsigned int __VERIFIER_nondet_uint(void);
speed_t tty_termios_baud_rate(struct ktermios *arg0) {
  // Typedef type
  // Real type: unsigned int
  // Simple type
  return __VERIFIER_nondet_uint();
}

// Function: tty_unlock
// with type: void tty_unlock(struct tty_struct *tty)
// with return type: void
void tty_unlock(struct tty_struct *arg0) {
  // Void type
  return;
}

// Function: tty_wait_until_sent
// with type: void tty_wait_until_sent(struct tty_struct *tty, long timeout)
// with return type: void
void tty_wait_until_sent(struct tty_struct *arg0, long arg1) {
  // Void type
  return;
}



#define NVRAM_SIZE	8192

static DEFINE_MUTEX(nvram_mutex);
static ssize_t nvram_len;

loff_t nvram_llseek(struct file *file, loff_t offset, int origin)
{
	switch (origin) {
	case 0:
		break;
	case 1:
		offset += file->f_pos;
		break;
	case 2:
		offset += nvram_len;
		break;
	default:
		offset = -1;
	}
	if (offset < 0)
		return -EINVAL;

	file->f_pos = offset;
	__VERIFIER_assert(file->f_pos == offset);

	return file->f_pos;
}

ssize_t read_nvram(struct file *file, char __user *buf,
			  size_t count, loff_t *ppos)
{
	unsigned int i;
	char __user *p = buf;

	if (!access_ok(VERIFY_WRITE, buf, count))
		return -EFAULT;
	if (*ppos >= nvram_len)
		return 0;
	for (i = *ppos; count > 0 && i < nvram_len; ++i, ++p, --count)
		if (__put_user(nvram_read_byte(i), p))
			return -EFAULT;
	*ppos = i;
	__VERIFIER_assert(*ppos == i);

	return p - buf;
}

ssize_t write_nvram(struct file *file, const char __user *buf,
			   size_t count, loff_t *ppos)
{
	unsigned int i;
	const char __user *p = buf;
	char c = __VERIFIER_nondet_char();

	if (!access_ok(VERIFY_READ, buf, count))
		return -EFAULT;
	if (*ppos >= nvram_len)
		return 0;
	for (i = *ppos; count > 0 && i < nvram_len; ++i, ++p, --count) {
		if (__get_user(c, p))
			return -EFAULT;
		nvram_write_byte(c, i);
	}
	*ppos = i;
	__VERIFIER_assert(*ppos == i);

	return p - buf;
}

static int nvram_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	switch(cmd) {
#ifdef CONFIG_PPC_PMAC
	case OBSOLETE_PMAC_NVRAM_GET_OFFSET:
		printk(KERN_WARNING "nvram: Using obsolete PMAC_NVRAM_GET_OFFSET ioctl\n");
	case IOC_NVRAM_GET_OFFSET: {
		int part, offset;

		if (!machine_is(powermac))
			return -EINVAL;
		if (copy_from_user(&part, (void __user*)arg, sizeof(part)) != 0)
			return -EFAULT;
		if (part < pmac_nvram_OF || part > pmac_nvram_NR)
			return -EINVAL;
		offset = pmac_get_partition(part);
		if (copy_to_user((void __user*)arg, &offset, sizeof(offset)) != 0)
			return -EFAULT;
		break;
	}
#endif /* CONFIG_PPC_PMAC */
	case IOC_NVRAM_SYNC:
		nvram_sync();
		break;
	default:
		return -EINVAL;
	}

	return 0;
}

long nvram_unlocked_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	int ret;

	mutex_lock(&nvram_mutex);
	ret = nvram_ioctl(file, cmd, arg);
	mutex_unlock(&nvram_mutex);

	return ret;
}

struct file_operations nvram_fops = {
	.owner		= THIS_MODULE,
	.llseek		= nvram_llseek,
	.read		= read_nvram,
	.write		= write_nvram,
	.unlocked_ioctl	= nvram_unlocked_ioctl,
};

static struct miscdevice nvram_dev = {
	NVRAM_MINOR,
	"nvram",
	&nvram_fops
};

int __init nvram_init(void)
{
	int ret = 0;

	printk(KERN_INFO "Generic non-volatile memory driver v%s\n",
		NVRAM_VERSION);
	ret = misc_register(&nvram_dev);
	if (ret != 0)
		goto out;

	nvram_len = nvram_get_size();
	if (nvram_len < 0)
		nvram_len = NVRAM_SIZE;

out:
	return ret;
}

void __exit nvram_cleanup(void)
{
        misc_deregister( &nvram_dev );
}

module_init(nvram_init);
module_exit(nvram_cleanup);

// Declare values needed by entry point wrappers
struct inode *whoop_inode_0;
struct file *whoop_file_0;
struct inode *whoop_inode_1;
struct file *whoop_file_1;
struct inode *whoop_inode_2;
struct file *whoop_file_2;
struct inode *whoop_inode_3;
struct file *whoop_file_3;
struct inode *whoop_inode_4;
struct file *whoop_file_4;
struct pci_dev *whoop_pci_dev;
char *whoop_buf;
struct platform_device *whoop_platform_device;
struct vm_area_struct *whoop_vm_area_struct;
struct cx_dev *whoop_cx_dev;

poll_table *whoop_poll_table;

loff_t *whoop_loff_t;
int whoop_int;

// Pthread wrappers for entry points
void *whoop_wrapper_write_nvram(void* args)
{
	write_nvram(whoop_file_0, whoop_buf, whoop_int, whoop_loff_t);
	return NULL;
}

void *whoop_wrapper_read_nvram(void* args)
{
	read_nvram(whoop_file_1, whoop_buf, whoop_int, whoop_loff_t);
	return NULL;
}

void *whoop_wrapper_nvram_unlocked_ioctl(void* args)
{
	nvram_unlocked_ioctl(whoop_file_2, whoop_int, whoop_int);
	return NULL;
}

void *whoop_wrapper_nvram_llseek(void* args)
{
	nvram_llseek(whoop_file_3, __VERIFIER_nondet_long(), whoop_int);
	return NULL;
}

void *whoop_wrapper_nvram_cleanup(void* args)
{
	nvram_cleanup();
	return NULL;
}

int main(void)
{
	// Instantiate values required by entry points
	whoop_inode_0 = (struct inode *) malloc(sizeof(struct inode));
	whoop_file_0 = (struct file *) malloc(sizeof(struct file));
	whoop_inode_1 = (struct inode *) malloc(sizeof(struct inode));
	whoop_file_1 = (struct file *) malloc(sizeof(struct file));
	whoop_inode_2 = (struct inode *) malloc(sizeof(struct inode));
	whoop_file_2 = (struct file *) malloc(sizeof(struct file));
	whoop_inode_3 = (struct inode *) malloc(sizeof(struct inode));
	whoop_file_3 = (struct file *) malloc(sizeof(struct file));
	whoop_inode_4 = (struct inode *) malloc(sizeof(struct inode));
	whoop_file_4 = (struct file *) malloc(sizeof(struct file));
	whoop_pci_dev = (struct pci_dev *) malloc(sizeof(struct pci_dev));
	whoop_buf = (char *) malloc(sizeof(char));
	whoop_platform_device = (struct platform_device *) malloc(sizeof(struct platform_device));
	whoop_vm_area_struct = (struct vm_area_struct *) malloc(sizeof(struct vm_area_struct));
	whoop_cx_dev = (struct cx_dev *) malloc(sizeof(struct cx_dev));

	whoop_poll_table = (poll_table *) malloc(sizeof(poll_table));

	whoop_loff_t = (loff_t *) malloc(sizeof(loff_t));
	whoop_int = __VERIFIER_nondet_int();
	assume_abort_if_not(whoop_int >= 0);

	// Call module_init function
	int _whoop_init_result = _whoop_init();

	// Declare pthread_t's
	pthread_t pthread_t_read_nvram;
	pthread_t pthread_t_nvram_llseek;

	// Create pthread threads
	pthread_create(&pthread_t_read_nvram, NULL, whoop_wrapper_read_nvram, NULL);
	pthread_create(&pthread_t_nvram_llseek, NULL, whoop_wrapper_nvram_llseek, NULL);

	// Wait for threads to finish
	pthread_join(pthread_t_read_nvram, NULL);
	pthread_join(pthread_t_nvram_llseek, NULL);

}
