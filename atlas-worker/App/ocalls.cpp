#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <sys/time.h>
#include "sgx_urts.h"
#include "Enclave_u.h"
#include "sgx_tcrypto.h"
#include <errno.h>
#include <locale.h>
#include <dlfcn.h>
#include <time.h>
#include <sys/types.h>
#include <dirent.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>

#define RED   "\x1B[31m"   
#define GRN   "\x1B[32m"   
#define YELLOW   "\x1B[33m"   
#define BLUE   "\x1B[34m"   
#define MAGEnTA   "\x1B[35m"   
#define CYAN   "\x1B[36m"   
#define WHITE   "\x1B[37m"   
#define RESET "\x1B[0m"    

char *
ocall_setlocale(int category, const char *locale)
{
    return setlocale(category, locale);
}

void
ocall_exit(int status)
{
    exit(status);
}

long int
ocall_clock()
{
    return clock();
}

long int
ocall_time(long int *src)
{
    return time(src);
}

char *
ocall_getenv(const char *name)
{
    return getenv(name);
}

int
ocall_write(int file, const void *buf, uint32_t size)
{
   return (int)write(file, buf, size);
}

int
ocall_fputs(const char *str, FILE *fd)
{
    return fputs(str, fd);
}

size_t
ocall_fwrite(const void *buffer, size_t size, size_t count, FILE *fd)
{
    return fwrite(buffer, size, count, fd);
}

char *recover_filename(FILE *fd);

char *
ocall_fgets(char *str, int n, FILE *fd)
{
#if defined(DEBUG)
    printf(RED "FGETS: stream  |%s|\n" RESET, recover_filename(fd));
#endif
   
    return fgets(str, n, fd);
}

int
ocall_fflush(FILE *ptr)
{
    return fflush(ptr);
}

struct lconv *
ocall_localeconv()
{
    return localeconv();
}

FILE *
ocall_fopen(const char *filename, const char *mode)
{
#if defined(DEBUG)
    printf(YELLOW "FOPEN: opening %s with mode %s\n" RESET, filename, mode);
#endif
    return fopen(filename, mode); 
}	


FILE *
ocall_fdopen(int a, const char *mode)
{
    return fdopen(a, mode); 
}	

FILE *
ocall_popen(const char *cmd, const char *type)
{
    return popen(cmd, type);
}

int
ocall_pclose(FILE *stream)
{
    return pclose(stream);

}

int
ocall_system(const char *str)
{
    int a;
    a = system(str);
    (void)a;
    return 0;
}

long int
ocall_mktime(struct tm *timeptr)
{
    return mktime(timeptr);
}

int
ocall_remove(const char *filename)
{
    return remove(filename);
}


void *
ocall_localtime_r(const long int *timer, void* res)
{
    return localtime_r(timer, (struct tm *)res);
}

void *
ocall_localtime(const long int *timer)
{
    return localtime(timer);
}

struct tm *
ocall_gmtime(const long int *timer)
{
    return gmtime(NULL);
}

int
ocall_fclose(FILE *ptr)
{
    return fclose(ptr);
}

int
ocall_setvbuf(FILE *stream, char *buffer, int mode, size_t size)
{
    return setvbuf(stream, buffer, mode, size);
}

long int
ocall_ftell(FILE *stream)
{
    return ftell(stream);
}

int
ocall_fseek(FILE *stream, long int offset, int whence)
{
    return fseek(stream, offset, whence);
}

void
ocall_clearerr(FILE *stream)
{
    clearerr(stream);
}

char *
recover_filename(FILE *f)
{
  int fd;
  char fd_path[255];
  char * filename = (char *)malloc(255);
  size_t n;

  fd = fileno(f);
  sprintf(fd_path, "/proc/self/fd/%d", fd);
  n = readlink(fd_path, filename, 255);
  if (n < 0)
      return NULL;
  filename[n] = '\0';
  return filename;
}

#if 0
char *
mfread(size_t *res, size_t size, size_t nmemb, FILE *stream)
{	
#if defined(DEBUG)
    printf(RED "FREAD: opening %s %zd %zd\n" RESET, recover_filename(stream), size, nmemb);
    //printf(RED "FREAD: character:|%s|\n" RESET, ((char *)ptr));
#endif
	void *bla = malloc(size * nmemb);
    *res = fread(bla, 1, size * nmemb, stream);
	return bla;
}
#endif


size_t
ocall_fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
{	
	size_t res;
#if defined(DEBUG)
    printf(RED "FREAD: opening %s %zd %zd\n" RESET, recover_filename(stream), size, nmemb);
    //printf(RED "FREAD: character:|%s|\n" RESET, ((char *)ptr));
#endif
    res = fread(ptr, 1, size * nmemb, stream);
	return res;
}

