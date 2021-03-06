// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// USB Device

#include		"UsbDevice.hpp"

struct usb_bus		*hbs::UsbDevice::_usb_busses = 0;

hbs::UsbDevice::UsbDevice(void)

{
  if (_usb_busses == NULL)
    {
      usb_init();

      /// Return how many busses or devices were added recently - return value seems useless
      // considering the system add them itself
      (void)usb_find_busses();
      (void)usb_find_devices();

      _usb_busses = usb_get_busses();
    }
}

hbs::UsbDevice::~UsbDevice(void)
{}
