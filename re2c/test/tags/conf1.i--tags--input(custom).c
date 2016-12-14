/* Generated by re2c */
#include <stddef.h>
#include <stdio.h>

static inline unsigned parse_oct(const char *s, const char *e)
{
    unsigned oct = 0;
    for (; s != e; ++s) {
        oct = oct * 10 + *s - '0';
    }
    return oct;
}

static void lex(const char *s)
{
#define YYPEEK()     *s
#define YYSKIP()     ++s
#define YYBACKUP()   marker = s
#define YYRESTORE()  s = marker
#define ZZBT(t)      t = s
#define ZZRT(t)      s = t
#define ZZCT(t1, t2) t1 = t2
    const char *marker, *p0, *p1, *p2, *p3;
    const char *zz_1;const char *zz_2;const char *zz_3;const char *zz_4;
    
{
	char yych;
	yych = YYPEEK ();
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		ZZBT (zz_4);
		goto yy4;
	default:	goto yy2;
	}
yy2:
	YYSKIP ();
yy3:
	{ printf("error\n"); return; }
yy4:
	YYSKIP ();
	YYBACKUP ();
	yych = YYPEEK ();
	switch (yych) {
	case '.':
		ZZBT (zz_3);
		goto yy5;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy7;
	default:	goto yy3;
	}
yy5:
	YYSKIP ();
	yych = YYPEEK ();
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy8;
	default:	goto yy6;
	}
yy6:
	YYRESTORE ();
	goto yy3;
yy7:
	YYSKIP ();
	yych = YYPEEK ();
	switch (yych) {
	case '.':
		ZZBT (zz_3);
		goto yy5;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy9;
	default:	goto yy6;
	}
yy8:
	YYSKIP ();
	yych = YYPEEK ();
	switch (yych) {
	case '.':
		ZZBT (zz_2);
		goto yy10;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy11;
	default:	goto yy6;
	}
yy9:
	YYSKIP ();
	yych = YYPEEK ();
	switch (yych) {
	case '.':
		ZZBT (zz_3);
		goto yy5;
	default:	goto yy6;
	}
yy10:
	YYSKIP ();
	yych = YYPEEK ();
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy12;
	default:	goto yy6;
	}
yy11:
	YYSKIP ();
	yych = YYPEEK ();
	switch (yych) {
	case '.':
		ZZBT (zz_2);
		goto yy10;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy13;
	default:	goto yy6;
	}
yy12:
	YYSKIP ();
	yych = YYPEEK ();
	switch (yych) {
	case '.':
		ZZBT (zz_1);
		goto yy14;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy15;
	default:	goto yy6;
	}
yy13:
	YYSKIP ();
	yych = YYPEEK ();
	switch (yych) {
	case '.':
		ZZBT (zz_2);
		goto yy10;
	default:	goto yy6;
	}
yy14:
	YYSKIP ();
	yych = YYPEEK ();
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy16;
	default:	goto yy6;
	}
yy15:
	YYSKIP ();
	yych = YYPEEK ();
	switch (yych) {
	case '.':
		ZZBT (zz_1);
		goto yy14;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy18;
	default:	goto yy6;
	}
yy16:
	YYSKIP ();
	yych = YYPEEK ();
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy19;
	default:	goto yy17;
	}
yy17:
	ZZCT (p3, zz_1);
	ZZCT (p2, zz_2);
	ZZCT (p1, zz_3);
	ZZCT (p0, zz_4);
	{
            printf("%u.%u.%u.%u\n",
                parse_oct(p0, p1),
                parse_oct(p1 + 1, p2),
                parse_oct(p2 + 1, p3),
                parse_oct(p3 + 1, s));
            return;
        }
yy18:
	YYSKIP ();
	yych = YYPEEK ();
	switch (yych) {
	case '.':
		ZZBT (zz_1);
		goto yy14;
	default:	goto yy6;
	}
yy19:
	YYSKIP ();
	yych = YYPEEK ();
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy20;
	default:	goto yy17;
	}
yy20:
	YYSKIP ();
	goto yy17;
}

}

int main(int argc, char **argv)
{
    for (int i = 1; i < argc; ++i) {
        lex(argv[i]);
    }
    return 0;
}
