pidwait(){
	while kill -0 $1 
	do 
	sleep 1	
	done 
	ls
}

