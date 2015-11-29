void fprocess(const char * pread, const char * pwrite)
{
	FILE * file_r;
	FILE * file_w;
	file_r = fopen(pread, "r");
	file_w = fopen(pwrite, "w");
	char ch;
	if ( NULL == file_r|| NULL == file_w)
		{
		    printf ("Error: NULL");
		    return ;
		}
	int a = 0, b = 0, i, c, d;
	for(i = 0; i < 12; i++)
		while (fgetc(file_r) != 10)
			;
	fscanf(file_r, "%i %i", &a, &b);
	c = a / b;
	d = a % b;
	fprintf(file_w, "%i %i", c, d);
	fclose (file_w);
	fclose (file_r);

}
