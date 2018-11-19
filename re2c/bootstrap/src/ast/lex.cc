#line 1 "../src/ast/lex.re"
#include "src/util/c99_stdint.h"
#include <stddef.h>
#include <string.h>
#include <algorithm>
#include <limits>
#include <string>

#include "src/conf/msg.h"
#include "src/code/output.h"
#include "src/re/encoding/enc.h"
#include "src/ast/input.h"
#include "src/ast/ast.h"
#include "src/ast/scanner.h"
#include "src/ast/parser.h" // needed by "y.tab.h"
#include "src/ast/unescape.h"
#include "src/util/range.h"
#include "src/util/s_to_n32_unsafe.h"
#include "src/util/string_utils.h"
#include "y.tab.h"

extern YYSTYPE yylval;

#define    YYCTYPE      unsigned char
#define    YYCURSOR     cur
#define    YYLIMIT      lim
#define    YYMARKER     mar
#define    YYCTXMARKER  ctx
#define    YYFILL(n)    { fill (n); }

namespace re2c
{

#line 56 "../src/ast/lex.re"


Scanner::ParseMode Scanner::echo(OutputFile &out)
{
    if (eof && cur == eof) // Catch EOF
    {
        return Stop;
    }

    tok = cur;
echo:
    ptr = cur;


#line 50 "src/ast/lex.cc"
{
	YYCTYPE yych;
	unsigned int yyaccept = 0;
	static const unsigned char yybm[] = {
		  0, 128, 128, 128, 128, 128, 128, 128, 
		128, 160,   0, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		160, 128,   0, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128,   0, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
	};
	if ((YYLIMIT - YYCURSOR) < 18) YYFILL(18);
	yych = (YYCTYPE)*YYCURSOR;
	if (yych <= '\r') {
		if (yych <= '\t') {
			if (yych >= 0x01) goto yy4;
		} else {
			if (yych <= '\n') goto yy6;
			if (yych <= '\f') goto yy4;
			goto yy8;
		}
	} else {
		if (yych <= '%') {
			if (yych <= '$') goto yy4;
			goto yy9;
		} else {
			if (yych == '/') goto yy10;
			goto yy4;
		}
	}
	++YYCURSOR;
#line 149 "../src/ast/lex.re"
	{
        if (cur != eof) goto echo;
        out.wraw(tok, ptr);
        return Stop;
    }
#line 114 "src/ast/lex.cc"
yy4:
	++YYCURSOR;
yy5:
#line 167 "../src/ast/lex.re"
	{ goto echo; }
#line 120 "src/ast/lex.cc"
yy6:
	yyaccept = 0;
	yych = (YYCTYPE)*(YYMARKER = ++YYCURSOR);
	if (yybm[0+yych] & 32) {
		goto yy11;
	}
	if (yych == '#') goto yy14;
yy7:
#line 161 "../src/ast/lex.re"
	{
        cline++;
        pos = cur;
        goto echo;
    }
#line 135 "src/ast/lex.cc"
yy8:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == '\n') goto yy6;
	goto yy5;
yy9:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == '{') goto yy16;
	goto yy5;
yy10:
	yyaccept = 1;
	yych = (YYCTYPE)*(YYMARKER = ++YYCURSOR);
	if (yych == '*') goto yy18;
	goto yy5;
yy11:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = (YYCTYPE)*YYCURSOR;
	if (yybm[0+yych] & 32) {
		goto yy11;
	}
	if (yych == '#') goto yy14;
yy13:
	YYCURSOR = YYMARKER;
	if (yyaccept == 0) {
		goto yy7;
	} else {
		goto yy5;
	}
yy14:
	++YYCURSOR;
	if ((YYLIMIT - YYCURSOR) < 5) YYFILL(5);
	yych = (YYCTYPE)*YYCURSOR;
	if (yych <= 0x1F) {
		if (yych == '\t') goto yy14;
		goto yy13;
	} else {
		if (yych <= ' ') goto yy14;
		if (yych == 'l') goto yy19;
		goto yy13;
	}
yy16:
	++YYCURSOR;
#line 70 "../src/ast/lex.re"
	{
        out.wraw(tok, ptr);
        return Parse;
    }
#line 183 "src/ast/lex.cc"
yy18:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == '!') goto yy20;
	goto yy13;
yy19:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'i') goto yy21;
	goto yy13;
yy20:
	yych = (YYCTYPE)*++YYCURSOR;
	switch (yych) {
	case 'g':	goto yy22;
	case 'h':	goto yy23;
	case 'i':	goto yy24;
	case 'm':	goto yy25;
	case 'r':	goto yy26;
	case 's':	goto yy27;
	case 't':	goto yy28;
	case 'u':	goto yy29;
	default:	goto yy13;
	}
yy21:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'n') goto yy30;
	goto yy13;
yy22:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'e') goto yy31;
	goto yy13;
yy23:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'e') goto yy32;
	goto yy13;
yy24:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'g') goto yy33;
	goto yy13;
yy25:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'a') goto yy34;
	if (yych == 't') goto yy35;
	goto yy13;
yy26:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'e') goto yy36;
	if (yych == 'u') goto yy37;
	goto yy13;
yy27:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 't') goto yy38;
	goto yy13;
yy28:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'y') goto yy39;
	goto yy13;
yy29:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 's') goto yy40;
	goto yy13;
yy30:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'e') goto yy41;
	goto yy13;
yy31:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 't') goto yy42;
	goto yy13;
yy32:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'a') goto yy43;
	goto yy13;
yy33:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'n') goto yy44;
	goto yy13;
yy34:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'x') goto yy45;
	goto yy13;
yy35:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'a') goto yy46;
	goto yy13;
yy36:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == '2') goto yy47;
	goto yy13;
yy37:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'l') goto yy48;
	goto yy13;
yy38:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'a') goto yy49;
	goto yy13;
yy39:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'p') goto yy50;
	goto yy13;
yy40:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'e') goto yy51;
	goto yy13;
yy41:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych <= '0') goto yy53;
	if (yych <= '9') goto yy13;
	goto yy53;
yy42:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 's') goto yy54;
	goto yy13;
yy43:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'd') goto yy55;
	goto yy13;
yy44:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'o') goto yy56;
	goto yy13;
yy45:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == ':') goto yy57;
	if (yych == 'n') goto yy58;
	goto yy13;
yy46:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'g') goto yy59;
	goto yy13;
yy47:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'c') goto yy16;
	goto yy13;
yy48:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'e') goto yy60;
	goto yy13;
yy49:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'g') goto yy61;
	goto yy13;
yy50:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'e') goto yy62;
	goto yy13;
yy51:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == ':') goto yy63;
	goto yy13;
yy52:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = (YYCTYPE)*YYCURSOR;
yy53:
	if (yych <= 0x1F) {
		if (yych == '\t') goto yy52;
		goto yy13;
	} else {
		if (yych <= ' ') goto yy52;
		if (yych <= '0') goto yy13;
		if (yych <= '9') {
			YYCTXMARKER = YYCURSOR;
			goto yy64;
		}
		goto yy13;
	}
yy54:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 't') goto yy66;
	goto yy13;
yy55:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'e') goto yy67;
	goto yy13;
yy56:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'r') goto yy68;
	goto yy13;
yy57:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'r') goto yy69;
	goto yy13;
yy58:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'm') goto yy70;
	goto yy13;
yy59:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 's') goto yy71;
	goto yy13;
yy60:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 's') goto yy72;
	goto yy13;
yy61:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 's') goto yy73;
	goto yy13;
yy62:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 's') goto yy74;
	goto yy13;
yy63:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'r') goto yy75;
	goto yy13;
yy64:
	++YYCURSOR;
	if ((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
	yych = (YYCTYPE)*YYCURSOR;
	if (yybm[0+yych] & 64) {
		goto yy64;
	}
	if (yych <= '\f') {
		if (yych <= 0x08) goto yy13;
		if (yych <= '\t') goto yy76;
		if (yych <= '\n') goto yy78;
		goto yy13;
	} else {
		if (yych <= '\r') goto yy80;
		if (yych == ' ') goto yy76;
		goto yy13;
	}
yy66:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'a') goto yy81;
	goto yy13;
yy67:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'r') goto yy82;
	goto yy13;
yy68:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'e') goto yy83;
	goto yy13;
yy69:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'e') goto yy84;
	goto yy13;
yy70:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'a') goto yy85;
	goto yy13;
yy71:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == ':') goto yy86;
	goto yy13;
yy72:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == ':') goto yy87;
	goto yy13;
yy73:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == ':') goto yy88;
	goto yy13;
yy74:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == ':') goto yy89;
	goto yy13;
yy75:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'e') goto yy90;
	goto yy13;
yy76:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = (YYCTYPE)*YYCURSOR;
	if (yych <= 0x1F) {
		if (yych == '\t') goto yy76;
		goto yy13;
	} else {
		if (yych <= ' ') goto yy76;
		if (yych == '"') goto yy91;
		goto yy13;
	}
yy78:
	++YYCURSOR;
	YYCURSOR = YYCTXMARKER;
#line 155 "../src/ast/lex.re"
	{
        out.wraw(tok, ptr + 1);
        set_sourceline();
        goto echo;
    }
#line 468 "src/ast/lex.cc"
yy80:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == '\n') goto yy78;
	goto yy13;
yy81:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 't') goto yy93;
	goto yy13;
yy82:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == ':') goto yy94;
	goto yy13;
yy83:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == ':') goto yy95;
	goto yy13;
yy84:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == '2') goto yy96;
	goto yy13;
yy85:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 't') goto yy97;
	goto yy13;
yy86:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'r') goto yy98;
	goto yy13;
yy87:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'r') goto yy99;
	goto yy13;
yy88:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'r') goto yy100;
	goto yy13;
yy89:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'r') goto yy101;
	goto yy13;
yy90:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == '2') goto yy102;
	goto yy13;
yy91:
	++YYCURSOR;
	if ((YYLIMIT - YYCURSOR) < 3) YYFILL(3);
	yych = (YYCTYPE)*YYCURSOR;
	if (yybm[0+yych] & 128) {
		goto yy91;
	}
	if (yych <= '\n') goto yy13;
	if (yych <= '"') goto yy103;
	goto yy104;
yy93:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'e') goto yy105;
	goto yy13;
yy94:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'r') goto yy106;
	goto yy13;
yy95:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'r') goto yy107;
	goto yy13;
yy96:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'c') goto yy108;
	goto yy13;
