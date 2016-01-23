#pragma once

namespace CommonUtil {
	//! Rodzic dla szablonu CommonUtil::Worker, wykorzystywany w CommonUtil::SimpleWorkerPool
	class Workable
	{
	public:
		/** Funkcja wirtualna, uchwyt do uruchomienia procedury dla SimpleWorkerPool.
		*/
		virtual void operator()() {};
	};

//! Wskaźnik na typ CommonUtil::Workable
typedef std::shared_ptr<Workable> WorkablePtr;
};
