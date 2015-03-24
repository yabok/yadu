#pragma once

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
#include <time.h>

int time_get_dst(time_t date, const char *tzfile,
                 time_t *switch_cur, char **zone_cur, bool *dst_cur,
                 time_t *switch_next, int *delta_next, char **zone_next, bool *dst_next);
