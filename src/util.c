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

#include "util.h"

#define HASH_TABLE_STARTING_ALLOC 50
#define HASH_TABLE_NEW_BATCH_FORMULAR(ac, mem) \
    ac * ((ac / HASH_TABLE_STARTING_ALLOC) + 1) * sizeof(mem)

hash_t
hash_chars(char *chars)
{

	/* Running of the hash first initialsed for bitshifts to work on the subsequent passes. */
	hash_t total = 5381;

	char c;
	while ((c = *chars++)) {
		total += ((total << 6) + total) + c;
	}
	return total;
}
