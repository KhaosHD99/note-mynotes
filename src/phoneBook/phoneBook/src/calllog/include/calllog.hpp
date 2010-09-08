class CCalllogManager
{
	typedef struct CallLog_Info
	{
		int count;
		CL_STATUS status;
		CallLog **calllog_buffs;
	}CallLog_Info;

	private:
		LpConfig * calllog_lpconfig;

		CallLog_Info calllog_missed, calllog_received, calllog_dailed;
		static CCalllogManager *calllog_instance;
	
	private:
		void init()
		{
			init_logs(&calllog_missed);
			init_logs(&calllog_received);
			init_logs(&calllog_dailed);
		}
	
		void init_log(CallLog_Info *clInfo)
		{
		    clInfo->count = 0;
            clInfo->calllog_buf = new CallLog*[MAX_CALLLOG_COUNT];

			for(int i = 0; i < MAX_CALLLOG_COUNT; i++)
			{
				clInfo->calllog_buf[i] = NULL;											//动态申请内存， 如int add(Contact contact)
			}
		}
	
		void uninit()
		{
			uninit_log(&calllog_missed);
			uninit_log(&calllog_received);
			uninit_log(&calllog_dailed);
		}

		void uninit_log(CallLog_Info *clInfo)
		{
			for(int i = 0; i < clInfo->count;	i++)
			{
				delete clInfo->calllog_buf[i];
				clInfo->calllog_buf[i] = NULL;
			}
			delete clInfo->calllog_buf;
			clInfo->calllog_buf = NULL;
		}
	
	public:
		static CCalllogManager *get_Instance();												//获最CCalllogManager对象，单一模式(全局只有一个对象)

		int load_logs_from_file();															//

		int get_calllog_count_by_type(CLSTATUS status);										//获取对应记录总量

		int get_calllog_by_index(CLSTATUS status, int index, CallLog *calllog);				//获取记录条目
		
		int add_calllog(CLSTATUS status, CallLog *calllog);

		int delete_calllog_by_index(CLSTATUS status, int index);

		int delete_calllog_all(CLSTATUS status);
		
		//sort
		void sort_by_date();																//有新往旧排

		int save_file();																	//

};

