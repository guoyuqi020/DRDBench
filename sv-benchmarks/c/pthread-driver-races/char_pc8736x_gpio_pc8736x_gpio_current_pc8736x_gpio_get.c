
/* linux/drivers/char/pc8736x_gpio.c

   National Semiconductor PC8736x GPIO driver.  Allows a user space
   process to play with the GPIO pins.

   Copyright (c) 2005,2006 Jim Cromie <jim.cromie@gmail.com>

   adapted from linux/drivers/char/scx200_gpio.c
   Copyright (c) 2001,2002 Christer Weinigel <wingel@nano-system.com>,
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

#include <linux/fs.h>
#include <linux/module.h>
#include <linux/errno.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/io.h>
#include <linux/ioport.h>
#include <linux/mutex.h>
#include <linux/nsc_gpio.h>
#include <linux/platform_device.h>
#include <linux/uaccess.h>

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

// Function: __release_region
// with type: void __release_region(struct resource *, resource_size_t , resource_size_t )
// with return type: void
void __release_region(struct resource *arg0, resource_size_t arg1, resource_size_t arg2) {
  // Void type
  return;
}

// Function: __request_region
// with type: struct resource *__request_region(struct resource *, resource_size_t start, resource_size_t n, const char *name, int flags)
// with return type: (struct resource)*
void *external_alloc(unsigned int size);
struct resource *__request_region(struct resource *arg0, resource_size_t arg1, resource_size_t arg2, const char *arg3, int arg4) {
  // Pointer type
  return (struct resource *)external_alloc(sizeof(struct resource));
}

// Function: __tty_alloc_driver
// with type: struct tty_driver *__tty_alloc_driver(unsigned int lines, struct module *owner, unsigned long flags)
// with return type: (struct tty_driver)*
void *external_alloc(unsigned int size);
struct tty_driver *__tty_alloc_driver(unsigned int arg0, struct module *arg1, unsigned long arg2) {
  // Pointer type
  return (struct tty_driver *)external_alloc(sizeof(default_alloc_size));
}

// Function: alloc_chrdev_region
// with type: int alloc_chrdev_region(dev_t *, unsigned, unsigned, const char *)
// with return type: int
int __VERIFIER_nondet_int(void);
int alloc_chrdev_region(dev_t *arg0, unsigned arg1, unsigned arg2, const char *arg3) {
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

// Function: cdev_add
// with type: int cdev_add(struct cdev *, dev_t , unsigned)
// with return type: int
int __VERIFIER_nondet_int(void);
int cdev_add(struct cdev *arg0, dev_t arg1, unsigned arg2) {
  // Simple type
  return __VERIFIER_nondet_int();
}

// Function: cdev_del
// with type: void cdev_del(struct cdev *)
// with return type: void
void cdev_del(struct cdev *arg0) {
  // Void type
  return;
}

// Function: cdev_init
// with type: void cdev_init(struct cdev *, struct file_operations *)
// with return type: void
void cdev_init(struct cdev *arg0, struct file_operations *arg1) {
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

// Function: inb_p
// with type: unsigned char inb_p(unsigned int)
// with return type: unsigned char
unsigned char __VERIFIER_nondet_uchar(void);
unsigned char inb_p(unsigned int arg0) {
  // Simple type
  return __VERIFIER_nondet_uchar();
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

// Function: nonseekable_open
// with type: int nonseekable_open(struct inode *inode, struct file *filp)
// with return type: int
int __VERIFIER_nondet_int(void);
int nonseekable_open(struct inode *arg0, struct file *arg1) {
  // Simple type
  return __VERIFIER_nondet_int();
}

// Function: outb_p
// with type: void outb_p(unsigned char value, unsigned int)
// with return type: void
void outb_p(unsigned char arg0, unsigned int arg1) {
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

// Function: platform_device_add
// with type: int platform_device_add(struct platform_device *pdev)
// with return type: int
int __VERIFIER_nondet_int(void);
int platform_device_add(struct platform_device *arg0) {
  // Simple type
  return __VERIFIER_nondet_int();
}

// Function: platform_device_alloc
// with type: struct platform_device *platform_device_alloc(const char *name, int id)
// with return type: (struct platform_device)*
void *external_alloc(unsigned int size);
struct platform_device *platform_device_alloc(const char *arg0, int arg1) {
  // Pointer type
  return (struct platform_device *)external_alloc(sizeof(struct platform_device));
}

// Function: platform_device_del
// with type: void platform_device_del(struct platform_device *pdev)
// with return type: void
void platform_device_del(struct platform_device *arg0) {
  // Void type
  return;
}

// Function: platform_device_put
// with type: void platform_device_put(struct platform_device *pdev)
// with return type: void
void platform_device_put(struct platform_device *arg0) {
  // Void type
  return;
}

// Function: platform_device_unregister
// with type: void platform_device_unregister(struct platform_device *)
// with return type: void
void platform_device_unregister(struct platform_device *arg0) {
  // Void type
  return;
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

// Function: register_chrdev_region
// with type: int register_chrdev_region(dev_t , unsigned, const char *)
// with return type: int
int __VERIFIER_nondet_int(void);
int register_chrdev_region(dev_t arg0, unsigned arg1, const char *arg2) {
  // Simple type
  return __VERIFIER_nondet_int();
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

// Skip function: snprintf

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

// Function: unregister_chrdev_region
// with type: void unregister_chrdev_region(dev_t , unsigned)
// with return type: void
void unregister_chrdev_region(dev_t arg0, unsigned arg1) {
  // Void type
  return;
}



#define DEVNAME "pc8736x_gpio"

static int major;		/* default to dynamic major */

