curl "http://www.jsoftware.com/jal/j904/addons/" -o - |grep "href=.*linux.tar.gz"|sed -E 's/.*"([^"]+)_linux.tar.gz".*/\1/'  > addons.txt
