#pragma once
//#define BOOST_LOG_DYN_LINK
#include <string>
#include <queue>
#ifdef _DEBUG
#undef _DEBUG
#include <Python.h>
#define _DEBUG
#else
#include <Python.h>
#endif
#include <boost/python.hpp>
#include <chrono>

#include "Common.h"
#include "PythonFile.h"
#include "Worker.h"

//! Wszystkie klasy wykorzystywane w Generator
namespace GeneratorUtil {};

using namespace GeneratorUtil;
using namespace CommonUtil;

//! Klasa odpowiedzialna za generowanie trajektorii obiektu.
class Generator : public Worker<OutputWorker>
{

	PythonFile pythonFile_;							//!< Aktualnie wykonywany skrypt Pythona.

	boost::python::object mainModule_;				//!< Zmienna związana z obsługą Pythona.
	boost::python::object mainNamespace_;			//!< Zmienna związana z obsługą Pythona.
	std::chrono::milliseconds waitTime_;			//!< Opóźnienie pomiędzy wysyłanymi sygnałami.

	std::function<void(Status)> receiverFunction_;	//!< Tymczasowe rozwiązanie: aktualna funkcja przyjmująca wyniki wykonania skryptu.


	long long time_;
    /** Właściwa inicjalizacja obiektu.
        Metoda inicjalizuje interpreter Pythona i ładuje do niego zawartość pliku podanego jako argument konstruktora Generator::Generator().
        \returns nic
        \throws boost::python::error_already_set (prawdopodobnie) gdy załadowanie skryptu zwróci błąd.
        \sa GeneratorUtil::PythonFile
    */
	void Init();

	/** Jednokrotne uruchomienie funkcji zawartej w skrypcie i zapisanie wartości argumencie.
        Metoda wykonuje jednokrotnie skrypt z Generator::pythonFile_ i zwraca wyniki do argumentu.
        \param retValue - zmienna w której znajdzie się rezultat skryptu(dwie pierwsze liczby z krotki).
        \returns nic
        \throws boost::python::error_already_set w przypadku błędów interpretera.
    */
	void ExecuteUpdate(std::array<double, 2>& retValue) const;

    /** Wysłanie otrzymanych wyników w świat
        Metoda wysyła wartości zmiennych w świat.
        \param  retValue parametry do wysłania w świat.
        \throws Błędy związane z propagacją wiadomości.
        \returns nic
        \sa Generator::receiverFunction_
    */
	void SendUpdate(std::array<double, 2>& retValue);

    /** Aktualny prototyp pętli komunikatów.
        \returns nic
        \throws nic
    */
	Status ThreadProc() override;

public:
	/** Konstruktor.
		\param pFilename Ścieżka do skryptu na podstawie której ścieżka ma zostać wygenerowana.
		\param waitTime Czas oczekiwania pomiędzy wywołaniami.
		\sa Start()

		W związku z planowaną wielowątkowością wszystkie kroki związane z inicjalizacją są opóźnione do wywołania funkcji Start()
	*/
	explicit Generator(std::string pFilename, std::chrono::milliseconds waitTime = std::chrono::milliseconds(100));
	/** Destruktor.

        \bug Według dokumentacji boost::python nie jest zalecane wywoływanie funkcji dot. zwracania zasobów za interpreter.
    */
    ~Generator();

	/** Funkcja odpowiedzialna za właściwy start obiektu.
		\param MessageLoop Określa, czy wewnętrzna pętla ma zostać uruchomiona - przydatne w celu testowania skryptu za pomocą ExecuteOnce()
		\sa ExecuteOnce()

	*/
	void Start(bool MessageLoop = true);

	/** Jednokrotne wywołanie procedury odpowiedzialnej za wywołanie skryptu.
        \returns Generator::receiverFunction_ powinno dostać jeden obiekt CommonUtil::Status.
    */
    void ExecuteOnce();

	/** Ustawienie odbiorcy wywołań skryptu.
		\param what funkcja która przyjmuje dane.
	*/
	void SetReceiver(std::function<void(Status)> what) { receiverFunction_ = what; }
};

/** \example benchmark.cpp
    Przykład użycia klasy Generator - liczenie wygenerowanych CommonUtil::Status.
*/
