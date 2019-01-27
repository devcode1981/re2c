#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "libre2c_posix/regex.h"
#include "libre2c_posix/regex-impl.h"
#include "src/util/c99_stdint.h"


static int test(const char *pattern, const char *string
    , size_t nmatch, const regoff_t *submatch)
{
    regex_t re;
    regmatch_t *pmatch = new regmatch_t[nmatch];
    int result;

    result = regcomp(&re, pattern, 0);
    if (result != 0) {
        fprintf(stderr, "regcomp() failed for RE %s\n", pattern);
        goto end;
    }

    result = regexec(&re, string, nmatch, pmatch, 0);
    if (result != 0) {
        if (nmatch == 0) {
            // failure was expected => it's a success
            result = 0;
        }
        else if (nmatch > 0) {
            fprintf(stderr, "regexec() failed for RE %s and string %s\n"
                , pattern, string);
            goto end;
        }
    }
    else if (nmatch == 0) {
        // regexed must have failed, something is wrong
        result = REG_NOMATCH;
        fprintf(stderr, "regexec() didn't fail while it should"
            " for RE %s and string %s\n", pattern, string);
        goto end;
    }

    assert(nmatch == 0 || nmatch == re.re_nsub);

    for (uint32_t i = 0; i < nmatch; ++i) {
        regoff_t so = submatch[2 * i];
        regoff_t eo = submatch[2 * i + 1];
        const regmatch_t &have = pmatch[i];

        if (so != have.rm_so || eo != have.rm_eo) {
            result = 1;
            fprintf(stderr, "incorrect submatch for RE %s and string %s:\n"
                "\tpmatch[%u].rm_so = %ld (expected %ld)\n"
                "\tpmatch[%u].rm_eo = %ld (expected %ld)\n"
                , pattern, string
                , i, have.rm_so, so
                , i, have.rm_eo, eo);
            goto end;
        }
    }

end:
    regfree(&re);
    delete[] pmatch;

    return result;
}

// Poor man's replacement for C++11 initializer lists. :)
// Variadic macros are non-standard in c++98. Variadic functions have
// subtle problems with types: literals are 'int' by default, so passing
// 'long' as vararg requres suffix 'L', which is easy to forget and hard
// to notice (the problem is platform/toolchain-specific).
#define  GS                                              static const regoff_t gs[]
#define  T(R,S,gs)                                       e |= test(R,S,sizeof(gs)/sizeof(gs[0])/2,gs);
#define  T0(R,S)                                         e |= test(R,S,0,NULL);
#define  T1(R,S,a,b)                                     { GS = {a,b};                                     T(R,S,gs); }
#define  T2(R,S,a,b,c,d)                                 { GS = {a,b,c,d};                                 T(R,S,gs); }
#define  T3(R,S,a,b,c,d,e,f)                             { GS = {a,b,c,d,e,f};                             T(R,S,gs); }
#define  T4(R,S,a,b,c,d,e,f,g,h)                         { GS = {a,b,c,d,e,f,g,h};                         T(R,S,gs); }
#define  T5(R,S,a,b,c,d,e,f,g,h,i,j)                     { GS = {a,b,c,d,e,f,g,h,i,j};                     T(R,S,gs); }
#define  T6(R,S,a,b,c,d,e,f,g,h,i,j,k,l)                 { GS = {a,b,c,d,e,f,g,h,i,j,k,l};                 T(R,S,gs); }
#define  T7(R,S,a,b,c,d,e,f,g,h,i,j,k,l,m,n)             { GS = {a,b,c,d,e,f,g,h,i,j,k,l,m,n};             T(R,S,gs); }
#define  T8(R,S,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p)         { GS = {a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p};         T(R,S,gs); }
#define  T9(R,S,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r)     { GS = {a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r};     T(R,S,gs); }
#define T10(R,S,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t) { GS = {a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t}; T(R,S,gs); }

