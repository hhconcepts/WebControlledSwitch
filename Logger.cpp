#include "Logger.h"
using namespace std;

Logger::Logger(int redLedPin, int greenLedPin, int baudRate /*= 115200*/): _ledsLogger(LedsLogger::Create(redLedPin, greenLedPin))
{
	Serial.begin(baudRate);
	Serial.setDebugOutput(true);
}

void Logger::OnCommand(const std::string & commandName, int commandId) const
{
	string log(commandName + " command recieved");
	Serial.println(log.c_str());
	_ledsLogger->BlinkGreen(commandId, 250);
}

void Logger::WriteErrorMessage(const std::string& message, int blinks) const
{
	Serial.println(message.c_str());
	_ledsLogger->BlinkRed(blinks, 300);
}

void Logger::OnWiFiStatusChanged(const ConnectionStatus& status) const
{
	Serial.println(status.Message().c_str());
	if (status.IsJustConnected())
	{
		Serial.print("IP address: ");
		Serial.println(status.LocalIP());
	}
	_ledsLogger->SetGreen(status.IsConnected() ? HIGH : LOW);
	_ledsLogger->SetRed(status.IsConnected() ? LOW : HIGH);

	if (!status.IsConnected())
		_ledsLogger->BlinkRed(3 + status.WifiCode(), 250);
}

void Logger::WriteMessage(const std::string& message)
{
	Serial.println(message.c_str());
}

void Logger::TestLeds() const
{
	_ledsLogger->BlinkGreen(3, 100);
	_ledsLogger->BlinkRed(3, 100);
}
