#include "utils.h"

char *strdup0(const char *s)
{
	size_t len = strlen(s);
	char *p;
	p = (char *)malloc(len + 1);
	if (p) {
		strncpy(p, s, len);
	}
	p[len] = '\0';
	return p;
}

unsigned char *strndup0(const unsigned char *s, size_t n)
{
	size_t i;
	const unsigned char *p = s;
	unsigned char *new;
	for (i = 0; i < n && *p; i++, p++)
		;
	new = (unsigned char *) malloc(i + 1);
	if (new) {
		memcpy(new, s, i);
		new[i] = '\0';
	}
	return new;
}