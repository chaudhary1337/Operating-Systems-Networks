# Client Sever

## Using
- `clear && make client && ./client` to start the client
- `clear && make server && ./server 69` starts a server with 69 threads
- `clear && make clean && clear` to clear out the `.o` files

Can use: `clear && make client && ./client < ./tests/client_test.txt` to test the client

## Logic
- Using threads allows for multiple clients to connect to the server at the same
- Since many threads can modify (add/del/upd) the same dict, we can have race condition
- to prevent race condition, I have used mutex locks, which makes the modifying (add/del/upd) operations thread safe - by making them atomic
- mutex locks say that only I can change the value inside the critical section
- note: what I have implemented is not parallelism, but concurrency
- I also used queue to store client connections that I can't currently process - because the all the threads from the pool are busy doing something else
- the queue and dequeue operations were also BT, so had to switch to CPP instead of C lol
- also, if I spammed requests, the server would hang. that's because eveything would be super busy, and once all the threads are done, we stop
- but there may still be more requests and the lock would still be in place
- thus, I use conditional variables. so, no busy waiting

## Resources
- use `echo "command" | nc machine_name port_number` to test out the server file (if you havent written the client yet)
- get started with this: http://www.cs.rpi.edu/~moorthy/Courses/os98/Pgms/socket.html
- pthreads: https://pages.cs.wisc.edu/~remzi/OSTEP/threads-api.pdf
- multithreaded server in c (vid): https://www.youtube.com/watch?v=Pg_4Jz8ZIH4
- thread pools (part 2 of the vid): https://www.youtube.com/watch?v=FMNnusHqjpw
- using conditional variables: https://www.youtube.com/watch?v=P6Z5K8zmEmc
