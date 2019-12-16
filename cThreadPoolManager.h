#pragma once
#include "singleton.h"
class cThreadPoolManager : public singleton<cThreadPoolManager>
{
public:
	cThreadPoolManager();
	virtual ~cThreadPoolManager();

	template <class F, class... Args>
	std::future<typename std::result_of<F(Args...)>::type> EnqueueJob(
		F&& f, Args&&... args);

	void Init();
private:
	// 총 Worker 쓰레드의 개수.
	size_t num_threads_;
	// Worker 쓰레드를 보관하는 벡터.
	std::vector<std::thread> worker_threads_;
	// 할일들을 보관하는 job 큐.
	std::queue<std::function<void()>> jobs_;
	// 위의 job 큐를 위한 cv 와 m.
	std::condition_variable cv_job_q_;
	std::mutex m_job_q_;

	// 모든 쓰레드 종료
	bool stop_all;

	// Worker 쓰레드
	void WorkerThread();
};

#define Thread cThreadPoolManager::GetInstance()


