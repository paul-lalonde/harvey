/*
 * This file is part of the UCB release of Plan 9. It is subject to the license
 * terms in the LICENSE file found in the top-level directory of this
 * distribution and at http://akaros.cs.berkeley.edu/files/Plan9License. No
 * part of the UCB release of Plan 9, including this file, may be copied,
 * modified, propagated, or distributed except according to the terms contained
 * in the LICENSE file.
 */

void _assert(char *);
void accounttime(void);
void acsched(void);
void addbootfile(char *, unsigned char *, u32);
Timer *addclock0link(void (*)(void), int);
int addconsdev(Queue *, void (*fn)(char *, int), int, int);
int addkbdq(Queue *, int);
int addphysseg(Physseg *);
void addwaitstat(usize pc, u64 t0, int type);
void addwatchdog(Watchdog *);
int adec(int *);
Block *adjustblock(Block *, int);
int ainc(int *);
void alarmkproc(void *);
Block *allocb(int);
void *alloczio(Segment *, i32);
int anyhigher(void);
int anyready(void);
Image *attachimage(int, Chan *, int, usize, usize);
Page *auxpage(usize);
Block *bl2mem(unsigned char *, Block *, int);
int blocklen(Block *);
void bootlinks(void);
void cachedel(Image *, u32);
void cachepage(Page *, Image *);
void callwithureg(void (*)(Ureg *));
int canlock(Lock *);
int canpage(Proc *);
int canqlock(QLock *);
int canrlock(RWlock *);
Chan *cclone(Chan *);
void cclose(Chan *);
void ccloseq(Chan *);
void chanfree(Chan *);
char *chanpath(Chan *);
void checkalarms(void);
void checkb(Block *, char *);
void clearwaitstats(void);
void closeegrp(Egrp *);
void closefgrp(Fgrp *);
void closepgrp(Pgrp *);
void closergrp(Rgrp *);
void cmderror(Cmdbuf *, char *);
int cmount(Chan **, Chan *, int, char *);
Block *concatblock(Block *);
void confinit(void);
int consactive(void);
void (*consdebug)(void);
void (*consputs)(char *, int);
Block *copyblock(Block *, int);
void copypage(Page *, Page *);
void cunmount(Chan *, Chan *);
Segment *data2txt(Segment *);
usize dbgpc(Proc *);
int checkdc(int dc);
int decrypt(void *, void *, int);
void delay(int);
void delconsdevs(void);
Proc *dequeueproc(Sched *, Schedq *, Proc *);
Chan *devattach(int, char *);
Block *devbread(Chan *, i32, i64);
i32 devbwrite(Chan *, Block *, i64);
Chan *devclone(Chan *);
int devconfig(int, char *, DevConf *);
Chan *devcreate(Chan *, char *, int, int);
void devdir(Chan *, Qid, char *, i64, char *, i32, Dir *);
i32 devdirread(Chan *, char *, i32, Dirtab *, int, Devgen *);
Devgen devgen;
void devinit(void);
Chan *devopen(Chan *, int, Dirtab *, int, Devgen *);
void devpermcheck(char *, int, int);
void devpower(int);
void devremove(Chan *);
void devreset(void);
void devshutdown(void);
i32 devstat(Chan *, unsigned char *, i32, Dirtab *, int, Devgen *);
Dev *devtabget(int, int);
void devtabinit(void);
i32 mtagsread(Chan *, void *, i32, i64);
i32 devtabread(Chan *, void *, i32, i64);
void devtabreset(void);
void devtabshutdown(void);
Walkqid *devwalk(Chan *, Chan *, char **, int, Dirtab *, int, Devgen *);
i32 devwstat(Chan *, unsigned char *, i32);
int devzread(Chan *, Kzio *, int, usize, i64);
int devzwrite(Chan *, Kzio *, int, i64);
void drawactive(int);
void drawcmap(void);
void dumpaproc(Proc *);
void dumpregs(Ureg *);
void dumpstack(void);
void dumpzseg(Segment *);
Fgrp *dupfgrp(Fgrp *);
int duppage(Page *);
Segment *dupseg(Segment **, int, int);
void dupswap(Page *);
char *edfadmit(Proc *);
void edfinit(Proc *);
int edfready(Proc *);
void edfrecord(Proc *);
void edfrun(Proc *, int);
void edfstop(Proc *);
void edfyield(void);
int elf64ldseg(Chan *c, usize *entryp, Ldseg **rp, char *mach,
	       u32 minpgsz);
