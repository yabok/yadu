/***
  Copyright (C) 2012 Kay Sievers

  yadu is free software; you can redistribute it and/or modify it under the
  terms of the GNU Lesser General Public License as published by the Free
  Software Foundation; either version 2.1 of the License, or (at your option)
  any later version.

  yadu is distributed in the hope that it will be useful, but WITHOUT ANY
  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
  A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more
  details.

  You should have received a copy of the GNU Lesser General Public License
  along with yadu; If not, see <http://www.gnu.org/licenses/>.
***/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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
