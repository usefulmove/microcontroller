# SPDX-FileCopyrightText: 2017 Scott Shawcroft, written for Adafruit Industries
# SPDX-FileCopyrightText: Copyright (c) 2022 Melissa LeBlanc-Williams for Adafruit Industries
#
# SPDX-License-Identifier: MIT
"""
`adafruit_esp32s2tft.network`
================================================================================

Helper library for the Adafruit ESP32-S2 TFT Feather.


* Author(s): Melissa LeBlanc-Williams

Implementation Notes
--------------------

**Hardware:**

* `Adafruit ESP32-S2 TFT Feather <https://www.adafruit.com/product/5300>`_

**Software and Dependencies:**

* Adafruit CircuitPython firmware for the supported boards:
  https://github.com/adafruit/circuitpython/releases

* Adafruit's PortalBase library: https://github.com/adafruit/Adafruit_CircuitPython_PortalBase

"""

import ssl
from adafruit_portalbase.network import NetworkBase
from adafruit_portalbase.wifi_esp32s2 import WiFi

try:
    from typing import Optional, Union, Callable
    from neopixel import NeoPixel
    from adafruit_io.adafruit_io import IO_MQTT
    import adafruit_minimqtt.adafruit_minimqtt as MQTT
except ImportError:
    pass

__version__ = "1.2.1"
__repo__ = "https://github.com/adafruit/Adafruit_CircuitPython_ESP32S2TFT.git"

IO_MQTT_BROKER = "io.adafruit.com"


class Network(NetworkBase):
    """Network Helper Class for the ESP32S2TFT Library

    :param status_neopixel: The initialized object for status DotStar. Defaults to ``None``,
                           to not use the status LED
    :param bool extract_values: If true, single-length fetched values are automatically extracted
                                from lists and tuples. Defaults to ``True``.
    :param debug: Turn on debug print outs. Defaults to False.

    """

    # pylint: disable=too-many-instance-attributes, too-many-locals, too-many-branches, too-many-statements
    def __init__(
        self,
        *,
        status_neopixel: Optional[NeoPixel] = None,
        extract_values: bool = True,
        debug: bool = False,
    ) -> None:
        super().__init__(
            WiFi(status_led=status_neopixel),
            extract_values=extract_values,
            debug=debug,
        )
        self._mqtt_client = None

    def init_io_mqtt(self) -> IO_MQTT:
        """Initialize MQTT for Adafruit IO"""
        try:
            aio_username = self._secrets["aio_username"]
            aio_key = self._secrets["aio_key"]
        except KeyError:
            raise KeyError(
                "Adafruit IO secrets are kept in secrets.py, please add them there!\n\n"
            ) from KeyError

        return self.init_mqtt(IO_MQTT_BROKER, 8883, aio_username, aio_key, True)

    # pylint: disable=too-many-arguments
    def init_mqtt(
        self,
        broker: str,
        port: int = 8883,
        username: str = None,
        password: str = None,
        use_io: bool = False,
    ) -> Union[MQTT.MQTT, IO_MQTT]:
        """Initialize MQTT"""
        self.connect()
        self._mqtt_client = MQTT.MQTT(
            broker=broker,
            port=port,
            username=username,
            password=password,
            socket_pool=self._wifi.pool,
            ssl_context=ssl.create_default_context(),
        )
        if use_io:
            self._mqtt_client = IO_MQTT(self._mqtt_client)

        return self._mqtt_client

    # pylint: enable=too-many-arguments

    def _get_mqtt_client(self) -> Union[MQTT.MQTT, IO_MQTT]:
        if self._mqtt_client is not None:
            return self._mqtt_client
        raise RuntimeError("Please initialize MQTT before using")

    def mqtt_loop(
        self, *args: int, suppress_mqtt_errors: bool = True, **kwargs: int
    ) -> None:
        """Run the MQTT Loop"""
        self._get_mqtt_client()
        if suppress_mqtt_errors:
            try:
                if self._mqtt_client is not None:
                    self._mqtt_client.loop(*args, **kwargs)
            except MQTT.MMQTTException as err:
                print(f"MMQTTException: {err}")
            except OSError as err:
                print(f"OSError: {err}")
        else:
            if self._mqtt_client is not None:
                self._mqtt_client.loop(*args, **kwargs)

    def mqtt_publish(
        self,
        *args: Union[str, int, float],
        suppress_mqtt_errors: bool = True,
        **kwargs: Union[str, int, float],
    ) -> None:
        """Publish to MQTT"""
        self._get_mqtt_client()
        if suppress_mqtt_errors:
            try:
                if self._mqtt_client is not None:
                    self._mqtt_client.publish(*args, **kwargs)
            except OSError as err:
                print(f"OSError: {err}")
        else:
            if self._mqtt_client is not None:
                self._mqtt_client.publish(*args, **kwargs)

    def mqtt_connect(
        self, *args: Union[bool, str, int], **kwargs: Union[bool, str, int]
    ) -> None:
        """Connect to MQTT"""
        self._get_mqtt_client()
        if self._mqtt_client is not None:
            self._mqtt_client.connect(*args, **kwargs)

    @property
    def on_mqtt_connect(self) -> Optional[Callable]:
        """
        Get or Set the MQTT Connect Handler

        """
        if self._mqtt_client:
            return self._mqtt_client.on_connect
        return None

    @on_mqtt_connect.setter
    def on_mqtt_connect(self, value: Callable) -> None:
        self._get_mqtt_client()
        self._mqtt_client.on_connect = value

    @property
    def on_mqtt_disconnect(self) -> Optional[Callable]:
        """
        Get or Set the MQTT Disconnect Handler

        """
        if self._mqtt_client:
            return self._mqtt_client.on_disconnect
        return None

    @on_mqtt_disconnect.setter
    def on_mqtt_disconnect(self, value: Callable) -> None:
        self._get_mqtt_client().on_disconnect = value

    @property
    def on_mqtt_subscribe(self) -> Optional[Callable]:
        """
        Get or Set the MQTT Subscribe Handler

        """
        if self._mqtt_client:
            return self._mqtt_client.on_subscribe
        return None

    @on_mqtt_subscribe.setter
    def on_mqtt_subscribe(self, value: Callable) -> None:
        self._get_mqtt_client().on_subscribe = value

    @property
    def on_mqtt_unsubscribe(self) -> Optional[Callable]:
        """
        Get or Set the MQTT Unsubscribe Handler

        """
        if self._mqtt_client:
            return self._mqtt_client.on_unsubscribe
        return None

    @on_mqtt_unsubscribe.setter
    def on_mqtt_unsubscribe(self, value: Callable) -> None:
        self._get_mqtt_client().on_unsubscribe = value

    @property
    def on_mqtt_message(self) -> Optional[Callable]:
        """
        Get or Set the MQTT Message Handler

        """
        if self._mqtt_client:
            return self._mqtt_client.on_message
        return None

    @on_mqtt_message.setter
    def on_mqtt_message(self, value: Callable) -> None:
        self._get_mqtt_client().on_message = value

    @property
    def enabled(self) -> bool:
        """
        Get or Set whether the WiFi is enabled

        """
        return self._wifi.enabled

    @enabled.setter
    def enabled(self, value: bool) -> None:
        self._wifi.enabled = bool(value)
