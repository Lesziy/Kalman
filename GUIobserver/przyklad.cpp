typedef signal <void (int)> Signal ;
typedef boost :: function <void (int)> Slot;



class ZPR_Signal {
	void connect (Slot slot) { signal_.connect (slot); }
	void setPosition(Status status){
		status_ = status;
		signal_(status);
	}
	private:
		Signal signal_ ; // Obiekt sygnału	
		Status status_;  // Stan
	
}

class ZPR_Slot { // Obserwuje stan
	public:
	virtual void update (Status status) = 0; // Odświeża widok
};




class Body public: ZPR_Signal{
	
};

class Sensor public: ZPR_Signal public: ZPR_Slot{
	
};
 
class Kalman public: ZPR_Signal public: ZPR_Slot{
	
};

class GUI public: ZPR_Slot{
	
};
 

Body body;
Sensor sensor;
Kalman sensor;
GUI gui;


body.connect( boost :: bind(& Sensor::update ,&sensor , _1) );
body.connect( boost :: bind(& GUI::update ,&gui , _1) );
sensor.connect( boost :: bind(& Kalman::update ,&kalman , _1) );
kalman.connect( boost :: bind(& GUI::update ,&gui , _1) )