yy97:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'c') goto yy110;
	goto yy13;
yy98:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'e') goto yy111;
	goto yy13;
yy99:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'e') goto yy112;
	goto yy13;
yy100:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'e') goto yy113;
	goto yy13;
yy101:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'e') goto yy114;
	goto yy13;
yy102:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'c') goto yy115;
	goto yy13;
yy103:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == '\n') goto yy78;
	if (yych == '\r') goto yy80;
	goto yy13;
yy104:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = (YYCTYPE)*YYCURSOR;
	if (yych <= 0x00) goto yy13;
	if (yych == '\n') goto yy13;
	goto yy91;
yy105:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == ':') goto yy117;
	goto yy13;
yy106:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'e') goto yy118;
	goto yy13;
yy107:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'e') goto yy119;
	goto yy13;
yy108:
	++YYCURSOR;
#line 91 "../src/ast/lex.re"
	{
        out.wraw(tok, ptr);
        out.wdelay_yymaxfill();
        lex_end_of_comment(out);
        goto echo;
    }
#line 596 "src/ast/lex.cc"
yy110:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'h') goto yy120;
	goto yy13;
yy111:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == '2') goto yy121;
	goto yy13;
yy112:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == '2') goto yy122;
	goto yy13;
yy113:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == '2') goto yy123;
	goto yy13;
yy114:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == '2') goto yy124;
	goto yy13;
yy115:
	++YYCURSOR;
#line 80 "../src/ast/lex.re"
	{
        out.wraw(tok, ptr);
        return Reuse;
    }
#line 624 "src/ast/lex.cc"
yy117:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'r') goto yy125;
	goto yy13;
yy118:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == '2') goto yy126;
	goto yy13;
yy119:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == '2') goto yy127;
	goto yy13;
yy120:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == ':') goto yy128;
	goto yy13;
yy121:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'c') goto yy129;
	goto yy13;
yy122:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'c') goto yy131;
	goto yy13;
yy123:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'c') goto yy133;
	goto yy13;
yy124:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'c') goto yy135;
	goto yy13;
yy125:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'e') goto yy137;
	goto yy13;
yy126:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'c') goto yy138;
	goto yy13;
yy127:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'c') goto yy139;
	goto yy13;
yy128:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'r') goto yy141;
	goto yy13;
yy129:
	++YYCURSOR;
#line 127 "../src/ast/lex.re"
	{
        out.wraw(tok, ptr);
        lex_tags(out, true);
        goto echo;
    }
#line 681 "src/ast/lex.cc"
yy131:
	++YYCURSOR;
#line 75 "../src/ast/lex.re"
	{
        out.wraw(tok, ptr);
        return Rules;
    }
#line 689 "src/ast/lex.cc"
yy133:
	++YYCURSOR;
#line 121 "../src/ast/lex.re"
	{
        out.wraw(tok, ptr);
        lex_tags(out, false);
        goto echo;
    }
#line 698 "src/ast/lex.cc"
yy135:
	++YYCURSOR;
#line 112 "../src/ast/lex.re"
	{
        out.wraw(tok, ptr);
        out.wdelay_line_info_output();
        out.wdelay_types();
        out.wdelay_line_info_input(cline, get_fname());
        lex_end_of_comment(out);
        goto echo;
    }
#line 710 "src/ast/lex.cc"
yy137:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == '2') goto yy142;
	goto yy13;
yy138:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == ':') goto yy143;
	goto yy13;
yy139:
	++YYCURSOR;
#line 85 "../src/ast/lex.re"
	{
        out.wraw(tok, ptr);
        lex_end_of_comment(out);
        goto echo;
    }
#line 727 "src/ast/lex.cc"
yy141:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'e') goto yy144;
	goto yy13;
yy142:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'c') goto yy145;
	goto yy13;
yy143:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'o') goto yy147;
	goto yy13;
yy144:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == '2') goto yy148;
	goto yy13;
yy145:
	++YYCURSOR;
#line 105 "../src/ast/lex.re"
	{
        out.wraw(tok, ptr);
        out.wdelay_state_goto(0);
        lex_end_of_comment(out);
        goto echo;
    }
#line 753 "src/ast/lex.cc"
yy147:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'f') goto yy149;
	if (yych == 'n') goto yy150;
	goto yy13;
yy148:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'c') goto yy152;
	goto yy13;
yy149:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'f') goto yy154;
	goto yy13;
yy150:
	++YYCURSOR;
#line 133 "../src/ast/lex.re"
	{
        out.wraw(tok, ptr);
        out.header_mode(true);
        out.need_header = true;
        lex_end_of_comment(out);
        goto echo;
    }
#line 777 "src/ast/lex.cc"
yy152:
	++YYCURSOR;
#line 98 "../src/ast/lex.re"
	{
        out.wraw(tok, ptr);
        out.wdelay_yymaxnmatch();
        lex_end_of_comment(out);
        goto echo;
    }
#line 787 "src/ast/lex.cc"
yy154:
	++YYCURSOR;
#line 141 "../src/ast/lex.re"
	{
        out.wraw(tok, ptr);
        out.header_mode(false);
        out.wdelay_line_info_input(cline, get_fname());
        lex_end_of_comment(out);
        goto echo;
    }
#line 798 "src/ast/lex.cc"
}
#line 168 "../src/ast/lex.re"

}

void Scanner::lex_end_of_comment(OutputFile &out)
{
    uint32_t ignored = 0;
    for (;;) {
#line 808 "src/ast/lex.cc"
{
	YYCTYPE yych;
	if ((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
	yych = (YYCTYPE)*YYCURSOR;
	if (yych <= '\f') {
		if (yych <= 0x00) goto yy158;
		if (yych == '\n') goto yy162;
		goto yy160;
	} else {
		if (yych <= '\r') goto yy164;
		if (yych == '*') goto yy165;
		goto yy160;
	}
yy158:
	++YYCURSOR;
#line 175 "../src/ast/lex.re"
	{ fatal_lc(get_cline(), get_column(), "expected end of block"); }
#line 826 "src/ast/lex.cc"
yy160:
	++YYCURSOR;
yy161:
#line 177 "../src/ast/lex.re"
	{ continue; }
#line 832 "src/ast/lex.cc"
yy162:
	++YYCURSOR;
#line 178 "../src/ast/lex.re"
	{ ++ignored; continue; }
#line 837 "src/ast/lex.cc"
yy164:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == '\n') goto yy162;
	goto yy161;
yy165:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych != '/') goto yy161;
	++YYCURSOR;
#line 179 "../src/ast/lex.re"
	{
            if (ignored > 0) {
                cline += ignored;
                out.wdelay_line_info_input(cline, get_fname());
            }
            tok = pos = cur;
            return;
        }
#line 855 "src/ast/lex.cc"
}
#line 187 "../src/ast/lex.re"
}
}

void Scanner::lex_tags(OutputFile &out, bool mtags)
{
    std::string fmt, sep;
    for (;;) {
#line 865 "src/ast/lex.cc"
{
	YYCTYPE yych;
	static const unsigned char yybm[] = {
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0, 128,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		128,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
	};
	if ((YYLIMIT - YYCURSOR) < 9) YYFILL(9);
	yych = (YYCTYPE)*YYCURSOR;
	if (yybm[0+yych] & 128) {
		goto yy172;
	}
	if (yych <= ')') {
		if (yych <= '\n') {
			if (yych >= '\t') goto yy175;
		} else {
			if (yych == '\r') goto yy177;
		}
	} else {
		if (yych <= 'f') {
			if (yych <= '*') goto yy178;
			if (yych >= 'f') goto yy179;
		} else {
			if (yych == 's') goto yy180;
		}
	}
	++YYCURSOR;
yy171:
#line 194 "../src/ast/lex.re"
	{ fatal_lc(get_cline(), get_column(), "unrecognized configuration"); }
#line 925 "src/ast/lex.cc"
yy172:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = (YYCTYPE)*YYCURSOR;
	if (yybm[0+yych] & 128) {
		goto yy172;
	}
#line 199 "../src/ast/lex.re"
	{ continue; }
#line 935 "src/ast/lex.cc"
yy175:
	++YYCURSOR;
#line 200 "../src/ast/lex.re"
	{ ++cline; continue; }
#line 940 "src/ast/lex.cc"
yy177:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == '\n') goto yy175;
	goto yy171;
yy178:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == '/') goto yy181;
	goto yy171;
yy179:
	yych = (YYCTYPE)*(YYMARKER = ++YYCURSOR);
	if (yych == 'o') goto yy183;
	goto yy171;
yy180:
	yych = (YYCTYPE)*(YYMARKER = ++YYCURSOR);
	if (yych == 'e') goto yy185;
	goto yy171;
yy181:
	++YYCURSOR;
#line 201 "../src/ast/lex.re"
	{
            out.wdelay_tags(new ConfTags(fmt, sep), mtags);
            tok = pos = cur;
            return;
        }
#line 965 "src/ast/lex.cc"
yy183:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'r') goto yy186;
yy184:
	YYCURSOR = YYMARKER;
	goto yy171;
yy185:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'p') goto yy187;
	goto yy184;
yy186:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'm') goto yy188;
	goto yy184;
yy187:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'a') goto yy189;
	goto yy184;
yy188:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'a') goto yy190;
	goto yy184;
yy189:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'r') goto yy191;
	goto yy184;
yy190:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 't') goto yy192;
	goto yy184;
yy191:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'a') goto yy194;
	goto yy184;
yy192:
	++YYCURSOR;
#line 196 "../src/ast/lex.re"
	{ fmt = lex_conf_string(); continue; }
#line 1004 "src/ast/lex.cc"
yy194:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych != 't') goto yy184;
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych != 'o') goto yy184;
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych != 'r') goto yy184;
	++YYCURSOR;
#line 197 "../src/ast/lex.re"
	{ sep = lex_conf_string(); continue; }
#line 1015 "src/ast/lex.cc"
}
#line 206 "../src/ast/lex.re"
}
}

