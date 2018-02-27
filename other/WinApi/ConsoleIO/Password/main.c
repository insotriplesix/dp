#include <windows.h>
#include <tchar.h>
#include <stdarg.h>

#define BUFSIZE 0x200

VOID CheckPasswords(LPTSTR pPass1, LPTSTR pPass2);
BOOL PrintStrings(HANDLE hOut, ...);
BOOL PrintMsg(HANDLE hOut, LPCTSTR pMsg);
BOOL ConsolePrompt(LPCTSTR pPromptMsg, LPTSTR pResp, DWORD maxChar, BOOL echo);
VOID ReportError(LPCTSTR userMessage, DWORD exitCode, BOOL printErrorMessage);

INT _tmain(INT argc, LPTSTR argv[])
{
	INT rc = 0;

	PTCHAR pPass1 = malloc(sizeof(TCHAR) * BUFSIZE);
	PTCHAR pPass2 = malloc(sizeof(TCHAR) * BUFSIZE);

	LPCTSTR pMsgInputPass = _T("\nInput password: ");
	LPCTSTR pMsgConfirmPass = _T("\nConfirm password: ");

	if (!ConsolePrompt(pMsgInputPass, (LPTSTR)pPass1, BUFSIZE, FALSE) ||
		!ConsolePrompt(pMsgConfirmPass, (LPTSTR)pPass2, BUFSIZE, FALSE)) {
		free(pPass1);
		free(pPass2);
		return -1;
	}

	CheckPasswords(pPass1, pPass2);

	free(pPass1);
	free(pPass2);
	return 0;
}

VOID CheckPasswords(LPTSTR pPass1, LPTSTR pPass2)
{
	if (lstrcmp(pPass1, pPass2) != 0)
		_ftprintf(stdout, _T("\nPasswords are different.\n"));
	else
		_ftprintf(stdout, _T("\nPasswords are equal.\n"));
}

BOOL PrintStrings(HANDLE hOut, ...)
{
	DWORD msgLen, count;
	LPCTSTR pMsg;
	va_list pMsgList;

	va_start(pMsgList, hOut);

	while ((pMsg = va_arg(pMsgList, LPCTSTR)) != NULL) {
		msgLen = _tcslen(pMsg);
		if (!WriteConsole(hOut, pMsg, msgLen, &count, NULL) &&
			!WriteFile(hOut, pMsg, msgLen * sizeof(TCHAR), &count, NULL)) {
			va_end(pMsgList);
			return FALSE;
		}
	}

	va_end(pMsgList);

	return TRUE;
}

BOOL PrintMsg(HANDLE hOut, LPCTSTR pMsg)
{
	return PrintStrings(hOut, pMsg, NULL);
}

BOOL ConsolePrompt(LPCTSTR pPromptMsg, LPTSTR pResp, DWORD maxChar, BOOL echo)
{
	HANDLE hIn, hOut;
	DWORD charIn, echoFlag;
	BOOL success;

	hIn = CreateFile(_T("CONIN$"), GENERIC_READ | GENERIC_WRITE, 0, NULL,
		OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	hOut = CreateFile(_T("CONOUT$"), GENERIC_WRITE, 0, NULL,
		OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	echoFlag = echo ? ENABLE_ECHO_INPUT : 0;

	success = SetConsoleMode(hIn, ENABLE_LINE_INPUT | echoFlag |
		ENABLE_WRAP_AT_EOL_OUTPUT | ENABLE_PROCESSED_OUTPUT) &&
		SetConsoleMode(hOut, ENABLE_WRAP_AT_EOL_OUTPUT |
		ENABLE_PROCESSED_OUTPUT) && PrintStrings(hOut, pPromptMsg, NULL) &&
		ReadConsole(hIn, pResp, maxChar - 2, &charIn, NULL);

	if (success)
		pResp[charIn - 2] = '\0';
	else
		ReportError(_T("ConsolePrompt failure."), 0, TRUE);

	CloseHandle(hIn);
	CloseHandle(hOut);

	return success;
}

VOID ReportError(LPCTSTR userMessage, DWORD exitCode, BOOL printErrorMessage)
{
	DWORD eMsgLen, errNum = GetLastError();
	LPTSTR lpvSysMsg;

	_ftprintf(stderr, _T("%s\n"), userMessage);

	if (printErrorMessage) {
		eMsgLen = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM, NULL, errNum,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&lpvSysMsg, 0, NULL);

		if (eMsgLen > 0)
			_ftprintf(stderr, _T("%s\n"), lpvSysMsg);
		else
			_ftprintf(stderr, _T("Last Error Number; %d.\n"), errNum);

		if (lpvSysMsg != NULL)
			LocalFree(lpvSysMsg);
	}

	if (exitCode > 0)
		ExitProcess(exitCode);
}
