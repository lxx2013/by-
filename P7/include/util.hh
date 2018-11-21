#ifndef _UTIL_HH_
#define _UTIL_HH_

// debug info is in blue
// you can hide/show debug info in main.cc
#ifdef DEBUG
#define debug(format, args...) fprintf(stdout, "\033[36m" format "\033[0m", ##args)
#else
#define debug(format, args...)
#endif
//line-column info is grey
#ifdef DEBUG
#define line(format, args...) fprintf(stdout, "\033[32m" format "\033[0m", ##args)
#else
#define line(format, args...)
#endif

// error info is in red
#define error(format, args...) fprintf(stderr, "\033[31m[ERROR]:  " format "\033[0m", ##args)

// warning info is in orange
#define warning(format, args...) fprintf(stderr, "\033[33m[WARNING]:" format "\033[30;1m", ##args)


#define printLoc(loc) printf("[%d %d %d %d]\n", loc->first_line, loc->first_column, \
        loc->last_line, loc->last_column)

extern bool handle_opt(int argc, char** argv);


#endif
