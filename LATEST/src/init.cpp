typedef enum{
      E_SHUTDOWN_NORMAL
   ,  E_SHUTDOWN_ABNORMAL
}t_Shutdown;

t_Shutdown e_Shutdown = E_SHUTDOWN_NORMAL;

int main(
#if(_ReSIM == STD_ON)
#else
   void
#endif
){
   return e_Shutdown;
}

