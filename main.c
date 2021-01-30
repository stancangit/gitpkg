#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

int isFileExists(const char *reponame);
int isFileExistsAccess(const char *reponame);
int isFileExistsStats(const char *reponame);

int main(){
	char reponame[20]="\0";
	char ownername[20]="\0";
	/*system("echo 'foo'"); example of bash usage in c.*/
	char command[50]="\0";
	if(geteuid() != 0)
	{
	    printf("RUN AS ROOT, HOW MANY TIMES DO WE HAVE TO TELL YOU OLD MAN\njust because i hate you, i am adding an error code");
	    return 66;
	}	

	printf("Welcome to gitpkg, enter the repo name\n");
	scanf ("%s", reponame);
	printf ("now enter the username of the owner\n");
	scanf ("%s", ownername);
	system("sudo rm -rf /tmp/gitpkg/");
	sprintf(command, "git clone https://github.com/%s/%s /tmp/gitpkg", ownername, reponame);
	printf("%s", command);
	system(command);
	/*all code regarding getting from github here*/
	
	if (isFileExistsAccess("/tmp/gitpkg"))
        {
            printf("\nrepo was copied correctly\n");
        }
	if (isFileExistsAccess("/tmp/gitpkg/install.sh"))
        {
            printf("\npackage has install script\n");
	    system("cd /tmp/gitpkg && echo $(pwd) && chmod +x install.sh && /tmp/gitpkg/install.sh");
	    return 0;

        }
	else if (isFileExistsAccess("/tmp/gitpkg/configure"))
        {
            printf("\npackage has configure file\n");
	    system("cd /tmp/gitpkg && echo $(pwd) && /tmp/gitpkg/configure && make && make install");
	    return 0;

        }
	else if (isFileExistsAccess("/tmp/gitpkg/CMakeLists.txt"))
	{
            printf("\npackage has cmake file\n");
            system("cd /tmp/gitpkg && echo $(pwd) && cmake . && make && make install");
	    return 0;
	}
        else if (isFileExistsAccess("/tmp/gitpkg/meson.build"))
        {
            printf("\npackage has cmake file\n");
            system("cd /tmp/gitpkg && echo $(pwd) && mkdir build && meson build && cd build/ && meson install");
	    return 0;
        }
	else {printf("\nCouldn't find build file, check /tmp/gitpkg and manually compile\n"); return 1;}


}
/*All this shit just to check if file exists*/



int isFileExists(const char *reponame)
{
    // Try to open file
    FILE *fptr = fopen(reponame, "r");

    // If file does not exists
    if (fptr == NULL)
        return 0;

    // File exists hence close file and return true.
    fclose(fptr);

    return 1;
}




int isFileExistsAccess(const char *reponame)
{
    // Check for file existence
    if (access(reponame, F_OK) == -1)
        return 0;

    return 1;
}




int isFileExistsStats(const char *reponame)
{
    struct stat stats;

    stat(reponame, &stats);

    // Check for file existence
    if (stats.st_mode & F_OK)
        return 1;

    return 0;
}
