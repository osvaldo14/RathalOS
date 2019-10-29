
#include "../display/display.h"
#include "../../common/fs/superblock.h"
#include "fs.h"
#include "../../common/func.h"

static uint8_t global_buffer[GLOBAL_BUFFER_SIZE];

static superblock_t* superblock; // 0 - 511
static bitmap_t inode_bitmap; // 512 - 2047
static inode_table_t inode_table; // 2048 - 4095
static file_open_t file_descriptor_tab[FILE_DESCRIPTOR_TAB_SIZE];


void file_superbloc_init(){
	ide_read_sector(0, &global_buffer[0]);
	superblock = (superblock_t*)&global_buffer[0];
}

void file_inode_bitmap_init(){
	ide_read_sector(superblock->inode_bitmap_start,&global_buffer[SECTOR_SIZE]);
	inode_bitmap.bits = (uint8_t*)&global_buffer[SECTOR_SIZE];
	inode_bitmap.count = superblock->inode_count; // ! size in bytes not this
	inode_bitmap.size = superblock->inode_bitmap_block_count * superblock->block_size;
}

void inode_table_init(){
	ide_read_sector(superblock->inode_start, &global_buffer[4*SECTOR_SIZE]);
	inode_table.inodes = (inode_t*)&global_buffer[4*SECTOR_SIZE];
	inode_table.inode_count = superblock->inode_count;
	inode_table.size = superblock->inode_count * sizeof(inode_t);
}

//Init the file descriptor tab:
void fdescriptor_tab_init(){
	memset(file_descriptor_tab,0,FILE_DESCRIPTOR_TAB_SIZE*sizeof(file_open_t));
}


void files_system_init() {
	file_superbloc_init();
	file_inode_bitmap_init();
	inode_table_init();
	fdescriptor_tab_init();
}


bool file_exists(char *filename){
	return (inode_get_from_filename(&inode_table, filename) != NULL);
}


int file_remove(char *filename){
	if( file_exists( filename ) ){
		inode_t * inode = inode_get_from_filename( &inode_table, filename );
		bitmap_set(&inode_bitmap, inode->number, 0);
		memset(&inode_table.inodes[inode->number], 0, sizeof( inode_t ));
		return 0;
	} else 
		return 1;
}

int file_open(char *filename){
	if(file_exists(filename)){
		for (int i = 0; i < FILE_DESCRIPTOR_TAB_SIZE ; ++i){
			if(file_descriptor_tab[i].status == 0){
				file_descriptor_tab[i].inode = inode_get_from_filename( &inode_table, filename );
				file_descriptor_tab[i].status = 1;
				file_descriptor_tab[i].offset = 0;
				return i;
			}
		}
	return -1;
	} else
		return -1;
}

int file_read(int fd, void *buf, uint_t count){
	if (file_descriptor_tab[fd].status < 1){
		return -1;
	}
	int block = 0; //get_block_from_offset(fd);

	//How many sectors to read
	int read = count/SECTOR_SIZE;
	int data_start = superblock-> datablocks_start;

	int block_adresses_per_block = SECTOR_SIZE / 2; //number of blocks adressed by 1 indirect block
	int indirect_block; 
	int adress_in_indirect_block;
	int data_block;
	int adress_block;

	if(block >= 0){ // the block is valid
		do {
			if(block < INODE_DIRECT_PTR_CNT){
				data_block = file_descriptor_tab[fd].inode->direct_ptr[block];
				ide_read_sector(data_start + data_block,buf);
			}else if(block >= INODE_DIRECT_PTR_CNT && block < (INODE_INDIRECT_PTR_CNT * block_adresses_per_block)){
				block -= INODE_DIRECT_PTR_CNT; // remove the offset from direct blocks
				indirect_block = block / block_adresses_per_block;
				adress_block = file_descriptor_tab[fd].inode->indirect_ptr[indirect_block];
				adress_in_indirect_block = 2 * (block % block_adresses_per_block);		
				ide_read_sector(data_start + (adress_block + adress_in_indirect_block) + 1, buf); 
				block += INODE_DIRECT_PTR_CNT;
			}
			block++;
			buf += (SECTOR_SIZE / sizeof(uint8_t)); // déplacer le pointeur d'écriture dans le buffer
		} while(read--);
		ide_read_sector(data_start + (data_block + adress_in_indirect_block),buf);
		return count;
	}
	return -1;
}

int file_seek(int fd, uint_t offset){
	if(file_descriptor_tab[fd].status == 1){
		file_descriptor_tab[fd].offset = offset;
		return offset;
	}else
		return -1;
}

void file_close(int fd){
	file_descriptor_tab[fd].status = 0;
}


file_iterator_t file_iterator(){
	file_iterator_t iterator;
	iterator.inode = &inode_table.inodes[0];
	return iterator;
}

bool file_has_next(file_iterator_t *it){

	uint_t number = it->inode->number;
	return !(inode_get_next(&inode_table, number) == NULL);
}

void file_next(char *filename, file_iterator_t *it){
	uint_t number = it->inode->number;
	if( file_has_next(it) ){
		inode_t* next_inode = inode_get_next( &inode_table, number );
		it->inode = next_inode;
		memcpy( filename, it->inode->name, INODE_FILENAME_LENGTH );
	}

}


int file_stat(char *filename, stat_t *stat){
	if( file_exists( filename ) ){
		inode_t *inode = inode_get_from_filename( &inode_table, filename );
		stat->size = inode->size;
		stat->inode = inode;		
		return 1;
	}
	return 0;

}

int get_block_from_offset(int fd){
	uint_t block_size = superblock->block_size;
	uint_t offset = file_descriptor_tab[fd].offset;
	if((offset / block_size) < INODE_DIRECT_PTR_CNT){
		//Direct block
		return (offset/SECTOR_SIZE);
	}
	else if((offset / block_size) > INODE_DIRECT_PTR_CNT && (offset / block_size) < (INODE_INDIRECT_PTR_CNT * block_size / sizeof(int*))){
		return offset/SECTOR_SIZE;
	}else
		return -1;
}

void print_inode(int fd){
	//Load inode
	inode_t *inode = file_descriptor_tab[fd].inode;
	printf("number : %d\nname : %s\nsize : %d\n",inode->number,inode->name,inode->size);
	for(int i=0;i<INODE_DIRECT_PTR_CNT;i++){
		printf("direct_ptr[%d] : %d\n",i,inode->direct_ptr[i]);
	}
	for(int j=0;j<INODE_INDIRECT_PTR_CNT;j++){
		printf("indirect_ptr[%d] : %d\n",j,inode->indirect_ptr[j]);
	}
}

