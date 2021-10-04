pstree $USER -a -p
echo -n "Enter parent pid: "
read pid
echo -n "Children: "
cat "/proc/$pid/task/$pid/children"
echo
pkill lab3.3.out