int Scanner::scan(const conopt_t *globopts)
{
scan:
    tchar = cur - pos;
    tok = cur;

#line 1027 "src/ast/lex.cc"
{
	YYCTYPE yych;
	unsigned int yyaccept = 0;
	static const unsigned char yybm[] = {
		  0, 128, 128, 128, 128, 128, 128, 128, 
		128, 144,   0, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		144, 128,   0, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		224, 224, 224, 224, 224, 224, 224, 224, 
		224, 224, 128, 128, 128, 128, 128, 128, 
		128, 160, 160, 160, 160, 160, 160, 160, 
		160, 160, 160, 160, 160, 160, 160, 160, 
		160, 160, 160, 160, 160, 160, 160, 160, 
		160, 160, 160, 128,   0, 128, 128, 160, 
		128, 160, 160, 160, 160, 160, 160, 160, 
		160, 160, 160, 160, 160, 160, 160, 160, 
		160, 160, 160, 160, 160, 160, 160, 160, 
		160, 160, 160, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
	};
	if ((YYLIMIT - YYCURSOR) < 5) YYFILL(5);
	yych = (YYCTYPE)*YYCURSOR;
	if (yybm[0+yych] & 16) {
		goto yy203;
	}
	if (yych <= '9') {
		if (yych <= '%') {
			if (yych <= '\r') {
				if (yych <= 0x08) goto yy201;
				if (yych <= '\n') goto yy206;
				if (yych >= '\r') goto yy208;
			} else {
				if (yych <= '"') {
					if (yych >= '"') goto yy209;
				} else {
					if (yych <= '#') goto yy211;
					if (yych >= '%') goto yy212;
				}
			}
		} else {
			if (yych <= '*') {
				if (yych <= '&') goto yy201;
				if (yych <= '\'') goto yy213;
				if (yych <= ')') goto yy215;
				goto yy217;
			} else {
				if (yych <= '-') {
					if (yych <= '+') goto yy215;
				} else {
					if (yych <= '.') goto yy218;
					if (yych <= '/') goto yy220;
				}
			}
		}
	} else {
		if (yych <= '[') {
			if (yych <= '=') {
				if (yych <= ':') goto yy221;
				if (yych <= ';') goto yy215;
				if (yych <= '<') goto yy222;
				goto yy224;
			} else {
				if (yych <= '?') {
					if (yych >= '?') goto yy215;
				} else {
					if (yych <= '@') goto yy211;
					if (yych <= 'Z') goto yy225;
					goto yy228;
				}
			}
		} else {
			if (yych <= 'q') {
				if (yych <= '^') {
					if (yych <= '\\') goto yy215;
				} else {
					if (yych != '`') goto yy225;
				}
			} else {
				if (yych <= 'z') {
					if (yych <= 'r') goto yy230;
					goto yy225;
				} else {
					if (yych <= '{') goto yy231;
					if (yych <= '|') goto yy215;
				}
			}
		}
	}
yy201:
	++YYCURSOR;
yy202:
#line 330 "../src/ast/lex.re"
	{
        fatal_lc(get_cline(), get_column(), "unexpected character: '%c'", *tok);
        goto scan;
    }
#line 1141 "src/ast/lex.cc"
yy203:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = (YYCTYPE)*YYCURSOR;
	if (yybm[0+yych] & 16) {
		goto yy203;
	}
#line 311 "../src/ast/lex.re"
	{ goto scan; }
#line 1151 "src/ast/lex.cc"
yy206:
	yyaccept = 0;
	yych = (YYCTYPE)*(YYMARKER = ++YYCURSOR);
	if (yych <= 0x1F) {
		if (yych == '\t') goto yy233;
	} else {
		if (yych <= ' ') goto yy233;
		if (yych == '#') goto yy236;
	}
yy207:
#line 318 "../src/ast/lex.re"
	{
        pos = cur;
        cline++;
        if (lexer_state == LEX_FLEX_NAME) {
            lexer_state = LEX_NORMAL;
            return TOKEN_FID_END;
        }
        else {
            goto scan;
        }
    }
#line 1174 "src/ast/lex.cc"
yy208:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == '\n') goto yy206;
	goto yy202;
yy209:
	++YYCURSOR;
#line 228 "../src/ast/lex.re"
	{ yylval.regexp = lex_str('"'); return TOKEN_REGEXP; }
#line 1183 "src/ast/lex.cc"
yy211:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych <= '^') {
		if (yych <= '@') goto yy202;
		if (yych <= 'Z') goto yy238;
		goto yy202;
	} else {
		if (yych == '`') goto yy202;
		if (yych <= 'z') goto yy238;
		goto yy202;
	}
yy212:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == '}') goto yy241;
	goto yy202;
yy213:
	++YYCURSOR;
#line 227 "../src/ast/lex.re"
	{ yylval.regexp = lex_str('\''); return TOKEN_REGEXP; }
#line 1203 "src/ast/lex.cc"
yy215:
	++YYCURSOR;
yy216:
#line 238 "../src/ast/lex.re"
	{ return *tok; }
#line 1209 "src/ast/lex.cc"
yy217:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == '/') goto yy241;
	goto yy216;
yy218:
	++YYCURSOR;
#line 306 "../src/ast/lex.re"
	{
        yylval.regexp = ast_dot(cline, get_column());
        return TOKEN_REGEXP;
    }
#line 1221 "src/ast/lex.cc"
yy220:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == '*') goto yy243;
	if (yych == '/') goto yy245;
	goto yy216;
yy221:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == '=') goto yy247;
	goto yy202;
yy222:
	++YYCURSOR;
#line 220 "../src/ast/lex.re"
	{ return lex_clist(); }
#line 1235 "src/ast/lex.cc"
yy224:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == '>') goto yy249;
	goto yy216;
yy225:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = (YYCTYPE)*YYCURSOR;
yy226:
	if (yybm[0+yych] & 32) {
		goto yy225;
	}
#line 283 "../src/ast/lex.re"
	{
        if (!globopts->FFlag || lex_namedef_context_re2c()) {
            yylval.str = new std::string (tok, tok_len());
            return TOKEN_ID;
        }
        else if (lex_namedef_context_flex()) {
            yylval.str = new std::string (tok, tok_len());
            lexer_state = LEX_FLEX_NAME;
            return TOKEN_FID;
        }
        else {
            std::vector<ASTChar> *str = new std::vector<ASTChar>;
            for (const char *s = tok; s < cur; ++s) {
                const uint32_t
                    chr = static_cast<uint8_t>(*s),
                    col = static_cast<uint32_t>(s - tok);
                str->push_back(ASTChar(chr, col));
            }
            yylval.regexp = ast_str(cline, get_column(), str, false);
            return TOKEN_REGEXP;
        }
    }
#line 1271 "src/ast/lex.cc"
yy228:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == '^') goto yy251;
#line 229 "../src/ast/lex.re"
	{ yylval.regexp = lex_cls(false); return TOKEN_REGEXP; }
#line 1277 "src/ast/lex.cc"
yy230:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'e') goto yy253;
	goto yy226;
yy231:
	yyaccept = 1;
	yych = (YYCTYPE)*(YYMARKER = ++YYCURSOR);
	if (yybm[0+yych] & 64) {
		goto yy256;
	}
	if (yych <= 'Z') {
		if (yych == ',') goto yy254;
		if (yych >= 'A') goto yy258;
	} else {
		if (yych <= '_') {
			if (yych >= '_') goto yy258;
		} else {
			if (yych <= '`') goto yy232;
			if (yych <= 'z') goto yy258;
		}
	}
yy232:
#line 215 "../src/ast/lex.re"
	{ lex_code_in_braces(); return TOKEN_CODE; }
#line 1302 "src/ast/lex.cc"
yy233:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = (YYCTYPE)*YYCURSOR;
	if (yych <= 0x1F) {
		if (yych == '\t') goto yy233;
	} else {
		if (yych <= ' ') goto yy233;
		if (yych == '#') goto yy236;
	}
yy235:
	YYCURSOR = YYMARKER;
	if (yyaccept <= 1) {
		if (yyaccept == 0) {
			goto yy207;
		} else {
			goto yy232;
		}
	} else {
		goto yy255;
	}
yy236:
	++YYCURSOR;
	if ((YYLIMIT - YYCURSOR) < 5) YYFILL(5);
	yych = (YYCTYPE)*YYCURSOR;
	if (yych <= 0x1F) {
		if (yych == '\t') goto yy236;
		goto yy235;
	} else {
		if (yych <= ' ') goto yy236;
		if (yych == 'l') goto yy260;
		goto yy235;
	}
yy238:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = (YYCTYPE)*YYCURSOR;
	if (yych <= 'Z') {
		if (yych <= '/') goto yy240;
		if (yych <= '9') goto yy238;
		if (yych >= 'A') goto yy238;
	} else {
		if (yych <= '_') {
			if (yych >= '_') goto yy238;
		} else {
			if (yych <= '`') goto yy240;
			if (yych <= 'z') goto yy238;
		}
	}
yy240:
#line 232 "../src/ast/lex.re"
	{
        const std::string *name = new std::string(tok + 1, tok_len() - 1);
        yylval.regexp = ast_tag(cline, get_column(), name, tok[0] == '#');
        return TOKEN_REGEXP;
    }
#line 1359 "src/ast/lex.cc"
yy241:
	++YYCURSOR;
#line 225 "../src/ast/lex.re"
	{ tok = cur; return 0; }
#line 1364 "src/ast/lex.cc"
yy243:
	++YYCURSOR;
#line 223 "../src/ast/lex.re"
	{ lex_c_comment(); goto scan; }
#line 1369 "src/ast/lex.cc"
yy245:
	++YYCURSOR;
#line 222 "../src/ast/lex.re"
	{ lex_cpp_comment(); goto scan; }
#line 1374 "src/ast/lex.cc"
yy247:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == '>') goto yy261;
#line 216 "../src/ast/lex.re"
	{ lex_code_indented(); return TOKEN_CODE; }
#line 1380 "src/ast/lex.cc"
yy249:
	++YYCURSOR;
#line 218 "../src/ast/lex.re"
	{ lex_cgoto(); return TOKEN_CNEXT; }
#line 1385 "src/ast/lex.cc"
yy251:
	++YYCURSOR;
#line 230 "../src/ast/lex.re"
	{ yylval.regexp = lex_cls(true);  return TOKEN_REGEXP; }
#line 1390 "src/ast/lex.cc"
yy253:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == '2') goto yy263;
	goto yy226;
yy254:
	++YYCURSOR;
yy255:
#line 267 "../src/ast/lex.re"
	{
        fatal_lc(get_cline(), get_column(),
            "illegal closure form, use '{n}', '{n,}', '{n,m}' where n and m are numbers");
    }