static DEFINE_MUTEX(pc8736x_gpio_config_lock);
static unsigned pc8736x_gpio_base;
static u8 pc8736x_gpio_shadow[4];

#define SIO_BASE1       0x2E	/* 1st command-reg to check */
#define SIO_BASE2       0x4E	/* alt command-reg to check */

#define SIO_SID		0x20	/* SuperI/O ID Register */
#define SIO_SID_PC87365	0xe5	/* Expected value in ID Register for PC87365 */
#define SIO_SID_PC87366	0xe9	/* Expected value in ID Register for PC87366 */

#define SIO_CF1		0x21	/* chip config, bit0 is chip enable */

#define PC8736X_GPIO_RANGE	16 /* ioaddr range */
#define PC8736X_GPIO_CT		32 /* minors matching 4 8 bit ports */

#define SIO_UNIT_SEL	0x7	/* unit select reg */
#define SIO_UNIT_ACT	0x30	/* unit enable */
#define SIO_GPIO_UNIT	0x7	/* unit number of GPIO */
#define SIO_VLM_UNIT	0x0D
#define SIO_TMS_UNIT	0x0E

/* config-space addrs to read/write each unit's runtime addr */
#define SIO_BASE_HADDR		0x60
#define SIO_BASE_LADDR		0x61

/* GPIO config-space pin-control addresses */
#define SIO_GPIO_PIN_SELECT	0xF0
#define SIO_GPIO_PIN_CONFIG     0xF1
#define SIO_GPIO_PIN_EVENT      0xF2

static unsigned char superio_cmd = 0;
static unsigned char selected_device = 0xFF;	/* bogus start val */

/* GPIO port runtime access, functionality */
static int port_offset[] = { 0, 4, 8, 10 };	/* non-uniform offsets ! */
/* static int event_capable[] = { 1, 1, 0, 0 };   ports 2,3 are hobbled */

#define PORT_OUT	0
#define PORT_IN		1
#define PORT_EVT_EN	2
#define PORT_EVT_STST	3

static struct platform_device *pdev;  /* use in dev_*() */

static inline void superio_outb(int addr, int val)
{
	outb_p(addr, superio_cmd);
	outb_p(val, superio_cmd + 1);
}