int emptystr(char *);
int encrypt(void *, void *, int);
void envcpy(Egrp *, Egrp *);
int eqchanddq(Chan *, int, u32, Qid, int);
int eqqid(Qid, Qid);
void error(char *);
char *errno2str(u32);
void exhausted(char *);
void exit(int);
u64 fastticks(u64 *);
u64 fastticks2ns(u64);
u64 fastticks2us(u64);
int fault(usize, usize, int);
void fdclose(int, int);
Chan *fdtochan(int, int, int, int);
int findmount(Chan **, Mhead **, int, u32, Qid);
int fixfault(Segment *, usize, int, int, int);
void fmtinit(void);
void forceclosefgrp(void);
void fortuna_get_bytes(unsigned len, u8 *dst);
void fortuna_add_entropy(const u8 *data, unsigned len);
void free(void *);
void freeb(Block *);
void freeblist(Block *);
int freebroken(void);
void freepte(Segment *, Pte *);
void getcolor(u32, u32 *, u32 *, u32 *);
char *getconfenv(void);
int getpgszi(usize);
Segment *getzkseg(void);
void gotolabel(Label *);
int haswaitq(void *);
void hexdump(void *v, int length);
void pahexdump(usize pa, int len);
void hnputl(void *, u32);
void hnputs(void *, u16);
void hnputv(void *, u64);
i32 hostdomainwrite(char *, i32);
i32 hostownerwrite(char *, i32);
void hzsched(void);
Block *iallocb(int);
void iallocsummary(void);
void initmark(Watermark *, int, char *);
void ilock(Lock *);
void initimage(void);
int iprint(char *, ...);
void isdir(Chan *);
int iseve(void);
int islo(void);
Segment *isoverlap(Proc *, usize, usize);
int isphysseg(char *);
void iunlock(Lock *);
void ixsummary(void);
int kbdcr2nl(Queue *, int);
int kbdgetmap(int, int *, int *, Rune *);
int kbdputc(Queue *, int);
void kbdputmap(u16, u16, Rune);
void initDeadKeys();
void kdbputdeadkey(Rune deadkey, Rune basekey, Rune finalkey);
void kickpager(int, int);
void killbig(char *);
int kmprint(char *, ...);
void kproc(char *, void (*)(void *), void *);
void kprocchild(Proc *, void (*)(void *), void *);
void (*kproftimer)(usize);
void ksetenv(char *, char *, int);
void kstrcpy(char *, char *, int);
void kstrdup(char **, char *);
i32 latin1(Rune *, int);
int lock(Lock *);
void log(Log *, int, char *, ...);
void logclose(Log *);
char *logctl(Log *, int, char **, Logflag *);
void logn(Log *, int, void *, int);
void logopen(Log *);
i32 logread(Log *, void *, i32, i64);
Page *lookpage(Image *, u32);
Cmdtab *lookupcmd(Cmdbuf *, Cmdtab *, int);
void mallocinit(void);
i32 mallocreadsummary(Chan *, void *, i32, i32);
void mallocsummary(void);
Block *mem2bl(unsigned char *, int);
void (*mfcinit)(void);
void (*mfcopen)(Chan *);
int (*mfcread)(Chan *, unsigned char *, int, i64);
void (*mfcupdate)(Chan *, unsigned char *, int, i64);
void (*mfcwrite)(Chan *, unsigned char *, int, i64);
void mfreeseg(Segment *, usize, int);
void microdelay(int);
u64 mk64fract(u64, u64);
void mkqid(Qid *, i64, u32, int);
void mmuflush(void);
void mmuprocinit(Proc *);
void mmuput(usize, Page *, u32);
void mmurelease(Proc *);
void mmuswitch(Proc *);
Chan *mntattachversion(char *muxattach, char *version, u8 tag,
		       Chan *(*mntchan)(void));
