# storm

This project is a high-concurrency C++ server framework designed to efficiently handle multiple client requests via the TCP/IP protocol. The server utilizes epoll for I/O multiplexing, allowing it to manage thousands of concurrent connections with minimal resource usage. The framework is highly modular and extensible, allowing different business logic to be encapsulated into plugins.

## 🚀 Features

- **High-Concurrency**: Efficiently handles large numbers of simultaneous client connections.
- **IO Multiplexing**: Uses epoll to efficiently handle multiple client connections with minimal thread overhead.
- **Task-Based Processing**: Requests from connected clients are encapsulated into tasks and distributed to a thread pool for execution.
- **Modular Business Logic**: Business logic is implemented in plugins (dynamic libraries), enabling easy extension and customization.
- **Separation of Business Logic and Framework**: The workflow-based design separates the server framework from application-specific logic, making it easy to add new features without modifying the core framework.

## 🛠️ System Workflow

1. **Client Connections**: Multiple clients connect to the server via TCP/IP.
2. **IO Multiplexing**: The server uses epoll to handle both new connections and incoming data from connected clients.
3. **Task Creation**: When a client sends a request, it is encapsulated into a task and passed to the Task Dispatcher.
4. **Task Distribution**: The Task Dispatcher assigns the task to a free worker thread in the Thread Pool.
5. **Task Execution**: Worker threads execute the task by passing it to the Business Engine, which executes a series of plugins in sequence based on a Workflow.
6. **Plugin Execution**: Each plugin in the workflow performs a specific part of the business logic, and after all plugins execute, the task is completed.

## 📂 Core Components

### Plugin

The Plugin class is an abstract class for business logic. Each plugin encapsulates a specific part of the business logic and can be loaded as a shared library.

- `setName(const std::string& name)`: Sets the name of the plugin.
- `getName()`: Gets the name of the plugin.
- `setSwitch(bool flag)`: Enables or disables the plugin.
- `getSwitch()`: Checks if the plugin is enabled.
- `virtual bool run(Context& ctx)`: Executes the plugin’s business logic.

### PluginHelper

PluginHelper manages the dynamic loading and unloading of plugins, as well as resolving symbols (functions) in the plugin.

- `load(const std::string& plugin)`: Loads a plugin from a shared library.
- `unload(const std::string& plugin)`: Unloads the plugin.
- `symbol(const std::string& plugin, const std::string& symbol)`: Retrieves a symbol from the plugin.
- `show()`: Lists loaded plugins.

### Work

A Work represents a series of plugins executed in sequence as part of the business logic. Each Work contains multiple plugins, and its execution is managed by the Workflow.

- `setId(int id)` Sets the unique ID for the work.
- `getId()`: Retrieves the work ID.
- `setSwitch(bool flag)`: Enables or disables the work.
- `getSwitch()`: Checks if the work is enabled.
- `append(Plugin* plugin)`: Appends a plugin to the work.
- `bool run(Context& ctx)`: Executes all the plugins in the work.

### Workflow

The Workflow class manages a set of Work objects and controls the execution flow of tasks by sequentially executing plugins from the corresponding Work.

- `load(const std::string& config)`: Loads a workflow configuration.
- `run(int id, const std::string& input, std::string& output)`: Executes the workflow for a specific ID.

### Task and TaskFactory

Tasks represent client requests. The WorkTask class is a concrete implementation of the Task class, encapsulating a client request.

- `run()`: Executes the task.
- `destroy()`: Cleans up resources associated with the task.

The TaskFactory class creates tasks dynamically based on the socket file descriptor.

## 🖥️ Getting Started

1. Clone the Repository

```sh
git clone https://github.com/jiafie7/storm.git
cd storm
```

2. Build the Project

```sh
# compile plugin
g++ -shared -fPIC -std=c++11 -I. plugin/echo_plugin.cpp utility/log_system.cpp utility/system.cpp -o plugin/echo_plugin.so

# compile service
mkdir build
cd build
cmake ..
make

# start service
./server

# function test
python3 client.py

# stress test
python3 bench.py 10000
```

3. Output

```sh
concurrence: 10000
thread finished, total time cost: 3.589s
Connection time=0.079ms, Request time=0.828ms, Total time=0.929ms
```

## 📂 Project Structure

```
storm/
├── config/ ──── configuration file
├── utility/ ──── tool class
├── xml/ ──── xml parser
├── socket/ ──── epoll for IO multiplexing
├── frame ──── encapsulate server
├── thread ──── thread pool and task dispatcher
├── task ──── concrete task implementation
├── engine ──── business engine implementation
├── plugin ──── business plugin implementation
├── server.cpp ──── main program entry file
└── CMakeLists.txt ──── project compile and build file
```

## 📝 License

This project is licensed under the MIT License. See the LICENSE file for more information.

## 🤝 Contributing

Contributions, bug reports, and feature requests are welcome. Feel free to fork the repository, open issues, or submit pull requests.
