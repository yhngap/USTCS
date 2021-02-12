
#ifndef ENGINE_H_
#define ENGINE_H_

enum Color {Black, White, Silver, Grey, Red, Blue};
class Engine
{
public:
	Engine(int nc);		// Conversion Constructor
	void Start();	//Start the engine
	void Stop();		//Stop the engine
	int getNumCylinder() const;

	//Todo: virtual function print()

	
private:
	int numCylinder;		//number of cylinders in the engine

};

#endif /* ENGINE_H_ */