#line 1403 "src/ast/lex.cc"
yy256:
	++YYCURSOR;
	if ((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
	yych = (YYCTYPE)*YYCURSOR;
	if (yybm[0+yych] & 64) {
		goto yy256;
	}
	if (yych == ',') goto yy264;
	if (yych == '}') goto yy265;
	goto yy235;
yy258:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = (YYCTYPE)*YYCURSOR;
	if (yych <= '^') {
		if (yych <= '9') {
			if (yych <= '/') goto yy235;
			goto yy258;
		} else {
			if (yych <= '@') goto yy235;
			if (yych <= 'Z') goto yy258;
			goto yy235;
		}
	} else {
		if (yych <= 'z') {
			if (yych == '`') goto yy235;
			goto yy258;
		} else {
			if (yych == '}') goto yy267;
			goto yy235;
		}
	}
yy260:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'i') goto yy269;
	goto yy235;
yy261:
	++YYCURSOR;
#line 219 "../src/ast/lex.re"
	{ lex_cgoto(); return TOKEN_CJUMP; }
#line 1444 "src/ast/lex.cc"
yy263:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'c') goto yy270;
	goto yy226;
yy264:
	yyaccept = 2;
	yych = (YYCTYPE)*(YYMARKER = ++YYCURSOR);
	if (yych <= '/') goto yy255;
	if (yych <= '9') goto yy271;
	if (yych == '}') goto yy273;
	goto yy255;
yy265:
	++YYCURSOR;
#line 240 "../src/ast/lex.re"
	{
        if (!s_to_u32_unsafe (tok + 1, cur - 1, yylval.bounds.min)) {
            fatal_lc(get_cline(), get_column(), "repetition count overflow");
        }
        yylval.bounds.max = yylval.bounds.min;
        return TOKEN_CLOSESIZE;
    }
#line 1466 "src/ast/lex.cc"
yy267:
	++YYCURSOR;
#line 272 "../src/ast/lex.re"
	{
        if (!globopts->FFlag) {
            fatal_lc(get_cline(), get_column(),
                "curly braces for names only allowed with -F switch");
        }
        yylval.str = new std::string (tok + 1, tok_len () - 2); // -2 to omit braces
        return TOKEN_ID;
    }
#line 1478 "src/ast/lex.cc"
yy269:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'n') goto yy275;
	goto yy235;
yy270:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == ':') goto yy276;
	goto yy226;
yy271:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = (YYCTYPE)*YYCURSOR;
	if (yych <= '/') goto yy235;
	if (yych <= '9') goto yy271;
	if (yych == '}') goto yy278;
	goto yy235;
yy273:
	++YYCURSOR;
#line 259 "../src/ast/lex.re"
	{
        if (!s_to_u32_unsafe (tok + 1, cur - 2, yylval.bounds.min)) {
            fatal_lc(get_cline(), get_column(), "repetition lower bound overflow");
        }
        yylval.bounds.max = std::numeric_limits<uint32_t>::max();
        return TOKEN_CLOSESIZE;
    }
#line 1505 "src/ast/lex.cc"
yy275:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == 'e') goto yy280;
	goto yy235;
yy276:
	++YYCURSOR;
#line 281 "../src/ast/lex.re"
	{ return TOKEN_CONF; }
#line 1514 "src/ast/lex.cc"
yy278:
	++YYCURSOR;
#line 248 "../src/ast/lex.re"
	{
        const char * p = strchr (tok, ',');
        if (!s_to_u32_unsafe (tok + 1, p, yylval.bounds.min)) {
            fatal_lc(get_cline(), get_column(), "repetition lower bound overflow");
        }
        if (!s_to_u32_unsafe (p + 1, cur - 1, yylval.bounds.max)) {
            fatal_lc(get_cline(), get_column(), "repetition upper bound overflow");
        }
        return TOKEN_CLOSESIZE;
    }
#line 1528 "src/ast/lex.cc"
yy280:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych <= '0') goto yy282;
	if (yych <= '9') goto yy235;
	goto yy282;
yy281:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = (YYCTYPE)*YYCURSOR;
yy282:
	if (yych <= 0x1F) {
		if (yych == '\t') goto yy281;
		goto yy235;
	} else {
		if (yych <= ' ') goto yy281;
		if (yych <= '0') goto yy235;
		if (yych >= ':') goto yy235;
		YYCTXMARKER = YYCURSOR;
	}
yy283:
	++YYCURSOR;
	if ((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
	yych = (YYCTYPE)*YYCURSOR;
	if (yych <= '\r') {
		if (yych <= '\t') {
			if (yych <= 0x08) goto yy235;
		} else {
			if (yych <= '\n') goto yy287;
			if (yych <= '\f') goto yy235;
			goto yy289;
		}
	} else {
		if (yych <= ' ') {
			if (yych <= 0x1F) goto yy235;
		} else {
			if (yych <= '/') goto yy235;
			if (yych <= '9') goto yy283;
			goto yy235;
		}
	}
yy285:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = (YYCTYPE)*YYCURSOR;
	if (yych <= 0x1F) {
		if (yych == '\t') goto yy285;
		goto yy235;
	} else {
		if (yych <= ' ') goto yy285;
		if (yych == '"') goto yy290;
		goto yy235;
	}
yy287:
	++YYCURSOR;
	YYCURSOR = YYCTXMARKER;
#line 313 "../src/ast/lex.re"
	{
        set_sourceline ();
        return TOKEN_LINE_INFO;
    }
#line 1589 "src/ast/lex.cc"
yy289:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == '\n') goto yy287;
	goto yy235;
yy290:
	++YYCURSOR;
	if ((YYLIMIT - YYCURSOR) < 3) YYFILL(3);
	yych = (YYCTYPE)*YYCURSOR;
	if (yybm[0+yych] & 128) {
		goto yy290;
	}
	if (yych <= '\n') goto yy235;
	if (yych >= '#') goto yy293;
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == '\n') goto yy287;
	if (yych == '\r') goto yy289;
	goto yy235;
yy293:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = (YYCTYPE)*YYCURSOR;
	if (yych <= 0x00) goto yy235;
	if (yych == '\n') goto yy235;
	goto yy290;
}
#line 334 "../src/ast/lex.re"

}

