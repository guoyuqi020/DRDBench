extern int __VERIFIER_nondet_int(void);
extern void abort(void);
#include <assert.h>
void reach_error() { assert(0); }

#include <pthread.h>

/*
to correctly model the cv_broadcast(COND) statement "b1_COND := 1;" must be manually changed to "b1_COND$ := 1;" in the abstract BP
*/

#define assert_nl(e) { if(!(e)) { goto ERROR; } }
#undef assert
#define assert(e) { if(!(e)) { ERROR: {reach_error();abort();}(void)0; } }

#define mutex_enter(m) pthread_mutex_lock(&m); //acquire lock and ensure no other thread unlocked it
#define mutex_exit(m) pthread_mutex_unlock(&m);

pthread_mutex_t MTX = PTHREAD_MUTEX_INITIALIZER;
_Bool COND = 0;
pthread_cond_t CONDVAR = PTHREAD_COND_INITIALIZER;

#define PSWITCH_EVENT_RELEASED 1
#define PENVSYS_EVENT_NORMAL 2
#define POWER_EVENT_RECVDICT 3

inline int sysmon_queue_power_event(){
  assert(1);
	if (__VERIFIER_nondet_int())
		return 0;
	return 1; }

inline int sysmon_get_power_event(){
  assert(1);
	if (__VERIFIER_nondet_int())	
		return 0;
	return 1; }

inline int sysmon_power_daemon_task(){
	if (__VERIFIER_nondet_int()) return __VERIFIER_nondet_int();
	mutex_enter(MTX);
	switch (__VERIFIER_nondet_int()) {
	case PSWITCH_EVENT_RELEASED:
		if (__VERIFIER_nondet_int()) {
			mutex_exit(MTX);
			goto out;}
		break;
	case PENVSYS_EVENT_NORMAL:
		if (__VERIFIER_nondet_int()) {
			mutex_exit(MTX);
			goto out;}
		break;
	default:
		mutex_exit(MTX);
		goto out;}
	sysmon_queue_power_event();
	if (__VERIFIER_nondet_int()) {
		mutex_exit(MTX);
		goto out;} 
	else {
		COND = 1;
		pthread_cond_broadcast(&CONDVAR);
		mutex_exit(MTX);}
	out:
  assert(1);
	return __VERIFIER_nondet_int(); }

inline void sysmonopen_power(){
	mutex_enter(MTX);
	mutex_exit(MTX);
  assert(1);
}

inline void sysmonclose_power(){
	mutex_enter(MTX);
	mutex_exit(MTX);
  assert(1);
}

inline void sysmonread_power(){
	if (__VERIFIER_nondet_int()){
		mutex_enter(MTX);
		for (;;) {
			if (sysmon_get_power_event()) {
				break;}
			if (__VERIFIER_nondet_int()) {
				break;}
			while (!COND) // avoid spurious wakeup
				pthread_cond_wait(&CONDVAR, &MTX);
			assert_nl(COND);
		}
		mutex_exit(MTX); }
  assert(1);
}

inline void sysmonpoll_power(){
	if(__VERIFIER_nondet_int()){
		mutex_enter(MTX);
		mutex_exit(MTX); }
  assert(1);
}

inline void filt_sysmon_power_rdetach(){
	mutex_enter(MTX);
	mutex_exit(MTX);
  assert(1);
}

inline void filt_sysmon_power_read(){
	mutex_enter(MTX);
	mutex_exit(MTX);
  assert(1);
}

inline void sysmonkqfilter_power(){
	mutex_enter(MTX);
	mutex_exit(MTX);
  assert(1);
}

inline void sysmonioctl_power(){
	switch (__VERIFIER_nondet_int()) {
	case POWER_EVENT_RECVDICT:
		mutex_enter(MTX);
		if (__VERIFIER_nondet_int()) {
			mutex_exit(MTX);
			break;}
		mutex_exit(MTX);
		mutex_enter(MTX);
		mutex_exit(MTX);
		break; }
  assert(1);
}

void* thr1(void* arg){
  while(1)
    switch(__VERIFIER_nondet_int()){
    case 0: sysmon_power_daemon_task(); break;
    case 1: sysmonopen_power(); break;
    case 2: sysmonclose_power(); break;
    case 3: sysmonread_power(); break;
    case 4: sysmonpoll_power(); break;
    case 5: filt_sysmon_power_rdetach(); break;
    case 6: filt_sysmon_power_read(); break;
    case 7: sysmonkqfilter_power(); break;
    case 8: sysmonioctl_power(); break; }}

int main(){
  pthread_t t;

  while(1) pthread_create(&t, 0, thr1, 0);
}

