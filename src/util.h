#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define _cleanup_free_ __attribute__((cleanup(freep)))
#define _cleanup_fclose_ __attribute__((cleanup(fclosep)))

static inline void fclosep(FILE ** p) {
	if (*p) {
		fclose(*p);
	}
}

static inline void freep(void * p) {
	free(*(void**) p);
}


static inline const char* yes_no(bool b) {
	return b ? "yes" : "no";
}


#define ELEMENTSOF(x) (sizeof(x)/sizeof((x)[0]))