bool Scanner::lex_namedef_context_re2c()
{

#line 1622 "src/ast/lex.cc"
{
	YYCTYPE yych;
	static const unsigned char yybm[] = {
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0, 128,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		128,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
	};
	if ((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
	yych = (YYCTYPE)*(YYMARKER = YYCURSOR);
	if (yych <= 0x1F) {
		if (yych == '\t') {
			YYCTXMARKER = YYCURSOR;
			goto yy297;
		}
	} else {
		if (yych <= ' ') {
			YYCTXMARKER = YYCURSOR;
			goto yy297;
		}
		if (yych == '=') {
			YYCTXMARKER = YYCURSOR;
			goto yy300;
		}
	}
yy296:
#line 341 "../src/ast/lex.re"
	{ return false; }
#line 1679 "src/ast/lex.cc"
yy297:
	++YYCURSOR;
	if ((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
	yych = (YYCTYPE)*YYCURSOR;
	if (yybm[0+yych] & 128) {
		goto yy297;
	}
	if (yych == '=') goto yy300;
yy299:
	YYCURSOR = YYMARKER;
	goto yy296;
yy300:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == '>') goto yy299;
	++YYCURSOR;
	YYCURSOR = YYCTXMARKER;
#line 340 "../src/ast/lex.re"
	{ return true; }
#line 1698 "src/ast/lex.cc"
}
#line 342 "../src/ast/lex.re"

}

bool Scanner::lex_namedef_context_flex()
{

#line 1707 "src/ast/lex.cc"
{
	YYCTYPE yych;
	static const unsigned char yybm[] = {
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0, 128,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		128,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
	};
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = (YYCTYPE)*YYCURSOR;
	if (yych == '\t') {
		YYCTXMARKER = YYCURSOR;
		goto yy306;
	}
	if (yych == ' ') {
		YYCTXMARKER = YYCURSOR;
		goto yy306;
	}
#line 350 "../src/ast/lex.re"
	{ return false; }
#line 1756 "src/ast/lex.cc"
yy306:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = (YYCTYPE)*YYCURSOR;
	if (yybm[0+yych] & 128) {
		goto yy306;
	}
	if (yych <= '<') {
		if (yych == ':') goto yy309;
	} else {
		if (yych <= '=') goto yy309;
		if (yych == '{') goto yy309;
	}
	YYCURSOR = YYCTXMARKER;
#line 349 "../src/ast/lex.re"
	{ return true; }
#line 1773 "src/ast/lex.cc"
yy309:
	++YYCURSOR;
	YYCURSOR = YYCTXMARKER;
#line 348 "../src/ast/lex.re"
	{ return false; }
#line 1779 "src/ast/lex.cc"
}
#line 351 "../src/ast/lex.re"

}

int Scanner::lex_clist()
{
    int kind = TOKEN_CLIST;
    CondList *cl = new CondList;

#line 1790 "src/ast/lex.cc"
{
	YYCTYPE yych;
	static const unsigned char yybm[] = {
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0, 128,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		128,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
	};
	goto yy311;
yy312:
	++YYCURSOR;
yy311:
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = (YYCTYPE)*YYCURSOR;
	if (yybm[0+yych] & 128) {
		goto yy312;
	}
	if (yych <= 0x1F) goto yy314;
	if (yych <= '!') goto yy315;
	if (yych == '>') goto yy318;
yy314:
#line 361 "../src/ast/lex.re"
	{ goto cond; }
#line 1842 "src/ast/lex.cc"
yy315:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = (YYCTYPE)*YYCURSOR;
	if (yych == '\t') goto yy315;
	if (yych == ' ') goto yy315;
#line 359 "../src/ast/lex.re"
	{ kind = TOKEN_CSETUP; goto cond; }
#line 1851 "src/ast/lex.cc"
yy318:
	++YYCURSOR;
#line 360 "../src/ast/lex.re"
	{ kind = TOKEN_CZERO; goto end; }
#line 1856 "src/ast/lex.cc"
}
#line 362 "../src/ast/lex.re"

cond:
    tok = cur;

#line 1863 "src/ast/lex.cc"
{
	YYCTYPE yych;
	static const unsigned char yybm[] = {
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128,   0,   0,   0,   0,   0,   0, 
		  0, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128,   0,   0,   0,   0, 128, 
		  0, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
	};
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = (YYCTYPE)*YYCURSOR;
	if (yych <= 'Z') {
		if (yych == '*') goto yy324;
		if (yych >= 'A') goto yy326;
	} else {
		if (yych <= '_') {
			if (yych >= '_') goto yy326;
		} else {
			if (yych <= '`') goto yy322;
			if (yych <= 'z') goto yy326;
		}
	}
yy322:
	++YYCURSOR;
#line 368 "../src/ast/lex.re"
	{ goto error; }
#line 1917 "src/ast/lex.cc"
yy324:
	++YYCURSOR;
#line 367 "../src/ast/lex.re"
	{ if (!cl->empty()) goto error; cl->insert("*"); goto next; }
#line 1922 "src/ast/lex.cc"
yy326:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = (YYCTYPE)*YYCURSOR;
	if (yybm[0+yych] & 128) {
		goto yy326;
	}
#line 366 "../src/ast/lex.re"
	{ cl->insert(std::string(tok, tok_len())); goto next; }
#line 1932 "src/ast/lex.cc"
}
#line 369 "../src/ast/lex.re"

next:

#line 1938 "src/ast/lex.cc"
{
	YYCTYPE yych;
	static const unsigned char yybm[] = {
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0, 128,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		128,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
	};
	if ((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
	yych = (YYCTYPE)*YYCURSOR;
	if (yych <= ' ') {
		if (yych == '\t') goto yy333;
		if (yych >= ' ') goto yy333;
	} else {
		if (yych <= ',') {
			if (yych >= ',') goto yy334;
		} else {
			if (yych == '>') goto yy337;
		}
	}
	++YYCURSOR;
yy332:
#line 374 "../src/ast/lex.re"
	{ goto error; }
#line 1991 "src/ast/lex.cc"
yy333:
	yych = (YYCTYPE)*(YYMARKER = ++YYCURSOR);
	if (yych <= ' ') {
		if (yych == '\t') goto yy339;
		if (yych <= 0x1F) goto yy332;
		goto yy339;
	} else {
		if (yych <= ',') {
			if (yych <= '+') goto yy332;
		} else {
			if (yych == '>') goto yy337;
			goto yy332;
		}
	}
yy334:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = (YYCTYPE)*YYCURSOR;
	if (yybm[0+yych] & 128) {
		goto yy334;
	}
#line 372 "../src/ast/lex.re"
	{ goto cond; }
#line 2015 "src/ast/lex.cc"
yy337:
	++YYCURSOR;
#line 373 "../src/ast/lex.re"
	{ goto end; }
#line 2020 "src/ast/lex.cc"
yy339:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = (YYCTYPE)*YYCURSOR;
	if (yych <= ' ') {
		if (yych == '\t') goto yy339;
		if (yych >= ' ') goto yy339;
	} else {
		if (yych <= ',') {
			if (yych >= ',') goto yy334;
		} else {
			if (yych == '>') goto yy337;
		}
	}
	YYCURSOR = YYMARKER;
	goto yy332;
}
#line 375 "../src/ast/lex.re"

end:
    yylval.clist = cl;
    return kind;
error:
    delete cl;
    fatal_l(get_cline(), "syntax error in condition list");
}

void Scanner::lex_cgoto()
{

#line 2051 "src/ast/lex.cc"
{
	YYCTYPE yych;
	static const unsigned char yybm[] = {
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0, 128,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		128,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
	};
	goto yy342;
yy343:
	++YYCURSOR;
yy342:
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = (YYCTYPE)*YYCURSOR;
	if (yybm[0+yych] & 128) {
		goto yy343;
	}
#line 387 "../src/ast/lex.re"
	{ goto name; }
#line 2099 "src/ast/lex.cc"
}
#line 388 "../src/ast/lex.re"

name:
    tok = cur;

#line 2106 "src/ast/lex.cc"
{
	YYCTYPE yych;
	static const unsigned char yybm[] = {
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128,   0,   0,   0,   0,   0,   0, 
		  0, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128,   0,   0,   0,   0, 128, 
		  0, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
	};
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = (YYCTYPE)*YYCURSOR;
	if (yych <= '^') {
		if (yych <= '@') goto yy348;
		if (yych <= 'Z') goto yy350;
	} else {
		if (yych == '`') goto yy348;
		if (yych <= 'z') goto yy350;
	}
yy348:
	++YYCURSOR;
#line 393 "../src/ast/lex.re"
	{ fatal_l(get_cline(), "syntax error in condition goto"); }
#line 2156 "src/ast/lex.cc"
yy350:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = (YYCTYPE)*YYCURSOR;
	if (yybm[0+yych] & 128) {
		goto yy350;
	}
#line 392 "../src/ast/lex.re"
	{ yylval.str = new std::string (tok, tok_len ()); return; }
#line 2166 "src/ast/lex.cc"
}
#line 394 "../src/ast/lex.re"

}

void Scanner::lex_code_indented()
{
    const uint32_t line = cline;
    tok = cur;
code:

#line 2178 "src/ast/lex.cc"
{
	YYCTYPE yych;
	if ((YYLIMIT - YYCURSOR) < 3) YYFILL(3);
	yych = (YYCTYPE)*YYCURSOR;
	if (yych <= '&') {
		if (yych <= '\f') {
			if (yych <= 0x00) goto yy355;
			if (yych == '\n') goto yy359;
			goto yy357;
		} else {
			if (yych <= '\r') goto yy361;
			if (yych == '"') goto yy362;
			goto yy357;
		}
	} else {
		if (yych <= 'z') {
			if (yych <= '\'') goto yy362;
			if (yych == '/') goto yy364;
			goto yy357;
		} else {
			if (yych == '|') goto yy357;
			if (yych <= '}') goto yy365;
			goto yy357;
		}
	}
yy355:
	++YYCURSOR;
#line 411 "../src/ast/lex.re"
	{ fail_if_eof(); goto code; }
#line 2208 "src/ast/lex.cc"
yy357:
	++YYCURSOR;
yy358:
#line 416 "../src/ast/lex.re"
	{ goto code; }
#line 2214 "src/ast/lex.cc"
yy359:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych <= '\f') {
		if (yych <= 0x08) goto yy360;
		if (yych <= '\n') goto yy367;
	} else {
		if (yych <= '\r') goto yy367;
		if (yych == ' ') goto yy367;
	}
yy360:
#line 404 "../src/ast/lex.re"
	{
        while (isspace(tok[0])) ++tok;
        while (cur > tok && isspace(cur[-1])) --cur;
        yylval.code = new Code(get_fname (), line, tok, tok_len ());
        return;
    }
#line 2232 "src/ast/lex.cc"
yy361:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == '\n') goto yy359;
	goto yy358;
yy362:
	++YYCURSOR;
#line 415 "../src/ast/lex.re"
	{ lex_string(cur[-1]); goto code; }
#line 2241 "src/ast/lex.cc"
yy364:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == '*') goto yy369;
	if (yych == '/') goto yy371;
	goto yy358;
yy365:
	++YYCURSOR;
#line 412 "../src/ast/lex.re"
	{ fatal_l(get_cline(), "Curly braces are not allowed after ':='"); }
#line 2251 "src/ast/lex.cc"
yy367:
	++YYCURSOR;
	YYCURSOR -= 1;
#line 403 "../src/ast/lex.re"
	{ goto code; }
#line 2257 "src/ast/lex.cc"
yy369:
	++YYCURSOR;
#line 413 "../src/ast/lex.re"
	{ lex_c_comment(); goto code; }
#line 2262 "src/ast/lex.cc"
yy371:
	++YYCURSOR;
#line 414 "../src/ast/lex.re"
	{ lex_cpp_comment(); goto code; }
#line 2267 "src/ast/lex.cc"
}
#line 417 "../src/ast/lex.re"

}

void Scanner::lex_code_in_braces()
{
    const uint32_t line = cline;
    uint32_t depth = 1;
code:

#line 2279 "src/ast/lex.cc"
{
	YYCTYPE yych;
	static const unsigned char yybm[] = {
		  0, 128, 128, 128, 128, 128, 128, 128, 
		128, 160,   0, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		160, 128,   0, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128,   0, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
	};
	if ((YYLIMIT - YYCURSOR) < 3) YYFILL(3);
	yych = (YYCTYPE)*YYCURSOR;
	if (yych <= '&') {
		if (yych <= '\f') {
			if (yych <= 0x00) goto yy375;
			if (yych == '\n') goto yy379;
			goto yy377;
		} else {
			if (yych <= '\r') goto yy381;
			if (yych == '"') goto yy382;
			goto yy377;
		}
	} else {
		if (yych <= 'z') {
			if (yych <= '\'') goto yy382;
			if (yych == '/') goto yy384;
			goto yy377;
		} else {
			if (yych <= '{') goto yy385;
			if (yych == '}') goto yy387;
			goto yy377;
		}
	}
yy375:
	++YYCURSOR;
#line 437 "../src/ast/lex.re"
	{ fail_if_eof(); goto code; }
#line 2343 "src/ast/lex.cc"
yy377:
	++YYCURSOR;
yy378:
#line 441 "../src/ast/lex.re"
	{ goto code; }
#line 2349 "src/ast/lex.cc"
yy379:
	yych = (YYCTYPE)*(YYMARKER = ++YYCURSOR);
	if (yybm[0+yych] & 32) {
		goto yy389;
	}
	if (yych == '#') goto yy392;
yy380:
#line 436 "../src/ast/lex.re"
	{ pos = cur; cline++; goto code; }
#line 2359 "src/ast/lex.cc"
yy381:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == '\n') goto yy379;
	goto yy378;
yy382:
	++YYCURSOR;
#line 440 "../src/ast/lex.re"
	{ lex_string(cur[-1]); goto code; }
#line 2368 "src/ast/lex.cc"
yy384:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == '*') goto yy394;
	if (yych == '/') goto yy396;
	goto yy378;
yy385:
	++YYCURSOR;
#line 434 "../src/ast/lex.re"
	{ ++depth; goto code; }
#line 2378 "src/ast/lex.cc"
yy387:
	++YYCURSOR;
#line 426 "../src/ast/lex.re"
	{
        if (--depth == 0) {
            yylval.code = new Code(get_fname (), line, tok, tok_len ());
            return;
        }
        goto code;
    }
#line 2389 "src/ast/lex.cc"
yy389:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = (YYCTYPE)*YYCURSOR;
	if (yybm[0+yych] & 32) {
		goto yy389;
	}
	if (yych == '#') goto yy392;
yy391:
	YYCURSOR = YYMARKER;
	goto yy380;
yy392:
	++YYCURSOR;
	if ((YYLIMIT - YYCURSOR) < 5) YYFILL(5);
	yych = (YYCTYPE)*YYCURSOR;
	if (yych <= 0x1F) {
		if (yych == '\t') goto yy392;
		goto yy391;
	} else {
		if (yych <= ' ') goto yy392;
		if (yych == 'l') goto yy398;
		goto yy391;
	}
yy394:
	++YYCURSOR;
#line 438 "../src/ast/lex.re"
	{ lex_c_comment(); goto code; }
#line 2417 "src/ast/lex.cc"
yy396:
	++YYCURSOR;
#line 439 "../src/ast/lex.re"
	{ lex_cpp_comment(); goto code; }
#line 2422 "src/ast/lex.cc"
yy398:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych != 'i') goto yy391;
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych != 'n') goto yy391;
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych != 'e') goto yy391;
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych <= '0') goto yy403;
	if (yych <= '9') goto yy391;
	goto yy403;
