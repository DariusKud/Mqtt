#pragma warning(push, 0)
#include <SimpleAmqpClient/SimpleAmqpClient.h>
#pragma warning(pop)

#include <iostream>
#include <time.h>

using namespace std;

constexpr auto QUEUE_NAME = "temperature";

int main()
{
while(1)
	{
		time_t laikas = time(NULL);
		auto channel = AmqpClient::Channel::Create();
		channel->DeclareQueue(QUEUE_NAME, false, true, false, true);
		auto consumerTag = channel->BasicConsume(QUEUE_NAME);
		clog << "Consumer tag: " << consumerTag << endl <<endl;
		auto envelop = channel->BasicConsumeMessage(consumerTag);
		clog <<ctime(&laikas)<< "Received Temperature " << envelop->Message()->Body() << endl <<endl;

	}
  return 0; 
}
