#include <stdio.h>
#include <limits.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
int main(void)
{
	long i = LONG_MAX;
	long act = 0;
	char s[1000] = { 0 };
	sprintf(s, "%ld1", i);
	act = strtol(s, NULL, 10);
	if (errno == ERANGE)
		fprintf(stderr, "strtol correctly set ERANGE for %s\n", s);
	else
		fprintf(stderr, "strtol did not set ERANGE for %s\n", s);
	if (act == LONG_MAX)
		fprintf(stderr, "strtol correctly set %s to LONG_MAX\n", s);
	else
		fprintf(stderr, "strtol did not set %s to LONG_MAX\n", s);
	errno = 0;
	
	long long i4 = LONG_MAX;
	i4++;
	long act4 = 0;
	char s4[1000] = { 0 };
	sprintf(s4, "%lld", i4);
	act4 = strtol(s4, NULL, 10);
	if (errno == ERANGE)
		fprintf(stderr, "strtol correctly set ERANGE for %s\n", s4);
	else
		fprintf(stderr, "strtol did not set ERANGE for %s\n", s4);
	if (act4 == LONG_MAX)
		fprintf(stderr, "strtol correctly set %s to LONG_MAX\n", s4);
	else
		fprintf(stderr, "strtol did not set %s to LONG_MAX\n", s4);

	errno = 0;
	long i1 = LONG_MIN;
	long act1 = 0;
	char s1[1000] = { 0 };
	sprintf(s1, "%ld1", i1);
	act1 = strtol(s1, NULL, 10);
	if (errno == ERANGE)
		fprintf(stderr, "strtol correctly set ERANGE for %s\n", s1);
	else
		fprintf(stderr, "strtol did not set ERANGE for %s\n", s1);
	if (act1 == LONG_MIN)
		fprintf(stderr, "strtol correctly set %s to LONG_MIN\n", s1);
	else
		fprintf(stderr, "strtol did not set %s to LONG_MIN\n", s1);
	errno = 0;
	long long i2 = LLONG_MAX;
	long long act2 = 0;
	char s2[1000] = { 0 };
	sprintf(s2, "%lld1", i2);
	act2 = strtol(s2, NULL, 10);
	if (errno == ERANGE)
		fprintf(stderr, "strtoll correctly set ERANGE for %s\n", s2);
	else
		fprintf(stderr, "strtoll did not set ERANGE for %s\n", s2);
	if (act == LLONG_MAX)
		fprintf(stderr, "strtoll correctly set %s to LLONG_MAX\n", s2);
	else
		fprintf(stderr, "strtoll did not set %s to LLONG_MAX\n", s2);
	errno = 0;
	long long i3 = LLONG_MIN;
	long long act3 = 0;
	char s3[1000] = { 0 };
	sprintf(s3, "%lld1", i3);
	act3 = strtol(s3, NULL, 10);
	if (errno == ERANGE)
		fprintf(stderr, "strtoll correctly set ERANGE for %s\n", s3);
	else
		fprintf(stderr, "strtoll did not set ERANGE for %s\n", s3);
	if (act3 == LLONG_MIN)
		fprintf(stderr, "strtoll correctly set %s to LLONG_MAX\n", s3);
	else
		fprintf(stderr, "strtoll did not set %s to LLONG_MAX\n", s3);
	
	return 0;
}
