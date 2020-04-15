#include <cstdlib>
#include "db.h"

PGconn* connect_to_database(const char* host, const char* dbname, const char* user, const char* password)
{
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
    return cnxn
}

void disconnect_from_database(PGconn* connection)
{
    PQfinish(connection);
}

PGresult* query(PGconn* connection, const char* sql, int n_params, const char** params)
{
    PGresult *res = PQexecParams(connection,
    sql,
    n_params,
    NULL,
    params,
    NULL,
    NULL,
    0
    )
    return res;
}

int update(PGconn* connection, const char* sql, int n_params, const char** params)
{
    PGresult *res = PQexecParams(connection,
    sql,
    n_params,
    NULL,
    params,
    NULL,
    NULL,
    0
    );
    if (PQresultStatus(res) == PGRES_FATAL_ERROR)
    {
        PQclear(res);
        return -1;
    }
    else if (PQresultStatus(res) == PGRES_COMMAND_OK)
    {
        return atoi(PQcmdTuples(res));
    }
    fprintf(stderr, "Update Failed\n");
    PQclear(res);
    return -2;
}

const char* field(PGresult* result, int row, int column)
{
    return NULL;
}

void end_query(PGresult* result)
{
}

void oops(PGconn *cnxn, const char* problem)
{
    fprintf(stderr, "%s: %s", problem, PQerrorMessage(cnxn));
    PQfinish(cnxn);
    exit(1);
}