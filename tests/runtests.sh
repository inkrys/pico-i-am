echo "Running unit tests:"
echo "------"
echo "Starting test script."
echo "------"
echo "Output from target:"
echo ""

if [[  -z $1 ]]; then
    serial_port=/dev/ttyACM1
else
    serial_port=$1
fi

stty -F $serial_port 115200 cs8 -cstopb
timeout 3s cat $serial_port

echo ""