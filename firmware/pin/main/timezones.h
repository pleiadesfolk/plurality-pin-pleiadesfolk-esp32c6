#pragma once

/** POSIX TZ string for an IANA time zone name ("Asia/Hong_Kong" -> "HKT-8"); NULL if unknown. */
const char *timezones_posix(const char *name);
