#include <stdlib.h>
#include <string.h>
#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYLEX yylex()
#define YYEMPTY -1
#define yyclearin (yychar=(YYEMPTY))
#define yyerrok (yyerrflag=0)
#define YYRECOVERING() (yyerrflag!=0)
#define YYPREFIX "yy"
#line 26 "parse.y"
#include <sys/types.h>
#include <sys/queue.h>
#include <sys/socket.h>
#include <sys/stat.h>

#include <net/if.h>

#include <netinet/in.h>

#include <arpa/inet.h>

#include <ctype.h>
#include <err.h>
#include <errno.h>
#include <event.h>
#include <imsg.h>
#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <syslog.h>
#include <unistd.h>
#include <vis.h>

#include "log.h"
#include "dhcp6leased.h"
#include "frontend.h"

TAILQ_HEAD(files, file)		 files = TAILQ_HEAD_INITIALIZER(files);
struct file 	 *file, *topfile;
int		 check_file_secrecy(int, const char *);
int		 yyparse(void);
int		 yylex(void);
int		 yyerror(const char *, ...)
    __attribute__((__format__ (printf, 1, 2)))
    __attribute__((__nonnull__ (1)));
int		 lookup(char *);
int		 igetc(void);

TAILQ_HEAD(symhead, sym)	 symhead = TAILQ_HEAD_INITIALIZER(symhead);
struct sym {
	TAILQ_ENTRY(sym)	 entry;
	int			 used;
	int			 persist;
	char			*nam;
	char			*val;
};

int	 symset(const char *, const char *, int);
char	*symget(const char *);

static struct dhcp6leased_conf	*conf;
static int			 errors;

static struct iface_conf	*iface_conf;
static struct iface_ia_conf	*iface_ia_conf;

struct iface_conf	*conf_get_iface(char *);
struct iface_pd_conf	*conf_get_pd_iface(char *, int);
void			 addressing_plan(struct iface_ia_conf *);
int			 fls64(uint64_t);

typedef struct {
	union {
		int64_t		 number;
		char		*string;
	} v;
	int lineno;
} YYSTYPE;

#line 84 "parse.c"
#define ERROR 257
#define DELEGATION 258
#define FOR 259
#define ON 260
#define PREFIX 261
#define REQUEST 262
#define RAPID 263
#define COMMIT 264
#define STRING 265
#define NUMBER 266
#define YYERRCODE 256
const short yylhs[] =
	{                                        -1,
    0,    0,    0,    0,    0,    0,    1,    1,    2,    5,
    5,    3,    7,    4,    6,    6,    8,    8,    9,
};
const short yylen[] =
	{                                         2,
    0,    2,    3,    3,    3,    3,    2,    1,    3,    2,
    0,    3,    0,    8,    4,    1,    3,    2,    1,
};
const short yydefred[] =
	{                                      1,
    0,    0,    0,    0,    2,    0,    0,    0,    6,    0,
    0,    0,    3,    4,    5,    0,   12,    8,    0,    0,
    7,    0,   13,    0,   19,    0,   14,   16,    0,    0,
   10,    0,    0,   15,    0,   18,   17,
};
const short yydgoto[] =
	{                                       1,
   19,    6,    7,    8,   30,   27,   24,   32,   28,
};
const short yysindex[] =
	{                                      0,
  -10,   -5, -255,  -50,    0,    3,    4,    5,    0, -242,
 -247, -246,    0,    0,    0, -240,    0,    0, -244, -243,
    0, -241,    0, -122,    0,   13,    0,    0,   13, -239,
    0, -123,   13,    0,   13,    0,    0,};
const short yyrindex[] =
	{                                      0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   -5,    0,
    0,    0,    0,    0,    0, -238,    0,    0, -121,    0,
    0,    0, -121,    0, -121,    0,    0,};
