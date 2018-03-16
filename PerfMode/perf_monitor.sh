# sudo turbostat  --interval 2

chkconfig anacron off
service irqbalance stop
service iptables stop
service postfix stop

swapoff -a
cpupower set --perf-bias 0
cpupower frequency-set --governor performance

#echo performance > /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor

echo "==========================Cache Information================================"
echo "CacheLineSize:"
cat /sys/devices/system/cpu/cpu0/cache/index*/coherency_line_size

echo -e "\n"
echo "CacheLevel:"
cat /sys/devices/system/cpu/cpu0/cache/index*/level 


echo -e "\n"
echo "CacheCapacity:"
cat /sys/devices/system/cpu/cpu0/cache/index*/size 

echo -e "\n"

echo "==========================CPU Information================================"
governors=$(cat /sys/devices/system/cpu/cpu0/cpufreq/scaling_available_governors)
current_governor=$(cat /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor)
current_freq=$(sudo cat /sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_cur_freq)

echo "CPU0 scaling_available_governors:\"$governors\""
echo "CPU0 current_governor:\"$current_governor\""
echo "CPU0 current_freq: $current_freq"

cat $(find /sys -name scaling_cur_freq)
cat $(find /sys -name scaling_governor)

perf stat  -e alignment-faults  -e cache-misses  -e instructions -e cpu-clock -e cpu-migrations -e major-faults -e minor-faults -e  page-faults \
-e task-clock -e l1d.replacement -e L1-dcache-load-misses  -e LLC-load-misses -e LLC-store-misses -e  l2_lines_in.e -e l2_lines_in.i -e l2_lines_in.s \
./test