Chan *mntauth(Chan *, char *);
usize mntversion(Chan *, u32, char *, usize);
void mountfree(Mount *);
u64 ms2fastticks(u32);
#define MS2NS(n) (((i64)(n)) * 1000000LL)
u64 ms2tk(u64);
void mul64fract(u64 *, u64, u64);
void muxclose(Mnt *);
void (*mwait)(void *);
Chan *namec(char *, int, int, int);
void nameerror(char *, char *);
Chan *newchan(void);
int newfd(Chan *);
Mhead *newmhead(Chan *);
Mount *newmount(Mhead *, Chan *, int, char *);
Page *newpage(int, Segment **, usize, usize, int);
Path *newpath(char *);
Pgrp *newpgrp(void);
Proc *newproc(void);
Rgrp *newrgrp(void);
Segment *newseg(int, usize, u64);
void newzmap(Segment *);
void nexterror(void);
void notemark(Watermark *, int);
u32 nhgetl(void *);
u16 nhgets(void *);
u64 nhgetv(void *);
void nixprepage(int);
int nrand(int);
u64 ns2fastticks(u64);
int okaddr(usize, i32, int);
int openmode(int);
Block *packblock(Block *);
Block *padblock(Block *, int);
void pagechainhead(Page *);
void pageinit(void);
u32 pagenumber(Page *);
u64 pagereclaim(Image *);
void pagersummary(void);
void pageunchain(Page *);
void panic(char *, ...);
Cmdbuf *parsecmd(char *a, int n);
void pathclose(Path *);
u64 perfticks(void);
void pexit(char *, int);
Page *pgalloc(usize, int);
void pgfree(Page *);
void pgrpcpy(Pgrp *, Pgrp *);
void pgrpnote(u32, char *, i32, int);
u64 physalloc(u64, int *, void *);
void physdump(void);
void physfree(u64, u64);
void physinit(u64, u64);
void *phystag(u64);
void pio(Segment *, usize, u32, Page **, int);
void portmwait(void *);
int postnote(Proc *, int, char *, int);
int pprint(char *, ...);
int preempted(void);
void prflush(void);
void printinit(void);
u64 procalarm(u64);
void procctl(Proc *);
void procdump(void);
int procfdprint(Chan *, int, int, char *, int);
void procflushseg(Segment *);
void procinit0(void);
void procpriority(Proc *, int, int);
void procrestore(Proc *);
void procsave(Proc *);
void (*proctrace)(Proc *, int, i64);
void proctracepid(Proc *);
void procwired(Proc *, int);
void psdecref(Proc *);
Proc *psincref(int);
int psindex(int);
void psinit(int);
Pte *ptealloc(Segment *);
Pte *ptecpy(Segment *, Pte *);
int pullblock(Block **, int);
Block *pullupblock(Block *, int);
Block *pullupqueue(Queue *, int);
void putimage(Image *);
void putmhead(Mhead *);
void putpage(Page *);
void putseg(Segment *);
void putstrn(char *, int);
void putswap(Page *);
int pwait(Waitmsg *);
void qaddlist(Queue *, Block *);
Block *qbread(Queue *, int);
i32 qbwrite(Queue *, Block *);
i32 qibwrite(Queue *, Block *);
Queue *qbypass(void (*)(void *, Block *), void *);
int qcanread(Queue *);
void qclose(Queue *);
int qconsume(Queue *, void *, int);
Block *qcopy(Queue *, int, u32);
int qdiscard(Queue *, int);
void qflush(Queue *);
void qfree(Queue *);
int qfull(Queue *);
Block *qget(Queue *);
void qhangup(Queue *, char *);
int qisclosed(Queue *);
int qiwrite(Queue *, void *, int);
int qlen(Queue *);
void qlock(QLock *);
void qnoblock(Queue *, int);
Queue *qopen(int, int, void (*)(void *), void *);
int qpass(Queue *, Block *);
int qpassnolim(Queue *, Block *);
int qproduce(Queue *, void *, int);
void qputback(Queue *, Block *);
i32 qread(Queue *, void *, int);
Block *qremove(Queue *);
void qreopen(Queue *);
void qsetlimit(Queue *, int);
void qunlock(QLock *);
int qwindow(Queue *);
int qwrite(Queue *, void *, int);
int rand(void);
u32 randomread(void *, u32);
u32 urandomread(void *, u32);
void rdb(void);
int readnum(u32, char *, u32, u32, int);
i32 readstr(i32, char *, i32, char *);
i32 readmem(i32, void *, i32, void *, i32);
void ready(Proc *);
i32 readzio(Kzio[], int, void *, i32);
void reboot(void *, void *, i32);
void rebootcmd(int, char **);
void relocateseg(Segment *, usize);
void renameuser(char *, char *);
void resched(char *);
void resrcwait(char *);
int return0(void *);
void rlock(RWlock *);
i32 rtctime(void);
int runac(Mach *m, void (*func)(void), int flushtlb, void *a, i32 n);
void runlock(RWlock *);
Proc *runproc(void);
void sched(void);
void scheddump(void);
void schedinit(void);
i32 seconds(void);
Segment *seg(Proc *, usize, int);
void segclock(usize);
void segpage(Segment *, Page *);
char *seprintmark(char *, char *, Watermark *);
u64 segppn(Segment *, u64);
int semadec(int *);
int semainc(int *);
char *seprintpagestats(char *, char *);
char *seprintphysstats(char *, char *);
int setcolor(u32, u32, u32, u32);
void setkernur(Ureg *, Proc *);
// The horror. But, well, it does make a BIG performance difference. We're told.
int slim_setlabel(Label *);
void setregisters(Ureg *, char *, char *, int);
char *skipslash(char *);
void sleep(Rendez *, int (*)(void *), void *);
void *smalloc(u32);
char *srvname(Chan *);
void startwaitstats(int);
int swapcount(u32);
void swapinit(void);
void syscallfmt(u8, int, Ar0 *, u64, u64, ...);
void sysrforkchild(Proc *, Proc *);
void timeradd(Timer *);
void timerdel(Timer *);
void timerintr(Ureg *, i64);
void timerset(u64);
void timersinit(void);
#define TK2MS(x) ((x) * (1000 / HZ))
u64 tod2fastticks(i64);
i64 todget(i64 *);
void todinit(void);
void todset(i64, i64, int);
void todsetfreq(i64);
Block *trimblock(Block *, int, int);
void tsleep(Rendez *, int (*)(void *), void *, i64);
Uart *uartconsole(int, char *);
int uartctl(Uart *, char *);
int uartgetc(void);
void uartkick(void *);
void uartputc(int);
void uartputs(char *, int);
void uartrecv(Uart *, char);
int uartstageoutput(Uart *);
void unbreak(Proc *);
void uncachepage(Page *);
i32 unionread(Chan *, void *, i32);
void unlock(Lock *);
void userinit(void);
usize userpc(Ureg *);
i32 userwrite(char *, i32);
void *validaddr(void *, i32, int);
void validname(char *, int);
char *validnamedup(char *, int);
void validstat(unsigned char *, usize);
void *vmemchr(const void *, int, u32);
Proc *wakeup(Rendez *);
int walk(Chan **, char **, int, int, int *);
void wlock(RWlock *);
void wunlock(RWlock *);
void yield(void);
usize zgetaddr(Segment *);
void zgrow(Segment *);
int ziofmt(Fmt *);
int zputaddr(Segment *, usize);
u32 ms(void);

//#pragma		varargck	argpos	iprint		1
//#pragma		varargck	argpos	panic		1
//#pragma		varargck	argpos	pprint		1

/* profiling. */
void oprofile_control_trace(int onoff);
int oprofread(void *va, int n);
void oprof_alarm_handler(Ureg *u);
void oprofile_add_backtrace(usize pc, usize fp);
void oprofile_add_userpc(usize pc);
int alloc_cpu_buffers(void);

#define I_AM_HERE print("Core 0 is in %s() at %s:%d\n", \
			__FUNCTION__, __FILE__, __LINE__);
