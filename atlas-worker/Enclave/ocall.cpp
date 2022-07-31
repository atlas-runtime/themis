#include <string>
extern "C" {
#include "Enclave_t.h"
#include <stdarg.h>
#include "sgx_includes.h"
#include "sgx_funcs.h"
#include <string.h>
#include <stdio.h>
#include "sgx_tcrypto.h"
#include "sgx_trts.h"

    size_t
    fwrite(const void *buffer, size_t size, size_t cont, FILE *fd)
    {
        size_t res;
        if (fd == stderr) {
            ocall_fwrite(&res, buffer, size, cont, fd);
        }
        return res;
    }

    int
    fprintf(FILE *file, const char* fmt, ...)
    {
        int res;
        res = 0;
        #define BUFSIZE 20000
        char buf[BUFSIZE];
        memset(buf, 0, BUFSIZE);
        va_list ap;
        va_start(ap, fmt);
        vsnprintf(buf, BUFSIZE, fmt, ap);
        va_end(ap);
        res+= (int)fwrite(buf, 1, strlen(buf), file);
        return res;   
    }


    int
    printf(const char* fmt, ...)
    {
        int res;
        res = 0;
        #define BUFSIZE 20000
        char buf[BUFSIZE];
        memset(buf, 0, BUFSIZE);
        va_list ap;
        va_start(ap, fmt);
        vsnprintf(buf, BUFSIZE, fmt, ap);
        va_end(ap);
        res+= (int)fwrite(buf, 1, strlen(buf), stdout);
        return res;   
    }

    int
    putchar(int a)
    {
        return printf("%c", a);
    }

    int fputc(int c, FILE *stream) {
        return fprintf(stream, "%c", c);

    }

    void ni(const char *s) {
        fprintf(stdout, "Not implemented %s\n", s);
        //abort();
    }
    
    int 
    sprintf(char* buf, const char *fmt, ...)
    {
        va_list ap;
        int ret;
        va_start(ap, fmt);
        ret = vsnprintf(buf, 1024, fmt, ap);
        va_end(ap);
        return ret;
    }


    int 
    nanosleep(const struct timespec *req, struct timespec *rem)
    {
        ni(__FUNCTION__);
        return 1;
    }

    void *
    dlopen(const char *fname, int flags) 
    { 
        ni(__FUNCTION__);
        return NULL;
    }

    int 
    dlclose(void *handle) 
    {
        ni(__FUNCTION__);
        return -1;

    }
    char *
    fgets(char *str, int n, FILE *fd)
    {
        ni(__FUNCTION__);
        return NULL;
        //char *result;
        //ocall_fgets(&result, str, n, fd);
        //return result;
    }

    char *
    getenv(const char *name)
    {
        ni(__FUNCTION__);
        return NULL;
    }

    struct lconv *
    localeconv(void)
    {
        ni(__FUNCTION__);
        return NULL;
    }

    int
    fputs(const char *str, FILE *stream)
    {
        ni(__FUNCTION__);
        return -1;
        //int res;
        //ocall_fputs(&res, str, stream); 
        //return res;
    }


    FILE *
    fopen(const char *filename, const char *mode)
    {
        FILE *fp;
        ocall_fopen(&fp, filename, mode);
        return fp;
    }

    void
    exit(int status_)
    {
        ocall_exit(status_);
        abort();
    }

    char *
    setlocale(int category, const char *locale)
    {
        ni(__FUNCTION__);
        return NULL;
        //char *a;
        //ocall_setlocale(&a, category, locale);
        //return a;
    }

    int
    system(const char *str)
    {
        ni(__FUNCTION__);
        return -1;
    }

    FILE *
    popen(const char *command, const char *type)
    {
        ni(__FUNCTION__);
        return NULL;
    }

    int 
    pclose(FILE *stream)
    {
        ni(__FUNCTION__);
        return -1;
    }

    long int
    mktime(void *timeptr)
    {
        ni(__FUNCTION__);
        return -1;
    }

    int 
    remove(const char *filename)
    {
        ni(__FUNCTION__);
        return -1;
    }

    void *
    localtime(const long int *timer)
    {
        ni(__FUNCTION__);
        return NULL;
    }

    struct tm *
    gmtime(const long int *timer)
    {
        ni(__FUNCTION__);
        //ocall_gmtime(&a, timer);
        return NULL;
    }

    int
    rename(const char *old_filename, const char *new_filename)
    {
        ni(__FUNCTION__);
        return -1;
    }

    char *
    tmpnam(char *str)
    {
        ni(__FUNCTION__);
        return NULL;
    }

    int
    fclose(FILE *ptr)
    {
        int a;
        a = 0;
        ocall_fclose(&a, ptr);
        return a;
    }

    int
    setvbuf(FILE *stream, char *buffer, int mode, size_t size)
    {
        ni(__FUNCTION__);
        return -1;
    }

    long int
    ftell(FILE *stream)
    {
        long int a;
        a = 0;
        ocall_ftell(&a, stream);
        return a;
    }

    int
    fseek(FILE *stream, long int offset, int whence)
    {
        int a;
        a = 0;
        ocall_fseek(&a, stream, offset, whence);
        return a;
    }

    FILE *
    tmpfile()
    {
        ni(__FUNCTION__);
        return NULL;
    }

    void
    clearerr(FILE *stream)
    {
        ni(__FUNCTION__);
    }

    size_t
    fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
    {
        size_t a;
        a = 0;
        /* 
         * lua parses the first char on the file for some weird reason
         * and the the rest
         */
		memset(ptr, 0, nmemb * size);
		ocall_fread(&a, ptr, size, nmemb, stream);
		((char *)ptr)[a] = '\0';
        return a;
    }

    int
    ferror(FILE *stream)
    {
        int a;
        a = 0;
        ocall_ferror(&a, stream);
        return a;
    }

    char *rec_filename(FILE *f);
    int counter = -1;
    size_t len = 0;
    char *buffer = NULL;

    int
    getc(FILE *stream)
    {
        int a;
        ocall_getc(&a, stream);
        return a;
    }

    int
    ungetc(int ch, FILE *stream)
    {
        int a;
        a = 0;
        ocall_ungetc(&a, ch, stream);
        return a;
    }

    FILE *
    freopen(const char *filename, const char *mode, FILE *stream)
    {
        ni(__FUNCTION__);
        return NULL;
        //FILE *fd;
        //fd = NULL;
        //ocall_freopen(&fd, filename, mode, stream);
        //return fd;
    }

    int
    feof(FILE *stream)
    {
        ni(__FUNCTION__);
        return -1;
        //int a;
        //a = 0;
        //ocall_feof(&a, stream);
        //return a;
    }

    int
    rand(void)
    {
        int a;
        sgx_read_rand((unsigned char *)&a, sizeof(a));
        if (a < 0)
            a *= -1; 
        
        //ocall_rand(&a);
        //fprintf(stdout, "output = %u\n", a);
        return a;   
    }

    long int
    time(long int *src)
    {
        long int a;
        a = 0;
        //ni(__FUNCTION__);
        //ocall_time(&a, src);
        return a;
    }

    void
    srand(unsigned int seed)
    {   
        ocall_srand(seed);
    }

    long int
    clock()
    {
        ni(__FUNCTION__);
        return -1;
        //long int a;
        //a = 0;
        //ocall_clock(&a);
        //return a;
    }

    int
    fflush(FILE *ptr)
    {
        int res;
        res = 0;
        return ocall_fflush(&res, ptr);
    }

    long int
    labs (long int i)
    {
        return i < 0 ? -i : i;
    }

    int
    puts(const char *s)
    {
        int a;
        a = fprintf(stdout, "%s", s);
        return a;
    }

    int
    putc(int a, FILE *f)
    {
        return fprintf(f, "%d", a);
    }

    void 
    perror(const char *p){
        fprintf(stdout, "%s", p);
    }

	int 
	strcmp(const char* s1, const char* s2)
	{
		while(*s1 && (*s1 == *s2)) {
			s1++;
			s2++;
		}
    	return *(const unsigned char*)s1 - *(const unsigned char*)s2;
	}

    char *
    strcpy(char *strDest, const char *strSrc)
    {
        char *temp = strDest;
        while(*strDest++ = *strSrc++); // or while((*strDest++=*strSrc++) != '\0');
        return temp;
    }

    char *
    strcat(char *dest, const char *src)
    {
        char *rdest = dest;

        while (*dest)
          dest++;
        while (*dest++ = *src++)
          ;
        return rdest;
    }

    char *
    strdup(char *src)
    {
        char *str;
        size_t len = strlen(src);
        str = (char *)malloc(len + 1);
        if (str) {
            memcpy(str, src, len + 1);
        }
        return str;
    }

    int 
    memcmp(const void *s1, const void *s2, size_t n)
    {
		size_t i;  
		const unsigned char * cs = (const unsigned char*) s1;
		const unsigned char * ct = (const unsigned char*) s2;

		for (i = 0; i < n; i++, cs++, ct++) {
		if (*cs < *ct)
			return -1;
		else if (*cs > *ct)
			return 1;
		}
		return 0;
	}

    int 
    __isnan(double x) 
    {
        return x != x;
    }
    int isinf(double x) { return !__isnan(x) && __isnan(x - x); }


    int clock_gettime(clockid_t clk_id, struct timespec *tp) {
        ni(__FUNCTION__);
        return -1;
        //fprintf(stdout,"Not implemented clock_gettime \n");
        //int a;
        //ocall_clock_gettime(&a, clk_id, tp);
        //return a;
    }

    int gettimeofday(struct timeval *tv, void *tz) {
        //ni(__FUNCTION__);
        return 0;
        //int a;
        //ocall_gettimeofday(&a ,tv, tz);
    };

    int waitpid(int pid, int *w, int opt){
        ni(__FUNCTION__);
        return -1;
    }
    int kill(int a, int s) {
        ni(__FUNCTION__);
        return -1;
    }

    int dup(int o){
        ni(__FUNCTION__);
        return -1;
    }


    int dup2(int o, int n){
        ni(__FUNCTION__);
        return -1;
    }

    int pipe(int p[2]) {
        ni(__FUNCTION__);
        return -1;

    }

    int _exit(int a) {
        ocall_exit(a);
        abort();
    }

    int fork(void) {
        ni(__FUNCTION__);
        return -1;
    }

    int close(int fd) {
        ni(__FUNCTION__);
        return -1;
        //int a;
        //ocall_close(&a, fd);
        //return a;
    }

    long sysconf(int n) {
        ni(__FUNCTION__);
        return -1;
    }

    int chdir(const char *path) {
        ni(__FUNCTION__);
        return -1;
    }

    int execv(const char *path, char *const argv[]) {
        ni(__FUNCTION__);
        return -1;

    }

    int execvp(const char *path, char *const argv[]) {
        ni(__FUNCTION__);
        return -1;

    }

    int closedir(void *dir) {
        ni(__FUNCTION__);
        return -1;
        //int a;
        //ocall_closedir(&a, dir);
        //return a;
    }

    void *opendir(const char *t) {
        //void *p;
        //ocall_opendir(&p, t);
        //return p;
        ni(__FUNCTION__);
        return NULL;

    }

    int symlink(const char *t, const char *l) {
        ni(__FUNCTION__);
        return -1;
        //int a;
        //ocall_symlink(&a, t, l);
        //return a;
    }

    struct utimbuf {
        long a;
        long b;
    };

    int utime(const char *t, const struct utimbuf *l) {
        ni(__FUNCTION__);
        return -1;
    }


    void *
    dlsym(void *handle, const char *s) {
        ni(__FUNCTION__);
        return NULL;
        //void *p;
        //ocall_dlsym(&p, handle, s);
        //return p;

    }

    int fgetc(FILE *stream) {
        unsigned char c;
        fread(&c, 1, sizeof(unsigned char), stream);
        return c;
    }

    FILE *
    fdopen(int fd, const char *mode) {
        ni(__FUNCTION__);
        return NULL;
    }

    int mkdir(const char *path, int l) {
        ni(__FUNCTION__);
        return -1;
    }

    void *readdir(DIR *l) {
        ni(__FUNCTION__);
        return NULL;
    }

    int fseeko(FILE *s, long offset, int w) {
        ni(__FUNCTION__);
        return -1;
    }

    int fileno(FILE *s) {
        ni(__FUNCTION__);
        return -1;
    }

    long ftello(FILE *s) {
        ni(__FUNCTION__);
        return -1;
    }

    void *localtime_r(const long int *a, void *r){
        ni(__FUNCTION__);                    
        return NULL;
        //struct tm *p = NULL;// = malloc(sizeof(struct tm));
        //ocall_localtime_r((void **)&p, a, r);
        //return p;                         
    }                                        

    size_t
    read(int fd, void *b, size_t c)
    {
        size_t l;
        ocall_read(&l, fd, b, c);
        return l;
    }

    size_t
    write(int fd, void *b, size_t c)
    {
        size_t l;
        ocall_write(&l, fd, b, c);
        return l;
    }

    long
	lseek(int f, long o, int w){
        ni(__FUNCTION__);
        return -1;
        //long a;
        //ocall_lseek(&a, f, o, w);
        //return a;
    }

    int
	isatty(int f) {
        ni(__FUNCTION__);
        return 0;
        //int a;
        //ocall_isatty(&a, f);
        //return 0;
    }

    int
	tcgetattr(int f, void *p) {
        ni(__FUNCTION__);
        return 0;
        //int a;
        //ocall_tcgetattr(&a, f, p);
        //return a;
    }

    int tcsetattr(int f, int oa, void *p) {
        ni(__FUNCTION__);
        //int a;
        //ocall_tcsetattr(&a, f, oa, p);
        //return a;
        return -1;

    }

    char *getcwd(char *b, size_t s) {
        //char *p;
        ni(__FUNCTION__);
        //ocall_getcwd(&p, b, s);
        return NULL;
    }
    int utimes(const char *f, const struct timeval[2]) {
        ni(__FUNCTION__);
        return -1;
    }

    int FD_ISSET(int fd, void *set) {
        //ocall_FD_ISSET(fd, set);
        ni(__FUNCTION__);
        return -1;
    }

    int FD_SET(int fd, void *set) {
        //ocall_FD_SET(fd, set);
        ni(__FUNCTION__);
        return -1;
    }

    void FD_ZERO(void *p) {
        ni(__FUNCTION__);
        //ocall_FD_ZERO(p);
        return ;

    }
    int lstat(const char *p, void *s) {
        ni(__FUNCTION__);
        return -1;
    }

    int stat(const char *p, void *s) {
        ni(__FUNCTION__);
        return -1;
        //int a;
        //ocall_stat(&a, (char *)p, s);
        //return a;
    }

    int select(int a, void *r, void *w, void *e, void *t) {
        //int b;
        //ocall_select(&b, a, r, w, e, t);
        ni(__FUNCTION__);
        return -1;

    }

    int open(const char *m, int a, int b) {
        ni(__FUNCTION__);
        return -1;
    }

    char *
    realpath(const char *rn, const char *r)
    {
        return NULL;
		//char *bot;
		//ocall_realpath(&bot, rn, (char *)rn);
        //return bot;
    }

    size_t 
    readlink(const char *r, char *b, size_t l) 
    {
        ni(__FUNCTION__);
        return -1;
    }

    void
    atomic_fetch_sub(int a) {
        ni(__FUNCTION__);
    }

    void
    atomic_fetch_xor(int a) {
        ni(__FUNCTION__);
    }

    void
    atomic_compare_exchange_strong(int a) {
        ni(__FUNCTION__);
    }

    void
    atomic_store(int a) {
        ni(__FUNCTION__);
    }

    void
    atomic_compare_exchage_strong(int a) {
        ni(__FUNCTION__);
    }

    void
    atomic_exchange(int a) {
        ni(__FUNCTION__);
    }

    void
    atomic_fetch_and(int a) {
        ni(__FUNCTION__);
    }

    void
    atomic_fetch_or(int a) {
        ni(__FUNCTION__);
    }

    void
    atomic_load(int a) {
        ni(__FUNCTION__);
    }

    void
    atomic_fetch_add(int a) {
        ni(__FUNCTION__);
    }
}
