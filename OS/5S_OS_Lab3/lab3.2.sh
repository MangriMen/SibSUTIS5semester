echo "PS: "
ps -a | grep "lab3.2.out"
echo "---"
echo "PSTREE: "
pstree $USER -a -p
echo "---"
echo -n "Enter parent pid: "
read pid
kill $pid
echo "---"
pstree $USER -a -p
echo "---"
echo "Killing child process (pid $(($pid+1)))..."
kill $(($pid+1))
echo "---"
pstree $USER -a -p
kill lab3.2.out