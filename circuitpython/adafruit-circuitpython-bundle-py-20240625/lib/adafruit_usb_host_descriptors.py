# SPDX-FileCopyrightText: Copyright (c) 2023 Scott Shawcroft for Adafruit Industries
#
# SPDX-License-Identifier: MIT
"""
`adafruit_usb_host_descriptors`
================================================================================

Helpers for getting USB descriptors

* Author(s): Scott Shawcroft
"""

import struct
from micropython import const

__version__ = "0.1.2"
__repo__ = "https://github.com/adafruit/Adafruit_CircuitPython_USB_Host_Descriptors.git"


# USB defines
# Use const for these internal values so that they are inlined with mpy-cross.
_DIR_OUT = const(0x00)
_DIR_IN = const(0x80)

_REQ_RCPT_DEVICE = const(0)

_REQ_TYPE_STANDARD = const(0x00)

_REQ_GET_DESCRIPTOR = const(6)

# No const because these are public
DESC_DEVICE = 0x01
DESC_CONFIGURATION = 0x02
DESC_STRING = 0x03
DESC_INTERFACE = 0x04
DESC_ENDPOINT = 0x05


def get_descriptor(device, desc_type, index, buf, language_id=0):
    """Fetch the descriptor from the device into buf."""
    # Allow capitalization that matches the USB spec.
    # pylint: disable=invalid-name
    wValue = desc_type << 8 | index
    wIndex = language_id
    device.ctrl_transfer(
        _REQ_RCPT_DEVICE | _REQ_TYPE_STANDARD | _DIR_IN,
        _REQ_GET_DESCRIPTOR,
        wValue,
        wIndex,
        buf,
    )


def get_device_descriptor(device):
    """Fetch the device descriptor and return it."""
    buf = bytearray(1)
    get_descriptor(device, DESC_DEVICE, 0, buf)
    full_buf = bytearray(buf[0])
    get_descriptor(device, DESC_DEVICE, 0, full_buf)
    return full_buf


def get_configuration_descriptor(device, index):
    """Fetch the configuration descriptor, its associated descriptors and return it."""
    # Allow capitalization that matches the USB spec.
    # pylint: disable=invalid-name
    buf = bytearray(4)
    get_descriptor(device, DESC_CONFIGURATION, index, buf)
    wTotalLength = struct.unpack("<xxH", buf)[0]
    full_buf = bytearray(wTotalLength)
    get_descriptor(device, DESC_CONFIGURATION, index, full_buf)
    return full_buf