const short yygindex[] =
	{                                      0,
    0,    0,    0,    0,  -26,    0,    0,    0,  -20,
};
#define YYTABLESIZE 255
const short yytable[] =
	{                                       5,
   26,   34,   31,   11,    9,   10,   36,   11,   37,   33,
   12,   35,   13,   14,   15,   16,   17,   23,   18,   20,
   21,   22,   29,    0,    0,   25,   11,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   25,   25,   11,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    2,    0,    0,    0,    0,
    0,    3,    0,    0,    4,
};
const short yycheck[] =
	{                                      10,
  123,  125,   29,  125,   10,  261,   33,  263,   35,   30,
   61,   32,   10,   10,   10,  258,  264,  259,  265,  260,
  265,  265,   10,   -1,   -1,  265,  265,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  265,  265,  265,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  256,   -1,   -1,   -1,   -1,
   -1,  262,   -1,   -1,  265,
};
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 266
#if YYDEBUG
const char * const yyname[] =
	{
"end-of-file",0,0,0,0,0,0,0,0,0,"'\\n'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'='",0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'{'",0,"'}'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"ERROR",
"DELEGATION","FOR","ON","PREFIX","REQUEST","RAPID","COMMIT","STRING","NUMBER",
};
const char * const yyrule[] =
	{"$accept : grammar",
"grammar :",
"grammar : grammar '\\n'",
"grammar : grammar varset '\\n'",
"grammar : grammar conf_main '\\n'",
"grammar : grammar ia_pd '\\n'",
"grammar : grammar error '\\n'",
"string : string STRING",
"string : STRING",
"varset : STRING '=' string",
"optnl : '\\n' optnl",
"optnl :",
"conf_main : REQUEST RAPID COMMIT",
"$$1 :",
"ia_pd : REQUEST PREFIX DELEGATION ON STRING FOR $$1 iface_block",
"iface_block : '{' optnl ifaceopts_l '}'",
"iface_block : ifaceoptsl",
"ifaceopts_l : ifaceopts_l ifaceoptsl optnl",
"ifaceopts_l : ifaceoptsl optnl",
"ifaceoptsl : STRING",
};
#endif
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH 10000
#endif
#endif
#define YYINITSTACKSIZE 200
/* LINTUSED */
int yydebug;
int yynerrs;
int yyerrflag;
int yychar;
short *yyssp;
YYSTYPE *yyvsp;
YYSTYPE yyval;
YYSTYPE yylval;
short *yyss;
short *yysslim;
YYSTYPE *yyvs;
unsigned int yystacksize;
int yyparse(void);
#line 210 "parse.y"

struct keywords {
	const char	*k_name;
	int		 k_val;
};

int
yyerror(const char *fmt, ...)
{
	va_list		 ap;
	char		*msg;

	file->errors++;
	va_start(ap, fmt);
	if (vasprintf(&msg, fmt, ap) == -1)
		fatalx("yyerror vasprintf");
	va_end(ap);
	logit(LOG_CRIT, "%s:%d: %s", file->name, yylval.lineno, msg);
	free(msg);
	return (0);
}

int
kw_cmp(const void *k, const void *e)
{
	return (strcmp(k, ((const struct keywords *)e)->k_name));
}

int
lookup(char *s)
{
	/* This has to be sorted always. */
	static const struct keywords keywords[] = {
		{"commit",	COMMIT},
		{"delegation",	DELEGATION},
		{"for",		FOR},
		{"on",		ON},
		{"prefix",	PREFIX},
		{"rapid",	RAPID},
		{"request",	REQUEST},
	};
	const struct keywords	*p;

	p = bsearch(s, keywords, sizeof(keywords)/sizeof(keywords[0]),
	    sizeof(keywords[0]), kw_cmp);

	if (p)
		return (p->k_val);
	else
		return (STRING);
}

#define START_EXPAND	1
#define DONE_EXPAND	2

static int	expanding;

int
igetc(void)
{
	int	c;

	while (1) {
		if (file->ungetpos > 0)
			c = file->ungetbuf[--file->ungetpos];
		else
			c = getc(file->stream);

		if (c == START_EXPAND)
			expanding = 1;
		else if (c == DONE_EXPAND)
			expanding = 0;
		else
			break;
	}
	return (c);
}

