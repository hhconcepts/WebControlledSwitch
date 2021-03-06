// RelayManager.h

#ifndef _RELAYMANAGER_h
#define _RELAYMANAGER_h
#include "arduino.h"
#include <functional>
#include "Singleton.h"


class RelayManager 
{
private:
	int _pin;
	int _state;
	std::function<void (const std::string &)> _logger;

protected:
	RelayManager(int pin, std::function<void(const std::string &)> logger);

 public:
	virtual ~RelayManager()	{}
	virtual void OnCommand(const std::string & commandName, int commandId) = 0;
	virtual void Set(int value);
	int State() const { return _state; }
	virtual void Loop() {}
};

typedef std::shared_ptr<RelayManager> RelayManagerPtr_t;
#endif

