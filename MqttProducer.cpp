#pragma warning(push, 0)
#include <SimpleAmqpClient/SimpleAmqpClient.h>
#pragma warning(pop)

#include <iostream>
#include <fstream>
#include <time.h>


void ReadTemperature();
void SendTemperature();

using namespace std;

constexpr auto QUEUE_NAME = "temperature";

float temperature;
string ans;
time_t laikas = time(NULL);

int main()
{
	
	while(1)
	{
	ReadTemperature();
	SendTemperature();
	sleep(300);
	}
  return 0; 
}

void ReadTemperature()
{
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
			cout <<"Temperature = " << temperature <<endl<<endl;
			ans = to_string(temperature).substr(0,6);
		}
	}

}

void SendTemperature() 
{
	auto channel = AmqpClient::Channel::Create();
	channel->DeclareQueue(QUEUE_NAME, false, true, false, true);
	auto message = AmqpClient::BasicMessage::Create(ans);
	channel->BasicPublish("", QUEUE_NAME, message);
	clog <<ctime(&laikas)<< "Sent "<< ans <<endl<<endl;
}