int main()
{
    int e = 0;

    T1("a",        "a",    0,1);
    T2("(a)",      "a",    0,1, 0,1);
    T2("(a*)",     "aaa",  0,3, 0,3);
    T3("(a*)(b*)", "aabb", 0,4, 0,2, 2,4);
    T3("(a*)(a*)", "aa",   0,2, 0,2, 2,2);
    T2("(a|aa)*",  "aa",   0,2, 0,2);
    T3("(a)|(a)",  "a",    0,1, 0,1, -1,-1);
    T3("(a)*(a)*", "a",    0,1, 0,1, -1,-1);

    T1("[a]",      "a",    0,1);
    T0("[a]",      "b");
    T0("[^a]",     "a");
    T1("[^a]",     "b",    0,1);
    T1("[ac]*",    "ac",   0,2);
    T1("[a-c]*",   "abc",  0,3);
    T1("[]]",      "]",    0,1);
    T0("[^]]",     "]");
    T1("[^]]",     "a",    0,1);
    T1("[-]",      "-",    0,1);
    T1("[]-]*",    "]-",   0,2);
    T1("[-a]*",    "-a",   0,2);
    T1("[a-]*",    "-a",   0,2);
    T1("[-a-]*",   "-a",   0,2);

    // basic
    T3("(..)*(...)*",              "a",           0,0, -1,-1, -1,-1);
    T3("(..)*(...)*",              "abcd",        0,4, 2,4, -1,-1);
    T3("(ab|a)(bc|c)",             "abc",         0,3, 0,2, 2,3);
    T2("(ab)c|abc",                "abc",         0,3, 0,2);
    T4("(a*)(b?)(b+)b{3}",         "aaabbbbbbb",  0,10, 0,3, 3,4, 4,7);
    T4("(a*)(b{0,1})(b{1,})b{3}",  "aaabbbbbbb",  0,10, 0,3, 3,4, 4,7);
    T3("((a|a)|a)",                "a",           0,1, 0,1, 0,1);
    T3("(a*)(a|aa)",               "aaaa",        0,4, 0,3, 3,4);
    T2("a*(a.|aa)",                "aaaa",        0,4, 2,4);
    T4("a(b)|c(d)|a(e)f",          "aef",         0,3, -1,-1, -1,-1, 1,2);
    T2("(a|b)?.*",                 "b",           0,1, 0,1);
    T3("(a|b)c|a(b|c)",            "ac",          0,2, 0,1, -1,-1);
    T3("(a|b)c|a(b|c)",            "ab",          0,2, -1,-1, 1,2);
    T3("(a|b)*c|(a|ab)*c",         "abc",         0,3, 1,2, -1,-1);
    T3("(.a|.b).*|.*(.a|.b)",      "xa",          0,2, 0,2, -1,-1);
    T2("a?(ab|ba)ab",              "abab",        0,4, 0,2);
    T2("a?(a[c]{0}b|ba)ab",        "abab",        0,4, 0,2);
    T1("ab|abab",                  "abbabab",     0,2);
    T3("(aa|aaa)*|(a|aaaaa)",      "aa",          0,2, 0,2, -1,-1);
    T3("(a.|.a.)*|(a|.a...)",      "aa",          0,2, 0,2, -1,-1);
    T4("(a)(b)(c)",                "abc",         0,3, 0,1, 1,2, 2,3);
    T7("((((((x))))))",            "x",           0,1, 0,1, 0,1, 0,1, 0,1, 0,1, 0,1);
    T7("((((((x))))))*",           "xx",          0,2, 1,2, 1,2, 1,2, 1,2, 1,2, 1,2);
    T2("a?(ab|ba)*",               "ababababababababababababababababababababababababababababababababababababababababa", 0,81, 79,81);
    T1("a*a*a*a*a*b",              "aaaaaaaaab",  0,10);
    T1("a[b]+bc",                  "abbc",        0,4);
    T1("a[b]+bc",                  "abbbbc",      0,6);
    T1("a[b]?bc",                  "abbc",        0,4);
    T1("a[b]?bc",                  "abc",         0,3);
    T1("a[b]?c",                   "abc",         0,3);
    T1("ab|cd",                    "abc",         0,2);
    T1("ab|cd",                    "abcd",        0,2);
    T3("((a))",                    "abc",         0,1, 0,1, 0,1);
    T3("(a)b(c)",                  "abc",         0,3, 0,1, 2,3);
    T1("a*",                       "aaa",         0,3);
    T2("(a*)*",                    "-",           0,0, 0,0);
    T2("(a*)+",                    "-",           0,0, 0,0);
    T2("(a*|b)*",                  "-",           0,0, 0,0);
    T2("(a+|b)*",                  "ab",          0,2, 1,2);
    T2("(a+|b)+",                  "ab",          0,2, 1,2);
    T2("(a+|b)?",                  "ab",          0,1, 0,1);
    T2("([abc])*d",                "abbbcd",      0,6, 4,5);
    T2("([abc])*bcd",              "abcd",        0,4, 0,1);
    T1("a|b|c|d|e",                "e",           0,1);
    T2("(a|b|c|d|e)f",             "ef",          0,2, 0,1);
    T3("((a*|b))*",                "-",           0,0, 0,0, 0,0);
    T2("(ab|a[b]*)bc",             "abc",         0,3, 0,1);
    T2("a([bc]*)c*",               "abc",         0,3, 1,3);
    T3("a([bc]*)(c*d)",            "abcd",        0,4, 1,3, 3,4);
    T3("a([bc]+)(c*d)",            "abcd",        0,4, 1,3, 3,4);
    T3("a([bc]*)(c+d)",            "abcd",        0,4, 1,2, 2,4);
    T1("a[bcd]*dcdcde",            "adcdcde",     0,7);
    T2("(ab|a)b*c",                "abc",         0,3, 0,2);
    T5("((a)(b)c)(d)",             "abcd",        0,4, 0,3, 0,1, 1,2, 3,4);
    T3("(.*)c(.*)",                "abcde",       0,5, 0,2, 3,5);
    T2("a(bc)d",                   "abcd",        0,4, 1,3);
    T2("a+(b|c)*d+",               "aabcdd",      0,6, 3,4);

    // categorize
    T4("(a*)(ab)*(b*)",            "abc",    0,2, 0,1, -1,-1, 1,2);
    T7("((a*)(ab)*)((b*)(a*))",    "aba",    0,3, 0,2, 0,0, 0,2, 2,3, 2,2, 2,3);
    T2("(...?.?)*",                "xxxxxx", 0,6, 4,6);
    T3("(a|ab)(bc|c)",             "abcabc", 0,3, 0,2, 2,3);
    T3("(aba|a*b)(aba|a*b)",       "ababa",  0,5, 0,2, 2,5);
    T2("(a*){2}",                  "xxxxx",  0,0, 0,0);
    T2("(a*)*",                    "a",      0,1, 0,1);
    T2("(aba|a*b)*",               "ababa",  0,5, 2,5);
    T3("(a(b)?)+",                 "aba",    0,3, 2,3, -1,-1);
    T2(".*(.*)",                   "ab",     0,2, 2,2);
    T6("(a?)((ab)?)(b?)a?(ab)?b?", "abab",   0,4, 0,1, 1,1, -1,-1, 1,2, -1,-1);

    // forcedassoc
    T3("(a|ab)(c|bcd)",       "abcd", 0,4, 0,1, 1,4);
    T3("(a|ab)(bcd|c)",       "abcd", 0,4, 0,1, 1,4);
    T3("(ab|a)(c|bcd)",       "abcd", 0,4, 0,1, 1,4);
    T3("(ab|a)(bcd|c)",       "abcd", 0,4, 0,1, 1,4);
    T5("((a|ab)(c|bcd))(d*)", "abcd", 0,4, 0,4, 0,1, 1,4, 4,4);
    T5("((a|ab)(bcd|c))(d*)", "abcd", 0,4, 0,4, 0,1, 1,4, 4,4);
    T5("((ab|a)(c|bcd))(d*)", "abcd", 0,4, 0,4, 0,1, 1,4, 4,4);
    T5("((ab|a)(bcd|c))(d*)", "abcd", 0,4, 0,4, 0,1, 1,4, 4,4);
    T5("(a|ab)((c|bcd)(d*))", "abcd", 0,4, 0,2, 2,4, 2,3, 3,4);
    T5("(a|ab)((bcd|c)(d*))", "abcd", 0,4, 0,2, 2,4, 2,3, 3,4);
    T5("(ab|a)((c|bcd)(d*))", "abcd", 0,4, 0,2, 2,4, 2,3, 3,4);
    T5("(ab|a)((bcd|c)(d*))", "abcd", 0,4, 0,2, 2,4, 2,3, 3,4);
    T3("(a*)(b|abc)",         "abc",  0,3, 0,0, 0,3);
    T3("(a*)(abc|b)",         "abc",  0,3, 0,0, 0,3);
    T5("((a*)(b|abc))(c*)",   "abc",  0,3, 0,3, 0,0, 0,3, 3,3);
    T5("((a*)(abc|b))(c*)",   "abc",  0,3, 0,3, 0,0, 0,3, 3,3);
    T5("(a*)((b|abc)(c*))",   "abc",  0,3, 0,1, 1,3, 1,2, 2,3);
    T5("(a*)((abc|b)(c*))",   "abc",  0,3, 0,1, 1,3, 1,2, 2,3);
    T3("(a*)(b|abc)",         "abc",  0,3, 0,0, 0,3);
    T3("(a*)(abc|b)",         "abc",  0,3, 0,0, 0,3);
    T5("((a*)(b|abc))(c*)",   "abc",  0,3, 0,3, 0,0, 0,3, 3,3);
    T5("((a*)(abc|b))(c*)",   "abc",  0,3, 0,3, 0,0, 0,3, 3,3);
    T5("(a*)((b|abc)(c*))",   "abc",  0,3, 0,1, 1,3, 1,2, 2,3);
    T5("(a*)((abc|b)(c*))",   "abc",  0,3, 0,1, 1,3, 1,2, 2,3);
    T2("(a|ab)",              "ab",   0,2, 0,2);
    T2("(ab|a)",              "ab",   0,2, 0,2);
    T3("(a|ab)(b*)",          "ab",   0,2, 0,2, 2,2);
    T3("(ab|a)(b*)",          "ab",   0,2, 0,2, 2,2);

    // glennfowler
    T4("(a?)((ab)?)",                    "ab",      0,2, 0,0, 0,2, 0,2);
    T5("(a?)((ab)?)(b?)",                "ab",      0,2, 0,1, 1,1, -1,-1, 1,2);
    T6("((a?)((ab)?))(b?)",              "ab",      0,2, 0,2, 0,0, 0,2, 0,2, 2,2);
    T6("(a?)(((ab)?)(b?))",              "ab",      0,2, 0,1, 1,2, 1,1, -1,-1, 1,2);
    T2("(.?)",                           "x",       0,1, 0,1);
    T2("(.?){1}",                        "x",       0,1, 0,1);
    T3("(.?)(.?)",                       "x",       0,1, 0,1, 1,1);
    T2("(.?){2}",                        "x",       0,1, 1,1);
    T2("(.?)*",                          "x",       0,1, 0,1);
    T2("(.?.?)",                         "xxx",     0,2, 0,2);
    T2("(.?.?){1}",                      "xxx",     0,2, 0,2);
    T3("(.?.?)(.?.?)",                   "xxx",     0,3, 0,2, 2,3);
    T2("(.?.?){2}",                      "xxx",     0,3, 2,3);
    T4("(.?.?)(.?.?)(.?.?)",             "xxx",     0,3, 0,2, 2,3, 3,3);
    T2("(.?.?){3}",                      "xxx",     0,3, 3,3);
    T2("(.?.?)*",                        "xxx",     0,3, 2,3);
    T4("a?((ab)?)(b?)",                  "ab",      0,2, 1,1, -1,-1, 1,2);
    T4("(a?)((ab)?)b?",                  "ab",      0,2, 0,1, 1,1, -1,-1);
    T3("a?((ab)?)b?",                    "ab",      0,2, 1,1, -1,-1);
    T2("(a*){2}",                        "xxxxx",   0,0, 0,0);
    T3("(ab?)(b?a)",                     "aba",     0,3, 0,2, 2,3);
    T3("(a|ab)(ba|a)",                   "aba",     0,3, 0,2, 2,3);
    T2("(a|ab|ba)",                      "aba",     0,2, 0,2);
    T3("(a|ab|ba)(a|ab|ba)",             "aba",     0,3, 0,2, 2,3);
    T2("(a|ab|ba)*",                     "aba",     0,3, 2,3);
    T2("(aba|a*b)",                      "ababa",   0,3, 0,3);
    T3("(aba|a*b)(aba|a*b)",             "ababa",   0,5, 0,2, 2,5);
    T0("(aba|a*b)(aba|a*b)(aba|a*b)",    "ababa");
    T2("(aba|a*b)*",                     "ababa",   0,5, 2,5);
    T2("(aba|ab|a)",                     "ababa",   0,3, 0,3);
    T3("(aba|ab|a)(aba|ab|a)",           "ababa",   0,5, 0,2, 2,5);
    T4("(aba|ab|a)(aba|ab|a)(aba|ab|a)", "ababa",   0,5, 0,2, 2,4, 4,5);
    T2("(aba|ab|a)*",                    "ababa",   0,5, 2,5);
    T3("(a(b)?)",                        "aba",     0,2, 0,2, 1,2);
    T5("(a(b)?)(a(b)?)",                 "aba",     0,3, 0,2, 1,2, 2,3, -1,-1);
    T3("(a(b)?)+",                       "aba",     0,3, 2,3, -1,-1);
    T3("(.*)(.*)",                       "xx",      0,2, 0,2, 2,2);
    T2(".*(.*)",                         "xx",      0,2, 2,2);
    T2("(a.*z|b.*y)",                    "azbazby", 0,5, 0,5);
    T3("(a.*z|b.*y)(a.*z|b.*y)",         "azbazby", 0,7, 0,5, 5,7);
    T2("(a.*z|b.*y)*",                   "azbazby", 0,7, 5,7);
    T3("(.|..)(.*)",                     "ab",      0,2, 0,2, 2,2);
    T4("((..)*(...)*)",                  "xxx",     0,3, 0,3, -1,-1, 0,3);
    T7("((..)*(...)*)((..)*(...)*)",     "xxx",     0,3, 0,3, -1,-1, 0,3, 3,3, -1,-1, -1,-1);
    T4("((..)*(...)*)*",                 "xxx",     0,3, 0,3, -1,-1, 0,3);

    // nullsubexpr
    T2("(a*)*",      "a",        0,1, 0,1);
    T2("(a*)*",      "x",        0,0, 0,0);
    T2("(a*)*",      "aaaaaa",   0,6, 0,6);
    T2("(a*)*",      "aaaaaax",  0,6, 0,6);
    T2("(a*)+",      "a",        0,1, 0,1);
    T2("(a*)+",      "x",        0,0, 0,0);
    T2("(a*)+",      "aaaaaa",   0,6, 0,6);
    T2("(a*)+",      "aaaaaax",  0,6, 0,6);
    T2("(a+)*",      "a",        0,1, 0,1);
    T2("(a+)*",      "x",        0,0, -1,-1);
    T2("(a+)*",      "aaaaaa",   0,6, 0,6);
    T2("(a+)*",      "aaaaaax",  0,6, 0,6);
    T2("(a+)+",      "a",        0,1, 0,1);
    T0("(a+)+",      "x");
    T2("(a+)+",      "aaaaaa",   0,6, 0,6);
    T2("(a+)+",      "aaaaaax",  0,6, 0,6);
    T2("([a]*)*",    "a",        0,1, 0,1);
    T2("([a]*)*",    "x",        0,0, 0,0);
    T2("([a]*)*",    "aaaaaa",   0,6, 0,6);
    T2("([a]*)*",    "aaaaaax",  0,6, 0,6);
    T2("([a]*)+",    "a",        0,1, 0,1);
    T2("([a]*)+",    "x",        0,0, 0,0);
    T2("([a]*)+",    "aaaaaa",   0,6, 0,6);
    T2("([a]*)+",    "aaaaaax",  0,6, 0,6);
    T2("([^b]*)*",   "a",        0,1, 0,1);
    T2("([^b]*)*",   "b",        0,0, 0,0);
    T2("([^b]*)*",   "aaaaaa",   0,6, 0,6);
    T2("([^b]*)*",   "aaaaaab",  0,6, 0,6);
    T2("([ab]*)*",   "a",        0,1, 0,1);
    T2("([ab]*)*",   "aaaaaa",   0,6, 0,6);
    T2("([ab]*)*",   "ababab",   0,6, 0,6);
    T2("([ab]*)*",   "bababa",   0,6, 0,6);
    T2("([ab]*)*",   "b",        0,1, 0,1);
    T2("([ab]*)*",   "bbbbbb",   0,6, 0,6);
    T2("([ab]*)*",   "aaaabcde", 0,5, 0,5);
    T2("([^a]*)*",   "b",        0,1, 0,1);
    T2("([^a]*)*",   "bbbbbb",   0,6, 0,6);
    T2("([^a]*)*",   "aaaaaa",   0,0, 0,0);
    T2("([^ab]*)*",  "ccccxx",   0,6, 0,6);
    T2("([^ab]*)*",  "ababab",   0,0, 0,0);
    T3("((z)+|a)*",  "zabcde",   0,2, 1,2, -1,-1);
    T2("(a)",        "aaa",      0,1, 0,1);
    T3("(a*)*(x)",   "x",        0,1, 0,0, 0,1);
    T3("(a*)*(x)",   "ax",       0,2, 0,1, 1,2);
    T3("(a*)*(x)",   "axa",      0,2, 0,1, 1,2);
    T3("(a*)+(x)",   "x",        0,1, 0,0, 0,1);
    T3("(a*)+(x)",   "ax",       0,2, 0,1, 1,2);
    T3("(a*)+(x)",   "axa",      0,2, 0,1, 1,2);
    T3("(a*){2}(x)", "x",        0,1, 0,0, 0,1);
    T3("(a*){2}(x)", "ax",       0,2, 1,1, 1,2);
    T3("(a*){2}(x)", "axa",      0,2, 1,1, 1,2);

    T4("(()|.)(b)",     "ab",    0,2, 0,1, -1,-1, 1,2);
    T4("(()|[ab])(b)",  "ab",    0,2, 0,1, -1,-1, 1,2);
    T3("(()|[ab])+b",   "aaab",  0,4, 2,3, -1,-1);
    T4("(.|())(b)",     "ab",    0,2, 0,1, -1,-1, 1,2);
    T4("([ab]|())(b)",  "ab",    0,2, 0,1, -1,-1, 1,2);
    T3("([ab]|())+b",   "aaab",  0,4, 2,3, -1,-1);
    T3("(.?)(b)",       "ab",    0,2, 0,1, 1,2);

    // other
    T2("(a|aa)*",                            "aaa",         0,3, 2,3);
    T2("(a|aa)*",                            "aaaa",        0,4, 2,4);
    T2("(aa|a)*",                            "aaa",         0,3, 2,3);
    T2("(aa|a)*",                            "aaaa",        0,4, 2,4);
    T2("a|(a)",                              "a",           0,1, -1,-1);
    T2("(a)|a",                              "a",           0,1, 0,1);
    T3("(b)a|b(a)",                          "ba",          0,2, 0,1, -1,-1);
    T3("b(a)|(b)a",                          "ba",          0,2, 1,2, -1,-1);
    T2("a*|(a|aa)*",                         "aa",          0,2, -1,-1);
    T2("(a|aa)*|a*",                         "aa",          0,2, 0,2);
    T2("(aa*|aaa*)*",                        "aaaaaa",      0,6, 0,6);
    T3("(aa*|aaa*)(aa*|aaa*)",               "aaaaaa",      0,6, 0,5, 5,6);
    T2("(aa*|aaa*){2}",                      "aaaaaa",      0,6, 5,6);
    T7("((aa)*|(aaa)*)((aa)*|(aaa)*)",       "aaaaaa",      0,6, 0,6, 4,6, -1,-1, 6,6, -1,-1, -1,-1);
    T4("((aa)*|(aaa)*){2}",                  "aaaaaa",      0,6, 6,6, -1,-1, -1,-1);
    T3("(aa)*|(aaa)*",                       "aaaaaa",      0,6, 4,6, -1,-1);
    T2("(X|Xa|Xab|Xaba|abab|baba|bY|Y)*",    "XY",          0,2, 1,2);
    T2("(X|Xa|Xab|Xaba|abab|baba|bY|Y)*",    "XabY",        0,4, 3,4);
    T2("(X|Xa|Xab|Xaba|abab|baba|bY|Y)*",    "XababY",      0,6, 4,6);
    T2("(X|Xa|Xab|Xaba|abab|baba|bY|Y)*",    "XabababY",    0,8, 7,8);
    T2("(X|Xa|Xab|Xaba|abab|baba|bY|Y)*",    "XababababY",  0,10, 8,10);
    T0("(y){2}",                             "NULL");
    T0("(y){2}",                             "y");
    T2("(y){2}",                             "yy",          0,2, 1,2);
    T2("(y){0,2}",                           "NULL",        0,0, -1,-1);
    T2("(y){0,2}",                           "y",           0,1, 0,1);
    T2("(y){0,2}",                           "yy",          0,2, 1,2);
    T0("(y){1,2}",                           "NULL");
    T2("(y){1,2}",                           "y",           0,1, 0,1);
    T2("(y){1,2}",                           "yy",          0,2, 1,2);
    T0("(y){1,2}y",                          "NULL");
    T0("(y){1,2}y",                          "y");
    T2("(y){1,2}y",                          "yy",          0,2, 0,1);
    T2("(y){1,2}y",                          "yyy",         0,3, 1,2);
    T0("(y){1,2}y?",                         "NULL");
    T2("(y){1,2}y?",                         "y",           0,1, 0,1);
    T2("(y){1,2}y?",                         "yy",          0,2, 1,2);
    T2("(y){1,2}y?",                         "yyy",         0,3, 1,2);
    T0("(y){2,}",                            "NULL");
    T0("(y){2,}",                            "y");
    T2("(y){2,}",                            "yy",          0,2, 1,2);
    T2("(y){2,}",                            "yyy",         0,3, 2,3);
    T2("(y?){2}",                            "NULL",        0,0, 0,0);
    T2("(y?){2}",                            "y",           0,1, 1,1);
    T2("(y?){2}",                            "yy",          0,2, 1,2);
    T2("(y?){0,2}",                          "NULL",        0,0, 0,0);
    T2("(y?){0,2}",                          "y",           0,1, 0,1);
    T2("(y?){0,2}",                          "yy",          0,2, 1,2);
    T2("(y?){1,2}",                          "NULL",        0,0, 0,0);
    T2("(y?){1,2}",                          "y",           0,1, 0,1);
    T2("(y?){1,2}",                          "yy",          0,2, 1,2);
    T0("(y?){1,2}y",                         "NULL");
    T2("(y?){1,2}y",                         "y",           0,1, 0,0);
    T2("(y?){1,2}y",                         "yy",          0,2, 0,1);
    T2("(y?){1,2}y",                         "yyy",         0,3, 1,2);
    T2("(y?){1,2}y?",                        "NULL",        0,0, 0,0);
    T2("(y?){1,2}y?",                        "y",           0,1, 0,1);
    T2("(y?){1,2}y?",                        "yy",          0,2, 1,2);
    T2("(y?){1,2}y?",                        "yyy",         0,3, 1,2);
    T2("(y?){2,}",                           "NULL",        0,0, 0,0);
    T2("(y?){2,}",                           "y",           0,1, 1,1);
    T2("(y?){2,}",                           "yy",          0,2, 1,2);
    T2("(y?){2,}",                           "yyy",         0,3, 2,3);
    T3("(y|(x?)){1,3}",                      "y",           0,1, 0,1, -1,-1);
    T2("(y[y]?){3}",                         "yyyy",        0,4, 3,4);

    // repetition
    T0("((..)|(.))",                         "");
    T0("((..)|(.))((..)|(.))",               "");
    T0("((..)|(.))((..)|(.))((..)|(.))",     "");
    T0("((..)|(.)){1}",                      "");
    T0("((..)|(.)){2}",                      "");
    T0("((..)|(.)){3}",                      "");
    T4("((..)|(.))*",                        "",            0,0, -1,-1, -1,-1, -1,-1);
    T4("((..)|(.))",                         "a",           0,1, 0,1, -1,-1, 0,1);
    T0("((..)|(.))((..)|(.))",               "a");
    T0("((..)|(.))((..)|(.))((..)|(.))",     "a");
    T4("((..)|(.)){1}",                      "a",           0,1, 0,1, -1,-1, 0,1);
    T0("((..)|(.)){2}",                      "a");
    T0("((..)|(.)){3}",                      "a");
    T4("((..)|(.))*",                        "a",           0,1, 0,1, -1,-1, 0,1);
    T4("((..)|(.))",                         "aa",          0,2, 0,2, 0,2, -1,-1);
    T7("((..)|(.))((..)|(.))",               "aa",          0,2, 0,1, -1,-1, 0,1, 1,2, -1,-1, 1,2);
    T0("((..)|(.))((..)|(.))((..)|(.))",     "aa");
    T4("((..)|(.)){1}",                      "aa",          0,2, 0,2, 0,2, -1,-1);
    T4("((..)|(.)){2}",                      "aa",          0,2, 1,2, -1,-1, 1,2);
    T0("((..)|(.)){3}",                      "aa");
    T4("((..)|(.))*",                        "aa",          0,2, 0,2, 0,2, -1,-1);
    T4("((..)|(.))",                         "aaa",         0,2, 0,2, 0,2, -1,-1);
    T7("((..)|(.))((..)|(.))",               "aaa",         0,3, 0,2, 0,2, -1,-1, 2,3, -1,-1, 2,3);
    T10("((..)|(.))((..)|(.))((..)|(.))",    "aaa",         0,3, 0,1, -1,-1, 0,1, 1,2, -1,-1, 1,2, 2,3, -1,-1, 2,3);
    T4("((..)|(.)){1}",                      "aaa",         0,2, 0,2, 0,2, -1,-1);
    T4("((..)|(.)){2}",                      "aaa",         0,3, 2,3, -1,-1, 2,3);
    T4("((..)|(.)){3}",                      "aaa",         0,3, 2,3, -1,-1, 2,3);
    T4("((..)|(.))*",                        "aaa",         0,3, 2,3, -1,-1, 2,3);
    T4("((..)|(.))",                         "aaaa",        0,2, 0,2, 0,2, -1,-1);
    T7("((..)|(.))((..)|(.))",               "aaaa",        0,4, 0,2, 0,2, -1,-1, 2,4, 2,4, -1,-1);
    T10("((..)|(.))((..)|(.))((..)|(.))",    "aaaa",        0,4, 0,2, 0,2, -1,-1, 2,3, -1,-1, 2,3, 3,4, -1,-1, 3,4);
    T4("((..)|(.)){1}",                      "aaaa",        0,2, 0,2, 0,2, -1,-1);
    T4("((..)|(.)){2}",                      "aaaa",        0,4, 2,4, 2,4, -1,-1);
    T4("((..)|(.)){3}",                      "aaaa",        0,4, 3,4, -1,-1, 3,4);
    T4("((..)|(.))*",                        "aaaa",        0,4, 2,4, 2,4, -1,-1);
    T4("((..)|(.))",                         "aaaaa",       0,2, 0,2, 0,2, -1,-1);
    T7("((..)|(.))((..)|(.))",               "aaaaa",       0,4, 0,2, 0,2, -1,-1, 2,4, 2,4, -1,-1);
    T10("((..)|(.))((..)|(.))((..)|(.))",    "aaaaa",       0,5, 0,2, 0,2, -1,-1, 2,4, 2,4, -1,-1, 4,5, -1,-1, 4,5);
    T4("((..)|(.)){1}",                      "aaaaa",       0,2, 0,2, 0,2, -1,-1);
    T4("((..)|(.)){2}",                      "aaaaa",       0,4, 2,4, 2,4, -1,-1);
    T4("((..)|(.)){3}",                      "aaaaa",       0,5, 4,5, -1,-1, 4,5);
    T4("((..)|(.))*",                        "aaaaa",       0,5, 4,5, -1,-1, 4,5);
    T4("((..)|(.))",                         "aaaaaa",      0,2, 0,2, 0,2, -1,-1);
    T7("((..)|(.))((..)|(.))",               "aaaaaa",      0,4, 0,2, 0,2, -1,-1, 2,4, 2,4, -1,-1);
    T10("((..)|(.))((..)|(.))((..)|(.))",    "aaaaaa",      0,6, 0,2, 0,2, -1,-1, 2,4, 2,4, -1,-1, 4,6, 4,6, -1,-1);
    T4("((..)|(.)){1}",                      "aaaaaa",      0,2, 0,2, 0,2, -1,-1);
    T4("((..)|(.)){2}",                      "aaaaaa",      0,4, 2,4, 2,4, -1,-1);
    T4("((..)|(.)){3}",                      "aaaaaa",      0,6, 4,6, 4,6, -1,-1);
    T4("((..)|(.))*",                        "aaaaaa",      0,6, 4,6, 4,6, -1,-1);
    T2("X(.?){0,}Y",                         "X1234567Y",   0,9, 7,8);
    T2("X(.?){1,}Y",                         "X1234567Y",   0,9, 7,8);
    T2("X(.?){2,}Y",                         "X1234567Y",   0,9, 7,8);
    T2("X(.?){3,}Y",                         "X1234567Y",   0,9, 7,8);
    T2("X(.?){4,}Y",                         "X1234567Y",   0,9, 7,8);
    T2("X(.?){5,}Y",                         "X1234567Y",   0,9, 7,8);
    T2("X(.?){6,}Y",                         "X1234567Y",   0,9, 7,8);
    T2("X(.?){7,}Y",                         "X1234567Y",   0,9, 7,8);
    T2("X(.?){8,}Y",                         "X1234567Y",   0,9, 8,8);
    T2("X(.?){0,8}Y",                        "X1234567Y",   0,9, 7,8);
    T2("X(.?){1,8}Y",                        "X1234567Y",   0,9, 7,8);
    T2("X(.?){2,8}Y",                        "X1234567Y",   0,9, 7,8);
    T2("X(.?){3,8}Y",                        "X1234567Y",   0,9, 7,8);
    T2("X(.?){4,8}Y",                        "X1234567Y",   0,9, 7,8);
    T2("X(.?){5,8}Y",                        "X1234567Y",   0,9, 7,8);
    T2("X(.?){6,8}Y",                        "X1234567Y",   0,9, 7,8);
    T2("X(.?){7,8}Y",                        "X1234567Y",   0,9, 7,8);
    T2("X(.?){8,8}Y",                        "X1234567Y",   0,9, 8,8);
    T3("(a|ab|c|bcd){0,}(d*)",               "ababcd",      0,6, 3,6, 6,6);
    T3("(a|ab|c|bcd){1,}(d*)",               "ababcd",      0,6, 3,6, 6,6);
    T3("(a|ab|c|bcd){2,}(d*)",               "ababcd",      0,6, 3,6, 6,6);
    T3("(a|ab|c|bcd){3,}(d*)",               "ababcd",      0,6, 3,6, 6,6);
    T0("(a|ab|c|bcd){4,}(d*)",               "ababcd");
    T3("(a|ab|c|bcd){0,10}(d*)",             "ababcd",      0,6, 3,6, 6,6);
    T3("(a|ab|c|bcd){1,10}(d*)",             "ababcd",      0,6, 3,6, 6,6);
    T3("(a|ab|c|bcd){2,10}(d*)",             "ababcd",      0,6, 3,6, 6,6);
    T3("(a|ab|c|bcd){3,10}(d*)",             "ababcd",      0,6, 3,6, 6,6);
    T0("(a|ab|c|bcd){4,10}(d*)",             "ababcd");
    T3("(a|ab|c|bcd)*(d*)",                  "ababcd",      0,6, 3,6, 6,6);
    T3("(a|ab|c|bcd)+(d*)",                  "ababcd",      0,6, 3,6, 6,6);
    T3("(ab|a|c|bcd){0,}(d*)",               "ababcd",      0,6, 3,6, 6,6);
    T3("(ab|a|c|bcd){1,}(d*)",               "ababcd",      0,6, 3,6, 6,6);
    T3("(ab|a|c|bcd){2,}(d*)",               "ababcd",      0,6, 3,6, 6,6);
    T3("(ab|a|c|bcd){3,}(d*)",               "ababcd",      0,6, 3,6, 6,6);
    T0("(ab|a|c|bcd){4,}(d*)",               "ababcd");
    T3("(ab|a|c|bcd){0,10}(d*)",             "ababcd",      0,6, 3,6, 6,6);
    T3("(ab|a|c|bcd){1,10}(d*)",             "ababcd",      0,6, 3,6, 6,6);
    T3("(ab|a|c|bcd){2,10}(d*)",             "ababcd",      0,6, 3,6, 6,6);
    T3("(ab|a|c|bcd){3,10}(d*)",             "ababcd",      0,6, 3,6, 6,6);
    T0("(ab|a|c|bcd){4,10}(d*)",             "ababcd");
    T3("(ab|a|c|bcd)*(d*)",                  "ababcd",      0,6, 3,6, 6,6);
    T3("(ab|a|c|bcd)+(d*)",                  "ababcd",      0,6, 3,6, 6,6);

    // rightassoc
    T4("(a|ab)(c|bcd)(d*)",                  "abcd",        0,4, 0,2, 2,3, 3,4);
    T4("(a|ab)(bcd|c)(d*)",                  "abcd",        0,4, 0,2, 2,3, 3,4);
    T4("(ab|a)(c|bcd)(d*)",                  "abcd",        0,4, 0,2, 2,3, 3,4);
    T4("(ab|a)(bcd|c)(d*)",                  "abcd",        0,4, 0,2, 2,3, 3,4);
    T4("(a*)(b|abc)(c*)",                    "abc",         0,3, 0,1, 1,2, 2,3);
    T4("(a*)(abc|b)(c*)",                    "abc",         0,3, 0,1, 1,2, 2,3);
    T4("(a*)(b|abc)(c*)",                    "abc",         0,3, 0,1, 1,2, 2,3);
    T4("(a*)(abc|b)(c*)",                    "abc",         0,3, 0,1, 1,2, 2,3);
    T4("(a|ab)(c|bcd)(d|.*)",                "abcd",        0,4, 0,2, 2,3, 3,4);
    T4("(a|ab)(bcd|c)(d|.*)",                "abcd",        0,4, 0,2, 2,3, 3,4);
    T4("(ab|a)(c|bcd)(d|.*)",                "abcd",        0,4, 0,2, 2,3, 3,4);
    T4("(ab|a)(bcd|c)(d|.*)",                "abcd",        0,4, 0,2, 2,3, 3,4);

    return e;
}

#undef GS
#undef T
#undef T0
#undef T1
#undef T2
#undef T3
#undef T4
#undef T5
#undef T6
#undef T7
