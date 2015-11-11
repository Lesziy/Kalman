typedef signal <void (int)> Signal ;
typedef boost :: function <void (int)> Slot;


class Temperature { // Reprezentuje stan
	public:
		void connect (Slot slot) { signal_.connect (slot); }
		void setTemperature(int temp ) { // Metoda generująca zmianę stanu
			temp_ = temp;
			signal_ (temp); // Emisja sygnału
		}
private:
	Signal signal_ ; // Obiekt sygnału
	int temp_; // Stan, temperatura
};



class DisplayCelsius { // Obserwuje stan
	public:
	DisplayCelsius() {}
	void update (int temp ); // Odświeża widok
	private:
	// Składowe związane z widokiem
};

Temperature temperature ;
DisplayCelsius display1 ;
temperature.connect ( boost :: bind(& DisplayCelsius::update ,&display1 , _1) );