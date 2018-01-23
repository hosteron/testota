#include <stdio.h>
#include <cf_buffer.h>
#include <cf_sigfd.h>
#include <cf_cmd.h>
#include <cf_fdevent.h>
#include <cf_common.h>
#include <cf_json.h>
#include <cf_log.h>
#include <sys/types.h>
       #include <sys/stat.h>
       #include <unistd.h>
#include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>

int main(int argc, char **argv)
{
	if(argc != 4)
	{
		printf("should be ./testota versionfile md5sum\n");
		return -1;
	}

	CFJson* nJson = CFJsonObjectNew();
	if(!nJson)
	{
		printf("new json error\n");
		return -1;
	}
	char filename[32] = {0};
	strncpy(filename, argv[2], sizeof(filename));
	printf("filename=%s\n", filename);
	char *ver = strstr(filename,"fw-");
	char *tail = strstr(filename, ".bin");
	if(!ver || !tail)
	{
		printf("filename =%s, syntax error\n",filename);
		return -1;
	}
	*tail = '\0';
	ver+= 3;
	CFJsonObjectAddString(nJson, "version", ver);
	CFJsonObjectAddString(nJson, "force","false");
	CFJson* onJson = CFJsonObjectNew();
	if(!onJson)
	{
		printf("new object json fail\n");
		return -1;
	}

	struct stat fst;
	
	if(stat(argv[2], &fst))
	{
		printf("stat file =%s error\n", argv[2]);
		CFJsonPut(nJson);
		CFJsonPut(onJson);
		return -1;
	}
	CFJsonObjectAddInt(onJson, "size",fst.st_size);
	CFJsonObjectAddString(onJson, "checkSum", argv[1]);
	CFJsonObjectAddString(onJson, "url", argv[3]);

	CFJsonObjectAdd(nJson,"fw0", onJson);
	char *teststr = CFJsonPrint(nJson);
	//printf("result = %s\n", teststr);
	int fd = open("latest.json",O_RDWR|O_CREAT);
	if(fd <= 0)
	{
		printf("open file fail\n");
		return -1;
	}
	write(fd, teststr,strlen(teststr)+1);
	fsync(fd);
	close(fd);
	CFJsonPut(nJson);

}
