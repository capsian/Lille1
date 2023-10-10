import natnet
import time

client = natnet.Client.connect(server='192.168.20.15')


def cb(rigid_bodies, markers, timing):
    print(timing.timestamp, 'regid bodies:')
    for rb in rigid_bodies:
        print(rb)
    print(timing.timestamp, 'markers:')
    for m in markers:
        print(m)
    time.sleep(2)


client.set_callback(cb)
client.spin()
