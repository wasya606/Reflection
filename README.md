# Reflection
Allows to register any function as command and invoke it from string and pass to it parameters.
The number of parameters - any.
Supported parameters types: all integer, floating, pointers

Example:

1. There is a some function:
   void someFunction(void* param1, char* param2, double param3, int& param4, double&& param5);

2. Register this function as command: registerCommand("SomeCMD", &someFunction);
3. Call function as command: runCommand("SomeCMD 0x1c108d88 Parameter_2 333.333 44444 555.55");