int
lgetc(int quotec)
{
	int		c, next;

	if (quotec) {
		if ((c = igetc()) == EOF) {
			yyerror("reached end of file while parsing "
			    "quoted string");
			if (file == topfile || popfile() == EOF)
				return (EOF);
			return (quotec);
		}
		return (c);
	}

	while ((c = igetc()) == '\\') {
		next = igetc();
		if (next != '\n') {
			c = next;
			break;
		}
		yylval.lineno = file->lineno;
		file->lineno++;
	}

	if (c == EOF) {
		/*
		 * Fake EOL when hit EOF for the first time. This gets line
		 * count right if last line in included file is syntactically
		 * invalid and has no newline.
		 */
		if (file->eof_reached == 0) {
			file->eof_reached = 1;
			return ('\n');
		}
		while (c == EOF) {
			if (file == topfile || popfile() == EOF)
				return (EOF);
			c = igetc();
		}
	}
	return (c);
}

void
lungetc(int c)
{
	if (c == EOF)
		return;

	if (file->ungetpos >= file->ungetsize) {
		void *p = reallocarray(file->ungetbuf, file->ungetsize, 2);
		if (p == NULL)
			err(1, "lungetc");
		file->ungetbuf = p;
		file->ungetsize *= 2;
	}
	file->ungetbuf[file->ungetpos++] = c;
}

int
findeol(void)
{
	int	c;

	/* Skip to either EOF or the first real EOL. */
	while (1) {
		c = lgetc(0);
		if (c == '\n') {
			file->lineno++;
			break;
		}
		if (c == EOF)
			break;
	}
	return (ERROR);
}

int
yylex(void)
{
	char	 buf[8096];
	char	*p, *val;
	int	 quotec, next, c;
	int	 token;

top:
	p = buf;
	while ((c = lgetc(0)) == ' ' || c == '\t')
		; /* nothing */

	yylval.lineno = file->lineno;
	if (c == '#')
		while ((c = lgetc(0)) != '\n' && c != EOF)
			; /* nothing */
	if (c == '$' && !expanding) {
		while (1) {
			if ((c = lgetc(0)) == EOF)
				return (0);

			if (p + 1 >= buf + sizeof(buf) - 1) {
				yyerror("string too long");
				return (findeol());
			}
			if (isalnum(c) || c == '_') {
				*p++ = c;
				continue;
			}
			*p = '\0';
			lungetc(c);
			break;
		}
		val = symget(buf);
		if (val == NULL) {
			yyerror("macro '%s' not defined", buf);
			return (findeol());
		}
		p = val + strlen(val) - 1;
		lungetc(DONE_EXPAND);
		while (p >= val) {
			lungetc((unsigned char)*p);
			p--;
		}
		lungetc(START_EXPAND);
		goto top;
	}

	switch (c) {
	case '\'':
	case '"':
		quotec = c;
		while (1) {
			if ((c = lgetc(quotec)) == EOF)
				return (0);
			if (c == '\n') {
				file->lineno++;
				continue;
			} else if (c == '\\') {
				if ((next = lgetc(quotec)) == EOF)
					return (0);
				if (next == quotec || next == ' ' ||
				    next == '\t')
					c = next;
				else if (next == '\n') {
					file->lineno++;
					continue;
				} else
					lungetc(next);
			} else if (c == quotec) {
				*p = '\0';
				break;
			} else if (c == '\0') {
				yyerror("syntax error");
				return (findeol());
			}
			if (p + 1 >= buf + sizeof(buf) - 1) {
				yyerror("string too long");
				return (findeol());
			}
			*p++ = c;
		}
		yylval.v.string = strdup(buf);
		if (yylval.v.string == NULL)
			err(1, "yylex: strdup");
		return (STRING);
	}

#define allowed_to_end_number(x) \
	(isspace(x) || x == ')' || x ==',' || x == '/' || x == '}' || x == '=')

	if (c == '-' || isdigit(c)) {
		do {
			*p++ = c;
			if ((size_t)(p-buf) >= sizeof(buf)) {
				yyerror("string too long");
				return (findeol());
			}
		} while ((c = lgetc(0)) != EOF && isdigit(c));
		lungetc(c);
		if (p == buf + 1 && buf[0] == '-')
			goto nodigits;
		if (c == EOF || allowed_to_end_number(c)) {
			const char *errstr = NULL;

			*p = '\0';
			yylval.v.number = strtonum(buf, LLONG_MIN,
			    LLONG_MAX, &errstr);
			if (errstr) {
				yyerror("\"%s\" invalid number: %s",
				    buf, errstr);
				return (findeol());
			}
			return (NUMBER);
		} else {
nodigits:
			while (p > buf + 1)
				lungetc((unsigned char)*--p);
			c = (unsigned char)*--p;
			if (c == '-')
				return (c);
		}
	}

#define allowed_in_string(x) \
	(isalnum(x) || (ispunct(x) && x != '(' && x != ')' && \
	x != '{' && x != '}' && \
	x != '!' && x != '=' && x != '#' && \
	x != ','))

	if (isalnum(c) || c == ':' || c == '_') {
		do {
			*p++ = c;
			if ((size_t)(p-buf) >= sizeof(buf)) {
				yyerror("string too long");
				return (findeol());
			}
		} while ((c = lgetc(0)) != EOF && (allowed_in_string(c)));
		lungetc(c);
		*p = '\0';
		if ((token = lookup(buf)) == STRING)
			if ((yylval.v.string = strdup(buf)) == NULL)
				err(1, "yylex: strdup");
		return (token);
	}
	if (c == '\n') {
		yylval.lineno = file->lineno;
		file->lineno++;
	}
	if (c == EOF)
		return (0);
	return (c);
}

