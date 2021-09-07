#ifndef HOLYC_PARSER_H
#define HOLYC_PARSER_H

#include "inc.h"
#include "util.h"

enum parser_type {
	/* Junk means non special to the parser, regular chars, used for starting tokens after specials. */
	PARSE_TYPE_JUNK,
	/* Includes spacees, newlines and tabs, also used for ending tokens. */
	PARSE_TYPE_WHITESPACE,
	/* Special includes grammer of the language and will split up tokens if found within (depends on mode). */
	PARSE_TYPE_SPECIAL,
};

/* Tempory chars buffer amount of char count. */
#define UNDER_CONSTRUCTION_SIZE 64 * sizeof(char)


/* 
 * For analysing the stream it each char is analysed for special chars or whitespace / newlines.
 * The right pinsor always advances until no more chars.
 * When a special char is found the substr of the buffer is retrieved using offsets calculated by the pinsor.
 * Then when the token is added the left is set to the right pinsor repeating until no more.
 */
struct pinsor {
	uint64_t left;
	uint64_t right;
};

/* 
 * Token is a sudo representation of the string it derives from.
 * A token is used for parsing and creating expressions to then convert into a series of instructions.
 * Each token stores the starting index of the character within the buffer, along with the length of it which can be used to extract the string without decoding the hash.
 */
struct token {
	hash_t hash;
	uint64_t start;
    uint16_t length;
};

/* Data passed throught the functions responsible for adding new tokens and formatting them. */
struct parser_update_data {
	struct token **tokens;
	uint32_t *token_count;
	uint32_t alloc_count;
	char **construction;
    uint32_t construction_size;
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
typedef void (*parser_function)(char *, const char, enum parser_type *, struct pinsor *, void *, void **, struct parser_update_data *);


/* Turns the chars into tokens, populates the structures */
int8_t parser_chars(char *, uint32_t, struct token **, uint32_t *);

/* Default call for char parsing, can only enable specific modes and responsible for apropriate token handling. */
void parser_mode_default(char *, const char, enum parser_type *, struct pinsor *, void *, void **, struct parser_update_data *);
/* Character and string share the same method, different extra stuff param. */
void parser_mode_characters(char *, const char, enum parser_type *, struct pinsor *, void *, void **, struct parser_update_data *);
/* Single line and multiline share the same method, one is newline sensitive. */
void parser_mode_comment(char *, const char, enum parser_type *, struct pinsor *, void *, void **, struct parser_update_data *);

#endif
