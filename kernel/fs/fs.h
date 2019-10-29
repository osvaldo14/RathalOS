#include "../../common/fs/inode.h"
#include "../drivers/ide.h"

#define FILE_DESCRIPTOR_TAB_SIZE 50
#define GLOBAL_BUFFER_SIZE 10000

typedef struct __attribute__ ((__packed__)) {
	int size;
	inode_t* inode;
} stat_t;

typedef struct __attribute__ ((__packed__)) {
	inode_t* inode;
} file_iterator_t;

typedef struct __attribute__ ((__packed__)) {
	inode_t* inode;
	uint8_t status;
	uint_t offset;
} file_open_t;

void file_superbloc_init();
void inode_table_init();
void file_inode_bitmap_init();

void files_system_init();


int file_stat(char *filename, stat_t *stat);

bool file_exists(char *filename);
int file_remove(char *filename);

int file_open(char *filename);
int file_read(int fd, void *buf, uint_t count);
int file_seek(int fd, uint_t offset);
void file_close(int fd);

file_iterator_t file_iterator();

bool file_has_next(file_iterator_t *it);
void file_next(char *filename, file_iterator_t *it);

void print_inode(int fd);

