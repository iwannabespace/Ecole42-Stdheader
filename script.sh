file="$1"

if [ -f $file ] ; then
	vim $file -c Stdheader -c wq
else
	echo "$file couldn't be found!"
fi
