#ifndef USERPROG_PROCESS_H
#define USERPROG_PROCESS_H

#include "threads/thread.h"
#include "filesys/off_t.h"

tid_t process_execute (const char *file_name);
int process_wait (tid_t);
void process_exit (void);
void process_activate (void);

/*struct cs_map
{
	struct cs_map* next;
	struct file* file;
	off_t ofs;
	uint32_t readbytes;
	uint32_t zerobytes;
	uint8_t* uvaddr;
	bool loaded;
	bool writable;
}*map_head;*/

bool lazy_load_segment(struct file* file, off_t ofs, uint8_t* upage, uint32_t readbytes, uint32_t zerobytes, bool writable);
bool lazy_load_page(struct file* file, off_t ofs, uint8_t* upage, uint32_t readbytes, uint32_t zerobytes, bool writable);

#endif /* userprog/process.h */