static inline int superio_inb(int addr)
{
	outb_p(addr, superio_cmd);
	return inb_p(superio_cmd + 1);
}

static int pc8736x_superio_present(void)
{
	int id;

	/* try the 2 possible values, read a hardware reg to verify */
	superio_cmd = SIO_BASE1;
	id = superio_inb(SIO_SID);
	if (id == SIO_SID_PC87365 || id == SIO_SID_PC87366)
		return superio_cmd;

	superio_cmd = SIO_BASE2;
	id = superio_inb(SIO_SID);
	if (id == SIO_SID_PC87365 || id == SIO_SID_PC87366)
		return superio_cmd;

	return 0;
}

static void device_select(unsigned devldn)
{
	superio_outb(SIO_UNIT_SEL, devldn);
	selected_device = devldn;
}

static void select_pin(unsigned iminor)
{
	/* select GPIO port/pin from device minor number */
	device_select(SIO_GPIO_UNIT);
	superio_outb(SIO_GPIO_PIN_SELECT,
		     ((iminor << 1) & 0xF0) | (iminor & 0x7));
}

static inline u32 pc8736x_gpio_configure_fn(unsigned index, u32 mask, u32 bits,
					    u32 func_slct)
{
	u32 config, new_config;

	mutex_lock(&pc8736x_gpio_config_lock);

	device_select(SIO_GPIO_UNIT);
	select_pin(index);

	/* read current config value */
	config = superio_inb(func_slct);

	/* set new config */
	new_config = (config & mask) | bits;
	superio_outb(func_slct, new_config);

	mutex_unlock(&pc8736x_gpio_config_lock);

	return config;
}

u32 pc8736x_gpio_configure(unsigned index, u32 mask, u32 bits)
{
	return pc8736x_gpio_configure_fn(index, mask, bits,
					 SIO_GPIO_PIN_CONFIG);
}

int pc8736x_gpio_get(unsigned minor)
{
	int port, bit, val;

	minor &= 0x1f;
	port = minor >> 3;
	bit = minor & 7;
	val = inb_p(pc8736x_gpio_base + port_offset[port] + PORT_IN);
	val >>= bit;
	val &= 1;

	dev_dbg(&pdev->dev, "_gpio_get(%d from %x bit %d) == val %d\n",
		minor, pc8736x_gpio_base + port_offset[port] + PORT_IN, bit,
		val);

	return val;
}

void pc8736x_gpio_set(unsigned minor, int val)
{
	int port, bit, curval;

	minor &= 0x1f;
	port = minor >> 3;
	bit = minor & 7;
	curval = inb_p(pc8736x_gpio_base + port_offset[port] + PORT_OUT);

	dev_dbg(&pdev->dev, "addr:%x cur:%x bit-pos:%d cur-bit:%x + new:%d -> bit-new:%d\n",
		pc8736x_gpio_base + port_offset[port] + PORT_OUT,
		curval, bit, (curval & ~(1 << bit)), val, (val << bit));

	val = (curval & ~(1 << bit)) | (val << bit);

	dev_dbg(&pdev->dev, "gpio_set(minor:%d port:%d bit:%d)"
		" %2x -> %2x\n", minor, port, bit, curval, val);

	outb_p(val, pc8736x_gpio_base + port_offset[port] + PORT_OUT);

	curval = inb_p(pc8736x_gpio_base + port_offset[port] + PORT_OUT);
	val = inb_p(pc8736x_gpio_base + port_offset[port] + PORT_IN);

	dev_dbg(&pdev->dev, "wrote %x, read: %x\n", curval, val);
	pc8736x_gpio_shadow[port] = val;
	__VERIFIER_assert(pc8736x_gpio_shadow[port] == val);
}

int pc8736x_gpio_current(unsigned minor)
{
	int port, bit;
	minor &= 0x1f;
	port = minor >> 3;
	bit = minor & 7;
        u8 tmp = pc8736x_gpio_shadow[port];
        __VERIFIER_assert(tmp == pc8736x_gpio_shadow[port]);
	return ((tmp >> bit) & 0x01);
}

