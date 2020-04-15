#include <cstdlib>
#include <cstdio>
#include <libpq-fe.h>
#include <cstring>
#include "msg.h"
#include "db.h"

static const char* INSERT_MEMBER =
    "insert into member(name, birth_date) values($1, $2)";

static const char* INSERT_MESSAGE =
    "insert into message(message_date, message_text) values($1, $2)";

static const char* INSERT_ROUTING =
    "select store_routing($1, $2, $3)";

static const char* PK_VALUE =
    "select lastval()";

static const char* BIRTH_DATE_QUERY =
    "select birth_date from member where name = $1";

static const char* SENDER_AND_RECEIVER_QUERY = ""
    "select distinct f.name, t.name\n"
    "from member f join routing r on f.member_id = r.from_member_id\n"
    "              join member t on r.to_member_id = t.member_id\n"
    "              join message m on r.message_id = m.message_id\n"
    "where m.message_date = $1\n"
    "order by f.name, t.name";


// API

int add_member(PGconn* connection, const char* name, const char* birth_date)
{
    const char* params[] = {name, birth_date};

    PGresult * res = query(connection, INSERT_MEMBER, 2, params);
        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
            PQclear(res);
            return -1;
        }
        PQclear(res);
    res = PQexec(connection, "select lastval()");
    int member_id = atoi(PQgetvalue(res, 0, 0));
    PQclear(res);
    return member_id;
}

int add_message(PGconn* connection, const char* message_date, const char* message_text)
{
    const char* params[] = {message_date, message_text};

    PGresult * res = query(connection, INSERT_MESSAGE, 2, params);
        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
            PQclear(res);
            return -1;
        }
        PQclear(res);
    res = PQexec(connection, "select lastval()");
    int message_id = atoi(PQgetvalue(res, 0, 0));
    PQclear(res);
    return message_id;
}

int add_routing(PGconn* connection, const char* from_member_id, const char* to_member_id, const char* message_ids)
{
    // Run INSERT_ROUTING
    // Return the value returned by the insert_routing stored procedure
    return -1;
}

int birth_date(PGconn* connection, const char* name, char* buffer)
{
    // Run BIRTH_DATE_QUERY
    return -1;
}

int senders_and_receivers(PGconn* connection, const char* date, int max_results, char* buffer[])
{
    // Run SENDER_AND_RECEIVER_QUERY
    return -1;
}
