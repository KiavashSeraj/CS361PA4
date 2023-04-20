all: 
	gcc message.c  calculator.c   -o calc
	gcc message.c        user.c   -o user

clean:
	rm -f calc  user