void pc8736x_gpio_change(unsigned index)
{
	pc8736x_gpio_set(index, !pc8736x_gpio_current(index));
}

static struct nsc_gpio_ops pc8736x_gpio_ops = {
	.owner		= THIS_MODULE,
	.gpio_config	= pc8736x_gpio_configure,
	.gpio_dump	= nsc_gpio_dump,
	.gpio_get	= pc8736x_gpio_get,
	.gpio_set	= pc8736x_gpio_set,
	.gpio_change	= pc8736x_gpio_change,
	.gpio_current	= pc8736x_gpio_current
};

int pc8736x_gpio_open(struct inode *inode, struct file *file)
{
	unsigned m = iminor(inode);
	file->private_data = &pc8736x_gpio_ops;
	__VERIFIER_assert(file->private_data == &pc8736x_gpio_ops);


	dev_dbg(&pdev->dev, "open %d\n", m);

	if (m >= PC8736X_GPIO_CT)
		return -EINVAL;
	return nonseekable_open(inode, file);
}

static struct file_operations pc8736x_gpio_fileops = {
	.owner	= THIS_MODULE,
	.open	= pc8736x_gpio_open,
	.write	= nsc_gpio_write,
	.read	= nsc_gpio_read,
	.llseek = no_llseek,
};

static void __init pc8736x_init_shadow(void)
{
	int port;

	/* read the current values driven on the GPIO signals */
	for (port = 0; port < 4; ++port)
		pc8736x_gpio_shadow[port]
		    = inb_p(pc8736x_gpio_base + port_offset[port]
			    + PORT_OUT);

}

static struct cdev pc8736x_gpio_cdev;

int __init pc8736x_gpio_init(void)
{
	int rc;
	dev_t devid;

	pdev = platform_device_alloc(DEVNAME, 0);
	if (!pdev)
		return -ENOMEM;

	rc = platform_device_add(pdev);
	if (rc) {
		rc = -ENODEV;
		goto undo_platform_dev_alloc;
	}
	dev_info(&pdev->dev, "NatSemi pc8736x GPIO Driver Initializing\n");

	if (!pc8736x_superio_present()) {
		rc = -ENODEV;
		dev_err(&pdev->dev, "no device found\n");
		goto undo_platform_dev_add;
	}
	pc8736x_gpio_ops.dev = &pdev->dev;
        __VERIFIER_assert(pc8736x_gpio_ops.dev == &pdev->dev);

	/* Verify that chip and it's GPIO unit are both enabled.
	   My BIOS does this, so I take minimum action here
	 */
	rc = superio_inb(SIO_CF1);
	if (!(rc & 0x01)) {
		rc = -ENODEV;
		dev_err(&pdev->dev, "device not enabled\n");
		goto undo_platform_dev_add;
	}
	device_select(SIO_GPIO_UNIT);
	if (!superio_inb(SIO_UNIT_ACT)) {
		rc = -ENODEV;
		dev_err(&pdev->dev, "GPIO unit not enabled\n");
		goto undo_platform_dev_add;
	}

	/* read the GPIO unit base addr that chip responds to */
	pc8736x_gpio_base = (superio_inb(SIO_BASE_HADDR) << 8
			     | superio_inb(SIO_BASE_LADDR));

	if (!request_region(pc8736x_gpio_base, PC8736X_GPIO_RANGE, DEVNAME)) {
		rc = -ENODEV;
		dev_err(&pdev->dev, "GPIO ioport %x busy\n",
			pc8736x_gpio_base);
		goto undo_platform_dev_add;
	}
	dev_info(&pdev->dev, "GPIO ioport %x reserved\n", pc8736x_gpio_base);

	if (major) {
		devid = MKDEV(major, 0);
		rc = register_chrdev_region(devid, PC8736X_GPIO_CT, DEVNAME);
	} else {
		rc = alloc_chrdev_region(&devid, 0, PC8736X_GPIO_CT, DEVNAME);
		major = MAJOR(devid);
	}

	if (rc < 0) {
		dev_err(&pdev->dev, "register-chrdev failed: %d\n", rc);
		goto undo_request_region;
	}
	if (!major) {
		major = rc;
		dev_dbg(&pdev->dev, "got dynamic major %d\n", major);
	}

	pc8736x_init_shadow();

	/* ignore minor errs, and succeed */
	cdev_init(&pc8736x_gpio_cdev, &pc8736x_gpio_fileops);
	cdev_add(&pc8736x_gpio_cdev, devid, PC8736X_GPIO_CT);

	return 0;

undo_request_region:
	release_region(pc8736x_gpio_base, PC8736X_GPIO_RANGE);
undo_platform_dev_add:
	platform_device_del(pdev);
undo_platform_dev_alloc:
	platform_device_put(pdev);

	return rc;
}

