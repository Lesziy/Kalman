#pragma once
//#define BOOST_LOG_DYN_LINK
#include <string>
#include <queue>
#include <Python.h>
#include <boost/python.hpp>
#include <chrono>
#include "Common.h"
#include "PythonFile.h"


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
	Status ExecuteUpdate();



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

};

/** \example benchmark.cpp
    Przykład użycia klasy Generator - liczenie wygenerowanych CommonUtil::Status.
*/
