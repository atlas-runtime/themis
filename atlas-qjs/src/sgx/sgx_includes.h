#ifndef _SGX_INC_
#define _SGX_INC_
#define LC_CTYPE 0
#define LC_NUMERIC 1
#define LC_TIME 2
#define LC_COLLATE 3
#define LC_MONETARY 4
#define LC_ALL 6
#define CLOCKS_PER_SEC 1000000
#define L_tmpnam 20
#define _IONBF 2
#define _IOLBF 1
#define _IOFBF 0
#ifndef _FILE_DEFINED

struct _IO_FILE {
  int _flags;		/* High-order word is _IO_MAGIC; rest is flags. */
#define _IO_file_flags _flags

  /* The following pointers correspond to the C++ streambuf protocol. */
  /* Note:  Tk uses the _IO_read_ptr and _IO_read_end fields directly. */
  char* _IO_read_ptr;	/* Current read pointer */
  char* _IO_read_end;	/* End of get area. */
  char* _IO_read_base;	/* Start of putback+get area. */
  char* _IO_write_base;	/* Start of put area. */
  char* _IO_write_ptr;	/* Current put pointer. */
  char* _IO_write_end;	/* End of put area. */
  char* _IO_buf_base;	/* Start of reserve area. */
  char* _IO_buf_end;	/* End of reserve area. */
  /* The following fields are used to support backing up and undo. */
  char *_IO_save_base; /* Pointer to start of non-current get area. */
  char *_IO_backup_base;  /* Pointer to first valid character of backup area */
  char *_IO_save_end; /* Pointer to end of non-current get area. */

  struct _IO_marker *_markers;

  struct _IO_FILE *_chain;

  int _fileno;
  int _flags2;
  long long int _old_offset; /* This used to be _offset but it's too small.  */

#define __HAVE_COLUMN /* temporary */
  /* 1+column number of pbase(); 0 is unknown. */
  unsigned short _cur_column;
  signed char _vtable_offset;
  char _shortbuf[1];

  /*  char* _save_gptr;  char* _save_egptr; */

};
typedef struct _IO_FILE FILE;
FILE *stdin, *stdout, *stderr;
#define _FILE_DEFINED
#endif

#ifndef _ERRNO_T_DEFINED
#define _ERRNO_T_DEFINED
typedef int errno_t;
#endif

#define _O_TEXT     0x4000  /* file mode is text (translated) */
#define _O_BINARY   0x8000  /* file mode is binary (untranslated) */

/* Seek method constants */
#define SEEK_CUR    1
#define SEEK_END    2
#define SEEK_SET    0

#define DECLARE_HANDLE(name) struct name##__{int unused;}; typedef struct name##__ *name
DECLARE_HANDLE  (HWND);

#ifndef CONST
#define CONST  const
#endif
typedef char CHAR;
typedef CONST CHAR *LPCSTR, *PCSTR;
typedef LPCSTR PCTSTR, LPCTSTR, PCUTSTR, LPCUTSTR;
typedef unsigned int UINT;

#define WINAPI      __stdcall


struct timeval {      
    long               tv_sec; 
    long               tv_usec;
};   

#define CLOCK_REALTIME          0    
#define CLOCK_MONOTONIC         1    
#define CLOCK_PROCESS_CPUTIME_ID    2
#define CLOCK_THREAD_CPUTIME_ID     3
#define CLOCK_MONOTONIC_RAW     4    
#define CLOCK_REALTIME_COARSE       5
#define CLOCK_MONOTONIC_COARSE      6
#define CLOCK_BOOTTIME          7    
#define CLOCK_REALTIME_ALARM        8
#define CLOCK_BOOTTIME_ALARM        9


#define FE_TONEAREST	0
#define FE_DOWNWARD	0x400
#define FE_UPWARD	0x800
#define FE_TOWARDZERO	0xc00

struct timespec {
    int tv_sec;
    int tv_nsec;
};
//#define LONG_MAX 0X7FFFFFFFFFFFFFFFL
#ifdef INFINITY
#undef INFINITY
#define INFINITY (__builtin_inf())
#endif
#define S_ISUID 04000
#define S_IFBLK   0060000
#define S_IFREG   0100000
#define S_IFDIR   0040000
#define S_IFCHR   0020000
#define S_IFMT    0170000
#define S_IFIFO   0010000


#define S_IFLNK   0120000
#define S_IFSOCK 0140000
#define S_IFBLK   0060000
#define S_ISGID   02000
#define WNOHANG     0x00000001

#define SIGHUP       1
#define SIGINT       2
#define SIGQUIT      3
#define SIGILL       4
#define SIGTRAP      5
#define SIGABRT      6
#define SIGIOT       6
#define SIGBUS       7
#define SIGFPE       8
#define SIGKILL      9
#define SIGUSR1     10
#define SIGSEGV     11
#define SIGUSR2     12
#define SIGPIPE     13
#define SIGALRM     14
#define SIGTERM     15
#define SIGSTKFLT   16
#define SIGCHLD     17
#define SIGCONT     18
#define SIGSTOP     19
#define SIGTSTP     20
#define SIGTTIN     21
#define SIGTTOU     22
#define SIGURG      23
#define SIGXCPU     24
#define SIGXFSZ     25
#define SIGVTALRM   26
#define SIGPROF     27
#define SIGWINCH    28
#define SIGIO       29

 #define O_ACCMODE      0003                  
 #define O_RDONLY         00                  
 #define O_WRONLY         01                  
 #define O_RDWR           02                  
 #ifndef O_CREAT                              
 # define O_CREAT       0100 /* Not fcntl.  */
 #endif                                       
 #ifndef O_EXCL                               
 # define O_EXCL        0200 /* Not fcntl.  */
 #endif                                       
 #ifndef O_NOCTTY                             
 # define O_NOCTTY      0400 /* Not fcntl.  */
 #endif                                       
 #ifndef O_TRUNC                              
 # define O_TRUNC      01000 /* Not fcntl.  */
 #endif                                       
 #ifndef O_APPEND                             
 # define O_APPEND     02000                  
 #endif                                       

