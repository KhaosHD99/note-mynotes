#ifndef CPRODCONS_DEF
#define CPRODCONS_DEF
#define BUFFER_SIZE 10
#define PRODUCER_SLEEP 1
#define CONSUMER_SLEEP 2

class CProdCons
{
    public:
	  typedef struct ProdCons 
      {
         int buffer[BUFFER_SIZE];
         pthread_mutex_t lock; 
         int readpos, writepos;
         sem_t empty_sem;
         sem_t full_sem;
      }ProdCons;
	  int in;
      int out;
	  ProdCons *pc_buffer;

    
		
      CProdCons();	
      void Init();
	  void Write(ProdCons *pc_buffer, int data);
	  void Read(ProdCons *pc_buffer);
	  void ShowBuffer();
	  //static void*  Producer_thread(void *data);
	  //static void*  Consumer_thread(void *data);
	  
    
};


#endif
