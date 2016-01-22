#pragma once
#include <vector>
#include <algorithm>
#include <initializer_list>
#include <algorithm>
#include <thread>
#include <functional>
#include <boost/any.hpp>
#include "Workable.h"

namespace CommonUtil
{
	//! Obiekt zajmujący się poszczególnymi wątkami aplikacji.
	class SimpleWorkerPool
	{
		//! Kolekcja wskaźników na poszczególne obiekty.
		std::vector<WorkablePtr> workers;

		//! Kolekcja wątków, wykorzystywana w operator()() do czekania na nie.
		std::vector<std::thread> threads;

	public:

		/** Rejestrowanie modułów aplikacji.
		/param Lista inicjalizacyjna zawierająca wskaźniki na moduły aplikacji.
		/returns nic
		*/
		void Register(std::initializer_list<WorkablePtr>);

		/** Uruchomienie wszystkich wątków zarejestrowanych poprzez metodę Register.
		*/
		void operator()();
	};

};
