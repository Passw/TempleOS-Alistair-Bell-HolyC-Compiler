/* 
 * Copyright (c) 2021 Alistair Bell <alistair@alistairbell.xyz>
 *
 * HolyC compiler is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "parser.h"

static void
holyc_parse_add_token(char *chars, struct holyc_parse_pinsor *pinsor, struct holyc_parse_update_data *data)
{
	/* Clean the previous junk that the construction had. */
	memset(*data->construction, 0, HOLYC_UNDER_CONSTRUCTION_SIZE);
	/* Copy the data to the buffer. */
	strncpy(*data->construction, chars + pinsor->left, pinsor->right - pinsor->left);

	/* Check for another batch token increase. */
	if (data->alloc_count <= *data->token_count + 1) {
		data->alloc_count += 20;
		*data->tokens = (struct holyc_token *)realloc(*data->tokens, sizeof(struct holyc_token) * data->alloc_count);
	}

	fprintf(stdout, "holyc: new token -> %s\n", *data->construction);

	struct holyc_token *insertion = &((*data->tokens)[(*data->token_count)]);

	*insertion = (struct holyc_token) {
		.hash = holyc_hash_chars(*data->construction),
		.start_char_index = pinsor->right,
	};
	++(*data->token_count);
}

void
holyc_parse_mode_characters(char *chars, const char current_char, enum holyc_parse_type *last_type, struct holyc_parse_pinsor *pinsor, void *baton, void **next_call, struct holyc_parse_update_data *update_data)
{
	/* Char that made the mode switch, " or '. */
	char start_char = *((char *)baton);
	if (current_char == start_char) {

		pinsor->right++;
		/* Add the big string or characters token. */
		holyc_parse_add_token(chars, pinsor, update_data);
		pinsor->left = pinsor->right;


		/* Change back to the default function. */
		*next_call = holyc_parse_type_default;

		/* Blatant lie. */
		*last_type = HOLYC_PARSE_TYPE_JUNK;
	};
}

void
holyc_parse_type_default(char *chars, const char current_char, enum holyc_parse_type *last_type, struct holyc_parse_pinsor *pinsor, void *baton, void **next_call, struct holyc_parse_update_data *data)
{
	if (pinsor->left > pinsor->right)
		return;

	switch (current_char) {
		case '\t' ... ' ': {
			if (*last_type != HOLYC_PARSE_TYPE_WHITESPACE) {
				holyc_parse_add_token(chars, pinsor, data);
			}
			pinsor->left = pinsor->right;
			pinsor->left++;
			*last_type = HOLYC_PARSE_TYPE_WHITESPACE;
			break;
		}

		/* Use fallthrough for regular characters. */

		case '0' ... '9': 
			/* FALLTHROUGH */
		case 'A' ... 'Z':
			/* FALLTHROUGH */
		case 0x5f ... 'z': {
			
			/* If a regular char proceeds a special add it to the list of tokens. */
			if (*last_type == HOLYC_PARSE_TYPE_SPECIAL) {
				holyc_parse_add_token(chars, pinsor, data);
				pinsor->left = pinsor->right;
			}

			/* Set the last type to junk. */
			*last_type = HOLYC_PARSE_TYPE_JUNK;
			break;
		}

		/* Default is for special chars, easier to use fallthroughs for regular chars as they are more bunched up. */
		default: {

			if (*last_type != HOLYC_PARSE_TYPE_WHITESPACE) {
				holyc_parse_add_token(chars, pinsor, data);
			}
			pinsor->left = pinsor->right;

			*last_type = HOLYC_PARSE_TYPE_SPECIAL;
		}
	}
}

int8_t 
holyc_parse_chars(char *chars, uint32_t char_count, struct holyc_token **tokens, uint32_t *token_count)
{
	/* Pinsor used like a claw for grabbing tokens. */
	struct holyc_parse_pinsor p = { 0 };

	/* Start in default mode. */
	holyc_parse_function callback = holyc_parse_type_default;

	/* Always have a non incrimented buffer. */
	char *chars_copy = chars;
	/* Stores the current character being inspected. */
	char current_char;

	/* 
	 * Prepare the memory. 
	 * In this situation the program gueses by the char count to how many to tokens to pre allocate, saves constant reallocation.
	 */
	*tokens = (struct holyc_token *)calloc((char_count / 4) + 5, sizeof(*(*tokens)));

	/* Last type of char that was inspected. */
	enum holyc_parse_type last_type = HOLYC_PARSE_TYPE_WHITESPACE;

	/* Buffer to parse to the hasher where a token is stored. */
	char *under_construction = (char *)malloc(HOLYC_UNDER_CONSTRUCTION_SIZE);

	/* Extra data passed onto the next function call, call specific data. */
	void *baton = malloc(sizeof(*baton));
	
	struct holyc_parse_update_data data = {
		.tokens = tokens,
		.alloc_count = (char_count / 4) + 5,
		.token_count = token_count,
		.construction = &under_construction,
	};
	
	/* Fixes stupid bug. */
	if ('\b' <  *chars && *chars < '!') {
		++p.left;
	}

	/* Loop througth the chars. */
	while ((current_char = *(chars_copy++))) {
		callback(chars, current_char, &last_type, &p, baton, (void **)&callback, &data);
		++p.right;
	}

	/* Reallocate the size of the token storage to what it actually needs to be. */
	*tokens = (struct holyc_token *)realloc(*tokens, *token_count * sizeof(*(*tokens)));

	free(under_construction);
	free(baton);
	return 0;
}
