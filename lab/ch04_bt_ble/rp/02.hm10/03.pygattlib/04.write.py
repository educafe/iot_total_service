#!/usr/bin/python
# -*- mode: python; coding: utf-8 -*-

# Copyright (C) 2014, Oscar Acena <oscaracena@gmail.com>
# This software is under the terms of Apache License v2 or later.

from __future__ import print_function

import sys
from gattlib import GATTRequester
import time


class Reader(object):
    def __init__(self, address):
        self.requester = GATTRequester(address, False)
        self.connect()
        self.send_data()

    def connect(self):
        print("Connecting...", end=' ')
        sys.stdout.flush()

        self.requester.connect(True)
        print("OK!")

    def send_data(self):
        # self.requester.write_by_handle(0x12, str(bytearray([2])))
		try:
			while True:
				self.requester.write_by_handle(0x12, str(bytearray(["1"])))
				time.sleep(2)
				self.requester.write_by_handle(0x12, str(bytearray(["0"])))
				time.sleep(2)
		except KeyboardInterrupt:
			self.requester.write_by_handle(0x12, str(bytearray(["0"])))
		finally:
			self.requester.write_by_handle(0x12, str(bytearray(["0"])))


if __name__ == '__main__':
    if len(sys.argv) < 2:
        print("Usage: {} <addr>".format(sys.argv[0]))
        sys.exit(1)

    Reader(sys.argv[1])
    print("Done.")
