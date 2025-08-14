#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"memory_header.h"

char sram[100*1000];// the SRAM of size 100KB whose memory address are allocated or deallocated
memory fre;

memory * allochead=NULL;//header of allocation list
memory *  freehead = &fre; // header of free list
memory* storealloc; // store memory structure add
     memory empty; // variable
memory * create_node(memory * mem,int i,char * addr)
 {   
      mem->start_add = addr;   // creating node by adding starting of allocated addr
      mem->mem_size=i;
      mem->next_mem= NULL;
      return mem;
 } 

  void insert_end(memory **head,int i,char * add,memory* mem)
  {
      if(add==NULL)
      {              // insert or adding memory structure to list 
        return ;
      } 
       memory * new= create_node(mem,i,add);
      
     
      if(*head==NULL)
      {
          *head=new;
          return ;
      }
      memory * temp = *head;
       while(temp->next_mem!=NULL)
       {
          temp=temp->next_mem;
       }
       temp->next_mem=new;

  }


  void insert(memory **head,memory * t )
  {
      if(t->start_add==NULL)
      {
        return ;
      }              // inserting already created structure mem
      if(*head==NULL)
      {
          *head=t;
          return ;
      }
      memory * temp = *head;
       while(temp->next_mem!=NULL)
       {
          temp=temp->next_mem;
       }
       temp->next_mem=t;

  }

  

   memory * deletee(memory **head,char * add )
  {
       if(add==NULL)
       {
         return NULL;
       }
      if(*head==NULL)    // deleting structure
      {
          return NULL;
      }
      memory * temp = *head;
      memory * prev=*head;
      int i=0;
              while(temp!=NULL)
       {  
         i++;
          if(temp->start_add== add&&i==1)
          {
            *head=temp->next_mem;
            break;
          } 
          else if(temp->start_add== add)
          {
                prev->next_mem=temp->next_mem;
               break;
          }
           prev=temp;
          temp=temp->next_mem;
       }
           temp->next_mem=NULL;
        return temp;

  }

void* allocate(int size)
{
    memory * freetemp= freehead;
    memory * temp= allochead;
     empty.start_add=NULL;         // allocating adddress
     int diff=100*1000;
     char * m;
      if(freetemp->next_mem==NULL)
         {   
              memory * memry=(memory *)fre.start_add;
             insert_end(&allochead,size,fre.start_add+sizeof(memory),memry);
             fre.start_add=fre.start_add+size+sizeof(memory);
             fre.mem_size=fre.mem_size-size-sizeof(memory);
             return memry->start_add;
              
         }
         storealloc=&empty;
       while(freetemp!=NULL)
    {
        
        if(freetemp->mem_size>=size)
        {
           if(freetemp->mem_size==size)
           {
             storealloc=freetemp;
             break;
           }
            
          else
          {
             
            if(freetemp->mem_size-size>0&&freetemp->mem_size-size<diff)
            {
                diff= freetemp->mem_size-size;
                storealloc=freetemp;
            }
          }
           
        }
        freetemp=freetemp->next_mem;
    }
      storealloc=deletee(&freehead,storealloc->start_add);
     insert(&allochead,storealloc);
             return storealloc->start_add;
     

}

void deallocate(void* ptr)
{
  
     memory *prev;
      if(allochead==NULL)
         {   
             return;          // deallocating 
         }
           
            prev=deletee(&allochead,ptr);
             insert(&freehead,prev);     
          
           
    }  


int main()
{
    fre.start_add = sram;
      fre.mem_size=100*100;
      fre.next_mem= NULL;
   int *m[4];
   m[0]=allocate(100);
   m[1]=allocate(1024);
   m[2]=allocate(4096);
    deallocate(m[1]);
   m[1]=allocate(512);
   
   return 0;
}


