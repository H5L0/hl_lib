

typedef void *hlThread;

typedef ureg *hlThreadResult;

typedef hlThreadResult(HL_API *hThreadCallback)(void *);

typedef ureg(HL_API *hlTask)(void *);


struct hlThread
{
	void *handle;
	int prority;
}



hlThread *hlCreateThread(hlTask task, void *ptr_arg);

//Unsafe
//(args_count, task, arg0, arg1, ...)	//args_count = 2
hlThread *hlCreateThreadUnsafe(t_size argc, ...);

hlThread *hlCreateThreadUnsafe(void* task, void *ptr_arg, t_size count_arg);


bool hlSetThreadPriority(hlThread *pThread, enum Priority priority);
bool hlSetThreadBackground(hlThread *pThread, bool isBackground);


void hlStartThread(hlThread *pThread);

//void hlResumeThread(hlThread *pThread);

void hlReleaseThread(hlThread *pThread);


//--  static function  --

void hlSleep(u32 time1000);

void hlSuspuendThread();	//??
bool hlSwitchThread();
void hlExitThread(ureg exit_code);


void hlpcStart();

void hlthStart();





