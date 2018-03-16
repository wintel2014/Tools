echo 0 > /sys/kernel/debug/tracing/events/exceptions/enable
if [[ $? -ne 0 ]]
then
    echo "root !!!!!!" 
    exit 2
fi



echo >  /sys/kernel/debug/tracing/trace
echo 4096 > /sys/kernel/debug/tracing/buffer_size_kb
#cat /sys/kernel/debug/tracing/trace
echo 1 >  /sys/kernel/debug/tracing/events/exceptions/enable
echo 1 > /sys/kernel/debug/tracing/tracing_on
echo "Start capturing page-fault events..."
echo "Stop if any key is pressed"


read stop

echo 0 > /sys/kernel/debug/tracing/tracing_on
cat /sys/kernel/debug/tracing/trace
echo 0 > /sys/kernel/debug/tracing/events/enable
