#Note 
Use #define BOOST_ASIO_ENABLE_HANDLER_TRACKING before including asio. This will log aync operation .

One can use service.Post function to create async call to any function. Boost asio is not just for networking. 

####Coroutines:
  1.derive from coroutine publically.
  2.
```
reenter(this){
    for(;;){
        yield async_call 
        ...
        yield async_call
        ...
    }
}
```

##How to use : 
Server<Connection> server(1); </br>
server.startServer(9999); </br>

###Server - this is aynchronous server that runs thread pool for given io_service.
###Connection - HTTP Handler for http operation. 
