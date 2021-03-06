#include <stdio.h>
#include "src/include/wren.h"

static void writeFn(WrenVM* vm, const char* text)
{
	printf("%s", text);
}

void errorFn(WrenVM* vm, WrenErrorType errorType,
		const char* module, const int line,
		const char* msg)
{
	switch (errorType)
	{
		case WREN_ERROR_COMPILE:
			{
				printf("[%s line %d] [Error] %s\n", module, line, msg);
			} break;
		case WREN_ERROR_STACK_TRACE:
			{
				printf("[%s line %d] in %s\n", module, line, msg);
			} break;
		case WREN_ERROR_RUNTIME:
			{
				printf("[Runtime Error] %s\n", msg);
			} break;
	}
}

int main()
{
	char Data[1024];

	WrenConfiguration config;
	wrenInitConfiguration(&config);
	config.writeFn = &writeFn;
	config.errorFn = &errorFn;
	WrenVM* vm = wrenNewVM(&config);

	const char* module = "main";
	//const char* script = "System.print(\"I am running in a VM!\")";

	fgets(Data, 1024, stdin);
	WrenInterpretResult result = wrenInterpret(vm, module, (const char*) Data);//script);

	switch (result)
	{
		case WREN_RESULT_COMPILE_ERROR:
			{ printf("Compile Error!\n"); } break;
		case WREN_RESULT_RUNTIME_ERROR:
			{ printf("Runtime Error!\n"); } break;
		case WREN_RESULT_SUCCESS:
			{ printf("Success!\n"); } break;
	}

	wrenFreeVM(vm);

}
