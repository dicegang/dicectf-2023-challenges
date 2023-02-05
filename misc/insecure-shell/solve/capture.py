import struct
import time

from scapy.all import *

pcap = rdpcap('../capture.pcap')
sessions = pcap.sessions()
client_packets = sessions['TCP 10.128.0.5:38042 > 34.68.198.132:22']
server_packets = sessions['TCP 34.68.198.132:22 > 10.128.0.5:38042']

timestamp = int(client_packets[0].time)

class Stream:
    def __init__(self, packets):
        self.packets = iter(packets.filter(lambda p: p.haslayer(Raw)))
        self.buf = b''

    def read(self, n):
        while len(self.buf) < n:
            try:
                packet = next(self.packets)
            except StopIteration:
                break
            self.buf += packet.load
        rv = self.buf[:n]
        self.buf = self.buf[n:]
        return rv

class RealtimeStream(Stream):
    def __init__(self, packets, speed=1):
        super().__init__(packets)
        self.last_ptime = float('inf')
        self.last_rtime = 0
        self.speed = speed

    def read(self, n):
        while len(self.buf) < n:
            try:
                packet = next(self.packets)
            except StopIteration:
                break
            ptime = float(packet.time)
            pelapsed = ptime - self.last_ptime
            relapsed = time.time() - self.last_rtime
            time.sleep(max(pelapsed - relapsed * self.speed, 0))
            self.last_ptime = ptime
            self.last_rtime = time.time()
            self.buf += packet.load
        rv = self.buf[:n]
        self.buf = self.buf[n:]
        return rv

u32 = lambda x: struct.unpack('>I', x)[0]

# parse client stream
client_stream = Stream(client_packets)
client_version = b''
while client_version[-2:] != b'\r\n':
    client_version += client_stream.read(1)
client_version = client_version[:-2]

size = u32(client_stream.read(4))
pad = client_stream.read(1)[0]
size = size - pad - 2
assert client_stream.read(1) == b'\x14'
client_kexinit = client_stream.read(size)
client_stream.read(pad)

size = u32(client_stream.read(4))
pad = client_stream.read(1)[0]
size = size - pad - 2
assert client_stream.read(1) == b'\x1e'
pub_size = u32(client_stream.read(4))
assert pub_size == 32
client_pub = client_stream.read(pub_size)
client_stream.read(pad)

size = u32(client_stream.read(4))
pad = client_stream.read(1)[0]
size = size - pad - 2
assert client_stream.read(1) == b'\x15'
client_stream.read(size)
client_stream.read(pad)

# parse server stream
server_stream = RealtimeStream(server_packets, speed=2)
server_version = b''
while server_version[-2:] != b'\r\n':
    server_version += server_stream.read(1)
server_version = server_version[:-2]

size = u32(server_stream.read(4))
pad = server_stream.read(1)[0]
size = size - pad - 2
assert server_stream.read(1) == b'\x14'
server_kexinit = server_stream.read(size)
server_stream.read(pad)

size = u32(server_stream.read(4))
pad = server_stream.read(1)[0]
assert server_stream.read(1) == b'\x1f'
host_size = u32(server_stream.read(4))
server_host_key = server_stream.read(host_size)
pub_size = u32(server_stream.read(4))
assert pub_size == 32
server_pub = server_stream.read(pub_size)
sig_size = u32(server_stream.read(4))
server_stream.read(sig_size)
server_stream.read(pad)

size = u32(server_stream.read(4))
pad = server_stream.read(1)[0]
size = size - pad - 2
assert server_stream.read(1) == b'\x15'
server_stream.read(size)
server_stream.read(pad)
