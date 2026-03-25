#! /bin/bash

mosquitto -c /etc/mosquitto/conf.d/wiz_test.conf &

mosquitto_instance=$!

sleep 1s

if [[  -z $1 ]]; then
    serial_port=/dev/ttyACM1
else
    serial_port=$1
fi

stty -F $serial_port 115200 cs8 -cstopb
timeout 3s cat $serial_port

kill $mosquitto_instance
echo ""