void __exit pc8736x_gpio_cleanup(void)
{
	dev_dbg(&pdev->dev, "cleanup\n");

	cdev_del(&pc8736x_gpio_cdev);
	unregister_chrdev_region(MKDEV(major,0), PC8736X_GPIO_CT);
	release_region(pc8736x_gpio_base, PC8736X_GPIO_RANGE);

	platform_device_unregister(pdev);
}

module_init(pc8736x_gpio_init);
module_exit(pc8736x_gpio_cleanup);

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
struct inode *whoop_inode_5;
struct file *whoop_file_5;
struct inode *whoop_inode_6;
struct file *whoop_file_6;
struct pci_dev *whoop_pci_dev;
const char *whoop_buf;
struct platform_device *whoop_platform_device;
struct vm_area_struct *whoop_vm_area_struct;
struct cx_dev *whoop_cx_dev;

poll_table *whoop_poll_table;

loff_t *whoop_loff_t;
int whoop_int;

// Pthread wrappers for entry points
void *whoop_wrapper_pc8736x_gpio_set(void* args)
{
	pc8736x_gpio_set(whoop_int, whoop_int);
	return NULL;
}

void *whoop_wrapper_pc8736x_gpio_open(void* args)
{
	pc8736x_gpio_open(whoop_inode_1, whoop_file_1);
	return NULL;
}

void *whoop_wrapper_pc8736x_gpio_get(void* args)
{
	pc8736x_gpio_get(whoop_int);
	return NULL;
}

void *whoop_wrapper_pc8736x_gpio_current(void* args)
{
	pc8736x_gpio_current(whoop_int);
	return NULL;
}

void *whoop_wrapper_pc8736x_gpio_configure(void* args)
{
	pc8736x_gpio_configure(whoop_int, whoop_int, whoop_int);
	return NULL;
}

void *whoop_wrapper_pc8736x_gpio_cleanup(void* args)
{
	pc8736x_gpio_cleanup();
	return NULL;
}

void *whoop_wrapper_pc8736x_gpio_change(void* args)
{
	pc8736x_gpio_change(whoop_int);
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
	whoop_inode_5 = (struct inode *) malloc(sizeof(struct inode));
	whoop_file_5 = (struct file *) malloc(sizeof(struct file));
	whoop_inode_6 = (struct inode *) malloc(sizeof(struct inode));
	whoop_file_6 = (struct file *) malloc(sizeof(struct file));
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
	pthread_t pthread_t_pc8736x_gpio_get;
	pthread_t pthread_t_pc8736x_gpio_current;

	// Create pthread threads
	pthread_create(&pthread_t_pc8736x_gpio_get, NULL, whoop_wrapper_pc8736x_gpio_get, NULL);
	pthread_create(&pthread_t_pc8736x_gpio_current, NULL, whoop_wrapper_pc8736x_gpio_current, NULL);

	// Wait for threads to finish
	pthread_join(pthread_t_pc8736x_gpio_get, NULL);
	pthread_join(pthread_t_pc8736x_gpio_current, NULL);

}
