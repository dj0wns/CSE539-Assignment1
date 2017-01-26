END=4294967295

for ((i=1;i<=${END};i++))
do
	bin/crypto d ${i} examples/example1.crypt examples/example1.decrypt > /dev/null
	DIFF=$(diff examples/example1 examples/example1.decrypt) 
	if [ "$DIFF" == "" ] 
	then
		echo "Got it!"
		exit
	fi
done