yy402:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = (YYCTYPE)*YYCURSOR;
yy403:
	if (yych <= 0x1F) {
		if (yych == '\t') goto yy402;
		goto yy391;
	} else {
		if (yych <= ' ') goto yy402;
		if (yych <= '0') goto yy391;
		if (yych >= ':') goto yy391;
		YYCTXMARKER = YYCURSOR;
	}
yy404:
	++YYCURSOR;
	if ((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
	yych = (YYCTYPE)*YYCURSOR;
	if (yybm[0+yych] & 64) {
		goto yy404;
	}
	if (yych <= '\f') {
		if (yych <= 0x08) goto yy391;
		if (yych <= '\t') goto yy406;
		if (yych <= '\n') goto yy408;
		goto yy391;
	} else {
		if (yych <= '\r') goto yy410;
		if (yych != ' ') goto yy391;
	}
yy406:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = (YYCTYPE)*YYCURSOR;
	if (yych <= 0x1F) {
		if (yych == '\t') goto yy406;
		goto yy391;
	} else {
		if (yych <= ' ') goto yy406;
		if (yych == '"') goto yy411;
		goto yy391;
	}
yy408:
	++YYCURSOR;
	YYCURSOR = YYCTXMARKER;
#line 435 "../src/ast/lex.re"
	{ set_sourceline (); goto code; }
#line 2481 "src/ast/lex.cc"
yy410:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == '\n') goto yy408;
	goto yy391;
yy411:
	++YYCURSOR;
	if ((YYLIMIT - YYCURSOR) < 3) YYFILL(3);
	yych = (YYCTYPE)*YYCURSOR;
	if (yybm[0+yych] & 128) {
		goto yy411;
	}
	if (yych <= '\n') goto yy391;
	if (yych >= '#') goto yy414;
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == '\n') goto yy408;
	if (yych == '\r') goto yy410;
	goto yy391;
yy414:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = (YYCTYPE)*YYCURSOR;
	if (yych <= 0x00) goto yy391;
	if (yych == '\n') goto yy391;
	goto yy411;
}
#line 442 "../src/ast/lex.re"

}

void Scanner::lex_string(char delim)
{
loop:

#line 2515 "src/ast/lex.cc"
{
	YYCTYPE yych;
	if ((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
	yych = (YYCTYPE)*YYCURSOR;
	if (yych <= '!') {
		if (yych <= '\n') {
			if (yych <= 0x00) goto yy417;
			if (yych <= '\t') goto yy419;
			goto yy421;
		} else {
			if (yych == '\r') goto yy423;
			goto yy419;
		}
	} else {
		if (yych <= '\'') {
			if (yych <= '"') goto yy424;
			if (yych <= '&') goto yy419;
			goto yy424;
		} else {
			if (yych == '\\') goto yy426;
			goto yy419;
		}
	}
yy417:
	++YYCURSOR;
#line 452 "../src/ast/lex.re"
	{ fail_if_eof(); goto loop; }
#line 2543 "src/ast/lex.cc"
yy419:
	++YYCURSOR;
yy420:
#line 453 "../src/ast/lex.re"
	{ goto loop; }
#line 2549 "src/ast/lex.cc"
yy421:
	++YYCURSOR;
#line 451 "../src/ast/lex.re"
	{ pos = cur; ++cline; goto loop; }
#line 2554 "src/ast/lex.cc"
yy423:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == '\n') goto yy421;
	goto yy420;
yy424:
	++YYCURSOR;
#line 449 "../src/ast/lex.re"
	{ if (cur[-1] == delim) return; else goto loop; }
#line 2563 "src/ast/lex.cc"
yy426:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych <= '&') {
		if (yych != '"') goto yy420;
	} else {
		if (yych <= '\'') goto yy427;
		if (yych != '\\') goto yy420;
	}
yy427:
	++YYCURSOR;
#line 450 "../src/ast/lex.re"
	{ goto loop; }
#line 2576 "src/ast/lex.cc"
}
#line 454 "../src/ast/lex.re"

}

void Scanner::lex_c_comment()
{
loop:

#line 2586 "src/ast/lex.cc"
{
	YYCTYPE yych;
	if ((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
	yych = (YYCTYPE)*YYCURSOR;
	if (yych <= '\f') {
		if (yych <= 0x00) goto yy431;
		if (yych == '\n') goto yy435;
		goto yy433;
	} else {
		if (yych <= '\r') goto yy437;
		if (yych == '*') goto yy438;
		goto yy433;
	}
yy431:
	++YYCURSOR;
#line 463 "../src/ast/lex.re"
	{ fail_if_eof(); goto loop; }
#line 2604 "src/ast/lex.cc"
yy433:
	++YYCURSOR;
yy434:
#line 464 "../src/ast/lex.re"
	{ goto loop; }
#line 2610 "src/ast/lex.cc"
yy435:
	++YYCURSOR;
#line 462 "../src/ast/lex.re"
	{ pos = cur; ++cline; goto loop; }
#line 2615 "src/ast/lex.cc"
yy437:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == '\n') goto yy435;
	goto yy434;
yy438:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych != '/') goto yy434;
	++YYCURSOR;
#line 461 "../src/ast/lex.re"
	{ return; }
#line 2626 "src/ast/lex.cc"
}
#line 465 "../src/ast/lex.re"

}