int
check_file_secrecy(int fd, const char *fname)
{
	struct stat	st;

	if (fstat(fd, &st)) {
		log_warn("cannot stat %s", fname);
		return (-1);
	}
	if (st.st_uid != 0 && st.st_uid != getuid()) {
		log_warnx("%s: owner not root or current user", fname);
		return (-1);
	}
	if (st.st_mode & (S_IWGRP | S_IXGRP | S_IRWXO)) {
		log_warnx("%s: group writable or world read/writable", fname);
		return (-1);
	}
	return (0);
}

struct file *
pushfile(const char *name, int secret)
{
	struct file	*nfile;

	if ((nfile = calloc(1, sizeof(struct file))) == NULL) {
		log_warn("calloc");
		return (NULL);
	}
	if ((nfile->name = strdup(name)) == NULL) {
		log_warn("strdup");
		free(nfile);
		return (NULL);
	}
	if ((nfile->stream = fopen(nfile->name, "r")) == NULL) {
		log_warn("%s", nfile->name);
		free(nfile->name);
		free(nfile);
		return (NULL);
	} else if (secret &&
	    check_file_secrecy(fileno(nfile->stream), nfile->name)) {
		fclose(nfile->stream);
		free(nfile->name);
		free(nfile);
		return (NULL);
	}
	nfile->lineno = TAILQ_EMPTY(&files) ? 1 : 0;
	nfile->ungetsize = 16;
	nfile->ungetbuf = malloc(nfile->ungetsize);
	if (nfile->ungetbuf == NULL) {
		log_warn("malloc");
		fclose(nfile->stream);
		free(nfile->name);
		free(nfile);
		return (NULL);
	}
	TAILQ_INSERT_TAIL(&files, nfile, entry);
	return (nfile);
}

int
popfile(void)
{
	struct file	*prev;

	if ((prev = TAILQ_PREV(file, files, entry)) != NULL)
		prev->errors += file->errors;

	TAILQ_REMOVE(&files, file, entry);
	fclose(file->stream);
	free(file->name);
	free(file->ungetbuf);
	free(file);
	file = prev;
	return (file ? 0 : EOF);
}

