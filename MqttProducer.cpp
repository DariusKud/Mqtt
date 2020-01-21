#include<iostream>
#include<fstream>
#include<string>
#include "SimplePocoHandler.h"

void ReadTemperatureFromFile();
void SendTemperature();

float temperature;

using namespace std;

int main()
{
	cout<<"Calling file read procedure"<<endl;
	ReadTemperatureFromFile();
	SendTemperature();
	
	return 0;
}

void ReadTemperatureFromFile() {


	const string temperatureString = "t=";
	cout<<"Reading file..."<<endl;
	ifstream file ("temperature.txt");

	if(!file.is_open())
	{
		cerr << "Failed to open file!" << endl;
		
	}

	string temperatureLine;
	size_t position;
	while (getline(file, temperatureLine))
	{
		if(temperatureLine.find(temperatureString) != string::npos)
		{
			cout << "Temperature Line at" << endl;
			cout << temperatureLine << endl;
			position = temperatureLine.find(temperatureString);
			cout << "Temperature index = "<< position << endl;
			temperature = stof(temperatureLine.substr(position + 2))/1000;
			cout <<"Temperature = " << temperature <<endl;
		}
	}

}

void SendTemperature() 
{
	SimplePocoHandler handler("localhost", 5672);
	
	AMQP::Connection connection(&handler, AMQP::Login("guest", "guest"), "/");
	AMQP::Channel channel(&connection);
	
	channel.onReady([&]()
	{
		if(handler.connected())
		{
			channel.publish("", "hello", "Hello World!");
			cout << " [x] Sent 'Hello World!" << endl;
			handler.quit();
		}
	});
	
	handler.loop();
}


