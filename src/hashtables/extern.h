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

#ifndef HOLYC_HASHTABLES_EXTERN_H
#define HOLYC_HASHTABLES_EXTERN_H

#include "../inc.h"

/* Hash table implimentation information.
 * ======================================
 *
 * The hash-type is defined in src/inc.h and is not directly controlled by this implimentation.
 * Each hash table is batch reallocated defined by a constant.
 * Each element within the root table stores a bucket, this helps deal with conflicts caused by likewise elements.
 * Until a conflict has occurred the bucket is void and instead the hash resides.
 * Searches consist of a single 64 bit unsigned integer. The lower 32 represent the root table index, upper the bucket index.
 *     If the root index does not contain an bucket then the hash_table_home->bucket_index will be 0,
 * Hash table buckets use sorted array of hashes, binary search is used to find the resident.
 */

#define HASH_TABLE_START_SIZE 50

struct hash_table {
	struct bucket *buckets;
	uint32_t bucket_count;
};
struct bucket {
	hash_t *residents;
	uint32_t resident_count;
	uint32_t alloc_count;
};

struct hash_table_home {
	uint64_t combined;
	union {
		struct {
			uint32_t root_index;
			uint32_t bucket_index;
		};
	};
};

/* Uses the amount of hashes to decide the apropriate algorithm that the sort uses, small numbers avoid large allocation based methods - merge or radix. */
void bucket_sort(struct bucket *);
/* A simple binary search algorithm, returns -1 on failure */
int64_t binary_search(hash_t *, hash_t, uint32_t, uint32_t);

void hash_table_create(struct hash_table *);
void hash_table_insert(struct hash_table *, hash_t *);
void hash_table_insert_batch(struct hash_table *, hash_t *, uint32_t);
/* Will return the home as UINT32_MAX on both of the members if it has not been found. */
struct hash_table_home hash_table_find(struct hash_table *, hash_t *);
void hash_table_destroy(struct hash_table *);

#endif
