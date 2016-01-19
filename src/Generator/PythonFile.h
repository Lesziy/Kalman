#pragma once
#include <string>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/filesystem.hpp>
#include <fstream>
#include <regex>

namespace GeneratorUtil {
    //! Abstrakcja obsługująca dostęp do skryptu.
    class PythonFile
    {

    	std::string pFilename_;			//!< Nazwa pliku.
    	std::string pSource_;			//!< Kod źródłowy pliku.
    	std::string pFuncName_;			//!< Nazwa funkcji.


    	//! Funkcja pobierająca zawartość pliku.
    	void GetFileContent();

    	//! Funkcja zwracająca prawdopodobną nazwę funkcji.
    	std::string GetFilenameWithoutEx() const;

    	//! Sprawdzenie, czy funkcja aby na pewno zawiera ciało funkcji którą możliwie-że-uruchomimy.
    	/*!
    		@throws std::runtime_error
    	*/
    	void CheckFile();
    public:
    	//! Konstruktor.
    	/*!
    		\param pF ścieżka do pliku, w klasie jest jako PythonFile::pFileName_
    		@copydetails PythonFile::CheckFile
    	*/
    	explicit PythonFile(std::string pF);

    	//! Funkcja zwracająca zawartość obiektu.
    	/*!
    		\return Zawartość pliku PythonFile::pFileName_
    	*/
    	const std::string & ToString() const;

    	//! Funkcja zwracająca nazwę głównej funkcji w obiekcie.
    	/*!
    		\return Nazwa aktualnej funkcji odpowiedzialnej za obliczanie trajektorii obiektu.
    	*/
    	std::string GetFunctionName() const;

    	~PythonFile();
    };
};
