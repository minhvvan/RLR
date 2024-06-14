#include "pch.h"
#include "DeadLockProfiler.h"
#include "CoreTLS.h"

void DeadLockProfiler::CheckCycle() {

	const int32 lockCount = static_cast<int32>(_nameTold.size());
	_discoverdOrder = vector<int32>(lockCount, -1);
	_discoveredCount = 0;
	_finished = vector<bool>(lockCount, false);
	_parent = vector<int32>(lockCount, -1);

	for (int32 lockid = 0; lockid < lockCount; lockid++) {
		Dfs(lockid);
	}
	_discoverdOrder.clear();
	_finished.clear();
	_parent.clear();

}

void DeadLockProfiler::Dfs(int32 here) {
	if (_discoverdOrder[here] != -1) {
		return;
	}

	_discoverdOrder[here] = _discoveredCount++;
	
	//모든 인접한 정점을 순회한다.
	auto findit = _lockHistory.find(here);
	if (findit == _lockHistory.end()) {
		_finished[here] = true;
		return;
	}

	set<int32>& nextSet = findit->second;
	for (int32 there : nextSet) {
		// 아직 방문한 적이 없다면 방문한다.
		if (_discoverdOrder[there] == -1) {
			_parent[there] = here;
			Dfs(there);
			continue;
		}
		//here 가 there 보다 먼저 발견되었다면 there 는 here 의 후손이다( 순방향 간선)
		if (_discoverdOrder[here] < _discoverdOrder[there])
			continue;

		//순방향이 아니고, Dfs(there)가 아직 종료하지 않았다면, there는 here의 선조이다.(역방향 간선)
		if (_finished[there] == false) {
			printf("%s -> %s\n", _idToName[here], _idToName[there]);
			int32 now = there;
			while (true) {
				printf("%s -> %s\n", _idToName[ _parent[now]], _idToName[now]);
				now = _parent[now];
				if (now == there) 
					break;
				
			}
			CRASH("DEADLOCK_DETECTED");
		}
	}
	_finished[here] = true;
}

void DeadLockProfiler::PopLock(const char* name) {
	LockGuard guard(_lock);
	if (_lockStack.empty()) {
		CRASH("MULTIPLE_UNLOCK");
	}
	int32 lockid = _nameTold[name];
	if (_lockStack.top() != lockid) {
		CRASH("INVALID_UNLOCK");
	}


	_lockStack.pop();
}
void DeadLockProfiler::PushLock(const char* name) {
	LockGuard guard(_lock);

	int32 lockid = 0;
	auto findit = _nameTold.find(name);
	if (findit == _nameTold.end()) {
		lockid = static_cast<int32>(_nameTold.size());
		_nameTold[name] = lockid;
		_idToName[lockid] = name;
	}
	else {
		lockid = findit->second;
	}

	//잡고 있는 락이 있었다면
	if (_lockStack.empty() == false) {
		//기존에 발견되지 않은 케이스라면 데드락 여부 다시 확인한다.
		const int32 previd = _lockStack.top();
		if (lockid != previd) {
			set<int32>& history = _lockHistory[previd];
			if (history.find(lockid) == history.end()) {
				history.insert(lockid);
				CheckCycle();
			}
		}


	}
	_lockStack.push(lockid);

}