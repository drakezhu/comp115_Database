#include <stdlib.h>
#include "db.h"

PGconn* connect_to_database(const char* host, const char* dbname, const char* user, const char* password)
{
    char connection_info[100];
    sprintf(connection_info, "host = %s dbname = %s user = %s password = %s", host, dbname, user, password);
    PGconn* connection = PQconnectdb(connection_info);
    ConnStatusType status = PQstatus(connection);
    if (status != CONNECTION_OK) {
        printf("Couldn't connect to database\n");
        exit(1);
    }
    return connection;
}

void disconnect_from_database(PGconn* connection)
{
    PQfinish(connection);
}

void begin_transaction(PGconn* connection, const char* isolation)
{
    
}

int commit_transaction(PGconn* connection)
{
    return -1;
}

PGresult* query(PGconn* connection, const char* sql, int n_params, const char** params)
{
    PGresult* result = PQexecParams(connection, sql, n_params, NULL, params, NULL, NULL, 0);
        ExecStatusType status = PQresultStatus(result);
        if (status == PGRES_FATAL_ERROR) {
            PQclear(result);
            return NULL;
        } else if (status != PGRES_TUPLES_OK) {
            fprintf(stderr, "query failed with status %d: %s\n", status, sql);
            PQclear(result);
            return NULL;
        } else {
            return result;
        };
}

int update(PGconn* connection, const char* sql, int n_params, const char** params)
{
    PGresult* result = PQexecParams(connection, sql, n_params, NULL, params, NULL, NULL, 0);
    ExecStatusType status = PQresultStatus(result);
    if (status == PGRES_FATAL_ERROR) {
        PQclear(result);
        return -1;
    } else if (status != PGRES_COMMAND_OK) {
        fprintf(stderr, "update failed with status %d: %s\n", status, sql);
        PQclear(result);
        return -2;
    } else {
        int update_count = atoi(PQcmdTuples(result));
        PQclear(result);
        return update_count;
    }

}

const char* field(PGresult* result, int row, int column)
{
    return
        PQgetisnull(result, row, column)
        ? NULL
        : PQgetvalue(result, row, column);
}

void end_query(PGresult* result)
{
    PQclear(result);    
}
