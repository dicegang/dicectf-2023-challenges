#!/usr/local/bin/python

import rpyc
from rpyc.utils.server import ThreadedServer

class CalcService(rpyc.Service):
    def exposed_add(self, l, r):
        return l + r
    def exposed_sub(self, l, r):
        return l - r
    def exposed_mul(self, l, r):
        return l * r
    def exposed_div(self, l, r):
        return l / r

if __name__ == "__main__":
    server = ThreadedServer(CalcService, port=9999)
    server.start()
