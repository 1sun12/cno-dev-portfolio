// who even needs malloc() when you can just write it yourself?

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // sbrk

// header for every newly allocated block of memory
// HEAP expands and shrinks in LIFO order; we can't just remove memory at the center
// so in order to combat this will be storing some helpful information about each block of mem.
struct header_t {
	size_t size;
	unsigned is_free;
	struct header_t *next;
};

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
		struct header_t *next;
	} s;
	ALIGN stub;
};
typedef union header header_t;

// head and tail pointer to keep track of our linked-list of mem. blocks
header_t *head, *tail;

// prevent two or more threads from accessing mem. at the same time 
// just using a basic global lock; a thread has to acquire this lock first before it can call malloc(custom)
pthread_mutex_t global_malloc_lock;

// make allocation to heap (custom)
void *malloc (size_t size) {
	// create a pointer to no-address (for now)
	void *block = NULL;

	// using syscall "sbrk", increment the brk pointer in HEAP, see "man 2 sbrk" for more info
	// brk points to the end of the HEAP
	// incrementing this pointer results in the allocation of more memory
	// decrementing has the opposite effect
	// sbrk(0);  --> gives current address of the program break
	// sbrk(+x); --> increments brk pointer by +x amount of bytes
	// sbrk(-x); --> decrements brk pointer by -x amount of bytes (returns (void*) -1 if failure)
	//
	// block = [pointer to a newly allocated memory block]
	block = sbrk(size);

	// check for failure ? return NULL if allocation did not work : return pointer to our newly alloc. mem.
	if (block == (void*) -1) {
		return NULL;
	}
	
	return block;
}

int main(void) {
	
}
