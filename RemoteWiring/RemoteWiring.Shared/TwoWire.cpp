#include "pch.h"
#include "TwoWire.h"

using namespace Wiring::I2C;

void
TwoWire::enable(
	uint16_t i2cReadDelayMicros_
	)
{
	_firmata->enableI2c( ( i2cReadDelayMicros_ > MAX_READ_DELAY_MICROS ) ? MAX_READ_DELAY_MICROS : i2cReadDelayMicros_ );
}


void
TwoWire::write(
	uint8_t address_,
	Platform::String ^message_
	)
{
	_firmata->writeI2c( address_, message_ );
}

void
TwoWire::read(
	uint8_t address_,
	size_t numBytes_,
	uint8_t reg_,
	bool continuous_,
	I2cCallback ^callback_
	)
{
	//if you want to do continuous reads, you must provide a register to prompt for new data
	if( continuous_ && ( reg_ == 0xFF ) ) return;
	_i2cReplyCallback = callback_;
	_firmata->readI2c( address_, numBytes_, reg_, continuous_ );
}


void
TwoWire::stop(
	uint8_t address_
	)
{
	_firmata->stopI2c( address_ );
}


 void
 TwoWire::onI2cReply( 
	Wiring::Firmata::I2cCallbackEventArgs ^args
	)
 {
	 if( _i2cReplyCallback ) _i2cReplyCallback( args->getAddress(), args->getResponseString() );
}