/*
 * SpeedFan Information Tool 2.0
 *
 * Retrieves temperature information from SpeedFan and outputs it to the console.
 *
 * (c) 2009, CapnBry 
 * Assumed to be free to use and reuse under the GNU Public License (GPL) v2.
 * as it was released here on the Kodi forum:
 * https://forum.kodi.tv/printthread.php?tid=52446
 * 
 * I have NOT compiled, tested nor used this code in any way, use at your own risk.
 *
 */
 
 #pragma pack(push,1)
struct SpeedFanSMA {
    WORD version;
    WORD flags;
    int MemSize;
    int handle;
    WORD NumTemps;
    WORD NumFans;
    WORD NumVolts;
    int temps[32];
    int fans[32];
    int volts[32];
};
#pragma pack(pop)

float CWIN32Util::GetSpeedFanTemp(int index)
{
  HANDLE hMapHandle = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0,
    sizeof(struct SpeedFanSMA), _T("SFSharedMemory_ALM"));
  if (hMapHandle == 0 || GetLastError() != ERROR_ALREADY_EXISTS)
    return 0.0f;
  struct SpeedFanSMA *p = (struct SpeedFanSMA *)MapViewOfFile(hMapHandle, FILE_MAP_READ,
    0, 0, sizeof(struct SpeedFanSMA));
  if (p)
  {
    float retVal = p->temps[index] / 100.0f;
    UnmapViewOfFile((void *)p);
    CloseHandle(hMapHandle);
    return retVal;
  }
  else
    CloseHandle(hMapHandle);
  return 0.0f;
}