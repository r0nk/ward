void errExit(char * reason, int exitCode){
	deInitGraphics();
	fprintf(stderr,"ERR: %s\n",reason);
	exit(exitCode);
}
