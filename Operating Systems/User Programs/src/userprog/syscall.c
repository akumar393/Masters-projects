#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "threads/vaddr.h"
#include "devices/shutdown.h"

static void syscall_handler (struct intr_frame *);
void* validPtr(void *);
struct file *getFile(int, int*);

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

void* validPtr(void *ptr)
{
	void *temp = NULL;
	if(ptr == NULL)
		return NULL;

	//printf("ptr = %p\n", ptr);
	if(!is_user_vaddr(ptr))
	{
		printf("%s: exit(-1)\n", thread_current()->name);
		thread_exit();
	}
	else
	{
		temp = pagedir_get_page(thread_current()->pagedir, ptr);
		//printf("temp = %p\n", temp);
		if(temp == NULL)
		{
			printf("%s: exit(-1)\n", thread_current()->name);
			thread_exit();
		}
	}
	return temp;

}

struct file* getFile(int fd, int* index)
{
	struct thread *current = thread_current();
	for(int i = 0; i < current->numFiles; i ++)
	{
		if(current->file_list[i].fd == fd)
		{
			*(index) = i;
			return current->file_list[i].file_n;
		}
	}
	return NULL;
}

static void
syscall_handler (struct intr_frame *f UNUSED) 
{
	//printf("SYSCALL_HANDLER IS EXECUTING\n");
	
	if(!validPtr(f->esp))
		return;

	//hex_dump(f->esp , f->esp , 300, true);
	int syscall_num = *((int *)(f->esp));

	//printf("syscall num is %d\n", syscall_num);
	


	switch(syscall_num)
	{
		case SYS_HALT:
			shutdown_power_off();
			break;

		case SYS_EXIT:
			{
				validPtr((f->esp + 4));
				int status = *((int *)(f->esp + 4));
				struct thread *temp_parent = thread_current()->parentPtr;
				int index = thread_current()->index_child;
				temp_parent->child_arr[index].exit_status = status;
				printf("%s: exit(%d)\n", thread_current()->name, status);
				thread_exit();
				//process_exit();
				break;
			}

		case SYS_EXEC:
			{
				validPtr(*(int *)(f->esp + 4));
				void *kernel_ptr = validPtr((f->esp + 4));
				//printf(" kernel_prt = %p\n", (int *)kernel_ptr);
				int len = strlen(*(int *)kernel_ptr);

				//printf("len = %d\n", len);
				char *exec_name = malloc(len + 1);
				memcpy(exec_name, *(int *)kernel_ptr, len + 1);

				//printf("value = %s\n", exec_name);
				f->eax = process_execute(exec_name);

				free(exec_name);
				break;
			}

		case SYS_WAIT:
			{
				int child_pid = *((int *)(f->esp + 4));
				//printf("Before waiting\n");
				f->eax = process_wait(child_pid);
				//process_wait(child_pid);
				//printf("After watintg\n");
				break;
			}

		case SYS_CREATE:
			{
				//printf("f->esp + 4 = %p\n", (int *)(f->esp + 4));
				//printf("*(f->esp + 4) = %s\n ", *(int*)(f->esp + 4));

				void *value_ptr = validPtr(*(int *)(f->esp + 4));
				if(value_ptr == NULL)
				{
					printf("%s: exit(-1)\n",thread_current()->name);
					thread_exit();
					break;
				}	
				void *kernel_ptr = validPtr(f->esp + 4);
				int len = strlen(*(int *)kernel_ptr);

				char *file_name = malloc(len + 1);
				memcpy(file_name, *(int *)kernel_ptr, len + 1);

				int file_len = *(int *)(f->esp + 8);


				f->eax = filesys_create(file_name, file_len);
				free(file_name);
				break;
			}

		case SYS_OPEN:
			{
				void *value_ptr = validPtr(*(int *)(f->esp + 4));
				if(value_ptr == NULL)
				{
					f->eax = -1;
					break;
				}
				void *kernel_ptr = validPtr(f->esp + 4);
				int len = strlen(*(int *)kernel_ptr);

				char *file_name = malloc(len + 1);
				memcpy(file_name, *(int *)kernel_ptr, len + 1);

				struct thread *current = thread_current();
				struct file *temp = filesys_open(file_name);
				//printf("Open temp = %p\n", temp);
				if(temp)
				{
					current->file_list[current->numFiles].file_n = filesys_open(file_name);
					current->file_list[current->numFiles].fd = (current->numFiles) + 2;
					current->file_list[current->numFiles].openStat = true;
					//printf("fd = %d file = %p\n", current->file_list[current->numFiles].fd, current->file_list[current->numFiles].file_n);
					//printf("current->numFiles = %d\n", current->numFiles);
					f->eax = current->file_list[current->numFiles].fd;
					current->numFiles++;
					//printf("f->eax = %d\n", f->eax);
				

					/*if(temp == current->exec_ptr)
						file_deny_write(temp);*/
				}
				else
					f->eax = -1;
				free(file_name);
				break;
			}

		case SYS_CLOSE:
			{
				void *kernel_ptr = validPtr(f->esp + 4);
				int index;
				struct file* temp = getFile(*(int *)(f->esp + 4), &index);
				if((temp == NULL) || !(thread_current()->file_list[index].openStat))
				{
					f->eax = -1;
					break;
				}
				thread_current()->file_list[index].openStat = false;
				file_close(temp);
				if(temp == thread_current()->exec_ptr)
				{
					//file_deny_write(temp);
				}
				break;
			}

		case SYS_READ:
			{
				void *kernel_ptr = validPtr(f->esp + 4);
				int index;
				struct file* temp = getFile(*(int *)(f->esp + 4), &index);
				if(temp == NULL)
				{
					f->eax = -1;
					break;
				}

				kernel_ptr = validPtr(*(int *)(f->esp + 8));

				if(kernel_ptr == NULL)
				{
					f->eax = -1;
					break;
				}


				kernel_ptr = validPtr(f->esp + 8);

				//printf("*kernel_ptr = %p\n", *(int*)kernel_ptr);

				int bufLen = *(int *)(f->esp + 12);

				//printf("bufLen = %d kernel_ptr = %p\n", bufLen, kernel_ptr);

				f->eax = file_read(temp, *(int *)kernel_ptr, bufLen);

				break;
			}

		case SYS_FILESIZE:
			{
				void *kernel_ptr = validPtr(f->esp + 4);
				int index;
				struct file* temp = getFile(*(int *)(f->esp + 4), &index);
				if(temp == NULL)
				{
					f->eax = -1;
					break;
				}

				f->eax = file_length(temp);
				break;
			}

		case SYS_WRITE:
			{
				int fd;
				fd = *((int *)(f->esp + 4));
				//printf("INside write\n");
				//printf("fd is %d\n", fd);
				//printf("f->esp = %p\n", f->esp);
				//printf("f->esp+8= %p f->esp+12 = %p\n", f->esp + 8, f->esp + 12);
				//printf("*(f->esp+8) = %p", *(int*)(f->esp + 8));
				//printf("*(f->esp + 12) = %p\n",*(int*)(f->esp + 12));
				if(fd == 1)
					putbuf(*(int*)(f->esp + 8), *(int*)(f->esp + 12));
				
				else
				{
					void *kernel_ptr = validPtr(f->esp +4);
					int index;
					struct file *temp = getFile(*(int *)(f->esp + 4), &index);
					if(temp == NULL)
					{
						f->eax = -1;
						break;
					}

					kernel_ptr = validPtr(*(int *)(f->esp + 8));
					if(kernel_ptr == NULL)
					{
						f->eax = -1;
						break;
					}

					kernel_ptr = validPtr(f->esp + 8);

					//printf("write *kernel_ptr = %p\n", *(int *)kernel_ptr);
					int bufLen = *(int *)(f->esp + 12);

					f->eax = file_write(temp, *(int *)kernel_ptr, bufLen);

				}

			}

			break;

		case SYS_TELL:
			{
				void *kernel_ptr = validPtr(f->esp + 4);
				int index;
				struct file* temp = getFile(*(int *)(f->esp + 4), &index);
				if(temp == NULL)
				{
					f->eax = -1;
					break;
				}

				f->eax = file_tell(temp);
				break;
			}

		case SYS_SEEK:
			{
				void *kernel_ptr = validPtr(f->esp + 4);
				int index;
				struct file* temp = getFile(*(int *)(f->esp + 4), &index);
				if(temp == NULL)
				{
					f->eax = -1;
					break;
				}

				int pos = *(int *)(f->esp + 8);
				file_seek(temp, pos);
				break;
			}

		case SYS_REMOVE:
			{
				//printf("*(f->esp + 4) = %s\n", *(int *)(f->esp + 4));
				void *kernel_ptr = validPtr(*(int *)(f->esp + 4));
				//printf("kernel_ptr1 = %p\n", kernel_ptr);
				if(kernel_ptr == NULL)
				{
					f->eax = 0;
					break;
				}
				kernel_ptr = validPtr(f->esp + 4);
				//printf("kernel_ptr2 = %p\n", kernel_ptr);
				int len = strlen(*(int *)kernel_ptr);

				char* file_name = malloc (len + 1);
				memcpy(file_name, *(int *)kernel_ptr, len + 1);

				f->eax = filesys_remove(file_name);
				//printf("f->eax = %d\n", f->eax);

				free(file_name);
				break;
			}

	}
  //printf ("system call!\n");
  //thread_exit ();
}