int
ocall_ferror(FILE *stream)
{
    return ferror(stream);
}


int
ocall_getc(FILE *stream)
{
    int res;
    res = getc(stream);
    //if(run_locally == 1)
    //    fseek(stream, 0, SEEK_SET);
#if defined(DEBUG)
    printf(GRN "GETC: stream  |%s|\n" RESET, recover_filename(stream));
    printf(GRN "GETC: opening |%d|->|%c|\n" RESET, res, (char)res);
#endif
    return res;
}

int
ocall_ungetc(int ch, FILE *stream)
{
    int res;
    res = ungetc(ch, stream);
#if defined(DEBUG)
    printf(CYAN "UNGETC: stream  |%s|\n" RESET, recover_filename(stream));
    printf(CYAN "UNGETC: opening |%d|->|%c|\n" RESET, res, (char)res);
#endif
    return res;
}

FILE *
ocall_freopen(const char *filename, const char *mode, FILE *stream)
{
#if defined(DEBUG)
    printf(GRN "FREOPEN: stream  |%s|\n" RESET, filename);
#endif
    return freopen(filename, mode, stream);
}

int
ocall_feof(FILE *stream)
{
#if defined(DEBUG)
    printf(CYAN "FEOF: stream  |%s|\n" RESET, recover_filename(stream));
#endif

    return feof(stream);
}

int
ocall_rand()
{   
    return rand();
}

/* 
 * random ocall function
 */
void
ocall_srand(unsigned int seed)
{
    srand(seed);

}

/*
 * ocall from lua function that prints numbers on stdout
 */
void
ocall_print_num(size_t s)
{
    fprintf(stdout, "%zd", s);
}

void *
ocall_dlopen(const char *fmt, int flags)
{
    return dlopen(fmt, flags);
}

int
ocall_dlclose(void *handle)
{
    return dlclose(handle);
}

int
ocall_close(int a) {
    return close(a);
}

long ocall_sysconf(int n) {
    return sysconf(n);
}

int ocall_chdir(const char *path) {
    return chdir(path);

}

int ocall_closedir(void *dir) {
    return closedir((DIR *)dir);
}

void *ocall_opendir(const char *t) {
    return opendir(t);
}

int ocall_symlink(const char *t, const char *l) {
    return symlink(t, l);
}

void *
ocall_dlsym(void *h, const char *s)
{
    return dlsym(h, s);
}

int
ocall_mkdir(const char *l, int m) {
    return mkdir(l, m);
}

int 
ocall_fseeko(FILE *s, long o, int w) {
    return fseeko(s, o, w);
}

int ocall_fileno(FILE *s) {
    return fileno(s);
}

long ocall_ftello(FILE *s) {
    return ftello(s);
}

size_t 
ocall_read(int fd, void *b, size_t c) {
    return read(fd, b, c);
}

size_t 
ocall_write(int fd, void *b, size_t c) {
    return write(fd, b, c);
}

size_t 
ocall_open(int fd, void *b, size_t c) {
    return read(fd, b, c);
}

long ocall_lseek(int f, long o, int w) {
    return lseek(f, o, w);
}

int 
ocall_isatty(int f){
    return isatty(f);
}

char *ocall_getcwd(char *b, size_t s) {
    return ocall_getcwd(b, s);
}

int ocall_signal(int a, void *b){
    return -1;//signal(a, b);
}

int ocall_ioctl(int fd, unsigned long req, struct winsize *ws) {
    return ioctl(fd, req, ws);
}

int ocall_tcgetattr(int f, void *p) {
    return 0;//tcgetattr(f, (struct termios *)p);
}

int ocall_tcsetattr(int f, int oa, const void *p) {
    return 0;//tcsetattr(f, oa, (struct termios*)p);
}

void
ocall_FD_ZERO(void *p) {
    FD_ZERO((fd_set *)p);
}


void
ocall_FD_SET(int fd, void *p) {
    FD_SET(fd, (fd_set *)p);
}

void
ocall_FD_ISSET(int fd, void *p) {
    FD_SET(fd, (fd_set *)p);
}

int ocall_select(int a, void *r, void *w, void *e, void *t) 
{
    (void)a;
    (void)r;
    (void)e;
    (void)t;
    return 0;//select(a, r, w, e, t); 
}

char *
ocall_realpath(const char *path, char *resolved_path)
{
	return realpath(path, resolved_path);
}


int ocall_gettimeofday(struct timeval *p, void *c)
{
    int z = gettimeofday(p, (struct timezone *)c);
    return z;
}

int
ocall_stat(char *p, void *a)
{
    int z;
    z = stat(p, (struct stat *)a);
    return z;
}

int
ocall_clock_gettime(int a, struct timespec *ts)
{
    return clock_gettime((clockid_t)a, ts);
}