struct dhcp6leased_conf *
parse_config(const char *filename)
{
	struct sym		*sym, *next;
	struct iface_conf	*iface;
	struct iface_ia_conf	*ia_conf;

	conf = config_new_empty();

	file = pushfile(filename, 0);
	if (file == NULL) {
		free(conf);
		return (NULL);
	}
	topfile = file;

	yyparse();
	errors = file->errors;
	popfile();

	/* Free macros and check which have not been used. */
	TAILQ_FOREACH_SAFE(sym, &symhead, entry, next) {
		if ((log_getverbose() == 2) && !sym->used)
			fprintf(stderr, "warning: macro '%s' not used\n",
			    sym->nam);
		if (!sym->persist) {
			free(sym->nam);
			free(sym->val);
			TAILQ_REMOVE(&symhead, sym, entry);
			free(sym);
		}
	}

	if (errors) {
		config_clear(conf);
		return (NULL);
	}

	SIMPLEQ_FOREACH(iface, &conf->iface_list, entry) {
		SIMPLEQ_FOREACH(ia_conf, &iface->iface_ia_list, entry) {
			addressing_plan(ia_conf);
		}
	}
	return (conf);
}

int
symset(const char *nam, const char *val, int persist)
{
	struct sym	*sym;

	TAILQ_FOREACH(sym, &symhead, entry) {
		if (strcmp(nam, sym->nam) == 0)
			break;
	}

	if (sym != NULL) {
		if (sym->persist == 1)
			return (0);
		else {
			free(sym->nam);
			free(sym->val);
			TAILQ_REMOVE(&symhead, sym, entry);
			free(sym);
		}
	}
	if ((sym = calloc(1, sizeof(*sym))) == NULL)
		return (-1);

	sym->nam = strdup(nam);
	if (sym->nam == NULL) {
		free(sym);
		return (-1);
	}
	sym->val = strdup(val);
	if (sym->val == NULL) {
		free(sym->nam);
		free(sym);
		return (-1);
	}
	sym->used = 0;
	sym->persist = persist;
	TAILQ_INSERT_TAIL(&symhead, sym, entry);
	return (0);
}

char *
symget(const char *nam)
{
	struct sym	*sym;

	TAILQ_FOREACH(sym, &symhead, entry) {
		if (strcmp(nam, sym->nam) == 0) {
			sym->used = 1;
			return (sym->val);
		}
	}
	return (NULL);
}

struct iface_conf *
conf_get_iface(char *name)
{
	struct iface_conf	*iface;
	size_t			 n;

	SIMPLEQ_FOREACH(iface, &conf->iface_list, entry) {
		if (strcmp(name, iface->name) == 0)
			return (iface);
	}

	iface = calloc(1, sizeof(*iface));
	if (iface == NULL)
		errx(1, "%s: calloc", __func__);
	n = strlcpy(iface->name, name, sizeof(iface->name));
	if (n >= sizeof(iface->name))
		errx(1, "%s: name too long", __func__);
	SIMPLEQ_INIT(&iface->iface_ia_list);

	SIMPLEQ_INSERT_TAIL(&conf->iface_list, iface, entry);

	return (iface);
}

struct iface_pd_conf *
conf_get_pd_iface(char *name, int prefixlen)
{
	struct iface_ia_conf	*iface_ia;
	struct iface_pd_conf	*iface_pd;
	size_t			 n;

	if (strcmp(name, "reserve") != 0) {
		SIMPLEQ_FOREACH(iface_ia, &iface_conf->iface_ia_list,
		    entry) {
			SIMPLEQ_FOREACH(iface_pd, &iface_ia->iface_pd_list,
			    entry) {
				if (strcmp(name, iface_pd->name) == 0)
					return NULL;
			}
		}
	}

	iface_pd = calloc(1, sizeof(*iface_pd));
	if (iface_pd == NULL)
		err(1, "%s: calloc", __func__);
	n = strlcpy(iface_pd->name, name, sizeof(iface_pd->name));
	if (n >= sizeof(iface_pd->name))
		errx(1, "%s: name too long", __func__);
	iface_pd->prefix_len = prefixlen;

	SIMPLEQ_INSERT_TAIL(&iface_ia_conf->iface_pd_list, iface_pd, entry);

	return (iface_pd);
}

static inline uint64_t
get_shift(int plen)
{
	if (plen > 64)
		plen -= 64;

	return 1ULL << (64 - plen);
}

