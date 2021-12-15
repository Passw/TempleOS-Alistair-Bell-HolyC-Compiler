#include "../src/inc.h"
#define _GNU_SOURCE
#include <stdio.h>

static const char *types[] = {
	"U8",
	"I8",
	"U16",
	"I16",
	"U32",
	"I32",
	"U64",
	"I64",
	"F64",
	"Boolean",
};
static const unsigned int types_len = ARRAY_LEN(types);
static const char *keywords[] = {
	"break",
	"case",
	"class",
	"const",
	"continue",
	"default",
	"do",
	"else",
	"enum",
	"extern",
	"for",
	"goto",
	"if",
	"return",
	"static",
	"struct",	
	"switch",
	"union",
	"while"
};
static const unsigned int keywords_len = ARRAY_LEN(keywords);

static const char *dump_header = "#ifndef HOLYC_DEFS_H\n#define HOLYC_DEFS_H\n\n/* This file was auto generated by tools/hashgen. */\n#include \"inc.h\"\n\n";
static const char *dump_footer = "\n#endif\n";

#define DSTR(str, f) \
	fwrite(str, strlen(str), 1, f);

struct out {
	const char *str;
	hash_t hash;
};

static hash_t
hash_chars(char *chars)
{
	hash_t total = 5381;
	char c;
	while ((c = *chars++)) {
		total += ((total << 5) + total) + c;
	}
	return total;
}

static void
printo(struct out *o)
{
	fprintf(stdout, "[%10s][%16lu]\n", o->str, o->hash);
}
static int 
sort_func(const void *v1, const void *v2)
{
	register struct out *o1 = (struct out *)v1;
	register struct out *o2 = (struct out *)v2;
	return o1->hash > o2->hash;
}
static void 
dump_as_array(const struct out out[], const char *head, const char *name, unsigned int len, FILE *f)
{
	unsigned int i;
	DSTR(head, f);
	for (i = 0; i < len; ++i) {
		char tmp[64] = { 0 };
		sprintf(tmp, "#define HASH_%s_%s %lu\n", name, out[i].str, out[i].hash);
		DSTR(tmp, f);
	}
}

int
main(int argc, const char *argv[])
{
	if (argc < 2) {
		fprintf(stderr,"error: no output specified.\n");
		return 1;
	}
	/* Save compile clock cycles. */
	struct stat s1, s2;
	if (stat(argv[0], &s1) == 0 && stat(argv[1], &s2) == 0) {
		if (s1.st_mtime < s2.st_mtime) {
			return 0;
		}
	} 

	struct out out_types[types_len];
	struct out out_keywords[keywords_len];
	
	/* Populate. */
	unsigned int i;
	for (i = 0; i < types_len; ++i) {
		out_types[i].str = types[i];
		out_types[i].hash = hash_chars((char *) types[i]);
	}
	for (i = 0; i < keywords_len; ++i) {
		out_keywords[i].str = keywords[i];
		out_keywords[i].hash = hash_chars((char *) keywords[i]);
	}

	/* Sort 
	qsort(out_types, types_len, sizeof(struct out), sort_func);
	qsort(out_keywords, keywords_len, sizeof(struct out), sort_func);
	*/

	/* Dump. */
	FILE *f = fopen(argv[1], "w");
	if (!f) {
		register int snap = errno;
		fprintf(stderr, "error: cannot dum to %s, %s.\n", argv[1], strerror(snap));
		return 1;
	}
	DSTR(dump_header, f);
	dump_as_array(out_types, "/* Predefined language types. */\n", "TYPES", types_len, f);
	dump_as_array(out_keywords, "/* Resevered keywords. */\n", "KEYWORDS", keywords_len, f);
	DSTR(dump_footer, f);
	
	return 0;
}
