#ifndef __i386_UACCESS_H
#define __i386_UACCESS_H

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

/*
 * User space memory access functions
 */
// #include <linux/config.h>
#include <linux/errno.h>
#include <linux/string.h>
// #include <asm/page.h>

#define VERIFY_READ 0
#define VERIFY_WRITE 1


int access_ok(int type, const void *addr, unsigned long size);
int __get_user(int size, const void *ptr);
int get_user(int size, void *ptr);
int __put_user(int size, void *ptr);
int put_user(int size, void *ptr);

unsigned long copy_to_user(void __user *to, const void *from, unsigned long n)
{
  return (unsigned long)__VERIFIER_nondet_ulong();
}

unsigned long copy_from_user(void *to, void __user *from, unsigned long n)
{
  return (unsigned long)__VERIFIER_nondet_ulong();
}

#endif /* __i386_UACCESS_H */
