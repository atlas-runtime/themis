#ifndef SGX_FUNCS_H
#define SGX_FUNCS_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>
//extern int stdin, stdout, stderr;
#include "sgx_structs.h"
#include "sgx_includes.h"
//extern int stdin, stdout, stderr;
#include "sgx_structs.h"
char *fgets(char *str, int n, FILE *fd);
//size_t ocall_fwrite(const FILE *buffer, size_t size, size_t cont, int *fd);
size_t fwrite(const void *buffer, size_t size, size_t cont, FILE *fd);
int fflush(FILE *ptr);
char *getenv(const char *name);
int fputs(const char *str, FILE *stream);
int fprintf(FILE *file, const char *fmt, ...);
char *getenv(const char *name);
long int clock();
long int time(long int *src);
char *strcpy(char *strDest, const char *strSrc);
struct lconv *localeconv(void);
FILE *fopen(const char *filename, const char *mode);
void exit(int status);
char *setlocale(int category, const char *locale);
int system(const char *str);
long int mktime(void *timeptr);
int remove(const char* filename);
void *localtime(const long int *timer);
void *localtime_r(const long int *, void *);
struct tm *gmtime(const long int *timer);
int rename(const char *old_filename, const char *new_filename);
char *tmpnam(char *str);
int fclose(FILE *fd);
int setvbuf(FILE *stream, char *buffer, int mode, size_t size);
long int ftell(FILE *stream);
int fseek(FILE *stream, long int offset, int whence);
FILE *tmpfile(void);
void clearerr(FILE *stream);
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
int ferror(FILE *stream);
int getc(FILE *stream);
int ungetc(int ch, FILE *stream);
FILE *freopen(const char *filename, const char *mode, FILE *stream);
int feof(FILE *stream);
int rand(void);
void srand(unsigned int seed);
int sprintf(char *str, const char *string,...); 
int fscanf(FILE *stream, const char *format, ...);
int printf(const char *format, ...);
int putchar(int a);
char *strcat(char *dst, const char *src);
void print_num(size_t s);
int putc(int c, FILE *f);
int puts(const char *p);
int strcmp(const char *str1, const char *str2);
int memcmp(const void *s1, const void *s2, size_t n);
void perror(const char *p);
FILE *popen(const char *command, const char *type);
int pclose(FILE *stream);
int dup(int);
int nanosleep(const struct timespec *req, struct timespec *rem);
int pipe(int fd[2]);
int chdir (const char *);
int execv(const char *p, char *const arg[]);
int execvp(const char *p, char *const arg[]);
int waitpid(int i, int *info, int opt);
int kill(int p, int sig);
int _exit(int a);
int dup2(int o, int n);
long sysconf(int n);
int fork(void);
int utimes(const char *f, const struct timeval[2]);
int closedir(void *dir);
void *readdir(DIR *l);
void *opendir(const char *t);
size_t readlink(const char *r, char *b, size_t l);
int symlink(const char *t, const char *l);
int lstat(const char *p, void *s);
int stat(const char *p, void *s);
size_t read(int, void *, size_t);
size_t write(int , void *, size_t);
char *getcwd(char *, size_t);
int mkdir(const char *, int);
int clock_gettime(clockid_t i, struct timespec *tp);
char *realpath(const char *rn, const char *r);
int ioctl(int, unsigned long, struct winsize *);
long lseek(int , long, int);
int pclose(FILE *);
FILE *popen(const char *, const char *);
int close(int);
int open(const char *, int, int);
long ftello(FILE *);
int fileno(FILE *);
int fseeko(FILE *, long o, int w);
int fgetc(FILE *);
int fputc(int , FILE *);
FILE *fdopen(int, const char *p);
int dlclose(void *);
void *dlopen(const char *, int);
void *dlsym(void *, const char *);
int gettimeofday(struct timeval *tv, void *tz);
void randombytes(unsigned char *a, unsigned char b);
char *strdup(char *);
char *get_module_code(const char *name);
void append_results(const char *);

#define dlmalloc_usable_size(p) malloc_usable_size(p)
#ifdef __cplusplus
}
#endif

#endif

