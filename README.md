# Websocket echo server

Example of multithreaded WebSocket echo server implemented with oatpp simple APIs.

More about oat++:
- Website: [https://oatpp.io](https://oatpp.io)
- Docs: [https://oatpp.io/docs/start](https://oatpp.io/docs/start)
- Oat++ Repo: [https://github.com/oatpp/oatpp](https://github.com/oatpp/oatpp)

## Overview

### Project layout

```
|- CMakeLists.txt                        // projects CMakeLists.txt
|- src/
|    |
|    |- controller/                      // Folder containing MyController where "/websocket-connect" endpoint is declared
|    |- websocket/                       // Folder where WebSocket listeners are declared
|    |- dto/                             // DTOs are declared here
|    |- AppComponent.hpp                 // Service config
|    |- Logger.hpp                       // Application Logger
|    |- App.cpp                          // main() is here
|
|- test/                                 // test folder
|- utility/install-oatpp-modules.sh      // utility script to install required oatpp-modules.
    
```

---

### Build and Run

#### Using CMake

- `oatpp` and `oatpp-websocket` modules installed. You may run `utility/install-oatpp-modules.sh` 
script to install required oatpp modules.

```
$ mkdir build && cd build
$ cmake ..
$ make 
$ ./my-project-exe  # - run application.
```

#### In Docker

```
$ docker build -t oatpp-example-websocket .
$ docker run -p 8000:8000 -t oatpp-example-websocket
```

### Connect to Server

Endpoint - `ws://localhost:8000/websocket-connect`.

You may use [http://www.websocket.org/echo.html](http://www.websocket.org/echo.html) online tool to test your websocket server.