void
addressing_plan(struct iface_ia_conf *ia_conf)
{
	struct iface_pd_conf	*pd_conf;
	uint64_t		*p, lo_counter, hi_counter, lo_shift, hi_shift;
	int			 prev_plen = -1;

	lo_counter = hi_counter = 0;

	SIMPLEQ_FOREACH(pd_conf, &ia_conf->iface_pd_list, entry) {
		/* not the first prefix */
		if (ia_conf->prefix_len != 0) {
			lo_shift = hi_shift = 0;
			if (prev_plen > pd_conf->prefix_len) {
				if (pd_conf->prefix_len > 64)
					lo_shift =
					    get_shift(pd_conf->prefix_len);
				else
					hi_shift =
					    get_shift(pd_conf->prefix_len);
			} else  {
				if (prev_plen > 64)
					lo_shift = get_shift(prev_plen);
				else
					hi_shift = get_shift(prev_plen);
			}

			if (lo_shift != 0) {
				if (lo_counter > UINT64_MAX - lo_shift) {
					/* overflow */
					hi_counter++;
					lo_counter = 0;
				} else {
					lo_counter += lo_shift;
					/* remove all lower bits */
					lo_counter &= ~(lo_shift - 1);
				}
			} else {
				hi_counter += hi_shift;
				/* remove all lower bits */
				hi_counter &= ~(hi_shift - 1);
				lo_counter = 0;
			}

		} else
			ia_conf->prefix_len = pd_conf->prefix_len;

		p = (uint64_t *)&pd_conf->prefix_mask.s6_addr;
		*p |= htobe64(hi_counter);

		p = (uint64_t *)&pd_conf->prefix_mask.s6_addr[8];
		*p |= htobe64(lo_counter);

		prev_plen = pd_conf->prefix_len;
	}

	if (hi_counter != 0)
		ia_conf->prefix_len = 64 - fls64(hi_counter);
	else if (lo_counter != 0)
		ia_conf->prefix_len = 128 - fls64(lo_counter);
}

/* from NetBSD's sys/sys/bitops.h */
/*-
 * Copyright (c) 2007, 2010 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Christos Zoulas and Joerg Sonnenberger.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
int
fls64(uint64_t _n)
{
	int _v;

	if (!_n)
		return 0;

	_v = 64;
	if ((_n & 0xFFFFFFFF00000000ULL) == 0) {
		_n <<= 32;
		_v -= 32;
	}
	if ((_n & 0xFFFF000000000000ULL) == 0) {
		_n <<= 16;
		_v -= 16;
	}
	if ((_n & 0xFF00000000000000ULL) == 0) {
		_n <<= 8;
		_v -= 8;
	}
	if ((_n & 0xF000000000000000ULL) == 0) {
		_n <<= 4;
		_v -= 4;
	}
	if ((_n & 0xC000000000000000ULL) == 0) {
		_n <<= 2;
		_v -= 2;
	}
	if ((_n & 0x8000000000000000ULL) == 0) {
		//_n <<= 1;
		_v -= 1;
	}
	return _v;
}
#line 930 "parse.c"
/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(void)
{
    unsigned int newsize;
    long sslen;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = yystacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;
    sslen = yyssp - yyss;
#ifdef SIZE_MAX
#define YY_SIZE_MAX SIZE_MAX
#else
#define YY_SIZE_MAX 0xffffffffU
#endif
    if (newsize && YY_SIZE_MAX / newsize < sizeof *newss)
        goto bail;
    newss = (short *)realloc(yyss, newsize * sizeof *newss);
    if (newss == NULL)
        goto bail;
    yyss = newss;
    yyssp = newss + sslen;
    if (newsize && YY_SIZE_MAX / newsize < sizeof *newvs)
        goto bail;
    newvs = (YYSTYPE *)realloc(yyvs, newsize * sizeof *newvs);
    if (newvs == NULL)
        goto bail;
    yyvs = newvs;
    yyvsp = newvs + sslen;
    yystacksize = newsize;
    yysslim = yyss + newsize - 1;
    return 0;
bail:
    if (yyss)
            free(yyss);
    if (yyvs)
            free(yyvs);
    yyss = yyssp = NULL;
    yyvs = yyvsp = NULL;
    yystacksize = 0;
    return -1;
}

#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab
int
yyparse(void)
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")))
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif /* YYDEBUG */

    yynerrs = 0;
    yyerrflag = 0;
    yychar = (-1);

    if (yyss == NULL && yygrowstack()) goto yyoverflow;
    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yysslim && yygrowstack())
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = (-1);
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;
#if defined(__GNUC__)
    goto yynewerror;