void Scanner::lex_cpp_comment()
{
loop:

#line 2636 "src/ast/lex.cc"
{
	YYCTYPE yych;
	if ((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
	yych = (YYCTYPE)*YYCURSOR;
	if (yych <= '\n') {
		if (yych <= 0x00) goto yy443;
		if (yych <= '\t') goto yy445;
		goto yy447;
	} else {
		if (yych == '\r') goto yy449;
		goto yy445;
	}
yy443:
	++YYCURSOR;
#line 473 "../src/ast/lex.re"
	{ fail_if_eof(); goto loop; }
#line 2653 "src/ast/lex.cc"
yy445:
	++YYCURSOR;
yy446:
#line 474 "../src/ast/lex.re"
	{ goto loop; }
#line 2659 "src/ast/lex.cc"
yy447:
	++YYCURSOR;
#line 472 "../src/ast/lex.re"
	{ pos = cur; ++cline; return; }
#line 2664 "src/ast/lex.cc"
yy449:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == '\n') goto yy447;
	goto yy446;
}
#line 475 "../src/ast/lex.re"

}

const AST *Scanner::lex_cls(bool neg)
{
    std::vector<ASTRange> *cls = new std::vector<ASTRange>;
    uint32_t u, l, c, c0 = get_column();
fst:
    tok = cur;
    c = get_column();
    
#line 2682 "src/ast/lex.cc"
{
	YYCTYPE yych;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = (YYCTYPE)*YYCURSOR;
	if (yych == ']') goto yy453;
#line 487 "../src/ast/lex.re"
	{ l = lex_cls_chr(); goto snd; }
#line 2690 "src/ast/lex.cc"
yy453:
	++YYCURSOR;
#line 486 "../src/ast/lex.re"
	{ return ast_cls(cline, c0, cls, neg); }
#line 2695 "src/ast/lex.cc"
}
#line 488 "../src/ast/lex.re"

snd:
    
#line 2701 "src/ast/lex.cc"
{
	YYCTYPE yych;
	if ((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
	yych = (YYCTYPE)*(YYMARKER = YYCURSOR);
	if (yych == '-') goto yy458;
yy457:
#line 491 "../src/ast/lex.re"
	{ u = l; goto add; }
#line 2710 "src/ast/lex.cc"
yy458:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych != ']') goto yy460;
	YYCURSOR = YYMARKER;
	goto yy457;
yy460:
	++YYCURSOR;
	YYCURSOR -= 1;
#line 492 "../src/ast/lex.re"
	{
            u = lex_cls_chr();
            if (l > u) {
                warn.swapped_range(cline, l, u);
                std::swap(l, u);
            }
            goto add;
        }
#line 2728 "src/ast/lex.cc"
}
#line 500 "../src/ast/lex.re"

add:
    cls->push_back(ASTRange(l, u, c));
    goto fst;
}

uint32_t Scanner::lex_cls_chr()
{
    tok = cur;
    const uint32_t l = get_cline(), c = get_column();
    
#line 2742 "src/ast/lex.cc"
{
	YYCTYPE yych;
	unsigned int yyaccept = 0;
	if ((YYLIMIT - YYCURSOR) < 10) YYFILL(10);
	yych = (YYCTYPE)*YYCURSOR;
	if (yych <= '\f') {
		if (yych <= 0x00) goto yy464;
		if (yych == '\n') goto yy468;
		goto yy466;
	} else {
		if (yych <= '\r') goto yy470;
		if (yych == '\\') goto yy471;
		goto yy466;
	}
yy464:
	++YYCURSOR;
#line 512 "../src/ast/lex.re"
	{ fail_if_eof(); return 0; }
#line 2761 "src/ast/lex.cc"
yy466:
	++YYCURSOR;
yy467:
#line 518 "../src/ast/lex.re"
	{ return static_cast<uint8_t>(tok[0]); }
#line 2767 "src/ast/lex.cc"
yy468:
	++YYCURSOR;
#line 513 "../src/ast/lex.re"
	{ fatal_lc(l, c, "newline in character class"); }
#line 2772 "src/ast/lex.cc"
yy470:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == '\n') goto yy468;
	goto yy467;
yy471:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych <= '\\') {
		if (yych <= '/') {
			if (yych <= '\f') {
				if (yych <= 0x00) goto yy472;
				if (yych == '\n') goto yy468;
				goto yy473;
			} else {
				if (yych <= '\r') goto yy475;
				if (yych == '-') goto yy476;
				goto yy473;
			}
		} else {
			if (yych <= 'U') {
				if (yych <= '3') goto yy478;
				if (yych <= '7') goto yy480;
				if (yych <= 'T') goto yy473;
				goto yy481;
			} else {
				if (yych == 'X') goto yy483;
				if (yych <= '[') goto yy473;
				goto yy484;
			}
		}
	} else {
		if (yych <= 'n') {
			if (yych <= 'b') {
				if (yych <= ']') goto yy486;
				if (yych <= '`') goto yy473;
				if (yych <= 'a') goto yy488;
				goto yy490;
			} else {
				if (yych == 'f') goto yy492;
				if (yych <= 'm') goto yy473;
				goto yy494;
			}
		} else {
			if (yych <= 't') {
				if (yych == 'r') goto yy496;
				if (yych <= 's') goto yy473;
				goto yy498;
			} else {
				if (yych <= 'v') {
					if (yych <= 'u') goto yy483;
					goto yy500;
				} else {
					if (yych == 'x') goto yy502;
					goto yy473;
				}
			}
		}
	}
yy472:
#line 516 "../src/ast/lex.re"
	{ fatal_lc(l, c, "syntax error in escape sequence"); }
#line 2833 "src/ast/lex.cc"
yy473:
	++YYCURSOR;
yy474:
#line 531 "../src/ast/lex.re"
	{
            warn.useless_escape(cline, get_column(), tok[1]);
            return static_cast<uint8_t>(tok[1]);
        }
#line 2842 "src/ast/lex.cc"
yy475:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == '\n') goto yy468;
	goto yy474;
yy476:
	++YYCURSOR;
#line 529 "../src/ast/lex.re"
	{ return static_cast<uint8_t>('-'); }
#line 2851 "src/ast/lex.cc"
yy478:
	yyaccept = 0;
	yych = (YYCTYPE)*(YYMARKER = ++YYCURSOR);
	if (yych <= '/') goto yy479;
	if (yych <= '7') goto yy503;
yy479:
#line 515 "../src/ast/lex.re"
	{ fatal_lc(l, c, "syntax error in octal escape sequence"); }
#line 2860 "src/ast/lex.cc"
yy480:
	++YYCURSOR;
	goto yy479;
yy481:
	yyaccept = 1;
	yych = (YYCTYPE)*(YYMARKER = ++YYCURSOR);
	if (yych <= '@') {
		if (yych <= '/') goto yy482;
		if (yych <= '9') goto yy505;
	} else {
		if (yych <= 'F') goto yy505;
		if (yych <= '`') goto yy482;
		if (yych <= 'f') goto yy505;
	}
yy482:
#line 514 "../src/ast/lex.re"
	{ fatal_lc(l, c, "syntax error in hexadecimal escape sequence"); }
#line 2878 "src/ast/lex.cc"
yy483:
	yyaccept = 1;
	yych = (YYCTYPE)*(YYMARKER = ++YYCURSOR);
	if (yych <= '@') {
		if (yych <= '/') goto yy482;
		if (yych <= '9') goto yy506;
		goto yy482;
	} else {
		if (yych <= 'F') goto yy506;
		if (yych <= '`') goto yy482;
		if (yych <= 'f') goto yy506;
		goto yy482;
	}
yy484:
	++YYCURSOR;
#line 528 "../src/ast/lex.re"
	{ return static_cast<uint8_t>('\\'); }
#line 2896 "src/ast/lex.cc"
yy486:
	++YYCURSOR;
#line 530 "../src/ast/lex.re"
	{ return static_cast<uint8_t>(']'); }
#line 2901 "src/ast/lex.cc"
yy488:
	++YYCURSOR;
#line 521 "../src/ast/lex.re"
	{ return static_cast<uint8_t>('\a'); }
#line 2906 "src/ast/lex.cc"
yy490:
	++YYCURSOR;
#line 522 "../src/ast/lex.re"
	{ return static_cast<uint8_t>('\b'); }
#line 2911 "src/ast/lex.cc"
yy492:
	++YYCURSOR;
#line 523 "../src/ast/lex.re"
	{ return static_cast<uint8_t>('\f'); }
#line 2916 "src/ast/lex.cc"
yy494:
	++YYCURSOR;
#line 524 "../src/ast/lex.re"
	{ return static_cast<uint8_t>('\n'); }
#line 2921 "src/ast/lex.cc"
yy496:
	++YYCURSOR;
#line 525 "../src/ast/lex.re"
	{ return static_cast<uint8_t>('\r'); }
#line 2926 "src/ast/lex.cc"
yy498:
	++YYCURSOR;
#line 526 "../src/ast/lex.re"
	{ return static_cast<uint8_t>('\t'); }
#line 2931 "src/ast/lex.cc"
yy500:
	++YYCURSOR;
#line 527 "../src/ast/lex.re"
	{ return static_cast<uint8_t>('\v'); }
#line 2936 "src/ast/lex.cc"
yy502:
	yyaccept = 1;
	yych = (YYCTYPE)*(YYMARKER = ++YYCURSOR);
	if (yych <= '@') {
		if (yych <= '/') goto yy482;
		if (yych <= '9') goto yy507;
		goto yy482;
	} else {
		if (yych <= 'F') goto yy507;
		if (yych <= '`') goto yy482;
		if (yych <= 'f') goto yy507;
		goto yy482;
	}
yy503:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych <= '/') goto yy504;
	if (yych <= '7') goto yy508;
yy504:
	YYCURSOR = YYMARKER;
	if (yyaccept == 0) {
		goto yy479;
	} else {
		goto yy482;
	}
yy505:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych <= '@') {
		if (yych <= '/') goto yy504;
		if (yych <= '9') goto yy510;
		goto yy504;
	} else {
		if (yych <= 'F') goto yy510;
		if (yych <= '`') goto yy504;
		if (yych <= 'f') goto yy510;
		goto yy504;
	}
yy506:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych <= '@') {
		if (yych <= '/') goto yy504;
		if (yych <= '9') goto yy511;
		goto yy504;
	} else {
		if (yych <= 'F') goto yy511;
		if (yych <= '`') goto yy504;
		if (yych <= 'f') goto yy511;
		goto yy504;
	}
yy507:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych <= '@') {
		if (yych <= '/') goto yy504;
		if (yych <= '9') goto yy512;
		goto yy504;
	} else {
		if (yych <= 'F') goto yy512;
		if (yych <= '`') goto yy504;
		if (yych <= 'f') goto yy512;
		goto yy504;
	}
yy508:
	++YYCURSOR;
#line 520 "../src/ast/lex.re"
	{ return unesc_oct(tok, cur); }
#line 3001 "src/ast/lex.cc"
yy510:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych <= '@') {
		if (yych <= '/') goto yy504;
		if (yych <= '9') goto yy514;
		goto yy504;
	} else {
		if (yych <= 'F') goto yy514;
		if (yych <= '`') goto yy504;
		if (yych <= 'f') goto yy514;
		goto yy504;
	}
yy511:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych <= '@') {
		if (yych <= '/') goto yy504;
		if (yych <= '9') goto yy507;
		goto yy504;
	} else {
		if (yych <= 'F') goto yy507;
		if (yych <= '`') goto yy504;
		if (yych <= 'f') goto yy507;
		goto yy504;
	}
yy512:
	++YYCURSOR;
#line 519 "../src/ast/lex.re"
	{ return unesc_hex(tok, cur); }
#line 3030 "src/ast/lex.cc"
yy514:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych <= '@') {
		if (yych <= '/') goto yy504;
		if (yych >= ':') goto yy504;
	} else {
		if (yych <= 'F') goto yy515;
		if (yych <= '`') goto yy504;
		if (yych >= 'g') goto yy504;
	}
yy515:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych <= '@') {
		if (yych <= '/') goto yy504;
		if (yych <= '9') goto yy506;
		goto yy504;
	} else {
		if (yych <= 'F') goto yy506;
		if (yych <= '`') goto yy504;
		if (yych <= 'f') goto yy506;
		goto yy504;
	}
}
#line 535 "../src/ast/lex.re"

}

uint32_t Scanner::lex_str_chr(char quote, bool &end)
{
    end = false;
    tok = cur;
    const uint32_t l = get_cline(), c = get_column();
    
#line 3064 "src/ast/lex.cc"
{
	YYCTYPE yych;
	unsigned int yyaccept = 0;
	if ((YYLIMIT - YYCURSOR) < 10) YYFILL(10);
	yych = (YYCTYPE)*YYCURSOR;
	if (yych <= '\f') {
		if (yych <= 0x00) goto yy518;
		if (yych == '\n') goto yy522;
		goto yy520;
	} else {
		if (yych <= '\r') goto yy524;
		if (yych == '\\') goto yy525;
		goto yy520;
	}
yy518:
	++YYCURSOR;
#line 545 "../src/ast/lex.re"
	{ fail_if_eof(); return 0; }
#line 3083 "src/ast/lex.cc"
yy520:
	++YYCURSOR;
yy521:
#line 551 "../src/ast/lex.re"
	{
            end = tok[0] == quote;
            return static_cast<uint8_t>(tok[0]);
        }
#line 3092 "src/ast/lex.cc"
yy522:
	++YYCURSOR;
#line 546 "../src/ast/lex.re"
	{ fatal_lc(l, c, "newline in character string"); }
#line 3097 "src/ast/lex.cc"
yy524:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == '\n') goto yy522;
	goto yy521;
yy525:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych <= '`') {
		if (yych <= '3') {
			if (yych <= '\n') {
				if (yych <= 0x00) goto yy526;
				if (yych <= '\t') goto yy527;
				goto yy522;
			} else {
				if (yych == '\r') goto yy529;
				if (yych <= '/') goto yy527;
				goto yy530;
			}
		} else {
			if (yych <= 'W') {
				if (yych <= '7') goto yy532;
				if (yych == 'U') goto yy533;
				goto yy527;
			} else {
				if (yych <= 'X') goto yy535;
				if (yych == '\\') goto yy536;
				goto yy527;
			}
		}
	} else {
		if (yych <= 'q') {
			if (yych <= 'e') {
				if (yych <= 'a') goto yy538;
				if (yych <= 'b') goto yy540;
				goto yy527;
			} else {
				if (yych <= 'f') goto yy542;
				if (yych == 'n') goto yy544;
				goto yy527;
			}
		} else {
			if (yych <= 'u') {
				if (yych <= 'r') goto yy546;
				if (yych <= 's') goto yy527;
				if (yych <= 't') goto yy548;
				goto yy535;
			} else {
				if (yych <= 'v') goto yy550;
				if (yych == 'x') goto yy552;
				goto yy527;
			}
		}
	}
