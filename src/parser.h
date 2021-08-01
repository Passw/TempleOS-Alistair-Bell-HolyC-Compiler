#ifndef HOLYC_PARSER_H
#define HOLYC_PARSER_H

#include "inc.h"
#include "util.h"

enum holyc_parse_type {
	/* Junk means non special to the parser, regular chars, used for starting tokens after specials. */
	HOLYC_PARSE_TYPE_JUNK,
	/* Includes spacees, newlines and tabs, also used for ending tokens. */
	HOLYC_PARSE_TYPE_WHITESPACE,
	/* Special includes grammer of the language and will split up tokens if found within (depends on mode). */
	HOLYC_PARSE_TYPE_SPECIAL,
};

/* Tempory chars buffer amount of char count. */
#define HOLYC_UNDER_CONSTRUCTION_SIZE 64 * sizeof(char)


/* 
 * For analysing the stream it each char is analysed for special chars or whitespace / newlines.
 * The right pinsor always advances until no more chars.
 * When a special char is found the substr of the buffer is retrieved using offsets calculated by the pinsor.
 * Then when the token is added the left is set to the right pinsor repeating until no more.
 */
struct holyc_parse_pinsor {
	uint64_t left;
	uint64_t right;
};

/* 
 * Token is a sudo representation of the string it derives from.
 * A token is used for parsing and creating expressions to then convert into a series of instructions.
 * Each token stores the starting index of the character within the buffer, knowledge of the next or the char count can get the origional string.
 */
struct holyc_token {
	holyc_hash_t hash;
	uint64_t start_char_index;
};

/* Data passed throught the functions responsible for adding new tokens and formatting them. */
struct holyc_parse_update_data {
	struct holyc_token **tokens;
	uint32_t *token_count;
	uint32_t alloc_count;
	char **construction;
};

/* 
 * Function that is called for each new char.
 * The running function can switch the next call based on the current char.
 * Paramas:
 *		all the chars,
 *      current char,
 *      last char type,
 *      pointer to source pinsor,
 *      pointer to function,
 *      pointer to add token data,
 */
typedef void (*holyc_parse_function)(char *, const char, enum holyc_parse_type *, struct holyc_parse_pinsor *, void *, void **, struct holyc_parse_update_data *);


/* Turns the chars into tokens, populates the structures */
int8_t holyc_parse_chars(char *, uint32_t, struct holyc_token **, uint32_t *);

/* Default call for char parsing, can only enable specific modes and responsible for apropriate token handling. */
void holyc_parse_type_default(char *, const char, enum holyc_parse_type *, struct holyc_parse_pinsor *, void *, void **, struct holyc_parse_update_data *);
/* Character and string share the same method, different extra stuff param. */
void holyc_parse_type_characters(char *, const char, enum holyc_parse_type *, struct holyc_parse_pinsor *, void *, void **, struct holyc_parse_update_data *);
/* Single line and multiline share the same method, one is newline sensitive. */
void holyc_parse_type_comment(char *, const char, enum holyc_parse_type *, struct holyc_parse_pinsor *, void *, void **, struct holyc_parse_update_data *);

#endif
