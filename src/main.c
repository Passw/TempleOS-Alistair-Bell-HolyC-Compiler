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

#include "inc.h"
#include "util.h"
#include "args.h"
#include "lexer.h"

/* Opens the files, validates its present and not a dir, reads the chars into the buffer. */
static int8_t 
handle_file(const char *file, const char *mode, char **char_buffer, uint32_t *char_count)
{
	/* Stat the file to check that it exists. */
	struct stat st;
	if (stat(file, &st) != 0) {
		fprintf(stderr, "error: unable to find file %s, does it exist?\n", file);	
		return ENOENT;
	}
	/* Check that it actually has blocks. */
	if (st.st_blocks <= 0) {
		fprintf(stdout, "warning: file %s lacks chars, pointless to compile an empty file!\n", file);	
	}

	/* Validate that it is not a directory. */
	if (S_ISDIR(st.st_mode)) {
		fprintf(stderr, "error: %s is a directory, please specify an actual source file!\n", file);
		return ENOENT;
	}

	FILE *f = fopen(file, mode);

	fseek(f, 0, SEEK_END);
	*char_count = ftell(f);
	rewind(f);

	/* 
	 * Allocate the buffer's memory.
	 * Zero the new memory.
	 * fread into the buffer returning success.
	*/
	size_t buffer_size = sizeof(*char_buffer) * (*char_count);
	*char_buffer = (char *)malloc(buffer_size);
	memset(*char_buffer, 0, buffer_size);

	fread((void *)(*char_buffer), buffer_size, sizeof(*char_buffer), f);
	fclose(f);
	return 0; 
}


int
main(int argc, const char **argv)
{
	/* Check that we actually got an argument. */
	if (argc < 2) {
		arguments_help();	
		return 1;
	}

	struct arguments_data data = { 0 };
	/* Misc flags return -1 for no continue. */
	int result;
	if ((result = arguments_handle(argc, argv, &data)) < 0) {
		if (result == -2) {
			arguments_help();
		}
		return 1;
	}

	/* Read the source file.
	 * Fetch the chars that we can parse.
	 */
	const char *target = data.compiling;

	char *chars = NULL;
	uint32_t char_count = 0;
	if (handle_file(target, "r", &chars , &char_count) != 0) {
		fprintf(stderr, "error: failed to compile %s, stage 1 failed.\n", target);
		return 1;
	}

	/*
	 * Call the parse function.
	 * This turns the chars into a series of identified tokens.
	 * The parser is smart and will not split strings and can identify strings against numerical constants.
	 */
	 struct token *tokens; 
	 uint32_t token_count = 0;
	 if (lex_chars(chars, &tokens, &token_count) < 0) {
		fprintf(stderr, "error: failed to compile %s, stage 2 failed.\n", target);
		return 1;
	 }

	if (token_count != 0) {
		free(tokens);
	}
	free(chars);
	return 0;
}
