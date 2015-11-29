void fprocess(const char * pread, const char * pwrite)
{
	FILE * file_r;
	FILE * file_w;
	file_r = fopen(pread, "r");
	file_w = fopen(pwrite, "w");
	char ch;
	if ( NULL == fr|| NULL == fw)
		{
		    printf ("Error: NULL");
		    return ;
		}
	int a = 0, b = 0, i;
	for(i = 0; i < 13; i++)
		while (fgetc(fr) != 10)
			;
	fscanf(file_r, "%i %i", &a, &b);
	fprintf(file_w, "%i %i", a / b, a % b);
	fclose (file_w);
	fclose (file_r);

}