yy526:
#line 549 "../src/ast/lex.re"
	{ fatal_lc(l, c, "syntax error in escape sequence"); }
#line 3153 "src/ast/lex.cc"
yy527:
	++YYCURSOR;
yy528:
#line 565 "../src/ast/lex.re"
	{
            if (tok[1] != quote) {
                warn.useless_escape(cline, get_column(), tok[1]);
            }
            return static_cast<uint8_t>(tok[1]);
        }
#line 3164 "src/ast/lex.cc"
yy529:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == '\n') goto yy522;
	goto yy528;
yy530:
	yyaccept = 0;
	yych = (YYCTYPE)*(YYMARKER = ++YYCURSOR);
	if (yych <= '/') goto yy531;
	if (yych <= '7') goto yy553;
yy531:
#line 548 "../src/ast/lex.re"
	{ fatal_lc(l, c, "syntax error in octal escape sequence"); }
#line 3177 "src/ast/lex.cc"
yy532:
	++YYCURSOR;
	goto yy531;
yy533:
	yyaccept = 1;
	yych = (YYCTYPE)*(YYMARKER = ++YYCURSOR);
	if (yych <= '@') {
		if (yych <= '/') goto yy534;
		if (yych <= '9') goto yy555;
	} else {
		if (yych <= 'F') goto yy555;
		if (yych <= '`') goto yy534;
		if (yych <= 'f') goto yy555;
	}
yy534:
#line 547 "../src/ast/lex.re"
	{ fatal_lc(l, c, "syntax error in hexadecimal escape sequence"); }
#line 3195 "src/ast/lex.cc"
yy535:
	yyaccept = 1;
	yych = (YYCTYPE)*(YYMARKER = ++YYCURSOR);
	if (yych <= '@') {
		if (yych <= '/') goto yy534;
		if (yych <= '9') goto yy556;
		goto yy534;
	} else {
		if (yych <= 'F') goto yy556;
		if (yych <= '`') goto yy534;
		if (yych <= 'f') goto yy556;
		goto yy534;
	}
yy536:
	++YYCURSOR;
#line 564 "../src/ast/lex.re"
	{ return static_cast<uint8_t>('\\'); }
#line 3213 "src/ast/lex.cc"
yy538:
	++YYCURSOR;
#line 557 "../src/ast/lex.re"
	{ return static_cast<uint8_t>('\a'); }
#line 3218 "src/ast/lex.cc"
yy540:
	++YYCURSOR;
#line 558 "../src/ast/lex.re"
	{ return static_cast<uint8_t>('\b'); }
#line 3223 "src/ast/lex.cc"
yy542:
	++YYCURSOR;
#line 559 "../src/ast/lex.re"
	{ return static_cast<uint8_t>('\f'); }
#line 3228 "src/ast/lex.cc"
yy544:
	++YYCURSOR;
#line 560 "../src/ast/lex.re"
	{ return static_cast<uint8_t>('\n'); }
#line 3233 "src/ast/lex.cc"
yy546:
	++YYCURSOR;
#line 561 "../src/ast/lex.re"
	{ return static_cast<uint8_t>('\r'); }
#line 3238 "src/ast/lex.cc"
yy548:
	++YYCURSOR;
#line 562 "../src/ast/lex.re"
	{ return static_cast<uint8_t>('\t'); }
#line 3243 "src/ast/lex.cc"
yy550:
	++YYCURSOR;
#line 563 "../src/ast/lex.re"
	{ return static_cast<uint8_t>('\v'); }
#line 3248 "src/ast/lex.cc"
yy552:
	yyaccept = 1;
	yych = (YYCTYPE)*(YYMARKER = ++YYCURSOR);
	if (yych <= '@') {
		if (yych <= '/') goto yy534;
		if (yych <= '9') goto yy557;
		goto yy534;
	} else {
		if (yych <= 'F') goto yy557;
		if (yych <= '`') goto yy534;
		if (yych <= 'f') goto yy557;
		goto yy534;
	}
yy553:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych <= '/') goto yy554;
	if (yych <= '7') goto yy558;
yy554:
	YYCURSOR = YYMARKER;
	if (yyaccept == 0) {
		goto yy531;
	} else {
		goto yy534;
	}
yy555:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych <= '@') {
		if (yych <= '/') goto yy554;
		if (yych <= '9') goto yy560;
		goto yy554;
	} else {
		if (yych <= 'F') goto yy560;
		if (yych <= '`') goto yy554;
		if (yych <= 'f') goto yy560;
		goto yy554;
	}
yy556:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych <= '@') {
		if (yych <= '/') goto yy554;
		if (yych <= '9') goto yy561;
		goto yy554;
	} else {
		if (yych <= 'F') goto yy561;
		if (yych <= '`') goto yy554;
		if (yych <= 'f') goto yy561;
		goto yy554;
	}
yy557:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych <= '@') {
		if (yych <= '/') goto yy554;
		if (yych <= '9') goto yy562;
		goto yy554;
	} else {
		if (yych <= 'F') goto yy562;
		if (yych <= '`') goto yy554;
		if (yych <= 'f') goto yy562;
		goto yy554;
	}
yy558:
	++YYCURSOR;
#line 556 "../src/ast/lex.re"
	{ return unesc_oct(tok, cur); }
#line 3313 "src/ast/lex.cc"
yy560:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych <= '@') {
		if (yych <= '/') goto yy554;
		if (yych <= '9') goto yy564;
		goto yy554;
	} else {
		if (yych <= 'F') goto yy564;
		if (yych <= '`') goto yy554;
		if (yych <= 'f') goto yy564;
		goto yy554;
	}
yy561:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych <= '@') {
		if (yych <= '/') goto yy554;
		if (yych <= '9') goto yy557;
		goto yy554;
	} else {
		if (yych <= 'F') goto yy557;
		if (yych <= '`') goto yy554;
		if (yych <= 'f') goto yy557;
		goto yy554;
	}
yy562:
	++YYCURSOR;
#line 555 "../src/ast/lex.re"
	{ return unesc_hex(tok, cur); }
#line 3342 "src/ast/lex.cc"
yy564:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych <= '@') {
		if (yych <= '/') goto yy554;
		if (yych >= ':') goto yy554;
	} else {
		if (yych <= 'F') goto yy565;
		if (yych <= '`') goto yy554;
		if (yych >= 'g') goto yy554;
	}
yy565:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych <= '@') {
		if (yych <= '/') goto yy554;
		if (yych <= '9') goto yy556;
		goto yy554;
	} else {
		if (yych <= 'F') goto yy556;
		if (yych <= '`') goto yy554;
		if (yych <= 'f') goto yy556;
		goto yy554;
	}
}
#line 571 "../src/ast/lex.re"

}

const AST *Scanner::lex_str(char quote)
{
    const uint32_t column = get_column();
    std::vector<ASTChar> *str = new std::vector<ASTChar>;
    for (bool end;;) {
        const uint32_t c = lex_str_chr(quote, end);
        if (end) return ast_str(cline, column, str, quote == '\'');
        str->push_back(ASTChar(c, get_column()));
    }
}

void Scanner::set_sourceline ()
{
sourceline:
    tok = cur;

#line 3386 "src/ast/lex.cc"
{
	YYCTYPE yych;
	static const unsigned char yybm[] = {
		  0, 128, 128, 128, 128, 128, 128, 128, 
		128, 128,   0, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128,   0, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128,   0, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
	};
	if ((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
	yych = (YYCTYPE)*YYCURSOR;
	if (yych <= '\r') {
		if (yych <= '\t') {
			if (yych >= 0x01) goto yy570;
		} else {
			if (yych <= '\n') goto yy572;
			if (yych <= '\f') goto yy570;
			goto yy574;
		}
	} else {
		if (yych <= '"') {
			if (yych <= '!') goto yy570;
			goto yy575;
		} else {
			if (yych <= '0') goto yy570;
			if (yych <= '9') goto yy576;
			goto yy570;
		}
	}
	++YYCURSOR;
#line 608 "../src/ast/lex.re"
	{
        --cur;
        tok = cur;
        return;
    }
#line 3450 "src/ast/lex.cc"
yy570:
	++YYCURSOR;
yy571:
#line 614 "../src/ast/lex.re"
	{ goto sourceline; }
#line 3456 "src/ast/lex.cc"
yy572:
	++YYCURSOR;
#line 603 "../src/ast/lex.re"
	{
        tok = cur;
        return;
    }
#line 3464 "src/ast/lex.cc"
yy574:
	yych = (YYCTYPE)*++YYCURSOR;
	if (yych == '\n') goto yy572;
	goto yy571;
yy575:
	yych = (YYCTYPE)*(YYMARKER = ++YYCURSOR);
	if (yych <= 0x00) goto yy571;
	if (yych == '\n') goto yy571;
	goto yy580;
yy576:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = (YYCTYPE)*YYCURSOR;
	if (yybm[0+yych] & 64) {
		goto yy576;
	}
#line 590 "../src/ast/lex.re"
	{
        if (!s_to_u32_unsafe (tok, cur, cline)) {
            fatal_lc(get_cline(), get_column(), "line number overflow");
        }
        goto sourceline;
    }
#line 3488 "src/ast/lex.cc"
yy579:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = (YYCTYPE)*YYCURSOR;
yy580:
	if (yybm[0+yych] & 128) {
		goto yy579;
	}
	if (yych <= '\n') goto yy581;
	if (yych <= '"') goto yy582;
	goto yy584;
yy581:
	YYCURSOR = YYMARKER;
	goto yy571;
yy582:
	++YYCURSOR;
#line 597 "../src/ast/lex.re"
	{
        in.escaped_file_name = std::string (tok + 1, tok_len () - 2); // strip quotes
        strrreplace (in.escaped_file_name, "\\", "\\\\");
        goto sourceline;
    }
#line 3511 "src/ast/lex.cc"
yy584:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = (YYCTYPE)*YYCURSOR;
	if (yych <= 0x00) goto yy581;
	if (yych == '\n') goto yy581;
	goto yy579;
}
#line 615 "../src/ast/lex.re"

}

void Scanner::fail_if_eof() const
{
    if (cur == eof) {
        const uint32_t col = static_cast<uint32_t>(cur - pos) - 1;
        fatal_lc(get_cline(), col, "unexpected end of input");
    }
}

} // end namespace re2c
