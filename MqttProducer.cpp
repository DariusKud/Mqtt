#include<iostream>
#include<fstream>
#include<string>


void ReadTemperatureFromFile();

float temperature;

using namespace std;

int main()
{
	cout<<"Calling file read procedure"<<endl;
	ReadTemperatureFromFile();
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