#endif
yynewerror:
    yyerror("syntax error");
#if defined(__GNUC__)
    goto yyerrlab;
#endif
yyerrlab:
    ++yynerrs;
yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yysslim && yygrowstack())
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = (-1);
        goto yyloop;
    }
yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yyvsp[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 6:
#line 111 "parse.y"
{ file->errors++; }
break;
case 7:
#line 114 "parse.y"
{
			if (asprintf(&yyval.v.string, "%s %s", yyvsp[-1].v.string, yyvsp[0].v.string) == -1) {
				free(yyvsp[-1].v.string);
				free(yyvsp[0].v.string);
				yyerror("string: asprintf");
				YYERROR;
			}
			free(yyvsp[-1].v.string);
			free(yyvsp[0].v.string);
		}
break;
case 9:
#line 127 "parse.y"
{
			char *s = yyvsp[-2].v.string;
			if (log_getverbose() == 1)
				printf("%s = \"%s\"\n", yyvsp[-2].v.string, yyvsp[0].v.string);
			while (*s++) {
				if (isspace((unsigned char)*s)) {
					yyerror("macro name cannot contain "
					    "whitespace");
					free(yyvsp[-2].v.string);
					free(yyvsp[0].v.string);
					YYERROR;
				}
			}
			if (symset(yyvsp[-2].v.string, yyvsp[0].v.string, 0) == -1)
				fatal("cannot store variable");
			free(yyvsp[-2].v.string);
			free(yyvsp[0].v.string);
		}
break;
case 12:
#line 151 "parse.y"
{
			conf->rapid_commit = 1;
		}
break;
case 13:
#line 156 "parse.y"
{
			iface_conf = conf_get_iface(yyvsp[-1].v.string);
			iface_ia_conf = calloc(1, sizeof(*iface_ia_conf));
			if (iface_ia_conf == NULL)
				err(1, "%s: calloc", __func__);
			iface_ia_conf->id = iface_conf->ia_count++;
			if (iface_conf->ia_count > MAX_IA) {
				yyerror("Too many prefix delegation requests");
				YYERROR;
			}
			SIMPLEQ_INIT(&iface_ia_conf->iface_pd_list);
			SIMPLEQ_INSERT_TAIL(&iface_conf->iface_ia_list,
			    iface_ia_conf, entry);
		}
break;
case 14:
#line 169 "parse.y"
{
			iface_conf = NULL;
			iface_ia_conf = NULL;
		}
break;
case 19:
#line 183 "parse.y"
{
			struct iface_pd_conf	*iface_pd_conf;
			int			 prefixlen;
			char			*p;
			const char		*errstr;

			p = strchr(yyvsp[0].v.string, '/');
			if (p != NULL) {
				*p++ = '\0';
				prefixlen = strtonum(p, 0, 128, &errstr);
				if (errstr != NULL) {
					yyerror("error parsing interface "
					    "\"%s/%s\"", yyvsp[0].v.string, p);
					free(yyvsp[0].v.string);
					YYERROR;
				}
			} else
				prefixlen = 64;
			if ((iface_pd_conf = conf_get_pd_iface(yyvsp[0].v.string, prefixlen))
			    == NULL) {
				yyerror("duplicate interface %s", yyvsp[0].v.string);
				free(yyvsp[0].v.string);
				YYERROR;
			}
		}
break;
#line 1218 "parse.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yysslim && yygrowstack())
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;
yyoverflow:
    yyerror("yacc stack overflow");
yyabort:
    if (yyss)
            free(yyss);
    if (yyvs)
            free(yyvs);
    yyss = yyssp = NULL;
    yyvs = yyvsp = NULL;
    yystacksize = 0;
    return (1);
yyaccept:
    if (yyss)
            free(yyss);
    if (yyvs)
            free(yyvs);
    yyss = yyssp = NULL;
    yyvs = yyvsp = NULL;
    yystacksize = 0;
    return (0);
}
