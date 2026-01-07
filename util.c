#include "util.h"
#include <stdio.h>
#include <stdarg.h>
void info(const char *f,...){ va_list a;va_start(a,f);fprintf(stderr,"[INFO] ");vfprintf(stderr,f,a);fprintf(stderr,"\n");va_end(a); }
void error(const char *f,...){ va_list a;va_start(a,f);fprintf(stderr,"[ERR] ");vfprintf(stderr,f,a);fprintf(stderr,"\n");va_end(a); }
