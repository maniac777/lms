
#ifndef _LMSD_H_
#define _LMSD_H_

#include "util.h"
#include "cron/cron.h"
#include "config/config.h"

typedef struct dictionary Config;

#define APIVERSION 5
#define PROGNAME "lmsd"

typedef void (*ConnHandle)();
typedef void (*QueryHandle)();

struct global
{
	int api_version;
	ConnHandle *conn;

	// db functions
	ConnHandle * (*db_connect)(const char *, const char *, const char *, const char *, int, int);
	int (*db_disconnect)(ConnHandle *);
	QueryHandle * (*db_query)(ConnHandle *, char *);
	QueryHandle * (*db_pquery)(ConnHandle *, char *, ...);
	void (*db_free)(QueryHandle **);
	int (*db_exec)(ConnHandle *, char *);
	int (*db_pexec)(ConnHandle *, char *, ...);
	int (*db_last_insert_id)(ConnHandle *, const char *);
	int (*db_begin)(ConnHandle *);
	int (*db_commit)(ConnHandle *);
	int (*db_abort)(ConnHandle *);
	int (*db_nrows)(QueryHandle *);
	int (*db_ncols)(QueryHandle *);
	char * (*db_get_data)(QueryHandle *, int, const char *);
	char * (*db_concat)(int cnt, ...);
	char * (*db_escape)(ConnHandle *, const char *);
	char * (*db_colname)(QueryHandle *, int);

	// config  functions
	char * (*config_getstring)(Config *, char *, char *, char *);
	int (*config_getint)(Config *, char *, char *, int);
	int (*config_getbool)(Config *, char *, char *, int);
	double (*config_getdouble)(Config *, char *, char *, double);

	// util functions
	int (*str_replace)(char **, const char *, const char *);
	char * (*str_save)(char *, const char *);
	char * (*str_concat)(const char *, const char *);
	char * (*str_upc)(const char *);
	char * (*str_lwc)(const char *);
	char * (*va_list_join)(int cnt, char * delim, va_list vl);

};

struct lmsd_module
{
	char *file;
	char *instance;
	Config *ini;
	void *dlh;
	void (*reload)(struct global *, struct lmsd_module *); 
};

struct instance
{
	char *name;
	char *crontab;
	char *module;
};

typedef struct lmsd_module MODULE;
typedef struct global GLOBAL;
typedef struct instance INSTANCE;

#endif
