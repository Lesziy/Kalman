#pragma once

namespace CommonUtil {
	//! Rodzic dla szablonu CommonUtil::Worker, wykorzystywany w CommonUtil::SimpleWorkerPool
	class Workable
	{
	public:
		virtual void operator()() {};
	};
};

//! Wskaźnik na typ CommonUtil::Workable
typedef std::shared_ptr<Workable> WorkablePtr;