#define _SC_OPEN_MAX 5
#define PATH_MAX 4096


#define RTLD_LAZY   0x00001 /* Lazy function call binding.  */           
#define RTLD_NOW    0x00002 /* Immediate function call binding.  */      
#define RTLD_BINDING_MASK   0x3 /* Mask of binding time value.  */       
#define RTLD_NOLOAD 0x00004 /* Do not load the object.  */               
#define RTLD_DEEPBIND   0x00008 /* Use deep binding.  */                 
                                                                      
/* If the following bit is set in the MODE argument to `dlopen',         
*     the symbols of the loaded object and its dependencies are made        
*         visible as if the object were linked directly into the program.  */   
#define RTLD_GLOBAL 0x00100                                              
                                                                      
/* Unix98 demands the following flag which is the inverse to RTLD_GLOBAL.
*     The implementation does this by default and so we can define the      
*         value to zero.  */                                                    
#define RTLD_LOCAL  0                                                    


#define ISIG    0000001
#define ICANON  0000002
#define XCASE   0000004
#define ECHO    0000010
#define ECHOE   0000020
#define ECHOK   0000040
#define ECHONL  0000100
#define NOFLSH  0000200
#define TOSTOP  0000400
#define ECHOCTL 0001000
#define ECHOPRT 0002000
#define ECHOKE  0004000
#define FLUSHO  0010000
#define PENDIN  0040000
#define IEXTEN  0100000
#define EXTPROC 0200000
                       
 #define TCOOFF      0  
 #define TCOON       1  
 #define TCIOFF      2  
 #define TCION       3  
                        
#define TCIFLUSH    0  
#define TCOFLUSH    1  
#define TCIOFLUSH   2  
                       
  #define TCSANOW     0  
  #define TCSADRAIN   1  
  #define TCSAFLUSH   2  
                         
 

//#include "termbits.h"
//#include "ioctl.h"

typedef long int off_t;

struct __dirstream {
    int fd;                        /* File descriptor.  */
    //__libc_lock_define (, lock) /* Mutex lock for this structure.  */
    size_t allocation;                /* Space allocated for the block.  */
    size_t size;                /* Total valid data in the block.  */
    size_t offset;                /* Current offset into the block.  */
    off_t filepos;                /* Position of next entry to read.  */
    int errcode;                /* Delayed error code.  */
    /* Directory block.  We must make sure that this block starts
       at an address that is aligned adequately enough to store
       dirent entries.  Using the alignment of "void *" is not
       sufficient because dirents on 32-bit platforms can require
       64-bit alignment.  We use "long double" here to be consistent
       with what malloc uses.  */
    char data[0] __attribute__ ((aligned (__alignof__ (long double))));
};

typedef struct __dirstream DIR;

typedef unsigned short ino_t;

struct dirent                                                  
  {                                                            
    ino_t d_ino;                                             
    __off_t d_off;                                             
    unsigned short int d_reclen;                               
    unsigned char d_type;                                      
    char d_name[256];       /* We must not include limits.h! */
  };                                                           


#ifdef FD_SETSIZE
#define __DARWIN_FD_SETSIZE     FD_SETSIZE
#else /* !FD_SETSIZE */
#define __DARWIN_FD_SETSIZE     1024
#endif /* FD_SETSIZE */
#define __DARWIN_NBBY           8                               /* bits in a byte */
#define __DARWIN_NFDBITS        (sizeof(__int32_t) * __DARWIN_NBBY) /* bits per mask */
#define __DARWIN_howmany(x, y)  ((((x) % (y)) == 0) ? ((x) / (y)) : (((x) / (y)) + 1)) /* # y's == x bits? */

typedef struct fd_set {
            __int32_t       fds_bits[__DARWIN_howmany(__DARWIN_FD_SETSIZE, __DARWIN_NFDBITS)];
} fd_set;

struct winsize {             
    unsigned short ws_row;   
    unsigned short ws_col;   
    unsigned short ws_xpixel;
    unsigned short ws_ypixel;
};                           


struct stat {                                                      
    unsigned long   st_dev;     /* Device.  */                     
    unsigned long   st_ino;     /* File serial number.  */         
    unsigned int    st_mode;    /* File mode.  */                  
    unsigned int    st_nlink;   /* Link count.  */                 
    unsigned int    st_uid;     /* User ID of the file's owner.  */
    unsigned int    st_gid;     /* Group ID of the file's group. */
    unsigned long   st_rdev;    /* Device number, if device.  */   
    unsigned long   __pad1;                                        
    long        st_size;    /* Size of file, in bytes.  */         
    int     st_blksize; /* Optimal block size for I/O.  */         
    int     __pad2;                                                
    long        st_blocks;  /* Number 512-byte blocks allocated. */
    long        st_atim;   /* Time of last access.  */            
    unsigned long   st_atim_nsec;                                 
    long        st_mtim;   /* Time of last modification.  */      
    unsigned long   st_mtime_nsec;                                 
    long        st_ctim;   /* Time of last status change.  */     
    unsigned long   st_ctime_nsec;                                 
    unsigned int    __unused4;                                     
    unsigned int    __unused5;                                     
};                                                                 

typedef int clockid_t;
extern int encrypted_mode;

#define TIOCGWINSZ  0x5413
#endif

