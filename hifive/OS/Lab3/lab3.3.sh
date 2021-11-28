echo "PSTREE: "
pstree $USER -a -p
echo "Enter parent pid: "
read pid
cat "/proc/$pid/task/$pid/children"
echo