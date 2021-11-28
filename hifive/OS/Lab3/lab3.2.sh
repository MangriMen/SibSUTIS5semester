echo "PS: "
ps -a | grep "lab3.2.hi5"
echo
echo "PSTREE: "
pstree $USER -a -p
echo
echo "Enter parent pid: "
read pid
kill $pid
echo
echo "Murdering child process: "
kill $(($pid + 1))
echo
pstree $USER -a -p