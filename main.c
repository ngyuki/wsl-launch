#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <shlwapi.h>

typedef HRESULT WslLaunchInteractive(
    PCWSTR distributionName,
    PCWSTR command,
    BOOL   useCurrentWorkingDirectory,
    DWORD  *exitCode
);

int wmain(int argc, wchar_t**argv)
{
    const wchar_t* file = PathFindFileName(argv[0]);
    wchar_t *name = malloc((wcslen(file) + 1) * sizeof(wchar_t));

    wcscpy(name, file);
    PathRemoveExtension(name);

    HINSTANCE wslapi = LoadLibrary(L"wslapi.dll");
    if (wslapi == NULL) {
        DWORD err = GetLastError();
        printf("err = %08x", err);
        free(name);
        return 1;
    }
    
    WslLaunchInteractive* wslLaunchInteractive = (WslLaunchInteractive*)GetProcAddress(wslapi, "WslLaunchInteractive");
    if (wslLaunchInteractive == NULL) {
        DWORD err = GetLastError();
        printf("err = %08x", err);
        free(name);
        return 1;
    }
    
    DWORD exitCode;
    HRESULT hr = wslLaunchInteractive(name, L"", FALSE, &exitCode);
    if (hr != S_OK) {
        printf("hr = %08x", hr);
        free(name);
        return 1;
    }
    
    free(name);
    return 0;
}
