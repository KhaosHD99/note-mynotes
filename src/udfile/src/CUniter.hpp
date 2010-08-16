#ifndef CUNITER_DEF
#define CUNITER_DEF

class CUniter
{
   public:
	 CUniter(char* savepath, char*filename);
     void Unite();
	 char *GetFileName(char *filepath);

   private:
	 char *p_filename;
	 char *p_savepath;

};
#endif

