#pragma once
#include <stack>
#include <map>
#include <vector>
#include <set>

/*--------------------
	DeadLockProfiler
---------------------*/



class DeadLockProfiler
{
public:
	void PushLock(const char* name);
	void PopLock(const char* name);
	void CheckCycle();
private:
	void Dfs(int32 index);
private:
	unordered_map<const char*, int32> _nameTold;
	unordered_map<int32,const char*> _idToName;
	stack<int32>					_lockStack;
	map<int32, set<int32>>			_lockHistory;

	mutex _lock;

private:
	vector<int32> _discoverdOrder;
	int32 _discoveredCount = 0;
	vector<bool>	_finished;
	vector<int32>	_parent;

};

