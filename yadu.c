#include <stdbool.h>
#include <time.h>
#include <limits.h>
#include <bsd/string.h>
#include <unistd.h>
#include <errno.h>

#include "util.h"
#include "time-dst.h"

#define FORMAT_TIMESTAMP_MAX ((4*4+1)+11+9+4+1) /* weekdays can be unicode */

static const char *jump_str(int delta_minutes, char *s, size_t size) {
	if (delta_minutes == 60) {
		return "one hour forward";
	} else if (delta_minutes == -60) {
		return "one hour backwards";
	} else if (delta_minutes < 0) {
		snprintf(s, size, "%i minutes backwards", -delta_minutes);
		return s;
	} else if (delta_minutes > 0) {
		snprintf(s, size, "%i minutes forward", delta_minutes);
		return s;
	} else {
		return "";
	}
}


int main(int argc, char ** argv) {
	if (argc != 2) {
		fprintf(stderr, "Usage: %s TIMEZONE\n", argv[0]);
		exit(2);
	}

	if (getenv("TZ")) {
		fprintf(stderr, "Warning: TZ variable set, output times will not be in the specified zone\n");
	} else {
		setenv("TZ", argv[1], 1);
	}

	// make path variable
	char path[PATH_MAX] = "/usr/share/zoneinfo/";
	strlcat(path, argv[1], PATH_MAX);
	if(access(path, F_OK|R_OK) == -1) {
		fprintf(stderr, "TZ file `%s' does not exist or is not readable\n", path);
		exit(2);
	}

	// get current time
	struct timespec tms;
	if (clock_gettime(CLOCK_REALTIME, &tms)) {
		return -1;
	}

	time_t time_cur,
	       time_next;
	_cleanup_free_ char * zone_cur = NULL,
	                    * zone_next = NULL;
	int delta_next = 0;
	bool is_dstc = false,
	     is_dstn = false;
	int r = time_get_dst(tms.tv_sec, path,
			&time_cur, &zone_cur, &is_dstc,
			&time_next, &delta_next, &zone_next, &is_dstn);

	if (r < 0) {
		printf("      DST active: %s\n", "n/a");
	} else {
		printf("      DST active: %s\n", yes_no(is_dstc));

		char a[FORMAT_TIMESTAMP_MAX];
		char b[FORMAT_TIMESTAMP_MAX];
		time_t time;
		time = time_cur - 1;
		struct tm tm;
		strftime(a, ELEMENTSOF(a), "%a %Y-%m-%d %H:%M:%S %Z", localtime_r(&time, &tm));
		strftime(b, ELEMENTSOF(b), "%a %Y-%m-%d %H:%M:%S %Z", localtime_r(&time_cur, &tm));
		printf(" Last DST change: DST %s at\n"
				"                  %.*s\n"
				"                  %.*s\n",
				is_dstc ? "began" : "ended",
				(int)sizeof(a), a,
				(int)sizeof(b), b);

		char s[32];
		time = time_next - 1;
		strftime(a, ELEMENTSOF(a), "%a %Y-%m-%d %H:%M:%S %Z", localtime_r(&time, &tm));
		strftime(b, ELEMENTSOF(b), "%a %Y-%m-%d %H:%M:%S %Z", localtime_r(&time_next, &tm));
		printf(" Next DST change: DST %s (the clock jumps %s) at\n"
				"                  %.*s\n"
				"                  %.*s\n",
				is_dstn ? "begins" : "ends",
				jump_str(delta_next, s, sizeof(s)),
				(int) sizeof(a), a,
				(int) sizeof(b), b);
	}
	return 0;
}
