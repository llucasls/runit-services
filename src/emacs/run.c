#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <dlfcn.h>

int main() {
	void *lib_handle = dlopen("./libconf.so", RTLD_LAZY);
	if (lib_handle) {
		void (*conf)(void) = dlsym(lib_handle, "conf");
		if (conf) conf();
		dlclose(lib_handle);
	}

	char *home_dir = getenv("HOME");
	int chdir_status = chdir(home_dir);

	if (chdir_status != 0) {
		perror("failed to change directory");
		return 1;
	}

	char *args[] = {"emacs", "--fg-daemon", NULL};
	execv("/usr/bin/emacs", args);

	perror("emacs");
	return 1;
}
