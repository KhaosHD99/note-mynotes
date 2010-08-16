#ifndef CDIVIDER_DEF
#define CDIVIDER_DEF

class CDivider
{
    
    public:
		
      CDivider(char *filename,char *savepath,int count);	
      void ShowTest();
	  void Divide();
	  int GetFileSize(char *filename);

	private:
	  char *p_filename;
	  char *p_savepath;
	  int m_count;
      int i;
};

#endif



