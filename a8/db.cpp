#include <cstdlib>
#include "db.h"

PGconn* connect_to_database(const char* host, const char* dbname, const char* user, const char* password)
{
    printf("hello world!\n");
    char cnxn_info[255];
    strcpy(cnxn_info,"host = ");
    strcat(cnxn_info,host);
    strcat(cnxn_info, " dbname = ");
    strcat(cnxn_info, dbname);
    strcat(cnxn_info, " user = ");
    strcat(cnxn_info, user);
    strcat(cnxn_info, " password = ");
    strcat(cnxn_info, password);
     PGconn * cnxn = PQconnectdb(cnxn_info);
     if (PQstatus(cnxn) != CONNECTION_OK)
     {
          oops(cnxn, "cnxnection to database failed");
     }
}

void disconnect_from_database(PGconn* connection)
{
    PQfinish(cnxn);
}

PGresult* query(PGconn* connection, const char* sql, int n_params, const char** params)
{
    return NULL;
}

int update(PGconn* connection, const char* sql, int n_params, const char** params)
{
    return -1;
}

const char* field(PGresult* result, int row, int column)
{
    return NULL;
}

void end_query(PGresult* result)
{
}

static void oops(PGconn *cnxn, const char* problem)
{
    fprintf(stderr, "%s: %s", problem, PQerrorMessage(cnxn));
    PQfinish(cnxn);
    exit(1);
}