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
	// �� Worker �������� ����.
	size_t num_threads_;
	// Worker �����带 �����ϴ� ����.
	std::vector<std::thread> worker_threads_;
	// ���ϵ��� �����ϴ� job ť.
	std::queue<std::function<void()>> jobs_;
	// ���� job ť�� ���� cv �� m.
	std::condition_variable cv_job_q_;
	std::mutex m_job_q_;

	// ��� ������ ����
	bool stop_all;

	// Worker ������
	void WorkerThread();
};

#define Thread cThreadPoolManager::GetInstance()


