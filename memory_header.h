
typedef struct memorystruct  // structure to store info about memeory and occupied and free memoery spaces 
{    
     char * start_add; // starting address of memeory;
     int  mem_size; // memory offset
     struct memorystruct* next_mem;// next memory storage
}memory;


extern memory * create_node(memory * mem,int i,char * addr);
extern void insert_end(memory **head,int i,char * add,memory* mem);
extern memory * deletee(memory **head,char * add );
extern void insert(memory **head,memory * t );

extern void* allocate(int size);
extern void deallocate(void* ptr);









