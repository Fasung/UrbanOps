#if defined _WIN32 || defined _WIN64
#define DLLIMPORT __declspec(dllimport)
#elif defined __linux__
#define DLLIMPORT __attribute__((visibility("default")))
#else
#define DLLIMPORT
#endif

extern "C"
{
	DLLIMPORT void Initialize();

	DLLIMPORT bool IsInitialized();

	DLLIMPORT bool Login();

	// Deprecated: Debug function DELETE THIS
	// Deprecated: Debug function DELETE THIS
	// Deprecated: Debug function DELETE THIS
	DLLIMPORT void SetStatus(bool newStatus);

	DLLIMPORT const char* GetClientAddress();
}
