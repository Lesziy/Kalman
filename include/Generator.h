#pragma once
//#define BOOST_LOG_DYN_LINK
#include <string>
#include <queue>
#include <Python.h>
#include <boost/python.hpp>
#include <chrono>
#include "PythonFile.h"
#include "Status.h"

using namespace GeneratorUtil;

//! Klasa odpowiedzialna za generowanie trajektorii obiektu.
class Generator
{

	PythonFile pythonFile_;							//!< Aktualnie wykonywany skrypt Pythona.

	boost::python::object mainModule_;				//!< Zmienna związana z obsługą Pythona.
	boost::python::object mainNamespace_;			//!< Zmienna związana z obsługą Pythona.
	std::chrono::milliseconds waitTime_;			//!< Opóźnienie pomiędzy wysyłanymi sygnałami.

	std::function<void(Status)> receiverFunction_;	//!< Tymczasowe rozwiązanie: aktualna funkcja przyjmująca wyniki wykonania skryptu.

	//! Inicjalizacja obsługi Pythona.
	void Init();

	//! Wykonanie funkcji ze skryptu.
	void ExecuteUpdate(std::array<double, 2>& retValue) const;
	//! Wysłanie danych ze skyptu w świat.
	void SendUpdate(std::array<double, 2>& retValue);
	//! Pętla komunikatów.
	void MessageLoop();

public:
	//! Konstruktor.
	/*!
		\param pFilename Ścieżka do skryptu na podstawie której ścieżka ma zostać wygenerowana.
		\param waitTime Czas oczekiwania pomiędzy wywołaniami.
		\sa Start()

		W związku z planowaną wielowątkowością wszystkie kroki związane z inicjalizacją są opóźnione do wywołania funkcji Start()
	*/
	explicit Generator(std::string pFilename, std::chrono::milliseconds waitTime = std::chrono::milliseconds(100));
	//! Destruktor.
	~Generator();

	//! Funkcja odpowiedzialna za właściwy start obiektu.
	/*!
		\param MessageLoop Określa, czy wewnętrzna pętla ma zostać uruchomiona - przydatne w celu testowania skryptu za pomocą ExecuteOnce()
		\sa ExecuteOnce()

	*/
	void Start(bool MessageLoop = true);

	//! Jednokrotne wywołanie procedury odpowiedzialnej za wywołanie skryptu: Generator::receiverFunction_ powinno dostać jeden obiekt Status.
	void ExecuteOnce();

	//! Ustawienie odbiorcy wywołań skryptu.
	/*!
		\param what funkcja która przyjmuje dane.
	*/
	void SetReceiver(std::function<void(Status)> what) { receiverFunction_ = what; }
	};
