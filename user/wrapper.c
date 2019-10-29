#include "wrapper.h"
#include "../common/syscall_nb.h"


void puts(char* str){
  syscall(SYSCALL_PUTS, (int)str, 0, 0, 0);
}

int exec(char* filename){
  printf("__exec\n");
  int ret;
  syscall(SYSCALL_EXEC, (int)filename, &ret, 0, 0);
  return ret;
}

int keypressed(){
  int ret;
  syscall(SYSCALL_KEYPRESSED, &ret, 0, 0, 0);
  return ret;
}

int getc(){
  int ret;
  syscall(SYSCALL_GETC, &ret, 0, 0, 0);
  return ret;
}

int file_stat(char *filename, stat_t *stats){
  int ret;
  syscall(SYSCALL_FILE_STAT, (int)filename, (int)stats, &ret, 0);
  return ret;
}

int file_open(char *filename){
  int ret;
  syscall(SYSCALL_FILE_OPEN, (int)filename, &ret, 0, 0);
  return ret;
}

int file_read(int fd, void *buf, uint_t count){
  int ret;
  syscall(SYSCALL_FILE_READ, (int)(&fd), (int)buf, (int)(&count), &ret);
  return ret;
}

void file_close(int fd){
  syscall(SYSCALL_FILE_CLOSE, (int)(&fd), 0, 0, 0);
}

int file_seek(int fd, uint_t offset){
  int ret;
  syscall(SYSCALL_FILE_SEEK, (int)(&fd), (int)(&offset), &ret, 0);
  return ret;
}

int file_remove(char *filename){
  int ret;
  syscall(SYSCALL_FILE_REMOVE, filename, &ret, 0, 0);
  return ret;
}

file_iterator_t file_iterator(){
  file_iterator_t ret;
  syscall(SYSCALL_FILE_ITERATOR, (int)&ret, 0, 0, 0);
  return ret;
}

bool file_has_next(file_iterator_t *it){
  bool ret;
  syscall(SYSCALL_FILE_HAS_NEXT, (int)it, &ret, 0, 0);
  return ret;
}

void file_next(char *filename, file_iterator_t *it){
  syscall(SYSCALL_FILE_NEXT, (int)filename, (int)it, 0, 0);
}

uint_t get_ticks() {
  uint_t ret;
  syscall(SYSCALL_GET_TICKS, &ret, 0, 0, 0);
  return ret;
}

void putc(char c){
  syscall(SYSCALL_PUTC, &c, 0, 0, 0);
}

// I would like to thank Mr Zaffini for his outstanding work in explaining this function to me
void printf(char* fmt, ...){
  char** argv = (&fmt) + 1;
  syscall(SYSCALL_PRINTF, fmt, argv, 0, 0);
}

int srand(uint_t seed){
  int ret;
  syscall(SYSCALL_SRAND, &seed, &ret, 0, 0);
  return ret;
}

int rand(){
  int ret;
  syscall(SYSCALL_RAND, &ret, 0, 0, 0);
  return ret;
}

void sleep(uint_t ms) {
  syscall(SYSCALL_SLEEP, &ms, 0, 0, 0);
}

void exit(){
  syscall(SYSCALL_EXIT, 0, 0, 0, 0);
}

int strlen(char* str) {
  int ret;
  syscall(SYSCALL_STRLEN, &str, &ret, 0, 0);
  return ret;
}

int strcmp(const char *p, const char *q){
  int ret;
  syscall(SYSCALL_STRCMP, &p, &q, &ret, 0);
  return ret;
}


void read_string(char *buffer){
  syscall(SYSCALL_READ_STRING, &buffer, 0, 0, 0);
}

extern char* trim(char* buf){
  int size = strlen(buf);
  char tmp[size];
  int cpt = 0;
  int i = 0;
  while(i < size){
    if(buf[i] != ' '){
      tmp[cpt] = buf[i];
      cpt++;
    }
    i++;
  }
  tmp[cpt] = '\0';
  for(int i=0; i<cpt; i++){
    buf[i] = tmp[i];
  }
  for(int i=cpt; i<size; i++){
    buf[i] = '\0';
  }
  printf("%s\n",tmp);
  printf("%s\n",buf);
  return buf;
}

extern int starts_with(char* str, char* line){
  int size = strlen(str);
  for(int i = 0; i < size; i++){
    if(str[i+1] != line[i]){
      return 0;
    }
  }
  return 1;
}

//https://www.geeksforgeeks.org/write-your-own-atoi/
extern int atoi(char* str){
  int res = 0; // Initialize result 

  // Iterate through all characters of input string and 
  // update result 
  for (int i = 0; str[i] != '\0'; ++i) 
      res = res*10 + str[i] - '0'; 

  // return result. 
  return res;  
}

