// who even needs malloc() when you can just write it yourself?

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // sbrk
#include <pthread.h>

// wrapping the above header in a union 
// this will align the header on a 16byte address of memory
// re-call that the size of a union is the larger size of its members 
// so... this garuntees that the end of our header is memory aligned
// the end of the header is where the actual memory block begins
typedef char ALIGN[16];
union header {
	struct {
		size_t size;
		unsigned is_free;
		union header *next;
	} s;
	ALIGN stub;
};
typedef union header header_t;

// head and tail pointer to keep track of our linked-list of mem. blocks
header_t *head, *tail;

// prevent two or more threads from accessing mem. at the same time 
// just using a basic global lock; a thread has to acquire this lock first before it can call malloc(custom)
pthread_mutex_t global_malloc_lock;

// helper function used in malloc() [custom]
header_t *get_free_block(size_t size) {
	header_t *curr = head;
	while(curr) {
		if (curr->s.is_free && curr->s.size >= size) return curr;
		curr = curr->s.next;
	}

	return NULL;
}

// make allocation to heap (custom)
void *malloc (size_t size) {
	// if size is screwed, just return NULL before starting
	if (!size) return NULL;

	// make some variables
	size_t total_size;
	void *block;
	header_t *header;

	// obtain the mutex lock 
	pthread_mutex_lock(&global_malloc_lock);
	
	// idrk what this does yet, stand-by :')
	header = get_free_block(size);

	if (header) {
		header->s.is_free = 0;
		pthread_mutex_unlock(&global_malloc_lock);
		return (void*)(header + 1);
	}

	// calculate total size of our memory block (header + mem. alloc.)
	total_size = sizeof(header_t) + size;

	// allocate memory! woohoo!
	block = sbrk(total_size);

	// check to see if the allocation failed
	if (block == (void*) - 1) {
		// if it did, return NULL and release lock 
		pthread_mutex_unlock(&global_malloc_lock);
		return NULL;
	}

	// fill our header with useful info about this mem. block 
	header = (header_t*)block;
	header->s.size = size;
	header->s.is_free = 0;
	header->s.next = NULL;

	if (!head) head = header;
	if (tail) tail->s.next = header;
	tail = header;
	pthread_mutex_unlock(&global_malloc_lock);
	return (void*)(header + 1);
}

void free(void *block)
{
	header_t *header, *tmp;
	void *programbreak;

	if (!block)
		return;
	pthread_mutex_lock(&global_malloc_lock);
	header = (header_t*)block - 1;

	programbreak = sbrk(0);
	if ((char*)block + header->s.size == programbreak) {
		if (head == tail) {
			head = tail = NULL;
		} else {
			tmp = head;
			while (tmp) {
				if(tmp->s.next == tail) {
					tmp->s.next = NULL;
					tail = tmp;
				}
				tmp = tmp->s.next;
			}
		}
		sbrk(0 - sizeof(header_t) - header->s.size);
		pthread_mutex_unlock(&global_malloc_lock);
		return;
	}
	header->s.is_free = 1;
	pthread_mutex_unlock(&global_malloc_lock);
}

int main(void) {
	
}
