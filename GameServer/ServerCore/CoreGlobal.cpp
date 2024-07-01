<<<<<<< Updated upstream
#include "pch.h"
#include "CoreGlobal.h"
#include "ThreadManager.h"
#include "DeadLockProfiler.h"
#include "Memory.h"
ThreadManager* GThreadManager = nullptr;
DeadLockProfiler* GDeadLockProfiler = nullptr;
Memory* GMemory = nullptr;
class CoreGlobal
{
public:
	CoreGlobal() {
		GThreadManager = new ThreadManager();
		GMemory = new Memory();
		GDeadLockProfiler = new DeadLockProfiler();
	}
	~CoreGlobal() {
		delete GThreadManager;
		delete GDeadLockProfiler;
		delete GMemory;
	}

private:


};

=======
#include "pch.h"
#include "CoreGlobal.h"
#include "ThreadManager.h"
#include "DeadLockProfiler.h"
#include "Memory.h"
ThreadManager* GThreadManager = nullptr;
DeadLockProfiler* GDeadLockProfiler = nullptr;
Memory* GMemory = nullptr;
class CoreGlobal
{
public:
	CoreGlobal() {
		GThreadManager = new ThreadManager();
		GMemory = new Memory();
		GDeadLockProfiler = new DeadLockProfiler();
	}
	~CoreGlobal() {
		delete GThreadManager;
		delete GDeadLockProfiler;
		delete GMemory;
	}

private:


};

>>>>>>> Stashed changes
CoreGlobal Core;