#include <cstdlib>
#include "db.h"

PGconn* connect_to_database(const char* host, const char* dbname, const char* user, const char* password)
{
    return NULL;
}

void disconnect_from_database(PGconn* connection)
{
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
