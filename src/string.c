#include "khash.h"
#include "latino.h"

struct sym_key {
	const char *ptr;
	size_t len;
};

static khint_t
sym_hash(struct sym_key key)
{
	const char *s = key.ptr;
	khint_t h;
	size_t len = key.len;

	h = *s++;
	while (len--) {
		h = (h << 5) - h + (khint_t)*s++;
	}
	return h;
}

static khint_t
sym_eq(struct sym_key a, struct sym_key b)
{
	if (a.len != b.len) return false;
	if (memcmp(a.ptr, b.ptr, a.len) == 0) return true;
	return false;
}

