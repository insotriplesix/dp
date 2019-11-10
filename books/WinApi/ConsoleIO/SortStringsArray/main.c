#include <windows.h>
#include <tchar.h>
#include <stdarg.h>

#define STRING_MAX 0x200
#define STRINGS_COUNT 5

BOOL PrintStrings(HANDLE hOut, ...);
BOOL PrintMsg(HANDLE hOut, LPCTSTR pMsg);

INT StringsComparer(LPCVOID pszLhs, LPCVOID pszRhs)
{
	LPCTSTR pszLeft = *(LPCTSTR *)pszLhs;
	LPCTSTR pszRight = *(LPCTSTR *)pszRhs;
	return lstrcmp(pszLeft, pszRight);
}

INT _tmain(INT argc, LPTSTR argv[])
{
	TCHAR aStrings[STRINGS_COUNT][STRING_MAX] = {
		_T("Prikol"), _T("jOma"), _T("_lohov"),
		_T("perdun0k"), _T("herman")
	};

	LPVOID pArrayStart = (LPVOID)&aStrings[0];

	// Error :(
	qsort(pArrayStart, STRINGS_COUNT, sizeof(LPCTSTR), StringsComparer);

	HANDLE hOut = CreateFile(_T("CONOUT$"), GENERIC_WRITE, 0, NULL,
		OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	SetConsoleMode(hOut, ENABLE_WRAP_AT_EOL_OUTPUT |
		ENABLE_PROCESSED_OUTPUT);

	for (int i = 0; i < STRINGS_COUNT; ++i) {
		_ftprintf(stdout, _T("%d -- %s\n"), i, aStrings[i]);
	}

	CloseHandle(hOut);

	return 0;
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
